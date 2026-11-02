#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sha256.h"

typedef struct {
    int height;
    char data[64];
    char prev_hash[65];
    char hash[65];
} Block;

int simulate_51_attack(int enable_defense) {
    printf("--- EXERCICE 1 : ATTAQUE DES 51%% & DOUBLE-SPENDING (Defense : %s) ---\n",
           enable_defense ? "ACTIVEE" : "DESACTIVEE");

    double attacker_power = 0.55; // 55% du hashrate total
    int honest_chain_len = 0;
    int private_chain_len = 0;
    int max_rounds = 100;
    int double_spend_success = 0;

    printf("[ETAPE 1] Transaction victime sur la chaine publique : \"Attaquant -> Marchand : 1000 Tokens\"\n");
    printf("[ETAPE 2] L'attaquant mine en secret sa branche privee : \"Attaquant -> Moi-meme : 1000 Tokens\"\n\n");

    for (int r = 1; r <= max_rounds; r++) {
        double p = (double)rand() / RAND_MAX;
        if (p < attacker_power) {
            private_chain_len++; // L'attaquant trouve un bloc secret
        } else {
            honest_chain_len++;  // Les honnetes avancent sur la chaine publique
        }

        // L'attaquant tente de diffuser sa chaine des qu'il depasse les confirmations
        if (honest_chain_len >= 5 && private_chain_len > honest_chain_len) {
            int reorg_depth = honest_chain_len;
            printf(">>> [Round %2d] L'attaquant diffuse sa chaine privee (Longueur : %d vs Publique : %d)\n",
                   r, private_chain_len, honest_chain_len);
            printf("    -> Profondeur de reorganisation demandee : %d blocs\n", reorg_depth);

            if (enable_defense) {
                // CONTRE-MESURE : Checkpoint & seuil max de reorg = 3 blocs
                if (reorg_depth > 3) {
                    printf("    [ALERTE SECURITE] Reorg depth = %d > seuil max autorise (3) !\n", reorg_depth);
                    printf("    [ACTION DEFENSE] Chaine privee REJETEE. Le double-spending a ECHOUE !\n\n");
                    return 0; // Attaque contrée
                }
            } else {
                // SANS DEFENSE : Regle de la chaine la plus longue acceptee aveuglement
                printf("    [VULNERABILITE] Le reseau adopte la chaine de l'attaquant (plus longue) !\n");
                printf("    [SUCCES ATTAQUE] La transaction du Marchand a DISPARU. Vol de 1000 Tokens confirme.\n\n");
                return 1; // Attaque réussie
            }
        }
    }
    return 0;
}

int main() {
    srand(42);

    // Test 1 : Sans défense
    simulate_51_attack(0);

    // Test 2 : Avec module de mitigation
    simulate_51_attack(1);

    return 0;
}
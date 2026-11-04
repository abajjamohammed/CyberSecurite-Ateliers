#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

int check_zeroes(const char *hash, int z) {
    for (int i = 0; i < z; i++) if (hash[i] != '0') return 0;
    return 1;
}

int main() {
    printf("========================================================================\n");
    printf("   BLOCK WITHHOLDING (BWA) EN POOL SUR LA BLOCKCHAIN (ATELIER 1)        \n");
    printf("========================================================================\n\n");

    Blockchain pool_chain;
    init_blockchain(&pool_chain, 3); // Difficulte reseau = 3 zeros

    Block b;
    b.index = 1;
    get_time(b.timestamp, sizeof(b.timestamp));
    strcpy(b.data, "Transactions de la Mining Pool");
    strcpy(b.prev_hash, pool_chain.chain[0].hash);

    int shares = 0;
    int blocks_found = 0;
    int blocks_sabotaged = 0;

    printf("[MINAGE REEL] Calcul des nonces avec hash_block() de l'Atelier 1...\n");
    for (unsigned long n = 0; n < 40000; n++) {
        b.nonce = n;
        hash_block(&b, b.hash);

        // Share pour la pool (difficulte 1 zero)
        if (check_zeroes(b.hash, 1)) {
            shares++;

            // Vrai bloc complet pour la Blockchain (difficulte 3 zeros)
            if (check_zeroes(b.hash, 3)) {
                blocks_found++;
                blocks_sabotaged++; // Le pirate ne l'ajoute JAMAIS a pool_chain !
            }
        }
    }

    printf("\n>>> SCENARIO 1 : SANS DEFENSE (Sabotage reussi) <<<\n");
    printf("  - Shares comptabilisees pour payer le pirate : %d\n", shares);
    printf("  - Vrais blocs trouves pour la Blockchain     : %d\n", blocks_found);
    printf("  - Blocs reellement ajoutes a la Blockchain    : 0 (100%% sabotes)\n");
    printf("  - Perte subie par la pool                    : %.2f BTC\n\n", blocks_sabotaged * 6.25);

    printf(">>> SCENARIO 2 : AVEC DEFENSE (Audit Statistique) <<<\n");
    double expected = shares / 256.0;
    double eff = ((double)(blocks_found - blocks_sabotaged) / expected) * 100.0;
    printf("  [DETECTION] Incoherence : %.1f blocs attendus selon les shares mais 0 bloc obtenu !\n", expected);
    printf("              Efficacite = %.1f%% -> Saboteur identifie !\n", eff);
    printf("  [DEFENSE] Mineur malveillant BANNI de la pool et gains bloques (Perte: 0 BTC).\n");

    return 0;
}
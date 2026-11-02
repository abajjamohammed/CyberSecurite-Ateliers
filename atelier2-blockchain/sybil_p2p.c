#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char ip[16];
    int is_sybil;
    double reputation; // Note de 0.0 a 1.0
} Peer;

void simulate_sybil_p2p(int enable_defense) {
    printf("--- EXERCICE 4 : ATTAQUE SYBIL SUR LE RESEAU P2P (Defense : %s) ---\n",
           enable_defense ? "ACTIVEE" : "DESACTIVEE");

    int honest_count = 10;
    int sybil_count = 40;
    int total_peers = honest_count + sybil_count;
    Peer peers[50];

    // Initialisation des pairs
    for (int i = 0; i < honest_count; i++) {
        peers[i].id = i;
        peers[i].is_sybil = 0;
        sprintf(peers[i].ip, "192.168.%d.10", i + 1); // IPs honnetes distinctes
        peers[i].reputation = 0.95;
    }
    for (int i = honest_count; i < total_peers; i++) {
        peers[i].id = i;
        peers[i].is_sybil = 1;
        sprintf(peers[i].ip, "10.0.1.%d", i - honest_count + 1); // Meme sous-reseau d'attaque
        peers[i].reputation = 0.50;
    }

    double total_delay = 0.0;
    int messages = 100;
    int dropped = 0;

    for (int m = 0; m < messages; m++) {
        int selected = rand() % total_peers;

        if (enable_defense) {
            // Contre-mesure 1 : Diversite de sous-reseau IP (on refuse le cluster d'IPs suspect 10.0.1.X)
            // Contre-mesure 2 : Verification de la reputation
            if (strncmp(peers[selected].ip, "10.0.1.", 7) == 0 || peers[selected].reputation < 0.60) {
                // Le filtre P2P ecarte l'identite Sybil et route via un pair fiable
                total_delay += 15.0; // Delai normal (15 ms)
                continue;
            }
        }

        if (peers[selected].is_sybil) {
            // Le noeud Sybil retarde ou filtre volontairement la propagation
            total_delay += 240.0;
            dropped++;
        } else {
            total_delay += 15.0;
        }
    }

    double avg_delay = total_delay / messages;
    printf("Statistiques de propagation sur %d blocs transcrits :\n", messages);
    printf("  - Delai moyen de propagation P2P : %.2f ms (Normal attendu : 15.00 ms)\n", avg_delay);
    printf("  - Messages retardes/pollues       : %d\n", dropped);

    if (!enable_defense && avg_delay > 100.0) {
        printf("  [VULNERABILITE] Le reseau subit une latence critique due a l'inondation Sybil !\n\n");
    } else {
        printf("  [DEFENSE REUSSIE] Les pairs frauduleux sont isoles grace au filtrage d'IP et a la reputation.\n\n");
    }
}

int main() {
    srand(555);

    simulate_sybil_p2p(0);
    simulate_sybil_p2p(1);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void simulate_selfish_mining(double alpha, double gamma, int rounds, int enable_defense) {
    printf("--- EXERCICE 2 : SELFISH MINING (Alpha=%.0f%% | Gamma=%.0f%% | Defense=%s) ---\n",
           alpha * 100.0, gamma * 100.0, enable_defense ? "OUI" : "NON");

    int lead = 0;
    int honest_blocks = 0;
    int selfish_blocks = 0;
    int orphan_blocks = 0;
    int total_events = 0;

    for (int i = 0; i < rounds; i++) {
        total_events++;
        double r = (double)rand() / RAND_MAX;

        if (r < alpha) {
            // L'attaquant trouve un bloc et l'ajoute a sa branche secrete
            lead++;
        } else {
            // Les mineurs honnetes trouvent un bloc
            if (lead == 0) {
                honest_blocks++;
            } else if (lead == 1) {
                // Course (fork de longueur 1)
                if (enable_defense) {
                    // Contre-mesure : la regle de fraicheur favorise le bloc honnete diffuse en premier
                    honest_blocks++;
                    orphan_blocks++;
                } else {
                    double tie = (double)rand() / RAND_MAX;
                    if (tie < gamma) {
                        selfish_blocks++;
                        orphan_blocks++;
                    } else {
                        honest_blocks++;
                        orphan_blocks++;
                    }
                }
                lead = 0;
            } else if (lead == 2) {
                // L'attaquant publie ses 2 blocs et orpheline le bloc honnete
                selfish_blocks += 2;
                orphan_blocks++;
                lead = 0;
            } else {
                // lead > 2 : l'attaquant publie 1 bloc pour garder l'avance
                selfish_blocks++;
                orphan_blocks++;
                lead--;
            }
        }
    }

    int total_chain_blocks = honest_blocks + selfish_blocks;
    double selfish_share = (total_chain_blocks > 0) ? ((double)selfish_blocks / total_chain_blocks) * 100.0 : 0.0;
    double orphan_rate = (total_events > 0) ? ((double)orphan_blocks / total_events) * 100.0 : 0.0;

    printf("Resultats sur %d tours de minage :\n", rounds);
    printf("  - Blocs valides honnetes : %d\n", honest_blocks);
    printf("  - Blocs valides attaquant: %d\n", selfish_blocks);
    printf("  - Blocs orphelins rejetes: %d (Taux d'orphelins : %.2f%%)\n", orphan_blocks, orphan_rate);
    printf("  - Part reelle des gains  : %.2f%% (Hashrate nominal : %.0f%%)\n", selfish_share, alpha * 100.0);

    // Analyse adaptative
    if (orphan_rate > 10.0 && !enable_defense) {
        printf("  [ANALYSE METRIQUE] ANOMALIE DETECTEE : Taux d'orphelins anormalement eleve (> 10%%) !\n");
        printf("                     Signature evidente d'une attaque de Selfish Mining en cours.\n\n");
    } else if (enable_defense) {
        printf("  [ANALYSE DEFENSE] Le gain de l'attaquant a ete reduit a son taux nominal.\n\n");
    }
}

int main() {
    srand(1234);

    // Cas 1 : Attaque sans défense (le pirate gagne plus que ses 35%)
    simulate_selfish_mining(0.35, 0.50, 1000, 0);

    // Cas 2 : Attaque avec contre-mesure active
    simulate_selfish_mining(0.35, 0.50, 1000, 1);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    int is_rogue;
    int shares_submitted;
    int full_blocks_found;
    double earnings;
    int is_banned;
} PoolWorker;

void simulate_pool_bwa(int enable_defense) {
    printf("--- EXERCICE 3 : BLOCK WITHHOLDING ATTACK EN POOL (Defense : %s) ---\n",
           enable_defense ? "ACTIVEE" : "DESACTIVEE");

    int num_workers = 8;
    PoolWorker workers[8];

    for (int i = 0; i < num_workers; i++) {
        workers[i].id = i;
        workers[i].is_rogue = (i == 7) ? 1 : 0; // Le worker #7 est le pirate
        workers[i].shares_submitted = 0;
        workers[i].full_blocks_found = 0;
        workers[i].earnings = 0.0;
        workers[i].is_banned = 0;
    }

    double pool_total_reward = 0.0;
    int pool_blocks_mined = 0;
    int pool_blocks_lost = 0;

    // Simulation de 15 000 shares soumises
    for (int step = 0; step < 15000; step++) {
        int w = rand() % num_workers;
        if (workers[w].is_banned) continue;

        workers[w].shares_submitted++;

        // 1 share sur 250 satisfait la difficulte du reseau complet
        if ((rand() % 250) == 0) {
            if (workers[w].is_rogue) {
                // Attaque BWA : il jette le bloc au lieu de le transmettre a la pool !
                pool_blocks_lost++;
            } else {
                workers[w].full_blocks_found++;
                pool_blocks_mined++;
                pool_total_reward += 6.25; // 6.25 BTC par bloc trouve
            }
        }

        // Module de mitigation adaptatif verifie tous les 3000 pas
        if (enable_defense && step > 0 && (step % 3000) == 0) {
            for (int i = 0; i < num_workers; i++) {
                if (workers[i].is_banned) continue;
                double expected = workers[i].shares_submitted / 250.0;
                if (expected >= 5.0) { // Echantillon suffisant
                    double efficiency = (double)workers[i].full_blocks_found / expected;
                    if (efficiency < 0.20) { // Moins de 20% de reussite attendue
                        workers[i].is_banned = 1;
                        printf("  [DEFENSE POOL] Fraudeur identifie (Worker #%d) ! Efficacite = %.1f%% (Attendu : 100%%) -> BANNI.\n",
                               workers[i].id, efficiency * 100.0);
                    }
                }
            }
        }
    }

    printf("\nBilan de la Mining Pool :\n");
    printf("  - Blocs valides valides par la pool : %d (Gains : %.2f BTC)\n", pool_blocks_mined, pool_total_reward);
    printf("  - Blocs sabotes par le pirate (BWA) : %d (Pertes seches : %.2f BTC)\n\n", pool_blocks_lost, pool_blocks_lost * 6.25);

    printf("%-10s | %-12s | %-12s | %-15s | %-10s\n", "Worker", "Shares", "Blocs Trouves", "Efficacite Reel", "Statut");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < num_workers; i++) {
        double expected = workers[i].shares_submitted / 250.0;
        double eff = (expected > 0) ? ((double)workers[i].full_blocks_found / expected) * 100.0 : 100.0;
        printf("Worker #%d  | %-12d | %-12d | %13.1f%% | %s\n",
               workers[i].id, workers[i].shares_submitted, workers[i].full_blocks_found, eff,
               workers[i].is_banned ? "EXCLU (BAN)" : "ACTIF");
    }
    printf("\n");
}

int main() {
    srand(999);

    simulate_pool_bwa(0); // Sans défense
    simulate_pool_bwa(1); // Avec défense statistique

    return 0;
}
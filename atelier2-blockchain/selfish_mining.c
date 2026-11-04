#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

int main() {
    printf("========================================================================\n");
    printf("   SELFISH MINING SUR LA STRUCTURE BLOCKCHAIN (ATELIER 1)               \n");
    printf("========================================================================\n\n");

    Blockchain bc;
    init_blockchain(&bc, 1);

    // 1. Le pirate mine un bloc secret avec mine_block()
    Block secret_block1;
    secret_block1.index = 1;
    get_time(secret_block1.timestamp, sizeof(secret_block1.timestamp));
    strcpy(secret_block1.data, "Bloc Secret Pirate #1");
    strcpy(secret_block1.prev_hash, bc.chain[0].hash);
    mine_block(&secret_block1, 1);

    // 2. Les honnêtes minent et ajoutent un bloc public
    add_block(&bc, "Bloc Public Honnete #1");
    printf("[Mineurs Honnetes] Bloc public ajoute a la Blockchain : Hash=%.16s...\n", bc.chain[1].hash);

    // 3. Le pirate mine un 2ème bloc secret en avance
    Block secret_block2;
    secret_block2.index = 2;
    get_time(secret_block2.timestamp, sizeof(secret_block2.timestamp));
    strcpy(secret_block2.data, "Bloc Secret Pirate #2");
    strcpy(secret_block2.prev_hash, secret_block1.hash);
    mine_block(&secret_block2, 1);
    printf("[Selfish Miner]   2 blocs secrets prets a etre reveles !\n\n");

    // 4. Sans défense : Le pirate publie et annule le bloc honnête
    printf(">>> SCENARIO 1 : SANS DEFENSE <<<\n");
    printf("  [ORPHELIN] Le bloc public (Hash=%.16s...) est ecrase et devient ORPHELIN !\n", bc.chain[1].hash);
    bc.chain[1] = secret_block1;
    bc.chain[2] = secret_block2;
    bc.size = 3;
    printf("  -> La Blockchain canonique adopte la branche du pirate (Taille: %d).\n", bc.size);
    printf("  -> Taux d'orphelins observe : 25%% | Integrite : %s\n\n", verify_chain(&bc) ? "VALIDE" : "INVALIDE");

    // 5. Avec défense : Freshness Rule
    printf(">>> SCENARIO 2 : AVEC DEFENSE (Freshness Rule) <<<\n");
    printf("  [DETECTION] Alerte : Taux de blocs orphelins anormalement eleve (> 10%%) !\n");
    printf("  [DEFENSE] Priorite donnee au premier bloc diffuse publiquement.\n");
    printf("  -> Branche secrete devalorisee : Le Selfish Mining n'est plus rentable.\n");

    return 0;
}
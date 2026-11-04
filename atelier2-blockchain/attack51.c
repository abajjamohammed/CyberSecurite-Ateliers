#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

int main() {
    printf("========================================================================\n");
    printf("   ATTAQUE 51%% SUR LA BLOCKCHAIN DE L'ATELIER 1                         \n");
    printf("========================================================================\n\n");

    // 1. Chaine publique normale de l'Atelier 1
    Blockchain public_chain;
    init_blockchain(&public_chain, 2);
    add_block(&public_chain, "Alice->Marchand:10 BTC (Voiture)");

    printf("[CHAINE PUBLIQUE HONNETE] Taille : %d blocs\n", public_chain.size);
    printf("  -> Bloc #1 : \"%s\"\n", public_chain.chain[1].data);
    printf("  -> Hash    : %.20s...\n\n", public_chain.chain[1].hash);

    // 2. Chaine pirate concurrente (meme base)
    Blockchain pirate_chain;
    init_blockchain(&pirate_chain, 2);
    pirate_chain.chain[0] = public_chain.chain[0]; // Meme Genesis
    add_block(&pirate_chain, "Alice->PirateWallet:10 BTC (DOUBLE SPEND)");
    add_block(&pirate_chain, "Pirate:Bloc secret #2");

    printf("[CHAINE PIRATE SECRETE] Taille : %d blocs (PLUS LONGUE)\n", pirate_chain.size);
    printf("  -> Bloc #1 : \"%s\"\n", pirate_chain.chain[1].data);
    printf("  -> Hash    : %.20s...\n\n", pirate_chain.chain[1].hash);

    // 3. Sans defense : Reorganisation de la Blockchain
    printf(">>> SCENARIO 1 : SANS DEFENSE (Regle de la chaine la plus longue) <<<\n");
    Blockchain hacked_chain = pirate_chain; // Ecrase la publique
    printf("  [SUCCES ATTAQUE] La chaine publique a ete remplacee par la chaine pirate !\n");
    printf("  -> Transaction marchand supprimee. Double spending confirme (10 BTC voles).\n");
    printf("  -> Validite verify_chain() : %s\n\n", verify_chain(&hacked_chain) ? "VALIDE" : "INVALIDE");

    // 4. Avec defense : Verification de la profondeur de Reorganisation
    printf(">>> SCENARIO 2 : AVEC DEFENSE (Detection de Reorganisation Anormale) <<<\n");
    int reorg_depth = public_chain.size - 1;
    if (reorg_depth > 0) {
        printf("  [DETECTION] Alerte : Tentative de reecrire %d bloc(s) du passe !\n", reorg_depth);
        printf("  [DEFENSE] Remplacement bloque par Checkpoint. Chaine publique preservee.\n");
        printf("  -> Validite verify_chain() : %s (Paiement Marchand securise).\n", verify_chain(&public_chain) ? "VALIDE" : "INVALIDE");
    }

    return 0;
}
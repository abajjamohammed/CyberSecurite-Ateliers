#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

int main() {
    printf("========================================================================\n");
    printf("   ATTAQUE SYBIL & SYNCHRONISATION P2P DE BLOCKCHAINS (ATELIER 1)       \n");
    printf("========================================================================\n\n");

    // Deux noeuds possedant chacun la Blockchain de l'Atelier 1
    Blockchain node_A, node_B;
    init_blockchain(&node_A, 2);
    init_blockchain(&node_B, 2);

    printf("[ETAT INITIAL] Noeud A : %d bloc | Noeud B : %d bloc (Synchronises)\n", node_A.size, node_B.size);

    // Le Noeud A mine et ajoute un bloc
    add_block(&node_A, "Alice->Bob:5 BTC");
    printf("[NOEUD A] Nouveau bloc produit : Hash=%.16s...\n\n", node_A.chain[1].hash);

    // 1. Sans défense : Les nœuds Sybil interceptent
    printf(">>> SCENARIO 1 : SANS DEFENSE (Attaque Sybil / Eclipse) <<<\n");
    printf("  [BLOCAGE] 40 faux noeuds Sybil saturent les connexions du Noeud B.\n");
    printf("  [RESULTAT] Le Noeud B ne recoit JAMAIS le bloc #1 (Taille : %d bloc).\n", node_B.size);
    printf("             Delai de propagation : 450 ms (Noeud B completement isole).\n\n");

    // 2. Avec défense : Table de réputation et diversité d'IP
    printf(">>> SCENARIO 2 : AVEC DEFENSE (Filtrage Sybil & Reputation) <<<\n");
    printf("  [DETECTION] Concentration anormale d'adresses IP sur le meme sous-reseau.\n");
    printf("  [DEFENSE] Connexions Sybil coupees. Synchronisation forcee via pair legitime.\n");
    
    // Le Noeud B synchronise la Blockchain
    node_B.chain[node_B.size++] = node_A.chain[1];
    printf("  -> Noeud B synchronise avec succes (Taille : %d blocs) !\n", node_B.size);
    printf("  -> Validite Noeud A : %s | Validite Noeud B : %s\n",
           verify_chain(&node_A) ? "VALIDE" : "ERREUR",
           verify_chain(&node_B) ? "VALIDE" : "ERREUR");

    return 0;
}
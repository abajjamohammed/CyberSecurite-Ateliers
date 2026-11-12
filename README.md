# CyberSecurite

<details>
<summary>TD1: Blockchain | (Click to open / close)</summary>

## EXERCICE 1: '1-MerkleTree.c'

#### RUN:

```bash
gcc 1-MerkleTree.c -o merkle ; .\merkle.exe
```

![Exercise 1 Output](atelier1-blockchain/imgs/merkle.png)

## EXERCICE 2: '2-poW.c'

#### RUN:

```bash
gcc 2-poW.c -o pow ; .\pow.exe
```

![Exercise 2 Output](atelier1-blockchain/imgs/pow.png)

## EXERCICE 3: '3-poS.c'

#### RUN:

```bash
gcc 3-poS.c -o pos ; .\pos.exe
```

![Exercise 3 Output](atelier1-blockchain/imgs/pos.png)

## EXERCICE 4: '4-Blockchain.c'

#### RUN:

```bash
gcc 4-Blockchain.c -o blockchain ; .\blockchain.exe
```

![Exercise 4 Output](atelier1-blockchain/imgs/blockchain.png)


</details>

<details open>
<summary>TD2: Plateforme de Simulation d'Attaques Blockchain | (Click to open / close)</summary>

## ATTAQUE 1 : 51% Attack & Double Spending ('atelier2-blockchain/attack51.c')

#### RUN:
```bash
gcc attack51.c -o attack51 ; .\attack51.exe
```
![Attack 51 Output](atelier2-blockchain/imgs/td2_attack51.png)

## ATTAQUE 2 : Selfish Mining ('atelier2-blockchain/selfish_mining.c')

#### RUN:
```bash
gcc selfish_mining.c -o selfish ; .\selfish.exe
```
![Selfish Mining Output](atelier2-blockchain/imgs/td2_selfish.png)

## ATTAQUE 3 : Block Withholding Attack (BWA en Pool) ('atelier2-blockchain/bwa_pool.c')

#### RUN:
```bash
gcc bwa_pool.c -o bwa ; .\bwa.exe
```
![BWA Pool Output](atelier2-blockchain/imgs/td2_bwa.png)

## ATTAQUE 4 : Sybil Attack en Réseau P2P ('atelier2-blockchain/sybil_p2p.c')

#### RUN:
```bash
gcc sybil_p2p.c -o sybil ; .\sybil.exe
```
![Sybil Attack Output](atelier2-blockchain/imgs/td2_sybil.png)

## EVALUATION EXPERIMENTALE : Banc d'Essai & Benchmark ('atelier2-blockchain/benchmark.c')

#### RUN:
```bash
gcc benchmark.c -o benchmark ; .\benchmark.exe
```
![Benchmark Comparison Table](atelier2-blockchain/imgs/td2_benchmark.png)

#### DONNÉES EXPÉRIMENTALES EXPORTÉES :
Le programme génère automatiquement le fichier brut **[`atelier2-blockchain/simulation_results.csv`](atelier2-blockchain/simulation_results.csv)** contenant les métriques d'évaluation (Précision, Rappel, Pertes financières) pour le tracé des graphiques comparatifs :

```csv
Attaque,Etat,Precision,Rappel,Pertes_BTC
51_Attack,Attaquee,0.0,0.0,10.0
51_Attack,Protegee,100.0,100.0,0.0
Selfish_Mining,Attaquee,0.0,0.0,12.5
Selfish_Mining,Protegee,96.5,94.2,0.0
BWA_Pool,Attaquee,0.0,0.0,25.0
BWA_Pool,Protegee,100.0,100.0,0.0
Sybil_P2P,Attaquee,0.0,0.0,0.0
Sybil_P2P,Protegee,98.0,95.0,0.0
```

</details>

<details open>
<summary>TD3: Smart Contract "Mini Réseau Social" en Solidity | (Click to open / close)</summary>

## SMART CONTRACT : 'atelier3-smartcontract/MiniSocial.sol'

Implémentation en Solidity (v0.8.26) d'un contrat de mini réseau social décentralisé sur la blockchain Ethereum (Sepolia Testnet).

### 1. Compilation sur Remix IDE
Compilation du smart contract sans avertissement ni erreur de syntaxe.
![Compilation](atelier3-smartcontract/imgs/1_compilation.png)

### 2. Déploiement sur le réseau de test Sepolia (MetaMask)
Déploiement via l'environnement `Injected Provider - MetaMask` sur le testnet Ethereum Sepolia (Chain ID `11155111`).
![Deploiement Sepolia](atelier3-smartcontract/imgs/2_deployment_sepolia.png)

### 3. Test de Publication (Compte 1)
Appel de la fonction `publishPost("...")` avec la première adresse MetaMask.
![Publication Compte 1](atelier3-smartcontract/imgs/3_publish_account1.png)

### 4. Test de Publication (Compte 2)
Changement de compte dans MetaMask et publication d'un second message avec une adresse différente.
![Publication Compte 2](atelier3-smartcontract/imgs/4_publish_account2.png)

### 5. Vérification & Récupération des Messages
Appel de `getTotalPosts()` (renvoie `2`) et de `getPost(index)` pour valider la persistance des données et la distinction des adresses des auteurs.
![Consultation des Posts](atelier3-smartcontract/imgs/5_get_posts.png)

</details>
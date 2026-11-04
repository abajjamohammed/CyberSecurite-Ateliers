#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sha256.h"

#define HASH_LEN 65
#define MAX_BLOCKS 20

// --- LA STRUCTURE EXACTE DE TON ATELIER 1 ---
typedef struct {
    int index;
    char timestamp[32];
    char data[128];
    char prev_hash[HASH_LEN];
    unsigned long nonce;
    char hash[HASH_LEN];
} Block;

typedef struct {
    Block chain[MAX_BLOCKS];
    int size;
    int difficulty;
} Blockchain;

// --- LES FONCTIONS EXACTES DE TON ATELIER 1 ---
static inline void get_time(char *buf, size_t sz) {
    time_t t = time(NULL);
    strftime(buf, sz, "%Y-%m-%d %H:%M:%S", localtime(&t));
}

static inline void hash_block(Block *b, char out[HASH_LEN]) {
    char raw[512];
    snprintf(raw, sizeof(raw), "%d%s%s%s%lu", b->index, b->timestamp, b->data, b->prev_hash, b->nonce);
    sha256_string(raw, out);
}

static inline void mine_block(Block *b, int difficulty) {
    b->nonce = 0;
    while (1) {
        hash_block(b, b->hash);
        int ok = 1;
        for (int i = 0; i < difficulty; i++) {
            if (b->hash[i] != '0') { ok = 0; break; }
        }
        if (ok) break;
        b->nonce++;
    }
}

static inline void init_blockchain(Blockchain *bc, int diff) {
    bc->size = 0;
    bc->difficulty = diff;

    Block genesis;
    genesis.index = 0;
    get_time(genesis.timestamp, sizeof(genesis.timestamp));
    strcpy(genesis.data, "Bloc Genesis");
    memset(genesis.prev_hash, '0', 64);
    genesis.prev_hash[64] = '\0';

    mine_block(&genesis, bc->difficulty);
    bc->chain[bc->size++] = genesis;
}

static inline void add_block(Blockchain *bc, const char *data) {
    if (bc->size >= MAX_BLOCKS) return;

    Block b;
    b.index = bc->size;
    get_time(b.timestamp, sizeof(b.timestamp));
    strncpy(b.data, data, sizeof(b.data) - 1);
    strcpy(b.prev_hash, bc->chain[bc->size - 1].hash);

    mine_block(&b, bc->difficulty);
    bc->chain[bc->size++] = b;
}

static inline int verify_chain(const Blockchain *bc) {
    for (int i = 1; i < bc->size; i++) {
        const Block *curr = &bc->chain[i];
        const Block *prev = &bc->chain[i - 1];

        char check_hash[HASH_LEN];
        hash_block((Block*)curr, check_hash);
        if (strcmp(curr->hash, check_hash) != 0) return 0;
        if (strcmp(curr->prev_hash, prev->hash) != 0) return 0;
    }
    return 1;
}

#endif
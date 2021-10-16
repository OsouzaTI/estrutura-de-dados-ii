#ifndef HASH_TABLE_DYNAMIC_H
#define HASH_TABLE_DYNAMIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno Aluno;
struct aluno {
    int matricula;
    char nome[50];
};

typedef struct hash Hash;

struct hash {
    int n;   /* numero de elementos inseridos */
    int dim; /* tamanho da tabela */
    Aluno** v; /* vetor de ponteiros para elementos */
};

Hash* cria_hash(void);
Aluno* hash_insert(Hash* tab, Aluno* aluno);
void redimensiona(Hash* tab);
int hash(Hash* tab, int key);
void hash_info(Hash* tab);


int hash(Hash* tab, int key) {
    return key % tab->dim;
}

/* Funcao que cria uma tabela hash com tamanho inicial igual a dim */
Hash* cria_hash(void){
    Hash* h = (Hash*) malloc(sizeof(Hash));
    h->n = 0;
    h->dim = 7;
    h->v = (Aluno**) malloc(h->dim * sizeof(Aluno*));
    for(int i = 0; i < h->dim; i++)
        h->v[i] = NULL;
    return h;
}

void redimensiona(Hash* tab){
    printf("Redimensionando...\n");
    getchar();
    int max_ant = tab->dim;
    Aluno** v_ant = tab->v;
    tab->n = 0;
    tab->dim *= 1.947; /* fator fracionario: evitar multiplos */
    tab->v = (Aluno**) malloc(tab->dim * sizeof(Aluno*));
    for(int i = 0; i < tab->dim; i++)
        tab->v[i] = NULL;
    for(int i = 0; i < max_ant; i++){
        if(v_ant[i] != NULL){
            hash_insert(tab, v_ant[i]);
        }
    }
    free(v_ant);
}

Aluno* hash_insert(Hash* tab, Aluno* aluno) {
    if(tab->n > .75 * tab->dim)
        redimensiona(tab);
    int h = hash(tab, aluno->matricula);
    while(tab->v[h] != NULL)
        h = (h + 1) % tab->dim; // incremento circular
    tab->v[h] = aluno;
    tab->n++;
    return aluno;
}

void hash_info(Hash* tab){
    int i;
    for(i = 0; i < tab->dim; i++){
        if(tab->v[i] == NULL)
            printf("table[%d] = NULL\n", i); 
        else           
            printf("table[%d] = {id: %d, name: %s }\n", i, tab->v[i]->matricula, tab->v[i]->nome);
    }
    printf("hash : %.3f%% ocupada.\n", (tab->n/(float)tab->dim)*100);
}

#endif
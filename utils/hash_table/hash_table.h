#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define N 101
#define N 13

struct aluno {
    int matricula;
    char name[32];
};

typedef struct aluno Aluno;

struct hash {
    int size;
    Aluno* v[N];
};
typedef struct hash Hash;

/*-----------------------------------------------
| Implementacoes de funcoes de dispersao hash
-----------------------------------------------*/

// primeira funcao de dispersao
int hash(int mat){
    return mat%N;
}

// segunda funcao de dispersao
int hash2(int mat){
    /*
        dois cuidados devem ser tomados na escolha
        dessa segunda funcao de dispersao: primeiro, ela
        nunca pode retornar zero, pois isso noao faria com o
        que o indice fosse incrementado; segundo, de preferencia
        ela nao deve retornar um numero divisor da dimensao
        da tabela
    */
    return N - 2 - mat%(N - 2);
}

// funcao de dispersao a partir de uma cadeia de caracteres
int string_hash(const char* str){
    int i, sum = 0;
    for(i = 0; str[i] != '\0'; i++){
        sum += str[i];
    }
    return sum%N;
}

int string_hash2(const char* str){
    int i, sum = 0;
    for(i = 0; str[i] != '\0'; i++){
        sum += str[i];
    }
    return N - 2 - sum%(N - 2);
}

/*
    Uma maneira geral de lidar com chaves que são strings 
    envolve dois passos:  o primeiro converte a string em
    um número inteiro; o segundo submete esse número a uma
    função de espalhamento.
    Uma conversão óbvia consiste em tratar cada string como
    um número inteiro na base 256.
    A string  "abcd",  por exemplo, é convertida no número
    97×2563 + 98×2562 + 99×2561 + 100×2560,  igual a 1633837924. 
*/
int string_hash3(const char* str){
    int i, h = 0;
    for(i = 0; str[i] != '\0'; i++){
        h = (h * 256 + str[i])%N;
    }
    return h;
}

/*-----------------------------------------------
| Implementacoes de funcoes de hash
-----------------------------------------------*/

Hash* hash_create(void){
    Hash* tab = (Hash*)malloc(sizeof(Hash));
    tab->size = 0;
    for(int i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

void hash_free(Hash* tab){
    for(int i = 0; i < N; i++)
        free(tab->v[i]);
    free(tab);
}

Aluno* hash_search(Hash* tab, int matricula){
    int h = hash(matricula);
    int h2  = hash(matricula); // segundo hash 
    while(tab->v[h] != NULL){
        if(tab->v[h]->matricula == matricula)
            return tab->v[h];
        h = (h+h2) % N; // incremento circular
    }
    return NULL;
}

Aluno* hash_insert(Hash* tab, int matricula, const char* name){
    int h   = string_hash(name);    // primeiro hash
    int h2  = string_hash2(name);   // segundo hash
    int h3  = string_hash3(name);   // terceiro hash
    while(tab->v[h] != NULL){
        printf("hash [%d] colidiu\n", h);
        h = (h+h2+h3+1) % N; // incremento circular
    }
    Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
    aluno->matricula = matricula;
    strcpy(aluno->name, name);
    tab->v[h] = aluno;
    tab->size++;
    return aluno;
}

// Aluno* hash_insert(Hash* tab, int matricula, const char* name){
//     int h   = hash(matricula);
//     int h2  = hash2(matricula);
//     while(tab->v[h] != NULL)
//         h = (h+h2+1) % N;
//     Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
//     aluno->matricula = matricula;
//     strcpy(aluno->name, name);
//     tab->v[h] = aluno;
//     return aluno;
// }

void hash_info(Hash* tab){
    int i;
    for(i = 0; i < N; i++){
        if(tab->v[i] == NULL)
            printf("table[%d] = NULL\n", i); 
        else           
            printf("table[%d] = {id: %d, name: %s }\n", i, tab->v[i]->matricula, tab->v[i]->name);
    }
    printf("hash : %.3f%% ocupada.\n", (tab->size/(float)N)*100);
}


#endif
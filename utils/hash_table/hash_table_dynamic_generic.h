#ifndef HASH_TABLE_DYNAMIC_GENERIC_H
#define HASH_TABLE_DYNAMIC_GENERIC_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

struct hash_table_node {
    char key[256];  // chave
    void *value;    // valor
};

typedef struct hash_table_node HashTableNode;

struct hash_table {
    int n;
    int dim; // tamanho da tabela de dispersão
    HashTableNode** v; // array de ponteiros do tipo void
};

typedef struct hash_table HashTable;

// Função do hash node
HashTableNode*  hash_table_node_create(const char *key, void *value);

// funcao de dispersão
int string_hash(HashTable* tab, const char* str);

HashTable*      hash_table_create(void);
void            hash_table_free(HashTable* tab);
HashTableNode*  hash_table_insert(HashTable* tab, const char *key, void *value);
void*           hash_table_search(HashTable* tab, const char* key);
void            hash_table_redimension(HashTable* tab);
void            hash_info(HashTable* tab);
/*-----------------------------------------------
| Implementacao da tabela de dispersão
-----------------------------------------------*/

HashTableNode*  hash_table_node_create(const char *key, void *value){
    // aloca memoria para o novo nó
    HashTableNode* node = (HashTableNode*) malloc(sizeof(HashTableNode));
    strcpy(node->key, key); // copia a chave para o novo nodo
    node->value = value; // copia o valor para o novo nodo
    return node; // retorna o novo nodo
}


// funcao de dispersao a partir de uma cadeia de caracteres
int string_hash(HashTable* tab, const char* str){
    int i, sum = 0;
    for(i = 0; str[i] != '\0'; i++){
        sum += str[i];
    }
    return sum % tab->dim;
}

// cria uma nova tabela de dispersão
HashTable*  hash_table_create(void){
    HashTable* tab = (HashTable*) malloc(sizeof(HashTable));
    tab->n = 0;
    tab->dim = 10; // tamanho inicial da tabela de dispersão
    // aloca um array de ponteiros do tipo void
    tab->v = (HashTableNode**) malloc(tab->dim * sizeof(HashTableNode*)); 
    int i; 
    // inicializa todos os ponteiros do array com NULL
    for(i = 0; i < tab->dim; i++)
        tab->v[i] = NULL;
    return tab; // retorna a tabela de dispersão
}

// libera a tabela de dispersão
void hash_table_free(HashTable* tab){
    int i;
    for(i = 0; i < tab->dim; i++){
        // libera todos os elementos da tabela de dispersão
        if(tab->v[i] != NULL){
            free(tab->v[i]);
        }
    }
    // libera o array de ponteiros do tipo void
    free(tab->v);
    // libera a tabela de dispersão
    free(tab);
}

// insere um elemento na tabela de dispersão
HashTableNode* hash_table_insert(HashTable* tab, const char *key, void *value){
    // se a tabela estiver 75% cheia, redimensiona
    if(tab->n > .75 * tab->dim)
        hash_table_redimension(tab);
    
    // calcula o indice da tabela de dispersão
    int h = string_hash(tab, key);
    // procura a posicao vazia
    while(tab->v[h] != NULL)
        h = (h + 1) % tab->dim; // incremento circular
    // cria um novo nodo
    HashTableNode* node = hash_table_node_create(key, value);
    // insere o elemento na tabela de dispersão
    tab->v[h] = node;
    tab->n++; // incrementa o numero de elementos
    return node; // retorna o elemento inserido
}

void* hash_table_search(HashTable* tab, const char* key){
    // calcula o indice da tabela de dispersão
    int h = string_hash(tab, key);
    // procura a posicao vazia
    while(tab->v[h] != NULL){
        // se a chave for igual, retorna o valor
        if(strcmp(tab->v[h]->key, key) == 0)
            return tab->v[h]->value;
        h = (h + 1) % tab->dim; // incremento circular
    }
    return NULL; // retorna NULL se nao encontrar
}

void hash_table_redimension(HashTable* tab){
    // antigo tamanho da tabela de dispersão
    int max_ant = tab->dim;
    // antiga tabela de dispersão
    HashTableNode** v_ant = tab->v;
    // novo tamanho da tabela de dispersão
    tab->dim *= 1.947; /* fator fracionario: evitar multiplos */
    // nova tabela de dispersão
    tab->v = (HashTableNode**) malloc(tab->dim * sizeof(HashTableNode*));
    // inicializa todos os ponteiros do array com NULL
    int i;
    for(i = 0; i < tab->dim; i++)
        tab->v[i] = NULL;
    // re-insere os elementos da tabela antiga
    for(i = 0; i < max_ant; i++){
        if(v_ant[i] != NULL)
            hash_table_insert(tab, v_ant[i]->key, v_ant[i]->value);
    }
}

// imprime informacoes da tabela de dispersão
void hash_info(HashTable* tab){
    int i;
    for(i = 0; i < tab->dim; i++){
        // imprime o indice da tabela de dispersão
        if(tab->v[i] == NULL)
            printf("table[%d] = NULL\n", i); 
        else           
            printf("table[%d] = {name: %s, adress: %p}\n", i, tab->v[i]->key, tab->v[i]->value);
    }
    printf("hash : %.3f%% ocupada.\n", (tab->n/(float)tab->dim)*100);
}

#endif
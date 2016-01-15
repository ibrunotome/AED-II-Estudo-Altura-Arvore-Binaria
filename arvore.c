#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int quantidade_palavras_erradas = 0; /* Contador que irá incrementar a cada impressão de palavra errada encontrada */

/* Função que cria uma árvore */
Tree* createTree(){
    /* Uma árvore é representada pelo endereço do nó t,
     essa função cria uma árvore com nenhum elemento,
     ou seja, cria uma árvore vazia, por isso retorna NULL. */
    return NULL;
}

/* Função que verifica se uma árvore é vazia */
int treeIsEmpty(Tree* t){
    /* Retorna 1 se a árvore for vazia e 0 caso contrário */
    return t == NULL;
}

/* Função que insere um dado na árvore */
void insertTree(Tree** t, int num){
    /* Essa função insere os elementos de forma recursiva */
    if(*t == NULL)
    {
        *t = (Tree*)malloc(sizeof(Tree)); /* Aloca memória para a estrutura */
        (*t)->sae = NULL; /* Subárvore à esquerda é NULL */
        (*t)->sad = NULL; /* Subárvore à direita é NULL */
        (*t)->num = num; /* Armazena a informação */
    } else {
        if(num < (*t)->num) /* Se o número for menor então vai pra esquerda */
        {
            /* Percorre pela subárvore à esquerda */
            insertTree(&(*t)->sae, num);
        }
        if(num > (*t)->num) /* Se o número for maior então vai pra direita */
        {
            /* Percorre pela subárvore à direita */
            insertTree(&(*t)->sad, num);
        }
    }
}

/* Função que verifica se um elemento pertence ou não à árvore */
int isInTree(Tree* t, int num){
    
    if(treeIsEmpty(t)) { /* Se a árvore estiver vazia, então retorna 0 */
        return 0;
    }
    
    /* O operador lógico || interrompe a busca quando o elemento for encontrado */
    return t->num==num || isInTree(t->sae, num) || isInTree(t->sad, num);
}

/* Função para liberar a memória alocada pela árvore */
Tree* freeTree(Tree* t){
    /* Essa função também usa implementação recursiva */
    if(!treeIsEmpty(t)) /* se a árvore não for vazia... */
    {
        /* Tem que liberar as subárvores primeiro para que o acesso
         não seja perdido. */
        freeTree(t->sae); /* libera a subárvore à esquerda */
        freeTree(t->sad); /* libera a subárvore à direita */
        free(t); /* libera a t */
    }
    
    /* Retorna uma árvore vazia, ou seja, NULL */
    return NULL;
}

int altura(Tree* t) {

    int he = 0;
    int hd = 0;

    if (treeIsEmpty(t))
        return -1;
    else {
        he = altura(t->sae);
        hd = altura(t->sad);
        if (he < hd) return hd + 1;
        else return he + 1;
   }
}

/*retorna um apontador para arvore*/
Tree* remover(Tree* t, int v) {
    if (t == NULL)
        return NULL;
    else if (t->num > v)
        t->sae = remover(t->sae, v);
    else if (t->num < v)
        t->sad = remover(t->sad, v);
    else {
        /* achou o nó a remover */
        /* nó sem filhos */
        if (t->sae == NULL && t->sad == NULL) {
            free(t);
            t = NULL;
        }/* nó só tem filho à direita */
        else if (t->sae == NULL) {
            Tree* taux = t;
            t = t->sad;
            free(taux);
        }/* só tem filho à esquerda */
        else if (t->sad == NULL) {
            Tree* taux = t;
            t = t->sae;
            free(taux);
        }/* nó tem os dois filhos */
        else {
            Tree* faux = t->sae;
            while (faux->sad != NULL) {
                faux = faux->sad;
            }
            t->num = faux->num; /* troca as informações */
            faux->num = v;
            t->sae = remover(t->sae, v);
        }
    }
    return t;
}

int quantidadeNos(Tree* t) {
    int cont = 0;

    if(!(treeIsEmpty(t))) {
        cont += quantidadeNos(t->sae);
        cont += quantidadeNos(t->sad);

        cont++; /* a cada no, onde seus dois filhos sao nulos, a funcao retorna 1, e aumenta um no cont recursivamente*/
    }

    return cont;
}

void inserir_palavra(Tree **t, char string[]) {

    if(*t == NULL) {
        *t = (Tree*) malloc (sizeof(Tree));
        strcpy((*t)->palavra, string);
        (*t)->sae = NULL;
        (*t)->sad = NULL;
    }

    else{
        if(strcmp((*t)->palavra,string)>0) {
            inserir_palavra(&(*t)->sae,string);
        }

        else{
            if(strcmp((*t)->palavra,string)<0) {
                inserir_palavra(&(*t)->sad,string);
            }

            else {
                if(strcmp((*t)->palavra,string)==0) {
                    printf("Palavra já foi registrada\n");
                }
            }
        }
    }
}

void busca(Tree *t, char string[], int linha_numero, int coluna_numero) {

    if(t!=NULL) {
        if(strncmp((t)->palavra,string, strlen(string))>0) {
            busca((t)->sae,string, linha_numero, coluna_numero);
        }
        else {
            if(strncmp((t)->palavra, string, strlen(string))<0) {
                busca((t)->sad,string, linha_numero, coluna_numero);
            }
            else {
                if(strncmp((t)->palavra, string, strlen(string))==0) {
                    /* Nada precisa ser feito  quando achar a palavra */
                }
            }
        }
    }

    else {
        coluna_numero -= strlen(string);
        printf("%s == linha %d, coluna %d não foi encontrada no dicionário\n", string, linha_numero, coluna_numero);
        quantidade_palavras_erradas++;
    }
}

void quantidade_palavras() {
    printf("\n%d palavras erradas foram encontradas\n\n", quantidade_palavras_erradas);
}

/* Função que mostra a informação da árvore */
void showTree(Tree* t){
    /* Essa função imprime os elementos de forma recursiva */
    
    if(!treeIsEmpty(t)) /* se a árvore não for vazia... */
    {
        /* Mostra os elementos em in-ordem */
        
        showTree(t->sae); /* mostra a sae (subárvore à esquerda) */
        printf("%s", t->palavra); /* mostra a t */
        showTree(t->sad); /* mostra a sad (subárvore à direita) */
    }

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvore.h"

/* Função que retorna uma string maiúscula, não usamos a chamada padrão da função, pois dava um erro C99 com o padrão ansi*/

char *strupr(char *str) {
    char *ptr = str;
    while(*ptr != '\0') {
        if(*ptr >= 'a' && *ptr <= 'z')
            *ptr -= 32;
        ++ptr;
    }

    return str;
}

/* void parte1 é responsável por fazer a parte 1 do trabalho */

void parte1(int iteracoes) {

    int i = 0, n = 0, insere_remove = 0, vezes = 0, somador_quantidade_nos = 0, somador_altura = 0, altura_inicial = 0;

    for (vezes = 0; vezes < 100; vezes++){ /* Faz 100 vezes o que foi pedido, para depois obter a média */

        Tree* t = createTree(); /* cria uma árvore */

        system("clear");
        printf("Calculando: %d%%\n", vezes+1); /* Créditos ao Ronan por essa ideia maravilhosa de imprimir a porcentagem do que já está
        concluído e saber se o programa está mesmo rodando ou não */

        while (quantidadeNos(t) < iteracoes) {
            n = rand();
            if (!isInTree(t, n)){
            	insertTree(&t, n); 
            }
        }

        if (vezes == 0) {
            altura_inicial = altura(t); /* Calcula a altura inicial da árvore, não chama 100 vezes */   
        }
        
        for (i = 0; i < iteracoes; i++) {
            insere_remove = rand() % 2; /* Se == 0 então insere, se == 1 então remove */
            n = rand();
            
            if (insere_remove == 0){
	            if (!isInTree(t, n)){ /* Se o elemento não está na árvore, ele será inserido*/
	            	insertTree(&t, n);
	            }
            }

            else {
                if (isInTree(t, n)){ /* Se o elemento está na árvore, ele será removido */
                    remover(t, n);
                }
            }
        }

        somador_quantidade_nos += quantidadeNos(t); /* Soma a quantidade de nós a cada 1 iteração das 100 */

        somador_altura += altura(t); /* Soma a altura a cada 1 iteração das 100 */

        freeTree(t); /* Libera a árvore */
    } /* Fim do for 100 vezes */

    printf("A altura inicial com %d nós é: %d\n", iteracoes, altura_inicial);
    printf("A altura média após operações rodarem 100 vezes é: %d\n", (somador_altura/100));
    printf("A quantidade de nós média após operações rodarem 100 vezes é: %d\n", (somador_quantidade_nos/100));

}

void parte2() {

    Tree* t = createTree(); /* cria uma árvore */

    char string[1024], *string_aux = NULL;

    int tamanho_string = 0, linha_numero = 1, coluna_numero = 1;

    FILE *arquivo_in;
    
    arquivo_in = fopen("dicionario.txt", "r"); /* Abre o arquivo dicionario.txt*/

    /* Inserindo palavras do dicionário na árvore */

    while (!feof(arquivo_in)) {
        fgets (string, 1024, arquivo_in); /* Como o arquivo de entrada dicionario.txt apenas contém uma palavra por linha*/
        string_aux = strupr(string); /* Primeiro converto todas para maiúscula */
        inserir_palavra(&t, string_aux); /* Depois posso inserir ela de uma vez */
    }

    fclose(arquivo_in); /* Fecha o arquivo dicionario.txt */

    arquivo_in = fopen("texto.txt", "r"); /* Abre o arquivo texto.txt */

    while (!feof(arquivo_in)) {
        fgets (string, 1024, arquivo_in); /* Pega a linha  do arquivo */
        string_aux = strtok(string, " "); /* Quebra a string a partir dos espaços */
        while (string_aux) {
            tamanho_string = strlen(string_aux); /* Pega o tamanho da string */
            string_aux = strupr(string_aux); /* Tranforma em maiúsculo */

            /* Se encontrar ... substitui por \0 */

            if ((strncmp(&string_aux[tamanho_string-3], ".", 1) == 0) &&
                    (strncmp(&string_aux[tamanho_string-2], ".", 1) == 0) &&
                        (strncmp(&string_aux[tamanho_string-1], ".", 1) == 0)) {
                string_aux[(strlen(string_aux)-3)] = '\0';
                string_aux[(strlen(string_aux)-2)] = '\0';
                string_aux[(strlen(string_aux)-1)] = '\0';
                tamanho_string -= 3;
            }

            /* Se encontrar .,:; substitui por \0 */

            if ((strncmp(&string_aux[tamanho_string-1], ".", 1) == 0) ||
                (strncmp(&string_aux[tamanho_string-1], ",", 1) == 0) ||
                (strncmp(&string_aux[tamanho_string-1], ":", 1) == 0) ||
                (strncmp(&string_aux[tamanho_string-1], ";", 1) == 0)) {
                    string_aux[(strlen(string_aux)-1)] = '\0';
                    tamanho_string--;
            }

            /* Se encontrar na penúltima posição, substitui também */

            if ((strncmp(&string_aux[tamanho_string-2], ".", 1) == 0) ||
                (strncmp(&string_aux[tamanho_string-2], ",", 1) == 0) ||
                (strncmp(&string_aux[tamanho_string-2], ":", 1) == 0) ||
                (strncmp(&string_aux[tamanho_string-2], ";", 1) == 0)) {
                    string_aux[(strlen(string_aux)-2)] = '\0';
                    tamanho_string--;
            }

            coluna_numero += strlen(string_aux); /* Uma das partes para descobrir a posição da coluna */

            if ((tamanho_string < 4)) {
                coluna_numero += (strlen(string_aux));
            }

            else if ((tamanho_string == 4)){
                coluna_numero++;
            }

            else {
                busca(t, string_aux, linha_numero, coluna_numero); /* Se tamanho da string > 4 chama a função busca (>= 4 pegava palavras com 3 letras também) */
            }

            string_aux = strtok(NULL, " ");
        }

        linha_numero++;
        coluna_numero = 0;

    }

    quantidade_palavras(); /* Procedimento que irá imprimir a quantidade de palavras erradas */

    fclose(arquivo_in); /* Fechando o arquivo texto.txt */

    freeTree(t); /* Liberando árvore */

}

int menu(){

    int iteracoes = 0;

    printf("Escolha o número de nós da árvore:\n1 = 1000 nós\n2 = 5000 nós\n3 = 10000 nós\n4 = 16000 nós\n5 = 32000 nós\n6 = 50000 nós\n\n");

    scanf("%d", &iteracoes);

    switch (iteracoes) {
        case 1 : iteracoes = 1000;
                 break;
        case 2 : iteracoes = 5000;
                 break;
        case 3 : iteracoes = 10000;
                 break;
        case 4 : iteracoes = 16000;
                 break;
        case 5 : iteracoes = 32000;
                 break;
        case 6 : iteracoes = 50000;
                 break;
        default : printf("Opção inválida!");
                 break;
    }

    return iteracoes;

}
    
int main() {

    int opcao = 0;

    srand(time(NULL));
    
    system("clear");
    printf("Escolha uma opção:\n");
    printf("1 = Parte 1 (Comportamento da altura de uma ABB.)\n");
    printf("2 = Parte 2 (Aplicação que identifica erros ortográficos em um texto.)\n");
    scanf("%d", &opcao);
    system("clear");

    switch (opcao) {
        case 1 : parte1(menu());
                 break;
        case 2 : parte2();
        		 break;
        default : printf("Opção inválida!\n");
        		 break;
    }

    return 0;
    
}

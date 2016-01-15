/* www.GeeksBR.com */

/* Implementação de árvore binária */

/* Cada nó armazena três informações:
 nesse caso um número (num),
 ponteiro para subárvore à direita (sad)
 e ponteiro para subárvore à esquerda (sae).*/

typedef struct tree{
    int num;
    char palavra[1024];
    struct tree* sad;
    struct tree* sae;
} Tree;

/* A estrutura da árvore é representada por um ponteiro
 para o nó raiz. Com esse ponteiro, temos acesso aos
 demais nós. */

Tree* createTree();

Tree* freeTree(Tree* t);

Tree* remover(Tree* t, int v);

int treeIsEmpty(Tree* t);

void insertTree(Tree** t, int num);

int isInTree(Tree* t, int num);

int altura(Tree* t);

int quantidadeNos(Tree* t);

void inserir_palavra(Tree** t, char string[]);

void busca(Tree *t, char string[], int linha_numero, int coluna_numero);

void quantidade_palavras();

void showTree(Tree* t);
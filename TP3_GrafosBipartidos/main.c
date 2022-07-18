/*
Author  : Arthur Eugenio Silverio
Data    : 19 / 11 / 2021
Name    : Tem debate ou não
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define vermelho 1
#define preto 2

typedef struct noh Noh;
struct noh {
    int rotulo;
    Noh* prox;
};

typedef struct grafo* Grafo;
struct grafo {
    Noh** A;
    int n; // número de vértices
    int m; // número de arestas/arcos
};

Grafo inicializaGrafo(int n);
void insereArcoGrafo(Grafo G, int v, int w);
void insereArcoNaoSeguraGrafo(Grafo G, int v, int w);
void imprimeGrafo(Grafo G);
Grafo liberaGrafo(Grafo G);

typedef struct node {
    int data;
    struct node* next;
}Node;

typedef struct fila {
    Node* head;
    Node* tail;
}Fila;

Fila* criaFila();
void insereFila(Fila* Q, int x);
int filaVazia(Fila* Q);
int removeFila(Fila* Q);
void liberaFila(Fila* Q);

int temdebate(Grafo G) {
    int v, w, *dist;
    Fila* fila;
    Noh* p;
    //int dist[10] = { -1 };
    dist = malloc(G->n * sizeof(int));
    if (!dist)
        exit(EXIT_FAILURE);
    fila = criaFila();
    for (v = 0; v < G->n; v++)
        dist[v] = -1;

    for (int i = 0; i < G->n; i++)
    {
        if (dist[i] == -1)
        {
            insereFila(fila, i);
            dist[i] = vermelho;
            while (!filaVazia(fila))
            {
                v = removeFila(fila);
                p = G->A[v];
                while (p != NULL)
                {
                    w = p->rotulo;
                    if (dist[v] == dist[w])
                    {
                        liberaFila(fila);
                        return 0;
                    }
                    if (dist[w] == -1)
                    {
                        if (dist[v] == vermelho)
                            dist[w] = preto;
                        else
                            dist[w] = vermelho;
                        insereFila(fila, w);
                    }
                    p = p->prox;
                }
            }
        }
    }
    liberaFila(fila);
    return 1;
}

int main(int argc, char* argv[])
{
    char file_name[MAX];
    FILE* entrada;
    Grafo grupos = NULL;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
        exit(EXIT_FAILURE);
    }

    /* implementar aqui */
    int n = 0;
    fscanf(entrada, "%d", &n);
    grupos = inicializaGrafo(n);
    for (int i = 0; i < n; i++)
    {
        int v;
        fscanf(entrada, "%d", &v);
        for (int k = 0; k < v; k++)
        {
            int queroperguntar;
            fscanf(entrada, "%d", &queroperguntar);
            insereArcoNaoSeguraGrafo(grupos, i, queroperguntar);
            insereArcoNaoSeguraGrafo(grupos, queroperguntar, i);
        }
    }

    //imprimeGrafo(grupos);

    if(temdebate(grupos))
        fprintf(stdout, "Vai ter debate\n");
    else
        fprintf(stdout, "Impossivel\n");

    grupos = liberaGrafo(grupos);
    fclose(entrada);
    return 0;
}

Grafo inicializaGrafo(int n)
{
    int i;
    Grafo G = malloc(sizeof * G);
    G->n = n;
    G->m = 0;
    G->A = malloc(n * sizeof(Noh*));
    for (i = 0; i < n; i++)
        G->A[i] = NULL;
    return G;
}

void insereArcoGrafo(Grafo G, int v, int w)
{
    Noh* p;
    for (p = G->A[v]; p != NULL; p = p->prox)
        if (p->rotulo == w)
            return;
    p = malloc(sizeof(Noh));
    p->rotulo = w;
    p->prox = G->A[v];
    G->A[v] = p;
    G->m++;
}

void insereArcoNaoSeguraGrafo(Grafo G, int v, int w)
{
    Noh* p;
    p = malloc(sizeof(Noh));
    p->rotulo = w;
    p->prox = G->A[v];
    G->A[v] = p;
    G->m++;
}

void imprimeGrafo(Grafo G)
{
    int i;
    Noh* p;
    fprintf(stdout, " %d %d \n", G->n, G->m);
    for (i = 0; i < G->n; i++) {
        for (p = G->A[i]; p != NULL; p = p->prox)
            fprintf(stdout, " %2d ", p->rotulo);
        fprintf(stdout, " -1 ");
        fprintf(stdout, "\n");
    }
}

Grafo liberaGrafo(Grafo G)
{
    int i;
    Noh* p;
    for (i = 0; i < G->n; i++) {
        p = G->A[i];
        while (p != NULL) {
            G->A[i] = p;
            p = p->prox;
            free(G->A[i]);
        }
        G->A[i] = NULL;
    }
    free(G->A);
    G->A = NULL;
    free(G);
    return NULL;
}

Fila* criaFila()
{
    Fila* Q;
    Q = malloc(sizeof(Fila));
    if (!Q)
        return NULL;

    Q->head = Q->tail = NULL;
    return Q;
}

int filaVazia(Fila* Q)
{
    if (Q->head == NULL && Q->tail == NULL)
        return 1;
    return 0;
}

void insereFila(Fila* Q, int x)
{
    Node* tmp;
    tmp = (Node*)malloc(sizeof(Node));
    if (!tmp)
        return;
    tmp->data = x;
    tmp->next = NULL;
    if (Q->tail == NULL)
    {
        Q->head = Q->tail = tmp;
    }
    else
    {
        Q->tail->next = tmp;
        Q->tail = tmp;
    }
}

int removeFila(Fila* Q)
{
    Node* tmp;
    int ret;
    if (Q->head == NULL) 
        return -1;
    else {
        tmp = Q->head;
        ret = tmp->data;
        Q->head = Q->head->next;
        if (Q->head == NULL) {
            Q->tail = NULL;
        }
        free(tmp);
        return ret;
    }
    return ret;
}

void liberaFila(Fila* Q) {
    Node* tmp;
    while (Q->head)
    {
        tmp = Q->head;
        Q->head = Q->head->next;
        free(tmp);
    }
    free(Q);
}
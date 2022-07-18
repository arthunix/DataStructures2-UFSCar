/*
Author  : Arthur Eugenio Silverio
Data    : 24 / 10 / 2021
Name    : Distância genômica

Description: O objetivo do programa ́e, dada uma sequência de números inteiros correspondendo ao genoma do indivíduo 2
(numerado de acordo com a ordem do indivíduo 1), determinar a distância genômica baseada apenas em inversões entre os 
dois indivíduos.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

unsigned long long merge_while_count(int v[], int p, int q, int r) {
    int i, j, k;
    unsigned long long num_inv = 0;
    i = p; j = q; k = 0;
    int* w = malloc((r - p)* sizeof(int));
    while (i < q && j < r)
    {
        if (v[i] <= v[j])
            w[k++] = v[i++];
        else // v[i] > v[j]
        {
            w[k++] = v[j++];
            num_inv += q - i;
        }
    }
    while (i < q)
        w[k++] = v[i++];
    while (j < r) 
        w[k++] = v[j++];
    for (k = 0; k < (r - p); k++)
        v[p + k] = w[k];
    free(w);
    return num_inv;
}

/* Inversion counter based on Merge Sort Algorithm 
   - time efeciency:  O(n*log(n))
   - space eficiency: O(n)                      */
unsigned long long count_inversion(int v[], int p, int r) {
    int m;
    unsigned long long num_inv = 0;
    if (r - p > 1)
    {
        m = (p + r) / 2; // m = p + (r - p) / 2;
        num_inv += count_inversion(v, p, m);
        num_inv += count_inversion(v, m, r);
        num_inv += merge_while_count(v, p, m, r);
    }
    return num_inv;
}

int main(int argc, char* argv[])
{
    char file_name[MAX];
    FILE* entrada;
    int i, n;
    unsigned long long num_inv = 0;

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
    // lendo do arquivo da instância
    fscanf(entrada, "%d", &n);
    int* v = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        fscanf(entrada, "%d", &v[i]);
    // imprime(v, n);
    num_inv = count_inversion(v, 0, n);

    // printf("%I64u\n", num_inv);
    printf("%llu\n", num_inv);

    fclose(entrada);
    return 0;
}
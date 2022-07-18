#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main(int argc, char *argv[])
{
    char file_name[MAX];
    FILE *entrada;

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

    fclose(entrada);
    return 0;
}

/*
Author  : Arthur Eugenio Silverio
Data    : 17 / 09 / 2021
Release : 29 / 09 / 2021
Name    : Administrando os Contatinhos

Description: O objetivo é armazenar e manipular os dados dos seus contatinhos usando as estruturas de dados
aprendidadas na diciplina, especificamente nesse foi ultilizado a estrutura de hash table tratando colisões
listas ligadas

(C) 2021 Arthur Eugenio Silverio
This file is released under the Simplified 2-clause BSD License (see https://en.wikipedia.org/wiki/BSD_licenses for more)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_SIZE 1000000

// User defined data types
typedef struct node Node;
typedef struct node {
	char name[11];
	char number[9];
	Node *next;
}node;
//typedef node **hash_table; It just confuses our life

// User defined functions
node** htInit(node* *table);
int hash(char name[]);
node** malloc_s(int size);
//node* malloc_safe();
node* htSearch(node* *cont, char nam[]);
node* htInsert(node* *cont, char nam[], char num[]);
node* htModify(node* *cont, char nam[], char num[]);
int htDelete(node* *cont, char nam[]);

int main(int argc, char* argv[])
{
	unsigned short int active = 1;
	node* *contatinhos = NULL;
	contatinhos = htInit(contatinhos);
	while (active)
	{
		char instruction;
		char name[10]; char number[9];
		scanf("%c", &instruction);
		switch (instruction)
		{
		case 'I':
			scanf("%s", name);
			scanf("%s", number);
			node* contact_insert = htInsert(contatinhos, name, number);
			if (contact_insert == NULL)
				printf("Contatinho ja inserido\n");
			break;
		case 'P':
			scanf("%s", name);
			node* contact_search = htSearch(contatinhos, name);
			if (contact_search == NULL)
				printf("Contatinho nao encontrado\n");
			else
				printf("Contatinho encontrado: telefone %s\n", contact_search->number);
			break;
		case 'A':
			scanf("%s", name);
			scanf("%s", number);
			node* contact_modify = htModify(contatinhos, name, number);
			if (contact_modify == NULL)
				printf("Operacao invalida: contatinho nao encontrado\n");
			break;
		case 'R':
			scanf("%s", name);
			if (!htDelete(contatinhos,name))
				printf("Operacao invalida: contatinho nao encontrado\n");
			break;
		case '0':
			active = 0;
			break;
		default:
			break;
		}
		//_flushall(); // Unix syscalls don't like this
	}
	//free(contatinhos); // We don't need to free memory?
	return 0;
}

node** htInit(node* *table)
{
	int h;
	table = malloc_s(HASH_TABLE_SIZE);
	for (h = 0; h < HASH_TABLE_SIZE; h++)
		table[h] = NULL;
	return table;
}

int hash(char name[])
{
    int i, h = 0;
    int primo = 127;
    for (i = 0; name[i] != '\0'; i++)
        h = (h * primo + name[i]) % HASH_TABLE_SIZE;
    return h;
}

node** malloc_s(int size)
{
	node** ptr = malloc(size*sizeof(node**));
	if (ptr == NULL) {
		fprintf(stderr, "Error: memory fault\n");
		exit(1);
	}
	return ptr;
}

/*node* malloc_safe()
{
	node* ptr = malloc(sizeof(node**));
	if (ptr == NULL) {
		fprintf(stderr, "Error: memory fault\n");
		exit(1);
	}
	return ptr;
}*/

node* htSearch(node* *cont, char nam[])
{
	node *p;
	int h = hash(nam);
	p = cont[h];
	while (p != NULL && strcmp(p->name, nam) != 0)
		p = p->next;
	if (p != NULL)
		return p;
	return NULL;
}

node* htInsert(node* *cont, char nam[], char num[])
{
	node *p;
	int h = hash(nam);
	p = cont[h];
	while (p != NULL && strcmp(p->name, nam) != 0)
		p = p->next;
	if(p != NULL && strcmp(p->name, nam) == 0)
		return NULL;
	if (p == NULL)
	{	// Always insert in the beginning of the list
		p = malloc(sizeof(*p));
		strcpy(p->name, nam);
		strcpy(p->number, num);
		p->next = cont[h];
		cont[h] = p;
	}
	return p;
}

node* htModify(node** cont, char nam[], char num[])
{
	node* p;
	int h = hash(nam);
	p = cont[h];
	while (p != NULL && strcmp(p->name, nam) != 0)
		p = p->next;
	if (p != NULL && strcmp(p->name, nam) == 0)
	{	// It just modify the value if it was find
		strcpy(p->number, num);
		return p;
	}
	return NULL;
}

int htDelete(node** cont, char nam[])
{
	node* p, *aux;
	int h = hash(nam);
	p = cont[h];
	if (p == NULL) // If it's a void list
		return 0;
	if (strcmp(p->name, nam) == 0)
	{	// Removing from the head of the list
		cont[h] = p->next;
		free(p);
		return 1;
	}
	while (p->next != NULL && strcmp((p->next)->name, nam) != 0)
		p = p->next;
	if (p->next != NULL)
	{	// Removing from the middle of the list
		aux = p->next; // The aux if to not delete the current pointier
		p->next = aux->next;
		free(aux);
		return 1;
	}
	return 0;
}
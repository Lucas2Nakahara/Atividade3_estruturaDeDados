#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 5
#define TAMANHO_TEXTO 100
#define MAX_OPERACOES 10

typedef struct {
    int dados[TAMANHO];
    int topo;
} Pilha;

bool isEmpty(Pilha *p){
	return p->topo == -1;
}



void inicializar(Pilha *p){
    p->topo = -1;
}

void push(Pilha *p, int dado){

	if(p->topo == TAMANHO - 1){
		printf("Pilha Cheia!");
		return;
	}

	p->topo++;
	p->dados[p->topo] = dado;

}

int imprime_pilha(Pilha *p){

	if(isEmpty(p)){
		printf("Pilha Vazia");
		return;
	}

	int i;

	for(i = 0; i <= p->topo; i++){
		printf("%d -> ", p->dados[i]);
	}

	printf("topo\n");
}


typedef struct {
    char operacoes[MAX_OPERACOES][TAMANHO_TEXTO];
    int topo;
} PilhaTexto;

void inicializarTexto(PilhaTexto *p) {
    p->topo = -1;
}

int isEmptyTexto(PilhaTexto *p) {
    return p->topo == -1;
}

int isFullTexto(PilhaTexto *p) {
    return p->topo == MAX_OPERACOES - 1;
}

void pushTexto(PilhaTexto *p, const char *texto) {
    if (isFullTexto(p)) {
        printf("Pilha de texto cheia!\n");
        return;
    }
    p->topo++;
    strcpy(p->operacoes[p->topo], texto);
}

char* popTexto(PilhaTexto *p) {
    if (isEmptyTexto(p)) {
        printf("Pilha de texto vazia!\n");
        return NULL;
    }
    return p->operacoes[p->topo--];
}

void escrever(PilhaTexto *undo, const char *textoAtual) {
    pushTexto(undo, textoAtual);
    printf("Texto atual: %s\n", textoAtual);
}

void desfazer(PilhaTexto *undo, PilhaTexto *redo) {
    if (isEmptyTexto(undo)) {
        printf("Nada para desfazer.\n");
        return;
    }
    char *ultimo = popTexto(undo);
    pushTexto(redo, ultimo);
    printf("Desfeito. Texto atual: %s\n", isEmptyTexto(undo) ? "(vazio)" : undo->operacoes[undo->topo]);
}

void refazer(PilhaTexto *undo, PilhaTexto *redo) {
    if (isEmptyTexto(redo)) {
        printf("Nada para refazer.\n");
        return;
    }
    char *refazerTexto = popTexto(redo);
    pushTexto(undo, refazerTexto);
    printf("Refeito. Texto atual: %s\n", refazerTexto);
}


int pop(Pilha *p){

	if(isEmpty(p)){
		printf("Pilha Vazia!");
		return;
	}

	int temp = p->dados[p->topo];
	p->topo--;
	return temp;

}

void topo(Pilha *p){
	if(isEmpty(p)){
		printf("Pilha Vazia!");
		return;
	}

	printf("\n\nTopo => %d", p->dados[p->topo]);
}

void inverter_vetor(int vetor[], int tamanho) {
    Pilha p;
    inicializar(&p);

    
    for (int i = 0; i < tamanho; i++) {
        push(&p, vetor[i]);
    }

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = pop(&p);
    }
}

void remover_pares(Pilha *p) {
    Pilha auxiliar;
    inicializar(&auxiliar);


    while (!isEmpty(p)) {
        int valor = pop(p);
        if (valor % 2 != 0) {
            push(&auxiliar, valor);
        }
    }

    while (!isEmpty(&auxiliar)) {
        push(p, pop(&auxiliar));
    }
}

void ordenar_pilha(Pilha *p) {
    Pilha aux;
    inicializar(&aux);

    while (!isEmpty(p)) {
        int tmp = pop(p);

        while (!isEmpty(&aux) && aux.dados[aux.topo] > tmp) {
            push(p, pop(&aux));
        }

        push(&aux, tmp);
    }

    while (!isEmpty(&aux)) {
        push(p, pop(&aux));
    }
}



main() {

    Pilha p1,p2;

    inicializar(&p1);
    inicializar(&p2);

    push(&p2, 10);
    push(&p2, 20);
    push(&p2, 30);

    push(&p1, 15);
    push(&p1, 25);
    push(&p1, 35);

    printf("Conteúdo da Pilha p1:\n");
    imprime_pilha(&p1);

    printf("\nConteúdo da Pilha p2:\n");
    imprime_pilha(&p2);

    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("\nVetor Original:\n ");
    for (int i = 0; i<tamanho; i++) {
        printf("%d", vetor[i]);
    }
    inverter_vetor(vetor, tamanho);

    printf("\nVetor Invertido: \n");
    for (int i=0; i<tamanho;i++) {
        printf("%d", vetor[i]);
    }


    PilhaTexto undo, redo;
    inicializarTexto(&undo);
    inicializarTexto(&redo);

    escrever(&undo, "Eae");
    escrever(&undo, "Eae, fi");
    escrever(&undo, "Eae, fi!");

    desfazer(&undo, &redo);
    desfazer(&undo, &redo); 

    refazer(&undo, &redo);  
    refazer(&undo, &redo); 
    refazer(&undo, &redo);  


    printf("Pilha original:\n");
    imprime_pilha(&p1);

    remover_pares(&p1);

    printf("\nPilha após remover pares:\n");
    imprime_pilha(&p1);

        printf("\n\n--- Ordenando pilha p1 ---\n");

    printf("Pilha antes da ordenação:\n");
    imprime_pilha(&p1);

    ordenar_pilha(&p1);

    printf("\nPilha após ordenação:\n");
    imprime_pilha(&p1);

    
    return 0;

}
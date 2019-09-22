/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cristian
 *
 * Created on 14 de Setembro de 2019, 19:16
 */

#include <cstdlib>
#include<stdio.h>
#include <string.h>
using namespace std;

#define MENU "\n1-Inserir\n2-Atualizar\n3-Excluir\n4-Listar\n5-Limpar a listar\n"

/*
 * 
 */

struct Num {
    int num;
    struct Num *prox;
} *inicio = NULL;

int listaIsVazia() {
    if (inicio == NULL)
        return 1;
    else
        return 0;
}

void inserirFim(struct Num item) {
    struct Num *aux = inicio, *novo = new(Num);
    novo->num = item.num;
    novo->prox = NULL;
    if (listaIsVazia() == 1)
        inicio = novo;
    else {
        for (; aux != NULL; aux = aux->prox);
        aux->prox = novo;
    }

}

void inserirInicio(struct Num item) {
    struct Num *novo = new(struct Num);
    novo->num = item.num;
    novo->prox = inicio;
    inicio = novo;



}

void listar(struct Num *aux) {
    if (aux == NULL)
        printf("\nLista vazia ou fim da lista.\n");
    else {
        printf("%d\n", aux->num);
        listar(aux->prox);
    }


}

struct Num *buscar(int num) {
    
    struct Num *aux = inicio;
    for (; aux != NULL; aux = aux->prox)
        if (aux->num == num)
            return aux;
    return NULL;

}

void ordernacaoEmBolha() {
    struct Num *antProx,*antAtual,*aux, *auxProx, *auxAtual = inicio;
    for (; auxAtual != NULL; auxAtual = auxAtual->prox) {
        for (auxProx = auxAtual->prox; auxProx != NULL;auxProx=auxProx->prox) {
            if (auxAtual->num > auxProx->num) {
                if (auxAtual == inicio) {
                    antProx->prox=auxAtual;
                    auxAtual->prox=auxProx->prox;
                    aux=auxProx;
                    aux->prox=antProx;
                    inicio=aux;
                    
                } else if (auxProx->prox != NULL) {
                    aux=auxProx;
                    auxAtual->prox=auxProx->prox;
                    antProx->prox=auxProx;
                    delete(aux);
                }
                else{
                    
                }

            }
            antProx=auxProx;
        }
        //antAtual=auxAtual;
        

    }

}

void excluir(int num) {
    struct Num *ant = NULL, *aux = inicio, *proc = buscar(num);
    if (proc == NULL)
        printf("\nNúmero não encontrado!\n");
    else {
        for (; aux != NULL; aux = aux->prox) {
            //verifica se é o mesmo endereço de memória.
            if (aux == proc)
                break;
            ant = aux;
        }
        //excluindo o primeiro elemento.
        if (ant == NULL) {
            inicio = aux->prox;
            free(aux);
        }//verificar se chegou ao final da lista.
        else if (aux != NULL) {
            ant->prox = aux->prox;
            free(aux);
        }
    }

}

void excluirTudo(struct Num *aux) {
    if (aux == NULL) {
        printf("\nLista vazia!!!\n");
    } else {
        printf("\nExcluindo o número %d\n", aux->num);
        excluir(aux->num);
        excluirTudo(aux->prox);
    }



}

void atualizar(int numProc, int numNovo) {
    struct Num *numAntigo = buscar(numProc);
    if (numAntigo == NULL) {
        printf("Esse número não existe!");
    } else {
        numAntigo->num = numNovo;
    }
}

int main(int argc, char** argv) {
    struct Num novoNum;
    char resp[1];
    int op = 0;
    do {
        int numAleatorio=rand()%100;
        printf(MENU);
        scanf("%d", &op);
        printf("\n");
        switch (op) {
            case 1:
                printf("\nInforme um número:");
                scanf("%d",&novoNum.num);
                inserirInicio(novoNum);
                break;
            case 2:
                int numAntigo, numNovo;
                printf("Informe o numero antigo:");
                scanf("%d*c", &numAntigo);
                printf("Informe o numero Novo:");
                scanf("%d*c", &numNovo);
                atualizar(numAntigo, numNovo);
                break;
            case 3:
                int num;
                printf("Informe o número a ser excluído:");
                scanf("%d*c", &num);
                excluir(num);
                break;
            case 4:
                listar(inicio);
                break;
            case 5:
                excluirTudo(inicio);
                break;
        }
        //ordernacaoEmBolha();
        printf("Deseja continuar(s/n)?");
        scanf("%s", &resp);
    } while (!strcasecmp(resp, "s"));
    return 0;
}


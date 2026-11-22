//
// Created by gusta on 19/11/2026.
//

#ifndef DESPESA_H
#define DESPESA_H

#define MAX 100

// cria a struct para despesas
typedef struct Despesa {
    int codigo;
    char nome[50];
    char categoria[50];
    int dia;
    int mes;
    int ano;
    double valor_pago;
}despesa;

// gera o vetor e externaliza como v[MAX]
typedef despesa *p_despesa;
extern p_despesa v[MAX];

// funcionalidades
void inicializar(void); // inicializa o ponteiro com NULL

void cadastrar(void); // Cadastra uma nova despesa na base de dados

void listar_todos(void); // Lista todas as despesas já cadastradas na base

void buscar_despesa(int codigo); // busca uma despesa por código

void relatorio(void); // gera um relátorio de todas as despesas cadastradas

void sair(void); // salvar e sair do programa

#endif //DESPESA_H
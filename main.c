#include "despesa.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // define as variáveis utilizadas
    int opcao;
    int codigo;

    // inicializa o programa
    inicializar();

    do {
        // menu do usuário
        printf("\nMenu Gerenciador de Despesas:\n\n");
        printf("1. Cadastrar Despesa\n");
        printf("2. Exibir Todas Despesas\n");
        printf("3. Buscar Despesa por Codigo\n");
        printf("4. Relatorio Geral\n");
        printf("5. Salvar e Sair do Sistema\n");

        printf("Digite o numero da opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {

            //cadastro de despesa
            case 1:
                cadastrar();
                break;

            // exibe todas as depesas cadastradas
            case 2:
                listar_todos();
                break;

            // exibe uma despesa filtrada pelo seu código
            case 3:
                printf("Digite o codigo da despesa que deseja visualizar: ");
                scanf("%d", &codigo);
                buscar_despesa(codigo);
                break;

            // exibe um relatório geral de todas as despesas cadastradas
            case 4:
                relatorio();
                break;

            // Salva os arquivos e sai do sistema
            case 5:
                printf("Arquivos salvos em despesas.txt\n");
                printf("Voce saiu do sistema!\n\n");
                sair();
                break;

            // validação de opção
            default:
                printf("Opcao invalida!\n");
        }
    }while(1);

    return 0; // padrão da main() mas inutilizado nesse programa
}


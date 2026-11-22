//
// Created by aluno on 19/11/2026.
//

// declara variáveis
#include "despesa.h"
#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>

p_despesa v[MAX]; // declara o vetor v (de despesas)

// função que inicializa o vetor de despesas
void inicializar(){
    for (int pos = 0; pos < MAX; pos++){
        v[pos] = NULL; // atribui NULL para todas as posições do vetor
    }

    // Encontra o arquivo caso ele exista
    FILE *despesas = fopen("../despesas.txt", "r");

    // Se o arquivo nao existir, retorna e inicia o sistema com o vetor vazio
    if (despesas == NULL)
    {
        return;
    }

    char linha[256];
    int pos = 0;
    int cod_lido;

    // Le o arquivo linha (fazendo a verificação se a linha está preenchida)
    while (pos < MAX && fgets(linha, sizeof(linha), despesas) != NULL)
    {
        // Procura a linha que inicia com: "Codigo X:"
        if (sscanf(linha, "Codigo %d:", &cod_lido) == 1)
        {
            p_despesa nova = (p_despesa) malloc(sizeof(despesa));
            if (nova == NULL)
            {
                printf("Erro ao alocar memoria ao carregar arquivo\n");
                break;
            }

            nova->codigo = cod_lido;

            // 1. Le a linha "Nome: ..."
            if (fgets(linha, sizeof(linha), despesas) != NULL)
            {
                linha[strcspn(linha, "\r\n")] = '\0'; // Remove quebra de linha
                // "%[^\n]" le toda a string (inclusive com espacos) apos "Nome: "
                sscanf(linha, "Nome: %[^\n]", nova->nome);
            }

            // 2. Le a linha "Categoria: ..."
            if (fgets(linha, sizeof(linha), despesas) != NULL)
            {
                linha[strcspn(linha, "\r\n")] = '\0';
                sscanf(linha, "Categoria: %[^\n]", nova->categoria);
            }

            // 3. Le a linha "Data: d/m/a"
            if (fgets(linha, sizeof(linha), despesas) != NULL)
            {
                sscanf(linha, "Data: %d/%d/%d", &nova->dia, &nova->mes, &nova->ano);
            }

            // 4. Le a linha "Valor: 0.00"
            if (fgets(linha, sizeof(linha), despesas) != NULL)
            {
                sscanf(linha, "Valor: %lf", &nova->valor_pago);
            }

            v[pos] = nova;
            pos++;
        }
    }

    fclose(despesas);
}

// cadastra uma nova despesa no vetor
void cadastrar() {
    int espaco_encontrado = 0; // verifica se o vetor tem espaço diponivel para um novo registro

    for (int pos = 0; pos < MAX; pos++) {
        if (v[pos] == NULL) {
            espaco_encontrado = 1; // se há espaço NULL então há espaço disponível

            int codigo = 0;

            for (int i = 0; i < MAX; i++) {
                if (v[i] != NULL) {  // verifica se existe depesa cadastrada
                    if (v[i]->codigo > codigo) { // busca o maior código registrado
                        codigo = v[i]->codigo; // atribui o codigo atual como maior codigo
                    }
                }
            }

            codigo++; // incrementa 1 no código atual para novo registro de despesa

            v[pos]= (p_despesa) malloc(sizeof(despesa)); // aloca uma quantidade de memória (sizeof(despesa)) para o novo registro

            // Verifica se a memória foi alocada
            if (v[pos] == NULL) {
                printf("Erro ao alocar memoria\n");
                return;
            }

            fflush(stdin); // limpa o buffer

            v[pos]->codigo = codigo; // salva o código atual e validado no vetor

            // requisita e recebe o nome da despesa
            // retira a quebra de linha no final do nome
            printf("Digite o nome da despesa : ");
            fgets(v[pos]->nome, sizeof(v[pos]->nome), stdin);
            v[pos]->nome[strcspn(v[pos]->nome, "\n")] = '\0';

            // requisita e recebe a categoria da despesa
            // retira a quebra de linha no final da categoria
            printf("Digite a categoria  da despesa : ");
            fgets(v[pos]->categoria, sizeof(v[pos]->categoria), stdin);
            v[pos]->categoria[strcspn(v[pos]->categoria, "\n")] = '\0';

            //requisita e recebe o dia que foi feito a despesa
            printf("Digite o dia em que voce fez a despeza( somente o dia)  : ");
            scanf("%d",&v[pos]->dia);

            //requisita e recebe o mes que foi feito a despesa
            printf("Digite o mes em que voce fez a despeza( somente o mes)  : ");
            scanf("%d",&v[pos]->mes);

            //requisita e recebe o ano que foi feito a despesa
            printf("Digite o ano em que voce fez a despeza( somente o ano)  : ");
            scanf("%d",&v[pos]->ano);

            //requisita e recebe o valor da despesa
            printf(" Digite o valor da despesa : ");
            scanf("%lf",&v[pos]->valor_pago);

            printf(" Despeza cadastrada com sucesso \n ");
            return;
        }
    }
    // se espaço encontrado == 0 quer dizer que o vetor todo já foi preenchido
    if (!espaco_encontrado) printf("Nao ha espaco disponivel!\n");
}

// lista todos os registros já concluídos
void listar_todos() {
    for (int pos = 0; pos < MAX; pos++) {
        if (v[pos] != NULL) { // verifica se há dados gravados na posição (pos)
            printf("---------------------------------------------------\n");
            printf("Codigo %d:\n", v[pos]->codigo);
            printf("Nome: %s\n", v[pos]->nome);
            printf("Categoria: %s\n", v[pos]->categoria);
            printf("Data: %d/%d/%d\n", v[pos]->dia, v[pos]->mes, v[pos]->ano);
            printf("Valor: %.2lf\n", v[pos]->valor_pago);
            printf("\n\n");
        }
        else break; // se posição == NULL acabou os registros
    }
}

// busca uma despesa pelo seu código
void buscar_despesa(int codigo) {
    for (int pos = 0; pos < MAX; pos++) {
        if (v[pos] != NULL && v[pos]->codigo == codigo) { // verifica se há dados gravados e compara o código com o do registro
            printf("---------------------------------------------------\n");
            printf("Codigo %d:\n", v[pos]->codigo);
            printf("Nome: %s\n", v[pos]->nome);
            printf("Categoria: %s\n", v[pos]->categoria);
            printf("Data: %d/%d/%d\n", v[pos]->dia, v[pos]->mes, v[pos]->ano);
            printf("Valor: %.2lf\n", v[pos]->valor_pago);
            printf("\n\n");
        }
    }
}

// gera um relatório com a media geral, o maior valor e a quantidade de registros gravados
void relatorio() {
    // define as variaveis
    double media_geral=0, maior_valor=0, contador=0;
    int qtd=0;

    // percorre o vetor e realiza os cálculos
    for (int pos = 0; pos < MAX; pos++) {
        if (v[pos] != NULL) {
            qtd++;
            contador += v[pos]->valor_pago;
            if (v[pos]->valor_pago > maior_valor) {
                maior_valor = v[pos]->valor_pago;
            }
        }
    }
    media_geral = contador/qtd;

    // exibe o resultado
    printf("-------RELATORIO GERAL--------\n");
    printf("Quantidade de despesa: %d\n", qtd);
    printf("Maior valor cadastrado: %.2lf\n", maior_valor);
    printf("Media do valor das despesas: %.2lf\n", media_geral);
    printf("\n\n");
}

// salva os dados em relatorio.txt e sai do programa
void sair() {

    // abre o cria o arquivo
    FILE *despesas = fopen("..//despesas.txt", "w");

    // valida abertura do arquivo
    if (despesas == NULL) {
        perror("Erro ao abrir ou criar o arquivo");
        return;
    }

    // grava os dados no txt
    for (int pos = 0; pos < MAX; pos++) {
        if (v[pos] != NULL) {
            fprintf(despesas, "---------------------------------------------------\n");
            fprintf(despesas, "Codigo %d:\n", v[pos]->codigo);
            fprintf(despesas, "Nome: %s\n", v[pos]->nome);
            fprintf(despesas, "Categoria: %s\n", v[pos]->categoria);
            fprintf(despesas, "Data: %d/%d/%d\n", v[pos]->dia, v[pos]->mes, v[pos]->ano);
            fprintf(despesas,"Valor: %.2lf\n", v[pos]->valor_pago);
            fprintf(despesas, "\n\n");
        }
    }

    // fecha o arquivo
    fclose(despesas);

    // limpa memória
    for (int pos = 0; pos < MAX; pos++) {
        if (v[pos] != NULL) {
            free(v[pos]);
            v[pos] = NULL;
        }
    }

    // sai do programa
    exit(0);
}
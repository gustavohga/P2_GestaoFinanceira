# Gerenciador de Despesas em C

Sistema de linha de comando para cadastro, consulta e relatório de despesas pessoais, desenvolvido em linguagem C como atividade acadêmica.

## 1. Identificação da dupla

| Nome completo | RA |
|---|---|
| Gustavo Henrique Gonçalves Aguiar | 1630482613016 |
| Matheus Almeida de Lucena | 1630482613014 |

Análise e Desenvolvimento de Sistemas - 2º Semestre
Linguagem de Programação - Maromo 

## 2. Motivo da escolha do tema

Escolhemos o tema **Controle de Gastos e Orçamento Pessoal** entre as opções listadas porque foi um tema que interessou os dois integrantes do grupo por ser um tema facilmente aplicável no dia a dia de cada um.

## 3. Como a dupla atacou e modelou o problema

### 3.1 Divisão de tarefas

Todas as decisões foram tomadas de forma conjunta sendo realizadas reuniões presenciais na faculdade e reuniões online através do Google Meet para a realização da escolha do tema, desenvolvimento, estruturação, testes, validação e entrega do projeto.

### 3.2 Organização dos arquivos

O projeto foi dividido em três arquivos, separando a interface com o usuário da lógica do sistema:

| Arquivo | Responsabilidade |
|---|---|
| `main.c` | Ponto de entrada. Exibe o menu, lê a opção do usuário e chama a função correspondente. |
| `despesa.h` | Definição da `struct Despesa`, do tipo `p_despesa`, da constante `MAX` e dos protótipos das funções. |
| `despesa.c` | Implementação de todas as funcionalidades e do vetor de despesas. |

### 3.3 Modelagem dos dados

Cada despesa é representada pela struct `Despesa` (apelidada de `despesa`):

```c
typedef struct Despesa {
    int codigo;
    char nome[50];
    char categoria[50];
    int dia;
    int mes;
    int ano;
    double valor_pago;
} despesa;
```

As despesas ficam em um **vetor de ponteiros** (`p_despesa v[MAX]`, com `MAX = 100`):

- Uma posição com `NULL` significa que está livre.
- Cada registro é alocado dinamicamente com `malloc` apenas quando uma nova despesa é cadastrada.
- Toda a memória é liberada com `free` ao sair do sistema.

### 3.4 Arquitetura das funções

| Função | O que faz |
|---|---|
| `inicializar()` | Zera o vetor (`NULL`) e, se o arquivo `despesas.txt` existir, carrega os registros salvos anteriormente. |
| `cadastrar()` | Procura a primeira posição livre, gera automaticamente o código (maior código existente + 1) e lê os dados da despesa. |
| `listar_todos()` | Exibe todas as despesas cadastradas. |
| `buscar_despesa(int codigo)` | Busca e exibe uma despesa pelo código informado. |
| `relatorio()` | Mostra a quantidade de despesas, o maior valor cadastrado e a média dos valores. |
| `sair()` | Grava os dados em `despesas.txt`, libera a memória alocada e encerra o programa. |

### 3.5 Tratamento dos dados e persistência

- Os dados são salvos em um arquivo de texto (`despesas.txt`) em formato legível, com um bloco por despesa:

  ```
  ---------------------------------------------------
  Codigo 1:
  Nome: Mercado
  Categoria: Alimentacao
  Data: 10/11/2026
  Valor: 150.75
  ```

- Ao iniciar, o programa lê esse arquivo linha a linha, identifica cada bloco pela linha `Codigo X:` e reconstrói os registros com `sscanf`.
- Os textos (nome e categoria) são lidos com `fgets`, permitindo espaços, e a quebra de linha é removida com `strcspn`.
- Há verificação de falha na alocação de memória, de abertura de arquivo e de vetor cheio.
- O código de cada despesa é gerado automaticamente, evitando repetição.

## 4. Compilação e execução

### Pré-requisitos

- Compilador GCC (ou outro compilador C compatível).

### Pelo terminal

Na pasta do projeto, compile com:

```bash
gcc main.c despesa.c -o gerenciador_despesas
```

Execute com:

- **Linux / macOS:**
  ```bash
  ./gerenciador_despesas
  ```
- **Windows (Prompt de Comando ou PowerShell):**
  ```bash
  gerenciador_despesas.exe
  ```

> **Atenção ao arquivo de dados:** o programa lê e grava o arquivo em `../despesas.txt`, ou seja, **na pasta anterior à pasta de onde o executável é executado**. Isso acontece porque o projeto foi desenvolvido em uma IDE que executa o programa dentro de uma subpasta de build (ex.: `cmake-build-debug`). Para rodar pelo terminal, execute o programa a partir de uma subpasta do projeto. Exemplo:
>
> ```bash
> mkdir build
> cd build
> gcc ../main.c ../despesa.c -o gerenciador_despesas
> ./gerenciador_despesas
> ```
>
> Dessa forma, o `despesas.txt` é criado na raiz do projeto.

### Pela IDE (CLion / Code::Blocks / Dev-C++)

1. Crie um projeto em C e adicione os arquivos `main.c`, `despesa.c` e `despesa.h`.
2. Compile e execute pelo botão de **Run** da IDE.
3. Se necessário, ajuste o diretório de execução para que o `despesas.txt` fique no local esperado.

### Uso do programa

Ao executar, o menu abaixo é exibido:

```
Menu Gerenciador de Despesas:

1. Cadastrar Despesa
2. Exibir Todas Despesas
3. Buscar Despesa por Codigo
4. Relatorio Geral
5. Salvar e Sair do Sistema
```

**Importante:** os dados só são gravados em `despesas.txt` ao escolher a opção **5**. Se o programa for fechado de outra forma, as despesas cadastradas na sessão serão perdidas.

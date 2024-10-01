# README: Shell

## Descrição

Este código implementa um shell simples em C, projetado para permitir a execução de comandos no sistema operacional. O shell suporta comandos como `cd` para mudar diretórios e `exit` para sair do programa. Para outros comandos, ele utiliza `execvp` para criar um novo processo que executa o comando solicitado.

## Funcionalidades

- **Execução de Comandos**: Permite a execução de comandos de sistema.
- **Mudança de Diretório**: Implementa o comando `cd` para navegar entre diretórios.
- **Saída do Shell**: Permite ao usuário sair do shell com o comando `exit`.
- **Gerenciamento de Processos**: Utiliza `fork` e `waitpid` para gerenciar processos filhos.

## Estrutura do Código

- **Inclusões de Bibliotecas**: O código inclui bibliotecas padrão como `<stdio.h>`, `<stdlib.h>`, `<string.h>`, e `<unistd.h>`, necessárias para entrada/saída, alocação de memória, manipulação de strings, e funções de sistema.
  
- **Definições**:
  - `BUF_SIZE`: Tamanho do buffer para leitura de comandos.
  - `CMD_MAX`: Número máximo de palavras em um comando.
  - `DIV`: Delimitadores para separação de palavras em comandos.

- **Loop Principal**:
  - Exibe o diretório atual e solicita um comando do usuário.
  - Lê a entrada e separa os comandos em tokens.
  - Processa comandos especiais (`cd` e `exit`).
  - Cria um processo filho para executar comandos, utilizando `fork` e `execvp`.

## Compilação e Execução

Para compilar o código, utilize o seguinte comando:

```bash
gcc -o shell shell.c

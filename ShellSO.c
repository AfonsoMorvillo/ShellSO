#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100
#define CMD_MAX 11 // Quantidade de palavras em um comando
#define DIV " \n"
int main()
{
    char *buffer;
    buffer = (char *)malloc(BUF_SIZE * sizeof(char));
    size_t tamanho = BUF_SIZE;

    char *cmd[CMD_MAX];
    char *token;

    char dir[100]; // Para a leitura do diretório atual
    int i;

    while (1)
    {
        printf("%s", getcwd(dir, 100)); // Exibe o diretório atual
        printf(" > ");
        getline(&buffer, &tamanho, stdin);

        token = strtok(buffer, DIV);
        for (i = 0; i < CMD_MAX && token != NULL; i++)
        {
            cmd[i] = token;            // Adiciona token a linha de comando
            token = strtok(NULL, " "); // Null se nao tiver mais tokens
        }

        cmd[i] = NULL; // Adiciona o termo nulo ao fim da linha de comando

        if (strcmp(cmd[0], "exit") == 0)
            break; // Comando exit

        for (i = 0; i < CMD_MAX; i++)
        {
            if (cmd[i] != NULL)
            {
                printf("Lido: %s \n", cmd[i]);
            }
        }

        for (i = 0; i < CMD_MAX; i++) // limpa o vetor
        {
            cmd[i] = NULL;
        }

    }

    puts("PROGRAMA ENCERRADO");

    free(buffer);
    return 0;
}

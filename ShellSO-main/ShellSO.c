#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 100
#define CMD_MAX 11    // Quantidade de palavras em um comando
#define DIV " \t\r\n" // separador de string
int main()
{
    char *buffer;
    buffer = (char *)malloc(BUF_SIZE * sizeof(char));
    size_t tamanho = BUF_SIZE;

    char *token;
    char *comandos[CMD_MAX];

    pid_t pid, wait;
    int result;

    char dir[100]; // Para a leitura do diretório atual
    int i;

    while (1)
    {
        printf("%s", getcwd(dir, 100)); // Exibe o diretório atual
        printf(" > ");

        if (getline(&buffer, &tamanho, stdin) == -1)
            break;

        token = strtok(buffer, DIV);
        for (i = 0; i < CMD_MAX && token != NULL; i++)
        {
            comandos[i] = token;       // Adiciona token a linha de comando
            token = strtok(NULL, DIV); // Null se nao tiver mais tokens
        }

        comandos[i] = NULL; // Adiciona o termo nulo ao fim da linha de comando

        if (strcmp(comandos[0], "exit") == 0)
            break; // Comando exit

        if (strcmp(comandos[0], "cd") == 0)
        {
            if (!comandos[1])
            {                          // Diretório não especificado
                chdir(getenv("HOME")); // Retorna para home
                continue;              // Retorna ao início do loop
            }
            else if (strcmp(comandos[1], "..") == 0)
            {                // cd ..
                chdir(".."); // Retorna para o diretório antecessor ao atual
                continue;
            }
            else
            {                                // Diretório especificado
                if (chdir(comandos[1]) != 0) // Tenta navegar para o diretório especificado
                {
                    perror("Erro ao navegar para o diretório especificado");
                    // Lida com erros aqui, se necessário
                }
                continue;
            }
        }

        pid = fork(); // Cria um processo filho que executa simultaneamente a mesma instrução que o processo pai

        if (pid == 0) // é o processo filho
        { 
            /* 
           Execvp substitui o processo filho por um novo processo, executado independente do processo pai.
           Retorna somente caso encontre um erro.
           */
            if (execvp(comandos[0], comandos) == -1)
                perror("lsh"); // Sinaliza erros na execução do processo filho
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
            perror("lsh"); // Sinaliza erros em fork() se for menor q zero

        else
        { // Processo pai sendo executado
            do
            {
                wait = waitpid(pid, &result, WUNTRACED); // Aguarda pela conclusão do processo filho
            } while (!WIFEXITED(result) && !WIFSIGNALED(result));
        }
    }

    putchar('\n');
    free(buffer);
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



int main()
{
    //variaveis
    char *line = NULL;
    size_t capacity = 0;
    ssize_t bytes_read;
    int status;
    int last_status = 0;
    //
    
    
    
    while (1){
        //prompt
        printf("⚚ -> ");
        fflush(stdout);
        //apaga a merda do enter
        bytes_read = getline(&line, &capacity, stdin);

        //controle de finalização do shell
        if (bytes_read == -1) {
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        
        if(strcmp(line, "exit") == 0){
            break;
        }        
        
        if(line[0] == '\0'){
            continue;
        }
        
        //controle de leitura de argumentos
        char *args[64];
        char *tolken = strtok(line, " ");

        int i = 0;
        for( ;tolken != NULL && i < 63; i++){
            args[i] = tolken;
            tolken = strtok(NULL, " ");
        }

        args[i] = NULL;
        
        if(args[0] == NULL){
            continue;
        }
        
        pid_t pid = fork();
        
        //Gerenciador de processos
        if(pid == 0){
            execvp(args[0], args);
            perror("execvp");
            _exit(127);
        }

        else if(pid > 0){
            //controle de timing e erros
            if(waitpid(pid,&status,0) == -1){
                perror("waitpid");
            }
            else{
                if (WIFEXITED(status)) {
                    last_status = WEXITSTATUS(status);
                }
                else if (WIFSIGNALED(status)) {
                    last_status = 128 + WTERMSIG(status);
                }
            }


        }
        else{
            perror("fork");
        }
    }

    //fim do codigo e liberação de memoria
    free(line);
    return 0;
}

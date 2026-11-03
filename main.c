#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *line = NULL;
    size_t capacity = 0;
    size_t bytes_read;


    while (1){
        
        printf("-> ");
        bytes_read = getline(&line, &capacity, stdin);
        
        if (bytes_read == -1){
            break;
        }
    }
    free(line);
    return 0;
}

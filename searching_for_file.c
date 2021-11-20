#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/sem.h>
#include <dirent.h>
#include <sys/stat.h>

void file_find(char *file_name, char *current_dir, int *depth, int *quantity, char **result_file) {
    int i = -2; //for skipping "." and ".." directiries
    int depth_1 = *depth - 1;
    struct dirent *file;
    DIR *dir;
    int a;
    
        if ((dir = opendir (current_dir)) == NULL) {
            printf("ERROR");
        }
        
        while ((file = readdir (dir)) != NULL) {
            if(file->d_type != 0 && file->d_type != 4) {
                
                a = strcmp(file->d_name, file_name);
                
                if(a == 0) {
                    char temp[100];
                    strcpy(temp, current_dir);
                    (*quantity)++;
                    result_file[*quantity] = strcat(temp, "/");
                    result_file[*quantity] = strcat(temp, file->d_name);
                    
                }
                
            }
            if(file->d_type == 4)
                ++i;
            
            if( (file->d_type == 4) && (i > 0)) {
                char temp[100];
                char *next_dir;
                strcpy(temp, current_dir);
                next_dir = strcat(temp, "/");
                next_dir = strcat(next_dir, file->d_name);
                if (depth_1 >= 0) {
                    file_find(file_name, next_dir, &depth_1, quantity, result_file);
                }
            }
        
        }
        closedir(dir);
}

int main() {
    int depth = 1;
    int quantity = -1;
    
    char** result_file = calloc(10, sizeof(char*));
    for(int i = 0; i < 10; ++i) {
        result_file[i] = calloc(1000, sizeof(char));
    }
    
    char file_name[1000] = "file.c";
    
    char* current_dir =  calloc(1000, sizeof(char));
    
    gets(current_dir);
    scanf("%d", &depth);
    
    file_find(file_name, current_dir, &depth, &quantity, result_file);
    
    for(int i = 0; i < 10; ++i) {
        printf("%s", result_file[i]);
    }
    return 0;
    
    
}

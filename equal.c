#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "funzioni.h"
#include <syslog.h>


int main(int argc, char *argv[]){
    
    openlog("equal", LOG_CONS || LOG_PERROR || LOG_PID, LOG_USER);
    
    char name1[40];
    char name2[40];
    
    strcpy(name1, argv[1]);
    strcpy(name2, argv[2]);
    
        
    if(is_file(name1) && is_file(name2)){
        
        if(twoFilesCompare(name1, name2)){
            printf("I Files sono uguali\n");
            return (0);
        }
        else{
            printf("I Files sono diversi\n");
            return (1);
        }
    }
    
    if(is_file(name1) && is_dir(name2)){
        
        if(scanDir(name2, name1)){
            printf("I file %s e %s/%s sono uguali\n", name1, name2, name1);
            return (0);
        }
        else{
            printf("I file %s e %s/%s sono diversi\n", name1, name2, name1);
            return (1);
        }
    }
    
    if(is_dir(name1) && is_file(name2)){
        
        if(scanDir(name1, name2)){
            printf("I file %s e %s/%s sono uguali\n", name2, name1, name2);
            return (0);
        }
        else{
            printf("I file %s e %s/%s sono diversi\n", name2, name1, name2);
            return (1);
        }
    
    }
    
    if(is_dir(name1) && is_dir(name2)){
        scorriCartelle(name1, name2);
        scorriCartelle(name2, name1);
        return (EXIT_SUCCESS);
    }
    
    void closelog ();    
    return (EXIT_FAILURE);
}
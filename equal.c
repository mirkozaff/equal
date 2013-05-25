#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "funzioni.h"


int main(int argc, char *argv[]){
    
    char fname1[40];
    char fname2[40];
    
    strcpy(fname1, argv[1]);
    strcpy(fname2, argv[2]);
    
        
    if(is_file(fname1) && is_file(fname2)){
        
        if(twoFilesCompare(fname1, fname2)){
            printf("I Files sono uguali\n");
            return (0);
        }
        else{
            printf("I Files sono diversi\n");
            return (1);
        }
    }
    
    if(is_file(fname1) && is_dir(fname2)){
        
        if(scanDir(fname2, fname1)){
            printf("I file %s e %s/%s sono uguali\n", fname1, fname2, fname1);
            return (0);
        }
        else{
            printf("I file %s e %s/%s sono diversi\n", fname1, fname2, fname1);
            return (1);
        }
    }
    
    if(is_dir(fname1) && is_file(fname2)){
        
        if(scanDir(fname1, fname2)){
            printf("I file %s e %s/%s sono uguali\n", fname2, fname1, fname2);
            return (0);
        }
        else{
            printf("I file %s e %s/%s sono diversi\n", fname2, fname1, fname2);
            return (1);
        }
    
    }
    
    if(is_dir(fname1) && is_dir(fname2)){}
    
    
    
    
    
    //stampadir("/home/mirko/Github/equal/prova");
    
    /*
    if(is_dir(fname1)){
        printf("%s è una directory\n", fname1);
    }
    if(is_dir(fname2)){
        printf("%s è una directory\n", fname2);
    }
    if(is_file(fname1)){
        printf("%s è un file\n", fname1);
    }
    if(is_file(fname2)){
        printf("%s è un file\n", fname2);
    }*/
    
    //sameFileCheck(fname1, fname2);

    //printf("result: %d\n",check_dup_memmap(fname1, fname2));
    return (EXIT_FAILURE);
}
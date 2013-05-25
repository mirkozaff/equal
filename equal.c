#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "funzioni.h"


int main(int argc, char *argv[]){
    
    char fname1[40];
    char fname2[40];
    
    strcpy(fname1, argv[1]);
    strcpy(fname2, argv[2]);
    
        
    if(is_file(fname1) && is_file(fname2)){
        
        safe_fopen(fname1, "r");
        safe_fopen(fname2, "r");

        if(is_binary(fname1) && is_binary(fname2)){
        
            if(check_same_size(fname1, fname2, NULL, NULL)){
                printf("I Files non sono uguali\n");
                return (1);
            }
            else{
                if(sameFileCheck(fname1, fname2)){
                    printf("I Files sono uguali\n");
                    return (0);
                }
                else{
                    printf("I Files non sono uguali\n");
                    return (1);
                }
            }
        }
        else if(!is_binary(fname1) && !is_binary(fname2)){
            
            if(check_same_size(fname1, fname2, NULL, NULL)){
                printf("I Files non sono uguali\n");
                return (1);
            }
            else{
                if(sameFileCheck(fname1, fname2)){                    
                    printf("I Files sono uguali\n");
                    return (0);
                }
                else{
                    textDiff(fname1, fname2);
                    printf("I Files non sono uguali\n");
                    return (1);
                }
            }
        }
        else{
            printf("I Files non sono uguali\n");
            return (1);
       }
    }
    
    if(is_dir(fname1) && is_dir(fname2)){}
    if(is_dir(fname1) && is_file(fname2)){}
    if(is_file(fname1) && is_dir(fname2)){}
    
    
    
    
    
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
    return (0);
}
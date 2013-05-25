#include <stdio.h>
#include <string.h>
#include "funzioni.h"




int main(int argc, char *argv[]){
    
    char fname1[40];
    char fname2[40];
    
    strcpy(fname1, argv[1]);
    strcpy(fname2, argv[2]);
    
    
    /*printf("Enter name of first file : ") ;
    gets(fname1);

    printf("Enter name of second file: ");
    gets(fname2);*/
    
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
    }
    
    //sameFileCheck(fname1, fname2);

    printf("result: %d\n",check_dup_memmap(fname1, fname2));
    return (0);
}
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv) {
    /*    
    String directory = "/home/mirko/Scaricati";
    
    printf("Directory scan of %s", directory, "\n");
    printdir(directory, 0);
    printf("done.\n");
    exit(0);
    */   
    char fname1[40], fname2[40];

    printf("Enter name of first file :") ;
    gets(fname1);

    printf("Enter name of second file:");
    gets(fname2);
    
    sameFileCheck(fname1, fname2);
}


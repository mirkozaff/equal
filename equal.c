/**
 *  Anno Accademico: 2012-2013
 *  Corso di Studio: Informatica
 *  Titolo del progetto: Modifica utility di base di GNU/Linux
 *  Autori: Zaffaroni Mirko n° 151818
 *	Bonetta Giovanni n° 152122
 **/


#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "funzioni.h"
#include <syslog.h>


int main(int argc, char *argv[]){
    
    openlog(argv[0], LOG_CONS || LOG_PID, LOG_LOCAL0);
    
    char name1[40];
    char name2[40];
    
    strcpy(name1, argv[1]);
    strcpy(name2, argv[2]);
    
        
    if(is_file(name1) && is_file(name2)){
        syslog(LOG_INFO, "Confrontro tra file e file iniziato");
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
        syslog(LOG_INFO, "Confrontro tra file e cartella iniziato");
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
        syslog(LOG_INFO, "Confrontro tra cartella e file iniziato");
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
        syslog(LOG_INFO, "Confrontro tra cartella e cartella iniziato");
        scorriCartelle(name1, name2);
        syslog(LOG_INFO, "Confronto eseguito");
        return (EXIT_SUCCESS);
    }
    
    syslog(LOG_INFO, "Nessun confronto eseguito");
    closelog();    
    return (EXIT_FAILURE);
}
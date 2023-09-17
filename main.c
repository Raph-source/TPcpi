#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include "fonction.c"

int main(int argc, char **argv){

    if(strcmp("install", argv[1]) == 0){// l'installation
        if(checkPackages(argv[2]) == 1){
            installPkg(argv[2]);
        }
        else{
            printf("cpi n'a pas de package %s\n", argv[2]);
        }
            
    }

    else if(strcmp("uninstall", argv[1]) == 0){//la désinstallation
        if(checkPackages(argv[2]) == 1){
            uninstallPkg(argv[2]);
        }
        else{
            printf("cpi n'a pas de package %s\n", argv[2]);
        }
    }
    else if(strcmp("list", argv[1]) == 0){
        listePackages();
    }
    else if(strcmp("listall", argv[1]) == 0){
        listeAll();
    }
    else{
        printf("cpi n'a pas d'argument %s\n", argv[1]);
    }

   
    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>


int checkPackages(char *pkg){
    FILE *fichier = fopen("allPackages.txt", "r");
    int len;
    char chaine[25];

    if(fichier == NULL){
        puts("Erreur de l'ouverture du fichier");
        exit(1);
    }
    while(fgets(chaine, sizeof(chaine), fichier) != NULL){
        len = strlen(chaine);
        chaine[len - 1] = '\0';
        if(strcmp(chaine, pkg) == 0){
            fclose(fichier);
            return 1;
        }       
    }
    return 0;
    
}

void listePackages(){
    FILE *fichier = fopen("packages.txt", "r");

    char chaine[25];

    if(fichier == NULL){
        puts("Erreur de l'ouverture du fichier");
        exit(1);
    }
    puts("LISTE PACKAGES");
    puts("===============");
    while(fgets(chaine, sizeof(chaine), fichier) != NULL){
        printf("* %s\n",chaine);
    }
    fclose(fichier);
}

void listeAll(){
    FILE *fichier = fopen("allPackages.txt", "r");

    char chaine[25];

    if(fichier == NULL){
        puts("Erreur de l'ouverture du fichier");
        exit(1);
    }
    puts("LIST ALL PACKAGES");
    puts("===============");
    while(fgets(chaine, sizeof(chaine), fichier) != NULL){
        printf("* %s\n",chaine);
    }
    fclose(fichier);
}

void addToFile(char* pkg){
    FILE *fichier = fopen("pacman.txt", "a");
    
    if(fichier == NULL){
        puts("Erreur de l'ouverture du fichier");
        exit(1);
    }

    fprintf(fichier, "%s\n", pkg);

    fclose(fichier);
}


void installPkg(char * pkg){
    DIR *dossier;
    struct dirent *entree;
    char cheminA[100], cheminB[100];
    char commande[100];

    //récupearation des fichier pour les maitre dans fichier
    strcpy(cheminA, "");
    strcpy(cheminB, "");
    strcpy(commande, "");
    
    strcat(cheminA, "packages\\");
    strcat(cheminA, pkg);
    strcat(cheminA, "\\src\\");

    strcat(cheminB, "packages\\");
    strcat(cheminB, pkg);
    strcat(cheminB, "\\include\\");

    dossier = opendir(cheminA);
    if(dossier == NULL){
        puts("Erreur d'ouverture du dossier");
        exit(1);
    }
    strcpy(commande, "echo > ");
    while((entree = readdir(dossier)) != NULL){
        if(entree->d_type == DT_REG){
            strcat(commande, entree->d_name);
            system(commande);

            addToFile(entree->d_name);

            strcpy(commande, "echo > ");
        }
    }
    closedir(dossier);

    dossier = opendir(cheminB);
    if(dossier == NULL){
        puts("Erreur d'ouverture du dossier");
        exit(1);
    }

    strcpy(commande, "echo > include/");
    while((entree = readdir(dossier)) != NULL){
        if(entree->d_type == DT_REG){
            strcat(commande, entree->d_name);
            system(commande);
            
            addToFile(entree->d_name);
            strcpy(commande, "echo > include/");
        }
    }
    closedir(dossier);
    FILE *fichier = fopen("packages.txt", "a");
        fprintf(fichier, "%s\n", pkg);
    fclose(fichier);
}


void deleteFromFile(char* file){
    FILE *fichier = fopen("pacman.txt", "r");
    FILE *fichierTemp = fopen("tempPackages.txt", "a");
    int len;
    char chaine[25];

    if(fichier == NULL){
        puts("Erreur de l'ouverture du fichier");
        exit(1);
    }

    while(fgets(chaine, sizeof(chaine), fichier) != NULL){
        len = strlen(chaine);
        chaine[len - 1] = '\0';
        if(strcmp(chaine, file) != 0){
            strcat(chaine, "\n");
            fprintf(fichierTemp, "%s", chaine);
        }
           
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove("pacman.txt");
    rename("tempPackages.txt", "pacman.txt");
}
void delPackages(char *pkg){
    FILE *fichier = fopen("packages.txt", "r");
    FILE *fichierTemp = fopen("tempPackages.txt", "a");
    int len;
    char chaine[25];

    if(fichier == NULL){
        puts("Erreur de l'ouverture du fichier");
        exit(1);
    }

    while(fgets(chaine, sizeof(chaine), fichier) != NULL){
        len = strlen(chaine);
        chaine[len - 1] = '\0';
        if(strcmp(chaine, pkg) != 0){
            strcat(chaine, "\n");
            fprintf(fichierTemp, "%s", chaine);
        }
           
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove("packages.txt");
    rename("tempPackages.txt", "packages.txt");
}

void uninstallPkg(char *pkg){
    DIR *dossier;
    struct dirent *entree;
    char cheminA[100], cheminB[100];
    char commande[100];

    //récupearation des fichier pour les maitre dans fichier
    strcpy(cheminA, "");
    strcpy(cheminB, "");
    strcpy(commande, "");

    strcat(cheminA, "packages\\");
    strcat(cheminA, pkg);
    strcat(cheminA, "\\src\\");

    strcat(cheminB, "packages\\");
    strcat(cheminB, pkg);
    strcat(cheminB, "\\include\\");

    dossier = opendir(cheminA);
    if(dossier == NULL){
        puts("Erreur d'ouverture du dossier");
        exit(1);
    }
    strcpy(commande, "del ");
    while((entree = readdir(dossier)) != NULL){
        if(entree->d_type == DT_REG){
            strcat(commande, entree->d_name);
            system(commande);

            deleteFromFile(entree->d_name);

            strcpy(commande, "del ");
        }
    }
    closedir(dossier);

    dossier = opendir(cheminB);
    if(dossier == NULL){
        puts("Erreur d'ouverture du dossier");
        exit(1);
    }

    strcpy(commande, "del include\\");
    while((entree = readdir(dossier)) != NULL){
        if(entree->d_type == DT_REG){
            strcat(commande, entree->d_name);
            system(commande);
            deleteFromFile(entree->d_name);
            strcpy(commande, "del include\\");
        }
    }
    closedir(dossier);

    delPackages(pkg);
}

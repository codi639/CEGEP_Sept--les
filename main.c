//
// Created by Jean-Lou Gilbertas on 11/02/2023.
//

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

void gotoxy(int colonne, int ligne);
int menu();
int genererNombreAleatoire(int min, int max);
void basePotence();
void potence(int etatPotence);
void devinerCapital(char pays[100], char capitaleADeviner[100], char capitale[50][100]);

void gotoxy(int colonne, int ligne){
    // Initialise les coordonnées.
    COORD coord = {colonne, ligne};

    // Place le curseur à l'endroit désiré à l'écran.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menu() {
    int continent;
    do {
        gotoxy(33, 2); printf("JEU DU PENDU\n");
        gotoxy(32, 3); printf("MENU PRINCIPAL\n");
        gotoxy(14, 8); printf("Africa\n");
        gotoxy(14, 9); printf("America\n");
        gotoxy(14, 10); printf("Asia\n");
        gotoxy(14, 11); printf("Europe\n");
        gotoxy(14, 12); printf("Oceania\n");
        gotoxy(14, 13); printf("Quitter\n");
        gotoxy(14, 15); printf("Veuillez choisir le continent : ");
        scanf("%d", &continent);
    } while (continent != 1 && continent != 2 && continent != 3 &&
             continent != 4 && continent != 5 && continent != 6);
    return continent;
}

int genererNombreAleatoire(int min, int max) {
    int nbrAleatoire;
    srand(clock());
    nbrAleatoire = (rand() % (max - min + 1)) + min;
    return nbrAleatoire;
}

void basePotence(){
    gotoxy(27, 2);printf("JEU DU PENDU");
    gotoxy(26, 4);printf("*************");
    for (int conteur = 12; conteur > 0; conteur--) {
        gotoxy(26, 5 + conteur);printf("*");
    }
    gotoxy(22, 18);printf("*********");
}

void potence(int etatPotence){
    system("cls");
    switch (etatPotence) {
        case 0:
            basePotence();
            break;
        case 1:
            basePotence();
            gotoxy(36, 5);printf("*****");
            gotoxy(36, 6);printf("*   *");
            gotoxy(36, 7);printf("*****");
            gotoxy(38, 8);printf("*");
            gotoxy(35, 9);printf("*******");
            gotoxy(35, 10);printf("*     *");
            gotoxy(35, 11);printf("*     *");
            break;
        case 2:
            basePotence();
            gotoxy(36, 5);printf("*****");
            gotoxy(36, 6);printf("*   *");
            gotoxy(36, 7);printf("*****");
            gotoxy(38, 8);printf("*");
            gotoxy(35, 9);printf("*******");
            gotoxy(35, 10);printf("*     *");
            gotoxy(35, 11);printf("*     *");
            gotoxy(35, 12);printf("*******");
            gotoxy(35, 13);printf(" *   * ");
            gotoxy(35, 14);printf(" *   * ");
            break;
    }
}

void devinerCapital(char pays[100], char capitaleADeviner[100], char capitale[50][100]){
    int compteur, indice = 0, tableauAleatoire[9], insertionAleatoire, nombreEssai = 0, choixUtilisateur;
    char listeCapitale[9][100];
    bool test = true;

    //potence(0);
    tableauAleatoire[0] = genererNombreAleatoire(0, 49);
    for (compteur = 1; compteur < 9; compteur++) {
        while (test == true){
            for (indice = 0; indice < compteur; indice++) {
                insertionAleatoire = genererNombreAleatoire(0, 49);
                if (tableauAleatoire[indice] == insertionAleatoire) {
                    test = true;
                } else {
                    test = false;
                }
            }
        }
        strcpy(listeCapitale[compteur], capitale[tableauAleatoire[indice]]);
    }

    insertionAleatoire = genererNombreAleatoire(0, 9);
    strcpy(listeCapitale[9], listeCapitale[insertionAleatoire]);
    strcpy(listeCapitale[insertionAleatoire], capitaleADeviner);
    for (compteur = 0; compteur < 9; compteur++) {
        gotoxy(80, 16 + compteur); printf("%d. %s\n", compteur + 1, listeCapitale[compteur]);
    }

    nombreEssai = 0;
    while (nombreEssai < 2){
        system("cls");
        potence(0);
        gotoxy(20, 21); printf("Quelle est la capitale du pays suivant ?%s : ", pays);
        gotoxy(20, 23); printf("Entrez votre choix : \n");
        scanf("%d", &choixUtilisateur);
        if (listeCapitale[choixUtilisateur] == capitaleADeviner) {
            gotoxy(20, 23); printf("Bravo, vous avez gagnez !\n");
            gotoxy(20, 24); printf("La capitale de ce pays est bien %s\n", capitaleADeviner);
        } else {
            nombreEssai++;
            potence(nombreEssai);
        }
        if (nombreEssai == 2) {
            gotoxy(20, 23); printf("Vous avez perdu !\n");
            gotoxy(20, 24); printf("La capitale de ce pays est %s\n", capitaleADeviner);
        }
    }
}

void main(){
    char paysPourTableau[50][100], capitalePourTableau[50][100], pays[100], capitaleADeviner[100], capitales[50][100];
    int continent, indexPays, indice, indexCapitale, compteur;
    FILE *fichierDePays, *fichierTestPays;

    indice = 0;
    //fichierTestPays = fopen("fichierPays.txt", "r");
    fichierDePays = fopen("fichierDePays.txt", "r");
    /*if (fichierTestPays == NULL) {
        printf("Erreur d'ouverture du fichier fichierPays.txt\n");
        exit(-1);
    } */if (fichierDePays == NULL) {
        printf("Erreur d'ouverture du fichier fichierDePays.txt");
        exit(-1);
    } else {
        while (fscanf(fichierDePays, "%s %s", paysPourTableau[indice], capitalePourTableau[indice]) != EOF) {
            indice++;
        }
    }
    
    do{
        continent = menu();
        switch (continent) {
            case 1:
                indexPays = genererNombreAleatoire(0, 9);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            case 2:
                indexPays = genererNombreAleatoire(10, 19);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            case 3:
                indexPays = genererNombreAleatoire(20, 29);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            case 4:
                indexPays = genererNombreAleatoire(30, 39);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            case 5:
                indexPays = genererNombreAleatoire(40, 49);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            default:
                printf("Veuillez saisir une un chiffre de la liste.\n");
        }
    } while (continent != 6);
    devinerCapital(pays, capitaleADeviner, capitales);
    printf("Hello World!\n");
    //basePotence();
    potence(1);
    //printf("Hello World!\n");
}
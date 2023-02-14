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
        gotoxy(14, 8); printf("1. Afrique\n");
        gotoxy(14, 9); printf("2. Amerique\n");
        gotoxy(14, 10); printf("3. Asie\n");
        gotoxy(14, 11); printf("4. Europe\n");
        gotoxy(14, 12); printf("5. Oceanie\n");
        gotoxy(14, 13); printf("6. Quitter\n");
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
    size_t compteur;
    size_t indice = 0;
    int tableauAleatoire[9];
    int insertionAleatoire;
    int nombreEssai = 0;
    int choixUtilisateur = 0;
    char listeCapitale[9][100];
    bool testEgaliteTableau = true;
    bool capitaleTrouvee = false;


    strcpy(listeCapitale[0], capitale[genererNombreAleatoire(0, 49)]);
    for (compteur = 1; compteur < 10; compteur++) {
        testEgaliteTableau = true;
        while (testEgaliteTableau){
            testEgaliteTableau = false;
            insertionAleatoire = genererNombreAleatoire(0, 49);
            for (indice = 0; indice < compteur; indice++) {
                if (strcmp(capitaleADeviner, capitale[insertionAleatoire]) == 0 || strcmp(listeCapitale[indice], capitale[insertionAleatoire]) == 0) {
                    testEgaliteTableau = true;
                    break;
                }
            }
        }
        strcpy(listeCapitale[compteur], capitale[insertionAleatoire]);
    }

    insertionAleatoire = genererNombreAleatoire(0, 8);
    //strcpy(listeCapitale[9], listeCapitale[insertionAleatoire]);
    strcpy(listeCapitale[insertionAleatoire], capitaleADeviner);


    nombreEssai = 0;
    while (nombreEssai < 2 && !capitaleTrouvee){
        system("cls");
        potence(nombreEssai);
        //printf("%s", listeCapitale[choixUtilisateur - 1]);
        //printf("%s", capitaleADeviner);
        for (compteur = 0; compteur < 9; compteur++) {
            gotoxy(80, 16 + compteur); printf("%d", compteur + 1);
            gotoxy(82, 16 + compteur); printf("%s   %d", listeCapitale[compteur], compteur);
        }
        gotoxy(20, 21); printf("Quelle est la capitale du pays suivant ?%s : ", pays);
        gotoxy(20, 23); printf("Entrez votre choix : \n");
        gotoxy(41, 23); scanf("%d", &choixUtilisateur);

        if (strcmp(capitaleADeviner, listeCapitale[choixUtilisateur - 1]) == 0) {
            gotoxy(20, 23); printf("Bravo, vous avez gagnez !\n");
            gotoxy(20, 24); printf("La capitale de ce pays est bien %s\n", capitaleADeviner);
            capitaleTrouvee = true;
            gotoxy(20, 25); printf("Appuyez sur une touche pour continuer...\n");
            scanf("%d", &choixUtilisateur);
            system("cls");
        } else {
            nombreEssai++;
        }
        if (nombreEssai == 2) {
            potence(2);
            gotoxy(20, 23); printf("Vous avez perdu !\n");
            gotoxy(20, 24); printf("La capitale de ce pays est %s\n", capitaleADeviner);
            gotoxy(20, 25); printf("Appuyez sur une touche pour continuer...\n");
            scanf("%d", &choixUtilisateur);
            system("cls");
        }
    }
}

void main(){
    system("cls");
    char paysPourTableau[50][100], capitalePourTableau[50][100], pays[100], capitaleADeviner[100], capitales[50][100];
    int continent, indexPays, indice, indexCapitale, compteur, test;
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
    /*for (test = 0; test < 50; test++) {
        printf("%s %s\n", paysPourTableau[test], capitalePourTableau[test]);
    }*/
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
                //gotoxy(30,24); printf("%s  %s %s  %s", paysPourTableau[indexPays], capitalePourTableau[indexPays], pays, capitaleADeviner);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            case 6:
                printf("Au revoir !\n");
                fclose(fichierDePays);
                return;
            default:
                printf("Veuillez saisir un chiffre de la liste.\n");
        } devinerCapital(pays, capitaleADeviner, capitales);
    } while (continent != 6);
}
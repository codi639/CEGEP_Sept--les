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

void gotoxy(int colonne, int ligne);
int menu();
int genererNombreAleatoire(int min, int max);
void basePotence();

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

void potence(int etatPotence, char listeCapital[]){

}

void main(){
    basePotence();
}
//
// Created by Jean-Lou Gilbertas on 11/02/2023.
//

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void gotoxy(int colonne, int ligne);
int menu();
int genererNombreAleatoire(int min, int max);
void basePotence();
void potence(int etatPotence);
void devinerCapitale(char pays[100], char capitaleADeviner[100], char capitale[50][100]);

//Fonction permettant de placer le curseur à l'endroit désiré à l'écran en choisissant les coordonnées.
void gotoxy(int colonne, int ligne){
    // Initialise les coordonnées.
    COORD coord = {colonne, ligne};

    // Place le curseur à l'endroit désiré à l'écran.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Fonction permettant d'afficher le menu principal.
int menu() {
    int continent = 0;
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
    } while (continent == 0);
    return continent;
}

//Fonction permettant de générer un nombre aléatoire dans un intervalle saisie.
int genererNombreAleatoire(int min, int max) {
    int nbrAleatoire;
    srand(clock());
    nbrAleatoire = (rand() % (max - min + 1)) + min;
    return nbrAleatoire;
}

//Fonction permettant d'afficher la base de la potence. (Uniquement le "bois" sans le bonhomme).
void basePotence(){
    gotoxy(27, 2);printf("JEU DU PENDU");
    gotoxy(26, 4);printf("*************");
    for (int conteur = 12; conteur > 0; conteur--) {
        gotoxy(26, 5 + conteur);printf("*");
    }
    gotoxy(22, 18);printf("*********");
}

//Fonction permettant d'afficher le bonhomme en fonction de l'état de la potence.
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

//Fonction permettant de jouer au jeu du pendu.
void devinerCapitale(char pays[100], char capitaleADeviner[100], char capitale[50][100]){
    //Déclaration des variables.
    size_t compteur;
    size_t indice = 0;
    int insertionAleatoire;
    int nombreEssai = 0;
    int choixUtilisateur = 0;
    char listeCapitale[9][100];
    bool testEgaliteTableau = true;
    bool capitaleTrouvee = false;

    //Vérification que la capitale à deviner n'est pas à la première place du tableau (afin d'éviter les doublons).
    while (testEgaliteTableau){
        testEgaliteTableau = false;
        insertionAleatoire = genererNombreAleatoire(0, 49);
        if (strcmp(capitaleADeviner, capitale[insertionAleatoire]) == 0) {
            testEgaliteTableau = true;
        }
    }
    //Remplissage du tableau avec les capitales.
    strcpy(listeCapitale[0], capitale[insertionAleatoire]);
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
    //Remplacement d'une capitale par la capitale à deviner.
    insertionAleatoire = genererNombreAleatoire(0, 8);
    strcpy(listeCapitale[insertionAleatoire], capitaleADeviner);

    //Début du jeu.
    nombreEssai = 0;
    while (nombreEssai < 2 && !capitaleTrouvee){
        system("cls");
        potence(nombreEssai);

        //Affichage des choix.
        for (compteur = 0; compteur < 9; compteur++) {
            gotoxy(80, 16 + compteur); printf("%d", compteur + 1);
            gotoxy(82, 16 + compteur); printf("%s", listeCapitale[compteur]);
        }
        //Demande de saisie du choix de l'utilisateur.
        gotoxy(20, 21); printf("Quelle est la capitale du pays suivant ?%s : ", pays);
        gotoxy(20, 23); printf("Entrez votre choix : \n");
        gotoxy(41, 23); scanf("%d", &choixUtilisateur);

        //Condition de victoire avec message de victoire.
        if (strcmp(capitaleADeviner, listeCapitale[choixUtilisateur - 1]) == 0) {
            gotoxy(20, 23); printf("Bravo, vous avez gagné !\n");
            gotoxy(20, 24); printf("La capitale de ce pays est bien %s\n", capitaleADeviner);
            capitaleTrouvee = true;
            gotoxy(20, 25); printf("Appuyez sur une touche pour continuer...\n");
            getch();
            system("cls");
        } else {
            //Incrémentation du nombre d'essai après chaque mauvaise réponse.
            nombreEssai++;
        }
        //Condition de défaite avec message de défaite.
        if (nombreEssai == 2) {
            potence(2);
            gotoxy(20, 23); printf("Vous avez perdu !\n");
            gotoxy(20, 24); printf("La capitale de ce pays est %s\n", capitaleADeviner);
            gotoxy(20, 25); printf("Appuyez sur une touche pour continuer...\n");
            getch();
            system("cls");
        }
    }
}

//Fonction permettant de choisir un pays et sa capitale au hasard.
void main(){
    setlocale(LC_ALL, "");


    system("cls");
    //Déclaration des variables
    char paysPourTableau[50][100];
    char capitalePourTableau[50][100];
    char pays[100];
    char capitaleADeviner[100];
    char capitales[50][100];
    int continent;
    int indexPays;
    int indice;
    int compteur;
    FILE *fichierDePays;

    //Ouverture du fichier de pays et remplissage des tableaux
    indice = 0;
    fichierDePays = fopen("fichierDePays.txt", "r");
    if (fichierDePays == NULL) {
        printf("Erreur d'ouverture du fichier fichierDePays.txt");
        exit(-1);
    } else {
        while (fscanf(fichierDePays, "%s %s", paysPourTableau[indice], capitalePourTableau[indice]) != EOF) {
            indice++;
        }
    }

    //Choix du pays et de sa capitale en fonction du continent choisi par le joueur
    do{
        continent = menu();
        switch (continent) {
            //Afrique
            case 1:
                indexPays = genererNombreAleatoire(0, 9);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            //Amérique
            case 2:
                indexPays = genererNombreAleatoire(10, 19);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            //Asie
            case 3:
                indexPays = genererNombreAleatoire(20, 29);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            //Europe
            case 4:
                indexPays = genererNombreAleatoire(30, 39);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            //Océanie
            case 5:
                indexPays = genererNombreAleatoire(40, 49);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                for (compteur = 0; compteur < 50; compteur++) {
                    strcpy(capitales[compteur], capitalePourTableau[compteur]);
                }
                break;
            //Sortie du jeux
            case 6:
                printf("Au revoir !\n");
                fclose(fichierDePays);
                return;
            default:
                printf("Veuillez saisir un chiffre de la liste.\n");
                break;
        } if (continent < 6) {
            devinerCapitale(pays, capitaleADeviner, capitales);
        } else{
            gotoxy(14, 15); printf("Veuillez choisir le continent :  \n");
        }
    } while (continent != 6);
}
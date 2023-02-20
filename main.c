/*************************************************
* Auteur : Jean-Lou Gilbertas                    *
* Date : 06 Février 2023                         *
* Intitulé : Jeu du Pendu                        *
* Description : Programme permettant de jouer à  *
* une version modifier du jeu du Pendu.          *
*************************************************/

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
    int continent; //Variable permettant de stocker le choix de l'utilisateur.
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
        scanf("%d", &continent); //Saisie du choix de l'utilisateur.
    } while (continent < 1 || continent > 6);
    return continent;
}

//Fonction permettant de générer un nombre aléatoire dans un intervalle saisie.
int genererNombreAleatoire(int min, int max) {
    int nbrAleatoire; //Variable permettant de stocker le nombre aléatoire.
    srand(clock()); //Initialisation de la fonction rand().
    nbrAleatoire = (rand() % (max - min + 1)) + min; //Génération du nombre aléatoire.
    return nbrAleatoire; //Retourne le nombre aléatoire.
}

//Fonction permettant d'afficher la base de la potence. (Uniquement le "bois" sans le bonhomme).
void basePotence(){
    gotoxy(27, 2); printf("JEU DU PENDU");
    gotoxy(26, 4); printf("*************");
    for (int conteur = 12; conteur > 0; conteur--) {
        gotoxy(26, 5 + conteur); printf("*");
    }
    gotoxy(22, 18); printf("*********");
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
            gotoxy(36, 5); printf("*****");
            gotoxy(36, 6); printf("*   *");
            gotoxy(36, 7); printf("*****");
            gotoxy(38, 8); printf("*");
            gotoxy(35, 9); printf("*******");
            gotoxy(35, 10); printf("*     *");
            gotoxy(35, 11); printf("*     *");
            gotoxy(35, 12); printf("*******");
            gotoxy(35, 13); printf(" *   * ");
            gotoxy(35, 14); printf(" *   * ");
            break;
    }
}

//Fonction permettant de jouer au jeu du pendu.
void devinerCapitale(char pays[100], char capitaleADeviner[100], char capitale[50][100]){
    //Déclaration des variables.
    size_t compteur; //Variable permettant de compter le nombre de lettre de la capitale à deviner.
    size_t indice = 0; //Variable permettant de parcourir le tableau.
    int insertionAleatoire; //Variable permettant de stocker le nombre aléatoire généré.
    int nombreEssai = 0; //Variable permettant de stocker le nombre d'essai.
    int choixUtilisateur = 0; //Variable permettant de stocker le choix de l'utilisateur.
    char listeCapitale[9][100]; //Tableau permettant de stocker la liste des capitales proposée.
    bool testEgaliteTableau = true; //Variable permettant de tester si la capitale à deviner est déjà dans le tableau.
    bool capitaleTrouvee = false; //Variable permettant de tester si la capitale à deviner a été trouvée.

    //Vérification que la capitale à deviner n'est pas à la première place du tableau (afin d'éviter les doublons).
    while (testEgaliteTableau){ //Tant que la capitale à deviner est déjà dans le tableau.
        testEgaliteTableau = false;
        insertionAleatoire = genererNombreAleatoire(0, 49); //Génération d'un nombre aléatoire.
        if (strcmp(capitaleADeviner, capitale[insertionAleatoire]) == 0) { //Si la capitale à deviner est à la première place du tableau.
            testEgaliteTableau = true;
        }
    }
    //Remplissage du tableau avec les capitales.
    strcpy(listeCapitale[0], capitale[insertionAleatoire]); //Remplissage de la première case du tableau avec la capitale à deviner.
    for (compteur = 1; compteur < 10; compteur++) { //Remplissage des autres cases du tableau.
        testEgaliteTableau = true;
        while (testEgaliteTableau){ //Tant que la capitale à deviner est déjà dans le tableau.
            testEgaliteTableau = false;
            insertionAleatoire = genererNombreAleatoire(0, 49); //Génération d'un nombre aléatoire.
            for (indice = 0; indice < compteur; indice++) { //Parcours du tableau.
                if (strcmp(capitaleADeviner, capitale[insertionAleatoire]) == 0 || strcmp(listeCapitale[indice], capitale[insertionAleatoire]) == 0) { //Si la capitale à deviner est déjà dans le tableau.
                    testEgaliteTableau = true;
                    break;
                }
            }
        }
        strcpy(listeCapitale[compteur], capitale[insertionAleatoire]); //Remplissage de la case du tableau avec la capitale.
    }
    //Remplacement d'une capitale par la capitale à deviner.
    insertionAleatoire = genererNombreAleatoire(0, 9);
    strcpy(listeCapitale[insertionAleatoire], capitaleADeviner); //Remplacement de la capitale par la capitale à deviner.

    //Début du jeu.
    nombreEssai = 0;
    while (nombreEssai < 2 && !capitaleTrouvee){ //Tant que le nombre d'essai est inférieur à 2 et que la capitale n'a pas été trouvée.
        system("cls");
        potence(nombreEssai); //Affichage de la potence en fonction de l'état du jeu (gagné, un échec ou deux échecs).

        //Affichage des choix.
        for (compteur = 0; compteur < 9; compteur++) { //Parcours du tableau.
            gotoxy(80, 10 + compteur); printf("%d", compteur + 1);
            gotoxy(82, 10 + compteur); printf("%s", listeCapitale[compteur]);
        }
        //Demande de saisie du choix de l'utilisateur.
        gotoxy(20, 21); printf("Quelle est la capitale du pays suivant ? %s", pays);
        gotoxy(20, 23); printf("Entrez votre choix : \n");
        gotoxy(41, 23); scanf("%d", &choixUtilisateur);

        //Condition de victoire avec message de victoire.
        if (strcmp(capitaleADeviner, listeCapitale[choixUtilisateur - 1]) == 0) { //Si la capitale à deviner est la même que la capitale proposée.
            gotoxy(20, 23); printf("Bravo, vous avez gagné !\n");
            gotoxy(20, 24); printf("La capitale de ce pays est bien %s\n", capitaleADeviner);
            capitaleTrouvee = true;
            gotoxy(20, 25); printf("Appuyez sur une touche pour continuer...\n");
            getch(); //Attente d'une touche.
            system("cls");
        } else {
            nombreEssai++; //Incrémentation du nombre d'essai après chaque mauvaise réponse.
        }
        //Condition de défaite avec message de défaite.
        if (nombreEssai == 2) { //Si le nombre d'essai est égal à 2.
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


    system("cls"); //Efface l'écran
    //Déclaration des variables
    char paysPourTableau[50][100]; //Tableau contenant les pays
    char capitalePourTableau[50][100]; //Tableau contenant les capitales
    char pays[100]; //Pays choisi au hasard
    char capitaleADeviner[100]; //Capitale du pays choisi au hasard
    int continent; //Continent choisi par le joueur
    int indexPays; //Index du pays choisi au hasard
    int indice;
    FILE *fichierDePays; //Fichier contenant les pays et leurs capitales

    //Ouverture du fichier de pays et remplissage des tableaux
    indice = 0;
    fichierDePays = fopen("fichierDePays.txt", "r"); //Ouverture du fichier
    if (fichierDePays == NULL) { //Vérification de l'ouverture du fichier
        printf("Erreur d'ouverture du fichier fichierDePays.txt");
        exit(-1);
    } else { //Remplissage des tableaux
        while (fscanf(fichierDePays, "%s %s", paysPourTableau[indice], capitalePourTableau[indice]) != EOF) {
            indice++;
        }
    }
    fclose(fichierDePays); //Fermeture du fichier
    //Choix du pays et de sa capitale en fonction du continent choisi par le joueur
    do{
        continent = menu(); //Affichage du menu et récupération du choix du joueur
        switch (continent) { //Choix du pays et de sa capitale en fonction du continent choisi par le joueur
            //Afrique
            case 1:
                indexPays = genererNombreAleatoire(0, 9); //Génération d'un nombre aléatoire entre 0 et 9
                strcpy(pays, paysPourTableau[indexPays]); //Copie du pays choisi au hasard dans le tableau pays
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]); //Copie de la capitale du pays choisi au hasard dans le tableau capitaleADeviner
                devinerCapitale(pays, capitaleADeviner, capitalePourTableau); //Appel de la fonction devinerCapitale afin de permettre au joueur de jouer
                break;
            //Amérique
            case 2:
                indexPays = genererNombreAleatoire(10, 19);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                devinerCapitale(pays, capitaleADeviner, capitalePourTableau);
                break;
            //Asie
            case 3:
                indexPays = genererNombreAleatoire(20, 29);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                devinerCapitale(pays, capitaleADeviner, capitalePourTableau);
                break;
            //Europe
            case 4:
                indexPays = genererNombreAleatoire(30, 39);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                devinerCapitale(pays, capitaleADeviner, capitalePourTableau);
                break;
            //Océanie
            case 5:
                indexPays = genererNombreAleatoire(40, 49);
                strcpy(pays, paysPourTableau[indexPays]);
                strcpy(capitaleADeviner, capitalePourTableau[indexPays]);
                devinerCapitale(pays, capitaleADeviner, capitalePourTableau);
                break;
            //Sortie du jeux
            case 6:
                return;
        }
    } while (continent != 6); //Tant que le joueur ne quitte pas le jeux (saisi 6)
}
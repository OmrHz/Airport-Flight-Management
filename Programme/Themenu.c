#include "themenu.h"
//==================================================================================================
void INTRO() // Introduction du programme
{

    SetConsoleTitle("TP1_ALSDD :Gestion des avions d'un Aeroport avec les listes simplement chainees");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    printf("____________________________________________________________________________________________________\n");
    printf("||        ===============================( BIENVENUE )==============================              ||\n");
    printf("||                        TP1_ALSDD   : Gestion des avions d'un Aeroport                          ||\n");
    printf("||                            Hamza Omar  ET Hassam Amar                                          ||\n");
    printf("||                                 Groupe  :   1CPI_G6                                            ||\n");
    printf("||                                 Module  :   ALSDD                                              ||\n");
    printf("||                                                                                                ||\n");
    printf("||            [ Ecole Nationale Superieure d'Informatique (ESI Ex INI) - Alger ]                  ||\n");
    printf("||        ==========================================================================              ||\n");
    printf("||________________________________________________________________________________________________||\n\n\n");
    printf("          Merci d'avoir choisir notre programme !\n\n");
    printf("=======================(Dans le MENU)============================\n");
    printf("||   la touche "" UP "" pour selectionner l'option precedente.     ||\n");
    printf("||   la touche "" DOWN "" pour selectionner l'option suivante.     ||\n");
    printf("||   Appuyez sur la touche "" ENTRER "" pour confirmer votre choix.||\n");
    printf("=================================================================");
    printf(" \n\n        Appuyer sur la touche ENTRER  pour continuer ! ");
    getch();
    system("cls");
}
// fonction qui efface les 19 lignes
void clear_19line()
{
    for (int i = 0; i < 19; i++)
    {
        printf("\033[1A"); // move cursor up one line
        printf("\033[K");  // clear the line
    }
}
// Fonction pour deplacer le curseur
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// fonction qui affiche le menu
void menu(char **options, int num_options, int *choix)
{
    int prev_choice = -1; // choix precedent de l'utilisateur
    int choice = 0;       // choix de l'utilisateur
    while (1)
    {
        clear_19line();                                  // effacer les 19 lignes
        printf("\033[44;37m");
        gotoxy(0, 0);                                    // positionner le curseur au debut de la ligne
        printf("\t\t M E N U   P R I N C I P A L : \n\n"); // saut de ligne
        printf("\033[0m");                               // reset text and background color to default
        for (int i = 0; i < num_options; i++)
        {
            if (i == choice)
            {                                   // si le choix de l'utilisateur est egal a l'option
                printf("\033[44;37m");          // set background to light blue, text to white
                printf("    %s  ", options[i]); // afficher l'option
                printf("\033[0m");              // reset text and background color to default
                printf("\n");                   // saut de ligne
            }
            else
            {
                printf("          %s          ", options[i]);
                printf("\n");
            }
            printf("\n");
        }
        if (prev_choice != choice)
        {
            gotoxy(0, num_options + 3);
        }
        prev_choice = choice;
        switch (getch())
        {
        case 72: // up arrow
            if (choice > 0)
            {
                choice--;
            }
            else
            {
                choice = num_options - 1; // wrap around to last option
            }
            break;
        case 80: // down arrow
            if (choice < num_options - 1)
            {
                choice++;
            }
            else
            {
                choice = 0; // wrap around to first option
            }
            break;
        case 13: // enter key
            system("cls");
            //  printf("\t Selected option: \n %s \n", options[choice]);
            *choix = choice + 1;
            return;
        }
    }
}
bool OUTRO()
{
    bool continuer = false;
    char choix;
    sleep(0.5);
    printf("\033[94m"); // couleur de fond bleu
    printf("Voulez-vous continuer ? (O/N) : ");
    choix = getche();
    printf("\n choix = %c",choix);
    if (choix == 'O' || choix == 'o')
    {
        continuer = true;
        system("cls");
    }
    else
    {
        continuer = false;
        system("cls");
        printf("\n \n \n \t Merci d'avoir utiliser notre programme !\n");
        printf("\t A bientot !\n");
        system("pause");
    }
    return continuer; 
}


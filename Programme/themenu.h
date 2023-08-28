#ifndef THE_MENU_H
#define THE_MENU_H

//bibliothèques utilisees dans le programme Themenu.c
#include <stdio.h>   //bibliothèque standard d'entree et sortie
#include <stdlib.h>  //bibliothèque standard
#include <stdbool.h> //bibliothèque pour les booleens
#include <string.h>  //bibliothèque pour les chaines de caractères
#include <time.h>    //bibliothèque pour les dates
#include <Windows.h> //bibliothèque pour les couleurs
#include <unistd.h>  //bibliothèque pour le sleep
#include <conio.h>
//prototypes des fonctions utilisees dans le programme Themenu.c

void INTRO();//fonction d'introduction
void clear_19line();//fonction de nettoyage de l'ecran
void gotoxy(int x, int y);//fonction de positionnement du curseur
void menu(char **options, int num_options, int *choix);//fonction du menu
bool OUTRO();//fonction de fin

#endif


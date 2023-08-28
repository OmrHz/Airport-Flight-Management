#ifndef LIBB_H
#define LIBB_HS

//bibliothèques utilisees dans le programme libb.c 
#include <stdio.h>   //bibliothèque standard d'entree et sortie
#include <stdlib.h>  //bibliothèque standard
#include <stdbool.h> //bibliothèque pour les booleens
#include <string.h>  //bibliothèque pour les chaines de caractères
#include <time.h>    //bibliothèque pour les dates
#include <unistd.h>  //bibliothèque pour le sleep
#include <conio.h>   //bibliothèque pour les touches
#include <ctype.h>  // pour les fonctions isdigit et isalpha


// Definition de la structure de donnees "Avion"
typedef struct Avion
{
    char code[50], etat;
    int cap, vols;
    int date[3];
    Avion *Next;
} Avion;  
// Definition du nouveau type PtrAvion (pointeur vers un avion)
typedef Avion *Ptrav;

//prototypes des fonctions utilisees dans le programme libb.c

   /*****************************************************************************************/
  /********************** Implementation de la machine abstraite LLCs **********************/
 /*****************************************************************************************/
/*****************************************************************************************/
// Procedure qui retourne un pointeur vers un Avion
void Allouer(Ptrav *p);//  On alloue dynamiquement la structure de controle avec un malloc.
// Procedure qui libere l'espace memoire du Avion pointe par p
void Liberer(Ptrav p);
// Procedure qui AFFECTE q dans le champ (Next) du Avion pointe par p
void Aff_adr(Ptrav p, Ptrav q);
// Procedure qui retourne le contenu du champ (Next) de Avion pointe par p
Ptrav Suivant(Ptrav p);
// Procedure qui AFFECTE le code dans le champ code de Avion pointe par p
void aff_code(Ptrav p, char *code);
// Procedure qui AFFECTE le cap dans le champ cap de Avion pointe par p
void aff_cap(Ptrav p, int cap);
// Procedure qui AFFECTE le vols dans le champ vols de Avion pointe par p
void aff_vols(Ptrav p, int vols);
// Procedure qui AFFECTE le etat dans le champ etat de Avion pointe par p
void aff_etat(Ptrav p, char etat);
// Procedure qui AFFECTE le date dans le champ date de Avion pointe par p
void aff_date(Ptrav p, int date[3]);
// fonction qui retourne le code du maillon pointe par p
char *code(Ptrav p);
// fonction qui retourne le cap du maillon pointe par p
int cap(Ptrav p);
// fonction qui retourne le vols du maillon pointe par p
int vols(Ptrav p);
// fonction qui retourne le etat du maillon pointe par p
char etat(Ptrav p);
// fonction qui retourne le date du maillon pointe par p
int *date(Ptrav p);
 /******************************************************************************************/
/******************************************************************************************/
 /****************************** Fonction auxiliaire ***************************************/
/*****************************************************************************************/ 
// Procedure qui vide le buffer
void ViderBuffer();
// Procedure qui efface la ligne courante
void clear_line() ;
//procedure qui permet de leberer l'espace memoire d'une LLC de type Avion
void LibererLLC (Ptrav p);
// Procedure qui genère une liste chainee
void GenLLC (Ptrav *L);
// Fonction qui retourne le nombre de maillons de la liste
int lenlist(Ptrav tete) ;
// Procedure qui affiche les informations d'une LLC de type Avion
void AffichLLC(Ptrav p,bool color);
// Procedure qui affiche l'heure actuelle du systeme
void printtime();
// Procedure qui remplit le champ code de Avion pointe par p
void Remp_code(Ptrav p, Ptrav pp);
// Procedure qui remplit le champ cap de Avion pointe par p
void Remp_cap(Ptrav p);
// Procedure qui remplit le champ vols de Avion pointe par p
void Remp_Etat(Ptrav p);
// Procedure qui remplit le champ etat de Avion pointe par p
void Remp_Date(Ptrav p);
// Procedure qui remplit le champ date de Avion pointe par p
void Remp_vols(Ptrav p);
// ajouter un maillon à la fin de la liste
void add_node(Ptrav p);
// affecter un maillon à un autre
void Aff_node(Ptrav m, Ptrav n); // m = new node , n = old node
// procedure qui donne la date de fabrication
void getdate (int *d,Ptrav p);
//================================================================================================
#endif

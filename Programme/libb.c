#include "libb.h"

/*****************************************************************************************************************************************/
/********************************************* Implémentation de la machine abstraite LLCs ***********************************************/
/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/

// Fonction qui retourne un pointeur vers un Avion
void Allouer(Ptrav *p) //  On alloue dynamiquement la structure de controle avec un malloc.
{
    *p = malloc(sizeof(Avion)); //  La taille à allouer est calculee automatiquement avec sizeof(Avion).
} //  L'ordinateur saura qu'il doit allouer l'espace necessaire au stockage de la structure Avion.
// Procedure qui detruit le maillon pointe par p
void Liberer(Ptrav p)
{
    free(p);
}
// Procedure qui AFFECTE q dans le champ (Next) du Avion pointe par p
void Aff_adr(Ptrav p, Ptrav q)
{
    p->Next = q; // (p->Next) est l'equivalent de (*p.Next)
}
// Fonction qui retourne le contenu du champ (Next) de Avion pointe par p
Ptrav Suivant(Ptrav p)
{
    return (p->Next);
}
// fonction qui AFFECTE le code dans le champ code de Avion pointe par p
void aff_code(Ptrav p, char *code)
{
    for (int i = 0; i <= strlen(code); i++)
    {
        p->code[i] = code[i];
    }
}
// fonction qui AFFECTE le cap dans le champ cap de Avion pointe par p
void aff_cap(Ptrav p, int cap)
{
    p->cap = cap;
}
// fonction qui AFFECTE le vols dans le champ vols de Avion pointe par p
void aff_vols(Ptrav p, int vols)
{
    p->vols = vols;
}
// fonction qui AFFECTE le etat dans le champ etat de Avion pointe par p
void aff_etat(Ptrav p, char etat)
{
    p->etat = etat;
}
// fonction qui AFFECTE le date dans le champ date de Avion pointe par p
void aff_date(Ptrav p, int date[3])
{
    p->date[0] = date[0];
    p->date[1] = date[1];
    p->date[2] = date[2];
}
// fonction qui retourne le code du maillon pointe par p
char *code(Ptrav p)
{
    return p->code;
}
// fonction qui retourne le cap du maillon pointe par p
int cap(Ptrav p)
{
    return p->cap;
}
// fonction qui retourne le vols du maillon pointe par p
int vols(Ptrav p)
{
    return p->vols;
}
// fonction qui retourne le etat du maillon pointe par p
char etat(Ptrav p)
{
    return p->etat;
}
// fonction qui retourne le date du maillon pointe par p
int *date(Ptrav p)
{
    return p->date;
}

/*****************************************************************************************************************************************/
/*****************************************************************************************************************************************/

// fonction qui vide le buffer
void ViderBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
// fonction qui efface la ligne courante
void clear_line()
{
    printf("\033[1A"); // move cursor up one line
    printf("\033[K");  // clear the line
    sleep(0.7);
}
// procedure qui permet de leberer l'espace memoire d'une LLC.....
void LibererLLC(Ptrav p)
{
    Ptrav q = NULL;
    while (p != NULL)
    {
        q = Suivant(p);
        Liberer(p);
        p = q;
    }
}
// fonction qui genère une liste chainee
void GenLLC(Ptrav *L)
{
    int nbav = 0;
    Ptrav p = NULL, q = NULL;
    printf("\n--->Combien d'avions souhaitez-vous stocker ses infos : ");
    scanf("%d", &nbav);
    Allouer(&p);
    strcpy(p->code, "");
    *L = p;
    q = p;
    for (int i = 1; i < nbav; i++)
    {
        Allouer(&p);
        strcpy(p->code, "");
        Aff_adr(q, p);
        q = p;
    }
    Aff_adr(p, NULL);
}

// Procedure qui affiche les informations d'une LLC de type Avion
void AffichLLC(Ptrav p, bool color)
{
    int i = 1;
    if (p == NULL)
    {
        printf("Il n'y a pas d'avions Disponible \n");
    }
    else
    {
        while (p)
        {
            printf("\n L'Avion N %d : \n", (i + 1));
            printf(" Code ['%s'] \n", p->code);
            if (color == true)
            {
                printf("\033[42;37m"); // couleur de fond rouge
                printf("Capacite de Stockage : %d\n", p->cap);
                printf("\033[0m");  // couleur de fond noir
                printf("\033[94m"); // couleur de fond bleu
            }
            else
            {
                printf(" Capacite de Stockage : %d \n ", p->cap);
            }
            printf(" Etats  ['%c'] \n ", p->etat);
            printf(" Date de fabrication :  %d / %d / %d \n", p->date[2], p->date[1], p->date[0]);
            printf(" Nombre de Vols : %d \n ", p->vols);
            p = Suivant(p);
            i++;
        }
    }
}
void printtime() // fonction qui affiche l'heure actuelle
{
    time_t t; // not a primitive datatype
    time(&t);
    printf("\n current time : %s", ctime(&t));
}
// Procedure qui remplit le champ code d' Avion pointe par p
void Remp_code(Ptrav p, Ptrav pp)
{
    char tmp[50] = "";
A:
    printf("Code :");
    scanf("%s", tmp);
    int b = 0;
    Ptrav q = pp;
    while (q != NULL)
    {
        b = strcmp(q->code, tmp);
        if (b == 0)
        {
            printf("\033[41;37m"); // couleur de fond rouge
            printf(" CODE Deja utilise ('Essaie un autre') \n");
            sleep(1.5);
            printf("\033[0m");  // couleur de fond PAR DEFAUT
            printf("\033[94m"); // couleur de fond bleu
            clear_line();
            clear_line();
            goto A;
        }
        q = Suivant(q);
    }
    strcpy(p->code, tmp);
    Liberer(q);
    clear_line();
}
// Procedure qui remplit le champ cap d' Avion pointe par p
void Remp_cap(Ptrav p)
{
    int tmp = 0;
A:
    // tmp = rand() % (1001 - 1) + 1;
    printf("Capacite de stockage [1..1000] :  ");
    ViderBuffer();
    scanf("%d", &tmp);
    if (tmp > 0 && tmp < 1001)
    {
        aff_cap(p, tmp);
        clear_line();
    }
    else
    {

        printf("\033[41;37m"); // couleur de fond rouge
        printf(" Invalid input. Please enter a value within the specified range. \n");
        sleep(1.5);
        printf("\033[0m");  // couleur de fond PAR DEFAUT
        printf("\033[94m"); // couleur de fond bleu
        clear_line();
        clear_line();
        goto A;
    }
}
// Procedure qui remplit le champ etat d' Avion pointe par p
void Remp_Etat(Ptrav p)
{
    char E = 'A';
A:
    printf("Etat ('D' pour decolle, 'A' pour atterri, 'M' pour maintenance) : ");
    ViderBuffer();
    scanf("%c", &E);
    if (E == 'M' || E == 'D' || E == 'A')
    {
        aff_etat(p, E);
        clear_line();
    }
    else
    {
        printf("\033[41;37m"); // couleur de fond rouge
        printf("Incorrect input. Please enter a valid option Or Try a capital Letter !!\n");
        sleep(2);
        printf("\033[0m");  // couleur de fond PAR DEFAUT
        printf("\033[94m"); // couleur de fond bleu
        clear_line();
        clear_line();
        goto A;
    }
}
// Procedure qui remplit le champ date de Avion pointe par p
void Remp_Date(Ptrav p)
{
    int tmp[3] = {0, 0, 0};
    printf("Date de fabrication :\n");
A:
    // tmp[0] = rand() % (31 - 1) + 1;
    printf("Day [1..31] : ");
    ViderBuffer();
    scanf(" %d", &tmp[0]);
    if (tmp[0] > 0 && tmp[0] < 32)
    {
        clear_line();
    }
    else
    {
        printf("\033[41;37m"); // couleur de fond rouge
        printf(" Invalid input. Please enter a value within the specified range. \n");
        sleep(1.5);
        printf("\033[0m");  // couleur de fond PAR DEFAUT
        printf("\033[94m"); // couleur de fond bleu
        clear_line();
        clear_line();
        goto A;
    }
B:
    //  tmp[1] = rand() % (12 - 1) + 1;
    printf("Month [1..12] : ");
    ViderBuffer();
    scanf(" %d", &tmp[1]);
    if (tmp[1] > 0 && tmp[1] < 13)
    {
        clear_line();
    }
    else
    {
        printf("\033[41;37m"); // couleur de fond rouge
        printf(" Invalid input. Please enter a value within the specified range. \n");
        sleep(1.5);
        printf("\033[0m");  // couleur de fond PAR DEFAUT
        printf("\033[94m"); // couleur de fond bleu
        clear_line();
        clear_line();
        tmp[1] = 0;
        goto B;
    }
C:
    // tmp[2] = rand() % (2023 - 1903) + 1903;
    printf("Year [1903..2023] : ");
    ViderBuffer();
    scanf(" %d", &tmp[2]);
    if (tmp[2] > 1902 && tmp[2] < 2024)
    {
        clear_line();
    }
    else
    {
        printf("\033[41;37m"); // couleur de fond rouge
        printf(" Invalid input. Please enter a value within the specified range. \n");
        sleep(1.5);
        printf("\033[0m");  // couleur de fond PAR DEFAUT
        printf("\033[94m"); // couleur de fond bleu
        clear_line();
        clear_line();
        tmp[2] = 0;
        goto C;
    }
    clear_line();
    aff_date(p, tmp);
}
// Procedure qui remplit le champ vols d' Avion pointe par p
void Remp_vols(Ptrav p)
{
    int tmp = 0;
A:
    // tmp = rand() % (10001 - 1) + 1;
    printf("Nombre de vols [1..10000] : ");
    ViderBuffer();
    scanf(" %d", &tmp);
    if (tmp > 0 && tmp < 10001)
    {
        aff_vols(p, tmp);
        clear_line();
    }
    else
    {
        printf("\033[41;37m"); // couleur de fond rouge
        printf(" Invalid input. Please enter a value within the specified range. \n");
        sleep(1.5);
        printf("\033[0m");  // couleur de fond PAR DEFAUT
        printf("\033[94m"); // couleur de fond bleu
        clear_line();
        clear_line();
        tmp = 0;
        goto A;
    }
}
// ajouter un maillon à la fin de la liste
void add_node(Ptrav p)
{
    Ptrav q = NULL;
    Allouer(&q);
    Aff_adr(q, NULL);
    Aff_adr(p, q);
}
// affecter un maillon à un autre
void Aff_node(Ptrav m, Ptrav n) // m = new node , n = old node
{
    strcpy(m->code, n->code);   // code
    for (int i = 0; i < 3; i++) // date
    {
        m->date[i] = n->date[i];
    }
    m->etat = n->etat; // etat
    m->cap = n->cap;   // cap
    m->vols = n->vols; // vols
}
// procedure qui donne la date de fabrication
void getdate(int *d, Ptrav p)
{
    for (int i = 0; i < 3; i++)
    {
        d[i] = p->date[i];
    }
}
// ==================================================================

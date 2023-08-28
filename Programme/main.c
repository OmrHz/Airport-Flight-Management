#include "libb.h"    //biblioth�que pour les fonctions
#include "theMenu.h" //biblioth�que pour le menu
// fonction qui retourne le nombre max de vols
int maxvol(Ptrav p)
{
    int mx = 0;
    while(p)
    {
        if (mx < p->vols)
        {
            mx = p->vols;
        }
        p = Suivant(p);
    }
    return mx;
}

// fonction qui retourne le nombre min de vols
int minvol(Ptrav p)
{
    int mx = 10001;
    while(p)
    {
        if (mx > p->vols)
        {
            mx = p->vols;
        }
        p = Suivant(p);
    }
    return mx;
}

// fonction qui retourne l'age de l'avion
int Age(Ptrav p)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;
    int age = year - p->date[2];
    if (month < p->date[1])
    {
        age--;
    }
    else if (month == p->date[1])
    {
        if (day < p->date[0])
        {
            age--;
        }
    }
    return age;
}

// fonction qui affiche les avions qui ont le nombre ( MAX / min )  de vols
void valprint(Ptrav p, int v,char message[10])
{
    printf("\033[94m"); // couleur bleu
    printf("===>> Les Avions qui ont assures le %s de vols et ages de moins de 10 ans sont:\n",message);
    int cpt = 1;
    while (p)
    {
        if (p->vols == v && Age(p) < 10)
        {
            printf(" L'Avion N %d : \n", cpt);
            printf("\t Code ['%s']  \n", p->code);
            printf("\t Cap : %d \n ", p->cap);
            printf("\t Etats  ['%c'] \n ", p->etat);
            printf("\t Date de fabrication : %d / %d / %d \n", p->date[2], p->date[1], p->date[0]);
            printf("\t Vols : %d \n ", p->vols);
            printf("\t Age : %d \n ", Age(p));
            printf("______________________________________________________________________________________\n");
            cpt++;
        }
        p = Suivant(p);
    }
}

// fonction qui calcule le nombre d avions decollee et le nombre de celle atterit.
void etatAV(Ptrav p)
{
    int cptA = 0, cptD = 0;
    while (p)
    {
        if (p->etat == 'A')
        {
            cptA++;
        }
        else if (p->etat == 'D')
        {
            cptD++;
        }
        p = Suivant(p);
    }
    printf("\033[94m"); // couleur de fond bleu
    printtime();
    printf("===>Le nombre d'Avions Atterit ['A'] : %d\n", cptA);
    printf("===>Le nombre d'Avions Decolle ['D'] : %d\n", cptD);
}

// scinder la liste en 3 listes selon l'etat de l'avion (D,A,M)
void Scindlist(Ptrav tete)
{
    Ptrav p = tete;
    Ptrav tD = NULL, tA = NULL, tM = NULL, A = NULL, D = NULL, M = NULL;
    //   A,D,M sont les tetes       tA,tD,tM   les pointeur de parcour
    while (p)
    {
        char state = p->etat;
        switch (state)
        {

        case 'D':
        {
            if (D == NULL)
            {
                Allouer(&D);
                Aff_adr(D, NULL);
                tD = D;
                Aff_node(tD, p);
            }
            else
            {
                add_node(tD);
                tD = Suivant(tD);
                Aff_node(tD, p);
            }
        }
        break;

        case 'A':
        {
            if (A == NULL)
            {
                Allouer(&A);
                Aff_adr(A, NULL);
                tA = A;
                Aff_node(tA, p);
            }
            else
            {
                add_node(tA);
                tA = Suivant(tA);
                Aff_node(tA, p);
            }
        }
        break;

        case 'M':
        {
            if (M == NULL)
            {
                Allouer(&M);
                Aff_adr(M, NULL);
                tM = M;
                Aff_node(tM, p);
            }
            else
            {
                add_node(tM);
                tM = Suivant(tM);
                Aff_node(tM, p);
            }
        }
        break;
        }
        p = Suivant(p);
    }
    printf("\033[42;37m");  // couleur de fond bleu
    printf("\n==>La Liste des avions Decolle :\n");
    printf("\033[0m");  // couleur de fond noir
    AffichLLC(D, false);
    printf("______________________________________________________________________________________\n");
    printf("\033[43;37m");
    printf("\n==>Liste des avions Atterit :\n");
    printf("\033[0m");
    AffichLLC(A, false);
    printf("______________________________________________________________________________________\n");
    printf("\033[41;37m");
    printf("\n==>Liste des avions en Maintenance :\n");
    printf("\033[0m");
    AffichLLC(M, false);
    printf("______________________________________________________________________________________\n");

}

// give 2 adresses and switch conten
void swapnode(Ptrav m, Ptrav n) // m et n sont les adresses des avions a echanger
{
    ///////////// code ///////////////////
    char tmp1[100] = {0};
    strcpy(tmp1, n->code);
    strcpy(n->code, m->code);
    strcpy(m->code, tmp1);
    //////////// date //////////////////
    int tmp3[3] = {0};
    getdate(tmp3, n);
    aff_date(n, m->date);
    aff_date(m, tmp3);
    ///////////// Etat ///////////////////
    char tmp = etat(n);
    aff_etat(n, etat(m));
    aff_etat(m, tmp);
    //////////// cap  //////////////////
    int tmpi = cap(n);
    aff_cap(n, cap(m));
    aff_cap(m, tmpi);
    //////////// vols //////////////////
    tmpi = vols(n);
    aff_vols(n, vols(m));
    aff_vols(m, tmpi);
}

// fonction qui  trier la liste des avions par ordre croissant des capacites de stockage
void selectionSort(Ptrav p)
{
    // on choisit le tri par selection
    Ptrav min_idx, test;
    Ptrav lastbd = p;

    // One by one move boundary of unsorted subarray
    while (Suivant(lastbd) != NULL)
    {
        // Find the minimum element in unsorted array
        min_idx = lastbd;
        test = Suivant(lastbd);
        while (test != NULL)
        {
            if (cap(test) < cap(min_idx))
            {
                min_idx = test;
            }
            test = Suivant(test);
        }

        // Swap the found minimum element with the first element
        if (min_idx != lastbd)
        {
            swapnode(min_idx, lastbd);
        }
        lastbd = Suivant(lastbd);
    }
    printf("\033[94m"); // couleur de fond bleu
    printf("\nLa liste des avions trier par ordre croissant des capacites de stockage : \n");
    AffichLLC(p, true);
}
// Procedure qui remplire les informations d'un avion
void LLCavion(Ptrav *t)
{
    printf("  ===========================================================\n");
    printf("\033[44;30m"); // set background to red, text to white
    printf("\t W E L C O M E   T O   E S I   A E R O P O R T \n");
    printf("\033[0m");  // reset to default
    printf("\033[94m"); // couleur de fond bleu
    printf("  ===========================================================\n");
    GenLLC(t);
    Ptrav p = *t;
    Ptrav pp = *t;
    int i=1;
    while(p)
    {
        printf("Les informations de l'Avion N: %d \n", i);
        // =================Code==================//
        Remp_code(p, pp);
        // =================Cap==================//
        Remp_cap(p);
        // =================Etat==================//
        Remp_Etat(p);
        // =================Date==================//
        Remp_Date(p);
        // =================Vols==================//
        Remp_vols(p);
        // add_node(p);
        clear_line();
        p = Suivant(p);
        i++;
    }
    Liberer(p);
}
// Fonction qui Verifier si un avion AV est dans l'aeroport
void CheckAV(Ptrav p)
{
    Ptrav q = NULL;
    q = p;
    char C[50] = "", answer = 'Y';
    while (answer == 'Y' || answer == 'y')
    {
        system("cls");
        printf("\033[94m"); // couleur de fond bleu
        printf("\nSaisissez le code que vous voulez verifier : ");
        scanf("%s", C);
        bool found = false;
        int b = 0;
        while (q)
        {
            b = strcmp(q->code, C);
            if (b == 0)
            {
                printf("L'avion avec le code [%s] est dans l'aeroport  \n", C);
                found = true;
                break;
            }
            q = Suivant(q);
        }
        if (!found)
        {
            printf("L'avion avec le code [%s] n'est pas dans l'aeroport : -1  \n", C);
        }
        printf("\nVoulez-vous essayer un autre code (Y/N) ? : ");
        answer = getche();
    }
}

// Procedure qui permet de supprimer les avions qui ont plus de 20 ans et qui sont en maintenance
void del_all_old(Ptrav *avi)
{
    char chois;
    Ptrav navi = NULL, tnavi = NULL,avi1 = *avi;
    while (avi1 != NULL)
    {
        if ((Age(avi1) <= 20) || (etat(avi1) != 'M'))
        {
            if (navi == NULL)
            {
                Allouer(&navi);
                tnavi = navi;
                Aff_adr(navi, NULL);
                Aff_node(navi, avi1);
            }
            else
            {
                add_node(navi);
                navi = Suivant(navi);
                Aff_node(navi, avi1);
            }
        }
        avi1 = Suivant(avi1);
    }
    printf("\033[94m"); // couleur de fond bleu
    printf("\nListe des avions restant apres suppression : \n");
    AffichLLC(tnavi, false);
    printf("\n voulez vous appliquer les changement ? (O/N)\n");
    chois=getche();
    if ((chois =='O') || (chois == 'o'))
    {
        LibererLLC(*avi);
        *avi=tnavi;
    }

}
//=====================================================================
int main()
{
    int choix = 0;
    char *options[] = {" Verifier une avion si elle est en aeroport", "Supression des avions agees plus de 20 ans en maitenance.", "Trier la liste des avions par ordre croissant des capacites de stockage", "Le nombre d avions decollee et le nombre de celle atterit. ", "Afficher les avions qui ont assuree le nombre maximal de vols et agees de moins de 10 ans.", "Afficher les avions qui ont assuree le nombre minimal de vols et agees de moins de 10 ans.", "decomposer la liste des avions en trois : atterit , decollee , en maintenance .","Quitter"};
    int num_options = sizeof(options) / sizeof(char *); // number of options
    INTRO();                                            // afficher l'introduction
    Ptrav av = NULL;
   LLCavion(&av);
MENU:
    menu(options, num_options, &choix); // afficher le menu
    switch (choix)
    {
    case 1: // Verifier une avion si elle est en aeroport
        CheckAV(av);
        system("cls");
        goto MENU;
        break;
    case 2: // Supression des avions agees plus de 20 ans en maitenance.
        del_all_old(&av);
        printf(" \n\n        Appuyer sur la touche ENTRER  pour continuer ! ");
        getch();
        system("cls");
        goto MENU;
        break;
    case 3: // Trier la liste des avions par ordre croissant des capacites de stockage
        selectionSort(av);
        printf(" \n\n        Appuyer sur la touche ENTRER  pour continuer ! ");
        getch();
        system("cls");
        goto MENU;
        break;
    case 4: // Le nombre d avions decollee et le nombre de celle atterit.
        etatAV(av);
        printf(" \n\n        Appuyer sur la touche ENTRER  pour continuer ! ");
        getch();
        system("cls");
        goto MENU;
        break;
    case 5: // Afficher les avions qui ont assuree le nombre maximal de vols et agees de moins de 10 ans.
        valprint(av, maxvol(av),"maximum");
        printf(" \n\n        Appuyer sur la touche ENTRER  pour continuer ! ");
        getch();
        system("cls");
        goto MENU;
        break;
    case 6: // Afficher les avions qui ont assuree le nombre minimal de vols et agees de moins de 10 ans.
        valprint(av, minvol(av),"minimum");
        printf(" \n\n        Appuyer sur la touche ENTRER  pour continuer ! ");
        getch();
        system("cls");
        goto MENU;
        break;
    case 7: // Decomposer la liste des avions en trois : Atterit , Decollee et en Maintenance .
        Scindlist(av);
        printf(" \n\n        Appuyer sur la touche ENTRER  pour continuer ! ");
        getch();
        system("cls");
        goto MENU;
        break;
    case 8:      // Quitter
        if (!OUTRO())
        {
            exit(0);// arreter le programme
        }
        else
        {
            goto MENU;
        }
        break;
    }
    LibererLLC(av);// liberer la memoire allouee pour la liste des avions
    return 0;
}

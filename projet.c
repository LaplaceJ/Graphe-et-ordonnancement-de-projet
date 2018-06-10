
#include "projet.h"
#define TAILLEMAX 256

void tri_insertion(int  ** tabNiv , struct Noeud * tabSommet , int  ns) {

    // tmp, entier tampon
    int tmp , j ;

    // cpnm, tampon d'une structure
    int  cmp ;

    for (int i = 2 ; i <=  ns  ; ++i) {
        // On commence à l'indice 2 car les deux premières tâches sont dèja triées par niveau croissant

        //On garde en mémoire l'indice du niveau courant
        tmp = (*tabNiv)[i] ;

        //On garde en mémoire le niveau courant
        cmp = tabSommet[(*tabNiv)[i]-1 ].niveau ;

        j = i ;
        while(j > 0 && tabSommet[(*tabNiv)[j-1]-1].niveau > cmp) {
            //Si on rencontre un niveau plus faible décale les niveaux pour créer un trou

            (*tabNiv)[j]  =  (*tabNiv)[j-1] ;
            j -- ;
        }

        //On insère tmp dans le trou
        (*tabNiv)[j] = tmp ;
    }
}

void bellman(int  * tabNiv , struct Noeud ** tabSommet , int  ns){

    //Bellman de niveau 0 à niveau p pour calculer la date au plus tôt
    for (int i = 0 ; i < ns ; ++i) {
        for (int j = 0; j < (*tabSommet)[tabNiv[i]-1].nbsucc; ++j) {
            if ((*tabSommet)[(*tabSommet)[tabNiv[i]-1].succ[j]].dPlusTot  <  ((*tabSommet)[tabNiv[i]-1]).dPlusTot  + ((*tabSommet)[tabNiv[i]-1]).poids  ){
                (*tabSommet)[(*tabSommet)[tabNiv[i]-1].succ[j]].dPlusTot =  ((*tabSommet)[tabNiv[i]-1]).dPlusTot  + ((*tabSommet)[tabNiv[i]-1]).poids ;
            }

        }

    }
    //On modifie la date au plus tard de p
    (*tabSommet)[ns].dPlusTard=(*tabSommet)[ns].dPlusTot;

    //Bellman de niveau p à niveau 0 pour calculer la date au plus tard
    for (int i = ns ; i > 0 ; --i) {
        for (int j = 0; j < (*tabSommet)[tabNiv[i]-1].nbpred; ++j) {
            if ( ((*tabSommet)[(*tabSommet)[tabNiv[i]-1].pred[j]].dPlusTard) == - 1
                 || ((*tabSommet)[(*tabSommet)[tabNiv[i]-1].pred[j]].dPlusTard > ((*tabSommet)[tabNiv[i]-1].dPlusTard  - (*tabSommet)[(*tabSommet)[tabNiv[i]-1].pred[j]].poids))){

                (*tabSommet)[(*tabSommet)[tabNiv[i]-1].pred[j]].dPlusTard = ((*tabSommet)[tabNiv[i]-1].dPlusTard  - (*tabSommet)[(*tabSommet)[tabNiv[i]-1].pred[j]].poids);
            }
        }
    }


}

void clear_noeud(struct  Noeud  * n , int ns ,  int * niv  ){
    //Destructeur de l'objet struct  Noeud
    for (int i = 0 ; i <=  ns ; ++i) {
        free(n[i].succ) ;
        free(n[i].pred) ;
    }

    free(n) ;
    free(niv) ;

}

void init_pred_p(struct Noeud ** tabSommet , int  ns){

    for (int i = 0; i < ns  ; ++i) {

        //Si le sommet n'a pas de successeur
        if((*tabSommet)[i].nbsucc == 0 ){
            //p devient un successeur de i
            (*tabSommet)[i].nbsucc = 1;
            (*tabSommet)[i].succ[0]= ns;

            //i devient un prédecesseur de p
            (*tabSommet)[ns].nbpred = (*tabSommet)[ns].nbpred + 1 ;
            (*tabSommet)[ns].pred = (int * ) realloc((*tabSommet)[ns].pred, sizeof(int  ) * ((*tabSommet)[ns].nbpred)   ) ;
            (*tabSommet)[ns].pred[(*tabSommet)[ns].nbpred-1]=i;

            //Mise à jours du niveau de p
            if((*tabSommet)[ns].niveau < (*tabSommet)[i].niveau+1){
                (*tabSommet)[ns].niveau=(*tabSommet)[i].niveau +1;

            }
        }
    }
}

void init_noeud(char* nFichier,struct Noeud** tabSommet, int** tabNiveau, int *ns){

    int a,b;//Nom des sommets
    double poids ;
    char c ;//caractère informatif
    char chaine[TAILLEMAX];
    FILE* fichier;

    //Ouverture du fichier
    fichier = fopen(nFichier, "r+");

    //Si l'ouverture aboutit
    if (fichier != NULL) {

        //Tant que le fichier n'a pas été lu en entier
        while (fgets(chaine, TAILLEMAX, fichier) != NULL) {

            //Réception de l'indicateur
            sscanf(chaine, "%c", &c);

            //p = nombre de sommets à initialiser
            if (c == 'p') {
                //ns = nombre de sommets
                sscanf(chaine, "%c %d", &c, ns);

                //Initialisation des tableaux
                *tabSommet = (struct Noeud *) malloc((*ns + 1) * sizeof(struct Noeud));
                *tabNiveau = (int *) malloc((*ns + 1) * sizeof(int));

                //Initialisation partiel du sommet p
                (*tabSommet)[*ns].poids = 0; // Poids = la durée de la tache correspondante
                (*tabSommet)[*ns].niveau = 0;
                (*tabSommet)[*ns].dPlusTot = 0;
                (*tabSommet)[*ns].dPlusTard = -1;
                (*tabSommet)[*ns].nbsucc = 0;
                (*tabSommet)[*ns].nbpred = 0;

                //Initialisation du tableau de predécesseur
                (*tabSommet)[*ns].pred = (int *) malloc(sizeof(int));

                //Ce vecteur n'est jamais utilisé pour p mais permet une destruction simplifier.
                (*tabSommet)[*ns].succ = (int *) malloc(sizeof(int));


            }
            //a = arc à initialiser
            else if (c == 'a') {

                //a = sommet initial
                //b = sommet final
                sscanf(chaine, "%c %d %d", &c, &a, &b);

                //On ajuste la différence entre l'arithmétique "humaine" et du c
                a = a - 1;
                b = b - 1;

                //Ajout d'un succésseur à a
                (*tabSommet)[a].nbsucc = (*tabSommet)[a].nbsucc + 1;
                (*tabSommet)[a].succ = (int *) realloc((*tabSommet)[a].succ, (*tabSommet)[a].nbsucc * sizeof(int));
                (*tabSommet)[a].succ[((*tabSommet)[a]).nbsucc - 1] = b;

                //Ajout d'un predécesseur à b
                (*tabSommet)[b].nbpred = (*tabSommet)[b].nbpred + 1;
                (*tabSommet)[b].pred = (int *) realloc((*tabSommet)[b].pred, (*tabSommet)[b].nbpred * sizeof(int));
                (*tabSommet)[b].pred[(*tabSommet)[b].nbpred - 1] = a;

                //Mise à jour du niveau de b.On compare le niveau actuel de b et celui de son predecesseur +1,
                //Si le niveau potentiel est plus grand alors on écrase l'ancien.
                if ((*tabSommet)[b].niveau < (*tabSommet)[a].niveau + 1) {
                    (*tabSommet)[b].niveau = (*tabSommet)[a].niveau + 1;

                }

            }
            //Noeuds à initialiser
            else if (c == 'v') {
                sscanf(chaine, "%c %d %lf", &c, &a, &poids);


                //On ajuste la différence entre l'arithmétique "humaine" et du c
                a = a - 1;

                (*tabSommet)[a].poids = poids;
                (*tabSommet)[a].niveau = 0;
                (*tabSommet)[a].dPlusTot = 0;
                (*tabSommet)[a].dPlusTard = -1;
                (*tabSommet)[a].nbsucc = 0;
                (*tabSommet)[a].nbpred = 0;

                (*tabSommet)[a].succ = (int *) malloc(sizeof(int));
                (*tabSommet)[a].pred = (int *) malloc(sizeof(int));
            }

        }
        // si c == 'c' commentaire
        //Initialisation du tableau niveau
        for (int i = 0; i < *ns + 1; i++) {

            (*tabNiveau)[i] = i + 1;
        }

        //Fermeture du fichier
        fclose(fichier);
    }
        //Si non nous renvoyons une erreur.
    else{
        printf("\nEchec chargement \n");
    }

}

void print_res(struct Noeud * tabSommet, int length){
    FILE * fp;
    int * tCri = (int * ) malloc(sizeof(int));
    int nbtCri =0;
    double marge;

    fp = fopen ("results.txt", "w+");

    for (int i = 0; i <= length ; ++i) {
        marge=tabSommet[i].dPlusTard - tabSommet[i].dPlusTot ;
        fprintf(fp,"sommet %d :"  , i + 1  ) ;
        fprintf(fp," Date au plus tot = %.2lf , Date au plus tard = %.2lf , Marge : %.2lf  \n " ,tabSommet[i].dPlusTot , tabSommet[i].dPlusTard , marge ) ;
        if (marge==0){
            nbtCri=nbtCri +1;
            tCri=(int * ) realloc(tCri,sizeof(int)*nbtCri);
            tCri[nbtCri-1]= i+1;
        }
    }
    fprintf(fp,"Tâches critiques : \n\n");
    for (int i = 0; i < nbtCri ; ++i) {
        fprintf(fp,"%d, ",tCri[i]);

    }
    fprintf(fp,"\n\n Durée minimale : %.2lf",tabSommet[length].dPlusTard);

    free(tCri);
    fclose(fp);

}



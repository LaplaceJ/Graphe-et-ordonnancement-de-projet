#include <stdio.h>
#include "projet.h"



int main(){
    int ns ;
    struct Noeud * tabSommet ;
    int * tabNiveau  ;
    char nomFichier[256] ;

    puts("Entrez le nom du fichier : ");
    scanf("%255s", nomFichier);

    init_noeud(nomFichier,&tabSommet,&tabNiveau,&ns);

    init_pred_p(&tabSommet , ns) ;

    tri_insertion(&tabNiveau , tabSommet , ns)  ;

    bellman(tabNiveau , &tabSommet, ns ) ;

    print_res(tabSommet  , ns);

    clear_noeud(tabSommet , ns ,  tabNiveau );

    return 0;
}


#ifndef PROJET_H
#define PROJET_H = 1

#include <stdio.h>
#include <stdlib.h>

/**
 * @Généralité_1 : une instance de struct Noeud est appelée nœud courant, tâche courante, sommet courant ou encore  Ni.
 * @Généralité_2 : struct Noeud représente une tâche dans un problème d'ordonancement potentiel-tâche.
 * @Généralité_3 : struct Noeud est utilisé dans un tableau nommé tabSommet. Ce tableau contient toutes les tâches du problème d'ordonancement courant.
 *
 *
 * @poids :  poids des arcs sortant du nœud courant.(poids>=0)
 *
 * @dPlusTot :  date au plus tôt de la tâche/nœud courante.(dPlusTot>=0)
 *
 * @dPlusTard :  date au plus tard de la tâche/nœud courante.(dPlusTard>=0)
 *
 * @niveau :  niveau des arcs sortant du nœud courant.(niveau>=0)
 *
 * @nbsucc :  nombre de successeur du nœud courant. Utilisée pour redimensionner succ.(nbsucc>=0)
 *
 * @succ :  tableau d'entier représentant un indice dans tabSommet. Les indices stockés représentent les
 *    successeurs de la tâche nœud courant. Par exemple succ[1] = 10, tabSommets[10] est un succésseur de Ni.
 *
 * @nbpred :  nombre de prédecesseur du nœud courant. Utilisée pour redimensionner pred.(nbpred>=0)
 *
 * @pred :  tableau d'entier représentant un indice dans tabSommet. Les indices stockés représentent les
 *    prédecesseur de la tâche nœud courant. Par exemple pred[1] = 10, tabSommets[10] est un prédecesseur de Ni.
 *
 *
 * @Nœuds_spéciaux :  Toutes les instances de struct Noeud ont au moins 1 successeur (Tâche_final appelé p ).
 *
 *    -p est le seul sommet sans successeur. p est la tâche final , son niveau est le plus haut ,
 *        il n'a pas de poids  et sa date au plus tot et au plus tard représente la durée du projet .
 *
 * @initialisation : voir fonction init_noeud
 *
 * @destructeur : fonction clear_noeud
 */
struct Noeud {
    double  poids ;
    double dPlusTot ;
    double dPlusTard ;
    int niveau ;
    int  nbsucc ;
    int  *  succ ;
    int  nbpred ;
    int  *  pred ;
};

/**
 * @définition : initilialisation de tabSommet et tabNiv en fonction d'un fichier formaté de la façon suivante :
 *   — Des lignes commençant par c, suivi d’un espace, contenant des commentaires,
 *   — une ligne commençant par p, suivi d’un espace, contenant la description du problème. Ici
 * nous considérerons le nombre de sommets,
 *   — n lignes commençant par v (vertex), suivi d’un espace, contenant les informations sur les
 * noeuds,
 *   — m lignes commençant par a (arc), suivi d’un espace, contenant les informations sur les
 * contraintes de précédences
 *
 *
 * @NotaBene : init_noeud initialise les niveaux , successeurs et prédécesseurs de chaque sommet.
 * Sauf pour les prédecesseurs de  p qui sont initialisé dans init_pred_p. P est à la case ns + 1 dans tabSommet.
 *
 * @param nFichier :  chaîne de caractères  représentant le nom du fichier à lire.
 * @param tabSommet : tableau contenant toutes les tâches du problème d'ordonnancement courant.
 * @param tabNiv : - Tableau d'entier représentant un indice dans tabSommet.
 *                 - Les indices stockés représentent  une tâche.
 *                 - Par exemple tabNiv[1] = 10, tabSommets[10] est un prédecesseur de Ni.
 *                 - Ce vecteur va être trié en fonction des niveaux des sommets.
 *                 - tabNiv[NS + 1 ] = indice de p (p toujours de niveau maximun)
 * @param ns : taille du vecteur tabSommet. (ns pour nombre de sommets ).
 *
 *
 *
 * @détail_Initialisation :
 * poids de s = poids donné;
 * niveau de s = 0 Valeur calculé lors de l'ajout des arcs
 * dPlusTot de s = 0
 * dPlusTard de s = -1 lors de l'algorithme de Bellman change cette variable si elle est égale à -1. Ceci permet de détecter
 * les sommets dont la date au plus tard doit être initialisée .
 * nbsucc de s = 0;
 * nbprec de s = 0;
 *
 *
 *
 */
void init_noeud ( char * nFichier  , struct Noeud ** tabSommet, int **  tabNiv , int * ns ) ;

/**
 * @définition : Destructeur des objets du projet
 *
 * @param n noeuds à désallouer
 * @param ns nombre de sommets hors p
 * @param niv tableau de niveau à désallouer
 */
void clear_noeud(struct Noeud * n  , int ns ,  int * niv ) ;

/**
 * @définition : tri par insertion du tableau tabNiveau.
 *
 *
 * @param tabNiv : - Tableau d'entier représentant un indice dans tabSommet.
 *                 - Les indices stockés représentent  une tâche.
 *                 - Par exemple tabNiv[1] = 10, tabSommets[10] est un prédecesseur de Ni.
 *                 - Ce vecteur va être trié en fonction des niveaux des sommets.
 * @param tabSommet : tableau contenant toutes les tâches du problème d'ordonnancement courant.
 * @param ns : taille du vecteur tabSommet. (ns pour nombre de sommets ).
 */
void tri_insertion(int  ** tabNiv , struct Noeud * tabSommet , int  ns) ;

/**
 * @définition : - Algorithme de bellman aller et retour.
 *               - Cette fonction permet, pour chaque sommet , de donner sa date au plus tôt et plus tard.
 *
 * @param tabNiv : - Tableau d'entier représentant un indice dans tabSommet.
 *                 - Les indices stockés représentent  une tâche.
 *                 - Par exemple tabNiv[1] = 10, tabSommets[10] est un prédecesseur de Ni.
 *                 - tabNiv doit être trié en fonction des niveaux des sommets.
 * @param tabSommet : tableau contenant toutes les tâches du problème d'ordonnancement courant.
 * @param ns : taille du vecteur tabSommet. (ns pour nombre de sommets ).
 */
void bellman(int  * tabNiv , struct Noeud ** tabSommet , int  ns) ;

/**
 * @définition : Permets d'ajouter p en successeur au sommet sans prédécesseur
 *
 * @param tabSommet : tableau contenant toutes les tâches du problème d'ordonnancement courant.
 * @param ns : taille du vecteur tabSommet. (ns pour nombre de sommets ).
 */
void init_pred_p(struct Noeud ** tabSommet , int  ns);

/**
 *
 * @définition Écrit le résultat du programme dans results.txt selon le format suivant :
 * X est un entier . x, y, z sont des réels
 * .
 * .
 * .
 * sommet Xi : Date au plus tot =  x.yy  , Date au plus tard = x.yy  , Marge : x.yy
 * .
 * .
 * .
 *
 * Tâches critiques :
 * x1, x2, ..., xn
 *
 *
 * Durée minimale : zzz
 *
 *
 *
 * @param nFichier :  chaîne de caractères  représentant le nom du fichier à lire.
 * @param tabSommet : tableau contenant toutes les tâches du problème d'ordonnancement courant.
 * @param ns : taille du vecteur tabSommet. (ns pour nombre de sommets ).
 */
void print_res(struct Noeud * tabSommet  ,  int  ns);

#endif

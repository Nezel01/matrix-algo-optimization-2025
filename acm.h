/**
 * \file acm.h
 * \brief Calcul et représentation d'arbres couvrant minimaux (en-tête)
 * \version 2
 * \date novembre 2020
 */

#ifndef ACM_H
#define ACM_H

#include "graph_mat-2.h"

/**
 * \brief Calcule l'arbre couvrant minimal de g par l'algorithme de Prim partant
 * du sommet \a depart
 * \param g adresse de la variable graph_mat à lire
 * \return l'adresse d'un arbre couvrant minimal (représenté comme un graphe)
 * si tout s'est bien passé, NULL en cas de problème d'allocation
 * mémoire
 * On suppose que le graphe est connexe.
 * De la mémoire est allouée pour l'acm. Il faut la libérer avec la
 * fonction gm_free.
 */
graph_mat *gm_acm_prim(const graph_mat *g, unsigned depart);

/**
 * \brief Calcule l'arbre couvrant minimal de g par l'algorithme de Kruskal
 * \param g adresse de la variable graph_mat à lire
 * \return l'adresse d'un arbre couvrant minimal de g
 * si tout s'est bien passé, NULL en cas de problème d'allocation
 * mémoire
 *
 * On suppose que \a g est connexe.
 * De la mémoire est allouée pour \a acm. Il faut la libérer avec la
 * fonction \a gm_detruire.
 */
graph_mat *gm_acm_kruskal(const graph_mat *g);

/**
 * \brief Écrit dans le fichier nommé \a nom_fichier une description au format
 * dot du graphe \a g avec son arbre couvrant minimal \a acm
 * \param g adresse de la variable graph_mat à lire
 * \param acm adresse de l'arbre couvrant minimal à lire
 * \return 0 si tout s'est bien passé, -1 en cas de problème d'entrée sortie
 *
 * Les arêtes de l'arbre couvrant minimal sont tracées en rouge. Celles qui
 * n'appartiennent pas à cet arbre couvrant sont tracées en noir.
 */
int gm_write_dot_with_mst(const graph_mat *g, const graph_mat *acm, const char *nom_fichier);

#endif /* ACM_H */

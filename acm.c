/**
 * \file acm.c
 * \brief Calcul et représentation d'arbres couvrant minimaux (implémentation)
 * \version 2
 * \date novembre 2020
 */
#include "acm.h"

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#define INFINI 999999

/*************** Prim */




graph_mat *gm_acm_prim(const graph_mat *g, unsigned depart){
  int n = gm_n(g), pivot;
  int parent[n], marque[n];
  double poid[n], tmp, poid_total = 0, min;
  graph_mat * h = gm_init(n);

  
  for(int i=0; i<n; i++){
    if(i == depart){
      poid[i] = 0;
      parent[i] = i;
    }else{
      poid[i] = INFINI;
      parent[i] = -1;
    }
    marque[i] = 0;
  }
  poid[depart] = 0;
  
  for(int i=0; i<n; i++){
      pivot = -1;
      min = DBL_MAX;
    for(int j=0; j<n; j++){     //Recup pivot
      if(marque[j] == 0 && poid[j] < min){
        min = poid[j];
        pivot = j;
      }
    }
    
    printf("pivot = %d\n",pivot);
    for(int j = 0; j<n; j++){
      tmp = gm_val_edge(g, pivot, j);
      if(tmp != DBL_MAX && marque[j] == 0){
        if(tmp < poid[j]){
          poid[j] = gm_val_edge(g, j, pivot);
          parent[j] = pivot;
        }
      }
    }
    marque[pivot] = 1;
  }
  for(int i=0; i<n; i++){
    poid_total += poid[i];
  }
  printf("Poid total Prim : %lg\n",poid_total);
  return h;
}

/*************** Kruskal */
/* type et fonctions auxiliaires pour Kruskal : ne pas modifier */

/**
 * \brief Type \a struct edge avec cout
 *
 * Une arête est représentée par ses deux extrémités :
 * \a v et \a w et sa valeur \a value
 * Pour l'unicité de la représentation, on supposera que
 * \f$ v \leq w \f$.
 * On accèdera directement aux champs de cette structure.
 */
struct edge {
	int v; /**<plus petite extrémité de l'arête */
	int w; /**<plus grande extrémité de l'arête */
	double value; /**<coût de l'arête */
};

/**gm_add_edge(h, tmp.w, tmp.v, tmp.value);
 * \brief Compare les arêtes par coût
 * \param e1 adresse de la première arête
 * \param e2 adresse de la deuxième arête
 * \return -1, 0 ou 1 selon que le coût de e1 est respectivement inférieur,
 * égal ou supérieur au coût de e2.
 *
 * Cette fonction n'est utilisée que par \a sort_edges et ne doit pas être
 * modifiée.
 */
static int cmp_edges(const void *e1, const void *e2)
{
	const struct edge *f1 = e1;
	const struct edge *f2 = e2;
	if (f1->value == f2->value)
		return 0;
	if (f1->value < f2->value)
		return -1;
	return 1;
}

/**
 * \brief Trie les arêtes du graph_mat par coût croissant
 * \param g adresse du graph_mat à lire
 * \return un pointeur vers un tableau des arêtes de g triées par coût
 * croissant. Les boucles sont supprimées et en cas d'arêtes multiple, seule
 * l'arête de plus petit coût est présente dans le tableau. Si l'allocation du
 * tableau a échoué, la valeur de retour est \a NULL.
 *
 * La fonction appelante devra libérer la mémoire allouée au tableau avec la
 * fonction \a free.
 */
static struct edge *sort_edges(const graph_mat *g)
{
	unsigned v, w, i = 0;
	struct edge *tab = malloc(gm_m(g) * sizeof(struct edge));
	if (!tab)
		return NULL;
	for (v = 0; v < gm_n(g); ++v)
		for (w = v + 1; w < gm_n(g); ++w)
			if (gm_mult_edge(g, v, w)) {
				tab[i].v = v;
				tab[i].w = w;
				tab[i].value = gm_val_edge(g, v, w);
				++i;
			}
	qsort(tab, i, sizeof(struct edge), cmp_edges);
	return tab;
}
/* Calcul de l'ACM par Kruskal : à remplir ! */

graph_mat *gm_acm_kruskal(const graph_mat *g){
  int n = gm_n(g), compo_connexe[n], tmp_rep, taille_h = 0, k=0;
  struct edge *arrete = sort_edges(g), tmp;
  double poid_total = 0;
  graph_mat * h = gm_init(n);
  for(int i=0; i<n; i++){
    compo_connexe[i] = i;
  }
  while(taille_h < n-1){
    tmp = arrete[k++];
    if(compo_connexe[tmp.v] != compo_connexe[tmp.w]){
      tmp_rep = compo_connexe[tmp.v];
      for(int j = 0; j<n; j++){       //mise a jour des composantes
        if(compo_connexe[j] == tmp_rep){
          compo_connexe[j] = compo_connexe[tmp.w];
        }
      }
      gm_add_edge(h, tmp.w, tmp.v, tmp.value);
      poid_total += tmp.value;
      taille_h++;
    }
  }
  printf("poid total Kruscal = %lg\n",poid_total);
  free(arrete);
  
  return h;
}

int gm_write_dot_with_mst(const graph_mat *g, const graph_mat *acm, const char *nom_fichier)
{
	unsigned u, v;
	FILE *f = fopen(nom_fichier, "w");
	if (!f) { perror("fopen"); return -1; }
	fputs("graph {\n", f);
	for (u = 0; u < gm_n(g); ++u)
		fprintf(f, "\t%d;\n", u);
	fputs("\n", f);
	fputs("\tsubgraph g {\n", f);
	for (u = 0; u < gm_n(g); ++u)
		for (v = u; v < gm_n(g); ++v)
			if (gm_mult_edge(g, u, v) &&
				( u == v || !gm_mult_edge(acm, u, v)))
					fprintf(f, "\t\t%d -- %d [label = %.2f];\n",
						u, v, gm_val_edge(g, u, v));
	fputs("\t}\n", f);
	fputs("\tsubgraph acm {\n\t\tedge [color = red]\n", f);
	for (u = 0; u < gm_n(acm); ++u)
		for (v = u; v < gm_n(acm); ++v)
			if (gm_mult_edge(acm, u, v))
				fprintf(f, "\t\t %d -- %d [fontcolor = red, label = %.2f];\n",
					u, v, gm_val_edge(acm, u, v));
	fputs("\t}\n}\n", f);
	fclose(f);
	return 0;
}

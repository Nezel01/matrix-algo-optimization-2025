#ifndef GRAPH_MAT_1
#define GRAPH_MAT_1

typedef struct graph_mat graph_mat;

/* Constructeur, générateur
 * Retourne un pointeur vers un graphe nouvellement alloué, à n sommets et sans
 * arête, ou bien le pointeur NULL en cas d'échec d'une allocation. */
graph_mat *gm_init(unsigned n);

/* Destructeur
 * Libère toute la mémoire associée au graphe d'adresse g.
 * Ne fait rien si g est le pointeur NULL */
void gm_free(graph_mat *g);

/* Accesseur, observateur
 * Retourne l'ordre (nombre de sommets) du graphe d'adresse g */
unsigned gm_n(const graph_mat *g);

/* Accesseur, observateur
 * Retourne le nombre d'arêtes du graphe d'adresse g */
unsigned gm_m(const graph_mat *g);

/* Accesseur, observateur
 * Retourne le nombre d'arêtes {v, w} du graphe d'adresse g.
 * On suppose que v et w sont entre 0 et n - 1 */
unsigned gm_mult_edge(const graph_mat *g, unsigned v, unsigned w);

/* Accesseur, observateur
 * Retourne la plus petite valeur d'une arête {v, w} du graphe d'adresse g, si
 * il y en a, sinon retourne DBL_MAX.
 * On suppose que v et w sont entre 0 et n - 1.
 */
double gm_val_edge(const graph_mat *g, unsigned v, unsigned w);

/* Modificateur, générateur
 * ajoute une arête {v, w} au graphe d'adresse g, de valeur val.
 * En cas d'arêtes multiples, seule la plus petite valeur d'une arête {v, w} est
 * sauvegardée.
 * On suppose que v et w sont entre 0 et n - 1 */
void gm_add_edge(graph_mat *g, unsigned v, unsigned w, double val);

/* Accesseur, observateur
 * Retourne le degré du sommet v dans le graphe d'adresse g
 * On suppose que v est entre 0 et n - 1 */
unsigned gm_degree(const graph_mat *g, unsigned v);

/* Fonction d'entrée-sortie
 * Affiche des informations sur le graphe d'adresse g dans le terminal */
void gm_disp(const graph_mat *g);

/* Fonction d'entrée-sortie
 * Écrit le graphe d'adresse g au format dot dans le fichier de nom filename.
 * retourne une valeur négative en cas d'erreur (fichier non ouvrable en
 * écriture, ...) et 0 sinon. */
int gm_write_dot(const graph_mat *g, const char *filename);

/* Autre constructeur
 * Retourne un pointeur vers un nouveau graphe aléatoire
 * d'ordre n, simple, où chaque arête est présente avec probabilité p
 * ou bien NULL en cas d'échec d'allocation
 * Les poids des arêtes présentes sont aussi aléatoires,
 * de loi uniforme sur [0, 1]
 */
graph_mat *gm_random(unsigned n, double p);

#endif /* ifndef GRAPH_MAT_1 */

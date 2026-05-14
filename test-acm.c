#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph_mat-2.h"
#include "acm.h"

int main()
{
	graph_mat *g = gm_random(15, 0.5);
	{ /* partie Prim */
		graph_mat *acm = gm_acm_prim(g, 0);
		if (acm != NULL) {
			gm_write_dot_with_mst(g, acm,
					"acm_prim.dot");
			system("dot -Tx11 acm_prim.dot");
			gm_free(acm);
		}
	}
	{ /* partie Kruskal */
		graph_mat *acm = gm_acm_kruskal(g);
		if (acm != NULL) {
			gm_write_dot_with_mst(g, acm,
					"acm_prim.dot");
			system("dot -Tx11 acm_prim.dot");
			gm_free(acm);
		}
	}
	gm_free(g);
	return EXIT_SUCCESS;
}

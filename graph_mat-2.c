#include "graph_mat-2.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>


struct graph_mat {
	unsigned n;
	unsigned m;
	unsigned *adj;
	/* int is_or; in future version*/
	double *values;
};

graph_mat *gm_init(unsigned n)
{
	graph_mat *g;
	unsigned v, w;
	
	g = malloc(sizeof(graph_mat));
	if (g == NULL) {
		perror("malloc in gm_init");
		return NULL;
	}
	g->adj = calloc(n * n, sizeof(unsigned));
	if (g->adj == NULL) {
		perror("calloc in gm_init");
		free(g);
		return NULL;
	}
	/* début solution */
	g->values = malloc(n * n * sizeof(double));
	if (g->values == NULL) {
		perror("malloc in gm_init");
		free(g->adj);
		free(g);
		return NULL;
	}
	for (v = 0; v < n; ++v)
		for (w = 0; w < n; ++w)
			g->values[v * n + w] = DBL_MAX;
	/* fin solution */
	g->n = n;
	g->m = 0;
	return g;
}

void gm_free(graph_mat *g)
{
	if (g == NULL)
		return;
	free(g->values);
	free(g->adj);
	free(g);
}

unsigned gm_n(const graph_mat *g)
{
	return g->n;
}

unsigned gm_m(const graph_mat *g)
{
	return g->m;
}

unsigned gm_mult_edge(const graph_mat *g, unsigned v, unsigned w)
{
	return g->adj[gm_n(g) * v + w];
}

void gm_add_edge(graph_mat *g, unsigned v, unsigned w, double val)
{
	++(g->adj[gm_n(g) * v + w]);
	if (v != w)
		++(g->adj[gm_n(g) * w + v]);
	++(g->m);
	double curr_val = g->values[gm_n(g) * v + w];
	if (val < curr_val)
		g->values[gm_n(g) * v + w] = g->values[gm_n(g) * w + v] = val;
}

double gm_val_edge(const graph_mat *g, unsigned v, unsigned w)
{
	return g->values[v * gm_n(g) + w];
}

unsigned gm_degree(const graph_mat *g, unsigned v)
{
	unsigned s = 0, w;
	for (w = 0; w < gm_n(g); ++w)
		if (v == w)
			s += 2 * gm_mult_edge(g, v, w);
		else
			s += gm_mult_edge(g, v, w);
	return s;
}

void gm_disp(const graph_mat *g)
{
	unsigned v, w;
	printf("n = %d, m = %d\n", gm_n(g), gm_m(g));
	for (v = 0; v < gm_n(g); ++v)
		for (w = 0; w < gm_n(g); ++w) {
			printf("%3d", gm_mult_edge(g, v, w));
			if (w != gm_n(g) - 1)
				printf(" ");
			else
				printf("\n");
		}
}

int gm_write_dot(const graph_mat *g, const char *filename)
{
	FILE *f;
	unsigned v, w, k;

	f = fopen(filename, "w");
	if (f == NULL) {
		perror("fopen in gm_write_dot");
		return -1;
	}

	fprintf(f, "graph {\n");
	for (v = 0; v < gm_n(g); ++v)
		fprintf(f, "\t%d;\n", v);

	fprintf(f, "\n");

	for (v = 0; v < gm_n(g); ++v)
		for (w = v; w < gm_n(g); ++w)
			for (k = 0; k < gm_mult_edge(g, v, w); ++k)
				fprintf(f, "\t%d -- %d;\n", v, w);
	fprintf(f, "}\n");
	fclose(f);
	return 0;
}

graph_mat *gm_random(unsigned n, double p){
	unsigned v, w;
	graph_mat *g = gm_init(n);
	
	
	if (g == NULL) {
		perror("gm_init in gm_random");
		return NULL;
	}
	for (v = 0; v < gm_n(g); ++v)
		for (w = v + 1; w < gm_n(g); ++w) {
			double u = (double) rand() / RAND_MAX;
			if (u < p) {
				double x = (double) rand() / RAND_MAX;
				gm_add_edge(g, v, w, x);
			}
		}
	return g;
}

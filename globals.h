#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int n_layers;
	int *neurons_per_layer;
	double ***weights;
	double **biases;
} network_t;
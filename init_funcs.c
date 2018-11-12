#include "init_funcs.h"

network_t
*init_network(){
	int i;
	network_t *net;
	
	net = malloc(sizeof(network_t));
	if(net == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("How many layers: ");
	scanf("%d", &net->n_layers);
	
	net->neurons_per_layer = malloc(sizeof(int)*net->n_layers);
	if(net->neurons_per_layer == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	for(i=0; i<net->n_layers; i++) {
		if(i==0) {
			printf("How many neurons in the input layer: ");
		} else if(i == net->n_layers-1) {
			printf("How many neurons in the output layer: ");
		} else {
			printf("How many neurons in hidden layer #%d: ", i);
		}
		scanf("%d", &net->neurons_per_layer[i]);
	}
	
	init_weights(net);
	init_biases(net);

	return net;
}

void 
init_weights(network_t *net){
	int i, j, k;
	//Using 0 every time so that the result can be replicated (but obviously we could base this off time if it turns out that's what we want)
	srand(0);
	
	net->weights = (double***) malloc(sizeof(double**)*net->n_layers-1);
	if (net->weights == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(k=0; k<net->n_layers-1; k++) {
		net->weights[k] = (double**) malloc(sizeof(double*)*net->neurons_per_layer[k]);
		if(net->weights[k] == NULL) {
			printf("Error while allocating space.\n");
			exit(EXIT_FAILURE);
		}
		for(i=0; i<net->neurons_per_layer[k]; i++) {
			net->weights[k][i] = (double*) malloc(sizeof(double)*net->neurons_per_layer[k+1]);
			if(net->weights[k][i] == NULL) {
				printf("Error while allocating space.\n");
				exit(EXIT_FAILURE);
			}
			for(j=0; j<net->neurons_per_layer[k+1]; j++) {
				net->weights[k][i][j] = rand()%10 + 1;
			}
		}
	}
	
	return;
}

void 
init_biases(network_t *net){
	int i,j;
	
	//Using 1 just so that the biases don't have the same values as the weights (for no real reason other than that)
	srand(1);
	
	net->biases = malloc(sizeof(double*)*net->n_layers);
	if(net->biases == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<net->n_layers; i++) {
		net->biases[i] = malloc(sizeof(double)*net->neurons_per_layer[i]);
		if(net->biases[i] == NULL) {
			printf("Error while allocating space.\n");
			exit(EXIT_FAILURE);
		}	
		for(j=0; j<net->neurons_per_layer[i]; j++) {
			//this is because the input layer doesn't need a bias (or an activation function in case I forget)
			if(i==0) {
				net->biases[i][j] = 0;
			} else {
				net->biases[i][j] = rand()%10 + 1;
			}
		}
	}
	
	return;
}
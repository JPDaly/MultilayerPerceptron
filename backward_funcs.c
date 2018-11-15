#include "header.h"

void
back_propagation(network_t *net, gradient_t *grad, double *output){
	int i,j,k;
	
	/*
	loop through each layer except input layer
		loop through current layer's activations
			determine gradient dC/dz 
				the equation used depends on whether this is the output layer or not
				if not output layer use previous layer in calculation
				otherwise use 2*(a-y)
		(use above value for the following calculations)
		loop through all weights in that connect the current layer
			calculate gradient for weights
		loop through each bias for this layer 
			calculate gradients for biases
		
	*/
	
	for(i=net->n_layers-1; i>=0; i--) {
		for(j=0; j<net->neurons_per_layer[i]; j++) {
			//activation gradients (actually just the derivative with respect to z)
			if(i==net->n_layers-1) {
				grad->activations[i][j] = 2*(net->activations[i][j] - output[j])*net->activations[i][j]*(1-net->activations[i][j]);
				continue;
			} else if(i!=0) {
				grad->activations[i][j] = 0;
				for(k=0; k<net->neurons_per_layer[i+1]; k++){
					grad->activations[i][j] += grad->activations[i+1][k]*net->weights[i][j][k];
				}
				grad->activations[i][j] /= (1.0*k);
			}
			
			//biases (need this as well as the above because this will eventually take the average
			grad->biases[i][j] += grad->activations[i][j];
			
			//weights
			for(k=0; k<net->neurons_per_layer[i+1]; k++){
				grad->weights[i][j][k] = grad->activations[i+1][k]*net->activations[i][j];
			}
		}
	}
	return;
}



double 
sig_derivative(double in){
	double sig = sigmoid(in);
	return sig*(1.0-sig);
}

gradient_t
*init_grad(network_t *net){
	int j,i;
	gradient_t *grad;
	
	grad = malloc(sizeof(gradient_t));
	if(grad == NULL) {
		printf("Error gradient_t while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	grad->weights = (double***) malloc(sizeof(double**)*net->n_layers-1);
	if (grad->weights == NULL) {
		printf("Error #8 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(j=0; j<net->n_layers-1; j++) {
		grad->weights[j] = (double**) malloc(sizeof(double*)*net->neurons_per_layer[j]);
		if(grad->weights[j] == NULL) {
			printf("Error grad_weights 1 while allocating space.\n");
			exit(EXIT_FAILURE);
		}
		for(i=0; i<net->neurons_per_layer[j]; i++) {
			grad->weights[j][i] = (double*) calloc(sizeof(double),net->neurons_per_layer[j+1]);
			if(grad->weights[j][i] == NULL) {
				printf("Error grad_weights 2 while allocating space.\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	grad->biases = (double**) malloc(sizeof(double*)*net->n_layers);
	if(grad->biases == NULL) {
		printf("Error #11 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<net->n_layers; i++) {
		grad->biases[i] = (double*) calloc(sizeof(double),net->neurons_per_layer[i]);
		if(grad->biases[i] == NULL) {
			printf("Error #12 while allocating space.\n");
			exit(EXIT_FAILURE);
		}	
	}
	
	grad->activations = (double**) malloc(sizeof(double*)*net->n_layers);
	if(grad->activations == NULL) {
		printf("Error #13 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<net->n_layers; i++) {
		grad->activations[i] = (double*) calloc(sizeof(double), net->neurons_per_layer[i]);
		if(grad->activations[i] == NULL) {
			printf("Error #14 while allocating space.\n");
			exit(EXIT_FAILURE);
		}
	}
	return grad;
}


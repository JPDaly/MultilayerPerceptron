#include "header.h"

void
back_propagation(network_t *net, gradient_t *grad, double *output, int batch_example){
	int i,j,k;
	
	//printf("	Start1\n");
	for(i=0; i<net->neurons_per_layer[net->n_layers-1]; i++) {
		grad->biases[net->n_layers-1][i] = 2*(net->activations[net->n_layers-1][i] - output[i])*net->activations[net->n_layers-1][i]*(1-net->activations[net->n_layers-1][i]);
	}
	//printf("	end1\n");
	
	//printf("	Start2\n");
	for(k=net->n_layers-2; k>=0; k--) {
		for(i=0; i<net->neurons_per_layer[k]; i++) {
			if(batch_example==0) grad->biases[k][i] = 0;
			for(j=0; j<net->neurons_per_layer[k+1]; j++){
				grad->biases[k][i] += net->activations[k+1][j]*(1-net->activations[k+1][j])*net->weights[k][j][i]; 
				//printf("	%f\n", net->activations[k][i]);
				if(batch_example == 0){
					grad->weights[k][j][i] = grad->biases[k+1][j]*net->activations[k][i];	
				} else {
					grad->weights[k][j][i] += grad->biases[k+1][j]*net->activations[k][i];
				}
			}
		}
	}
	//printf("	end2\n");

	return;
}


void 
grad_descent(network_t *net, gradient_t *grad, int n_examples){
	int i,j,k;
	
	//printf("\n\n----Weights----\n\n");
	//update weights
	//printf("here1\n");
	for(k=0; k<net->n_layers-1; k++) {
		//printf("here2\n");
		for(i=0; i<net->neurons_per_layer[k+1]; i++) {
			//printf("here3\n");
			for(j=0; j<net->neurons_per_layer[k]; j++) {
				//printf("here4\n");
				//printf("%f\n", grad->weights[k][i][j]);
				/*
				Subtracting is definitely correct!! imagine a 2d graph where 
					you want to minimise the function and see which way the x-axis goes as you add/subtract
					the gradient from the x-axis
				*/
				//printf("%f\n", net->weights[k][i][j]);
				net->weights[k][i][j] -= LEARNING_RATE*grad->weights[k][i][j]/(1.0*n_examples);
				//printf("	%f\n", net->weights[k][i][j]);
				//printf("	%f\n", grad->biases[k][j]);
			}
		}
	}
	
	for(k=1; k<=net->n_layers-1; k++) {
		for(j=0; j<net->neurons_per_layer[k]; j++) {
			net->biases[k][j] -= LEARNING_RATE*grad->biases[k][j]/(1.0*n_examples);
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
		grad->weights[j] = (double**) malloc(sizeof(double*)*net->neurons_per_layer[j+1]);
		if(grad->weights[j] == NULL) {
			printf("Error grad_weights 1 while allocating space.\n");
			exit(EXIT_FAILURE);
		}
		for(i=0; i<net->neurons_per_layer[j+1]; i++) {
			grad->weights[j][i] = (double*) calloc(sizeof(double),net->neurons_per_layer[j]);
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
		grad->activations[i] = (double*) malloc(sizeof(double)*net->neurons_per_layer[i]);
		if(grad->activations[i] == NULL) {
			printf("Error #14 while allocating space.\n");
			exit(EXIT_FAILURE);
		}
	}
	return grad;
}


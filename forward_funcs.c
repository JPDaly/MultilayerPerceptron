#include "header.h"

void
calc_output(network_t *net, double *input){
	int i,j,k;
	
	for(i=0; i<net->neurons_per_layer[0]; i++) {
		net->activations[0][i] = input[i];
	}
	//This implements Sigmoid(Sum(w*x) + b) but I need to make sure this is the correct formula
	for(k=0; k<net->n_layers-1; k++) {
		for(i=0; i<net->neurons_per_layer[k+1]; i++) {
			net->activations[k+1][i] = net->biases[k+1][i];
			for(j=0; j<net->neurons_per_layer[k]; j++) {
				net->activations[k+1][i] += net->weights[k][j][i]*net->activations[k][j];
			}
			net->activations[k+1][i] = sigmoid(net->activations[k+1][i]);
		}
	}
	return;
}

double 
calc_error(int length, double *output, double *desired_output){
	int i;
	double error = 0.0;
	for(i=0; i<length; i++) {
		error += (desired_output[i]-output[i])*(desired_output[i]-output[i]);
	}
	return error;
}

void
read_batch(FILE *data_file, data_t *data){
	int i, points_collected=0, n_features=0;
	char c;
	
	while(points_collected < data->batch_size){
		while(n_features < data->features+1) {
			c = getc(data_file);
			//somehow get the features from the file (transform char to double)
		}
	}
	
	return;
}
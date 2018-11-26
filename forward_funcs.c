#include "header.h"


//Basically matrix multiplication for each layer to produce the output layer
void
calc_output(network_t *net, double *input){
	int i,j,k;
	
	//Take the input data and set it as the activations of the input layer
	for(i=0; i<net->neurons_per_layer[0]; i++) {
		net->activations[0][i] = input[i];
	}

	//This implements Sigmoid(Sum(w*x) + b) but I need to make sure this is the correct formula
	for(k=0; k<net->n_layers-1; k++) {
		for(j=0; j<net->neurons_per_layer[k+1]; j++) {
			net->activations[k+1][j] = net->biases[k+1][j];
			for(i=0; i<net->neurons_per_layer[k]; i++) {
				net->activations[k+1][j] += net->weights[k][j][i]*net->activations[k][i];
			}
			net->activations[k+1][j] = sigmoid(net->activations[k+1][j]);
		}
	}
	return;
}

//Finds the error based on the produced output and the desired output
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
read_batch(FILE *data_file, data_t *data, double **batch, int *points_read){
	int i,j;
	char c;
	
	for(i=0; i<data->batch_size; i++){
		(*points_read)++;
		for(j=0; j<data->features+1; j++) {
			fscanf(data_file, "%lf", &batch[i][j]);
			c = getc(data_file);
			if(c != ',' && c != '\n' && c != EOF){
				printf("The data isn't formatted correctly.\n");
				exit(EXIT_FAILURE);
			}
		}
		if(*points_read == data->data_size) {
			i++;
			break;
		}
	}
	batch[i][0] = -1.0;
	return;
}


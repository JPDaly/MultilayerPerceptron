#include "header.h"
#include <time.h>

void print_network(network_t *net);
double sig_derivative(double in);

int
main(int argc, char *argv[]){
	clock_t end, start;
	network_t *net;
	data_t *data;
	double input[3] = {1,2,3};
	double output[1] = {1};
	
	//inititalising
	net = init_network();
	data = init_data();
	
	
	//Start timing
	start = clock();
	
	//Feed forward
	calc_output(net, input);
	calc_error(net->neurons_per_layer[net->n_layers-1], net->activations[net->n_layers-1], output);
	
	
	//Stop timing
	end = clock();

	//Print values in network
	//print_network(net);
	
	
	//Print runtime
	printf("\n------ Runtime = %.5f seconds ------\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	//Free memory
	free(net->activations);
	free(net->weights);
	free(net->biases);
	free(net->neurons_per_layer);
	free(net);
	
	return 0;
}


/*
To compile all the files together use the following:
	gcc -Wall -o main main.c init_funcs.c
You don't need to include the header files.
You can also continue to add more .c files to the end of this as you need/use them.
*/





//The following are here because I don't think they have anything to do with initialising or feed forward
void 
print_network(network_t *net){
	int k,j,i;
	
	printf("\n\n----Weights----\n\n");
	for(i=0; i<net->n_layers-1; i++){
		printf("\nLink #%d\n", i+1);
		for(j=0; j<net->neurons_per_layer[i]; j++){
			for(k=0; k<net->neurons_per_layer[i+1]; k++){
				printf("%.2f,", net->weights[i][j][k]);
			}
			printf("\n");
		}
	}
	
	printf("\n\n----Biases----\n\n");
	for(i=0; i<net->n_layers; i++){
		printf("\nLayer #%d\n", i+1);
		for(j=0; j<net->neurons_per_layer[i]; j++){
			printf("%.2f,", net->biases[i][j]);
		}
	}
	
	printf("\n\n----Activations----\n\n");
	for(i=0; i<net->n_layers; i++){
		printf("\nLayer #%d\n", i+1);
		for(j=0; j<net->neurons_per_layer[i]; j++){
			printf("%.2f,", net->activations[i][j]);
		}
	}
	printf("\n\n");
	return;
}


double 
sig_derivative(double in){
	double sig = sigmoid(in);
	return sig*(1.0-sig);
}

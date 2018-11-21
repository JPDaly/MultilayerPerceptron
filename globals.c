#include "header.h"

//Simply returns the output of sigmoid given an input
double 
sigmoid(double in){
	return 1.0/(1.0 + exp(-in));
}


//Returns the binary of num (a base 10 integer) in a int array.
double
*num_to_binary(int num, int max_digits) {
	int power = 0, max_power=max_digits-1, product=1, sum=1, i;
	double *binary;
	int digits=0;
	
	//Determine the maximum power of 2 required to make num
	while(sum < num || (max_power != -1 && power != max_power)){
		power++;
		product *= 2;
		sum += product;
	}
	
	max_power = power;
	
	//Set size of int array (extra space for end of array number)
	binary = malloc(sizeof(double)*(max_power+2));
	if(binary == NULL){
		printf("Error #15 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	//adds a 1 to the binary array if the max_power of 2 remains in num then subtract that power of 2
	for(i=max_power; i>=0; i--) {
		if(num-product >= 0) {
			num -= product;
			binary[digits++] = 1.0;
		} else {
			binary[digits++] = 0.0;
		}
		product /= 2;
	}
	//add end of array number
	binary[digits] = -1;
	
	return binary;
}

void 
print_network(network_t *net){
	int k,j,i;
	
	printf("\n\n----Basic shape of network----\n\n");
	for(i=0; i<net->n_layers; i++){
		if(i!=0) printf("-");
		printf("%d", net->neurons_per_layer[i]);
	}
	
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
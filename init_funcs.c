#include "header.h"

//Initialise the network_t by allocating appropriate space
network_t
*init_network(data_t *data){
	int i;
	double *output_binary;
	network_t *net;
	
	//allocate space for network_t variable
	net = malloc(sizeof(network_t));
	if(net == NULL) {
		printf("Error #6 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	//ask for the number of hidden layers the user wants
	printf("How many hidden layers do you want: ");
	scanf("%d", &net->n_layers);
	//add two to allow for input and output layers
	net->n_layers+=2;
	
	//allocate space for the neurons per layer int array 
	net->neurons_per_layer = malloc(sizeof(int)*net->n_layers);
	if(net->neurons_per_layer == NULL) {
		printf("Error #7 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	//set size of each layer
	net->neurons_per_layer[0] = data->features;
	output_binary = num_to_binary(data->n_classes, 0);
	//output layer only requires minimum amount of neurons required to make n_classes in binary
	i=-1;
	while(output_binary[++i] != -1);
	net->neurons_per_layer[net->n_layers-1] = i;
	free(output_binary);
	//Ask for sizes of hidden layers
	for(i=1; i<net->n_layers-1; i++) {
		printf("How many neurons in hidden layer #%d: ", i);
		scanf("%d", &net->neurons_per_layer[i]);
	}
	
	init_weights(net);
	init_biases(net);
	init_activations(net);

	return net;
}

//Allocate space for the weights array based on sizes of layers
void 
init_weights(network_t *net){
	int i, j, k;
	//Using 0 every time so that the result can be replicated (but obviously it could base this off time if it turns out that's what is needed)
	srand(0);
	
	//all of the following is allocating space and checking if it worked
	net->weights = (double***) malloc(sizeof(double**)*net->n_layers-1);
	if (net->weights == NULL) {
		printf("Error #8 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(k=0; k<net->n_layers-1; k++) {
		net->weights[k] = (double**) malloc(sizeof(double*)*net->neurons_per_layer[k+1]);
		if(net->weights[k] == NULL) {
			printf("Error #9 while allocating space.\n");
			exit(EXIT_FAILURE);
		}
		for(i=0; i<net->neurons_per_layer[k+1]; i++) {
			net->weights[k][i] = (double*) malloc(sizeof(double)*net->neurons_per_layer[k]);
			if(net->weights[k][i] == NULL) {
				printf("Error #10 while allocating space.\n");
				exit(EXIT_FAILURE);
			}
			//Give a random value to each weight
			for(j=0; j<net->neurons_per_layer[k]; j++) {
				net->weights[k][i][j] = (rand()%100)/10.0 - 0.5;
			}
		}
	}
	return;
}

//Allocate space for the biases array based on sizes of layers
void 
init_biases(network_t *net){
	int i,j;
	
	//Using 1 just so that the biases don't have the same values as the weights (for no real reason other than that)
	srand(1);
	
	//All of the below is allocating space and checking if it worked
	net->biases = (double**) malloc(sizeof(double*)*net->n_layers);
	if(net->biases == NULL) {
		printf("Error #11 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<net->n_layers; i++) {
		net->biases[i] = (double*) malloc(sizeof(double)*net->neurons_per_layer[i]);
		if(net->biases[i] == NULL) {
			printf("Error #12 while allocating space.\n");
			exit(EXIT_FAILURE);
		}	
		for(j=0; j<net->neurons_per_layer[i]; j++) {
			if(i==0) {
				//these are 0 because the input layer doesn't need a bias (or an activation function in case I forget)
				net->biases[i][j] = 0;
			} else {
				//Otherwise give a random value
				net->biases[i][j] = -(rand()%100)/100.0 - 0.5;
			}
		}
	}
	return;
}

//Use Calloc to set all activations of the neurons to 0 to start off with
void 
init_activations(network_t *net){
	int i;
	
	net->activations = (double**) malloc(sizeof(double*)*net->n_layers);
	if(net->activations == NULL) {
		printf("Error #13 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<net->n_layers; i++) {
		net->activations[i] = (double*) calloc(sizeof(double), net->neurons_per_layer[i]);
		if(net->activations[i] == NULL) {
			printf("Error #14 while allocating space.\n");
			exit(EXIT_FAILURE);
		}
	}

	return;
}

//Initialise the data_t struct 
data_t
*init_data(){
	int i;
	FILE *f;
	data_t *data;

	data = malloc(sizeof(data_t));
	if(data == NULL) {
		printf("Error #1 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	//initialise for use later when setting the actual value
	data->max = -DBL_MAX;
	data->min = DBL_MAX;
	f = get_file_location(data);
	
	//Get the number of possible classes that a point can be given
	printf("How many classifications are there: ");
	scanf("%d", &data->n_classes);
	
	printf("How many features are there per example: ");
	scanf("%d", &data->features);
	
	printf("How many data points are there: ");
	scanf("%d", &data->data_size);
	
	read_data(data, f);
	
	//Allocate space to the batch array which will contain subsets of the data
	data->batch = (double**) malloc(sizeof(double*)*data->batch_size);
	if(data->batch == NULL) {
		printf("Error #2 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<data->batch_size; i++){
		data->batch[i] = (double*) malloc(sizeof(double)*data->features+1);
		if(data->batch[i] == NULL) {
			printf("Error #3 while allocating space.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	fclose(f);
	return data;
}

//Ask for data file location and return the opened file
FILE
*get_file_location(data_t *data){
	char temp_file_loc[MAX_FILE_LOC_LENGTH];
	FILE *f;
	
	//Get the file location and make sure it can be opened
	while(1){
		printf("Enter location of the data file: ");
		scanf("%s", temp_file_loc);
		f = fopen(temp_file_loc, "r");
		if(f != NULL) break;
		printf("\nThis file couldn't be opened.\nTry again.\n");
	}
	
	//Save this to data_t
	data->file_location = malloc(sizeof(char)*(strlen(temp_file_loc)+1));
	if(data->file_location == NULL) {
		printf("Error #4 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	strcpy(data->file_location, temp_file_loc);
	return f;
}

//Gets important information needed for initialising the neural network from the data
void
read_data(data_t *data, FILE *f){
	int i, j;
	char c;
	double temp;
	
	for(i=0; i<data->data_size; i++) {
		for(j=0; j<data->features; j++){
			fscanf(f, "%lf", &temp);
			if(temp > data->max) {
				data->max = temp;
			} 
			if(temp < data->min) {
				data->min = temp;
			}
			fgetc(f);
		}
		while((c = fgetc(f)) != '\n' && c != EOF);
	}
	
	
	//Prompt the user to enter the batch size that will be used. (also recommends factors of the dataset size to use).
	while(1) {
		i=0;
		printf("The following are the factors of your dataset size (");
		for(i=1; i<=data->data_size; i++) {
			if(data->data_size%i == 0){
				printf("%d", i);
				if(i != data->data_size) printf(",");
			}
		}
		printf(")\nEnter batch size: ");
		scanf("%d", &data->batch_size);
		if(data->batch_size <= data->data_size && data->batch_size >= 1) break;
		printf("\nThis is outside  the range of possible values.\n\n");
	}
	data->batches = data->data_size/data->batch_size;
	if(data->data_size%data->batch_size != 0) data->batches++;
	return;
}

//Checks if a value isn't inside an array
int
unique_val(double *array, int length, double val){
	int i;
	for(i=0; i<length; i++) {
		if(array[i] == val) return FALSE;
	}
	return TRUE;
}


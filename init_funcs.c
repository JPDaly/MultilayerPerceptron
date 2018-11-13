#include "header.h"

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
	init_activations(net);

	return net;
}

void 
init_weights(network_t *net){
	int i, j, k;
	//Using 0 every time so that the result can be replicated (but obviously it could base this off time if it turns out that's what is needed)
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
	
	net->biases = (double**) malloc(sizeof(double*)*net->n_layers);
	if(net->biases == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<net->n_layers; i++) {
		net->biases[i] = (double*) malloc(sizeof(double)*net->neurons_per_layer[i]);
		if(net->biases[i] == NULL) {
			printf("Error while allocating space.\n");
			exit(EXIT_FAILURE);
		}	
		for(j=0; j<net->neurons_per_layer[i]; j++) {
			if(i==0) {
				//these are 0 because the input layer doesn't need a bias (or an activation function in case I forget)
				net->biases[i][j] = 0;
			} else {
				net->biases[i][j] = -(rand()%20 + 1);
			}
		}
	}
	return;
}

void 
init_activations(network_t *net){
	int i;
	
	net->activations = (double**) malloc(sizeof(double*)*net->n_layers);
	if(net->activations == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<net->n_layers; i++) {
		net->activations[i] = (double*) calloc(sizeof(double), net->neurons_per_layer[i]);
		if(net->activations[i] == NULL) {
			printf("Error while allocating space.\n");
			exit(EXIT_FAILURE);
		}
	}

	return;
}

data_t
*init_data(){
	int i;
	FILE *f;
	data_t *data;

	data = malloc(sizeof(data_t));
	if(data == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	data->features = 0;
	f = get_file_location(data);
	count_features_datapoints(data, f);
	
	data->batch = (double**) malloc(sizeof(double*)*data->batch_size);
	if(data->batch == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<data->batch_size; i++){
		data->batch[i] = (double*) malloc(sizeof(double)*data->features+1);
		if(data->batch[i] == NULL) {
			printf("Error while allocating space.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	fclose(f);
	return data;
}

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
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	strcpy(data->file_location, temp_file_loc);
	 return f;
}

void 
count_features_datapoints(data_t *data, FILE *f){
	int chars_in_line=0, datapoints=1, features=0, i;
	int *pos_batch_sizes;
	char c;
	
	//Count data points and number of features per point
	while((c = getc(f)) != EOF) {
		chars_in_line++;
		if(c == '\n' && chars_in_line != 1) {
			data->features = features;
			datapoints++;
			chars_in_line = 0;
		} else if(c == '\n' && chars_in_line == 1) {
			datapoints--;
			break;
		} else if(c == ',' && data->features == 0) {
			features++;
		}
	}
	
	//Prompt the user to enter the batch size that will be used. (also recommends factors of the dataset size to use).
	pos_batch_sizes = get_factors(datapoints);
	while(1) {
		i=0;
		printf("Enter batch size.\nThe following are the factors of your dataset size (");
		while(pos_batch_sizes[i++] != -1) {
			if(i!=1) printf(",");
			printf("%d", pos_batch_sizes[i-1]);
		}
		printf("): ");
		scanf("%d", &data->batch_size);
		if(data->batch_size <= datapoints && data->batch_size >= 1) break;
		printf("\nThis is outside the range of possible values.\n\n");
	}	
	free(pos_batch_sizes);
	return;
}
#include "header.h"

void
learn(network_t *net, data_t *data){
	int i,j, points_read=0;
	double **batch, error, *output;
	gradient_t *grad;
	FILE *f;
	
	grad = init_grad(net);
	
	//Make 2D array based on size of decided batches (+1 so that end of batch value can be used)
	batch = malloc(sizeof(double*)*(data->batch_size+1));
	if(batch == NULL) {
		printf("Error #16 while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<data->batch_size+1; i++){
		batch[i] = malloc(sizeof(double)*(data->features+1));
		if(batch[i] == NULL) {
			printf("Error #17 while allocating space.\n");
			exit(EXIT_FAILURE);
		}	
	}
	//Open data file
	f = fopen(data->file_location, "r");
	if(f == NULL) {
		printf("Couldn't open file.\n");
		exit(EXIT_FAILURE);
	}
	//iterate through getting one batch at a time
	for(i=0; i<data->batches; i++){
		error=0.0;
		//get batch
		read_batch(f, data, batch, &points_read);
		//iterate through points in batch
		for(j=0; j<data->batch_size; j++){
			//break early if last batch isn't a full size batch
			if(batch[j][0] == -1.0) break;
			//store the desired output for later
			output = num_to_binary((int)(batch[j][data->features]));
			//Calc output (just updates activations array)
			calc_output(net, batch[j]);
			//printf("calculated %f should be %f\n", net->activations[net->n_layers-1][0], output[0]);
			//calculate error
			error += calc_error(net->neurons_per_layer[net->n_layers-1], net->activations[net->n_layers-1], output);
			back_propagation(net, grad, output, j);
		}
		
		//take grads off values
		grad_descent(net, grad, j);
		error /= j; //average of error
		printf("Error for batch #%d = %f\n", i, error);
	}
	
	fclose(f);
	return;
}


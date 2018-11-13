#define MAX_FILE_LOC_LENGTH 200

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	int n_layers;
	int *neurons_per_layer;
	double **activations;
	double ***weights;
	double **biases;
} network_t;

typedef struct {
	int data_size;
	int batch_size;
	int features;
	char *file_location;
	double **batch;
} data_t;


//Initial functions
network_t *init_network();
void init_weights(network_t *net);
void init_biases(network_t *net);
void init_activations(network_t *net);
data_t *init_data();
FILE *get_file_location(data_t *data);
void count_features_datapoints(data_t *data, FILE *f);

//Feed forward functions
void calc_output(network_t *net, double *input);
double calc_error(int length, double *output, double *desired_output);
void read_batch(FILE *data_file, data_t *data);

//For all
double sigmoid(double in);
int *get_factors(int num);
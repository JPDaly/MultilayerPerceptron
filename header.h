#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define TRUE 1
#define FALSE 0
#define INIT_N_CLASSES 20
#define RAND_BIAS_MAX 1
#define RAND_WEIGHT_MAX 1
#define LEARNING_RATE 1
#define MAX_FILE_LOC_LENGTH 200

typedef struct {
	int n_layers;
	int *neurons_per_layer;
	double **activations;
	double **biases;
	double ***weights;
} network_t;

typedef struct {
	int data_size;
	int batch_size;
	int features;
	int batches;
	int n_classes;
	double max;
	double min;
	char *file_location;
	double **batch;
} data_t;

typedef struct {
	double ***weights;
	double **biases;
	double **activations;
}gradient_t;


//Initial functions
network_t *init_network(data_t *data);
void init_weights(network_t *net);
void init_biases(network_t *net);
void init_activations(network_t *net);
data_t *init_data();
FILE *get_file_location(data_t *data);
void read_data(data_t *data, FILE *f);
int unique_val(double *array, int length, double val);
void normalise_data(FILE *f);

//Feed forward functions
void calc_output(network_t *net, double *input);
double calc_error(int length, double *output, double *desired_output);
void read_batch(FILE *data_file, data_t *data, double **batch, int *points_read);

//Back propagation
void back_propagation(network_t *net, gradient_t *grad, double *output, int batch_example);
double sig_derivative(double in);
gradient_t *init_grad(network_t *net);
void grad_descent(network_t *net, gradient_t *grad, int n_examples);

//learn (calls forward and back functions)
void learn(network_t *net, data_t *data);

//data manipulation
void prepare_data(data_t *data);
void normalise(double **file_content, double max, double min);

//For all
double sigmoid(double in);
double *num_to_binary(int num, int max_digits);
void print_network(network_t *net);




//this function should include all declarations of functions and constants that are only needed for initialising the program.
//aka only those that init_funcs needs

#include "globals.h"

network_t *init_network();
void init_weights(network_t *net);
void init_biases(network_t *net);
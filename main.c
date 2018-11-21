#include "header.h"
#include <time.h>

/*
set PATH=c:/MinGW/bin;%PATH% 
For compiling:
gcc -Wall -o main main.c globals.c forward_funcs.c learn.c init_funcs.c backward_funcs.c data_manip.c 
*/

int
main(int argc, char *argv[]){
	clock_t end, start;
	network_t *net;
	data_t *data;
	
	//inititalising
	data = init_data();
	net = init_network(data);
	prepare_data(data);
 
	
	//Start timing
	start = clock();
	
	//Before training print
	print_network(net);
	
	//Learn
	learn(net, data);
	
	//train
	
	
	//Stop timing
	end = clock();

	//Print values in network
	print_network(net);
	
	//Print runtime
	printf("\n------ Runtime = %.3f seconds ------\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("C:\\Users\\JordanDaly\\Documents\\Programming\\MultilayerPerceptron\\Resources\\data.txt\n");
	
	return 0;
}


/*
To compile all the files together use the following:
	gcc -Wall -o main main.c init_funcs.c
You don't need to include the header files.
You can also continue to add more .c files to the end of this as you need/use them.
*/

//The following are here because I don't think they have anything to do with initialising or feed forward









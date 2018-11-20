#include "header.h"

void 
prepare_data(data_t *data){
	int i,j;
	FILE *f;
	double **file_content
	
	f = fopen(data->file_location, 'r');
	if(f == NULL) {
		printf("Couldn't open file.\n");
		exit(EXIT_FAILURE);
	}
	
	file_content = malloc(sizeof(double*)*data->data_size);
	if(file_content == NULL) {
		printf("Error. No space for file_content\n");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<data->data_size; i++){
		file_content[i] = malloc(sizeof(double)*(data->features+1));
		if(file_content[i] == NULL){
			printf("Error. No space for file_content[%d]\n", i);
			exit(EXIT_FAILURE);
		}
	}
	for(i=0; i<data->data_size; i++) {
		for(j=0; j<data->features+1; j++) {
			
		}
	}
	
	
	return;
}



void 
normalise(double **file_content, double max, double min){

	return;
}
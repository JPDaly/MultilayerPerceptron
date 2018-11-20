#include "header.h"

/*
At the moment this function reads in all the values from the file and saves them into an array.
I don't think this would be ideal for much larger datasets.
For that reason I chose to do this in this function rather than in the read_data() function so that if in the future I decide to
	change the way this is done it will be easier.
*/

void 
prepare_data(data_t *data){
	int i,j;
	char c;
	double **file_content
	FILE *f;
	
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
			scanf("%lf", file_content[i][j]);
			file_content[i][j] = ((file_content[i][j]-data->max)/(data->max - data->min)) - 0.5; //normalising
			//then need to print this to a new document
			fgetc(f);
		}
		while((c=fgetc(f)) != '\n' && c != EOF);
	}
	
	return;
}

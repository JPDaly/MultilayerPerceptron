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
	double temp, label;
	FILE *f, *output_f;
	
	f = fopen(data->file_location, "r");
	if(f == NULL) {
		printf("Couldn't open file.\n");
		exit(EXIT_FAILURE);
	}
	
	output_f = fopen("Resources/normalised_data.txt", "w");
	if(output_f == NULL) {
		printf("Error couldn't open normalised_data.txt.\n");
		exit(EXIT_FAILURE);
	}
	
	
	//Normalisation
	for(i=0; i<data->data_size; i++) {
		for(j=0; j<data->features+1; j++) { 
			fscanf(f, "%lf", &temp); 
			if(j == 0) { 
				label = temp; 
			} else { 
				fprintf(output_f,"%f", ((temp-data->min)/(data->max - data->min)) - 0.5); //normalising 
			} 
			c = fgetc(f);
			if(j!=data->features && j != 0) fprintf(output_f,"%c", c); 
		} 
		fprintf(output_f,",%f\n", label); 
	} 
	
	fclose(f);
	fclose(output_f);
	
	return;
}

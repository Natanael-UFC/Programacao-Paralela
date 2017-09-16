#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double ** matrix_1;
double ** matrix_2;
double ** matrix_3;

typedef struct {
	int fromidx, lenght, columns;
} thread_arg, *ptr_thread_arg;

double ** allocate_matrix(int num_rows, int num_columns){
	double ** matrix, *tmp;
	int i = 0;

	if(num_rows < 1 || num_columns < 1){
		printf("Error: Parametro invalido !\n");
		return(NULL);
	}

    tmp = (double *) malloc (sizeof(double ) * num_rows * num_columns);
    matrix = (double **) malloc (sizeof(double *) * num_rows);

    if(matrix == NULL){
		printf("Error: Memoria insuficiente **\n");
		return(NULL);
	}
    for (i = 0; i < num_rows; i++)
        matrix[i] = &tmp[i * num_columns];
    return matrix;
}

double ** release_matrix(double ** matrix, int num_rows, int num_columns){
	int i = 0;
	if(matrix == NULL) return (NULL);

	if(num_rows < 1 || num_columns < 1){
		printf("Error: Parametro invalido !\n");
		return matrix;
	}

	free(matrix);
	return(NULL);
}

void read_matrix(double ** matrix, int num_rows, int num_columns){
	int i = 0, j = 0;

	for(i = 0; i < num_rows; i++)
		for(j = 0; j < num_columns; j++)
			matrix[i][j] = 1.0;
}

void *func_mult_matx(void *arg){
	ptr_thread_arg argument = (ptr_thread_arg)arg;
	int i, j, k, endidx;

	endidx = argument->fromidx + argument->lenght;

	for(i = 0; i < argument->columns; i++){
		printf("%d\n", i);
		for(j = argument->fromidx; j < endidx; j++){
			for(k = 0; k < argument->columns; k++){
				matrix_3[i][j] = matrix_3[i][j] + (matrix_1[i][k] * matrix_2[k][j]);
			}
		}
	}
/*
	if(my_data->id_1 == 1){
		tam_th = (tam / 2) - 1;
		for(i = 0; i <= tam_th; i++){
			for(j = 0; j < tam; j++){
				for (k = 0; k <= tam_th; k++){
					matriz_3[i][j] = matriz_3[i][j] + (matriz_1[i][k] * matriz_2[k][j]);
				}
			}
		}
	}

    if(my_data->id_2 == 2){
		tam_th2 = (tam / 2);
		for(i = tam_th2; i < tam; i++){
			for(j = 0; j < tam; j++){
				for (k = tam_th2; k < tam; k++){
					matriz_3[i][j] = matriz_3[i][j] + (matriz_1[i][k] * matriz_2[k][j]);
				}
			}
		}
	}
	*/
}

void print_out(double ** matrix, int num_rows, int num_columns){
	int i = 0, j = 0;
	for(i = 0; i < num_rows; i++){
		for(j = 0; j < num_columns; j++){
			printf("\t%0.1f", matrix[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]){

	int num_rows = 0, num_columns = 0, num_threads = 0, i, lenght;

	num_rows = atoi(argv[1]);
	num_columns = num_rows;
	num_threads = atoi(argv[2]);

	pthread_t threads[num_threads];
	thread_arg arguments[num_threads];

	matrix_1 = allocate_matrix(num_rows, num_columns);
	matrix_2 = allocate_matrix(num_rows, num_columns);
	matrix_3 = allocate_matrix(num_rows, num_columns);

	read_matrix(matrix_1, num_rows, num_columns);
	read_matrix(matrix_2, num_rows, num_columns);

	lenght = num_rows / num_threads;

	for(i = 0; i < num_threads; i++){
		arguments[i].fromidx = i * lenght;
		arguments[i].lenght = lenght;
		arguments[i].columns = num_columns;
		pthread_create(&(threads[i]), NULL, func_mult_matx, &(arguments[i]));
	}
	for(i = 0; i < num_threads; i++){
		pthread_join(threads[i], NULL);
	}

	print_out(matrix_1, num_rows, num_columns);
	printf("\n");
	print_out(matrix_2, num_rows, num_columns);
	printf("\n");
	print_out(matrix_3, num_rows, num_columns);

	release_matrix(matrix_1, num_rows, num_columns);
	release_matrix(matrix_2, num_rows, num_columns);
	release_matrix(matrix_3, num_rows, num_columns);

	pthread_exit(NULL);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double ** matriz_1;
double ** matriz_2;
double ** matriz_3;

struct data{
	int tam;
	int id_1;
	int id_2;
};

double ** aloca_matriz(int n_linhas, int n_colunas){
	double ** matriz, *tmp;
	int i = 0;

	if(n_linhas < 1 || n_colunas < 1){
		printf("Error: Parametro invalido !\n");
		return(NULL);
	}

        tmp = (double *) malloc (sizeof(double ) * n_linhas * n_colunas);
        matriz = (double **) malloc (sizeof(double *) * n_linhas);

        if(matriz == NULL){
		printf("Error: Memoria insuficiente **\n");
		return(NULL);
	}
        for (i = 0; i < n_linhas; i++)
           matriz[i] = &tmp[i * n_colunas];

        return matriz;
}

double ** libera_matriz(double ** matriz, int n_linhas, int n_colunas){
	int i = 0;

	if(matriz == NULL) return (NULL);

	if(n_linhas < 1 || n_colunas < 1){
		printf("Error: Parametro invalido !\n");
		return matriz;
	}

	free(matriz);
	return(NULL);
}

void le_matriz(double ** matriz, int n_linhas, int n_colunas){
	int i = 0, j = 0;

	for(i = 0; i < n_linhas; i++)
		for(j = 0; j < n_colunas; j++)
			matriz[i][j] = 1.0;
}

void *mult(void *arg){

	struct data *my_data;

	my_data = (struct data *) arg;

	int i, j, k, tam_th, tam_th2, tam;

	tam = my_data->tam;

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
}

void imprime(double ** matriz, int n_linhas, int n_colunas){
	int i = 0, j = 0;
	for(i = 0; i < n_linhas; i++){
		for(j = 0; j < n_colunas; j++){
			printf("\t%0.1f", matriz[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]){

	int linhas = 0, colunas = 0;
	struct data values;

	pthread_t thread_1;
	pthread_t thread_2;

	linhas = atoi(argv[1]);
	colunas = atoi(argv[1]);

	matriz_1 = aloca_matriz(linhas, colunas);
	matriz_2 = aloca_matriz(linhas, colunas);
	matriz_3 = aloca_matriz(linhas, colunas);

	values.tam = linhas;
	values.id_1 = 1;
	values.id_2 = 2;

	le_matriz(matriz_1, linhas, colunas);
	le_matriz(matriz_2, linhas, colunas);

	pthread_create(&thread_1, NULL, mult, (void *)(&values));
	pthread_create(&thread_2, NULL, mult, (void *)(&values));

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	imprime(matriz_1, linhas, colunas);
	printf("\n");
	imprime(matriz_2, linhas, colunas);
	printf("\n");
	imprime(matriz_3, linhas, colunas);

	libera_matriz(matriz_1, linhas, colunas);
	libera_matriz(matriz_2, linhas, colunas);
	libera_matriz(matriz_3, linhas, colunas);

	pthread_exit(NULL);

	return 0;
}

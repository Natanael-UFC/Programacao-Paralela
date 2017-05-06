#include <stdio.h>
#include <stdlib.h>

double ** aloca_matriz(int n_linhas, int n_colunas){
	double ** matriz;
	int i = 0;

	if(n_linhas < 1 || n_colunas < 1){
		printf("Error: Parametro invalido !\n");
		return(NULL);
	}

	matriz = (double **) calloc (n_colunas, sizeof(double *));

	if(matriz == NULL){
		printf("Error: Memoria insuficiente **\n");
		return(NULL);
	}

	for(i = 0; i < n_colunas; i++){
		matriz[i] = (double *) calloc(n_linhas, sizeof(double));
		if(matriz[i] == NULL){
			printf("Error: Memoria insuficiente **\n");
		}
	}
	return matriz;
}

double ** libera_matriz( double ** matriz, int n_linhas, int n_colunas){
	int i = 0;

	if(matriz == NULL) return (NULL);

	if(n_linhas < 1 || n_colunas < 1){
		printf("Error: Parametro invalido !\n");
		return matriz;
	}

	for(i = 0; i < n_colunas; i++) free(matriz[i]);

	free(matriz);
	return(NULL);
}

void le_matriz(double ** matriz, int n_linhas, int n_colunas){
	int i = 0, j = 0;

	for(i = 0; i < n_linhas; i++){
		for(j = 0; j < n_colunas; j++){
			matriz[i][j] = 1.0;
		}
	}
}

void multiplica(double ** matriz_1, double ** matriz_2, double ** matriz_final, int qntd){
	int i = 0, j = 0, k = 0;
	for(i = 0; i < qntd; i++){
		for(j = 0; j < qntd; j++){
			for(k = 0; k < qntd; k++){
				matriz_final[i][j] = matriz_final[i][j] + (matriz_1[i][k] * matriz_2[k][j]);
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

	linhas = atoi(argv[1]);
	colunas = atoi(argv[1]);

	double ** matriz_1 = aloca_matriz(linhas, colunas);
	double ** matriz_2 = aloca_matriz(linhas, colunas);
	double ** matriz_3 = aloca_matriz(linhas, colunas);

	le_matriz(matriz_1, linhas, colunas);
	le_matriz(matriz_2, linhas, colunas);

	multiplica(matriz_1, matriz_2, matriz_3, linhas);

	imprime(matriz_1, linhas, colunas);
	printf("\n");
	imprime(matriz_2, linhas, colunas);
	printf("\n");
	imprime(matriz_3, linhas, colunas);

	libera_matriz(matriz_1, linhas, colunas);
	libera_matriz(matriz_2, linhas, colunas);
	libera_matriz(matriz_3, linhas, colunas);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    int quadros,numero_referencia,paginas_faltantes = 0;

    scanf("%d", &quadros);
    scanf("%d", &numero_referencia);

    int *quadros_vetor = malloc(quadros * sizeof(int));

    for(int i = 0; i < quadros; i++) quadros_vetor[i] = -1;

    for(int i = 0; i < numero_referencia; i++) {
        int controle = 0;
        int referencia = 0;
        scanf("%d", &referencia);

        for(int j = 0; j < quadros; j++) {
            if(quadros_vetor[j] == referencia) {
                controle = 1;
            }
        }
        
        if(controle == 0) {
            int vetor_auxiliar[quadros];

            for(int i = quadros - 1; i > -1; i--) {
                vetor_auxiliar[i] = quadros_vetor[i + 1];
            }

            vetor_auxiliar[quadros - 1] = referencia;

            for(int j = 0; j < quadros; j++) {
                quadros_vetor[j] = vetor_auxiliar[j];
            }

            paginas_faltantes++;
        }
    }

    printf("%d", paginas_faltantes);

    return 0;
}
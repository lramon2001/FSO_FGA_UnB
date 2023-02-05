#include <stdio.h>
#include <stdlib.h>



int pesquisar(int chave, int *fr, int tamanho) {

    for(int i = 0; i < tamanho; i++) {
        if(fr[i] == chave) return 1;
    }
    return 0;
}

int previsao(int *paginas, int *fr, int numero_de_paginas, int indice, int tamanho) {
     int o_mais_longe = indice;
    int res = -1;
   
    for(int i = 0; i < tamanho; i++) {
        int j = 0;
        for(j = indice; j < numero_de_paginas; j++) {
            if(fr[i] == paginas[j]) {
                if(j > o_mais_longe) {
                    o_mais_longe = j;
                    res = i;
                }
                break;
            }
        }

        if(j == numero_de_paginas) {
            return i;
        }
    }

    return (res == -1) ? 0 : res;
} 

int pagina_otima(int *paginas, int numero_de_paginas, int numero_de_quadros) {
    int fr[numero_de_quadros];
    int hit = 0;
    int indice = 0;

    for(int i = 0; i < numero_de_quadros; i++) fr[i] = -1;

    for(int i = 0; i < numero_de_paginas; i++) {
        if(pesquisar(paginas[i], fr, numero_de_quadros)) {
            hit++;
            continue;
        }

        if(indice < numero_de_quadros) fr[indice++] = paginas[i];
        else {
            int j = previsao(paginas, fr, numero_de_paginas, i + 1, numero_de_quadros);
            fr[j] = paginas[i];
        }
    }

    printf("%d\n", numero_de_paginas - hit);
}


int main() {
    int numero_de_quadros = 0,numero_de_paginas =0;

    scanf("%d", &numero_de_quadros);
    scanf("%d", &numero_de_paginas);

    int *paginas = malloc(numero_de_paginas * sizeof(int));

    for(int i = 0; i < numero_de_paginas; i++) scanf("%d", &paginas[i]);

    pagina_otima(paginas, numero_de_paginas, numero_de_quadros);
}
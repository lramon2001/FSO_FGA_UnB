#include<stdio.h>

int encontraLRU(int tempo[], int n) {
  int i, minimo = tempo[0], posicao = 0;

  for (i = 1; i < n; ++i) {
    if (tempo[i] < minimo) {
      minimo = tempo[i];
      posicao = i;
    }
  }
  return posicao;
}

int main() {
  int numero_de_quadros, numero_de_paginas, quadros[10000], paginas[10000], contador = 0, tempo[100], bandeira1, bandeira2, i, j, posicao, faltas = 0;
  
  scanf("%d", & numero_de_quadros);
  
  scanf("%d", & numero_de_paginas);
  
  for (i = 0; i < numero_de_paginas; ++i)scanf("%d", & paginas[i]);

  for (i = 0; i < numero_de_quadros; ++i) quadros[i] = -1;

  for (i = 0; i < numero_de_paginas; ++i) {
    bandeira1 = bandeira2 = 0;

    for (j = 0; j < numero_de_quadros; ++j) {
      if (quadros[j] == paginas[i]) {
        contador++;
        tempo[j] = contador;
        bandeira1 = bandeira2 = 1;
        break;
      }
    }

    if (bandeira1 == 0) {
      for (j = 0; j < numero_de_quadros; ++j) {
        if (quadros[j] == -1) {
          contador++;
          faltas++;
          quadros[j] = paginas[i];
          tempo[j] = contador;
          bandeira2 = 1;
          break;
        }
      }
    }

    if (bandeira2 == 0) {
      posicao = encontraLRU(tempo, numero_de_quadros);
      contador++;
      faltas++;
      quadros[posicao] = paginas[i];
      tempo[posicao] = contador;
    }

  }
  printf("%d", faltas);

  return 0;
}
// The longest common subsequence in C

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "energia.h" 

int i, j, m, n, LCS_table[5000][5000];
char S1[5000];
char S2[5000];
char b[5000][5000];

void lcsAlgo() {

  FILE* inputFile1 = fopen("input1.txt", "r");
  FILE* inputFile2 = fopen("input2.txt", "r");

  fgets(S1, 5000, inputFile1);
  fgets(S2, 5000, inputFile2);


  rapl_init();
  start_rapl_sysfs(); // (3) Iniciar a contagem de consumo de energia
  clock_t t = clock(); // Iniciar a contagem de tempo

  m = strlen(S1);
  n = strlen(S2);

  // Filling 0's in the matrix
  for (i = 0; i <= m; i++)
    LCS_table[i][0] = 0;
  for (i = 0; i <= n; i++)
    LCS_table[0][i] = 0;

  // Building the mtrix in bottom-up way
  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++) {
      if (S1[i - 1] == S2[j - 1]) {
        LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
      } else if (LCS_table[i - 1][j] >= LCS_table[i][j - 1]) {
        LCS_table[i][j] = LCS_table[i - 1][j];
      } else {
        LCS_table[i][j] = LCS_table[i][j - 1];
      }
    }

  int index = LCS_table[m][n];
  char lcsAlgo[index + 1];
  lcsAlgo[index] = '\0';

  int i = m, j = n;
  while (i > 0 && j > 0) {
    if (S1[i - 1] == S2[j - 1]) {
      lcsAlgo[index - 1] = S1[i - 1];
      i--;
      j--;
      index--;
    }

    else if (LCS_table[i - 1][j] > LCS_table[i][j - 1])
      i--;
    else
      j--;
  }

  // Printing the sub sequences
  printf("S1 : %s \nS2 : %s \n", S1, S2);
  printf("LCS: %s", lcsAlgo);

  t = clock() - t; // Finalizar contagem do tempo
  double energy = end_rapl_sysfs();   // (5) Finalizar a contagem dos contadores de energia
  double tempo = ((double)t)/CLOCKS_PER_SEC; // transforma tempo para segundos
  printf("\nTempo de execucao em segundos: %.20f\n", tempo);
  printf("Energia consumida em Joules:   %.20f\n", energy); // (6) imprimir consumo de energia em Joules
}

int main() {
  lcsAlgo();
  printf("\n");
}
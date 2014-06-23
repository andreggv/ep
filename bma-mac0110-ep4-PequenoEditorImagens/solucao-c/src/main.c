#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***  Definição de constantes ***/
#define MAXLIN       400      /* Número máximo de linhas para matrizes */
#define MAXCOL       400      /* Número máximo de colunas para matrizes */
#define MAXVIZ       9        /* Número máximo de vizinhos */ 
#define MAXNOMEARQ   81       /* Tamanho máximo (80) para nome de arquivo */

/*** Protótipos das funcoes ***/

void le_arquivopgm(char nomearq[], int a[][MAXCOL], int *lin, int *col,
      int *valmaior);

void escreve_arquivopgm(char nomearq[], int a[][MAXCOL], int lin, int col,
      int valmaior);

void escreve_matriz_tela(int a[][MAXCOL], int linhas, int colunas, int maior_valor);

void negativo(int a[][MAXCOL], int linhas, int colunas, int *maior);

void rebate_horizontal(int a[][MAXCOL], int linhas, int colunas);

void rebate_vertical(int a[][MAXCOL], int linhas, int colunas);

void rotacao(int a[][MAXCOL], int *lin, int *col);

void filtro_mediana(int a[][MAXCOL], int linhas, int colunas, int *maior);

void copia_matriz(int a[][MAXCOL], int b[][MAXCOL], int linhas, int colunas);

int maior_valor_matriz(int a[][MAXCOL], int linhas, int colunas);

int determina_mediana(int a[][MAXCOL], int linhas, int colunas, int i, int j);

void ordena(int v[], int n);


int main()
{
   int img[MAXLIN][MAXCOL];         /* Matriz que representa uma imagem */
   int nlin;                        /* Número de linhas da imagem */
   int ncol;                        /* Número de colunas da imagem */ 
   int maior_valor;                 /* Maior tonalidade de cinza da imagem */
   char inic_nome_arq[MAXNOMEARQ];  /* Nome de arquivo sem extensao .pgm */
   char codigo;                     /* Código da funcao de transformacao */

/*le_arquivo_pgm(inic_nome_arq, imagem, &nlinhas, &ncolunas, &maior_valor);

escreve_matriz_tela(imagem, nlinhas, ncolunas, maior_valor);

printf("\nLista das possiveis funcoes de transformacao e seus codigos:\n\n");
printf("n - negativo\n");
printf("h - rebater na horizontal\n");
printf("v - rebater na vertical\n");
printf("r - rotacao\n");
printf("m - filtro da mediana\n");

printf("\nDigite o codigo da funcao que deseja aplicar : "); 
scanf(" %c", &codigo);

switch (codigo)  {

  case 'n' : * COMPLETE ... *

  case 'h' :rebate_horizontal(imagem, nlinhas, ncolunas);
            printf("\nFuncao REBATE NA HORIZONTAL realizada com sucesso.\n");
            strcat(inic_nome_arq, "-h"); 
 	      break;

  case 'v' : * COMPLETE ... *

  case 'r' : * COMPLETE ... *

  case 'm' : * COMPLETE ... *

  default: printf("\nCodigo invalido\n");
   
}

escreve_matriz_tela(imagem, nlinhas, ncolunas, maior_valor);

escreve_arquivo_pgm(inic_nome_arq, imagem, nlinhas, ncolunas, maior_valor);*/

return 0;

}


/* Definicoes das funcoes descritas acima */


/* Escreva um comentario para esta funcao ... */
void le_arquivo_pgm(char inic_nome_arq[], int a[][MAXCOL],
                    int *lin, int *col, int *maior)
{
 FILE *arqentra;
 char chave[10];
 int i, j, aux, linhas, colunas, maior_valor;
 char nome_arq[MAXNOMEARQ];

 printf("Digite o nome de um arquivo (com uma imagem) sem extensao .pgm : ");
 scanf("%s", inic_nome_arq);
 
 /* define o nome completo do arquivo */
 strcpy(nome_arq, inic_nome_arq);  /* copia inic_nome_arq para nome_arq */
 strcat(nome_arq, ".pgm");         /* concatena ".pgm" no final de nome_arq */
 
 /* abre o arquivo para ler */
 arqentra = fopen(nome_arq, "r");
 if (arqentra == NULL)  {
   printf("Erro na abertura do arquivo %s\n", nome_arq);
   exit (EXIT_FAILURE);
 }

 /* le informacoes iniciais da imagem */
  aux = fscanf(arqentra, "%s", chave);
  if (aux != 1)  {
    printf("Erro na leitura do arquivo %s \n", nome_arq);
    exit (EXIT_FAILURE);
  }
  if (strcmp(chave,"P2") != 0)  {
    printf("Formato (%s) desconhecido\n", chave);
    exit (EXIT_FAILURE);
  }
  aux = fscanf(arqentra, "%d %d %d", &colunas, &linhas, &maior_valor);
  if (aux != 3)  {
    printf("Formato incorreto\n");
    exit (EXIT_FAILURE);
  }

  /* le os elementos da  matriz (imagem)  */
  for (i = 0; i < linhas; i++)  {
     for (j = 0; j < colunas; j++)  {
        fscanf(arqentra, "%d", &a[i][j]);
     }
  }

  fclose(arqentra);   /* fecha arquivo */
   
  *lin = linhas;
  *col = colunas;
  *maior = maior_valor;

  printf("\nAs informacoes da imagem no arquivo %s foram obtidas com sucesso.\n", 
         nome_arq);

}


/* Escreva um comentario para esta funcao ... */
void escreve_arquivo_pgm(char inic_nome_arq[], int a[][MAXCOL],
                         int linhas, int colunas, int maior_valor)
{
 FILE *arqsai;
 int i, j, k;
 char nome_arq[MAXNOMEARQ];

 /* define o nome completo do arquivo */
 strcpy(nome_arq, inic_nome_arq);  /* copia inic_nome_arq para nome_arq */
 strcat(nome_arq, ".pgm");         /* concatena ".pgm" no final de nome_arq */

 /* abre o arquivo para escrever */
 arqsai = fopen(nome_arq, "w");
 if (arqsai == NULL)  {
   printf("Erro na abertura do arquivo %s\n", nome_arq);
   exit (EXIT_FAILURE);
 }

 /* escreve informacoes iniciais da imagem */
 fprintf(arqsai, "P2\n");
 fprintf(arqsai, "%d %d\n%d\n", colunas, linhas, maior_valor);

 /* escreve os elementos da matriz (imagem) */
 for (i = 0; i < linhas; i++)  {
    for (j = 0; j < colunas; )  {
       for (k = 0; j < colunas && k < 15; j++, k++) 
          fprintf(arqsai, "%4d", a[i][j]);
       fprintf(arqsai, "\n");
    }
 }

 fclose(arqsai);   /* fecha arquivo */

 printf("\nArquivo %s (com a imagem transformada) foi criado com sucesso.\n\n", 
        nome_arq);
 

}


/* ESCREVA AS DEFINICOES DAS OUTRAS FUNCOES  ... */

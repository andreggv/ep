#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***  Definição de constantes ***/

#define MAXLIN       400      /* Número máximo de linhas para matrizes */
#define MAXCOL       400      /* Número máximo de colunas para matrizes */
#define MAXVIZ       9        /* Número máximo de vizinhos */ 
#define MAXNOMEARQ   100      /* Tamanho máximo (80) para nome de arquivo */

/*** Protótipos das funcoes ***/

void le_arqpgm(char imgnome[], int img[][MAXCOL], int *lin, int *col, int *valmaior);

void escreve_arqpgm(char imgnome[], int img[][MAXCOL], int lin, int col, int valmaior);

/*void escreve_matriztela(int [][MAXCOL], int lin, int col, int valmaior);

void negativo(int a[][MAXCOL], int lin, int col, int *maior);

void rebate_horizontal(int a[][MAXCOL], int linhas, int colunas);

void rebate_vertical(int a[][MAXCOL], int linhas, int colunas);

void rotacao(int a[][MAXCOL], int *lin, int *col);

void filtro_mediana(int a[][MAXCOL], int linhas, int colunas, int *maior);

void copia_matriz(int a[][MAXCOL], int b[][MAXCOL], int linhas, int colunas);

int maior_valor_matriz(int a[][MAXCOL], int linhas, int colunas);

int determina_mediana(int a[][MAXCOL], int linhas, int colunas, int i, int j);

void ordena(int v[], int n);
*/

int main()
{
   int img[MAXLIN][MAXCOL];         /* Matriz que representa uma imagem */
   int nlin;                        /* Número de linhas da imagem */
   int ncol;                        /* Número de colunas da imagem */ 
   int valmaior;                    /* Maior tonalidade de cinza da imagem */
   char imgnome[MAXNOMEARQ];        /* Nome de arquivo sem extensao .pgm */
   /*char codigo;                     * Código da funcao de transformacao */

   le_arqpgm(imgnome, img, &nlin, &ncol, &valmaior);

   escreve_arqpgm(imgnome, img, nlin, ncol, valmaior);

/*escreve_matriz_tela(imagem, nlinhas, ncolunas, maior_valor);

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


/* Esta função lê um arquivo de entrada, através do nome que o usuário digitar,
 * e grava na matriz dada. Os parâmetros que devem ser dados são:
 *    - imgnome  : vetor que armazena o nome (sem a extensão) do arquivo a ser
 *                 lido
 *    - img      : matriz que armazena os dados do arquivo
 *    - lin      :  ponteiro para o inteiro que armazena o número de linhas da
 *                 matriz
 *    - col      : ponteiro para o inteiro que armazena o número de colunas da
 *                 matriz
 *    - valmaior : pontiro para o inteiro que armazena o valor máximo encontrado
 *                 no arquivo
 */
void le_arqpgm(char imgnome[], int img[][MAXCOL], int *lin, int *col, int *valmaior)
{
   char arqnome[MAXNOMEARQ];  /* Nome completo do arquivo de entrada */
   FILE *arq;                 /* Ponteiro para o arquivo de entrada */
   char chave[10];            /* Código chave do arquivo pgm */
   int i, j;                  /* Variáveis contadoras */

   /* Inicia variáveis */
   for (i = 0; i < MAXNOMEARQ; i++)
      arqnome[i] = '\0';
   arq = NULL;
   for (i = 0; i < MAXLIN; i++)
      for (j = 0; j < MAXCOL; j++)
         img[i][j] = -1;

   /* Pega o nome do arquivo dentro do diretório entrada */
   printf("Digite o nome do arquivo a ser processado sem extensao .pgm: ");
   scanf("%s", imgnome);
   strcat(arqnome, "entrada/");
   strcat(arqnome, (const char *) imgnome);
   strcat(arqnome, ".pgm");
 
   /* Tenta abrir o arquivo */
   arq = fopen(arqnome, "r");
   if (arq == NULL)  {
      printf("Erro na abertura do arquivo '%s'. ", arqnome);
      printf("O arquivo '%s.pgm' está no diretório 'entrada/'?\n", imgnome);
      exit (EXIT_FAILURE);
   }

   /* Lê a chave do arquivo */
   if (fscanf(arq, "%s", chave) != 1)  {
      printf("Erro na leitura do arquivo '%s'.\n", arqnome);
      exit (EXIT_FAILURE);
   }
   if (strcmp(chave,"P2") != 0)  {
      printf("Formato do arquivo '%s' desconhecido.\n", chave);
      exit (EXIT_FAILURE);
   }

   /* Lê número de linha e coluna da imagem */
   if (fscanf(arq, "%d %d\n", lin, col) != 2)  {
      printf("Erro ao ler número de linhas e colunas da imagem do arquivo ");
      printf("'%s'.\n", arqnome);
      exit (EXIT_FAILURE);
   }

   /* Verifica se a imagem é mto grande */
   if (*lin > MAXLIN || *col > MAXCOL) {
      printf("A imagem do arquivo '%s' é muito grande para ", arqnome);
      printf("ser processada. O tamanho máximo suportador é: ");
      printf("%d linhas x %d colunas\n", MAXLIN, MAXCOL);
      exit (EXIT_FAILURE);
   }


   /* Lê o maior valor de cor da imagem */
   if (fscanf(arq, "%d\n", valmaior) != 1)  {
      printf("Erro ao ler o maior valor da cor da imagem ");
      printf("do arquivo '%s'.\n", arqnome);
      exit (EXIT_FAILURE);
   }

   /* Lê os valores de cada linha de pixel da coluna e armazena na matriz dada */
   for (i = 0; i < *lin; i++)
      for (j = 0; j < *col; j++)
         if (fscanf(arq, "%d", &img[i][j]) != 1) {
            printf("Erro ao ler o arquivo. Ele deve estar corrompido.");
            exit (EXIT_FAILURE);
         }

   /* Fecha arquivo de entrada */
   fclose(arq);

   /* Imprime mensagem que informa que o arquivo foi carregado com sucesso */
   printf("\nO arquivo '%s' foi carregado com sucesso.\n", arqnome);

   return;
}


/* Encreve a matriz que representa a imagem em um arquivo .pgm no diretório
 * saída. Os parâmetros que devem ser dados são:
 *    - imgnome  : nome da imagem.
 *    - img      : matriz que contém os valores dos pixels da imagem.
 *    - lin      : número de linhas da imagem.
 *    - col      : coluna da imagem.
 *    - valmaior : maior valor de um pixel da imagem
 */
void escreve_arqpgm(char imgnome[], int img[][MAXCOL], int lin, int col, int valmaior)
{
   char arqnome[MAXNOMEARQ];  /* Nome completo do arquivo de saída */
   FILE *arq;                 /* Ponteiro para o arquivo de saída */
   int i, j;                  /* Variáveis contadoras */
   int ncharlin, nchar;       /* Controla o número de caracteres na linha */
   int valpixel;              /* Valor do pixel a ser gravado */

   /* Inicia variáveis */
   for (i = 0; i < MAXNOMEARQ; i++)
      arqnome[i] = '\0';
   arq = NULL;

   /* Pega nome completo do arquivo de saída */
   strcat(arqnome, "saida/");
   strcat(arqnome, (const char *) imgnome);
   strcat(arqnome, ".pgm");

   /* Abre arquivo de saída */
   arq = fopen(arqnome, "w");
   if (arq == NULL)  {
      printf("Erro ao tentar escrever '%s'. ", arqnome);
      printf("O diretório 'saida/' existe?\n");
      exit (EXIT_FAILURE);
   }

   /* Imprime código do cabeçalho do arquivo de saída */
   if (fprintf(arq, "P2\n") == -1) {
      printf("Erro ao imprimir código do cabeçalho do arquivo '%s'.\n", arqnome);
      exit (EXIT_FAILURE);
   }

   /* Imprime número de linhas e colunas da imagem no arquivo de saída */
   if (fprintf(arq, "%d %d\n", lin, col) == -1) {
      printf("Erro ao imprimir número de linhas e colunas no arquivo '%s'.\n", arqnome);
      exit (EXIT_FAILURE);
   }

   /* Imprime número do maior valor de cor da imagem no arquivo de saída */
   if (fprintf(arq, "%d\n", valmaior) == -1) {
      printf("Erro ao imprimir maior valor de cor da imagem no arquivo '%s'.\n", arqnome);
      exit (EXIT_FAILURE);
   }

   /* Imprime imagem no arquivo de saída */
   ncharlin = 0;
   for (i = 0; i < lin; i++)  {
      for (j = 0; j < col; j++)  {
         /* Pega valor do pixel */
         valpixel = img[i][j];

         /* Verifica se o pixel não ultrapassa o maior valor */
         if (valpixel > valmaior) {
            printf("Erro. O pixel %d,%d possui valor %d que ", i, j, valpixel);
            printf("é maior que maior valor %d que foi fornecido. ", valmaior);
            printf("Este pixel terá valor %d", valmaior);
            valpixel = valmaior;
         }

         /* Imprime pixel e verifica se houve erro */
         nchar = fprintf(arq, "%d", valpixel);
         if (nchar == -1) {
            printf("Erro ao imprimir algum pixel no arquivo de saída '%s'.\n", arqnome);
            exit (EXIT_FAILURE);
         }

         /* Verifica o tamanho da linha. Arquivos .pgm do tipo P2 deve ter 
          * linhas com no máximo 70 caracteres */
         ncharlin += nchar;
         if (ncharlin > 70) {
            /* Pula linha */
            if (fprintf(arq, "\n") == -1) {
               printf("Erro ao escrever arquivo de saída '%s'.\n", arqnome);
               exit (EXIT_FAILURE);
            }
            /* Zera variável contadora de caracteres da linha */
            ncharlin = 0;
         }
         else {
            /* Coloca espaça depois do número */
            fprintf(arq, " ");
            ncharlin++;
         }
      }

      /* Pula linha  para a mudança de linha da imagem */
      if (fprintf(arq, "\n") == -1) {
         printf("Erro ao escrever arquivo de saída '%s'.\n", arqnome);
         exit (EXIT_FAILURE);
      }

      /* Zera variável contadora de caracteres da linha */
      ncharlin = 0;
   }

   /* Fecha arquivo de entrada */
   fclose(arq);

   /* Imprime mensagem que informa que o arquivo foi carregado com sucesso */
   printf("\nO arquivo '%s' foi carregado com sucesso.\n", arqnome);

   return;
}

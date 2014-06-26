#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***  Definição de constantes ***/

#define MAXLIN       400      /* Número máximo de linhas para matrizes */
#define MAXCOL       400      /* Número máximo de colunas para matrizes */
#define MAXVIZ       9        /* Número máximo de vizinhos */ 
#define MAXNOMEARQ   100      /* Tamanho máximo (80) para nome de arquivo */

/*** Protótipos das funcoes ***/

int le_arqpgm(char imgnome[], int img[][MAXCOL], int *lin, int *col, int *valmaior);
int escreve_arqpgm(char imgnome[], int img[][MAXCOL], int lin, int col, int valmaior);
void escreve_matriztela(int m[][MAXCOL], int lin, int col, int valmaior);
void cria_arqnomesaida(char resnome[], char imgnome[], char opcao);
void negativo(int img[][MAXCOL], int res[][MAXCOL], int lin, int col, int valmaior);
void rebate_horizontal(int img[][MAXCOL], int res[][MAXCOL], int lin, int col);
/*void rebate_vertical(int a[][MAXCOL], int linhas, int colunas);
void rotacao(int a[][MAXCOL], int *lin, int *col);
void filtro_mediana(int a[][MAXCOL], int linhas, int colunas, int *maior);
void copia_matriz(int a[][MAXCOL], int b[][MAXCOL], int linhas, int colunas);
int maior_valor_matriz(int a[][MAXCOL], int linhas, int colunas);
int determina_mediana(int a[][MAXCOL], int linhas, int colunas, int i, int j);
void ordena(int v[], int n);
*/

/***  Função main ***/

int main()
{
   int img[MAXLIN][MAXCOL];   /* Matriz que representa uma imagem */
   int res[MAXLIN][MAXCOL];   /* Resultado das transformações */
   int nlin;                  /* Número de linhas da imagem */
   int ncol;                  /* Número de colunas da imagem */ 
   int valmaior;              /* Maior tonalidade de cinza da imagem */
   char imgnome[MAXNOMEARQ];  /* Nome de arquivo de entrada sem extensao .pgm */
   char resnome[MAXNOMEARQ+2];/* Nome de arquivo resultado sem extensao .pgm */
   char opcao;                /* Opção do menu escolhida pelo usuário*/

   /* Laço para do programa. Apenas sai dele se o usuário pedir */
   while (1) {

      /* Primeiro menu que pede ao usuário se ele deseja manipular alguma imagem
       * ou se deseja sair do programa */
      printf("\nEscolha uma das opções:\n");
      printf("   0 - Sair\n");
      printf("   1 - Manipular uma nova imagem\n");
      printf("Digite: ");
      scanf("\n%c", &opcao);

      /* Sai do laço e finaliza o programa caso a opção 0 foi escolhida */
      if (opcao != '1')
         break;

      /* Pega o nome da imagem para fazer as manipulações */
      printf("\nDigite o nome do arquivo a ser processado sem extensao .pgm: ");
      scanf("%s", imgnome);

      /* Leitura do arquivo pgm desejado */
      if (!le_arqpgm(imgnome, img, &nlin, &ncol, &valmaior))
         continue;

      /* Segundo menu para escolher o que o usuário deseja fazer com a imagem
       * informada */
      printf("\nEscolha o que deseja fazer com a imagem:\n");
      printf("   p - imprimir na tela\n");
      printf("   n - negativo\n");
      printf("   h - rebater na horizontal\n");
      printf("   v - rebater na vertical\n");
      printf("   r - rotacao\n");
      printf("   m - filtro da mediana\n");
      printf("Digite: ");
      scanf("\n%c", &opcao);
      printf("\n");

      /* Executa ação referente à opção escolhida */
      switch (opcao) {

         /* Escreve matriz na tela */
         case 'p':
            escreve_matriztela(img, nlin, ncol, valmaior);
            break;

         /* Faz o negativo e salva o resultado em arquivo */
         case 'n':
            negativo(img, res, nlin, ncol, valmaior);
            cria_arqnomesaida(resnome, imgnome, opcao);
            escreve_arqpgm(resnome, res, nlin, ncol, valmaior);
            break;

         /* Faz o negativo e salva o resultado em arquivo */
         case 'h':
            rebate_horizontal(img, res, nlin, ncol);
            cria_arqnomesaida(resnome, imgnome, opcao);
            escreve_arqpgm(resnome, res, nlin, ncol, valmaior);
            break;

         default:
            printf("Ação ainda não implementada.\n");

      }
      

   }





   return EXIT_SUCCESS;
}

/* Definições do protótipos das funções */

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
 * Devolve 1 caso a leitura tenha sido bem sicedida ou 0 caso contrário.
 */
int le_arqpgm(char imgnome[], int img[][MAXCOL], int *lin, int *col, int *valmaior)
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

   /* Monta nome completo do arquivo */
   strcat(arqnome, "entrada/");
   strcat(arqnome, (const char *) imgnome);
   strcat(arqnome, ".pgm");
 
   /* Tenta abrir o arquivo */
   arq = fopen(arqnome, "r");
   if (arq == NULL)  {
      printf("\nErro na abertura do arquivo '%s'. ", arqnome);
      printf("O arquivo '%s.pgm' está no diretório 'entrada/'?\n\n", imgnome);
      return 0;
   }

   /* Lê a chave do arquivo */
   if (fscanf(arq, "%s", chave) != 1)  {
      printf("Erro na leitura do arquivo '%s'.\n", arqnome);
      return 0;
   }
   if (strcmp(chave,"P2") != 0)  {
      printf("Formato do arquivo '%s' desconhecido.\n", chave);
      return 0;
   }

   /* Lê número de linha e coluna da imagem */
   if (fscanf(arq, "%d %d\n", col, lin) != 2)  {
      printf("Erro ao ler número de linhas e colunas da imagem do arquivo ");
      printf("'%s'.\n", arqnome);
      return 0;
   }

   /* Verifica se a imagem é mto grande */
   if (*lin > MAXLIN || *col > MAXCOL) {
      printf("A imagem do arquivo '%s' é muito grande para ", arqnome);
      printf("ser processada. O tamanho máximo suportador é: ");
      printf("%d linhas x %d colunas\n", MAXLIN, MAXCOL);
      return 0;
   }


   /* Lê o maior valor de cor da imagem */
   if (fscanf(arq, "%d\n", valmaior) != 1)  {
      printf("Erro ao ler o maior valor da cor da imagem ");
      printf("do arquivo '%s'.\n", arqnome);
      return 0;
   }

   /* Lê os valores de cada linha de pixel da coluna e armazena na matriz dada */
   for (i = 0; i < *lin; i++)
      for (j = 0; j < *col; j++)
         if (fscanf(arq, "%d", &img[i][j]) != 1) {
            printf("Erro ao ler o arquivo. Ele deve estar corrompido.");
            return 0;
         }

   /* Fecha arquivo de entrada */
   fclose(arq);

   /* Imprime mensagem que informa que o arquivo foi carregado com sucesso */
   printf("\nO arquivo '%s' foi carregado com sucesso.\n", arqnome);

   /* Devolve valor de sucesso */
   return 1;
}

/* Encreve a matriz que representa a imagem em um arquivo .pgm no diretório
 * saída. Os parâmetros que devem ser dados são:
 *    - imgnome  : nome da imagem.
 *    - img      : matriz que contém os valores dos pixels da imagem.
 *    - lin      : número de linhas da imagem.
 *    - col      : coluna da imagem.
 *    - valmaior : maior valor de um pixel da imagem
 */
int escreve_arqpgm(char imgnome[], int img[][MAXCOL], int lin, int col, int valmaior)
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
      return 0;
   }

   /* Imprime código do cabeçalho do arquivo de saída */
   if (fprintf(arq, "P2\n") == -1) {
      printf("Erro ao imprimir código do cabeçalho do arquivo '%s'.\n", arqnome);
      return 0;
   }

   /* Imprime número de linhas e colunas da imagem no arquivo de saída */
   if (fprintf(arq, "%d %d\n", col, lin) == -1) {
      printf("Erro ao imprimir número de linhas e colunas no arquivo '%s'.\n", arqnome);
      return 0;
   }

   /* Imprime número do maior valor de cor da imagem no arquivo de saída */
   if (fprintf(arq, "%d\n", valmaior) == -1) {
      printf("Erro ao imprimir maior valor de cor da imagem no arquivo '%s'.\n", arqnome);
      return 0;
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
            return 0;
         }

         /* Verifica o tamanho da linha. Arquivos .pgm do tipo P2 deve ter 
          * linhas com no máximo 70 caracteres */
         ncharlin += nchar;
         if (ncharlin > 70) {
            /* Pula linha */
            if (fprintf(arq, "\n") == -1) {
               printf("Erro ao escrever arquivo de saída '%s'.\n", arqnome);
               return 0;
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
         return 0;
      }

      /* Zera variável contadora de caracteres da linha */
      ncharlin = 0;
   }

   /* Fecha arquivo de entrada */
   fclose(arq);

   /* Imprime mensagem que informa que o arquivo foi carregado com sucesso */
   printf("\nO arquivo '%s' foi carregado com sucesso.\n", arqnome);

   return 1;
}

/* Dados as inforções de uma matriz de inteiros, a imprime na tela. Os
 * parâmetros são:
 *    - m        : matriz de inteiros a ser impressa
 *    - lin      : número de linhas da matriz
 *    - col      : número de colunas da matriz
 *    - valmaior : maior valor de um pixel
 */
void escreve_matriztela(int m[][MAXCOL], int lin, int col, int valmaior)
{
   int i, j;      /* Variáveis contadoras */
   
   printf("Maior valor: %d\n", valmaior);
   printf("Dimensões: %d linhas x %d colunas\n", lin, col);

   /* Laço para imprimir na tela os valores dos pixels */
   for (i = 0; i < lin; i++) {
      for (j = 0; j < col; j++)
         printf("%4d ", m[i][j]);
      printf("\n");
   }

   return;
}

/* Função útil para criar os nomes dos arquivos de saída. Os parâmetros são:
 *    - resnome : onde o nome do arquivo de saída será armazenado
 *    - imgnome : nome da imagem sem extensão .pgm
 *    - opcao   : caractere que será anexado no final do nome
 */
void cria_arqnomesaida(char resnome[], char imgnome[], char opcao)
{
   int i;      /* Variável contadora */

   for (i = 0; imgnome[i] != '\0'; i++)
      resnome[i] = imgnome[i];
   resnome[i] = '-';
   resnome[i+1] = opcao;
   resnome[i+2] = '\0';

   return;
}

/* Cria o negativo da imagem dada e salva em outra matriz resultado. Os
 * parâmetros que devem ser passados são:
 *    - img      : matriz da imagem de entrada
 *    - res      : matriz da imagem resultado
 *    - lin      : número de linhas da matriz
 *    - col      : número de colunas da matriz
 *    - valmaior : maior valor de cor da matriz de entrada (que também é a mesma
 *                 da matriz resultado)
 */
void negativo(int img[][MAXCOL], int res[][MAXCOL], int lin, int col, int valmaior)
{
   int i, j;   /* Variáveis contadoras */

   /* Faz a transformação */
   for (i = 0; i < lin; i++)
      for (j = 0; j < col; j++)
         res[i][j] = valmaior - img[i][j];

   return;
}

/* Faz transformação que deixa a imagem de "ponta cabeça". Os parâmetros que
 * devem ser passados são:
 *    - img      : matriz da imagem de entrada
 *    - res      : matriz da imagem resultado
 *    - lin      : número de linhas da matriz
 *    - col      : número de colunas da matriz
 */
void rebate_horizontal(int img[][MAXCOL], int res[][MAXCOL], int lin, int col)
{
   int i, j;   /* Variáveis contadoras */

   for (i = 0; i < lin; i++)
      for (j = 0; j < col; j++)
         res[lin-1-i][col-1-j] = img[i][j];

   return;
}

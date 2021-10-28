#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NL 3
#define NC 3

typedef struct matrizEsparsa
{
  int lin;
  int col;
  int valor;
  struct matrizEsparsa *ponteiroColuna;
  struct matrizEsparsa *ponteiroLinha;

} mEsp;

void inicializar(mEsp *vetLin[], mEsp *vetCol[])
{
  int i;
  for (i = 0; i < NL; i++)
    vetLin[i] = NULL;

  for (i = 0; i < NC; i++)
    vetCol[i] = NULL;
}

mEsp *verificaOcupado(mEsp *vetLin[], int lin, int col)
{
  mEsp *aux = vetLin[lin];
  while (aux != NULL && col > aux->col)
    aux = aux->ponteiroLinha;

  if (aux != NULL && col == aux->col)
    return aux;
  return NULL;
}

void exibir(mEsp *vetLin[])
{
  int i;
  int j;
  mEsp *aux;

  for (i = 0; i < NL; i++)
  {
    for (j = 0; j < NC; j++)
    {
      aux = verificaOcupado(vetLin, i, j);

      if (aux)
        printf("[%0.2d]", aux->valor);
      else
        printf("[  ]");
    }
    putchar('\n');
  }
}

void insere(mEsp *vetLin[], mEsp *vetCol[], int lin, int col, int valor)
{
  mEsp *ant;
  mEsp *aux = verificaOcupado(vetLin, lin, col);

  if (aux != NULL)
    aux->valor = valor;
  else
  {
    mEsp *nova = malloc(sizeof(mEsp));
    nova->lin = lin;
    nova->col = col;
    nova->valor = valor;

    //Ligacao Horizontal
    if (vetLin[lin] == NULL || col < vetLin[lin]->col)
    {
      nova->ponteiroLinha = vetLin[lin];
      vetLin[lin] = nova;
    }
    else
    {
      aux = vetLin[lin];
      while (aux != NULL && col > aux->col)
      {
        ant = aux;
        aux = aux->ponteiroLinha;
      }
      ant->ponteiroLinha = nova;
      nova->ponteiroLinha = aux;
    }

    //Ligacao Vertical
    if (vetCol[col] == NULL || col < vetCol[col]->lin)
    {
      nova->ponteiroColuna = vetCol[col];
      vetCol[col] = nova;
    }
    else
    {
      aux = vetCol[col];
      while (aux != NULL && lin > aux->lin)
      {
        ant = aux;
        aux = aux->ponteiroColuna;
      }
      ant->ponteiroColuna = nova;
      nova->ponteiroColuna = aux;
    }
  }
}

void soma(mEsp *vetLinA[], mEsp *vetLinB[], mEsp *vetLinC[], mEsp *vetColC[])
{
  int j;
  int soma;

  mEsp *auxA;
  mEsp *auxB;

  for (int i = 0; i < NL; i++)
  {
    for (j = 0; j < NC; j++)
    {
      soma = 0;

      auxA = verificaOcupado(vetLinA, i, j);
      auxB = verificaOcupado(vetLinB, i, j);

      if (auxA != NULL || auxB != NULL)
      {
        if (auxA != NULL)
          soma = auxA->valor;

        if (auxB != NULL)
          soma += auxB->valor;

        insere(vetLinC, vetColC, i, j, soma);
      }
    }
  }
}

void multiplica(mEsp *vetLinA[], mEsp *vetLinB[], mEsp *vetLinC[], mEsp *vetColC[])
{
  mEsp *auxA;
  mEsp *auxB;

  int c;
  int k;
  int soma;

  for (int l = 0; l < NL; l++)
    for (c = 0; c < NC; c++)
    {
      soma = 0;

      for (k = 0; k < NC; k++)
      {
        auxA = verificaOcupado(vetLinA, l, k);
        auxB = verificaOcupado(vetLinB, k, c);

        if (auxA != NULL && auxB != NULL)
          soma += auxA->valor * auxB->valor;
      }

      if (soma != 0)
        insere(vetLinC, vetColC, l, c, soma);
    }
}

void somaMatrizes(void)
{
  //////////////////////////////////MATRIZ A
  mEsp *vetLin[NL];
  mEsp *vetCol[NC];

  inicializar(vetLin, vetCol);

  insere(vetLin, vetCol, 0, 4, 9);
  insere(vetLin, vetCol, 1, 1, 3);
  insere(vetLin, vetCol, 2, 4, 35);
  insere(vetLin, vetCol, 3, 2, 1);
  insere(vetLin, vetCol, 3, 0, 5);

  exibir(vetLin);
  putchar('\n');
  //////////////////////////////////MATRIZ A

  //////////////////////////////////MATRIZ B
  mEsp *vetLinB[NL];
  mEsp *vetColB[NC];

  inicializar(vetLinB, vetColB);

  insere(vetLinB, vetColB, 2, 0, 0);
  insere(vetLinB, vetColB, 4, 3, 3);
  insere(vetLinB, vetColB, 3, 4, 2);

  exibir(vetLinB);
  putchar('\n');
  //////////////////////////////////MATRIZ B

  //////////////////////////////////MATRIZ C (Soma)
  mEsp *vetLinC[NL];
  mEsp *vetColC[NC];
  inicializar(vetLinC, vetColC);
  soma(vetLin, vetLinB, vetLinC, vetColC);
  exibir(vetLinC);
  putchar('\n');
  //////////////////////////////////MATRIZ C
}

void multiplicaoMatrizes(void)
{
  srand(time(NULL));

  //////////////////////////////////MATRIZ A
  mEsp *vetLinA[NL];
  mEsp *vetColA[NC];
  inicializar(vetLinA, vetColA);
  int c;
  for (int l = 0; l < NL; l++)
    for (c = 0; c < NC; c++)
      insere(vetLinA, vetColA, l, c, 1 + rand() % 9);
  exibir(vetLinA);
  putchar('\n');
  //////////////////////////////////MATRIZ A

  //////////////////////////////////MATRIZ B
  mEsp *vetLinB[NL];
  mEsp *vetColB[NC];
  inicializar(vetLinB, vetColB);
  for (int l = 0; l < NL; l++)
    for (c = 0; c < NC; c++)
      insere(vetLinB, vetColB, l, c, 1 + rand() % 9);
  exibir(vetLinB);
  putchar('\n');
  //////////////////////////////////MATRIZ B

  //////////////////////////////////MATRIZ C (Multiplicacao)
  mEsp *vetLinC[NL];
  mEsp *vetColC[NC];
  inicializar(vetLinC, vetColC);
  multiplica(vetLinA, vetLinB, vetLinC, vetColC);
  exibir(vetLinC);
  putchar('\n');
  //////////////////////////////////MATRIZ C
}

int main(void)
{
  //somaMatrizes();
  multiplicaoMatrizes();
  return 0;
}

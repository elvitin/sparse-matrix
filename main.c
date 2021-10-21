#include <stdio.h>

#define NL 5
#define NC 6

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
        printf("[%d]", aux->valor);
      else
        printf("[0 ]");
    }
    putchar('\n');
  }
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

int main(void)
{

  return 0;
}
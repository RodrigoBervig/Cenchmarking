typedef struct RNnodo RNtree;
typedef unsigned long long int ull;

struct RNnodo
{
  int key;
  int red;
  struct RNnodo *esq;
  struct RNnodo *dir;
  struct RNnodo *pai;
};

static RNtree *NodoNULL = NULL; //only one instance to save space

RNtree *InsereRN(RNtree *t, int key, ull *operacoes);
int Consulta(int X, RNtree *T);
RNtree *Remove(RNtree *t, int key);
void destroiRN(RNtree *t);

RNtree *VerificaRN(RNtree *t, int key, ull *operacoes);
RNtree *RotacaoSimplesEsq(RNtree *t);
RNtree *RotacaoSimplesDir(RNtree *t);
void Desenha(RNtree *t, int nivel);
RNtree *Maior(RNtree *t);
RNtree *Menor(RNtree *t);

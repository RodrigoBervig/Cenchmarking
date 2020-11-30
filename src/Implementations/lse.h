typedef struct TipoPtNo PtNo;

typedef unsigned long long int ull;

struct TipoPtNo
{
       int info;
       int size;
       PtNo *prox;
};

PtNo *cria_lista(void);
PtNo *insere_ord(PtNo *l, int dados, ull *operacoes);
void imprime(PtNo *l);
PtNo *destroi(PtNo *l);
PtNo *consulta(PtNo *l, int dado, ull *operacoes);
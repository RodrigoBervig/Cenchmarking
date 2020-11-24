typedef int tipoinfo;
typedef unsigned long long int ull;

struct TNodoA
{
        tipoinfo info;
        struct TNodoA *esq;
        struct TNodoA *dir;
};

typedef struct TNodoA pNodoA;

pNodoA *InsereArvore(pNodoA *a, tipoinfo ch, ull *operacoes);
void preFixadoE(pNodoA *a);
pNodoA *consultaABP(pNodoA *a, tipoinfo chave, ull *operacoes);
void destroiABP(pNodoA *a);

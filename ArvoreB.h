
typedef struct NO ArvB;

ArvB* cria_ArvB();
void libera_ArvB(ArvB *raiz);
int busca_ArvB(ArvB *raiz, int valor);
int ehVazia_ArvB(ArvB *raiz);
int totalNo_ArvB(ArvB *raiz);
void emOrdem_ArvB(ArvB *raiz);
void posOrdem_ArvB(ArvB *raiz);
int insere_ArvB(ArvB* raiz, int valor);
int remove_ArvB(ArvB *raiz, int valor);



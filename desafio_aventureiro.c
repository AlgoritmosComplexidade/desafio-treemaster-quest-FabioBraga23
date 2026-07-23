/*
 Biblioteca Digital com Balanceamento DSW
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Documento{
    int id;
    char titulo[100];
    char autor[50];
    int anoPublicacao;
};

struct No{
    struct Documento documento;
    struct No *esquerda,*direita;
};

// Cria um novo nó da Árvore com os dados do documento.
struct No* criarNo(struct Documento d){
    struct No *n=(struct No*)malloc(sizeof(struct No));
    if(n==NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    n->documento=d;
    n->esquerda=n->direita=NULL;
    return n;
}

// Insere um documento na Árvore binária de busca.
struct No* inserir(struct No *r, struct Documento d){
    if(r==NULL) return criarNo(d);

    if(d.id<r->documento.id)
        r->esquerda=inserir(r->esquerda,d);
    else if(d.id>r->documento.id)
        r->direita=inserir(r->direita,d);
    else
        printf("ID %d ja cadastrado.\n",d.id);

    return r;
}

// Exibe os documentos em ordem crescente de ID.
void emOrdem(struct No *r,int *contador){
    if(r){
        emOrdem(r->esquerda,contador);
        printf("Documento %d:\n\n",(*contador)++);
        printf("ID: %d\n",r->documento.id);
        printf("Titulo: %s\n",r->documento.titulo);
        printf("Autor: %s\n",r->documento.autor);
        printf("Ano de publicacao: %d\n",r->documento.anoPublicacao);
        printf("-------------------------------------\n");
        emOrdem(r->direita,contador);
    }
}

// Calcula a altura da Árvore.
int altura(struct No *r){
    if(r==NULL) return 0;
    int he=altura(r->esquerda);
    int hd=altura(r->direita);
    return (he>hd?he:hd)+1;
}

// Conta a quantidade de nós da Árvore.
int contarNos(struct No *r){
    if(r==NULL) return 0;
    return 1+contarNos(r->esquerda)+contarNos(r->direita);
}

// Transforma a Árvore em uma espinha dorsal (vine).
void criarEspinha(struct No **raiz){
    struct No falso;
    falso.direita=*raiz;
    struct No *avo=&falso;
    struct No *filho=avo->direita;

    while(filho){
        if(filho->esquerda){
            struct No *tmp=filho->esquerda;
            filho->esquerda=tmp->direita;
            tmp->direita=filho;
            avo->direita=tmp;
            filho=tmp;
        }else{
            avo=filho;
            filho=filho->direita;
        }
    }
    *raiz=falso.direita;
}

// Comprime a espinha dorsal realizando rotações à esquerda.
void comprimir(struct No **raiz,int cont){
    struct No falso;
    falso.direita=*raiz;
    struct No *scanner=&falso;

    for(int i=0;i<cont;i++){
        struct No *filho=scanner->direita;
        if(!filho) break;
        struct No *neto=filho->direita;
        if(!neto) break;

        scanner->direita=neto;
        filho->direita=neto->esquerda;
        neto->esquerda=filho;
        scanner=neto;
    }
    *raiz=falso.direita;
}

// Aplica o algoritmo DSW para balancear a Árvore.
void balancearDSW(struct No **raiz){
    criarEspinha(raiz);
    int n=contarNos(*raiz);

    int m=1;
    while(m<=n) m*=2;
    m=m/2-1;

    comprimir(raiz,n-m);

    while(m>1){
        m/=2;
        comprimir(raiz,m);
    }
}

// Lê os dados de um documento informados pelo usuário.
void lerDocumento(struct Documento *d,int numero){
    printf("\nCadastro do Documento %d\n",numero);

    printf("ID: ");
    scanf("%d",&d->id);
    getchar();

    printf("Titulo: ");
    fgets(d->titulo,sizeof(d->titulo),stdin);
    d->titulo[strcspn(d->titulo,"\n")]=0;

    printf("Autor: ");
    fgets(d->autor,sizeof(d->autor),stdin);
    d->autor[strcspn(d->autor,"\n")]=0;

    printf("Ano de publicacao: ");
    scanf("%d",&d->anoPublicacao);
    getchar();
}

// Fução principal do programa.
int main(){
    struct No *raiz=NULL;
    struct Documento d1,d2;

    printf("=== Biblioteca Digital ===\n");

    lerDocumento(&d1,1);
    raiz=inserir(raiz,d1);

    lerDocumento(&d2,2);
    raiz=inserir(raiz,d2);

    printf("\n=== Documentos cadastrados ===\n\n");
    int contador=1;
    emOrdem(raiz,&contador);

    int antes=altura(raiz);

    printf("\nAplicando algoritmo DSW...\n");
    balancearDSW(&raiz);

    int depois=altura(raiz);

    printf("\n=== Metricas de desempenho ===\n");
    printf("Altura antes: %d\n",antes);
    printf("Altura apos: %d\n",depois);

    printf("\n=== Documentos apos balanceamento ===\n\n");
    contador=1;
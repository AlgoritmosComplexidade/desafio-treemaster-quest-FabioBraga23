/*
    Biblioteca Digital
    Árvore AVL + Fallback DSW
    TreeMaster Quest - Nível Mestre
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Documento{

    unsigned long int id;
    char titulo[100];
    char autor[50];
    int anoPublicacao;

}Documento;

typedef struct NoAVL{

    Documento documento;

    struct NoAVL *esquerda;
    struct NoAVL *direita;

    int altura;

}NoAVL;

typedef struct{

    float alturaAntes;
    float alturaDepois;
    float numeroRotacoes;
    float tempoExecucao;

}Metricas;

int rotacoesAVL=0;





/*====================================================
                    ALTURA
====================================================*/

int maximo(int a,int b){

    return (a>b)?a:b;

}

int alturaNo(NoAVL *no){

    if(no==NULL)
        return -1;

    return no->altura;

}

void atualizarAltura(NoAVL *no){

    if(no==NULL)
        return;

    no->altura=
        1+
        maximo(
            alturaNo(no->esquerda),
            alturaNo(no->direita)
        );

}

int fatorBalanceamento(NoAVL *no){

    if(no==NULL)
        return 0;

    return
        alturaNo(no->esquerda)-
        alturaNo(no->direita);

}





/*====================================================
                CRIAÇÃO DO NÓ
====================================================*/

NoAVL* criarNo(Documento doc){

    NoAVL *novo=
        (NoAVL*)malloc(sizeof(NoAVL));

    if(novo==NULL){

        printf("Erro de memoria.\n");
        exit(1);

    }

    novo->documento=doc;

    novo->esquerda=NULL;
    novo->direita=NULL;

    novo->altura=0;

    return novo;

}





/*====================================================
            ROTAÇÃO SIMPLES À DIREITA
====================================================*/

NoAVL* rotacaoDireita(NoAVL *raiz){

    NoAVL *novaRaiz=
        raiz->esquerda;

    NoAVL *subArvore=
        novaRaiz->direita;

    novaRaiz->direita=raiz;

    raiz->esquerda=subArvore;

    atualizarAltura(raiz);

    atualizarAltura(novaRaiz);

    rotacoesAVL++;

    return novaRaiz;

}





/*====================================================
            ROTAÇÃO SIMPLES À ESQUERDA
====================================================*/

NoAVL* rotacaoEsquerda(NoAVL *raiz){

    NoAVL *novaRaiz=
        raiz->direita;

    NoAVL *subArvore=
        novaRaiz->esquerda;

    novaRaiz->esquerda=raiz;

    raiz->direita=subArvore;

    atualizarAltura(raiz);

    atualizarAltura(novaRaiz);

    rotacoesAVL++;

    return novaRaiz;

}

/*====================================================
            ROTAÇÃO DUPLA ESQUERDA-DIREITA
====================================================*/

NoAVL* rotacaoEsquerdaDireita(NoAVL *raiz){

    raiz->esquerda=
        rotacaoEsquerda(raiz->esquerda);

    return rotacaoDireita(raiz);

}





/*====================================================
            ROTAÇÃO DUPLA DIREITA-ESQUERDA
====================================================*/

NoAVL* rotacaoDireitaEsquerda(NoAVL *raiz){

    raiz->direita=
        rotacaoDireita(raiz->direita);

    return rotacaoEsquerda(raiz);

}





/*====================================================
                INSERÇÃO AVL
====================================================*/

NoAVL* inserirAVL(NoAVL *raiz, Documento doc){

    if(raiz==NULL)
        return criarNo(doc);

    if(doc.id < raiz->documento.id){

        raiz->esquerda=
            inserirAVL(raiz->esquerda,doc);

    }

    else if(doc.id > raiz->documento.id){

        raiz->direita=
            inserirAVL(raiz->direita,doc);

    }

    else{

        printf("\nID ja cadastrado.\n");

        return raiz;

    }

    atualizarAltura(raiz);

    int fb=fatorBalanceamento(raiz);

    /* Caso LL */

    if(fb>1 &&
       doc.id < raiz->esquerda->documento.id)

        return rotacaoDireita(raiz);

    /* Caso RR */

    if(fb<-1 &&
       doc.id > raiz->direita->documento.id)

        return rotacaoEsquerda(raiz);

    /* Caso LR */

    if(fb>1 &&
       doc.id > raiz->esquerda->documento.id)

        return rotacaoEsquerdaDireita(raiz);

    /* Caso RL */

    if(fb<-1 &&
       doc.id < raiz->direita->documento.id)

        return rotacaoDireitaEsquerda(raiz);

    return raiz;

}





/*====================================================
                PERCURSO EM ORDEM
====================================================*/

void emOrdem(NoAVL *raiz,int *contador){

    if(raiz==NULL)
        return;

    emOrdem(raiz->esquerda,contador);

    printf("Documento %d\n\n",(*contador)++);

    printf("ID: %lu\n",
           raiz->documento.id);

    printf("Titulo: %s\n",
           raiz->documento.titulo);

    printf("Autor: %s\n",
           raiz->documento.autor);

    printf("Ano de publicacao: %d\n",
           raiz->documento.anoPublicacao);

    printf("----------------------------------\n");

    emOrdem(raiz->direita,contador);

}





/*====================================================
                CONTAGEM DE NÓS
====================================================*/

int contarNos(NoAVL *raiz){

    if(raiz==NULL)
        return 0;

    return
        1+
        contarNos(raiz->esquerda)+
        contarNos(raiz->direita);

}





/*====================================================
                LEITURA DOS DOCUMENTOS
====================================================*/

void lerDocumento(Documento *doc,int numero){

    printf("\nCadastro do Documento %d\n",numero);

    printf("ID: ");
    scanf("%lu",&doc->id);

    getchar();

    printf("Titulo: ");

    fgets(doc->titulo,
          sizeof(doc->titulo),
          stdin);

    doc->titulo[
        strcspn(doc->titulo,"\n")
    ]=0;

    printf("Autor: ");

    fgets(doc->autor,
          sizeof(doc->autor),
          stdin);

    doc->autor[
        strcspn(doc->autor,"\n")
    ]=0;

    printf("Ano de publicacao: ");

    scanf("%d",
          &doc->anoPublicacao);

    getchar();

}

/*====================================================
                ALTURA DA ÁRVORE
====================================================*/

int alturaArvore(NoAVL *raiz){

    if(raiz==NULL)
        return 0;

    int he=alturaArvore(raiz->esquerda);
    int hd=alturaArvore(raiz->direita);

    return (he>hd?he:hd)+1;

}





/*====================================================
                INSERÇÃO BST
(Usada apenas para comparação com DSW)
====================================================*/

NoAVL* inserirBST(NoAVL *raiz, Documento doc){

    if(raiz==NULL)
        return criarNo(doc);

    if(doc.id < raiz->documento.id)
        raiz->esquerda=inserirBST(raiz->esquerda,doc);

    else if(doc.id > raiz->documento.id)
        raiz->direita=inserirBST(raiz->direita,doc);

    atualizarAltura(raiz);

    return raiz;

}





/*====================================================
                DSW
====================================================*/

void criarEspinha(NoAVL **raiz){

    NoAVL falso;
    falso.direita=*raiz;

    NoAVL *avo=&falso;
    NoAVL *filho=avo->direita;

    while(filho){

        if(filho->esquerda){

            NoAVL *temp=filho->esquerda;

            filho->esquerda=temp->direita;
            temp->direita=filho;

            avo->direita=temp;

            filho=temp;

        }else{

            avo=filho;
            filho=filho->direita;

        }

    }

    *raiz=falso.direita;

}

void comprimir(NoAVL **raiz,int cont){

    NoAVL falso;
    falso.direita=*raiz;

    NoAVL *scanner=&falso;

    for(int i=0;i<cont;i++){

        NoAVL *filho=scanner->direita;

        if(filho==NULL)
            break;

        NoAVL *neto=filho->direita;

        if(neto==NULL)
            break;

        scanner->direita=neto;

        filho->direita=neto->esquerda;

        neto->esquerda=filho;

        scanner=neto;

    }

    *raiz=falso.direita;

}

void balancearDSW(NoAVL **raiz){

    criarEspinha(raiz);

    int n=contarNos(*raiz);

    int m=1;

    while(m<=n)
        m*=2;

    m=m/2-1;

    comprimir(raiz,n-m);

    while(m>1){

        m/=2;

        comprimir(raiz,m);

    }

}





/*====================================================
                    MAIN
====================================================*/

int main(){

    Documento d1,d2;

    NoAVL *raizAVL=NULL;
    NoAVL *raizDSW=NULL;

    Metricas avl;
    Metricas dsw;

    printf("=== Biblioteca Digital ===\n");

    lerDocumento(&d1,1);
    lerDocumento(&d2,2);

    /*================ AVL =================*/

    avl.alturaAntes=alturaArvore(raizAVL);

    rotacoesAVL=0;

    clock_t inicio=clock();

    raizAVL=inserirAVL(raizAVL,d1);
    raizAVL=inserirAVL(raizAVL,d2);

    clock_t fim=clock();

    avl.tempoExecucao=
        ((float)(fim-inicio))/CLOCKS_PER_SEC;

    avl.alturaDepois=alturaArvore(raizAVL);

    avl.numeroRotacoes=(float)rotacoesAVL;

    /*================ DSW =================*/

    raizDSW=inserirBST(raizDSW,d1);
    raizDSW=inserirBST(raizDSW,d2);

    dsw.alturaAntes=alturaArvore(raizDSW);

    inicio=clock();

    balancearDSW(&raizDSW);

    fim=clock();

    dsw.tempoExecucao=
        ((float)(fim-inicio))/CLOCKS_PER_SEC;

    dsw.alturaDepois=alturaArvore(raizDSW);

    dsw.numeroRotacoes=0;

    printf("\n=== Documentos cadastrados ===\n\n");

    int contador=1;

    emOrdem(raizAVL,&contador);

    printf("\n=== Comparacao de desempenho ===\n\n");

    printf("Altura da arvore: %s (%d)\n",

        avl.alturaDepois<=dsw.alturaDepois ?
        "AVL venceu" :
        "DSW venceu",

        avl.alturaDepois<=dsw.alturaDepois);

    printf("Numero de rotacoes: %s (%d)\n",

        avl.numeroRotacoes<=dsw.numeroRotacoes ?
        "AVL venceu" :
        "DSW venceu",

        avl.numeroRotacoes<=dsw.numeroRotacoes);

    printf("Tempo de execucao: %s (%d)\n",

        avl.tempoExecucao<=dsw.tempoExecucao ?
        "AVL venceu" :
        "DSW venceu",

        avl.tempoExecucao<=dsw.tempoExecucao);

    return 0;

}
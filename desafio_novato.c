#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=========================================================
// Estrutura que representa um documento da biblioteca
//=========================================================
struct Documento {
    int id;
    char titulo[100];
    char autor[50];
    int anoPublicacao;
};

//=========================================================
// Estrutura do nó da Árvore Binária de Busca (ABB)
//=========================================================
struct No {
    struct Documento documento;
    struct No *esquerda;
    struct No *direita;
};

//=========================================================
// Cria um novo nó
//=========================================================
struct No* criarNo(struct Documento doc) {

    struct No *novo = (struct No*) malloc(sizeof(struct No));

    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    novo->documento = doc;
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

//=========================================================
// Insere um documento na ABB
//=========================================================
struct No* inserir(struct No *raiz, struct Documento doc) {

    if (raiz == NULL) {
        return criarNo(doc);
    }

    if (doc.id < raiz->documento.id) {
        raiz->esquerda = inserir(raiz->esquerda, doc);
    }
    else if (doc.id > raiz->documento.id) {
        raiz->direita = inserir(raiz->direita, doc);
    }
    else {
        printf("\nErro: já existe um documento com o ID %d.\n", doc.id);
    }

    return raiz;
}

//=========================================================
// Percurso em ordem
// Exibe os documentos em ordem crescente de ID
//=========================================================
void emOrdem(struct No *raiz) {

    static int contador = 1;

    if (raiz != NULL) {

        emOrdem(raiz->esquerda);

        printf("Documento %d:\n\n", contador++);
        printf("ID: %d\n", raiz->documento.id);
        printf("Título: %s\n", raiz->documento.titulo);
        printf("Autor: %s\n", raiz->documento.autor);
        printf("Ano de publicação: %d\n\n",
               raiz->documento.anoPublicacao);

        emOrdem(raiz->direita);
    }
}

//=========================================================
// Função principal
//=========================================================
int main() {

    struct No *raiz = NULL;

    struct Documento doc1;
    struct Documento doc2;

    printf("=============================================\n");
    printf(" Biblioteca Digital - Cadastro de Documentos\n");
    printf("=============================================\n\n");

    //-----------------------------------------------------
    // Cadastro do primeiro documento
    //-----------------------------------------------------
    printf("Cadastro do Documento 1\n\n");

    printf("ID: ");
    scanf("%d", &doc1.id);
    getchar();

    printf("Título: ");
    fgets(doc1.titulo, sizeof(doc1.titulo), stdin);
    doc1.titulo[strcspn(doc1.titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(doc1.autor, sizeof(doc1.autor), stdin);
    doc1.autor[strcspn(doc1.autor, "\n")] = '\0';

    printf("Ano de publicação: ");
    scanf("%d", &doc1.anoPublicacao);
    getchar();

    raiz = inserir(raiz, doc1);

    printf("\nDocumento 1 cadastrado com sucesso!\n\n");

    //-----------------------------------------------------
    // Cadastro do segundo documento
    //-----------------------------------------------------
    printf("Cadastro do Documento 2\n\n");

    printf("ID: ");
    scanf("%d", &doc2.id);
    getchar();

    printf("Título: ");
    fgets(doc2.titulo, sizeof(doc2.titulo), stdin);
    doc2.titulo[strcspn(doc2.titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(doc2.autor, sizeof(doc2.autor), stdin);
    doc2.autor[strcspn(doc2.autor, "\n")] = '\0';

    printf("Ano de publicação: ");
    scanf("%d", &doc2.anoPublicacao);

    raiz = inserir(raiz, doc2);

    printf("\nDocumento 2 cadastrado com sucesso!\n");

    //-----------------------------------------------------
    // Exibição dos documentos
    //-----------------------------------------------------
    printf("\n=============================================\n");
    printf("DOCUMENTOS CADASTRADOS\n");
    printf("=============================================\n\n");

    emOrdem(raiz);

    return 0;
}
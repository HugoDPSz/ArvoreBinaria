#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *direita;
    struct no *esquerda;
} no;

no *inserirNo(no *raiz, int valor){
    no *aux = (no *)calloc(1, sizeof(no));

    aux->valor = valor;
    aux->direita = NULL;
    aux->esquerda = NULL;

    if(raiz == NULL){
        return aux;
    }
    if(aux->valor < raiz->valor){
        if(raiz->esquerda == NULL){
            raiz->esquerda = aux;
        } else{
            raiz->esquerda = inserirNo(raiz->esquerda, valor);
        }
    } else{
        if(raiz->direita == NULL){
            raiz->direita = aux;
        }else{
            raiz->direita = inserirNo(raiz->direita, valor);
        }
    }

    return raiz;
}

no *encontrarMinimo(no *raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}


no *removerNo(no *raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = removerNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = removerNo(raiz->direita, valor);
    } else {

        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        if (raiz->esquerda == NULL) {
            no *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            no *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        no *temp = encontrarMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = removerNo(raiz->direita, temp->valor);
    }
    return raiz;
}

void preordem(no *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->valor);
        preordem(raiz->esquerda);
        preordem(raiz->direita);
    }
}

void emordem(no *raiz){
    if(raiz != NULL){
        emordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emordem(raiz->direita);
    }
}

void posordem(no *raiz){
    if(raiz != NULL){
        posordem(raiz->esquerda);
        posordem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

int contaNo(no *raiz){
    int x, y;
    if(raiz == NULL){
        return 0;
    }

    x = contaNo(raiz->direita);
    y = contaNo(raiz->esquerda);

    return x + y + 1;
}

int contaNivel(no *raiz){
    int x, y;
    if(raiz == NULL){
        return 0;
    }

    x = contaNivel(raiz->direita);
    y = contaNivel(raiz->esquerda);

    if(x>y){
        return x + 1;
    } else{
        return y + 1;
    }
}

int main(){
    int n, valor, opcao;
    no *raiz = NULL;

    printf("Deseja inserir quantos nos?\n");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        printf("Digite o valor para inserir:\n");
        scanf("%d", &valor);

        raiz = inserirNo(raiz, valor);
    }

    printf("Deseja ver a arvore em:\n1 - Pre ordem\n2 - Em ordem\n3 - Pos ordem\n");
    scanf("%d", &opcao);

    switch(opcao){
        case 1:
            preordem(raiz);
            break;
        case 2:
            emordem(raiz);
            break;
        case 3:
            posordem(raiz);
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }
    printf("\nDeseja remover qual valor?\n");
    scanf("%d", &valor);
    removerNo(raiz, valor);

    printf("A alteracao em ordem resulta na seguinte arvore:\n");
    emordem(raiz);

    int nos = contaNo(raiz);
    printf("\nA arvore tem %d nos\n", nos);

    int nivel = contaNivel(raiz);
    printf("A arvore tem nivel %d\n", nivel);

    return 0;    
}

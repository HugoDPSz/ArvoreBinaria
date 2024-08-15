#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* right;
    struct node* left;
} node;

node* insert(node* root, int x) {
    node *aux = (node *)calloc(1, sizeof(node));

    aux->data = x;
    aux->right = NULL;
    aux->left = NULL;

    if (root == NULL) {
        root = aux;
    } else {
        node *current = root;
        node *parent = NULL;
        while (1) {
            parent = current;
            if (x < current->data) {
                current = current->left;

                if (current == NULL) {
                    parent->left = aux;
                    return root;
                }
            } else {
                current = current->right;

                if (current == NULL) {
                    parent->right = aux;
                    return root;
                }
            }
        }
    }

    return root;
}

void emordem(node* root) {
    if (root) {
        emordem(root->left);
        printf("%d ", root->data);
        emordem(root->right);
    }
}

void preordem(node* root) {
    if (root) {
        printf("%d ", root->data);
        preordem(root->left);
        preordem(root->right);
    }
}

void posordem(node* root) {
    if (root) {
        posordem(root->left);
        posordem(root->right);
        printf("%d ", root->data);
    }
}

int procura(node* root, int alvo) {
    node *current = root;
    printf("\nPassando pelos elementos: ");

    while (current) {
        printf("%d ", current->data);

        if (alvo < current->data) {
            current = current->left;
        } else if (alvo > current->data) {
            current = current->right;
        } else {
            return 1;
        }
    }
    return 0;
}

int main() {
    node *root = NULL;
    int lista[] = {34, 52, 33, 65, 28, 654, 21, 76, 123, 98, 12, 32};

    for (int i = 0; i < 12; i++) {
        root = insert(root, lista[i]);
    }

    printf("\nEm ordem: ");
    emordem(root);

    printf("\nPré-ordem: ");
    preordem(root);

    printf("\nPós-ordem: ");
    posordem(root);

    int alvo = 98;

    int aux = procura(root, alvo);
    if (aux) {
        printf("\n[%d] encontrado\n", alvo);
    } else {
        printf("\nNao encontrado\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct posicaoNO
{
    int64_t data;
    struct posicaoNO* prox;
};

struct Fila
{
    struct posicaoNO* frente;
    struct posicaoNO* atras;
    int size;
};

struct Fila* criarFila() {
    struct Fila* fila = (struct Fila*)malloc(sizeof(struct Fila));
    fila->frente = fila->atras = NULL;
    fila->size = 0;
    return fila;
}

int tamanhoFila(struct Fila* fila) {
    return fila->size;
}

void addElemento(struct Fila* fila, int64_t valor) {
    struct posicaoNO* novoNO = (struct posicaoNO*)malloc(sizeof(struct posicaoNO));
    novoNO->data = valor;
    novoNO->prox = NULL;

    if (fila->atras == NULL) {
        fila->frente = fila->atras = novoNO;
    } else {
        fila->atras->prox = novoNO;
        fila->atras = novoNO;
    }

    fila->size++;
}

void exibirElementos(struct Fila* fila) {
    struct posicaoNO* elem = fila->frente;
    printf("Elementos da fila: ");
    while (elem != NULL) {
        printf("%lld ", elem->data);
        if (elem->prox == NULL) {
            break;
        }
        elem = elem->prox;
    }
    printf("\n");
}

int64_t consultarElementos(struct Fila* fila, int posicao) {
    if (posicao < 1 || posicao > fila->size) {
        printf("\nPosicao incorreta.");
        return -1;
    }

    struct posicaoNO* elem = fila->frente;
    for (int i = 1; i < posicao; i++) {
        elem = elem->prox;
    }

    return elem->data;
}

void excluirElemento(struct Fila* fila) {
    if (fila->frente == NULL) {
        printf("\nA fila esta vazia.");
        return;
    }
    struct posicaoNO* elem = fila->frente;
    fila->frente = fila->frente->prox;
    free(elem);
    fila->size--;
}

void resetarLista(struct Fila* fila) {
    while (fila->frente != NULL) {
        excluirElemento(fila);
    }
    fila->frente = fila->atras = NULL;
    fila->size = 0;
    printf("\nFila Resetada.");
}

int main() {
    struct Fila* fila = criarFila();
    int menu;
    int64_t valor;
    int posicao;

    do {
        printf("\nMenu de opcoes:\n");
        printf("\n1. Adicionar um elemento na fila");
        printf("\n2. Exibir elementos da fila");
        printf("\n3. Consulta elemento da fila");
        printf("\n4. Excluir elemento da fila");
        printf("\n5. Resetar a Fila");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("Digite o valor a ser adicionado: ");
                scanf("%" SCNd64, &valor);
                addElemento(fila, valor);
                break;
            case 2:
                exibirElementos(fila);
                break;
            case 3:
                printf("Digite a posicao do elemento que voce quer consultar: ");
                scanf("%d", &posicao);
                valor = consultarElementos(fila, posicao);
                if (valor != -1) {
                    printf("\nElemento na posicao %d: %lld\n", posicao, valor);
                }
                break;
            case 4:
                excluirElemento(fila);
                break;
            case 5:
                resetarLista(fila);
                exibirElementos(fila);
                break;
            case 0:
                break;
            default:
                printf("\nopcao Invalida.\n");
        }
    } while (menu != 0);

    return 0;
}
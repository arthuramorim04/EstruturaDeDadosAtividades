#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
//criando a estrutura da lista de funcionarios
typedef struct dataNode {
    char nome[61];
    float salario;
} DataNode;

//criando a estrutura do node(ponteiro)
typedef struct node {
    DataNode data;
    struct node *next;
    struct node *last;
} Node;

//definindo o tamanho da lista e seu inicio
typedef struct list {
    int size;
    Node *head;
} List;


//cabecalho de funcoes
List *createList();

void push(List *list, DataNode data);

void printList(List *list);

bool isEmpty(List *list);

Node *atPos(List *list, int index);

int indexOf(List *list, Node *node);

void xchgNodes(List *list, Node *nodeA, Node *nodeB);

Node *min(List *list, int index);

Node *max(List *list, int index);

void decSort(List *list);

//funcao para criar um ponteiro para alocar espaco de memoria
List *createList() {
    List *list = (List *) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;

    return list;
}

//funcao push que ira inserir os elementos no comeco da lista
void push(List *list, DataNode data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (list[(list->size - 1)].size > 0) {
        node->data = data;
        node->next = list->head;
        node->last = list[list->size - 1].head;
        list->head = node;

    } else {
        node->data = data;
        node->next = list->head;
        node->last = NULL;
        list->head = node;
    }
    list->size++;
}

//funcao para exibir os dados na tela
void printList(List *list) {
    Node *pointer = list->head;

    if (isEmpty(list)) {
        printf("Lista Vazia\n");
        return;
    }

    printf("------Listas de Funcionarios------\n");
    while (pointer != NULL) {
        printf("Nome: %s\n", pointer->data.nome);
        if (pointer->data.salario < 850.0) {
            printf("Imposto: Isento");
            printf("Salario Liquido: R$%.2f\n", pointer->data.salario);
        } else {
            if (pointer->data.salario >= 850 && pointer->data.salario < 1200) {
                printf("Imposto: %.2f", (pointer->data.salario * 0.1));
                printf("Salario: R$%.2f\n", pointer->data.salario - (pointer->data.salario * 0.1));
            } else {
                if (pointer->data.salario >= 1200) {
                    printf("Imposto: %.2f", (pointer->data.salario * 0.2));
                    printf("Salario Liquido: R$%.2f\n", pointer->data.salario - (pointer->data.salario * 0.2));
                }
            }
        }
        printf("\n");
        pointer = pointer->next;
    }
    printf("\n");
}

void fistLetter(List *list) {
    Node *pointer = list->head;

    if (isEmpty(list)) {
        printf("Lista Vazia\n");
        return;
    }
    char firstLetter, aux;
    printf("\nDigite a primeira letra do nome que deseja buscar: ");
    scanf("%s", &firstLetter);
    aux = toupper(firstLetter);
    int count = 0;

    printf("------Listas de Funcionarios------\n");
    while (pointer != NULL) {
        if (pointer->data.nome[0] == aux || toupper(pointer->data.nome[0]) == aux) {
            printf("Nome: %s\n", pointer->data.nome);
            printf("Salario: R$%.2f\n", pointer->data.salario);
            if (pointer->data.salario < 850.0) {
                printf("Imposto: Isento");
            } else {
                if (pointer->data.salario >= 850 && pointer->data.salario < 1200) {
                    printf("Imposto: %.2f", (pointer->data.salario * 0.1));
                    printf("Salario: R$%.2f\n", pointer->data.salario - (pointer->data.salario * 0.1));
                } else {
                    if (pointer->data.salario >= 1200) {
                        printf("Imposto: %.2f", (pointer->data.salario * 0.2));
                        printf("Salario Liquido: R$%.2f\n", pointer->data.salario - (pointer->data.salario * 0.2));
                    }
                }
            }
            printf("\n");
            count++;

        }
        pointer = pointer->next;
    }
    if (count == 0) {
        printf("\nNao foi encontrado nenhum funcionario que inicie com essa letra!");
    }
}

//retorna se a lista esta vazia
bool isEmpty(List *list) {
    return (list->size == 0);
}

//funcao que passa o indice e tera como retorno o nó
Node *atPos(List *list, int index) {
    if (index >= 0 && index < list->size) {
        Node *node = list->head;

        int i;
        for (i = 0; i < index; i++)
            node = node->next;

        return node;
    }
    return NULL;
}


//indice do nó
int indexOf(List *list, Node *node) {

    if (node != NULL) {
        Node *pointer = list->head;

        int index = 0;

        while (pointer != node && pointer != NULL) {
            pointer = pointer->next;
            index++;
        }

        if (pointer != NULL)
            return index;
    }
    printf("No nao pertence a lista\n");
    return -1;
}


void xchgNodes(List *list, Node *nodeA, Node *nodeB) {

    if (nodeA == nodeB)
        return;

    int indexA = indexOf(list, nodeA);
    int indexB = indexOf(list, nodeB);

    if (indexA == -1 || indexB == -1)
        return;

    if (indexA > indexB) {
        nodeA = nodeB;
        nodeB = atPos(list, indexA);

        indexA = indexB;
        indexB = indexOf(list, nodeB);
    }

    Node *pb = atPos(list, indexB - 1);
    if (nodeA == list->head) {
        list->head = nodeB;
    } else {
        Node *pa = atPos(list, indexA - 1);
        pa->next = nodeB;
    }

    pb->next = nodeA;

    Node* pointer = nodeA->next;
    nodeA->next = nodeB->next;
    nodeA->last = nodeB->last;
    nodeB->next = pointer;
}

Node *max(List *list, int index) {
    Node *ponteiro = atPos(list, index);
    if (ponteiro != NULL) {
        Node *maxNode = ponteiro;

        while (ponteiro != NULL) {
            if (ponteiro->data.nome[0] > maxNode->data.nome[0])
                maxNode = ponteiro;
            ponteiro = ponteiro->next;
        }
        return maxNode;
    }
    return NULL;
}

//funcao para achar o valor minimo da lista
Node *min(List *list, int index) {
    Node *pointer = atPos(list, index);
    if (pointer != NULL) {
        Node *minNode = pointer;

        while (pointer != NULL) {
            if (pointer->data.nome[0] < minNode->data.nome[0])
                minNode = pointer;
            pointer = pointer->next;
        }
        return minNode;
    }
    return NULL;
}

//ordena em ordem decrescente
void decSort(List *list) {
    int i;
    for (i = 0; i < list->size - 1; i++)
        xchgNodes(list, atPos(list, i), max(list, i));
    printList(list);
}

void crescSort(List *list) {
    int i;
    for (i = 0; i < list->size - 1; i++)
        xchgNodes(list, atPos(list, i), min(list, i));
    printList(list);
}

int main() {
    int funcionarios;
    float salario_d;
    List *lista = createList();
    DataNode data;
    printf("------Cadastro de Funcionarios------\n");
    funcionarios = 6;
    while (funcionarios != 0) {
        printf("Digite o nome do funcionario: ");
        scanf("%s", &data.nome);
        printf("Digite o salario do funcionario: ");
        scanf("%f", &data.salario);
        printf("\n");

        push(lista, data);
        funcionarios--;
    };
    printList(lista);
    int menu = -1;
    do {
        printf("Escolha uma das seguintes opcoes:\n1 -Buscar funcionarios pela primeira letra do nome.\n2 - Ordena de forma Decrescente:");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                fistLetter(lista);
                break;
            case 2:
                decSort(lista);
                printList(lista);
                break;
            case 3:
                crescSort(lista);
                printList(lista);
                break;

            default:
                break;
        }

    } while (menu != 0);
}
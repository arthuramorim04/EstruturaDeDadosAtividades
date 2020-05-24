#include <stdio.h>
#include <stdlib.h>
#include <wingdi.h>

//criando a estrutura da lista de alunos
typedef struct alunoData {
    char nome[61];
    float nota;
} aluno;

//criando a estrutura do node(ponteiro)
typedef struct node {
    aluno data;
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

void push(List *list, aluno data);

void printList(List *list);

bool isEmpty(List *list);

Node *atPos(List *list, int index);

//funcao para criar um ponteiro para alocar espaco de memoria
List *createList() {
    List *list = (List *) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;

    return list;
}

//funcao push que ira inserir os elementos no comeco da lista
void push(List *list, aluno data) {
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

    printf("------Listas de aluno------\n");
    while (pointer != NULL) {

        printf("Nome: %s\n", pointer->data.nome);
        printf("Nota: %.2f\n", pointer->data.nota);
        printf("\n");

        pointer = pointer->next;

    }
    printf("\n");
}

//retorna se a lista esta vazia
bool isEmpty(List *list) {
    return (list->size == 0);
}

//mexer aqui para pegar o last
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

void listaAprovados(List *list, int index) {

    Node *ponteiro = atPos(list, index);
    int contador = 0;


    if (ponteiro != NULL) {

        while (ponteiro != NULL) {
            if (ponteiro->data.nota >= 7) {
                printf("Nome: %s\n", ponteiro->data.nome);
                printf("Nota: R$%.2f\n", ponteiro->data.nota);
            }
            ponteiro = ponteiro->next;
        }
        if (contador == 0) {
            printf("\nNenhum aluno foi aprovad!\n");
        }
    }
}

int main() {
    int alunos;
    List *lista = createList();
    aluno data;
    alunos = 5;
    
    while (alunos != 0) {
        printf("Digite o nome do aluno: ");
        scanf("%s", &data.nome);
        printf("Digite o nota do aluno: ");
        scanf("%f", &data.nota);
        printf("\n");

        push(lista, data);
        funcionarios--;
    };

    printList(lista);
    int menu = -1;
    do {
        printf("----Menu Principal---\n1 - Lista de alunos aprovados\n\n0 - Sair do Sistema\n:");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("\nLista de alunos aprovados:\n");
                listaAprovados(lista, 0);
                break;

            default:
                break;
        }

    } while (menu != 0);
}
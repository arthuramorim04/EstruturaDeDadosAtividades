#include <stdio.h>
#include <stdlib.h>

typedef struct dataNode{
    int id;
    int quantidade;
    float preco;

}DataNode;

typedef struct node{
    DataNode data;
    struct node* next;
} Node;

typedef struct list{
    int size;
    Node* head;
}List;

List* createList();
void push (List* list, DataNode data);
void printList(List* list);

List* createList(){
    List* list = (List*) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;

    return list;
}

void push(List* list, DataNode data){
    Node* node = (Node*) malloc(sizeof(Node));

    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

void printList(List* list){
    Node* pointer = list->head;
    float porcentagem, desconto;
    printf("Digite a porcentagem de desconto a ser aplicada aos produtos: ");
    scanf("%f", &desconto);
    DataNode data;

    if (pointer == NULL)
        printf("Lista Vazia");

    printf("------Lista de Produtos------\n");
    while (pointer != NULL){
        printf("ID: %d\n", pointer->data.id);
        printf("Valor: R$%.2f\n", pointer->data.preco);
        float newValue = (pointer->data.preco - (pointer->data.preco * (desconto / 100)));
        printf("Valor com Desconto: R$%.2f\n", newValue);
        printf("Quantidade: %d unidade(s)\n",pointer->data.quantidade);
        printf("\n");
        pointer = pointer->next;
    }
    printf("\n");
}

int main(){
    int produtos;

    List* lista = createList();
    DataNode data;
    printf("------Cadastro de Produtos------\n");
    produtos = 5;
    while (produtos!=0){
        printf("Digite o ID do produto: ");
        scanf("%d", &data.id);
        printf("Digite o preco da unidade do produto: ");
        scanf("%f", &data.preco);
        printf("Digite a quantidade de produto no estoque: ");
        scanf("%d", &data.quantidade);

        printf("\n");

        push(lista, data);
        produtos--;
    };

    printList(lista);
}
#include <stdio.h>
#include <stdlib.h>

//criando a estrutura da lista de numeros
typedef struct dataNode{
    int id;
}DataNode;

//criando a estrutura do node(ponteiro)
typedef struct node{
    DataNode data;
    struct node* next;
    struct node* last;
} Node;

//definindo o tamanho da lista e seu inicio
typedef struct list{
    int size;
    Node* head;
}List;

//cabecalho de funcoes
List* createList();
void push (List* list, DataNode data);
void printList(List* list);

//funcao para criar um ponteiro para alocar espaco de memoria
List* createList(){
    List* list = (List*) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;

    return list;
}

//funcao push que ira inserir os elementos no comeco da lista
void push(List* list, DataNode data){
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

void createLists(List* list,List* par,List* impar){
    Node* ponteiro = list->head;

    while (ponteiro != NULL){
        float a = ponteiro->data.id%2;
        if( a == 0){
            push(par,ponteiro->data);
        }else{
            push(impar,ponteiro->data);
        }
        ponteiro = ponteiro->next;
    }

}

//funcao para exibir os dados na tela
void printList(List* list){
    Node* pointer = list->head;
    DataNode data;

    if (pointer == NULL)
        printf("Lista Vazia");

    while (pointer != NULL){
        printf("numero: %d\n", pointer->data.id);
        printf("\n");
        pointer = pointer->next;
    }
    printf("\n");
}

//funcao que passa o indice e tera como retorno o nó
Node* atPos(List* list, int index){
    if (index >= 0 && index < list->size){
        Node* node = list->head;

        int i;
        for (i = 0; i < index; i++)
            node = node->next;

        return node;
    }
    return NULL;
}


//indice do nó
int indexOf(List* list, Node* node){

    if (node != NULL){
        Node* pointer = list->head;

        int index = 0;

        while (pointer != node && pointer != NULL){
            pointer = pointer->next;
            index++;
        }

        if (pointer != NULL)
            return index;
    }
    printf("No nao pertence a lista\n");
    return -1;
}




void xchgNodes(List* list, Node* nodeA, Node* nodeB){

    if (nodeA==nodeB)
        return;

    int indexA = indexOf(list, nodeA);
    int indexB = indexOf(list, nodeB);

    if (indexA == -1 || indexB == -1)
        return;

    if(indexA > indexB){
        nodeA = nodeB;
        nodeB = atPos(list, indexA);

        indexA = indexB;
        indexB = indexOf(list, nodeB);
    }

    Node* pb = atPos(list, indexB - 1);
    if (nodeA== list -> head){
        list->head = nodeB;
    }
    else{
        Node* pa = atPos(list, indexA - 1);
        pa -> next = nodeB;
    }

    pb->next = nodeA;

    Node* pointer = nodeA->next;
    nodeA->next = nodeB->next;
    nodeA->last = nodeB->last;
    nodeB->next = pointer;
}

Node* max(List* list, int index){
    Node* ponteiro = atPos(list, index);
    if (ponteiro != NULL){
        Node* maxNode = ponteiro;

        while (ponteiro != NULL){
            if(ponteiro->data.id > maxNode->data.id)
                maxNode = ponteiro;
            ponteiro = ponteiro->next;
        }
        return maxNode;
    }
    return NULL;
}

//funcao para achar o valor minimo da lista
Node* min(List* list, int index){
    Node* pointer = atPos(list, index);
    if (pointer != NULL){
        Node* minNode = pointer;

        while (pointer != NULL){
            if(pointer->data.id < minNode->data.id)
                minNode = pointer;
            pointer = pointer->next;
        }
        return minNode;
    }
    return NULL;
}

//ordena em ordem decrescente
void  decSort(List* list){
    int i;
    for (i=0; i < list -> size -1; i++)
        xchgNodes(list, atPos(list, i), max (list, i));
    printList(list);
}

void crescSort(List* list){
    int i;
    for (i=0; i < list -> size -1; i++)
        xchgNodes(list, atPos(list, i), min (list, i));
    printList(list);
}



int main(){
    int produtos;

    List* lista = createList();
    List* listaPar = createList();
    List* listaImpar = createList();
    DataNode data;
    DataNode dataPar;
    DataNode dataImpar;
    produtos = 20;
    int contador = 0;
    while (produtos!=0){
        contador++;
        printf("Digite o numero na posicao %d: ",contador);
        scanf("%d", &data.id);
        printf("\n");

        push(lista, data);
        produtos--;

    }
    createLists(lista, listaPar,listaImpar);

    printf("\nLista Par\n");
    printList(listaPar);
    printf("\nLista Impar\n");
    printList(listaImpar);
    printf("\nLista completa\n");
    printList(lista);

    printf("\nlista crescente\n");
    crescSort(lista);
    printf("\nlista decrescebte\n");
    decSort(lista);

}
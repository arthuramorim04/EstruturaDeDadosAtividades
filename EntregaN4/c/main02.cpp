#include <stdio.h>
#include <stdlib.h>
#include <wingdi.h>

//criando a estrutura da lista de funcionario
typedef struct dataNode{
    char nome[61];
    float salario;
}DataNode;

//criando a estrutura do node(ponteiro)
typedef struct node{
    DataNode data;
    struct node* next;
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
bool isEmpty(List* list);
Node* atPos(List* list, int index);
int indexOf(List* list, Node* node);
void xchgNodes(List* list, Node* nodeA, Node* nodeB);
Node* min(List* list, int index);
Node* max(List* list, int index);
void decSort(List* list);

//funcao para criar um ponteiro para alocar espaco de memoria
List* createList(){
    List* list = (List*) malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;

    return list;
}

//funcao push que ira inserir os elementos no comeco da lista
void push(List* list, DataNode data){
    Node* node = (Node*) malloc(sizeof(Node));

    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

//funcao para exibir os dados na tela
void printList(List* list){
    Node* pointer = list->head;

    if (isEmpty(list)){
        printf("Lista Vazia\n");
        return;
    }

    printf("------Listas de Funcionarios------\n");
    while (pointer != NULL){
        printf("Nome: %s\n", pointer->data.nome);
        printf("Salario: R$%.2f\n", pointer->data.salario);
        printf("\n");
        pointer = pointer->next;
    }
    printf("\n");
}
void printListMaiorSalario(List* list, float mairosalario){
    Node* pointer = list->head;

    if (isEmpty(list)){
        printf("Lista Vazia\n");
        return;
    }

    printf("------Listas de Funcionario(s) com maior salario------\n");
    while (pointer != NULL){
        if(pointer->data.salario == mairosalario){
            printf("Nome: %s\n", pointer->data.nome);
            printf("Salario: R$%.2f\n", pointer->data.salario);
            printf("\n");
        }
        pointer = pointer->next;
    }
    printf("\n");
}

//retorna se a lista esta vazia
bool isEmpty(List* list){
    return(list->size ==0);
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

//troca de lugares indices
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
    nodeB->next = pointer;
}

//funcao para achar o valor minimo da lista
Node* min(List* list, int index){
    Node* pointer = atPos(list, index);
    if (pointer != NULL){
        Node* minNode = pointer;

        while (pointer != NULL){
            if(pointer->data.salario < minNode->data.salario)
                minNode = pointer;
            pointer = pointer->next;
        }
        return minNode;
    }
    return NULL;
}


//funcao para achar o valor maximo da lista
Node* max(List* list, int index){
    Node* ponteiro = atPos(list, index);
    if (ponteiro != NULL){
        Node* maxNode = ponteiro;

        while (ponteiro != NULL){
            if(ponteiro->data.salario > maxNode->data.salario)
                maxNode = ponteiro;
            ponteiro = ponteiro->next;
        }
        return maxNode;
    }
    return NULL;
}


void listaMaiorSalario(List* lista, int index){
    Node* maiorSalario = max(lista,index);
    printListMaiorSalario(lista,maiorSalario->data.salario);
}

float mediaSalarial(List* list, int index){

    Node* ponteiro = atPos(list,index);

    float mSalarial = 0.0;
    int contador = 0;

    if (ponteiro != NULL){
        mSalarial = 0.0;

        while (ponteiro != NULL){
            if(ponteiro->data.salario > -1) {
                float aux = mSalarial;
                mSalarial = aux + ponteiro->data.salario;
                contador++;
            }
            ponteiro = ponteiro->next;
        }
        return mSalarial/contador;
    }
    return 0.0;
}

int contagemFaixaSalarial(List* list, int index){

    Node* ponteiro = atPos(list,index);
    float faixaSalarial = 0.0;
    int contador = 0;
    printf("\nDigite a faixa salarial: \n");

    scanf("%f",&faixaSalarial);


    if (ponteiro != NULL){

        while (ponteiro != NULL){
            if(ponteiro->data.salario > faixaSalarial) {
                contador++;
            }
            ponteiro = ponteiro->next;
        }
        return contador;
    }
    return 0;
}

//ordena em ordem decrescente
void decSort(List* list){
    int i;
    for (i=0; i < list -> size -1; i++)
        xchgNodes(list, atPos(list, i), max (list, i));
}

int main(){
    int funcionarios;
    float salario_d;
    List* lista = createList();
    DataNode data;
    printf("------Cadastro de Funcionarios------\n");
    funcionarios = 8;
    while (funcionarios!=0){
        printf("Digite o nome do funcionario: ");
        scanf("%s", &data.nome);
        printf("Digite o salario do funcionario: ");
        scanf("%f", &data.salario);
        printf("\n");

        push(lista, data);
        funcionarios--;
    };
    decSort(lista);
    printList(lista);
    int menu = -1;
    do{
        printf("\n Escolha uma das seguintes opcoes:\n1) Verificar funcionario com maior salario\n2) Verificar a media salarial\n3) Quantidade de funcionarios com salario superior a x valor\nPara o programa encerrar digite 0: \n");
        scanf("%d", &menu);

        switch (menu){
            case 1:
                printf("\nMaior salario:\n");
                listaMaiorSalario(lista, 0);
                break;
            case 2:
                printf("\nMeedia salarial: %.2f\n", mediaSalarial(lista,0));
                break;
            case 3:
                printf("\nQuantidade de funcionarios nessa faixa salarial: %i \n",contagemFaixaSalarial(lista,0));
                break;

            default:
                break;
        }

    }while (menu != 0);
}
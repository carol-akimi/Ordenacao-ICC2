#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define QTD_TEST 28
#include <limits.h>

void bubble_sort(int *vet, int n){
    int comp = 0; int trocas = 0; //comp: comparações, trocas: trocas
    for (int i = 0; i < n; i++){
        int troca = 0; //conta a quantidade de trocas feitas
        for (int j = 0; j < n - i - 1; j++){
            //compara de dois em dois elementos, troca se 
            //o seu sucessor está na ordem incorreta 
            comp++;
            if (vet[j] > vet[j + 1]){
                int aux = vet[j]; 
                vet[j] = vet[j + 1]; 
                vet[j + 1] = aux; 
                troca = 1;
                trocas++; 
            }
        }
        //se não ocorreu nenhuma troca, o vetor está ordenado, encerra o laço
        if(troca == 0){
            break; 
        }
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

void selection_sort(int *vet, int n){
    int comp = 0; int trocas = 0;  //comp: comparações, trocas: trocas
    for (int i = 0; i < n-1; i++){
        int min = i; //armazena a posição do menor elemento
        for (int j = i + 1; j < n; j++){
            comp++; 
            //busca se existe um elemento menor que o armazenado atualemente
            if (vet[j] < vet[min])
                min = j; 
        }
        //se um menor elemento é encontrado, há uma troca com o item de posição i   
        if(i != min){
            int aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
            trocas++; 
        }
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

void insertion_sort(int *vet, int n){
    int comp = 0; int trocas = 0; //comp: comparações, trocas: trocas
    int j; 
    for (int i = 1; i < n; i++){
        //armazena o valor atual para que não seja perdido após as movimentações
        int x = vet[i]; 
        //os elementos maiores que x são movidos uma posição para frente
        for (j = i - 1; j >= 0; j--){
            comp++; 
            if (vet[j] > x){
                vet[j+1] = vet[j]; 
                trocas++; 
            }else{
                break; 
            }
        }
        //insere o elemento na posição correta, os elementos  
        //a esquerda dessa posição já estão ordenados 
        vet[j+1] = x;
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

void shell_sort(int *vet, int inc[], int n, int n_inc){
    //inc é o vetor que armazena os intervalos que serão feitos as ordenações
    int comp = 0; int trocas = 0; //comp: comparações, trocas: trocas
    int i, j; 
    int h; 
    //itera pelos elementos de inc, que armazena as distâncias dos sub-conjuntos
    for (int k = 0; k < n_inc; k++){ //vai iterar pelos elementos de inc
        h = inc[k]; 
        //realiza uma inserção simples, mas os elementos estão 
        //separados por uma distância h 
        for (i = h; i < n; i++){
            int x = vet[i]; 
            for (j = i - h; j >= 0; j -= h){
                comp++;
                if (vet[j] > x){
                    vet[j+h] = vet[j]; 
                    trocas++; 
                }else{
                    break; 
                }
            }
            vet[j+h] = x; 
        }
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

//Função devove a mediana dados três elementos
int mediana(int a, int b, int c, int *vet){
    if((a >= b && a <= c)||(a <= b && a >= c))
        return a;
    else if((b>=a && b<=c)||(b<=a && b >= c))
        return b;
    else
        return c;
}


void quick_sort(int *vet, int inicio, int fim, int *comp, int *trocas){
    int i = inicio; 
    int j = fim; 
    //o pivo é a mediana entre o elemento do inicio, meio e fim
    int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim], vet); 
    do{
        //organiza os elementos de forma que todos a esquerda
        //sejam menores e os da direita, maiores
        while (vet[i] < pivo){
            i++; 
            (*comp)++; 
        }
        (*comp)++; 
        while (vet[j] > pivo){
            j--; 
            (*comp)++; 
        }
        (*comp)++; 
        if (i <= j){ 
            //troca os elementos se o da direita é menor que um no lado esquerdo
            int aux = vet[i]; 
            vet[i] = vet[j]; 
            vet[j] = aux; 
            i++; 
            j--; 
            (*trocas)++; 
        }
    //para a iteração quando i e j se "cruzam"
    //chama recursivamente a função para cada metade do vetor
    }while (i < j); 
        if (j > inicio)
            quick_sort(vet, inicio, j, comp, trocas); 
        if (i < fim)
            quick_sort(vet, i, fim, comp, trocas);
}

//Função que rearranja a heap em uma heap máxima, raiz com o maior elemento
void rearranjar_heap(int *heap, int tam_heap, int i, int *comp, int *trocas){
    int esq, dir, maior, aux; 
    //índices para acessar os filhos da esquerda e direita 
    esq = 2*i + 1;
    dir = 2*i + 2;
    maior = i; //armazena o índice do maior elemento 
    //verifica se estamos acessando um índice válido, se sim, verifica 
    //se existe um elemento maior que o que já está sendo armazenado 
    (*comp)++; 
    if ((esq < tam_heap) && (heap[esq] > heap[maior])){
        maior = esq; 
    }
    (*comp)++; 
    if ((dir < tam_heap) && (heap[dir] > heap[maior])){
        maior = dir; 
    }
    //realiza a troca dos elementos de posição maior e i 
    //chama recursivamente a função até que a heap esteja rearranjada
    if(maior != i){
        aux = heap[maior];
        heap[maior] = heap[i];
        heap[i] = aux;
        (*trocas)++; 
        rearranjar_heap(heap, tam_heap, maior, comp, trocas);
    }
}

//Função que constrói uma heap máxima 
void construir_heap(int *heap, int tam_heap, int *comp, int *trocas){
    //rearranja todos os nós menos os nós folhas 
    //a cada chamada esses nós são raízes de heaps máximas
    for (int i = (tam_heap/2) - 1; i >= 0; i--){
        rearranjar_heap(heap, tam_heap, i, comp, trocas); 
    }
}

void heap_sort(int *vet, int n, int *comp, int *trocas){
    //constrói a heap máxima
    construir_heap(vet, n, comp, trocas); 
    int tam_heap = n, aux; 
    //inverte de posição o nó raiz com o último nó da heap e rearranja 
    //a heap aṕos a troca, isso é feito n-1 vezes até que esteja ordenado
    for (int i = n-1; i > 0; i--){
        aux = vet[0]; 
        vet[0] = vet[i]; 
        vet[i] = aux; 
        tam_heap--; 
        (*trocas)++; 
        rearranjar_heap(vet, tam_heap, 0, comp, trocas); 
    }
}

//Função que faz a junção de dois subvetores, de forma que eles fiquem ordenados 
void intercala(int *vet, int inicio, int meio, int fim, int *comp, int *trocas){
    int i, j, k;
    int n1, n2;
    //Tamanho dos vetores 
    n1 = meio - inicio + 1;
    n2 = fim - meio; 

    int L[n1+1], R[n2+1]; 

    //Preenchimento dos vetores 
    for (i = 0; i < n1; i++){
        L[i] = vet[inicio + i]; 
    }
    L[n1] = INT_MAX; //sentinela
    for (j = 0; j < n2; j++){
        R[j] = vet[meio + j + 1]; 
    } 
    R[n2] = INT_MAX;  //sentinela2

    i = 0; j = 0; 
    for (k = inicio; k <= fim; k++){
        //compara os elementos de cada metade e os organiza de forma ordenada no 
        //vetor vet. O sentinela garante que se um dos sub-vetores não tiver elementos,
        //o restante vai ser preenchido pelo outro sub-vetor.  
        (*comp)++; 
        if (L[i] <= R[j]){
            vet[k] = L[i]; 
            i++; 
        }else{
            vet[k] = R[j]; 
            j++; 
        }
    }
}

void merge_sort(int *vet, int inicio, int fim, int *comp, int *trocas){
    //divide o vetor ao meio até que não seja mais possível e chama a função 
    //recursiva para cada metade do vetor, após as divisões a função intercala 
    //faz a junçã de forma ordenada 
    if (inicio < fim){
        int meio = (inicio+fim)/2; 
        merge_sort(vet, inicio, meio, comp, trocas);
        merge_sort(vet, meio+1, fim, comp, trocas); 
        intercala(vet, inicio, meio, fim, comp, trocas); 
    }
}

int *contagem_de_menores(int *vet, int n){
    int comp = 0, trocas = 0; 
    //armazena quantos elementos são menores que o elemento daquela posição
    int *posicao = (int*)malloc(sizeof(int)*n); 
    //zerar o vetor posicao 
    for (int i = 0; i < n; i++){
        posicao[i] = 0; 
    }
    //conta quantos elementos são menores que cada item
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--){
            comp++; 
            if (vet[i] < vet[j]){
                posicao[j]++; 
            }
            else{
                posicao[i]++;
            }   
        }
    }
    //vetor em que serão colocados os elementos ordenados
    int *sorted = (int*)malloc(sizeof(int)*n); 
    //o vetor sorted recebe o elemento no índice posicão[i], ou seja, 
    //considerando quantos elementos são menores que o analisado
    for (int i = 0; i < n; i++){
        sorted[posicao[i]] = vet[i]; 
    }    
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
    return sorted; 
}

//Função que devolve qual digito está na posição pos 
int digito(int num, int pos){
    for(int i=0; i<(pos-1); i++)
        num /= 10;

    return num % 10;
}

int *counting_sort(int *vet, int tam, int pos){
    //cada índice corresponde a um número, e a quantidade que essa posição
    //armazena é a quantidade de vezes que esse número aparece no vetor
    //nesse caso, os números são apenas de 0-9
    int tipos[10] = {0};
    //conta quantos dígitos de cada número aparecem 
    for(int i = 0; i < tam; i++){
        tipos[digito(vet[i], pos)]++;
    }
    //soma com a quantidade de vezes que o núemro anterior aparece para fornecer 
    //a posição certa em que esse número deve ocupar no vetor ordenado
    for(int i = 1; i < 10; i++)
        tipos[i] += tipos[i-1];
    //vetor ordenado
    int* sorted = malloc(tam * sizeof(int));
    //armazena os elementos no vetor ordenado de acordo com sua posição
    //determinada pelo vetor tipos, faz um decremento no vetor tipos,
    //pois a cada iteração temos menos um elemento daquele para ser inserido
    for(int i = tam-1; i >= 0; i--){
        sorted[tipos[digito(vet[i], pos)]-1] = vet[i];
        tipos[digito(vet[i], pos)]--;
    }

    free(vet);
    return sorted;
}

int *radixsort(int *vet, int tam, int n_dig){
    //n_dig armazena a quantidade máxima de dígitos que cada número possui
    //loop que itera por todos os dígitos do número, os ordenado os ordenando
    //do mais ao menos significativo utilizando o algoritmo counting sort 
    for(int i = 1; i <= n_dig; i++){
        vet = counting_sort(vet, tam, i);
    }
    printf("Quantidade de comparações: 0\n"); 
    printf("Quantidade de movimentações: 0\n"); 
    return vet; 
}

//Função que imprime os elementos de um vetor 
void imprimir_vetor(int *vet, int n){
    for (int i = 0; i < n; i++){
        printf("%d ", vet[i]); 
    }
    printf("\n"); 
}

// int main(void){
//     int n; 

//     printf("Tamanho do vetor:\n"); 
//     scanf("%d", &n); 

//     int *vet = (int*) malloc(sizeof(int)*n);
    // printf("Tamanho do vetor:\n"); 
    // scanf("%d", &n); 
    
    // int *vet = (int*) malloc(sizeof(int)*n); 
    // bubble_sort(vet, n);
    // selection_sort(vet, n);
    // insertion_sort(vet, n); 
    // int inc[] = {5, 3, 1};
    // shell_sort(vet, inc, n, 3); 
    // quick_sort(vet, 0, n-1); 
    // heap_sort(vet, n); 
    // merge_sort(vet, 0, n-1); 
    // contagem_de_menores(vet, n); 
    // radixsort(vet, n, 6); //rever isso 

//     clock_t ini, fim;
//     ini=clock();
//     bubble_sort(vet, n);
//     selection_sort(vet, n);
//     insertion_sort(vet, n); 
//     int inc[] = {5, 3, 1};
//     shell_sort(vet, inc, n, 3); 
//     quick_sort(vet, 0, n-1); 
//     heap_sort(vet, n); 
//     merge_sort(vet, 0, n-1); 
//     contagem_de_menores(vet, n); 
//     radixsort(vet, n, n_dig); //rever isso
//     fim=clock();

//     imprimir_vetor(vet, n); 
    
//     double tempo=(double)(fim-ini)/CLOCKS_PER_SEC;
//     FILE* f=fopen("results.csv", "r+");
//     fprintf(f, "%lf\n", tempo)

// }

int main(int argc, char* argv[]){
    FILE* in = fopen(argv[1], "r");
    FILE* out=fopen("results.csv", "r+");
    for(int i=0; i<QTD_TEST; i++){
        const char* filename;
        fscanf(in, " %s", filename); //le qual vai ser o arquivo teste
        FILE* input=fopen(filename, "r"); //abre o arquivo da vez
        int n;
        fscanf(input, "%d", &n);
        int *vet = (int*) malloc(sizeof(int)*n);
        for(int i=0; i<n; i++){
            fscanf(input, "%d", &vet[i]);
        }
        fclose(input);
        //imprimir_vetor(vet, n);
        clock_t ini, fim;
            ini=clock();
        bubble_sort(vet, n);
        // selection_sort(vet, n);
        // insertion_sort(vet, n);
        // int inc[] = {5, 3, 1};
        // shell_sort(vet, inc, n, 3); 
        // quick_sort(vet, 0, n-1); 
        // heap_sort(vet, n); 
        // merge_sort(vet, 0, n-1); 
        // contagem_de_menores(vet, n); 
        // radixsort(vet, n, n_dig); //rever isso
            fim=clock();
        free(vet);

        double tempo=(double)(fim-ini)/CLOCKS_PER_SEC;
        fprintf(out, "%lf, ", tempo);
        printf("%d: BUBBLE SORT TOOK %lf s for %d elements\n", i, tempo, n);
    }
    fprintf(out, "\n");

    fclose(in);
    fclose(out);
}
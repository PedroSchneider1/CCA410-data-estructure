#include <stdio.h>

/*
Especificações:
    Função hash: h(k) = k mod 7
    Tratamento de colisões: encadeamento externo
    Conjunto: {190, 322, 172, 89, 13, 4, 769, 61, 15, 76}
Tarefas:
    1. Calcule h(k) para cada valor
    2. Desenhe a tabela hash resultante
    3. Simule inserção e remoção
    4. Analise o fator de carga final
*/

#define TABLE_SIZE 10

int h(int k){
    return k % 7;
}

int main(int argc, char const *argv[])
{
    int hash[7];
    int arr[] = {190, 322, 172, 89, 13, 4, 769, 61, 15, 76};
    
    for (size_t i = 0; i < 10; i++){
        int index = h(arr[i]); // Calcula o índice usando a função de hash
        printf("h(%3d) = %d\n", arr[i], index);

        // Sondagem linear: procura a próxima posição livre
        while (hash[index] != 0)
        {
            index++; // tenta a próxima posição
            if (index >= TABLE_SIZE) // se passar do fim da tabela, volta ao início
                index = 0;
        }

            // Insere o elemento na posição encontrada
            hash[index] = arr[i];
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>   // implementar threads
#include <semaphore.h> // implementar semáforos
#include <unistd.h>
#include <ctype.h>   // para utilizar a função toupper();
#include <stdbool.h> // para uso de variáveis booleanas;

// variáveis globais:
int comparadorPrioritario[2] = {-1, 0}, comparadorSecundario[2] = {-1, 0}; // comparadores acessados pelas threads t1 e t2
int intCartasJ1[8], intCartasJ2[8];                                        // valores das cartas acessados pelas threads
int placarJ1, placarJ2;                                                    // acumuladores de placar
int rodada, vencedorRodada;                                                // contador global e vencedor da rodada
sem_t semaforo;                                                            // define o semáforo

int charToInt(char c) // função que define a pontuação por carta
{
    switch (c)
    {
    case 'J':
        return 1;
    case 'Q':
        return 2;
    case 'K':
        return 3;
    case 'A':
        return 4;
    default:
        return -1; // se o jogador insere um valor inválido o sistema atribui pontuação zero à sua escolha
    }
}

// função que define o vencedor e contabiliza o placar parcial e final
int vencedorDaRodada()
{
    if (comparadorPrioritario[0] >= comparadorSecundario[0])
    { // lógica de prioridade
        if (comparadorPrioritario[1] == 1)
        {                                                                    // verifica se o vencedor é o jogador 1
            placarJ1 = placarJ1 + intCartasJ1[rodada] + intCartasJ2[rodada]; // acumula placar para jogador 1
            return 1;                                                        // retorna o vencedor da rodada
        }
        else
        {
            placarJ2 = placarJ2 + intCartasJ1[rodada] + intCartasJ2[rodada]; // ou acumula placar para jogador 2
            return 2;                                                        // retorna o vencedor da rodada
        }
    }
    else
    { // se comparadorSecundario maior
        if (comparadorSecundario[1] == 2)
        {                                                                    // verifica se o vencedor é o jogador 2
            placarJ2 = placarJ2 + intCartasJ1[rodada] + intCartasJ2[rodada]; // acumula placar para o jogador 2
            return 2;                                                        // retorna o vencedor da rodada
        }
        else
        {
            placarJ1 = placarJ1 + intCartasJ1[rodada] + intCartasJ2[rodada]; // ou acumula placar para o jogador 1
            return 1;                                                        // retorna o vencedor da rodada
        }
    }
}

// função booleana para verificar entrada do usuário
bool verificarEscolha(int vetor[8], int tamanho)
{
    // Verificar se o vetor está integralmente preenchido
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] == 0)
        {
            printf("\nEscolha inválida, você precisa escolher 8 cartas, tente novamente: \n");
            return false;
        }
    }
    // Verificar se o vetor está preenchido com números de 1 a 4
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] < 1 || vetor[i] > 4)
        {
            printf("\nEscolha inválida, você precisa escolher apenas as cartas J, Q, K ou A, tente novamente: \n");
            return false;
        }
    }
    // Verificar se cada número não se repete mais que duas vezes
    for (int i = 1; i <= 4; i++)
    {
        int contador = 0;
        for (int j = 0; j < tamanho; j++)
        {
            if (vetor[j] == i)
            {
                contador++;
            }
        }
        if (contador > 2)
        {
            printf("\nEscolha inválida, você deve escolher 2 cartas de cada tipo, tente novamente: \n");
            return false;
        }
    }

    // Se todas as condições foram atendidas, retorna verdadeiro
    return true;
}

// função para thread1 vinculada ao Jogador 1
void *threadBody1(void *id)
{
    int jogador = 1;
    sem_wait(&semaforo); // pede acesso ao semáforo
    if (comparadorPrioritario[0] == -1)
    { // grava no contador prioritário se o mesmo estiver com valor defaut (-1)
        comparadorPrioritario[0] = intCartasJ1[rodada];
        comparadorPrioritario[1] = jogador; // grava no índice "1" o número do jogador que gravou no índice "0"
    }
    else
    {
        comparadorSecundario[0] = intCartasJ1[rodada]; // grava no contador secundário
        comparadorSecundario[1] = jogador;             // grava no índice "1" o número do jogador que gravou no índice "0"
    }
    sem_post(&semaforo); // avisa ao semáforo que já efetuou a ação
    pthread_exit(NULL);  // destrói a thread
}

// função para thread 2, similar a anterior
void *threadBody2(void *id)
{
    int jogador = 2;
    sem_wait(&semaforo);
    if (comparadorPrioritario[0] == -1)
    {
        comparadorPrioritario[0] = intCartasJ2[rodada];
        comparadorPrioritario[1] = jogador;
    }
    else
    {
        comparadorSecundario[0] = intCartasJ2[rodada];
        comparadorSecundario[1] = jogador;
    }
    sem_post(&semaforo);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    char linha[100];                          // variável para captura da linha de entrada
    char *letra;                              // para salvar o caractere oriundo da quebra da linha
    char cartasJ1[8], cartasJ2[8], caractere; // para armazenar os caracteres nos respectivos vetores
    int i, j;                                 // contadores
    char repeat;                              // variável para loop principal, usada no fim do programa

    sem_init(&semaforo, 0, 1); // inicializa o semáforo
    pthread_attr_t attr;       // declara variável attr para usar os valores padrão

    // define attribute
    pthread_attr_init(&attr);

    pthread_t threadJ1, threadJ2; // define as treads para cada jogador

    do // laço de repetição principal
    {
        system("clear || cls"); // Limpa a tela do console

        // tela de abertura
        printf("Bem-vindo ao JOGO DE CARTAS!\n\n");
        printf("Essas são as cartas.\n\n");
        printf("##### ##### ##### ##### ##### ##### ##### #####\n");
        printf("#   # #   # #   # #   # #   # #   # #   # #   #\n");
        printf("# J # # Q # # K # # A # # J # # Q # # K # # A #\n");
        printf("#   # #   # #   # #   # #   # #   # #   # #   #\n");
        printf("##### ##### ##### ##### ##### ##### ##### #####\n\n");

        printf("Pressione 'ENTER' para esolher a ordem das cartas.\n");
        while (getchar() != '\n')
            ; // lê e descarta os caracteres do buffer até encontrar '\n'

        printf("JOGADOR 1:\n\n");
        printf("Escolha a ordem em que você jogará suas cartas:\n");
        
        

        do // estrutura de repetição para viabilizar a verificação da entrada do jogador e solicitar nova entrada em caso de erro
        {
            fgets(linha, 100, stdin); // salva a linha digitada

            letra = strtok(linha, " \n");  // separa a string utilizando "espaço" ou "nova linha" como delimitador.
            i = 0;                         // contador para a função while
            while (letra != NULL && i < 8) // loop para cada quebra de string enquanto i < 8
            {
                sscanf(letra, "%c", &caractere);         // associa a quebra a um caractere
                cartasJ1[i] = toupper(caractere);        // função para converter os caracteres em maiúsculas e atribui a um vetor de char
                intCartasJ1[i] = charToInt(cartasJ1[i]); // atribui um valor inteiro para cada carta
                i++;                                     // incrementa contador
                letra = strtok(NULL, " \n");             // continua o processo de quebra de linha
            }
        } while (!verificarEscolha(intCartasJ1, 8));

        // apresenta na tela a escolha do jogador
        printf("\nA ordem das cartas escolhidas do JOGADOR 1 foram: \n\n");
        printf("##### ##### ##### ##### ##### ##### ##### #####\n");
        printf("#   # #   # #   # #   # #   # #   # #   # #   #\n");
        for (j = 0; j < i; j++)
        {
            printf("# %c # ", cartasJ1[j]);
        }
        printf("\n#   # #   # #   # #   # #   # #   # #   # #   #\n");
        printf("##### ##### ##### ##### ##### ##### ##### #####\n\n");

        printf("Pressione 'ENTER' para continuar.\n");
        while (getchar() != '\n')
            ; // lê e descarta os caracteres do buffer até encontrar '\n'

        system("clear || cls"); // Limpa a tela do console

        // repete o processo para o jogador 2
        printf("JOGADOR 2:\n\n");
        printf("Escolha a ordem em que você jogará suas cartas:\n");

        do 
        {
            fgets(linha, 100, stdin); 

            letra = strtok(linha, " \n");  
            i = 0;                         
            while (letra != NULL && i < 8) 
            {
                sscanf(letra, "%c", &caractere);         
                cartasJ2[i] = toupper(caractere);        
                intCartasJ2[i] = charToInt(cartasJ2[i]); 
                i++;                                     
                letra = strtok(NULL, " \n");             
            }
        } while (!verificarEscolha(intCartasJ2, 8));

        printf("\nA ordem das cartas escolhidas do JOGADOR 2 foram: \n\n");
        printf("##### ##### ##### ##### ##### ##### ##### #####\n");
        printf("#   # #   # #   # #   # #   # #   # #   # #   #\n");
        for (j = 0; j < i; j++)
        {
            printf("# %c # ", cartasJ2[j]);
        }
        printf("\n#   # #   # #   # #   # #   # #   # #   # #   #\n");
        printf("##### ##### ##### ##### ##### ##### ##### #####\n\n");

        printf("Pressione 'ENTER' para inciar o jogo!\n"); // inicia a apuração dos resultados

        // define placar inicial
        placarJ1 = 0;
        placarJ2 = 0;
        while (getchar() != '\n')
            ;                   // lê e descarta os caracteres do buffer até encontrar '\n'
        system("clear || cls"); // Limpa a tela do console

        rodada = 0;        // contador de rodadas
        int arg = rodada;  // definição do argumento das funções threads
        while (rodada < 8) // incia as rodadas de apuração
        {
            // inicializa as threads
            pthread_create(&threadJ1, &attr, threadBody1, &arg);
            pthread_create(&threadJ2, &attr, threadBody2, &arg);
            sleep(1); // faz a thread principal aguardar a atualização das variáveis comparativas

            // imprime na tela a escolha dos jogadores
            printf("Rodada %d:\n\n", rodada + 1);
            printf("JOGADOR 1 | JOGADOR 2\n");
            printf("  #####       #####\n");
            printf("  #   #       #   #\n");
            printf("  # %c #   X   # %c #\n", cartasJ1[rodada], cartasJ2[rodada]);
            printf("  #   #       #   #\n");
            printf("  #####       #####\n\n");

            // Chama função que verifica vencedor da rodada e atribui à uma variável além de contabilizar o placar do jogo
            vencedorRodada = vencedorDaRodada(); 

            // imprime o placar parcial do jogo
            printf("O Jogador %d venceu e rodada e ganhou %d + %d = %d pontos!\n\n",
                   vencedorRodada, intCartasJ1[rodada], intCartasJ2[rodada], intCartasJ1[rodada] + intCartasJ2[rodada]);
            printf("Placar ao final da rodada %d:\n", rodada + 1);
            printf("Jogador 1: %d pontos\n", placarJ1);
            printf("Jogador 2: %d pontos\n\n", placarJ2);
            comparadorPrioritario[0] = -1; // redefine o valor do contadorPrioritário para o defaut
            rodada++;
            if (rodada == 8)
            {
                // imprime resultado final
                printf("\nO vencedor foi o Jogador ");
                if (placarJ1 > placarJ2)
                    printf("1");
                if (placarJ2 > placarJ1)
                    printf("2");
                if (placarJ1 == placarJ2)
                    printf("%d", comparadorPrioritario[1]);
                printf("! Parabéns!!!!\n");
            }
            printf("\nPressione 'ENTER' para continuar...\n");

        while (getchar() != '\n'); // lê e descarta os caracteres do buffer até encontrar '\n'            
        }
    // opção de loop para nova partida    
    printf("\nSe deseja jogar outra partida digite 'S', ou 'N' para sair\n");
    scanf(" %c", &repeat);   
    } while (repeat == 'S' || repeat == 's'); // inicia nova partida ou encerra o programa

    printf("\n\nObrigado por jogar o JOGO DE CARTAS!\n\n");
    printf("[Autores]\n");
    printf("-Glauber Gouveia\n");
    printf("-Hiosery Gabriel\n");
    printf("-Larissa Hora\n");
    printf("-Guilherme Guimarães\n\n\n");

    pthread_exit(NULL); // destrói a thread principal

}

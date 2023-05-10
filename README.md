# :black_joker: Jogo de Cartas :black_joker:
Projeto de MATA58 - Sistemas Operacionais (2023.1)

Jogo de cartas utilizando semáforo e threads

## 📝 Sumário
- [1. Execução do jogo](#execucao_do_jogo)
- [2. Manual de utilização](#manual_de_utilizacao)
- [3. Plano de ação](#plano_de_acao)
- [4. Link para o vídeo da Demo](#video_demo)
- [5. Link para a documentação do projeto](#link_doc)
- [6. Equipe](#equipe)

## :computer: 1. Execução do jogo: <a name = "execucao_do_jogo"></a>
   - 1.1 - Primeiramente, o usuário deve baixar ou clonar a pasta diretamento do github;
   - 1.2 - Com a pasta na máquina do usuário, deve localizar o arquivo "JogoCartas.c";
   - 1.3 - Confirmando a presença do arquivo na máquina, o usuário deverá abrir o terminal em seu computador;
   - 1.4 - No terminal, o usuário deve acessar a pasta "jogo-cartas-main" (através dos comandos *ls* e *cd*) a qual o arquivo "JogoCartas.c" estará presente dentro dela;
   - 1.5 - Dentro da pasta, o usuário deve digitar "*gcc -o **NomeDoExecutavel** JogoCartas.c*" para criar o executavel do arquivo do jogo;
   - 1.6 - Criado o executavel, o usuário deve executar o arquivo, para isso, deve digitar "./**_NomeDoExecutavel_**" e o jogo será iniciado.
   - 1.7 - Bem-vindo ao JOGO DE CARTAS!

## 2. :green_book: Manual de utilização: <a name = "manual_de_utilizacao"></a>
###### Entrada dos jogadores
   - 2.1 - Assim que for executado, o compilador gera o output na parte inferior da tela. Para iniciar o jogo, pressione a tecla "Enter";
   - 2.2 - Em seguida, o JOGADOR 1 deve inserir a ordem das cartas que escolher, a fim de acumular pontos derrotando o adversário no máximo de rodadas possível, definindo uma estratégia, ou contando com a "sorte"; 
   - 2.3 - As cartas são: J, Q, K, A;
        - 2.3.1 - As cartas valem: J = 1, Q = 2, K = 3, A = 4;
        - 2.3.2 - Ou seja, A > K > Q > J;
   - 2.4 - A entrada deve ser a sequência das cartas que o jogador escolher, incluindo um espaço em branco entre cada carta, (por exemplo: J Q K A J Q K A) depois pressionar a tecla "Enter" para continuar o jogo;
   - 2.5 - Uma prévia da organização escolhida pelo JOGADOR 1 é apresentada, então pressione a tecla "Enter" para continuar;
   - 2.6 - A mesma sequência (tópico 2.2 até o tópico 2.5) acontece com o jogador 2.
###### Inicio das rodadas
   - 2.7 - Após as entradas de ambos os jogadores, o jogo começa a comparar as entradas na ordem. Quando um jogador inserir uma carta mais valiosa que a de seu oponente, o valor das cartas é somado e atribuído para o ganhador ao final de cada rodada.
        - 2.7.1 - Em caso de empate, a implementação do semáforo decide quem ganha a rodada.
   - 2.8 - Ao final de 8 rodadas um jogador é apontado como vencedor com base na soma de pontos em cada rodada. 

## :scroll: 3. Plano de ação: <a name = "plano_de_acao"></a>
| Tópico | Data | Responsável | Status |
| ------ | ---- | ----------- | ------ |
| Estudar semáforos  | 14/04/2023  | Todos | Feito
| Estudar thread e processos | 17/04/2023 | Todos  | Feito
| Definição do jogo | 18/04/2023 | Todos | Feito
| Código inicial | 23/04/2023 | Glauber | Feito
| Refinamento da definição do jogo | 25/04/2023 | Glauber e Guilherme | Feito
| Refinamento do código | 27/04/2023 | Todos | Feito
| Criação do github | 01/05/2023 | Larissa | Feito
| Criação da documentação | 01/05/2023 | Hiosery | Feito
| Criação do vídeo | 07/05/2023 | Hiosery | Feito
| Finalizar documentação | 07/05/2023 | Todos | Feito
| Ajustar o README do github | 09/05/2023 | Larissa e Guilherme | Feito
| Postagem no AVA | 11/05/2023 | Todos | Feito

## :clapper: 4. Link para o vídeo da Demo: <a name = "video_demo"></a>
https://youtu.be/y5WiFIvnVVc
## :bookmark_tabs: 5. Link para a documentação do projeto: <a name = "link_doc"></a>

https://docs.google.com/document/d/1cyS5Gpt8nmxcoKUUpCo84hIPHsNS836XhwSgp_cwOr4/edit?usp=sharing

## :woman_technologist: 6. Equipe: <a name = "equipe"></a>

Glauber Gouveia

Guilherme Guimaraes

Hiosery Gabriel

Larissa Hora

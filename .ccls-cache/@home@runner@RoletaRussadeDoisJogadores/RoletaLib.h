#include <iostream>
#include <time.h>
using namespace std;

struct ColorStruct { // Struct de Cores do terminal
  string reset = "\x1b[0m";
  string bold = "\x1b[1m";
  string italic = "\x1b[3m";
  string underline = "\x1b[4m";
  string inverse = "\x1b[7m";
  string black = "\x1b[30m";
  string red = "\x1b[31m";
  string green = "\x1b[32m";
  string yellow = "\x1b[33m";
  string blue = "\x1b[34m";
  string magenta = "\x1b[35m";
  string cyan = "\x1b[36m";
  string white = "\x1b[37m";
  string gray = "\x1b[90m";
  string bright_red = "\x1b[91m";
  string bright_green = "\x1b[92m";
  string bright_yellow = "\x1b[93m";
  string bright_blue = "\x1b[94m";
  string bright_magenta = "\x1b[95m";
  string bright_cyan = "\x1b[96m";
  string bright_white = "\x1b[97m";
  string bg_black = "\x1b[40m";
  string bg_red = "\x1b[41m";
  string bg_green = "\x1b[42m";
  string bg_yellow = "\x1b[43m";
  string bg_blue = "\x1b[44m";
  string bg_magenta = "\x1b[45m";
  string bg_cyan = "\x1b[46m";
  string bg_white = "\x1b[47m";
  string bg_gray = "\x1b[100m";
  string bg_bright_red = "\x1b[101m";
  string bg_bright_green = "\x1b[102m";
  string bg_bright_yellow = "\x1b[103m";
  string bg_bright_blue = "\x1b[104m";
  string bg_bright_magenta = "\x1b[105m";
  string bg_bright_cyan = "\x1b[106m";
  string bg_bright_white = "\x1b[107m";
};

void ClearScreeen() {
  cout << "\033[2J\033[0;0H"; // Comando para limpar a a tela
}

void PauseScreen() {
  if (system("read 0 -p") == -1) { // Comando para pausar a tela.
  }
}

template <int QuantTiros> struct TamborDaArma { //Tipo dedicado a armazenar a quantidade de rodadas do jogo e o tamanho máximo do tambor da arma.
  unsigned short int Rodadas = 3; //Tipo otimizado visando utilizar o mínimo de memória possível
  bool Tambor[QuantTiros]; //vetor booleanos  acompanhado com o tamanho máximo do tambor, se armazenar o valor verdadeiro, significa que ele está carregado, se falso, significa que ele está vazio
};

template <int EscolhaQuantVidas> struct InfosParticipantes { //Tipo dedicado a armazenar infomrações importantes do jogador
  unsigned short int Vidas = EscolhaQuantVidas; //Otimizado de maneira que economize o máximo de memória possível
  string NomeDosJogadores; // armazena o nome dos jogadores.
};



template <int QuantPlayers, int EscolhaQuantVidas> struct Participante {
  InfosParticipantes<EscolhaQuantVidas> Jogadores[QuantPlayers];
}; //Tipo dedicado exclusivamente para alocar a quanitidade de jogadores num vetor.


template <int QuantPlayers, int EscolhaQuantVidas>
bool VerificaMorte(Participante<QuantPlayers, EscolhaQuantVidas> Players){ //Essa função verifica se a vida de um dos participantes é menor ou igual a 0.
  for(int i = 0; i < QuantPlayers; i++)
    if(Players.Jogadores[i].Vidas <= 0)
      return true;

  return false;
}
/*
Lógica do tambor da arma:
0 = descarregado
1 = carregado;
*/
template <int QuantTiros> void PreencherArma(TamborDaArma<QuantTiros> &Roleta) { //Função que preenche o tambor da arma com valores verdadeiros(balas carregadas) e falsos(tambor vazio) de maneira aleatório e num certo intervalo de tempo
  srand(time(NULL)); //gera números aleatório com base no horário do computador
  int NumeroAleatorio; //intermedia o preenchimento no tambor
  int VerificaTambor = 0; //Verifica se o tambor respeita uma regra de preenchimento
  do {
    for (int i = 0; i < QuantTiros; i++) {
      NumeroAleatorio = rand() % 2; //gera o número aleatório entre  e 0 e 1
      Roleta.Tambor[i] == (NumeroAleatorio == 0) ? Roleta.Tambor[i] = false //com base no número gerado, preenche o tambor com valores falsos
                                                 : Roleta.Tambor[i] = true; // ou verdadeiros
      if (NumeroAleatorio == 0)
        VerificaTambor++; //verifica se o tambor não ultrapassou uma certa quantidade de valores vazios, assim o tambor não pode ser totalmente preenchido com valores falsos num preenchido com valores totalmente verdeiros
    }
  } while (VerificaTambor <= (QuantTiros / 2 + 1) && (VerificaTambor >= QuantTiros / 2 - 1)); //Esse laço impede que o tambor seja preenchido de maneira desbalanceada
}

template <int QuantTiros>
void ExibirBalasVerdadeiraEFalsas(TamborDaArma<QuantTiros> Roleta) { //Mostra a quantidade de balas verdeiras e falsas na arma, mas omite sua ordem
  int BalasVerdadeiras = 0, BalasFalsas = 0;
  for (int i = 0; i < QuantTiros; i++)
    Roleta.Tambor[i] == 0 ? BalasFalsas++ : BalasVerdadeiras++;
  cout << "\nHá " << BalasVerdadeiras << " balas verdadeiras.\n";
  cout << "\nHá " << BalasFalsas << " balas falsas.\n";
  PauseScreen();
  ClearScreeen();
}

template <int QuantPlayers, int EscolhaQuantVidas>
void ExibirInfos(Participante<QuantPlayers, EscolhaQuantVidas> Membros,
                 int NumPlayer) { //Essa funçã o exibe o nome do jogador e a quantidade de vidas dele durante o jogo
  ColorStruct Colors;
  cout << Colors.bright_blue << Membros.Jogadores[NumPlayer].NomeDosJogadores
       << Colors.reset << "\n";
  for (int j = 0; j < Membros.Jogadores[NumPlayer].Vidas; j++) {
    cout << Colors.magenta << "♥ " << Colors.reset;
  }
  cout << "\n";
}

template <int QuantPlayers, int EscolhaQuantVidas>
void SolicitarNomeDosJogadores(
    Participante<QuantPlayers, EscolhaQuantVidas> &Membros) {
  for (int i = 0; i < QuantPlayers; i++) { //Ao iniciar o jogo...
    cout << "\nDigite o nome do " << i + 1 << "º jogador:\n"; //...solicita o nome do jogador
    cin >> Membros.Jogadores[i].NomeDosJogadores;
    ClearScreeen();
  }
}

void Desenhos(int Select) { //Função dedicada somente a armazenar desenhos ASCII para usar durante o jogo
  ColorStruct Colors;
  switch (Select) {
  case 1:
    cout << "\n";
    cout << Colors.red << " ,-.______________,=========,  \n";
    cout << "[|  )_____________)#######((_  \n";
    cout << " /===============.-.___,--\" _\\ \n";
    cout << "\"-._,__,__[JW]____\\########/   \n";
    cout << "          \\ (  )) )####O##(    \n";
    cout << "           \\ \\___/,.#######\\   \n";
    cout << "            `====\"  \\#######\\  \n";
    cout << "                     \\#######\\ \n";
    cout << "                      )##O####|\n";
    cout << "                      )####__,\"\n";
    cout << "                      `--\"\"     \n" << Colors.reset;
    cout << "\n";
    break;
  case 2:
    cout << "\n";
    cout << " +-'~`---------------------------------/\\--         \n";
    cout << "||\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\" \\\\\\\\  \\/~)     \n";
    cout << "||                                  \\\\\\\\  \\/_     \n";
    cout << " |~~~~~~~~-________________-_________________\\ ~--_ \n";
    cout << " !---------|_________       ------~~~~~(--   )--~~  \n";
    cout << "                     \\ /~~~~\\~~\\   )--- \\_ /(       \n";
    cout << "                      ||     |  | \\   ()   \\\\       \n";
    cout << "                      \\\\____/_ / ()\\        \\\\      \n";
    cout << "                       `~~~~~~~~~-. \\        \\\\     \n";
    cout << "                                   \\ \\  <($)> \\\\    \n";
    cout << "                                    \\ \\        \\\\   \n";
    cout << "                                     \\ \\        \\\\  \n";
    cout << "                                      \\ \\        \\\\ \n";
    cout << "                                       \\ \\  ()    \\|\n";
    cout << "                                       _\\_\\__====~~~\n";
    cout << "\n";
    break;
  case 3:
    cout << "\n";
    cout << Colors.red
         << "  ..                                              \n";
    cout << "####################################  ##          \n";
    cout << "##########################        ######          \n";
    cout << "##########################mmmmmm######            \n";
    cout << "                  ########################        \n";
    cout << "                      ######--mm########  ####    \n";
    cout << "                      ####    ##  ####  ########  \n";
    cout << "                      ####  ####  ##..##########++\n";
    cout << "                        ####    ####  ############\n";
    cout << "                          ########    ############\n";
    cout << "                                        ##########\n";
    cout << "                                        ##########\n";
    cout << "                                        ##########\n";
    cout << "                                        ##########\n";
    cout << "                                        ##########\n";
    cout << "                                          ######  \n"
         << Colors.reset;
    cout << "\n";
    break;
  case 4:
    break;
    default:
    cout << "\nDessenho ASCII não encontrado\n";
  }
}

template <int QuantTiros, int QuantPlayers, int EscolhaQuantVidas>
void TiroDaArma(Participante<QuantPlayers, EscolhaQuantVidas> &Players,
                TamborDaArma<QuantTiros> Roleta, int bala, int vez) { //Essa função verifica a tomada de decisão do jogador da vez e verifica se bala da arma é verdeira ou falsa
  int EscolherAtirar;
  int Adversario;

  if (vez == 0) // "vez refere-se a quem está jogado na vez, se é o primeiro ou o segundo jogador"
    Adversario = 1; //com base nessa informação, armazena a ordem do adversário para usar na lógica de desconto de vidas
  else
    Adversario = 0; //Se vez não for a posição 0(primeiro jogador), logo, só pode ser o segundo, então adversário recebe a posição do primeiro.

  do {
    cout << "\nEm quem você deseja atirar? \n"
         << "1-Você.\n"
         << "2-Adversário.\n";
    cin >> EscolherAtirar;
    if (EscolherAtirar != 1 && EscolherAtirar != 2)
      cout << "Opção inválida, tente novamente.\n"; //Uma mensagem é exibida caso o valor digitado seja inválido
  } while (EscolherAtirar != 1 && EscolherAtirar != 2); //Laço para tratamento de erro, evitando que o usuário difite valores fora do intervalo

  //Trabalha-se com todas as possibilidades de jogo
  if (Roleta.Tambor[bala] == true && EscolherAtirar == 1) { //Se a bala for verdadeira e escolher atirar em si mesmo
    Players.Jogadores[vez].Vidas--; //vida descontada
    cout << "\nVocê atirou em si em mesmo!\n"; //Mensagem avisando que atirou em si mesmo
  }
  if (Roleta.Tambor[bala] == false && EscolherAtirar == 1) { //bala falsa e atirar em si mesmo
    cout << "\nNão havia bala no tambor\n"; //Mensagem avisando que não há balas no tambor
  }
  if (Roleta.Tambor[bala] == true && EscolherAtirar == 2) { //balas verderias e escolher atirar no adversário
    Players.Jogadores[Adversario].Vidas--; //Vida do adversário é decrementada
    cout << "\n"
         << Players.Jogadores[Adversario].NomeDosJogadores << " levou um tiro!\n"; // Mensagem avisando que o adver´sario levou um tiro
  }
  if (Roleta.Tambor[bala] == false && EscolherAtirar == 2) { //balas falsas e esvolher atirar no adversário
    cout << "\nNão havia bala no tambor\n"; //Mensagem avisando que não havia balas.
  }
}

template <int QuantPlayers, int EscolhaQuantVidas>
void ExibirVencedor(Participante<QuantPlayers, EscolhaQuantVidas> Players){ //Essa função exibe o nome do vencedor verificando se a quantidade de vidas do perdedor é igual a 0.
  int Perdedor;
  for(int i = 0; i < QuantPlayers; i++)
    if(Players.Jogadores[i].Vidas <= 0)
       Perdedor = i;

  Perdedor == 0? cout << "\nO Vencedor é " << Players.Jogadores[1].NomeDosJogadores << ".\n" : cout << "\nO Vencedor é " << Players.Jogadores[0].NomeDosJogadores << ".\n";
}

template <int QuantTiros, int QuantPlayers, int EscolhaQuantVidas>
void EscolhaAcao(Participante<QuantPlayers, EscolhaQuantVidas> &Players,
TamborDaArma<QuantTiros> Roleta, int bala, int vez) { //Função para tomar a decisão entre atirar ou usar um item dde auxílio durante o jogo
  int Escolha = 0;
  do {
    cout << "\n Escolha uma ação: \n"
         << "\n1-Atirar \n"
         << "\n2-Usar item\n";
    cin >> Escolha;
    if (Escolha != 1 && Escolha != 2) //mensagem caso escolhe fora do intervalo
      cout << "\nOpção inválida, tente novamente.\n";
  } while (Escolha != 1 && Escolha != 2); //Controle de erros
  ClearScreeen();
  switch (Escolha) {
  case 1: //caso seja escolhido o primeiro, executa a função de atirar
    TiroDaArma(Players, Roleta, bala, vez);
    break;
  case 2: //caso o segundo, chama a função de itens.
    break;
  }
}

template <int QuantTiros, int QuantPlayers, int EscolhaQuantVidas>
void RoletaRussa(Participante<QuantPlayers, EscolhaQuantVidas> Players,
                 TamborDaArma<QuantTiros> Roleta) { //Função principal que roda toda a partida
  ColorStruct Colors;
  SolicitarNomeDosJogadores(Players); //Solcita o nome dos jogadores
    for (int i = 0/*i = rodadas*/; (i < Roleta.Rodadas) && !VerificaMorte(Players); i++) { //O jogo roda enquanto todas as rodadas não tiverem passado ou enquanto nenhum jogador morre
      PreencherArma(Roleta); //A arma á preenchida de maneira aletória
      ExibirBalasVerdadeiraEFalsas(Roleta); //Exibe a quantidade de balas verdeiras ou falsas, mas omite a posição
      for (int k = 0/*k = Quantidade de tiros da balas*/; k < QuantTiros && !VerificaMorte(Players); k++) {
        for (int j = 0/*j = vez do jogador, vai alternando a cada bala*/; j < QuantPlayers && !VerificaMorte(Players); j++) {
          cout << (i + 1) << "º Rodada. \n"; //exibe a rodada atual
          cout << (k + 1) << "º Tiro. \n"; //exibe a quantidade de tiros atual da arma
          ExibirInfos(Players, 0); //Exibe a informação do primeiro jogador
          Desenhos(3); //Mostra um desenho ASCII
          ExibirInfos(Players, 1); //Exibe as informações do segundo jogador
          cout << Colors.bright_yellow << "\nVez de "
               << Players.Jogadores[j].NomeDosJogadores << ".\n"
               << Colors.reset; //Mostra de quem é a vez de jogar
          EscolhaAcao(Players, Roleta, k, j); //exibe as opções para o jogador escolher
          PauseScreen();
          ClearScreeen();
        }
      }
    }
    ExibirVencedor(Players);
}
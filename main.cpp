#include <climits>
#include <iostream>

#define EMPTY 0
#define PALS 4
#define ORS 1
#define ESPASSES 2
#define COPES 3
#define BASTONS 4
#define SOTA 10
#define CAVALL 11
#define REI 12
#define NUMEROS 12

#define NUM_CARTES 3
#define CARTES_PER_JUGADOR 3
#define GUANYA_JUGADOR 1
#define GUANYA_ORDINADOR 2

struct Carta {
  int pal;
  int numero;
};

struct Jugador {
  Carta mao[CARTES_PER_JUGADOR];
};

int Aleatori(int NumMin, int NumMax) {
  return NumMin + (rand() % (NumMax - NumMin + 1));
}

void InicialitzarBaralla(Carta baralla[]) {
  for (int index_pal = 0; index_pal < PALS; index_pal++)
    for (int index_num = 0; index_num < NUMEROS; index_num++)
      baralla[index_pal * NUMEROS + index_num] = {index_pal + 1, index_num + 1};
}

void MostrarCarta(Carta carta) {

  if (carta.numero == 0)
    std::cout << "Empty";
  else {
    switch (carta.numero) {
    case SOTA:
      std::cout << "Sota";
      break;
    case CAVALL:
      std::cout << "Cavall";
      break;
    case REI:
      std::cout << "Rei";
      break;
    default:
      std::cout << carta.numero;
      break;
    }
    std::cout << " de ";
    switch (carta.pal) {
    case COPES:
      std::cout << "Copes";
      break;
    case ESPASSES:
      std::cout << "Espasses";
      break;
    case ORS:
      std::cout << "Ors";
      break;
    case BASTONS:
      std::cout << "Bastons";
      break;
    default:
      break;
    }
  }
  std::cout << std::endl;
}

bool CompararCartes(Carta carta1, Carta carta2) {
  if (carta1.numero == carta2.numero)
    return carta1.pal > carta2.pal;
  return carta1.numero > carta2.numero;
}

void Intercanviar(Carta &carta_1, Carta &carta_2) {
  Carta carta_aux = carta_1;
  carta_1 = carta_2;
  carta_2 = carta_aux;
}

void Remenar(Carta baralla[], int numero_intercanvis) {
  for (int index = 0; index < numero_intercanvis; index++) {
    int posicio_carta_1 = Aleatori(0, NUM_CARTES - 1);
    int posicio_carta_2 = Aleatori(0, NUM_CARTES - 1);
    if (posicio_carta_1 == posicio_carta_2)
      continue;
    Intercanviar(baralla[posicio_carta_1], baralla[posicio_carta_2]);
  }
}
void RepartirCartes(Carta baralla[], Jugador &jugador, Jugador &ordinador) {
  int index_baralla = 0;
  for (int i = 0; i < CARTES_PER_JUGADOR; i++) {
    jugador.mao[i] = baralla[index_baralla++];
    ordinador.mao[i] = baralla[index_baralla++];
  }
}

bool AreThereCardsLeft(Jugador jugador, Jugador ordinador) {
  for (int i = 0; i < CARTES_PER_JUGADOR; i++) {
    if (jugador.mao[i].numero != 0 || ordinador.mao[i].numero != 0) {
      return true;
    }
  }
  return false;
}

int ObtainPlayerChoice(Jugador jugador) {
  std::cout << "Les teves cartes són: \n";
  for (int i = 0; i < CARTES_PER_JUGADOR; i++) {
    std::cout << i + 1 << ": ";
    MostrarCarta(jugador.mao[i]);
  }

  int choice;
  std::cout << "Tria una carta per jugar (1, 2, 3): " << std::endl;
  std::cin >> choice;

  while (std::cin.fail() || choice <= 0 || choice > CARTES_PER_JUGADOR ||
         jugador.mao[choice - 1].numero == 0) {
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cout << "Elecció no vàlida. Torna a triar: " << std::endl;
    std::cin >> choice;
  }
  return choice;
}

int ComputerChoice(Jugador ordinador) {
  int highest_index = 0;
  for (int i = 1; i < CARTES_PER_JUGADOR; i++) {
    if (CompararCartes(ordinador.mao[i], ordinador.mao[highest_index]))
      highest_index = i;
  }
  return highest_index;
}

void PlayCards(Carta carta_jugador, Carta carta_ordinador) {
  std::cout << "Jugues: ";
  MostrarCarta(carta_jugador);
  std::cout << "\nL'ordinador juga: ";
  MostrarCarta(carta_ordinador);
  std::cout << std::endl;
}

void AccumulatePoints(Carta carta_jugador, Carta carta_ordinador,
                      int &punts_jugador, int &punts_ordinador) {

  if (CompararCartes(carta_jugador, carta_ordinador)) {
    std::cout << "Guanyes la ronda!\n";
    punts_jugador += carta_jugador.numero;
  } else {
    std::cout << "L'ordinador guanya la ronda!\n";
    punts_ordinador += carta_ordinador.numero;
  }
}

void ReplacePlayedCard(Carta baralla[], int index_baralla, Jugador &jugador,
                       int choice) {
  if (index_baralla < NUM_CARTES) {
    jugador.mao[choice] = baralla[index_baralla + 1];
  } else {
    jugador.mao[choice] = {0, 0};
  }
}

void JugarRonda(Carta baralla[], int &index_baralla, Jugador &jugador,
                Jugador &ordinador, int &punts_jugador, int &punts_ordinador) {
  int player_choice = ObtainPlayerChoice(jugador);
  Carta carta_jugador = jugador.mao[player_choice - 1];

  int comp_choice = ComputerChoice(ordinador);
  Carta carta_ordinador = ordinador.mao[comp_choice];

  PlayCards(carta_jugador, carta_ordinador);

  AccumulatePoints(carta_jugador, carta_ordinador, punts_jugador,
                   punts_ordinador);

  ReplacePlayedCard(baralla, index_baralla, jugador, player_choice - 1);
  index_baralla++;
  ReplacePlayedCard(baralla, index_baralla, ordinador, comp_choice);
  index_baralla++;
}

int main() {
  srand(0);

  Carta baralla[NUM_CARTES];
  InicialitzarBaralla(baralla);
  Remenar(baralla, 1000);

  int index_baralla = 0;
  Jugador jugador;
  Jugador ordinador;

  RepartirCartes(baralla, jugador, ordinador);
  index_baralla += CARTES_PER_JUGADOR * 2;
  std::cout << index_baralla << std::endl;

  int punts_jugador = 0;
  int punts_ordinador = 0;
  int ronda = 0;

  do {
    std::cout << "Ronda " << ronda + 1 << ":\n";
    JugarRonda(baralla, index_baralla, jugador, ordinador, punts_jugador,
               punts_ordinador);
    ronda++;
  } while (AreThereCardsLeft(jugador, ordinador));

  std::cout << "Punts jugador: " << punts_jugador << std::endl;
  std::cout << "Punts ordinador: " << punts_ordinador << std::endl;

  if (punts_jugador > punts_ordinador) {
    std::cout << "Jugador guanya el joc!\n";
  } else if (punts_jugador < punts_ordinador) {
    std::cout << "Ordinador guanya el joc!\n";
  } else {
    std::cout << "Empat!\n";
  }

  return 0;
}

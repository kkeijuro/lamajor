#include <iostream>
#include <climits>

#define PALS 4
#define ORS 1
#define ESPASSES 2
#define COPES 3
#define BASTONS 4
#define SOTA 10
#define CAVALL 11
#define REI 12
#define NUMEROS 12

#define NUM_CARTES PALS*NUMEROS
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
    for(int index_pal = 0; index_pal < PALS; index_pal++)
        for(int index_num = 0; index_num < NUMEROS; index_num++)
            baralla[index_pal*NUMEROS + index_num] = {index_pal + 1, index_num + 1};
}

void MostrarCarta(Carta carta) {
    switch(carta.numero) {
        case SOTA: std::cout<<"Sota"; break;
        case CAVALL: std::cout<<"Cavall"; break;
        case REI: std::cout<<"Rei"; break;
        default: std::cout<<carta.numero; break;
    }
    std::cout <<" de ";
    switch(carta.pal) {
        case COPES: std::cout<<"Copes"; break;
        case ESPASSES: std::cout<<"Espasses"; break;
        case ORS: std::cout<<"Ors"; break;
        case BASTONS: std::cout<<"Bastons"; break;
        default: break;
    }
}

int CompararCartes(const Carta carta1, const Carta carta2) {
    if (carta1.numero == carta2.numero) 
        return carta1.pal > carta2.pal ? GUANYA_JUGADOR : GUANYA_ORDINADOR;
    return carta1.numero > carta2.numero ? GUANYA_JUGADOR : GUANYA_ORDINADOR;
}

void Intercanviar(Carta& carta_1, Carta& carta_2) {
    Carta carta_aux = carta_1;
    carta_1 = carta_2;
    carta_2 = carta_aux;
}

void Remenar(Carta baralla[], int numero_intercanvis) {
    for(int index = 0; index < numero_intercanvis; index++) {
        int posicio_carta_1 = Aleatori(0, NUM_CARTES-1);
        int posicio_carta_2 = Aleatori(0, NUM_CARTES-1);
        if(posicio_carta_1 == posicio_carta_2) continue;
        Intercanviar(baralla[posicio_carta_1], baralla[posicio_carta_2]);
    }
}
void RepartirCartes(Carta baralla[], int& index_baralla, Jugador& jugador, Jugador& ordinador) {
    for (int i = 0; i < CARTES_PER_JUGADOR; i++) {
        jugador.mao[i] = baralla[index_baralla++];
        ordinador.mao[i] = baralla[index_baralla++];
    }
}

void JugarRonda(Carta baralla[], int& index_baralla, Jugador& jugador, Jugador& ordinador, int& punts_jugador, int& punts_ordinador) {
    // Display player's hand and prompt for choice
    std::cout << "Les teves cartes són: \n";
    for (int i = 0; i < CARTES_PER_JUGADOR; i++) {
        std::cout << i + 1 << ": ";
        MostrarCarta(jugador.mao[i]);
        std::cout << std::endl;
    }

    int choice;
 
    std::cout << "Tria una carta per jugar (1, 2, 3): ";
    std::cin >> choice;
    while (std::cin.fail() || choice <= 0 || choice >= CARTES_PER_JUGADOR){
      std::cin.clear(); // clear input buffer to restore cin to a usable state
      std::cin.ignore(INT_MAX, '\n'); // ignore last input
      std::cout << "Només podeu introduir números 1, 2 o 3.\n";
      std::cin >> choice;
    }
   

    Carta carta_jugador = jugador.mao[choice - 1];

    // Computer selects the highest card in hand
    int highest_index = 0;
    for (int i = 1; i < CARTES_PER_JUGADOR; i++) {
        if (CompararCartes(ordinador.mao[i], ordinador.mao[highest_index]) == GUANYA_JUGADOR)
            highest_index = i;
    }
    Carta carta_ordinador = ordinador.mao[highest_index];
    // Show the cards played
    std::cout << "Jugues: ";
    MostrarCarta(carta_jugador);
    std::cout << "\nL'ordinador juga: ";
    MostrarCarta(carta_ordinador);
    std::cout << std::endl;

  // Compare the cards and update points
    if (CompararCartes(carta_jugador, carta_ordinador) == GUANYA_JUGADOR) {
        std::cout << "Guanyes la ronda!\n";
        punts_jugador += carta_jugador.numero;
    } else {
        std::cout << "L'ordinador guanya la ronda!\n";
        punts_ordinador += carta_ordinador.numero;
    }

    // Replace played cards if cards are left in the deck
    if(index_baralla < NUM_CARTES) {
        jugador.mao[choice - 1] = baralla[index_baralla++];
        ordinador.mao[highest_index] = baralla[index_baralla++];
    }
}


int main() {
    srand(0);
    
    Carta baralla[NUM_CARTES];
    InicialitzarBaralla(baralla);
    Remenar(baralla, 1000);
    
    int index_baralla = 0;
    Jugador jugador;
    Jugador ordinador;

    RepartirCartes(baralla, index_baralla, jugador, ordinador);

    int punts_jugador = 0;
    int punts_ordinador = 0;

    for (int ronda = 0; ronda < NUM_CARTES / CARTES_PER_JUGADOR; ronda++) {
        std::cout << "Ronda " << ronda + 1 << ":\n";
        JugarRonda(baralla, index_baralla, jugador, ordinador, punts_jugador, punts_ordinador);
        if (index_baralla >= NUM_CARTES)
            break;
    }

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
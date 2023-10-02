#include <iostream>
#include <stdlib.h>

#define PALS 4
#define COPES 1
#define ESPASSES 2
#define ORS 3
#define BASTONS 4
#define SOTA 10
#define CAVALL 11
#define REI 12
#define NUMEROS 12

#define NUM_CARTES PALS*NUMEROS

#define EMPAT 0
#define GUANYA_JUGADOR 1
#define GUANYA_ORDINADOR 2

int Aleatori(int NumMin, int NumMax)
{
    int NumAleatori;

    NumAleatori = NumMin + (rand() % (NumMax - NumMin + 1));

    return NumAleatori;
}

typedef struct {
    int pal;
    int numero;
} Carta;


void InicialitzarBaralla(Carta baralla[]) {
    for(int index_pal = 0; index_pal < PALS; index_pal++)
        for(int index_num = 0; index_num < NUMEROS; index_num++)
            baralla[index_pal*NUMEROS + index_num] = Carta{index_pal + 1, index_num + 1};
}

void MostrarCarta(const Carta& carta) {
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

int main() {

}

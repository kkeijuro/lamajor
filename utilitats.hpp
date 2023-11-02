#pragma once

#define PALS_BARALLA 4
#define BASTONS 1
#define COPES 2
#define ESPASES 3
#define ORS 4

#define SOTA 10
#define CAVALL 11
#define REI 12
#define NUMEROS_BARALLA 12
#define NUM_CARTES_BARALLA PALS_BARALLA*NUMEROS_BARALLA

#define PAL_CARTA_BUIT 0
#define NUMERO_CARTA_BUIT 0

#define INDEX_NO_TROBAT -1

#define CARTES_PER_JUGADOR 3

#define GUANYA_HUMA 1
#define GUANYA_ORDINADOR 2

struct Carta {
    int pal;
    int numero;
};

struct Jugador {
    Carta ma[CARTES_PER_JUGADOR];
    Carta pila[NUM_CARTES_BARALLA];
};

void Inicialitzar(Carta cartes[], int nCartes);
void InicialitzarBarallaEspanyola(Carta baralla[]);
void MostrarCarta(Carta carta);
void MostrarCartes(Carta cartes[], int nCartes);
bool EsCartaBuida(Carta carta);
int IndexCartaAmbValor(Carta cartes[], int nCartes);
int IndexCartaSenseValor(Carta cartes[], int nCartes);
void Intercanviar(Carta &carta_1, Carta &carta_2);
void Remenar(Carta baralla[], int nCartes, int numero_intercanvis);
Carta AgafarCarta(Carta cartes[], int nCartes);
void OrdenarCartes(Carta cartes[], int nCartes);
bool CompararCartes(Carta carta1, Carta carta2);
void AfegirCarta(Carta cartes[], int nCartes, Carta carta);
void SubstituirCartaBuida(Carta fontCartes[], int nCartesFont, Carta receptorCartes[], int nCartesReceptor);

Carta ObtindreSeleccioHuma(Jugador& jugador, int nCartes);
Carta SeleccioOrdinador(Jugador& ordinador, int nCartes, Carta carta_jugador);
int PuntsCartes(Carta cartes[], int nCartes);
int JugarRonda(Carta baralla[], Jugador &jugador, Jugador &ordinador, bool es_ordinador_primer);
void JugarLaMajor(Carta baralla[], Jugador& huma, Jugador& ordinador);
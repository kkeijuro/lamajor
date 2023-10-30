#include <iostream>
#include "utilitats.hpp"

int Aleatori(int NumMin, int NumMax) {
    return NumMin + (rand() % (NumMax - NumMin + 1));
}

void InicialitzarBarallaEspanyola(Carta baralla[]) {
    for (int index_pal = 0; index_pal < PALS_BARALLA; index_pal++)
        for (int index_num = 0; index_num < NUMEROS_BARALLA; index_num++)
            baralla[index_pal * NUMEROS_BARALLA + index_num] = {index_pal + 1, index_num + 1};
}

void MostrarCarta(Carta carta) {
    if(EsCartaBuida(carta)) return;
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
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            std::cout << carta.numero;
        default:
            break;
    }
    std::cout << " de ";
    switch (carta.pal) {
        case COPES:
            std::cout << "Copes";
            break;
        case ESPASES:
            std::cout << "Espases";
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
    std::cout << std::endl;
}

void MostrarCartes(Carta cartes[], int nCartes) {
    for(int i = 0; i < nCartes; i++) {
        MostrarCarta(cartes[i]);
    }
}

bool EsCartaBuida(Carta carta) {
    return (carta.numero == NUMERO_CARTA_BUIT && carta.pal == PAL_CARTA_BUIT);
}

int IndexCartaAmbValor(Carta cartes[], int nCartes) {
    int index_carta = 0;
    while((EsCartaBuida(cartes[index_carta])) && (index_carta < nCartes)){
        index_carta++;
    }
    if (index_carta >= nCartes) return INDEX_NO_TROBAT;
    return index_carta;
}

int IndexCartaSenseValor(Carta cartes[], int nCartes) {
    int index_carta = 0;
    while((!EsCartaBuida(cartes[index_carta])) && (index_carta < nCartes)) {
        index_carta++;
    };
    if (index_carta >= nCartes) return INDEX_NO_TROBAT;
    return index_carta;
}

void Intercanviar(Carta &carta_1, Carta &carta_2) {
    Carta carta_aux = carta_1;
    carta_1 = carta_2;
    carta_2 = carta_aux;
}

void Remenar(Carta baralla[], int nCartes, int numero_intercanvis) {
    for (int index = 0; index < numero_intercanvis; index++) {
        int posicio_carta_1 = Aleatori(0, nCartes - 1);
        int posicio_carta_2 = Aleatori(0, nCartes - 1);
        if (posicio_carta_1 == posicio_carta_2)
            continue;
        Intercanviar(baralla[posicio_carta_1], baralla[posicio_carta_2]);
    }
}

Carta AgafarCarta(Carta cartes[], int nCartes) {
    int index = IndexCartaAmbValor(cartes, nCartes);
    if(index == INDEX_NO_TROBAT) return {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
    Carta carta_seleccionada = cartes[index];
    cartes[index] = {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
    return carta_seleccionada;
}

bool CompararCartes(Carta carta1, Carta carta2) {
    if (carta1.numero == carta2.numero)
        return carta1.pal > carta2.pal;
    return carta1.numero > carta2.numero;
}

void OrdenarCartes(Carta cartes[], int nCartes) {
    Carta t;
    for(int i = 0; i < nCartes; i++) {
        for (int j = 0; j < nCartes - i - 1; j++) {
            if (CompararCartes(cartes[j + 1], cartes[j])) /* orden ascendente */
            {
                t = cartes[j];
                cartes[j] = cartes[j + 1];
                cartes[j + 1] = t;
            }
        }
    }
}

void AfegirCarta(Carta cartes[], int nCartes, Carta carta) {
    int index = IndexCartaSenseValor(cartes, nCartes);
    if(index >= nCartes) return;
    cartes[index] = carta;
}

void SubstituirCartaBuida(Carta fontCartes[], int nCartesFont, Carta receptorCartes[], int nCartesReceptor) {
    Carta carta = AgafarCarta(fontCartes, nCartesFont);
    AfegirCarta(receptorCartes, nCartesReceptor, carta);
}


Carta ObtindreSeleccioHuma(Jugador& jugador) {
    std::cout << "Les teves cartes són: \n";
    for (int i = 0; i < CARTES_PER_JUGADOR; i++) {
        if(!EsCartaBuida(jugador.ma[i])) {
            std::cout << i + 1 <<": ";
            MostrarCarta(jugador.ma[i]);
        }
    }
    int choice;
    std::cout << "Tria una carta per jugar: " << std::endl;
    std::cin >> choice;

    while (std::cin.fail() || choice <= 0 || choice > CARTES_PER_JUGADOR ||
           jugador.ma[choice - 1].numero == 0) {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Elecció no vàlida. Torna a triar: " << std::endl;
        std::cin >> choice;
    }
    choice--;
    std::cout << "Opcio: "<< choice<< std::endl;
    Carta carta = jugador.ma[choice];
    jugador.ma[choice] = Carta{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
    OrdenarCartes(jugador.ma, CARTES_PER_JUGADOR);
    return carta;
}

Carta SeleccioOrdinador(Jugador& ordinador, Carta carta_jugador) {
    std::cout << "Cartes Ordinador: "<<std::endl;
    MostrarCartes(ordinador.ma, CARTES_PER_JUGADOR);
    Carta carta = ordinador.ma[1];
    ordinador.ma[1] = Carta{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
    OrdenarCartes(ordinador.ma, CARTES_PER_JUGADOR);
    return carta;
}


int PuntsCartes(Carta cartes[], int nCartes) {
    int punts_totals = 0;
    int index = 0;
    while(!EsCartaBuida(cartes[index]) && (index <= nCartes)) {
        punts_totals += cartes[index].numero;
        index++;
    }
    return punts_totals;
}

void MostrarJugada(Carta carta_jugador, Carta carta_ordinador) {
    std::cout << "Jugues: ";
    MostrarCarta(carta_jugador);
    std::cout << "\nL'ordinador juga: ";
    MostrarCarta(carta_ordinador);
    std::cout << std::endl;
}

void RepartirCartes(Carta cartes[], int nCartes, Jugador &jugador, Jugador &ordinador, int cartesRepartir) {
    int i = IndexCartaAmbValor(cartes, nCartes);
    for (; i < cartesRepartir; i++) {
        jugador.ma[i] = AgafarCarta(cartes, nCartes);
        ordinador.ma[i] = AgafarCarta(cartes, nCartes);
    }
}

int JugarRonda(Carta baralla[], Jugador &jugador, Jugador &ordinador, bool es_ordinador_primer) {
    int resultat_ronda;
    Carta carta_usuari;
    Carta carta_ordinador;
    if(es_ordinador_primer) {
        carta_ordinador = SeleccioOrdinador(ordinador, Carta{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT});
        carta_usuari = ObtindreSeleccioHuma(jugador);
    }
    else {
        carta_usuari = ObtindreSeleccioHuma(jugador);
        carta_ordinador = SeleccioOrdinador(ordinador, carta_usuari);
    }
    MostrarJugada(carta_usuari, carta_ordinador);
    if(CompararCartes(carta_usuari, carta_ordinador)) {
        //Guardar punts Huma
        std::cout << "Guanya Huma!"<<std::endl;
        resultat_ronda = GUANYA_HUMA;
        AfegirCarta(jugador.pila, NUM_CARTES_BARALLA, carta_usuari);
        AfegirCarta(jugador.pila, NUM_CARTES_BARALLA, carta_ordinador);
    }
    else {
        //Guardar Punts Ordinador
        std::cout << "Guanya Ordinador!"<<std::endl;
        AfegirCarta(ordinador.pila, NUM_CARTES_BARALLA, carta_usuari);
        AfegirCarta(ordinador.pila, NUM_CARTES_BARALLA, carta_ordinador);
        resultat_ronda = GUANYA_ORDINADOR;
    }
    std::cout << "Pila Huma: "<<std::endl;
    MostrarCartes(jugador.pila, NUM_CARTES_BARALLA);
    std::cout << "Pila Ordinador: "<<std::endl;
    MostrarCartes(ordinador.pila, NUM_CARTES_BARALLA);
    //AcumularPunts(carta_jugador, carta_ordinador, punts_jugador,
    //                punts_ordinador);

    SubstituirCartaBuida(baralla, NUM_CARTES_BARALLA, jugador.ma, CARTES_PER_JUGADOR);
    SubstituirCartaBuida(baralla, NUM_CARTES_BARALLA, ordinador.ma, CARTES_PER_JUGADOR);

    return resultat_ronda;
}

void JugarLaMajor(Carta baralla[], Jugador& huma, Jugador& ordinador) {
    InicialitzarBarallaEspanyola(baralla);
    Inicialitzar(huma.pila, NUM_CARTES_BARALLA);
    Inicialitzar(ordinador.pila, NUM_CARTES_BARALLA);

    Remenar(baralla, NUM_CARTES_BARALLA, 1000);
    RepartirCartes(baralla, NUM_CARTES_BARALLA, huma, ordinador, CARTES_PER_JUGADOR);
    OrdenarCartes(huma.ma, CARTES_PER_JUGADOR);
    OrdenarCartes(ordinador.ma, CARTES_PER_JUGADOR);
    bool es_ordinador_primer = false;

    int ronda = 0;

    do {
        std::cout << "Ronda " << ronda + 1 << ":\n";
        int resultat_ronda = JugarRonda(baralla, huma, ordinador, es_ordinador_primer);
        if (resultat_ronda == GUANYA_ORDINADOR) es_ordinador_primer = true;
        else es_ordinador_primer = false;
        ronda++;
        std::cout << "Ronda: "<< ronda<<" Cartes: "<< IndexCartaAmbValor(baralla, NUM_CARTES_BARALLA) << " Cartes: " << NUM_CARTES_BARALLA<<std::endl;
    } while (IndexCartaAmbValor(baralla, NUM_CARTES_BARALLA) < NUM_CARTES_BARALLA);
}

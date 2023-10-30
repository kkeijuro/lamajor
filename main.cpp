#include <iostream>

#include "utilitats.hpp"


void Inicialitzar(Carta cartes[], int nCartes) {
    for (int index = 0; index < nCartes; index++)
        cartes[index] = Carta{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
}

void InicialitzarBarallaEspanyolaTest(Carta baralla[]) {
    for (int index_pal = 0; index_pal < PALS_BARALLA; index_pal++)
        for (int index_num = 0; index_num < NUMEROS_BARALLA; index_num++)
            baralla[index_pal * NUMEROS_BARALLA + index_num] = {index_pal + 1, index_num + 1};
}

bool TestInicalitzarBaralla() {
    std::cout << "Comment :=>>----- TEST: Funció InicialitzarBarallaEspanyola -----" << std::endl;
    bool testCorrecte = true;
    Carta baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyola(baralla);
    for(int index_pal = 0; index_pal < PALS_BARALLA;index_pal++) {
        for(int index_num = 0; index_num < NUMEROS_BARALLA;index_num++) {
            Carta carta1 = {index_pal + 1, index_num + 1};
            Carta carta2 = baralla[index_pal * NUMEROS_BARALLA + index_num];
            if(carta1.pal != carta2.pal || carta1.numero != carta2.numero)
             {
                testCorrecte = false;
                break;
            }
        }
    }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test InicialitzarBarallaEspanyola: CORRECTE!" << std::endl<< std::endl;
    }
    else {
        std::cout << "Comment :=>> Test InicialitzarBarallaEspanyola: ERROR - Revisa que la funcio InicialitzarBarallaEspanyola es correcte"
                  << std::endl<< std::endl;
    }
    return testCorrecte;
}

bool TestCartaBuida() {
    std::cout << "Comment :=>>----- TEST: Funció EsCartaBuida -----" << std::endl;
    bool testCorrecte = true;
    Carta carta_buida = {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
    if(!EsCartaBuida(carta_buida)) testCorrecte = false;

    Carta baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyola(baralla);
    for(int index_pal = 0; index_pal < PALS_BARALLA;index_pal++) {
        for(int index_num = 0; index_num < NUMEROS_BARALLA;index_num++) {
            Carta carta = baralla[index_pal * NUMEROS_BARALLA + index_num];
            if (EsCartaBuida(carta)) testCorrecte = false;
            }
        }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test EsCartaBuida: CORRECTE!" << std::endl<< std::endl;
    }
    else {
        std::cout << "Comment :=>> Test EsCartaBuida: ERROR - Revisa que la funcio EsCartaBuida es correcte"
                  << std::endl<< std::endl;
    }
    return testCorrecte;
}

bool TestIndexCarta() {
    std::cout << "Comment :=>>----- TEST: IndexCartaAmbValor/IndexCartaSenseValor -----" << std::endl;
    bool testIndexAmbValorCorrecte = true;
    bool testIndexSenseValorCorrecte = true;

    int tamany_baralla = NUM_CARTES_BARALLA*2;
    Carta baralla_test[NUM_CARTES_BARALLA*2];

    for(int index = 0; index <= tamany_baralla;index++)
        baralla_test[index] =  {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};

    // Tota la baralla amb cartes buides
    if (IndexCartaAmbValor(baralla_test, tamany_baralla) != INDEX_NO_TROBAT)
        testIndexAmbValorCorrecte = false;
    if (IndexCartaSenseValor(baralla_test, tamany_baralla) != 0)
        testIndexSenseValorCorrecte = false;

    // Substituim els valors de la carta d'un a un de buida a valor
    // Comprovem que els index SenseValor van canviant
    for(int index = 0; index < tamany_baralla - 1; index++) {
        baralla_test[index] = Carta{ORS, 1};
        if (IndexCartaSenseValor(baralla_test, tamany_baralla) != index + 1){
            testIndexSenseValorCorrecte = false;
        }
        if(IndexCartaAmbValor(baralla_test, tamany_baralla) != 0) {
            testIndexAmbValorCorrecte = false;
        }
    }

    // Assignem un valor a l'ultima carta del array (abans no ho hem fet)
    baralla_test[tamany_baralla - 1] = Carta{ORS, 1};

    // Tota la baralla amb cartes amb valor
    if (IndexCartaAmbValor(baralla_test, tamany_baralla) != 0)
        testIndexAmbValorCorrecte = false;
    if (IndexCartaSenseValor(baralla_test, tamany_baralla) != INDEX_NO_TROBAT)
        testIndexSenseValorCorrecte = false;

    // Substituim els valors de la carta d'un a un de valor a buida
    // Comprovem que els index Carta amb valor van canviant
    for(int index = 0; index < tamany_baralla - 1; index++) {
        baralla_test[index] = Carta{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
        if(IndexCartaSenseValor(baralla_test, tamany_baralla) != 0) {
            testIndexSenseValorCorrecte = false;
            break;
        }
        if(IndexCartaAmbValor(baralla_test, tamany_baralla) != index + 1) {
            testIndexAmbValorCorrecte = false;
            break;
        }
    }

    // Assignem carta buida a l'ultima carta del array (abans no ho hem fet)
    baralla_test[tamany_baralla - 1] = Carta{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};

    // Substituim els valors de la carta d'un a un de buida a valor
    // Comprovem que els index SenseValor van canviant
    for(int index = tamany_baralla - 1; index >= 1; index--) {
        baralla_test[index] = Carta{ORS, 1};
        if(IndexCartaSenseValor(baralla_test, tamany_baralla) != 0) {
            testIndexSenseValorCorrecte = false;
            break;
        }
        if(IndexCartaAmbValor(baralla_test, tamany_baralla) != index) {
            testIndexAmbValorCorrecte = false;
            break;
        }
    }

    // Assignem carta buida a la primera carta del array (abans no ho hem fet)
    baralla_test[0] =  Carta{ORS, 1};
    // Substituim els valors de la carta d'un a un de valor a buida
    // Comprovem que els index Carta amb valor van canviant
    for(int index = tamany_baralla - 1; index >= 1; index--) {
        baralla_test[index] = Carta{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT};
        if(IndexCartaSenseValor(baralla_test, tamany_baralla) != index) {
            testIndexSenseValorCorrecte = false;
            break;
        }
        if(IndexCartaAmbValor(baralla_test, tamany_baralla) != 0) {
            testIndexAmbValorCorrecte = false;
            break;
        }
    }
    if(testIndexSenseValorCorrecte && testIndexAmbValorCorrecte) {
        std::cout << "Comment :=>> Test IndexCartaAmbValor/IndexCartaSenseValor: Correcte!"<<std::endl<< std::endl;
    }
    else {
        if(!testIndexAmbValorCorrecte)
            std::cout << "Comment :=>> Test IndexCartaAmbValor/IndexCartaSenseValor: ERROR! : Comprova IndexCartaAmbValor"<<std::endl<< std::endl;
        if(!testIndexSenseValorCorrecte)
            std::cout << "Comment :=>> Test IndexCartaAmbValor/IndexCartaSenseValor: ERROR! : Comprova IndexCartaSenseValor"<<std::endl<< std::endl;
    }
    return testIndexSenseValorCorrecte && testIndexAmbValorCorrecte;
}

bool TestIntercanviar() {
    std::cout << "Comment :=>>----- TEST: Funció Intercanviar -----" << std::endl;

    bool TestCorrecte = true;
    int Num0, Num1;
    int Pal0, Pal1;

    Carta Baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyola(Baralla);

    Num0 = Baralla[0].numero;
    Pal0 = Baralla[0].pal;
    Num1 = Baralla[1].numero;
    Pal1 = Baralla[1].pal;

    Intercanviar(Baralla[0], Baralla[1]);

    if (Baralla[0].numero == Num1 && Baralla[0].pal == Pal1 && Baralla[1].numero == Num0 && Baralla[1].pal == Pal0) {
        TestCorrecte = TestCorrecte && true;
        std::cout << "Comment :=>> Test Intercanviar: CORRECTE!" << std::endl << std::endl;

    } else {
        std::cout << "Comment :=>> Test Intercanviar: ERROR - Revisa les funcions InicialitzarBaralla i Intercanviar." << std::endl << std::endl;
        TestCorrecte = false;
    }

    return TestCorrecte;
}

bool TestRemenar() {
    std::cout << "Comment :=>>----- TEST: Funcio Remenar -----" << std::endl;
    bool TestCorrecte = true;
    int Canvis;

    int seed = 46;
    srand(seed);

    Carta Baralla1[NUM_CARTES_BARALLA];
    Carta Baralla2[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyola(Baralla1);
    InicialitzarBarallaEspanyola(Baralla2);

    Remenar(Baralla1, NUM_CARTES_BARALLA, 0);
    Canvis = 0;
    for (int i = 0; i < NUM_CARTES_BARALLA; i++) {
        if ((Baralla1[i].numero != Baralla2[i].numero) || (Baralla1[i].pal != Baralla2[i].pal)) {
            Canvis++;
        }
    }

    if (Canvis == 0) {
        TestCorrecte = TestCorrecte && true;
        std::cout << "Comment :=>> Test Remenar Sense Intercanvis: CORRECTE!" << std::endl;
    } else {
        TestCorrecte = false;
        std::cout << "Comment :=>> Test Remenar Sense Intercanvis: ERROR - Revisa la funcio Remenar. Quin comportament te la funcio quan el NumIntercanvis es 0?" << std::endl;
    }


    Remenar(Baralla1, NUM_CARTES_BARALLA, 10);
    Canvis = 0;
    for (int i = 0; i < NUM_CARTES_BARALLA; i++) {
        if ((Baralla1[i].numero != Baralla2[i].numero) || (Baralla1[i].pal != Baralla2[i].pal)) {
            Canvis++;
        }
    }

    if (Canvis == 14) {
        TestCorrecte = TestCorrecte && true;
        std::cout << "Comment :=>> Test Remenar: CORRECTE!" << std::endl << std::endl;

    } else {
        TestCorrecte = false;
        std::cout << "Comment :=>> Test Remenar: ERROR - Revisa la funcio Remenar." << std::endl << std::endl;
    }

    return TestCorrecte;
}

bool TestCompararCartes() {
    std::cout << "Comment :=>>----- TEST: Funcio CompararCartes -----" << std::endl;
    bool TestCorrecte = true;
    Carta ComparacionsA[] = {{ORS, 1}, {ESPASES, 5}, {BASTONS, 3}, {COPES, 5}, {ESPASES, 5}};
    Carta ComparacionsB[] = {{ORS, 2}, {ESPASES, 4}, {ORS, 3}, {COPES, 5}, {COPES, 5}};
    bool resultat[] = {false, true, false, false, true};

    for(int index = 0; index < 5; index++) {
        bool resultat_comparacio = CompararCartes(ComparacionsA[index], ComparacionsB[index]);
        if(resultat_comparacio != resultat[index]) {
            TestCorrecte = false;
        }
    }
    if(TestCorrecte)
        std::cout << "Comment :=>> Test CompararCartes: CORRECTE!" << std::endl<<std::endl;
    else
        std::cout << "Comment :=>> Test CompararCartes: ERROR!" << std::endl<<std::endl;
    return TestCorrecte;
}


bool TestAgafarCarta() {
    std::cout << "Comment :=>>----- TEST: Funcio AgafarCarta -----" << std::endl;
    bool TestCorrecte = true;
    Carta baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyolaTest(baralla);
    for (int index_pal = 0; index_pal < PALS_BARALLA; index_pal++)
        for (int index_num = 0; index_num < NUMEROS_BARALLA; index_num++) {
            Carta carta1 = AgafarCarta(baralla, NUM_CARTES_BARALLA);
            Carta carta2 = {index_pal + 1, index_num + 1};
            if(carta1.pal != carta2.pal || carta1.numero != carta2.numero)
                TestCorrecte = false;
        }
    if(!TestCorrecte) {
        std::cout << "Comment :=>> Test AgafarCarta: ERROR - Revisa la funcio AgafarCarta." << std::endl;
    }
    MostrarCartes(baralla, NUM_CARTES_BARALLA);
    Carta carta = AgafarCarta(baralla, NUM_CARTES_BARALLA);
    if(!EsCartaBuida(carta)) {
        MostrarCarta(carta);
        TestCorrecte = false;
        std::cout << "Comment :=>> Test Remenar: ERROR - Revisa la funcio AgafarCarta. Que passa quan no hi han cartes?"
                  << std::endl;
    }
    if(TestCorrecte)
        std::cout << "Comment :=>> Test AgafarCarta: CORRECTE!" << std::endl<<std::endl;
    else
        std::cout << "Comment :=>> Test AgafarCarta: ERROR!" << std::endl<<std::endl;
    return TestCorrecte;
}

bool TestInicialitzar() {
    bool TestCorrecte = true;
    return TestCorrecte;
}

bool TestSubstituirCarta() {
    bool TestCorrecte = true;
    return TestCorrecte;
}

bool TestAfegirCarta() {
    bool TestCorrecte = true;
    return TestCorrecte;
}

bool TestSeleccioHuma() {
    bool TestCorrecte = true;
    return TestCorrecte;
}

bool TestSeleccioOrdinador() {
    bool TestCorrecte = true;
    return TestCorrecte;
}

bool TestPuntsCartes() {
    bool TestCorrecte = true;
    return TestCorrecte;
}


int main() {
    int grade = 0;
    bool resultatTest;
    resultatTest = TestInicalitzarBaralla();
    if(resultatTest)
        grade += 5;


    resultatTest = TestCartaBuida();
    if(resultatTest)
        grade += 5;

    resultatTest = TestIndexCarta();
    if(resultatTest)
        grade += 10;

    resultatTest = TestIntercanviar();
    if(resultatTest)
        grade += 5;

    resultatTest = TestRemenar();
    if(resultatTest)
        grade += 5;

    resultatTest = TestAgafarCarta();
    if(resultatTest)
        grade += 5;

    resultatTest = TestCompararCartes();
    if(resultatTest)
        grade += 5;

    std::cout << "Grade :=>> " << grade << std::endl;
}
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "utilitats.hpp"
#include "solucions.hpp"
 
bool TestInicalitzarBaralla() {
    std::cout << "Comment :=>>----- TEST: Funció InicialitzarBarallaEspanyola -----" << std::endl;
    bool testCorrecte = true;
    Carta baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyolaT(baralla);
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
    InicialitzarBarallaEspanyolaT(baralla);
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

    bool testCorrecte = true;
    int Num0, Num1;
    int Pal0, Pal1;

    Carta Baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyolaT(Baralla);

    Num0 = Baralla[0].numero;
    Pal0 = Baralla[0].pal;
    Num1 = Baralla[1].numero;
    Pal1 = Baralla[1].pal;

    Intercanviar(Baralla[0], Baralla[1]);

    if (Baralla[0].numero == Num1 && Baralla[0].pal == Pal1 && Baralla[1].numero == Num0 && Baralla[1].pal == Pal0) {
        testCorrecte = testCorrecte && true;
        std::cout << "Comment :=>> Test Intercanviar: CORRECTE!" << std::endl << std::endl;

    } else {
        std::cout << "Comment :=>> Test Intercanviar: ERROR - Revisa les funcions InicialitzarBaralla i Intercanviar." << std::endl << std::endl;
        testCorrecte = false;
    }

    return testCorrecte;
}

bool TestRemenar() {
    std::cout << "Comment :=>>----- TEST: Funcio Remenar -----" << std::endl;
    bool testCorrecte = true;
    int Canvis;

    int seed = 46;
    srand(seed);

    Carta Baralla1[NUM_CARTES_BARALLA];
    Carta Baralla2[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyolaT(Baralla1);
    InicialitzarBarallaEspanyolaT(Baralla2);

    Remenar(Baralla1, NUM_CARTES_BARALLA, 0);
    Canvis = 0;
    for (int i = 0; i < NUM_CARTES_BARALLA; i++) {
        if ((Baralla1[i].numero != Baralla2[i].numero) || (Baralla1[i].pal != Baralla2[i].pal)) {
            Canvis++;
        }
    }

    if (Canvis == 0) {
        testCorrecte = testCorrecte && true;
        std::cout << "Comment :=>> Test Remenar Sense Intercanvis: CORRECTE!" << std::endl;
    } else {
        testCorrecte = false;
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
        testCorrecte = testCorrecte && true;
        std::cout << "Comment :=>> Test Remenar: CORRECTE!" << std::endl << std::endl;

    } else {
        testCorrecte = false;
        std::cout << "Comment :=>> Test Remenar: ERROR - Revisa la funcio Remenar." << std::endl << std::endl;
    }

    return testCorrecte;
}

bool TestCompararCartes() {
    std::cout << "Comment :=>>----- TEST: Funcio CompararCartes -----" << std::endl;
    bool testCorrecte = true;
    Carta ComparacionsA[] = {{ORS, 1}, {ESPASES, 5}, {BASTONS, 3}, {COPES, 5}, {ESPASES, 5}};
    Carta ComparacionsB[] = {{ORS, 2}, {ESPASES, 4}, {ORS, 3}, {COPES, 5}, {COPES, 5}};
    bool resultat[] = {false, true, false, false, true};

    for(int index = 0; index < 5; index++) {
        bool resultat_comparacio = CompararCartes(ComparacionsA[index], ComparacionsB[index]);
        if(resultat_comparacio != resultat[index]) {
            testCorrecte = false;
        }
    }
    if(testCorrecte)
        std::cout << "Comment :=>> Test CompararCartes: CORRECTE!" << std::endl<<std::endl;
    else
        std::cout << "Comment :=>> Test CompararCartes: ERROR!" << std::endl<<std::endl;
    return testCorrecte;
}


bool TestAgafarCarta() {
    std::cout << "Comment :=>>----- TEST: Funcio AgafarCarta -----" << std::endl;
    bool testCorrecte = true;
    Carta baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyolaT(baralla);
    for (int index_pal = 0; index_pal < PALS_BARALLA; index_pal++)
        for (int index_num = 0; index_num < NUMEROS_BARALLA; index_num++) {
            Carta carta1 = AgafarCarta(baralla, NUM_CARTES_BARALLA);
            Carta carta2 = {index_pal + 1, index_num + 1};
            if(carta1.pal != carta2.pal || carta1.numero != carta2.numero)
                testCorrecte = false;
        }
    if(!testCorrecte) {
        std::cout << "Comment :=>> Test AgafarCarta: ERROR - Revisa la funcio AgafarCarta." << std::endl;
    }
    Carta carta = AgafarCarta(baralla, NUM_CARTES_BARALLA);
    if(!EsCartaBuidaT(carta)) {
        testCorrecte = false;
        std::cout << "Comment :=>> Test Remenar: ERROR - Revisa la funcio AgafarCarta. Que passa quan no hi han cartes?"
                  << std::endl;
    }
    if(testCorrecte)
        std::cout << "Comment :=>> Test AgafarCarta: CORRECTE!" << std::endl<<std::endl;
    else
        std::cout << "Comment :=>> Test AgafarCarta: ERROR!" << std::endl<<std::endl;
    return testCorrecte;
}

bool TestInicialitzar() {
    std::cout << "Comment :=>>----- TEST: Procediment Inicialitzar -----" << std::endl;
    bool testCorrecte = true;
    int num_cartes = 100;
    Carta baralla[num_cartes];
    Inicialitzar(baralla, num_cartes);
    for(int index = 0; index < num_cartes; index++) {
        if(!EsCartaBuidaT(baralla[index])) {
            testCorrecte = false;
            break;
        }
    }
    if(testCorrecte)
        std::cout << "Comment :=>> Test Inicialitzar: CORRECTE!" << std::endl<<std::endl;
    else
        std::cout << "Comment :=>> Test Inicialitzar: ERROR!" << std::endl<<std::endl;
    return testCorrecte;
}


bool TestAfegirCarta() {
    bool testCorrecte = true;
    std::cout << "Comment :=>>----- TEST: Procediment AfegirCarta -----" << std::endl;
    //std::vector<std::vector<Carta>> test_baralla= {{}};
    int num_cartes = NUM_CARTES_BARALLA;
    Carta baralla[num_cartes];
    InicialitzarT(baralla, num_cartes);
    for (int index_pal = 0; index_pal < PALS_BARALLA; index_pal++)
        for (int index_num = 0; index_num < NUMEROS_BARALLA; index_num++) {
            Carta carta = {index_pal + 1, index_num + 1};
            AfegirCarta(baralla, num_cartes, carta);
            int index = IndexCartaSenseValorT(baralla, num_cartes);
            int index_carta = index_pal * NUMEROS_BARALLA + index_num + 1;
            if(index_carta == NUM_CARTES_BARALLA) {
                if(index != INDEX_NO_TROBAT) {
                    testCorrecte = false;
                }
            }
            else {
                if(index != index_carta) {
                    testCorrecte = false;
                }
            }
        }
   for (int index_pal = 0; index_pal < PALS_BARALLA; index_pal++) {
        for (int index_num = 0; index_num < NUMEROS_BARALLA; index_num++) {
            Carta carta1 = baralla[index_pal * NUMEROS_BARALLA + index_num];
            Carta carta2 = {index_pal + 1, index_num + 1};
            if (carta1.pal != carta2.pal || carta1.numero != carta2.numero) {
                testCorrecte = false;
                break;
            }
        }
    }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test AfegirCarta: CORRECTE!" << std::endl<< std::endl;
    }
    else {
        std::cout << "Comment :=>> Test AfegirCarta: ERROR - Revisa si el procediment AfegirCarta es correcte"
                  << std::endl<< std::endl;
    }
    return testCorrecte;
}

bool TestSubstituirCarta() {
    std::cout << "Comment :=>>----- TEST: Procediment SubstituirCarta -----" << std::endl;
    bool testCorrecte = true;

    std::vector<std::vector<Carta>> font = {{{ORS, 12}},
                                            {{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}}};
    std::vector<std::vector<Carta>> receptor = {{{ORS, 10}, {BASTONS, 4},{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}},
                                                {{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}}};
    std::vector<std::pair<int, Carta>> results = {{2, {ORS, 12}},
                                                  {0, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}}};
    for(int index = 0; index < font.size(); index++) {
        std::vector<Carta> font_vector = font[index];
        std::vector<Carta> receptor_vector = receptor[index];
        Carta *font_cartes = &(font_vector[0]);
        Carta *receptor_cartes = &(receptor_vector[0]);
        Carta carta1 = font_cartes[0];
        SubstituirCartaBuida(font_cartes, font_vector.size(), receptor_cartes, receptor_vector.size());
        auto result = results[index];
        Carta carta2 = receptor_cartes[result.first];

        if (carta1.pal != carta2.pal || carta1.numero != carta2.numero) {
            testCorrecte = false;
            break;
        }
        if(!EsCartaBuidaT(font_cartes[0])) {
            testCorrecte = false;
            break;
        }
    }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test SubstituirCarta: CORRECTE!" << std::endl<< std::endl;
    }
    else {
        std::cout << "Comment :=>> Test SubstituirCarta: ERROR - Revisa si el procediment SubstituirCarta es correcte"
                  << std::endl<< std::endl;
    }
    return testCorrecte;
}

bool TestSeleccioHuma() {
    std::cout << "Comment :=>>----- TEST: Procediment SeleccioHuma -----" << std::endl;
    bool testCorrecte = true;
    Jugador huma;

    std::vector<std::vector<Carta>> mans = {{{ORS, 12}, {BASTONS, 8}, {COPES, 3}},
                                            {{ESPASES, 9}, {ORS, 9}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}},
                                            {{COPES, 7}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT},{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}}};
    std::vector<std::string> user_in = {{"5\n3\n"}, {"3\n1\n"}, {"3\n2\n1\n"}};
    std::vector<int> result = {2, 0, 0, 0};

    for(int index = 0; index < mans.size(); index++) {
        std::istringstream stream(user_in[index]);
        std::streambuf* cin_backup = std::cin.rdbuf(stream.rdbuf());
        memcpy(&huma.ma, &(mans[index][0]), 3*sizeof(Carta));
        Carta carta1 = huma.ma[result[index]];
        Carta carta2 = ObtindreSeleccioHuma(huma, mans[index].size());
        if (carta1.pal != carta2.pal || carta1.numero != carta2.numero) {
            testCorrecte = false;
            break;
        }
        if(!EsCartaBuidaT(huma.ma[2])) {
            testCorrecte = false;
            break;
        }
        std::cin.rdbuf(cin_backup);
    }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test SeleccioHuma: CORRECTE!" << std::endl<< std::endl;
    }
    else {
        std::cout << "Comment :=>> Test SeleccioHuma: ERROR - Revisa si la funcio SeleccioHuma es correcte"
                  << std::endl<< std::endl;
    }
    return testCorrecte;
}

bool TestSeleccioOrdinador() {
    std::cout << "Comment :=>>----- TEST: Procediment SeleccioOrdinador -----" << std::endl;
    bool testCorrecte = true;
    Jugador ordinador;

    std::vector<std::vector<Carta>> mans = {{{ORS, 3}, {ORS, 2}, {ORS, 1}},
                                                    {{ESPASES, 9}, {ESPASES, 7}, {ORS, 1}},
                                                    {{ORS, 7}, {COPES, 3}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}},
                                                    {{ORS, 3}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}},
                                                    {{ESPASES, 10}, {ORS, 5}, {BASTONS, 1}}};
    std::vector<Carta> cartes_jugador = {{ORS, 12},
                                        {BASTONS, 8},
                                        {COPES, 9},
                                        {ESPASES, 9},
                                        {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}};
    std::vector<int> resultat = {2, 0, 1, 0, 0};

    for(int index = 0; index < mans.size(); index++) {
        memcpy(&ordinador.ma, &(mans[index][0]), 3*sizeof(Carta));
        Carta carta_jugador = cartes_jugador[index];
        Carta carta1 = ordinador.ma[resultat[index]];
        Carta carta2 = SeleccioOrdinador(ordinador,3, carta_jugador);
        if (carta1.pal != carta2.pal || carta1.numero != carta2.numero) {
            std::cout << "Comment :=>> Test SeleccioOrdinador: ERROR - Revisa si la funcio SeleccioOrdinador es correcte"<<std::endl;
            testCorrecte = false;
            break;
        }

    }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test SeleccioOrdinador: CORRECTE!" << std::endl;
    }
    std::cout<<std::endl;
    return testCorrecte;
}

bool TestPuntsCartes() {
    std::cout << "Comment :=>>----- TEST: Funcio PuntsCartes -----" << std::endl;
    bool testCorrecte = true;
    std::vector<std::vector<Carta>> cartes = {{{ORS, 3}, {ORS, 2}, {ORS, 1}},
                                            {{ESPASES, 9}, {ESPASES, 7}, {ORS, 1}},
                                            {{ORS, 7}, {COPES, 3}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}},
                                            {{ORS, 3}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}},
                                            {{PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}, {PAL_CARTA_BUIT, NUMERO_CARTA_BUIT}}};

    std::vector<int> result = {6, 17, 10, 3, 0};

    for(int index = 0; index < cartes.size(); index++) {
        int value = PuntsCartes(&(cartes[index][0]), cartes[index].size());
        if(value != result[index]) {
            std::cout
                    << "Comment :=>> Test Funcio: ERROR - Revisa si la funcio PuntsCartes es correcte"
                    << std::endl;
            testCorrecte = false;
            break;
        }
    }

    Carta baralla[NUM_CARTES_BARALLA];
    InicialitzarBarallaEspanyolaT(baralla);
    int value = PuntsCartes(baralla, NUM_CARTES_BARALLA);
    if(value != 312) {
        std::cout << "Comment :=>> Test Funcio: ERROR - Revisa si la funcio PuntsCartes es correcte"
        << std::endl;
        testCorrecte = false;
    }

    if(testCorrecte) {
        std::cout << "Comment :=>> Test SeleccioOrdinador: CORRECTE!" << std::endl;
    }
    std::cout<<std::endl;
    return testCorrecte;
}

bool TestRondaLaMajor() {
    bool testCorrecte = true;
    std::cout << "Comment :=>>----- TEST: Funcio JugarRonda -----" << std::endl;
    int num_rondes = 1000;
    srand(time(NULL));
    std::vector<int> seq_aleatoria;
    for(int index = 1; index <= num_rondes; index++) {
        seq_aleatoria.push_back(AleatoriT(0, INT16_MAX));
    }
    int ronda = 0;
    for(auto valor_aleatori: seq_aleatoria) {
        ronda++;
        std::cout << "Comment :=>>----- TEST: RONDA " <<ronda <<" -----" << std::endl;
        srand(valor_aleatori);
        RandomNumberStreambuf customBuffer(1, 3);
        std::cin.clear();
        std::cin.sync();
        std::streambuf* cin_backup = std::cin.rdbuf(&customBuffer);
        std::cout << "Comment :=>>----- RONDA PROVA " <<ronda <<" -----" << std::endl;
        Jugador huma1;
        Jugador ordinador1;
        Carta baralla1[NUM_CARTES_BARALLA];
        InicialitzarT(huma1.ma, CARTES_PER_JUGADOR);
        InicialitzarT(ordinador1.ma, CARTES_PER_JUGADOR);
        InicialitzarT(huma1.pila, NUM_CARTES_BARALLA);
        InicialitzarT(ordinador1.pila, NUM_CARTES_BARALLA);
        InicialitzarBarallaEspanyolaT(baralla1);
        RemenarT(baralla1, NUM_CARTES_BARALLA, 1000);
        RepartirCartesT(baralla1, NUM_CARTES_BARALLA, huma1, ordinador1, CARTES_PER_JUGADOR);
        bool ordinador_juga_primer1 = AleatoriT(0, 1);
        int result_1 = JugarRonda(baralla1, huma1, ordinador1, ordinador_juga_primer1);

        std::cout << "Comment :=>>----- RONDA BONA " <<ronda <<" -----" << std::endl;
        srand(valor_aleatori);
        //RandomNumberStream randomGen2(1, 3);
        //std::cin.rdbuf(randomGen2.rdbuf());
        Jugador huma2;
        Jugador ordinador2;
        Carta baralla2[NUM_CARTES_BARALLA];
        InicialitzarT(huma2.ma, CARTES_PER_JUGADOR);
        InicialitzarT(ordinador2.ma, CARTES_PER_JUGADOR);
        InicialitzarT(huma2.pila, NUM_CARTES_BARALLA);
        InicialitzarT(ordinador2.pila, NUM_CARTES_BARALLA);
        InicialitzarBarallaEspanyolaT(baralla2);
        RemenarT(baralla2, NUM_CARTES_BARALLA, 1000);
        RepartirCartesT(baralla2, NUM_CARTES_BARALLA, huma2, ordinador2, CARTES_PER_JUGADOR);
        bool ordinador_juga_primer2 = AleatoriT(0, 1);
        int result_2 = JugarRondaT(baralla2, huma2, ordinador2, ordinador_juga_primer2);
        if(!CompararArrayCartes(huma1.pila, huma2.pila, NUM_CARTES_BARALLA)) {
            testCorrecte = false;
            std::cout << "Comment :=>> Test JugarRonda: ERROR: Comprova la pila de l'humà" << std::endl;
            break;
        }
        if(!CompararArrayCartes(ordinador1.pila, ordinador2.pila, NUM_CARTES_BARALLA)) {
            testCorrecte = false;
            std::cout << "Comment :=>> Test JugarRonda: ERROR: Comprova la pila de l'ordinador" << std::endl;
            break;
        }
        if(!CompararArrayCartes(huma1.ma, huma2.ma, CARTES_PER_JUGADOR)) {
            testCorrecte = false;
            std::cout << "Comment :=>> Test JugarRonda: ERROR: Comprova la ma de l'humà" << std::endl;
            break;
        }
        if(!CompararArrayCartes(ordinador1.ma, ordinador2.ma, CARTES_PER_JUGADOR)) {
            testCorrecte = false;
            std::cout << "Comment :=>> Test JugarRonda: ERROR: Comprova la ma de l'ordinador" << std::endl;
            break;
        }
        if(result_1 != result_2) {
            testCorrecte = false;
            std::cout << "Comment :=>> Test JugarRonda: ERROR: Comprova el resultat" << std::endl;
            break;
        }
       std::cin.rdbuf(cin_backup);
    }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test JugarRonda: CORRECTE!" << std::endl;
    }
    std::cout<<std::endl;
    return testCorrecte;
}

bool TestJocLaMajor() {
    bool testCorrecte = true;
    int num_rondes = 10;
    srand(time(NULL));
    std::vector<int> seq_aleatoria;
    for(int index = 0; index < num_rondes; index++) {
        seq_aleatoria.push_back(AleatoriT(0, INT16_MAX));
    }
    int joc = 0;
    for(auto valor_aleatori: seq_aleatoria) {
        joc++;
        std::cout << "Comment :=>>----- TEST: JOC " <<joc <<" -----" << std::endl;
        std::cout << "Comment :=>>----- JOC PROVA " <<joc <<" -----" << std::endl;
        srand(valor_aleatori);
        RandomNumberStreambuf customBuffer(1, 3);
        std::cin.clear();
        std::cin.sync();
        std::streambuf* cin_backup = std::cin.rdbuf(&customBuffer);
        Jugador huma1;
        Jugador ordinador1;
        Carta baralla1[NUM_CARTES_BARALLA];
        InicialitzarBarallaEspanyolaT(baralla1);
        RemenarT(baralla1, NUM_CARTES_BARALLA, 1000);
        JugarLaMajor(baralla1, huma1, ordinador1);

        std::cout << "Comment :=>>----- JOC BO " <<joc <<" -----" << std::endl;
        srand(valor_aleatori);

        Jugador huma2;
        Jugador ordinador2;
        Carta baralla2[NUM_CARTES_BARALLA];
        InicialitzarBarallaEspanyolaT(baralla2);
        RemenarT(baralla2, NUM_CARTES_BARALLA, 1000);
        JugarLaMajorT(baralla2, huma2, ordinador2);
        if(!CompararArrayCartes(huma1.pila, huma2.pila, NUM_CARTES_BARALLA)) {
            testCorrecte = false;
            std::cout << "Comment :=>> Test JugarRonda: ERROR: Comprova la pila de l'humà" << std::endl;
            break;
        }
        if(!CompararArrayCartes(ordinador1.pila, ordinador2.pila, NUM_CARTES_BARALLA)) {
            testCorrecte = false;
            std::cout << "Comment :=>> Test JugarRonda: ERROR: Comprova la pila de l'ordinador" << std::endl;
            break;
        }
    }
    if(testCorrecte) {
        std::cout << "Comment :=>> Test JugarRonda: CORRECTE!" << std::endl;
    }
    return testCorrecte;
}



int main() {

    int grade = 0;
    bool testCorrecte;
    testCorrecte = TestInicalitzarBaralla();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }

    testCorrecte = TestCartaBuida();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }

    testCorrecte = TestIndexCarta();
    if(testCorrecte)
        grade += 10;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }

    testCorrecte = TestIntercanviar();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestRemenar();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestAgafarCarta();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestCompararCartes();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestInicialitzar();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestAfegirCarta();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestSubstituirCarta();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestSeleccioHuma();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestSeleccioOrdinador();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestPuntsCartes();
    if(testCorrecte)
        grade += 5;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestRondaLaMajor();
    if(testCorrecte)
        grade += 10;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    testCorrecte = TestJocLaMajor();
    if(testCorrecte)
        grade += 20;
    else {
        std::cout << "Comment :=>> Arregla els errors abans de continuar"<<std::endl;
        goto END;
    }
    END:
    std::cout << "Grade :=>> " << grade << std::endl;
}
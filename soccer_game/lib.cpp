#include "lib.h"
#include <iostream>
#include <string>

using namespace std;

void imprimirResultados(Partido partidos[], int cantidadPartidos) {
    int totales[cantidadPartidos];

    for (int i = 0; i < cantidadPartidos; i++) {
        totales[i] = partidos[i].getGolesEquipo1() + partidos[i].getGolesEquipo2();
    }

    for (int i = 0; i < cantidadPartidos - 1; i++) {
        for (int j = 0; j < cantidadPartidos - i - 1; j++) {
            if (totales[j] < totales[j + 1]) {
                int temp = totales[j];
                totales[j] = totales[j + 1];
                totales[j + 1] = temp;
                Partido tempPartido = partidos[j];
                partidos[j] = partidos[j + 1];
                partidos[j + 1] = tempPartido;
            }
        }
    }

    cout << "--- Resultados de Partidos Ordenados por Goles (Mayor a Menor) ---" << endl;
    for (int i = 0; i < cantidadPartidos; i++) {
        cout << partidos[i].getEquipo1().getNombre() << " " << partidos[i].getGolesEquipo1() << " - "
             << partidos[i].getEquipo2().getNombre() << " " << partidos[i].getGolesEquipo2() << " | Total: "
             << totales[i] << endl;
    }
    cout << "------------------------------------------------------------------" << endl;
}

void determinarGanadores(Partido partidos[], int cantidadPartidos, Equipo ganadores[], int puntos_ganadores[]) {
    string equipos[6] = {"UCC", "UNC", "UNRC", "UTN", "UBP", "UES21"};
    int puntos[6] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < cantidadPartidos; i++) {
        string equipo1 = partidos[i].getEquipo1().getNombre();
        string equipo2 = partidos[i].getEquipo2().getNombre();
        int goles1 = partidos[i].getGolesEquipo1();
        int goles2 = partidos[i].getGolesEquipo2();

        int index1 = -1, index2 = -1;
        
        for (int j = 0; j < 6; j++) {
            if (equipos[j] == equipo1) {
                index1 = j;
            }
            if (equipos[j] == equipo2) {
                index2 = j;
            }
        }

        if (goles1 > goles2) {
            puntos[index1] += 3; 
        } else if (goles1 < goles2) {
            puntos[index2] += 3;
        } else {
            puntos[index1] += 1;
            puntos[index2] += 1;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            if (puntos[j] < puntos[j + 1]) {
                int tempPuntos = puntos[j];
                puntos[j] = puntos[j + 1];
                puntos[j + 1] = tempPuntos;
                string tempEquipo = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = tempEquipo;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        puntos_ganadores[i] = puntos[i];
        ganadores[i] = Equipo(equipos[i]); 
    }
}

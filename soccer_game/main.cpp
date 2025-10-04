#include "lib.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    // Arreglo predefinido de partidos
    const int CANTIDAD_PARTIDOS = 15;
    Partido partidos[CANTIDAD_PARTIDOS] = {
        Partido(Equipo("UNRC"), Equipo("UBP"), 0, 0),
        Partido(Equipo("UCC"), Equipo("UNRC"), 3, 0),
        Partido(Equipo("UTN"), Equipo("UBP"), 2, 2),
        Partido(Equipo("UNC"), Equipo("UES21"), 3, 1),
        Partido(Equipo("UBP"), Equipo("UES21"), 2, 1),
        Partido(Equipo("UCC"), Equipo("UTN"), 4, 1),
        Partido(Equipo("UNC"), Equipo("UNRC"), 2, 2),
        Partido(Equipo("UCC"), Equipo("UBP"), 0, 2),
        Partido(Equipo("UNC"), Equipo("UTN"), 0, 1),
        Partido(Equipo("UTN"), Equipo("UNRC"), 0, 1),
        Partido(Equipo("UCC"), Equipo("UNC"), 2, 1),
        Partido(Equipo("UCC"), Equipo("UES21"), 2, 2),
        Partido(Equipo("UNC"), Equipo("UBP"), 1, 3),
        Partido(Equipo("UTN"), Equipo("UES21"), 1, 0),
        Partido(Equipo("UNRC"), Equipo("UES21"), 2, 3)
    };

    Equipo ganadores[3] = { Equipo(""), Equipo(""), Equipo("") };
    int puntos_ganadores[3] = {0, 0, 0};

    imprimirResultados(partidos, CANTIDAD_PARTIDOS);

    determinarGanadores(partidos, CANTIDAD_PARTIDOS, ganadores, puntos_ganadores);

    cout << "\n--- Ganadores del Torneo ---" << endl;
    cout << "1° Lugar: " << ganadores[0].getNombre() << " (Puntos: " << puntos_ganadores[0] << ")" << endl;
    cout << "2° Lugar: " << ganadores[1].getNombre() << " (Puntos: " << puntos_ganadores[1] << ")" << endl;
    cout << "3° Lugar: " << ganadores[2].getNombre() << " (Puntos: " << puntos_ganadores[2] << ")" << endl;
    cout << "----------------------------" << endl;

    return 0;
}
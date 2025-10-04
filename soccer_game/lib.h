#ifndef LIB_H
#define LIB_H

#include <string>

using namespace std;

class Equipo {
    private:
        string nombre;
    public:
        Equipo(string n) : nombre(n) {}
        string getNombre() const { return nombre; }
};

class Partido {
    private:
        Equipo equipo1;
        Equipo equipo2;
        int golesEquipo1;
        int golesEquipo2;
    public:
        Partido(Equipo e1, Equipo e2, int g1, int g2) 
            : equipo1(e1), equipo2(e2), golesEquipo1(g1), golesEquipo2(g2) {}
        Equipo getEquipo1() const { return equipo1; }
        Equipo getEquipo2() const { return equipo2; }
        int getGolesEquipo1() const { return golesEquipo1; }
        int getGolesEquipo2() const { return golesEquipo2; }
};

void imprimirResultados(Partido partidos[], int cantidadPartidos);

void determinarGanadores(Partido partidos[], int cantidadPartidos, Equipo ganadores[], int puntos_ganadores[]);

#endif
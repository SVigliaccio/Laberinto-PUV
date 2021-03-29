#ifndef RANKING_H
#define RANKING_H

#include "Registro.h"
#include "GUI.h"
#include "Archivo.h"
#include "Jugador.h"


class Ranking : public Registro, public Archivo
{
    private:
        Jugador _jugador;

    public:
        Jugador VecArchivo[5];
        Ranking(const char name[10] = {"Username"}, float puntos = 0);
        void Cargar();
        void Cargar(const char name[10] = {"Username"}, float puntos = 0);
        virtual ~Ranking();
        void Mostrar();
        int getSize(){return sizeof *this;}
        float getPuntos(){return _jugador.ptsTOTAL;}
        const char* getNombre(){return _jugador.nombre;}
        Jugador &getJugador(){return _jugador;}
        Jugador *getJugadores(){return VecArchivo;}
        /// ARCHIVOS
        int extraerReg();
        ///VALIDAR
        void compararPuntos();

};


#endif // RANKING_H

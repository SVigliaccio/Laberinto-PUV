#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

class Jugador : public Registro
{
    public:
    char nombre[10] = {}; ///Nombre del jugador
    float ptsTOTAL=0;

    int getSize(){return sizeof *this;}
};


#endif // JUGADOR_H_INCLUDED

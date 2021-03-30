#include <string.h>
#include<iostream>
#include <cstdlib> /// new y delete

#include "Ranking.h"
#include "Registro.h"
#include "GUI.h"
#include "Archivo.h"
#include "Jugador.h"
#define MOSTRAR(x) std::cout << x << std::endl

Ranking::Ranking(const char name[10], float puntos)
:Archivo( "Ranking.dat", _jugador.getSize() )
{
    Cargar(name, puntos);
}

Ranking::~Ranking()
{
    if(p) fclose(p);
    //dtor
}
void Ranking::Cargar(){}
void Ranking::Cargar(const char name[10], float puntos){ /// al finalizar el game en gameplay debe cargarse el registro.
    strcpy(_jugador.nombre, name);
    _jugador.ptsTOTAL = puntos;
}

void Ranking::Mostrar(){
    if(!abrirArchivo(SoloLectura))
    {
        defaultArchivo(5, &_jugador);
    }

    abrirArchivo(SoloLectura);
    fseek(p, 0, 0);

    for(int j=0 ; j<5; j++){
        fread( &VecArchivo[j], tamanioRegistro, 1, p);
         //std::cout<<j+1<<") "<<VecArchivo[j].nombre<<std::endl;
         //std::cout<<j+1<<") "<<VecArchivo[j].ptsTOTAL<<std::endl;
    }
    cerrarArchivo();

}

///ARCHIVOS
int Ranking::extraerReg() ///luego eliminar los cout.
{

    Mostrar();
    compararPuntos();
    Mostrar();


    return 1;
}

void Ranking::compararPuntos(){ ///compara y graba en el archivo
    if(!abrirArchivo(Escritura))
    {
        MOSTRAR("no pudo abrir");
        return;
    }
    Jugador aux;
    for(int i = 0; i<5; i++)
        {

            if( _jugador.ptsTOTAL >= VecArchivo[i].ptsTOTAL )
                {
                   aux.ptsTOTAL = VecArchivo[i].ptsTOTAL;
                   strcpy(aux.nombre, VecArchivo[i].nombre);

                   strcpy( VecArchivo[i].nombre, _jugador.nombre );
                   VecArchivo[i].ptsTOTAL = _jugador.ptsTOTAL;


                    MOSTRAR("nombre a grabar");
                    MOSTRAR( VecArchivo[i].nombre );
                    MOSTRAR("Puntos a grabar");
                    MOSTRAR( VecArchivo[i].ptsTOTAL );



                   strcpy(_jugador.nombre, aux.nombre );
                   _jugador.ptsTOTAL = aux.ptsTOTAL;

                }
                //this->CargarpRegistro(VecObj[i]);
                //this->GrabarRegistro();
                if(!fwrite(&VecArchivo[i], tamanioRegistro, 1, p)) MOSTRAR("NOOOO GRAAABAAA");
        }
    cerrarArchivo();

}

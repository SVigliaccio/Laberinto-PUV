#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <cstdlib> /// new y delete
#include<stdio.h> /// FILE ARCHIVOS
#include "Registro.h"

///////////////////////////
//TIPOS ENUMERADOS PARA USAR CON LA CLASE ARCHIVO
enum Estado{//DEFINE LOS ESTADOS EN LOS QUE PUEDE ESTAR EL ARCHIVO
  NoExiste,
  Cerrado,
  AbiertoRB,
  AbiertoWB,
  AbiertoAB,
  AbiertoRBmas
  };

 enum Modo{//DEFINE LOS MODOS DE APERTURA DE UN ARCHIVO
   SoloLectura,
   Escritura,
   Agregar,
   LecturaEscritura
   };

class Archivo
{
    protected:
    FILE *p;
    int tamanioRegistro;
    Registro *pRegistro;

    char *nombreArchivo;
    int cantRegistros;
    int estado;

    bool abrirArchivo(Modo modo);

    void cerrarArchivo(){
      fclose(p);
      estado=Cerrado;
      }

    public:
        Archivo(const char *nombre, int tam );
        virtual ~Archivo();
        void CargarpRegistro(Registro *padre);

        //virtual int extraerReg();

        bool defaultArchivo(int cantidad, Registro *padre); /// setear cierta cant de registros a lo que contenga *padre.
        //bool GrabarRegistro();
};

#endif // ARCHIVO_H

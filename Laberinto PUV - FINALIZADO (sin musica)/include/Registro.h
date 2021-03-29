#ifndef REGISTRO_H
#define REGISTRO_H


class Registro{
  public:
      virtual void Cargar(){};
      //virtual void Mostrar(){};
      virtual int getSize(){};//DEVUELVE EL SIZEOF DEL OBJETO
      virtual float getPuntos(){};
      ///virtual Registro& operator=(Registro*) =0;//SOBRECARGA PARA ASIGNAR UN PUNTERO REGISTRO A UNA REFERENCIA A UN OBJETO DE UNA CLASE DERIVADA DE REGISTRO
      ///virtual bool comparaID(Registro*)=0;// SE SUPONE QUE CADA CLASE TIENE UNA PROPIEDAD QUE
  };                                      // IDENTIFICA A CADA OBJETO (UN PROPIEDAD CLAVE)
     //COMO ESA IDENTIFICACION UNICA (ID) PUEDE SER DE DISTINTO TIPO SE DEBE HACER UN METODO
      //PARA COMPARAR EL VALOR DE LA PROPIEDAD CLAVE ENTRE DISTINTOS OBJETOS

#endif // REGISTRO_H

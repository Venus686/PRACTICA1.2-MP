#ifndef CONTRATO_H
#define CONTRATO_H

#include <iostream> //cin, cout
#include "Fecha.h"

using namespace std;

class Contrato {
  static int contador; //variable compartida por los objetos, estatica
  const int idContrato;
  long int dniContrato;
  Fecha fechaContrato;
public:
  Contrato(long int dni, Fecha f);
  virtual ~Contrato();
  Contrato(const Contrato& c); //CONSTRUCTOR DE COPIA

//Contrato& operator=(const Contrato& c); //no es necesario y ademas no puede ser usado porque Contrato tiene un
                                          //atributo constante idContrato que no puede modificarse
                                          //no se puede usar el = en el main con objetos Contrato

  int getIdContrato() const { return this->idContrato; }
  long int getDniContrato() const { return this->dniContrato; }
  Fecha getFechaContrato() const { return this->fechaContrato; }

  void setFechaContrato(Fecha f) { this->fechaContrato=f; }
  void setDniContrato(long int dni) { this->dniContrato=dni; }

  virtual float factura () const=0;
  virtual void ver() const; // se va a sobreescribir en las clases hijas
  friend ostream& operator<<(ostream &s, const Contrato &c);
};

ostream& operator<<(ostream &s, const Contrato &c);

#endif // CONTRATO_H

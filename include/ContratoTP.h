#ifndef CONTRATOTP_H
#define CONTRATOTP_H

#include <iostream> //cin, cout
#include "Fecha.h"
#include "Contrato.h"

using namespace std;

class ContratoTP: public Contrato {
  static int minutosTP;
  static float precioTP;
  int minutosHablados;
  static const float precioExcesoMinutos;

public:
  ContratoTP(long int dni, Fecha f, int m);
  //virtual ~ContratoTP(); //No es necesario porque no hay puntero a implementar
  //ContratoTP(const ContratoTP& c);  //No hace falta porque no hay puntero
  //ContratoTP& operator=(const ContratoTP& c); //¿es necesario? pensar y reflexionad

  static int getLimiteMinutos() { return ContratoTP::minutosTP; }
  static float getPrecio() { return ContratoTP::precioTP; }
  static void setTarifaPlana(int m, float p); //el el .cpp se pone la cabecera sin la palabra
  void setMinutosHablados(int m) { this->minutosHablados=m; }

  void ver()const;
  virtual float factura() const;
  int getMinutosHablados() const { return this->minutosHablados; }
  friend ostream& operator<<(ostream &s, const ContratoTP &c);

};

ostream& operator<<(ostream &s, const ContratoTP &c);

#endif // CONTRATOTP_H

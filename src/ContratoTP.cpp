#include "ContratoTP.h"

using namespace std;
int ContratoTP::minutosTP=300;
float ContratoTP::precioTP=10;
const float ContratoTP::precioExcesoMinutos=0.15;



ContratoTP::ContratoTP(long int dni, Fecha f,int m ): Contrato(dni, f) {
  this->minutosHablados=m;
}

//static se pone en el .h (no se pone en el .cpp)
void ContratoTP::setTarifaPlana(int m, float p) {
  ContratoTP::minutosTP=m; //puedo poner minutosTP=m ...pongo ContratoTP::minutosTP para recordar que es estatico
  ContratoTP::precioTP=p;  //puedo poner precioTP=p  ...pongo ContratoTP::precioTP para recordar que es estatico
}


float ContratoTP::factura() const {
	if(this->minutosHablados<= this->minutosTP){
        return this->precioTP; //se paga la tarifa plana
	}else{
        int exc_lim =this->minutosHablados- this->minutosTP;
        return this->precioTP+(exc_lim * this->precioExcesoMinutos);
	}
}

void ContratoTP::ver() const {
  Contrato::ver(); //IMPORTANTE: llamamos al ver que heredo de mi padre PARA QUE MUESTRE LO DEL PADRE

  cout << " " << this->minutosHablados << "m, "  << this->minutosTP << " (" << this->precioTP<<")";
}


ostream& operator<<(ostream &s, const ContratoTP &c) {
  s << (Contrato &)c;

  s << " " << c.getMinutosHablados() << "m, " << c.getLimiteMinutos() << "(" << c.getPrecio() << ") - " << c.factura() << "$";
  return s;
}

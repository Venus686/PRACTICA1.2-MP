#include "Cliente.h"
#include <cstdlib>
#include <cstring> //strlen, strcpy
#include <iomanip> //std::setprecision
#include <sstream> //stringstream
#include "Cliente.h"
using namespace std;

//Cliente::Cliente(long int d, char *nom, Fecha f):fechaAlta(f.getDia(), f.getMes(), f.getAnio()) {


Cliente::Cliente(long int d, char *nom, Fecha f):fechaAlta(f) { //esta cabecera es mas corta (invoco
  this->dni=d;                                                  //constructor copia de fecha
                                                                //en vez de constructor de 3 parametros)
  this->nombre=new char[strlen(nom)+1];
  strcpy(this->nombre, nom);

  //this->fechaAlta=f;//MAL!!!! los tipos no primitivos debe ir en zona inicializadores
}

Cliente:: Cliente (const Cliente &copia) : dni(copia.dni), fechaAlta(copia.fechaAlta){
    nombre= new char[strlen(copia.nombre)+1];
    strcpy(this->nombre, copia.nombre);
}

Cliente::~Cliente() {
    delete [] this->nombre; //si en el constructor uso new [] en el destructor uso delete []
}

void Cliente:: setNombre(const char* nombre){
    delete[]this -> nombre; //liberar la memoria
    this->nombre=new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}

void Cliente::setFecha(Fecha F){
    this->fechaAlta=F;
}

///OPERADODR DE ASIGNACIÓN
Cliente& Cliente::operator=(const Cliente& c) {
  if (this != &c) { //si no es el mismo objeto
    this->dni=c.dni;

    delete [] this->nombre;
    this->nombre=new char[strlen(c.nombre)+1];
    strcpy(this->nombre, c.nombre);

    this->fechaAlta=c.fechaAlta;
  }
  return *this;
}

///OPERADOR DE COMPARACIÓN
bool Cliente::operator==(Cliente c) const {
  if (this->dni!=c.dni) return false;
  if (strcmp(this->nombre, c.nombre)!=0) return false;
  if (this->fechaAlta.getDia()!=c.fechaAlta.getDia() ||
      this->fechaAlta.getMes()!=c.fechaAlta.getMes() ||
      this->fechaAlta.getAnio()!=c.fechaAlta.getAnio()) return false;
  return true;
}

ostream& operator<<(ostream& os, const Cliente& c) {
    const char* meses[] = { "ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic" };

    os << c.getNombre() << " (" << c.getDni() << " - ";
    int dia = c.fechaAlta.getDia();
    if (dia < 10) {
            os << "0"; // si el dia es menor que 10 se pone un 0
        }
        os << dia << " ";

        // Muestra mes y año
        os << meses[c.fechaAlta.getMes() - 1] << " " << c.fechaAlta.getAnio() << ")";

    return os;
}


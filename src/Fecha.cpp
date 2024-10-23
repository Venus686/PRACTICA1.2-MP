#include <iostream>
#include "Fecha.h"
using namespace std;

Fecha::Fecha(const int &dia, const int &m, const int &anio) {
    this->setFecha(dia, m, anio); //el cogido es el mismo que el del metodo setFecha
}


//asignamos la fecha que mas se ajuste
void Fecha::setFecha(const int &dia, const int &mes, const int &a) {
    //dmax-> almacena el numero maximo de dias del mes actual
    int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};// array del numero de dias de cada mes

    this->anio=a; //VIP debo asignar año para que al llamar a bisiesto() tenga el año bien

    if (this->bisiesto()){
        diaMes[2]=29; //febrero tiene 29 dias si es bisiesto
    }

    /// MES
    if (mes < 1) {
        this->mes = 1; // Si el mes es menor que 1, ponemos enero
    }
    else if (mes > 12) {
        this->mes = 12; // Si el mes es mayor que 12, será diciembre
    }
    else {
        this->mes = mes;
    }

    dmax = diaMes[this->mes]; //miramos el dia maximo que tiene ese mes

    /// DIA
    if (dia > dmax) {
        this->dia = dmax;// Si el dia es mayor que el que se el máximo, se le asigna el máximo
    }
    else if (dia < 1) {
        this->dia = 1; //si es menor que 1, se pone a 1
    }
    else {
        this->dia = dia;
    }
}

bool Fecha::bisiesto() const {
    if (this->anio%4==0) { //si es divisible entre 4, podría ser bisiesto
        if(this->anio % 100 == 0){
            if(this->anio % 400 == 0){
                return true; //si es divisible por 4 por 100 y por 400 es bisiesto
            }
        }else{
            return true;// si se divide por 4 y no por 100 es bisiesto, como 2024
        }
    }else{
        return false;//no es divisible por 4
    }
}

void Fecha::ver() const {
  if (this->dia < 10)
    cout << "0";
  cout << this->dia << "/";
  if (this->mes < 10)
    cout << "0";
  cout << this->mes << "/" << this->anio;
}

Fecha& Fecha::operator++() {   //++f (Primero se incrementa, y se devuelve incrementado)
    int dmax; //numero maximo de dias del mes actual
    int diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if (this->bisiesto()){
        diaMes[2]=29;
    }//si el año es bisiesto febrero tiene 29 dias

    dmax=diaMes[this->mes];

    this->dia++;
    if (this->dia>dmax) { //si al incrementar dia superamos el numero de dias de dicho mes
        this->dia=1;      //pasamos a 1
        this->mes++;      //del mes siguiente
        if (this->mes>12) { //si al incrementar mes pasamos de 12 meses
            this->mes=1;    //pasamos al mes 1
            this->anio++;   //del año siguiente
        }
    }
    return *this; //devolvemos el objeto fecha ya incrementado
}

Fecha Fecha::operator++(int i){
    Fecha aux= *this; //guardamos la fecha original

    int dmax; //numero maximo de dias del mes actual
    int diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
     if (this->bisiesto()){
        diaMes[2]=29;
    }//si el año es bisiesto febrero tiene 29 dias

    dmax=diaMes[this->mes];
    this->dia++;
    if (this->dia>dmax) { //si al incrementar dia superamos el numero de dias de dicho mes
        this->dia=1;      //pasamos a 1
        this->mes++;      //del mes siguiente
        if (this->mes>12) { //si al incrementar mes pasamos de 12 meses
            this->mes=1;    //pasamos al mes 1
            this->anio++;   //del año siguiente
        }
    }
    return aux; //devolvemos el objeto fecha original
}


Fecha Fecha::operator+(const int &i) const{
    Fecha aux= *this;
    for (int j=0; j<i; ++j){
        ++aux; // usamos ++f ya implementado
    }
    return aux;
}
/*se usa ++f y no f++ para evitar la sobrecarga
de crear copias del objeto en cada interación y más si
la i es muy grande*/


Fecha operator+(const int &i, const Fecha &f) {
    Fecha aux= f; //creo la copia
    aux =aux+i; //uso el op. f+i
    return aux;
}

ostream& operator<< (ostream& s, const Fecha& f){
    s << f.dia << "/" << f.mes << "/" << f.anio; // Formato DD/MM/AAAA
    return s;
}


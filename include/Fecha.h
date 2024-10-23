#ifndef FECHA_H
#define FECHA_H
#include <iostream>
using namespace std;

class Fecha{
    int dia;
    int mes, anio;
public:

    Fecha(const int &d,const int &m,const int &a); ///CONSTRUCTOR

    void setFecha(const int &d,const int &m,const int &a);
    int getAnio() const{return  this-> anio;};
    int getDia() const{return dia;}
    int getMes() const{return this-> mes;}

    ///METODOS
    void ver()const;
    bool bisiesto() const;

    ///OPERADORES
    Fecha operator++( int i); //f++ (se incrementa despues)
    Fecha& operator++(); // ++f (primero se incrementa y se devuelve incrementado)
    Fecha operator+(const int &i) const; //f+i
    friend Fecha operator+(const int &i, const Fecha &f); //i+f
    friend ostream& operator<< (ostream& S, const Fecha& f);
};

// ostream-> flujos de salida, operador << (imprime datos a consola)
//Fecha operator+(const int &i, const Fecha &f); // const por velocidad y seguridad
//ostream& operator<< (ostream& s, const Fecha& f)

#endif // FECHA_H

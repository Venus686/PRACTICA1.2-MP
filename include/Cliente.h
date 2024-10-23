#ifndef CLIENTE_H
#define CLIENTE_H
#include "Fecha.h"
#include <iostream>
using namespace std;


class Cliente{
    long int dni;
    char* nombre; // destructor, constructor de copia y operador de asig
    //Cliente (const Cliente&)
    //Cliente &operator=(const Cliente&)
    Fecha fechaAlta;

    public:
    ///CONSTRUCTORES Y DESTRUCTOR
    Cliente(long int d, char* nom, Fecha j);
    Cliente (const Cliente &copia);
    ~Cliente();

    void setNombre(const char* name);
    void setFecha(Fecha F);

    const char* getNombre()const {return nombre;}
    long int getDni() const{return dni;}
    Fecha getFecha() const{return fechaAlta;}

    ///OPERADORES
    bool operator==(Cliente c)const; //if (c1==c2)
    Cliente& operator=(const Cliente& c);
    friend ostream& operator<< (ostream& os, const Cliente& c);
};

#endif // CLIENTE_H


//Fecha & operator++();
//Fecha operator++(int i);
// Fecha operator++(int i)const;

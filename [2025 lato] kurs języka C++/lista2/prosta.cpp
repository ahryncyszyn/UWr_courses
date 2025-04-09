#include "prosta.hpp"

prosta::prosta() : A(1), B(1), C(0) {};

prosta::prosta(double new_A, double new_B, double new_C)
: A(new_A), B(new_B), C(new_C) 
{
    if (A == 0 && B == 0) 
    {
        throw std::invalid_argument("A i B nie mogą być jednocześnie równe 0");
    }
};

prosta::~prosta() {};

double prosta::getA() const 
{
    return A; 
}

double prosta::getB() const 
{
    return B;
}

double prosta::getC() const 
{
    return C;
}

void prosta::setA(double newA) 
{
    A = newA;
}

void prosta::setB(double newB) 
{
    B = newB;
}

void prosta::setC(double newC) 
{
    C = newC;
}


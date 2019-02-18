#include <assert.h>
#include <stdexcept>
#include "imaginary.h"
#include <math.h>
// functions : add multiply negate conjugate maginitude


//Default Constructor

Imaginary::Imaginary(){
    real = 0;
    imag = 0;
}


Imaginary::Imaginary(double re, double im):Imaginary(){
    real = re;
    imag = im;
}

Imaginary::Imaginary(double val):Imaginary(){
    real = val;
    imag = val;
}
/*
Imaginary::Imaginary(const Imaginary& other) : Imaginary() {
    *this = other;
}
*/
double Imaginary::re(){
    return real;
}

double Imaginary::im(){
    return imag;
}

Imaginary Imaginary::conjugate (){
    imag = -1.0*imag;
    return *this;
}

double Imaginary::magnitude(){
    return(sqrt((real*real)+(imag*imag)));
}




Imaginary& Imaginary::operator+=(const Imaginary& other){
    real = real + other.real;
    imag = imag + other.imag;
    return *this;
}

Imaginary& Imaginary::operator*=(const Imaginary& other){
    double r = real * other.real  - imag*other.imag;
    double i = imag * other.real + real* other.imag;
    real = r;
    imag = i;
    return *this;
}
bool Imaginary::operator==(const Imaginary& other) const{
    if(real == other.real && imag == other.imag){
        return 1;
    }
    return 0;
}
Imaginary Imaginary::operator+(const Imaginary& other) const{
    double r = real + other.real;
    double i  = imag + other.imag;
    return Imaginary(r,i);
}
Imaginary Imaginary::operator*(const Imaginary& other) const{
    double r = real * other.real  - imag*other.imag;
    double i = imag * other.real + real* other.imag;
    
    return Imaginary(r,i);
}
#include "imaginary.h"
#include <math.h>
// functions : add multiply negate conjugate maginitude
Imaginary add (Imaginary a, Imaginary b){
  return (Imaginary){a.real + b.real , a.im + b.im};
}

Imaginary multiply (Imaginary a, Imaginary b){
  return (Imaginary){a.real * b.real ,  a.im * b.im};
}

Imaginary negate (Imaginary a){
  return (Imaginary) {-1*a.real,-1*a.im};
}

Imaginary conjugate (Imaginary a){
  return (Imaginary) {a.real,-1*a.im};
}

double magnitude (Imaginary a){
  return sqrt(a.real * a.real + a.im * a.im);
}




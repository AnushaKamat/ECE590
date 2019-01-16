#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce (Fraction a) {
  int num , den , neg, GCD;

  if(a.num == 0 && a.den == 0){  //Case : 0/0
    num = 0;
    den = 0;
  }
  else if (a.den == 0){             //Case : X/0 =>1/0
    num = 1;
    den = 0;
  }
  else if (a.num == 0){             //Case : 0/y => 0/1
    num = 0;
    den = 1;
  }
  else{                         //Reduction Case
    num = a.num;
    den = a.den;

    neg = ((a.num < 0) && (a.den < 0)) ? 1 :0;
    a.num = (a.num > 0) ? a.num: -1*a.num;
    a.den = (a.den > 0) ? a.den :-1*a.den;

    while (a.num != a.den){       //Using the GCD of num and den of fraction
      if(a.num > a.den){
        a.num = a.num - a.den;
      }
      else{
        a.den = a.den - a.num;
      }
    }
    GCD = a.num;
    //Reducing num and den by dividing with GCD 
    if (neg == 1){                //case of -X/-Y
      num =  -1 * (num / GCD);  
      den = -1 * (den / GCD);
    }
    else{
      num =  num / GCD;
      den = den / GCD;  
    }

  }
  return (Fraction) { num, den };
}
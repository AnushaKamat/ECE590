#ifndef IMAGINARY_H
#define IMAGINARY_H
#include <iostream>


/*! @file */

/*! \breif Imaginary object and method definitions
 *
 *  A imaginary object is a struct with a real,denoted real , and
 *  a imaginary, denoted im. Varions Methods that take imaginary number  and return 
 *  imaginary numbers do arithmetical operations on them.
 */


class Imaginary {

public:
    Imaginary(); //Default Constructor
    Imaginary(double re , double im);
    Imaginary(double val);

    // Destructor
   // ~Imaginary();

    //Getters
    double re();
    double im();

   

    //Conjugate
/*! \fn conjugate
 *  Complex Conjugate of the imaginary number
 *  \param a The term
 */
    Imaginary conjugate();

    //Magnitude
 /*! \fn magnitude
 *  Provides magnitude of Complex imaginary number
 *  \param a The term
 */
   double magnitude();

// Overload functions : +=, *=, ==, * and +


      Imaginary& operator+=(const Imaginary& other);
      
      Imaginary& operator*=(const Imaginary& other);
      bool operator==(const Imaginary& other) const;
      Imaginary operator+(const Imaginary& other) const;
      Imaginary operator*(const Imaginary& other) const;

private:
    double real,imag;


};





#endif
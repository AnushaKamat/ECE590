#ifndef IMAGINARY_H
#define IMAGINARY_H

/*! @file */

/*! \breif Imaginary object and method definitions
 *
 *  A imaginary object is a struct with a real,denoted real , and
 *  a imaginary, denoted im. Varions Methods that take imaginary number  and return 
 *  imaginary numbers do arithmetical operations on them.
 */
typedef struct {
    double real;
    double im;
} Imaginary;

/*! \fn add 
 *  Adds two imaginary numbers together
 *  \param a The first summand
 *  \param b The second summand
 */
Imaginary add ( Imaginary a, Imaginary b );

/*! \fn multiply
 *  Multiply two imaginary numbers together
 *  \param a The first term
 *  \param b The second term
 */
Imaginary multiply ( Imaginary a, Imaginary b );

/*! \fn negate
 *  Negates the imaginary number
 *  \param a The term
 */
Imaginary negate ( Imaginary a );

/*! \fn conjugate
 *  Complex Conjugate of the imaginary number
 *  \param a The term
 */
Imaginary conjugate ( Imaginary a );

/*! \fn magnitude
 *  Provides magnitude of Complex imaginary number
 *  \param a The term
 */
double magnitude ( Imaginary a );


#endif
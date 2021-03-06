#include <stdlib.h>
#ifndef SOLUTIONS_H
#define SOLUTIONS_H
/*! @file */

/*! \breif Assignment 2 , Due 25th Jan 2019
 *  Q1. Running Total
 *  Q2. Reverse in Place
 *  Q3. Reverse with new array
 *  Q4. Number of Instances in a array
 *  Q5. ToSet : To provide new array with duplicates removed
 *  Q7. Map a Point to manipulated Point using the function passed by function pointer 
 *  Q8. RPN : init, push, pop, add, multiply, negate, error, free
 */


/*! \fn running_total 
 *  Add parameter num to previously calculated sum
 *  \param num The number to be added 
 *  A static variable sum is used to keep track of sum in between fn calls
 */
int running_total(int num);


/*! \fn reverse_in_place 
 *  \param collection A collection / array of numbers
 *  \param numofvalues The length of collection  
 *  The fn takes these parameters and returns the reverse of this collection in the place of same collection
 */
void reverse_in_place(int * collection, int numofvalues);

/*! \fn reverse 
 *  \param collection A collection / array of numbers
 *  \param numofvalues The length of collection  
 *  The fn takes these parameters and returns the reverse of the collection in another collection 
 */
int * reverse(int * collection, int numofvalues);

/*! \fn num_instances
 *  \param collection A collection / array of numbers
 *  \param numofvalues The length of collection  
 *  \param value The specific number
 *  The fn takes looks for instances of the specific number in the collection of a particular length
 *  and returns the number of instances.
 */
int num_instances(int * collection, int numofvalues, int value);

/*! \fn to_set
 *  \param collection A collection / array of numbers
 *  \param size The length of collection  
 *  \param newsize The new length of transformed collection
 *  The fn takes a collection and its length and removes all duplicates or repeated numbers
 *  and returns the transformed collection and its new size.
 */
int * to_set(int * collection, int size, int * newsize );

/*! \fn map
 *  \param pointCollection A collection / array of struct Points
 *  \param size The length of collection  
 *  \param fptr The function pointer 
 *  The fn takes a collection, its length and the function pointer.
 *  It basically applies the function onto all points in the collection.
 */
typedef struct{
    double x,y,z;
}Point;


Point * map(Point * pointCollection,int size, Point (*fptr)(Point));

/*! \fn REVERSE POLISH NOTATION 
 *  The Stack is created using a struct which has a index to top, size of stack and pointers o values stored in them
 *  The status is an enum with multiple error conditions.
 */

typedef struct {
    int top;
    int size;
    double * array;
}Stack;

typedef enum status {
  NOT_INITIALIZED_ERROR, OK, POP_ERROR, NEGATE_ERROR, MULT_ERROR, ADD_ERROR, OVERFLOW_ERROR
} Status;

/*! \fn isFull
 *  isFull is a function to check if stack is full
 */
int isFull();

/*! \fn isEmpty
 *  isEmpty is a function to check if stack is empty
 */
int isEmpty();

/*! \fn isInf
 *  isInf to check if the number is more than max 
 */
int isInf(double x);


/*! \fn rpn_init
 *  The fn basically sets the whole RPN
 *  It creates a new stack.
 *  Frees old stack.
 *  Clears error
 */
void rpn_init();

/*! \fn rpn_push
 *  The fn pushes a double onto the stack.
 *  If stack is unintialised, it doesnt push the value
 *  If stack is full, it reallocates the size as double the previous size
 *  Clears error
 */
void rpn_push(double val);

/*! \fn rpn_add
 *  The fn adds the top 2 elements of the stack and puts into top of stack.
 *  If stack is unintialised and add is called, it doesnt add anything.
 *  If 2 operands for add is not found on stack , then ADD_ERROR is set
 *  If sum is greater than DBL_MAX or less than -DBL_MAX then a overflow error is set
 */
void rpn_add();

/*! \fn rpn_negate
 *  The fn negates the top element of the stack.
 *  If stack is unintialised and negate is called, it doesnt negate.
 *  If the operand for negation is not found on stack , then NEGATE_ERROR is set
 */
void rpn_negate();

/*! \fn rpn_multiply
 *  The fn multiplies the top 2 elements of the stack and puts into top of stack.
 *  If stack is unintialised and multiply is called, it doesnt multiply anything.
 *  If 2 operands for multiply is not found on stack , then MULT_ERROR is set
 *  If product is greater than DBL_MAX or less than -DBL_MAX then a overflow error is set
 */
void rpn_multiply();


/*! \fn rpn_pop
 *  The fn multpops the topmost element of stack.
 *  If stack is unintialised and pop is called, it pops 0.
 *  If stack is empty, then sets POP_ERROR
 */
double rpn_pop();


/*! \fn rpn_error
 *  The fn returns the various error set in all previous cases when called upon
 */
Status rpn_error();


/*! \fn rpn_free
 *  The fn frees the stack.
 *  Clears the error and sets to NOT_INITIALISED.
 */
void rpn_free();

#endif
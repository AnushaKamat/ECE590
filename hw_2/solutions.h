#include <stdlib.h>
#ifndef SOLUTIONS_H
#define SOLUTIONS_H

//#define NULL 0

//Things remaining to do :
//1. Documentation/Comment the code
//dddddddddddddddddddd2. ToSet function needs change(segmentation/Memory error)
//ddddddddddddddddddd 3. Robust Test Cases
//4. Add README file

/*! @file */

//Running Total
int running_total(int num);

//Reverse in Place
void reverse_in_place(int * collection, int numofvalues);

//Reverse
int * reverse(int * collection, int numofvalues);

//num of instances
int num_instances(int * collection, int numofvalues, int value);

//toset
int * to_set(int * collection, int size, int * newsize );

//map
typedef struct{
    double x,y,z;
}Point;
//Point negate(Point p);

Point * map(Point * pointCollection,int size, Point (*fptr)(Point));

//7. Reverse Polish Notation
typedef struct {
    int top;
    int size;
    double * array;
}Stack;
//Stack * stack = (Stack *)malloc(sizeof(Stack));


typedef enum status {
  NOT_INITIALIZED_ERROR, OK, POP_ERROR, NEGATE_ERROR, MULT_ERROR, ADD_ERROR, OVERFLOW_ERROR
} Status;

void rpn_init();
void rpn_push(double val);
void rpn_add();
void rpn_negate();
void rpn_multiply();
double rpn_pop();
Status rpn_error();
void rpn_free();

#endif
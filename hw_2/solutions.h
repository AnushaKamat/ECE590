#include<stdlib.h>
#ifndef SOLUTIONS_H
#define SOLUTIONS_H

//#define NULL 0

/*! @file */

//Running Total
int running_total(int num);

//Reverse in Place
void reverse_in_place(int * collection, const int numofvalues);

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
void rpn_init(void);

typedef enum status {
  OK, NOT_INITIALIZED_ERROR, POP_ERROR, NEGATE_ERROR, MULT_ERROR, ADD_ERROR, OVERFLOW_ERROR
} Status;

void rpn_init(void);
void rpn_push(double);
void rpn_add(void);
void rpn_negate(void);
void rpn_multiply(void);
double rpn_pop(void);
Status rpn_error(void);
void rpn_free(void);

#endif
#include "solutions.h"
#include<float.h>

int running_total(int num){
  static int sum =0;
  sum +=num;
  return sum;
}

void reverse_in_place(int * collection, const int numofvalues){
  int rev[numofvalues];
  for(int i = 0; i <numofvalues ; i++){
    rev[numofvalues - 1 -i] =  collection[i];
  }
  for(int i = 0; i <numofvalues ; i++){
    collection[i] = rev[i];
  }

}

int * reverse(int * collection, int numofvalues){
  int * newcollection = (int *) calloc(numofvalues,sizeof(int));
  for(int i = 0; i <numofvalues ; i++){
    newcollection[i] = collection[numofvalues-1-i];
  }
  return newcollection;
}

int num_instances(int * collection, int numofvalues, int value){
  int rep =0;
  for(int i = 0; i < numofvalues;i++){
    if(collection[i] == value){
      rep++;
    }
  }
  return rep;
}

int * to_set(int * collection, int size, int * nsize ){
  int * newcollection = (int*) malloc (size * sizeof(int));
  int newsize =0;
  int flag_add_val;
  for(int i = 0; i < size; i++){
    flag_add_val = 1;
    for(int j =0; j < newsize; j++){
      if(collection[i] == newcollection[j]){
        flag_add_val = 0;
        break;
      }
    }
    if(flag_add_val == 1){
      newcollection[newsize] = collection[i];
      newsize++;
    }
  }
  *nsize = newsize;
  return newcollection;
}

Point * map(Point * pointCollection,int size, Point (*fptr)(Point)){
  Point * newPointCollection = (Point *)calloc(size,sizeof(Point));
  for(int i = 0 ; i<size;i++){
    newPointCollection[i] = (*fptr)(pointCollection[i]);
  }
  return newPointCollection;
}

/****************************************************************/
/*                     RPN Calculator                          */
/***************************************************************/

static Stack stack;// = (Stack *)malloc(sizeof(Stack));
static Status error = NOT_INITIALIZED_ERROR;
void rpn_init(void){
  if(error != NOT_INITIALIZED_ERROR){
    rpn_free();
  }
  stack.size = 100; //need to realloc if more than 100 pushes happen
  stack.top = -1;//TOP
  stack.array = (double*)calloc(stack.size,sizeof(double));
  error = OK;
  return;
}

int isFull(){
  return stack.top == stack.size -1;
}

int isEmpty(){
  return stack.top == -1;
}

int isInf(double x){
  return(x < -DBL_MAX || x > DBL_MAX);
} 


void rpn_push(double item){ //what if stack is not initialised and push is made ??
  if(error != NOT_INITIALIZED_ERROR){ //If stack is not uninitialised and a push is tried to be made,  then it is not considered 
    if(isFull()){                     // Stack is Full considered
      stack.size *= 2;
      double  *tmp = (double *)realloc(stack.array, sizeof(double)*(stack.size));
      if (!tmp) {                     //new allocated pointer is a null, error case to exit
        exit(1);
      }
      else {
        stack.array = tmp;            //reallocation
      }
    }
    stack.array [++stack.top] = item;
  } 
}


void rpn_add(void){
  if(error != NOT_INITIALIZED_ERROR){   //Addded before initialising, no action
    if(stack.top <= 0){                   // ADD ERROR : 2 operands for add is not available
      if(error == OK){
       error = ADD_ERROR;
     }
    }
    else{
     double a = rpn_pop();
      double b = rpn_pop();
  
      if(isInf(a+b)){                     //OVERFLOW ERROR
       if(error == OK){
          error = OVERFLOW_ERROR;
        }
        rpn_push(0);
      }
      else{
        rpn_push(a+b);
      }
    }
  }
}


void rpn_negate(void){
  if(error != NOT_INITIALIZED_ERROR){   //Uninitialised Stack
    if(stack.top ==-1){
      if(error == OK){
        error = NEGATE_ERROR;           //No operand to negare
      }
    }
    else{
      stack.array[stack.top] *= -1.0;   //Negate
    }
  }
}

void rpn_multiply(void){
  if(error != NOT_INITIALIZED_ERROR){     //Uninitialised Stack
    if(stack.top <= 0){
      if(error == OK){                    //2 Operands not found
        error = MULT_ERROR;
      }
    }
    else{
      double a = rpn_pop();
      double b = rpn_pop();
      if(isInf(a*b)){                     //Overflow
        if (error == OK){
          error = OVERFLOW_ERROR;
        }
        rpn_push(0);
      }
      else{
        rpn_push(a*b);                    //Multiply
      }
    } 
  }
}


double rpn_pop(void){
  if(error != NOT_INITIALIZED_ERROR){
    if(isEmpty()){
      if(error == OK){
        error = POP_ERROR;                     //nothing to pop, stack is empty , pop error
      }
      return 0;
    }
    return stack.array[stack.top--];          // pop
  }
  else 
    return 0;                                 //uninitialised stack, pops 0
}

Status rpn_error(void){
  return error;
}

void rpn_free(void){
  free(stack.array);
  error = NOT_INITIALIZED_ERROR;
}
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
//might fail for 0 when used with calloc
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
 // * newPointCollection = (*fptr)(* pointCollection);
  return newPointCollection;
}

/****************************************************************/
/*                     RPN Calculator                          */
/***************************************************************/

 Stack * stack;// = (Stack *)malloc(sizeof(Stack));
 Status error = NOT_INITIALIZED_ERROR;
void rpn_init(void){

  stack = (Stack *)malloc(sizeof(Stack));
  stack->size = 100; //need to realloc if more than 100 pushes happen
  stack -> top = -1;//TOP
  stack -> array = (double*)calloc(stack->size,sizeof(double));
  error = OK;
  return;
}

int isFull(){
  return stack->top == stack->size -1;
}

int isEmpty(){
  return stack->top == -1;
}
int is_inf(double x){
  return(x < -DBL_MAX || x > DBL_MAX);
} 
int flag =0;
void rpn_push(double item){ //what if stack is not initialised and push is made ??
 if(error != NOT_INITIALIZED_ERROR){ //!=non initialised?
   if(isFull()){
    stack -> size += 100;
    double  *tmp = (double *)realloc(stack->array, sizeof(double)*(stack->size));
if (!tmp) {
    flag = 1;
} else {
    stack->array = tmp;
}
    
  }
  stack -> array [++stack->top] = item;
 } 
}
void rpn_add(void){
  //less than 2 operands available
  //overflow check
  if(error != NOT_INITIALIZED_ERROR){
  if(stack -> top <= 0){
    if(error == OK){
      error = ADD_ERROR;
    }
  }
  else{
  double a = rpn_pop();
  double b = rpn_pop();
  
  if(is_inf(a+b)){
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
  //error for negating when there is nothing
   if(error != NOT_INITIALIZED_ERROR){
  if(stack ->top ==-1){
    if(error == OK){
      error = NEGATE_ERROR;
    }
  }
  else{
    stack ->array[stack->top] *= -1.0;
  }
   }
}
void rpn_multiply(void){
  //less than 2 operands
  //overflow error
  if(error != NOT_INITIALIZED_ERROR){
  if(stack -> top <= 0){
    if(error == OK){
    error = MULT_ERROR;
    }
  }
  else{
    double a = rpn_pop();
    double b = rpn_pop();
  if(is_inf(a*b)){
    if (error == OK){
    error = OVERFLOW_ERROR;
    }
    rpn_push(0);
  }
  else{
    rpn_push(a*b);
  }
  } 
  }
}
double rpn_pop(void){
if(error != NOT_INITIALIZED_ERROR){
  if(isEmpty()){
    //initialise pop error
    if(error == OK){
    error = POP_ERROR;
    }
    return 0;
  }
  return stack->array[stack->top--];
}
else 
  return 0;
}

Status rpn_error(void){
  return error;
}

void rpn_free(void){
  free(stack->array);//how to un-initialize
  free(stack);
  error = NOT_INITIALIZED_ERROR;
}
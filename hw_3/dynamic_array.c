#include "dynamic_array.h"
#include "arbitrary_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

static DynamicArray* DynamicArray_sort (const DynamicArray * da){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    int sz = DynamicArray_size(da);
    double tmp;
    DynamicArray * sorted_da =  DynamicArray_copy (da);
    for(int i = 0; i<sz; i++){
        for(int j = i+1;j<sz; j++){
            if(DynamicArray_get(sorted_da,i)>DynamicArray_get(sorted_da,j)){
                tmp = DynamicArray_get(sorted_da,i);
                DynamicArray_set(sorted_da,i, DynamicArray_get(sorted_da,j));
                DynamicArray_set(sorted_da,j,tmp);
            }
        }
    }
    return sorted_da;
}

/* public functions **********************************************************/

/* Arbitrary Array to save all pointers to DynamicArrays created*/
static ArbitraryArray* ptrtoDA = ArbitraryArray_new(sizeof(DynamicArray *)); 


static int count =0;

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    ArbitraryArray_push(ptrtoDA,da);
    count++;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    count--;  //***********Check ***********//

    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }
    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_first(da);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(result); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(result, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {
    assert(da->buffer != NULL);
    if ( b < a ) {
        printf("DynamicArray_subarray called with invalid indices (b=%d<a%d)", b, a);
        exit(1);
    }
    DynamicArray * result = DynamicArray_new();
    for (int i=a; i<b; i++) {
        DynamicArray_push(result,DynamicArray_get(da, i));
    }
    return result;
}

double DynamicArray_sum ( const DynamicArray * da ){ //check divide by zero
   int sz;
   double sum = 0;
   assert(da->buffer != NULL);
   sz = DynamicArray_size(da);
   for(int i =0 ; i<sz; i++){
       sum += DynamicArray_get(da, i);
   } 
   return sum;
}

double DynamicArray_mean ( const DynamicArray * da ){ //check divide by zero
   int sz;
   double avg = 0;
   assert(da->buffer != NULL);
   assert(DynamicArray_size(da) > 0);
   sz = DynamicArray_size(da);
   avg = DynamicArray_sum (da);
   avg /=sz;
   return avg;
}

double DynamicArray_min ( const DynamicArray * da ){
    double min;
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    DynamicArray * sort_da =  DynamicArray_sort(da);
    min =  DynamicArray_get(sort_da, 0);
    DynamicArray_destroy(sort_da);  
    return min;
}
double DynamicArray_max ( const DynamicArray * da ){
    double max;
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    DynamicArray * sort_da =  DynamicArray_sort(da);
    max =  DynamicArray_get(sort_da, DynamicArray_size(da)-1);
    DynamicArray_destroy(sort_da);  
    return max;
}
double DynamicArray_median ( const DynamicArray * da ){
    double median = 0;
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    DynamicArray * sort_da =  DynamicArray_sort(da);
    DynamicArray_print_debug_info(sort_da);
    if(DynamicArray_size(sort_da)%2 == 0){
        median = DynamicArray_get(sort_da, (int)DynamicArray_size(da)/2)+DynamicArray_get(sort_da, (int)((DynamicArray_size(da)/2)-1));
        median /=2;
    }
    else{
        median = DynamicArray_get(sort_da, (int)(DynamicArray_size(da)/2));
    }
    DynamicArray_destroy(sort_da);  
    return median;
}

double DynamicArray_last (const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double last;
    last =DynamicArray_get(da, DynamicArray_size(da)-1);
    return last;
}

double DynamicArray_first (const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double first;
    first = DynamicArray_get(da, 0);
    return first;
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    DynamicArray * copy_da = DynamicArray_new();
    int sz = DynamicArray_size(da);  
    for(int i = 0; i<sz; i++){
        DynamicArray_set(copy_da, i, DynamicArray_get(da,i) );
    }
    return copy_da;
}

DynamicArray * DynamicArray_range ( double a, double b, double step){
    DynamicArray * da = DynamicArray_new();
    int flag = 0;
    if (step > 0){
        if(a< b){
            flag = 1;
        }
    }
    else{
        if(a > b){
            flag =1 ;
        }
    }
    if(flag){
        int n = (b - a)/step;
        n++;
        for(int i = 0 ; i < n; i++  ){
            DynamicArray_set(da,i,a+i*step);
        }
    }
    return da;
}
DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ){
    int sz1 = DynamicArray_size(a);
    int sz2 = DynamicArray_size(b);
    DynamicArray * da = DynamicArray_new();
    for(int i = 0; i<sz1 ;i++){
        DynamicArray_set(da, i, DynamicArray_get(a,i) );
    }
    for(int i = 0; i<sz2 ;i++){
        DynamicArray_set(da, i+sz1, DynamicArray_get(b,i) );
    }
    return da;
}

DynamicArray * DynamicArray_take(const DynamicArray *da,const int n){
    assert(da->buffer != NULL);
    DynamicArray * take_da = DynamicArray_new(); 
    int i = 0;
    if(n > 0){
        if(n < DynamicArray_size(da)){
            for(int i = 0 ; i <n; i++){ //n +ve, take from start and append with zeros if surpasses
                DynamicArray_set(take_da, i, DynamicArray_get(da,i) );
            }
        }
        else{
            for(int i = 0 ; i <DynamicArray_size(da); i++){ //n +ve, take from start and append with zeros if surpasses
                DynamicArray_set(take_da, i, DynamicArray_get(da,i) );
            }
            for(int i = DynamicArray_size(da); i<n;i++){
                DynamicArray_set(take_da, i, 0);
            }
        }
    }
    else{
        //n is -ve take from back and append with zeros if surpassed
        if(abs(n) < DynamicArray_size(da)){
            for(int i = DynamicArray_size(da) + n  ; i < DynamicArray_size(da); i++){ //n +ve, take from start and append with zeros if surpasses
                DynamicArray_set(take_da, i- DynamicArray_size(da) - n , DynamicArray_get(da,i) );
                //printf("%d",i);
            }
            
        }
        else{
            for(int i = 0 ; i < DynamicArray_size(da) ; i++){ //n +ve, take from start and append with zeros if surpasses
                DynamicArray_set(take_da, i, DynamicArray_get(da,i) );
            }
            
            
            for(int i = DynamicArray_size(da);i < abs(n);i++){
                DynamicArray_set(take_da, i, 0);
            }
        }
    }
    return take_da;
}
int DynamicArray_search (const DynamicArray * da){
    int index;
    for(int i = 0; i<ArbitraryArray_size(ptrtoDA);i++){
        DynamicArray** ptr_da = (DynamicArray**)ArbitraryArray_get_ptr(ptrtoDA,i);
        if(*ptr_da == da){
            index =i;
        }
    }
    return index;
}
int DynamicArray_is_valid( const DynamicArray * da){          //***********Check ***********//
    int i = 0;
    int index = DynamicArray_search(da);
    DynamicArray** ptr_da = (DynamicArray**)ArbitraryArray_get_ptr(ptrtoDA,index);
    if((*ptr_da)->buffer!=NULL){
        return 1;
    }
    return 0;
}

/*! Returns the number of arrays that have been constructed to far.
 */
int DynamicArray_num_arrays(){                        //***********Check ***********//
    return count;
}

/*! Destroys all arrays that have been constructed so far.
 */
int DynamicArray_destroy_all(){                           //***********Check ***********//
    
    int i = 0;
     for (i = 0; i< ArbitraryArray_size(ptrtoDA);i++){
        DynamicArray** ptr_da = (DynamicArray**)ArbitraryArray_get_ptr(ptrtoDA,i);
        if((*ptr_da)->buffer !=NULL){
            (*ptr_da)->buffer =NULL;
            count --;
        }
    }
}


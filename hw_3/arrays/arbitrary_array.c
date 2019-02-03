#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dynamic_array.h"
#include "arbitrary_array.h"


/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const ArbitraryArray * da, int index ) {
    return da->element_size * index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const ArbitraryArray * da, int offset ) {
    return ( offset - da->origin ) / da->element_size;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( ArbitraryArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity * da->element_size;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( ArbitraryArray * da ) {

    char * temp = (char *) calloc ( 2 * da->capacity, da->element_size );
    
    int new_origin = da->element_size * (da->capacity - (offset_to_index(da,da->end) - offset_to_index(da,da->origin))/2);
    int new_end = new_origin + (da->end - da->origin);
    
    for ( int i=0; i<ArbitraryArray_size(da); i++ ) {
        memcpy(temp + new_origin + i * da->element_size,
               da->buffer + da->origin + i * da->element_size,
               da->element_size);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

ArbitraryArray * ArbitraryArray_new(int element_size) {
    ArbitraryArray * da = (ArbitraryArray *) malloc(sizeof(ArbitraryArray));
    da->element_size = element_size;
    da->capacity = ARBITRARY_ARRAY_INITIAL_CAPACITY;
    da->buffer = (char *) calloc ( 
        da->capacity, 
        element_size
    ); 
    da->origin = ( da->capacity / 2 ) * da->element_size;
    da->end = da->origin;
    return da;
}

void ArbitraryArray_destroy(ArbitraryArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int ArbitraryArray_size(const ArbitraryArray * da) {
    assert(da->buffer != NULL);
    return ( da->end - da->origin ) / da->element_size;
}

void * ArbitraryArray_get_ptr(const ArbitraryArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= ArbitraryArray_size(da) ) {
        return NULL;
    } else {
        return (void*) ( da->buffer + index_to_offset(da, index) );
    }
}

void ArbitraryArray_set_from_ptr(ArbitraryArray * da, int index, void * ptr) {

    assert(da->buffer != NULL);
    assert ( index >= 0 );

    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    memcpy(da->buffer + index_to_offset(da, index), ptr, da->element_size);
    if ( index >= ArbitraryArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

void ArbitraryArray_print_debug_info(const ArbitraryArray * da) {

    printf ( "  size: %d\n  capacity: %d elements\n", ArbitraryArray_size(da), da->capacity);
    printf ( "  element size: %d\n", da->element_size);
    printf ( "  buffer addr: %d\n  origin addr: %d\n", da->buffer, da->buffer + da->origin);
    printf ( "  end addr: %d\n", da->buffer + da->end);
    printf ( "\n" );

}

char * ArbitraryArray_to_string(const ArbitraryArray * a, char * (*element_to_string) (void * p ) ){
    char * str = (char *) calloc (20,ArbitraryArray_size(a)),temp[20];
    int j = 0;
    for ( int i=0; i < ArbitraryArray_size(a); i++ ) {
        if ( ArbitraryArray_get_ptr (a,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } 
        else {
            snprintf ( temp, 20,(*element_to_string) (ArbitraryArray_get_ptr(a,i)) ); 
        }

        if ( i < ArbitraryArray_size(a) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } 
        else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }
    }
    return str;
}

void ArbitraryArray_push(ArbitraryArray * da, void * value ) {
    ArbitraryArray_set_from_ptr(da, ArbitraryArray_size(da), value );
}

void ArbitraryArray_remove_ptr(ArbitraryArray * aa, void *da) {           //***********Check ***********//
    assert(aa->buffer != NULL);
    int i = 0;
    while(i < ArbitraryArray_size(aa)){
        DynamicArray ** ptr_da = (DynamicArray**)ArbitraryArray_get_ptr(aa,i);
        if(da ==  (*ptr_da)){
            ArbitraryArray_set_from_ptr(aa, i, 0);
            printf("goes into remove if case \n");
            break;
        }
        i++;
    }
    return;
}
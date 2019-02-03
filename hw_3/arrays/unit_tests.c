#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "arbitrary_array.h"
#include "gtest/gtest.h"

#define X 1.2345

typedef struct {
    double x, y, z;
} Point;

typedef struct {
            double a;
            int b;
            double c;
} simply;

char * point_to_string ( void * p ) {
    Point * q = (Point *) p;
    char * str = (char *) calloc(40, sizeof(char));
    snprintf(str,40,"{%.1lf,%.1lf,%.1lf}", q->x, q->y, q->z);
    return str;
}

char * simply_to_string ( void * s ) {
    simply * q = (simply *) s;
    char * str = (char *) calloc(40, sizeof(char));
    snprintf(str,40,"{%.1lf,%d,%.1lf}", q->a, q->b, q->c);
    return str;
}

char * double_to_string(void * d){
    double * dp =  (double *) d;
    char * str = (char *) calloc(40, sizeof(char));
    snprintf(str,40,"{%.1lf}",*dp);
    return str;
}

namespace {
    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        DynamicArray_print_debug_info(da);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        DynamicArray_print_debug_info(da);        
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        DynamicArray_print_debug_info(da);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 1;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        DynamicArray_print_debug_info(da); 
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        DynamicArray_print_debug_info(da); 
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 1;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        DynamicArray_print_debug_info(da); 
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        DynamicArray_print_debug_info(da);         
        DynamicArray_destroy(da);          
    } 

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        DynamicArray_print_debug_info(da);         
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_print_debug_info(da);         
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ///ASSERT_EQ(DynamicArray_get(y,i), sin(0.1*i));
            // ASSERT_DOUBLE_EQ(DynamicArray_get(y,i), sin(0.1*i));
            ASSERT_LT(
                abs(DynamicArray_get(y,i) - sin(0.1*i)),
                DBL_EPSILON
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }     

    TEST(DynamicArray, MeanBasic) {
        DynamicArray * t = DynamicArray_new();
        double m;
        for ( int i=0; i<5; i++ ) {
            DynamicArray_set(t, i, i+1);
            
        }
        m = DynamicArray_mean(t);
        ASSERT_DOUBLE_EQ(m,3.0 );
        DynamicArray_destroy(t);    
                           
    }  

    TEST(DynamicArray, MinBasic) {
        DynamicArray * t = DynamicArray_new();
        double m;
        for ( int i=0; i<5; i++ ) {
            DynamicArray_set(t, i, -i-1);
            
        }
        m = DynamicArray_min(t);
        ASSERT_DOUBLE_EQ(m,-5.0 );
        DynamicArray_destroy(t);    
                           
    }   

    TEST(DynamicArray, MaxBasic) {
        DynamicArray * t = DynamicArray_new();
        double m;
        for ( int i=0; i<5; i++ ) {
            DynamicArray_set(t, i, i+1);
            
        }
        m = DynamicArray_max(t);
        ASSERT_DOUBLE_EQ(m,5.0 );
        DynamicArray_destroy(t);    
                           
    }    

    TEST(DynamicArray, MedianBasic) {
        
        DynamicArray * t = DynamicArray_new();
        double m;
        DynamicArray_set(t, 0, 26);
        DynamicArray_set(t, 1, 16);
        DynamicArray_set(t, 2, 36);   
        
        m = DynamicArray_median(t);
        ASSERT_DOUBLE_EQ(m,26.0 );
        DynamicArray_destroy(t);  
        
        DynamicArray * t2 = DynamicArray_new();
        double m2;
        DynamicArray_set(t2, 0, 26);
        DynamicArray_set(t2, 1, 16);
        DynamicArray_set(t2, 2, 36);   
        DynamicArray_set(t2, 3, 46); 
        
        m2 = DynamicArray_median(t2);
        ASSERT_DOUBLE_EQ(m2,31.0 );
        DynamicArray_destroy(t2);   
                           
    }
    TEST(DynamicArray, LastBasic) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, -X);  
        DynamicArray_print_debug_info(da);
        x = DynamicArray_last(da);  
        DynamicArray_print_debug_info(da);         
        //ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,-X);
        //ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_print_debug_info(da);         
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, FirstBasic) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, -X);  
        DynamicArray_print_debug_info(da);
        x = DynamicArray_first(da);  
        DynamicArray_print_debug_info(da);         
        //ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        //ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_print_debug_info(da);         
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, RangeBasic) {
        DynamicArray * x = DynamicArray_range ( 1, 5, 1);  
        DynamicArray_print_debug_info(x);
                
        DynamicArray_destroy(x);          

        DynamicArray * ax = DynamicArray_range ( 5, 17, 4);  
        DynamicArray_print_debug_info(ax);
                
        DynamicArray_destroy(ax); 
    }
    TEST(DynamicArray, ConcatBasic) {
        DynamicArray * x = DynamicArray_range ( 1, 5, 1);  
        DynamicArray_print_debug_info(x);
        DynamicArray * ax = DynamicArray_range ( 6, 10, 1);  
        DynamicArray_print_debug_info(ax);
        DynamicArray *r = DynamicArray_concat(x,ax);
        DynamicArray_print_debug_info(r);
        DynamicArray_destroy(r);
        DynamicArray_destroy(x);         
        DynamicArray_destroy(ax); 
    }
    TEST(DynamicArray, TakeBasic) {
        DynamicArray * a = DynamicArray_range ( 1, 5, 1);  
        DynamicArray_print_debug_info(a);
        DynamicArray *b = DynamicArray_take(a,2);
        DynamicArray_print_debug_info(b);
        DynamicArray *c = DynamicArray_take(a,7);
        DynamicArray_print_debug_info(c);
        DynamicArray *d = DynamicArray_take(a,10);
        DynamicArray_print_debug_info(d);

        DynamicArray * e = DynamicArray_range ( 5, 1, -1); 
        DynamicArray_print_debug_info(e);
        DynamicArray *f = DynamicArray_take(e,2);
        DynamicArray_print_debug_info(f);
        DynamicArray *g = DynamicArray_take(e,7);
        DynamicArray_print_debug_info(g);

        printf("Negative \n");
        DynamicArray * a2 = DynamicArray_range ( 1, 5, 1);  
        DynamicArray_print_debug_info(a2);
        DynamicArray *b2 = DynamicArray_take(a2,-2);
        DynamicArray_print_debug_info(b2);
        DynamicArray *c2 = DynamicArray_take(a2,-7);
        DynamicArray_print_debug_info(c2);
        DynamicArray *d2 = DynamicArray_take(a2,-10);
        DynamicArray_print_debug_info(d2);

        DynamicArray * e2 = DynamicArray_range ( 5, 1, -1); 
        DynamicArray_print_debug_info(e2);
        DynamicArray *f2 = DynamicArray_take(e2,-2);
        DynamicArray_print_debug_info(f2);
        DynamicArray *g2 = DynamicArray_take(e2,-7);
        DynamicArray_print_debug_info(g2);


        DynamicArray_destroy(g);
        DynamicArray_destroy(g2);
        DynamicArray_destroy(f);
        DynamicArray_destroy(e);
        DynamicArray_destroy(d);
        DynamicArray_destroy(c);  
        DynamicArray_destroy(b);  
        DynamicArray_destroy(a);       
        DynamicArray_destroy(d2);
        DynamicArray_destroy(c2);  
        DynamicArray_destroy(b2);  
        DynamicArray_destroy(a2);    
        
    }


   TEST(ArbitraryArray, Basics1) {

       ArbitraryArray * a = ArbitraryArray_new(sizeof(double));
       ArbitraryArray * b = ArbitraryArray_new(sizeof(Point));
       ArbitraryArray * c = ArbitraryArray_new(sizeof(ArbitraryArray));

       ASSERT_EQ(NULL, ArbitraryArray_get_ptr(a,0));
       ASSERT_EQ(NULL, ArbitraryArray_get_ptr(b,0));
       ASSERT_EQ(NULL, ArbitraryArray_get_ptr(c,0));

       double x = 3.14;
       ArbitraryArray_print_debug_info(a);
       ArbitraryArray_set_from_ptr(a, 0, &x);
       ArbitraryArray_print_debug_info(a);
       ASSERT_EQ(x, *((double *) ArbitraryArray_get_ptr(a,0)));

       Point p = { 3.1, 4.1, 5.9 };
       ArbitraryArray_set_from_ptr( b, 9, &p );
       ArbitraryArray_print_debug_info(b);       

       Point * q = ((Point *) ArbitraryArray_get_ptr(b,9));
       ASSERT_EQ(p.x, q->x);
       ASSERT_EQ(p.y, q->y);
       ASSERT_EQ(p.z, q->z);

       ArbitraryArray_destroy(a);
       ArbitraryArray_destroy(b);
       ArbitraryArray_destroy(c);

   }
   
    TEST(DynamicArray, Min_Max){
        
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 35.0);
        DynamicArray_push(da, -2.0);
        DynamicArray_push(da, 18.0);
        ASSERT_DOUBLE_EQ(DynamicArray_max(da), 35.0);
        ASSERT_DOUBLE_EQ(DynamicArray_min(da), -2.0);
        DynamicArray_pop_front(da);
        ASSERT_DOUBLE_EQ(DynamicArray_max(da), 18.0);
        DynamicArray_pop(da);
        ASSERT_DOUBLE_EQ(DynamicArray_max(da), -2.0);
        ASSERT_DOUBLE_EQ(DynamicArray_min(da), -2.0);
        DynamicArray_pop(da);
        ASSERT_DEATH(DynamicArray_max(da), ".*Assertion.*");
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, Median){
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 2.0);
        DynamicArray_push(da, 10.0);
        DynamicArray_push(da, 21.0);
        DynamicArray_push(da, 3.0);
        DynamicArray_push(da, 11.0);
        ASSERT_DOUBLE_EQ(DynamicArray_median(da), 10.0);
        DynamicArray_push(da, 4.0);
        ASSERT_DOUBLE_EQ(DynamicArray_median(da), 7.0);
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, Sum_Mean){
        DynamicArray * da = DynamicArray_new();
        ASSERT_DOUBLE_EQ(DynamicArray_sum(da), 0);
        ASSERT_DEATH(DynamicArray_mean(da), ".*Assertion.*");
        double sum = -5.2+6.8+9.9+(-4.35)+0.77;
        double mean = sum/5.0;
        DynamicArray_push(da, -5.2);
        DynamicArray_push(da, 6.8);
        DynamicArray_push(da, 9.9);
        DynamicArray_push(da, -4.35);
        DynamicArray_push(da, 0.77);        
        ASSERT_DOUBLE_EQ(DynamicArray_sum(da), sum);
        ASSERT_DOUBLE_EQ(DynamicArray_mean(da), mean);
        DynamicArray_destroy(da);
        free(da);
    }
    
    TEST(DynamicArray, First_Last){
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 23.0);
        DynamicArray_push(da, 45.0);
        ASSERT_DOUBLE_EQ(DynamicArray_first(da), 23.0);
        ASSERT_DOUBLE_EQ(DynamicArray_last(da), 45.0);
        DynamicArray_pop(da);
        ASSERT_DOUBLE_EQ(DynamicArray_first(da), 23.0);
        ASSERT_DOUBLE_EQ(DynamicArray_last(da), 23.0);
        DynamicArray_pop(da);
        ASSERT_DEATH(DynamicArray_first(da), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_last(da), ".*Assertion.*");
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, Copy){
        DynamicArray * da = DynamicArray_new();
        for (int i = 0; i < 5; i++){
            DynamicArray_push(da, i);
        }
        DynamicArray *ptr = DynamicArray_copy(da);
        for (int i = 0; i < 5; i++){
            ASSERT_EQ(DynamicArray_get(ptr, i), i);
        }
        DynamicArray_set(ptr, 2, 101);
        ASSERT_EQ(DynamicArray_get(da, 2), 2);
        ASSERT_EQ(DynamicArray_get(ptr, 2), 101);
        DynamicArray_destroy(da);
        DynamicArray_destroy(ptr);
        free(da);
        free(ptr);
    }

    TEST(DynamicArray, Range){
        DynamicArray * a = DynamicArray_range(1.0, 2.0, 0.3);
        for(int i=0; i<DynamicArray_size(a); i++){
            ASSERT_LT(
                abs(DynamicArray_get(a,i) - (1.0 + i*0.3)),
                DBL_EPSILON
            );
        }
        DynamicArray * b = DynamicArray_range(7.0, 1.0, -2);
        for(int i=0; i<DynamicArray_size(b); i++){
            ASSERT_LT(
                abs(DynamicArray_get(b,i) - (7.0 - i*2)),
                DBL_EPSILON
            );
        }
        DynamicArray * c = DynamicArray_range(6, 4, 3);
        ASSERT_EQ(DynamicArray_size(c), 0);
        ASSERT_DEATH(DynamicArray_first(c), ".*Assertion.*");
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        free(a);
        free(b);
        free(c);
    }

    TEST(DynamicArray, Concat)
    {
        DynamicArray *a = DynamicArray_new();
        DynamicArray *b = DynamicArray_range(1, 2, 0.1);
        DynamicArray *c = DynamicArray_concat(a, b);
        for (int i = 0; i < DynamicArray_size(b); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, DynamicArray_size(a) + i), 1 + 0.1 * i);
        }
        DynamicArray_destroy(a);        
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        free(a);
        free(b);
        free(c);
    }
    TEST(DynamicArray, Take){
        DynamicArray *a = DynamicArray_range(-2, 3, 1);
        DynamicArray *b = DynamicArray_take(a, 2);
        for (int i = 0; i < DynamicArray_size(b); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(b, i), -2 + i);
        }
        DynamicArray *c = DynamicArray_take(a, -2); 
        for (int i = 0; i < DynamicArray_size(c); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, i), i+2);
        }
        DynamicArray *d = DynamicArray_take(a, 10); 
        for (int i = 6; i < DynamicArray_size(d); i++)
        {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, i), 0);
        }
        DynamicArray_destroy(a);        
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
        free(a);
        free(b);
        free(c);
        free(d);
    }


    TEST(ArbitraryArray, String){
        Point p = {1, 2, 3}, q = {4, 5, 6};
        ArbitraryArray *a = ArbitraryArray_new(sizeof(Point));
        ArbitraryArray_set_from_ptr(a, 0, &p);
        ArbitraryArray_set_from_ptr(a, 1, &q);    
        char *s = ArbitraryArray_to_string(a, point_to_string);
        ASSERT_STREQ(s, "{1.0,2.0,3.0},{4.0,5.0,6.0}");
        ArbitraryArray_destroy(a);
        free(a);  

        Point p2 = {1.1, 2.1, 3.1}, q2 = {4.1, 5.1, 6.1};
        ArbitraryArray *a2 = ArbitraryArray_new(sizeof(Point));
        ArbitraryArray_set_from_ptr(a2, 0, &p2);
        ArbitraryArray_set_from_ptr(a2, 1, &q2);      
        char *s2 = ArbitraryArray_to_string(a2, point_to_string);
        ASSERT_STREQ(s2, "{1.1,2.1,3.1},{4.1,5.1,6.1}");
        ArbitraryArray_destroy(a2);
        free(a2);
 
        simply p3 = {1.1, 2, 3.1}, q3 = {4.1, 5, 6.1};
        ArbitraryArray *a3 = ArbitraryArray_new(sizeof(simply));      
        ArbitraryArray_set_from_ptr(a3, 0, &p3);
        ArbitraryArray_set_from_ptr(a3, 1, &q3);
        char *s3 = ArbitraryArray_to_string(a2, simply_to_string);
        ASSERT_STREQ(s3, "{1.1,2,3.1},{4.1,5,6.1}");
        ArbitraryArray_destroy(a3);
        free(a3);
    
        double p4 = 1.2, q4 = 4.2;
        ArbitraryArray *a4 = ArbitraryArray_new(sizeof(double));
        ArbitraryArray_set_from_ptr(a4, 0, &p4);
        ArbitraryArray_set_from_ptr(a4, 1, &q4);
        char *s4 = ArbitraryArray_to_string(a4, double_to_string);
        ASSERT_STREQ(s4, "{1.2},{4.2}");
        ArbitraryArray_destroy(a4);
        free(a4);
    }

    TEST(ArbitraryArray,OfPointers) {

    // Create the array that will hold the pointers
    ArbitraryArray * ptrs = ArbitraryArray_new(sizeof(DynamicArray *));

    // Create a couple of dynamic arrays
    DynamicArray * a = DynamicArray_new(),* b = DynamicArray_new();

    // Add the dynamic arrays to the pointer array
    ArbitraryArray_set_from_ptr(ptrs, 0, &a);
    ArbitraryArray_set_from_ptr(ptrs, 1, &b);

    // Get them back. Note that because the array contains pointers,
    // and _get_ptr returns a pointer to a pointer, we need to cast
    // its result as a pointer to a DynamicArray pointer.
    DynamicArray ** ptr_a = (DynamicArray **) ArbitraryArray_get_ptr(ptrs,0);
    DynamicArray ** ptr_b = (DynamicArray **) ArbitraryArray_get_ptr(ptrs,1);

    // Check that the pointers are equal
    ASSERT_EQ(*ptr_a, a);
    ASSERT_EQ(*ptr_b, b);
    ASSERT_NE(*ptr_a, b);
    ASSERT_NE(*ptr_b, a);
    ArbitraryArray_destroy(ptrs);
    free(ptrs);
    DynamicArray_destroy(a);
    free(a);
    }

    
    TEST(DynamicArray, All){
        DynamicArray *a = DynamicArray_range(0, 1, 0.1);
        ASSERT_EQ(DynamicArray_is_valid(a), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 1);
        
        DynamicArray *b = DynamicArray_range(1.1, 2, 0.1);
        ASSERT_EQ(DynamicArray_num_arrays(), 2);
        
        DynamicArray *c = DynamicArray_concat(a, b);
        ASSERT_EQ(DynamicArray_num_arrays(), 3);
        
        DynamicArray *d = DynamicArray_take(a, -3);
        ASSERT_EQ(DynamicArray_num_arrays(), 4);
        
        DynamicArray *e = DynamicArray_copy(b);
        ASSERT_EQ(DynamicArray_num_arrays(), 5);
        
        DynamicArray *f = DynamicArray_copy(b);
        ASSERT_EQ(DynamicArray_num_arrays(), 6);
        
        DynamicArray_destroy(f);
        free(f);
         ASSERT_EQ(DynamicArray_num_arrays(), 5);
        
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_is_valid(a), 0);
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        free(a);
        free(b);
        free(c);
        free(d);
        free(e);
        
    } 
}

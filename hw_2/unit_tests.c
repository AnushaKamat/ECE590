#include "gtest/gtest.h"
#include "solutions.h"

namespace {

    TEST(HW2,RunningTotal) {
        ASSERT_EQ(running_total(-2),  -2);
        ASSERT_EQ(running_total(5),  3);
        ASSERT_EQ(running_total(-7), -4);
        ASSERT_EQ(running_total(12), 8); 
        ASSERT_EQ(running_total(0),8);
        ASSERT_EQ(running_total(-7),1);  
        ASSERT_EQ(running_total(212356),212357);  
    } 
    
    TEST(HW2,ReverseInPlace) {
        int x[] = {-9, -8, -7, -6, -5};
        int ansx[] = {-5, -6, -7, -8, -9};
        reverse_in_place(x,5);
        for(int i=0; i<5; i++)
            ASSERT_EQ(x[i], ansx[i]);
        int y[] = {-9, -8, -7, -6, -5, -4};
        int ansy[] = {-4, -5, -6, -7, -8, -9};
        reverse_in_place(y,6);
        for(int i=0; i<6; i++)
            ASSERT_EQ(y[i], ansy[i]);                           
    }
    
    TEST(HW2,Reverse) {
        int x[] = {-1, -2, -3, -4, -5, -6, -7, -8};
        int * y = reverse(x,8);
        for(int i=0; i<8; i++)
            ASSERT_EQ(y[i], x[8-1-i]);
          
        free(y);
        int a[] = {-1, -2, -3, -4, -5, -6, -7};
        int * b = reverse(a,7);
        for(int i=0; i<7; i++)
            ASSERT_EQ(b[i], a[7-1-i]);
          
        free(b);
    }
    
    TEST(HW2,NumInstances) {
        int a[] = { 1, 333, 8, 3, 333, 4, 7, 2, 333, 101, 101, 333  };
        ASSERT_EQ(num_instances(a,12, 8), 1);
        ASSERT_EQ(num_instances(a,12, 101), 2);
        ASSERT_EQ(num_instances(a,12, 333), 4);
        ASSERT_EQ(num_instances(a,12, 1010), 0);
        int b[] = {0, 7, 9, 6, 5, 9, 9, 6, 0, 0, 0, 5, 5};
        ASSERT_EQ(num_instances(b,13, 0), 4);
        ASSERT_EQ(num_instances(b,13, 9), 3);
        ASSERT_EQ(num_instances(b,13, 7), 1);
        ASSERT_EQ(num_instances(b,13, 6), 2);        
        ASSERT_EQ(num_instances(b,13, 5), 3);
    }
    
    TEST(HW2,ToSet) {
        int a[] = { -9, -9, 6, -2, -9, 4, 6, 2, 77, 5 };
        int n;
        int * b = to_set(a, 10, &n);
        ASSERT_EQ(n,7);
        ASSERT_EQ(num_instances(b,7, 1),0);
        ASSERT_EQ(num_instances(b,7, -9),1);
        ASSERT_EQ(num_instances(b,7, 77),1);  
        free(b);
        
        int x[] = { 0, 1000, 20, 0, 0, 0, 20, 1000};
        int m;
        int * y = to_set(x, 8, &m);
        ASSERT_EQ(m,3);
        ASSERT_EQ(num_instances(y,3, 0),1);
        ASSERT_EQ(num_instances(y,3, 20),1);
        ASSERT_EQ(num_instances(y,3, 1000),1);  
        ASSERT_EQ(num_instances(y,3, 10000),0); 
        free(y);

    }
    
    Point negate(Point p) {
        return { -p.x, -p.y, -p.z };
    }

    Point add1(Point p){
        return {p.x + 1, p.y + 1, p.z + 1};
    }
    Point square(Point p) {
        return { p.x*p.x, p.y*p.y, p.z*p.z };
    }

    TEST(HW2,PointMap) {
        Point a[] = { { 1,2,3 }, { 5,12,13 } };
        Point * b = map(a,2,square);
        for(int i=0; i<2; i++) {
            ASSERT_EQ(b[i].x, a[i].x*a[i].x);
            ASSERT_EQ(b[i].y, a[i].y*a[i].y);
            ASSERT_EQ(b[i].z, a[i].z*a[i].z);
        }
        free(b);

        Point * c = map(a,2,add1);
        for(int i=0; i<2; i++) {
            ASSERT_EQ(c[i].x, a[i].x + 1);
            ASSERT_EQ(c[i].y, a[i].y + 1);
            ASSERT_EQ(c[i].z, a[i].z + 1);
        }
    } 

    TEST(HW2, RPN_BASIC_INIT) {
        rpn_init();
        ASSERT_EQ(rpn_error(), OK);   
    }

    TEST(HW2, RPN_BASIC_POP_ERROR){
        rpn_init();
        rpn_pop();
        ASSERT_EQ(rpn_error(), POP_ERROR);   
    }

    TEST(HW2, RPN_REINIT) {
        rpn_init();
        rpn_push(555.0);
        rpn_init();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);
        ASSERT_EQ(rpn_error(), POP_ERROR);

        rpn_init();
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);
        ASSERT_EQ(rpn_error(), ADD_ERROR);

        rpn_init();
        rpn_multiply();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);
        ASSERT_EQ(rpn_error(), MULT_ERROR);

        rpn_init();
        rpn_negate();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);
        ASSERT_EQ(rpn_error(), NEGATE_ERROR);

        rpn_init();
        rpn_free();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);

    }

    TEST(HW2, RPN_BASIC_PUSH){
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);     
        ASSERT_DOUBLE_EQ(rpn_pop(), 2.0);
        rpn_push(4.0);
        ASSERT_DOUBLE_EQ(rpn_pop(), 4.0);
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.5);
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);

    }
    
    TEST(HW2, RPN_NEGATE){
        rpn_init();
        rpn_push(5.0);
        rpn_negate(); 
        ASSERT_DOUBLE_EQ(rpn_pop(),-5.0);    
        rpn_push(-18.1);
        rpn_negate(); 
        ASSERT_DOUBLE_EQ(rpn_pop(), 18.1);  

    }
    TEST(HW2, RPN_NEGATE_ERROR){
        rpn_init();
        rpn_negate(); 
        ASSERT_EQ(rpn_error(), NEGATE_ERROR); 
    }

    TEST(HW2, RPN_BASIC_ADD){
        rpn_init();
        rpn_push(1.0);
        rpn_push(0.5);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 1.5);
        rpn_push(1.5);
        rpn_push(-30);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), -28.5);
        rpn_push(-1.5);
        rpn_push(-30);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), -31.5);

    }

    TEST(HW2, RPN_BASIC_ADD_ERROR){
        rpn_init();
        rpn_add();
        ASSERT_EQ(rpn_error(), ADD_ERROR);

        rpn_init();
        rpn_push(1.3);
        rpn_add();
        ASSERT_EQ(rpn_error(), ADD_ERROR);

    }
    
    TEST(HW2, RPN_ADD_TWO_LARGE){
        rpn_init();
        rpn_push(0.9E+308);
        rpn_push(0.9E+308);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);

        rpn_init();
        rpn_push(-0.9E+308);
        rpn_push(-0.9E+308);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);

    }
    
    TEST(HW2, RPN_BASIC_MULTIPLY){
        rpn_init();
        rpn_push(25.0);
        rpn_push(0.5);
        rpn_multiply();
        ASSERT_DOUBLE_EQ(rpn_pop(), 12.5);
        rpn_push(20.0/3.0);
        rpn_push(-2.0);
        rpn_multiply();
        ASSERT_DOUBLE_EQ(rpn_pop(), -20.0*(2.0/3.0));
    }

    TEST(HW2, RPN_BASIC_MULTIPLY_ERROR){
        rpn_init();
        rpn_multiply();
        ASSERT_EQ(rpn_error(), MULT_ERROR);

        rpn_init();
        rpn_push(1.3);
        rpn_multiply();
        ASSERT_EQ(rpn_error(), MULT_ERROR);
    }

    TEST(HW2, RPN_MULTIPLY_TWO_LARGE){
        rpn_init();
        rpn_push(5E+154);
        rpn_push(-2E+155);
        rpn_multiply();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);

        rpn_init();
        rpn_push(0.9E+308);
        rpn_push(0.9E+308);
        rpn_multiply();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);

        rpn_init();
        rpn_push(-0.9E+308);
        rpn_push(-0.9E+308);
        rpn_multiply();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
    }

    TEST(HW2, RPN_NOT_INITIALIZED_ERROR)
    {
        rpn_init();
        rpn_free();
        rpn_push(1.0);
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);

        rpn_init();
        rpn_free();
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);

        rpn_init();
        rpn_free();
        rpn_multiply();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);

        rpn_init();
        rpn_free();
        rpn_negate();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);

        rpn_init();
        rpn_free();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);


    }
	
    TEST(HW2, RPN_REALLOC_PUSH){
        rpn_init();
        for(int i=0; i<1000; i++)
            rpn_push(1.0);
        rpn_push(101.1);
        ASSERT_DOUBLE_EQ(rpn_pop(), 101.1);
        ASSERT_EQ(rpn_error(), OK);
    }

    TEST(HW2, RPN_MULTIPLE_ERROR){
        
        rpn_init();
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);
        ASSERT_EQ(rpn_error(), ADD_ERROR);
        rpn_push(-0.9E+308);
        rpn_push(-0.9E+308);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), ADD_ERROR);

        rpn_init();
        rpn_push(-0.9E+308);
        rpn_push(-0.9E+308);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0.0);
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_add();
        ASSERT_DOUBLE_EQ(rpn_pop(), 0);
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);

        rpn_init();
        rpn_negate();
        ASSERT_EQ(rpn_error(), NEGATE_ERROR);
        ASSERT_DOUBLE_EQ(rpn_pop(),0);
        ASSERT_EQ(rpn_error(), NEGATE_ERROR);
    }
	
}

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "imaginary.h"
#include "typed_matrix.h"
#include "gtest/gtest.h"
//#include "GTestNoDeath.h"
#include <iostream>

//TestCases for TypedArray and Typed Matrix
namespace {
    class Point {
        public:
        Point(double x, double y, double z) : x(x), y(y), z(z) {};
        Point() : x(0), y(0), z(0) {};

        double magnitude(const Point &p) {
            return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
        }

        double x, y, z;
    };

    TEST(TypedArray, Push1) {
        TypedArray<int> a;
        a.push(21);
        a.push(13);
        EXPECT_EQ(a.safe_get(0), 21);
        EXPECT_EQ(a.safe_get(1), 13);
    }

    TEST(TypedArray, Push2) {
        TypedArray<int> a;
        a.push(1);
        a.push(3);
        a.push(5);
        a.push(7);
        a.push(9);
        EXPECT_EQ(a.safe_get(0), 1);
        EXPECT_EQ(a.safe_get(1), 3);
        EXPECT_EQ(a.safe_get(2), 5);
        EXPECT_EQ(a.safe_get(3), 7);
        EXPECT_EQ(a.safe_get(4), 9);
    }

    TEST(TypedArray, Push3) {
        TypedArray<double> a;
        a.push(3.34);
        a.push(9.78);
        a.push(6.45);
        a.push(8.88);
        a.push(0.12);
        EXPECT_DOUBLE_EQ(a.safe_get(0), 3.34);
        EXPECT_DOUBLE_EQ(a.safe_get(1), 9.78);
        EXPECT_DOUBLE_EQ(a.safe_get(2), 6.45);
        EXPECT_DOUBLE_EQ(a.safe_get(3), 8.88);
        EXPECT_DOUBLE_EQ(a.safe_get(4), 0.12);
    }

    TEST(TypedArray, Push4) {
        TypedArray<Point> a;
        a.push(Point(1.0, 2.0, 3.0));
        a.push(Point(4.0, 11.0, 6.0));
        a.push(Point(77.0, 8.0, 9.0));
        Point p = a.safe_get(1);
        EXPECT_DOUBLE_EQ(p.x, 4.0);
        EXPECT_DOUBLE_EQ(p.y, 11.0);
        EXPECT_DOUBLE_EQ(p.z, 6.0);
        Point q = a.safe_get(2);
        EXPECT_DOUBLE_EQ(q.x, 77.0);
        EXPECT_DOUBLE_EQ(q.y, 8.0);
        EXPECT_DOUBLE_EQ(q.z, 9.0);       
    }

    TEST(TypedArray, Push_front1) {
        TypedArray<int> a;
        a.push_front(21);
        a.push_front(13);
        EXPECT_EQ(a.safe_get(0), 13);
        EXPECT_EQ(a.safe_get(1), 21);
    }

    TEST(TypedArray, Push_front2){
        TypedArray<double> a;
        a.push_front(2.0);
        a.push_front(4.0);
        a.push_front(6.0);
        a.push_front(8.0);
        a.push_front(10.0);
        EXPECT_DOUBLE_EQ(a.safe_get(0), 10.0);
        EXPECT_DOUBLE_EQ(a.safe_get(1), 8.0);
        EXPECT_DOUBLE_EQ(a.safe_get(2), 6.0);
        EXPECT_DOUBLE_EQ(a.safe_get(3), 4.0);
        EXPECT_DOUBLE_EQ(a.safe_get(4), 2.0);
    }

    TEST(TypedArray, Push_front3){
        TypedArray<int> a;
        a.push_front(127);
        a.push_front(126);
        a.push_front(125);
        a.push_front(124);
        EXPECT_EQ(a.safe_get(0), 124);
        EXPECT_EQ(a.safe_get(1), 125);
        EXPECT_EQ(a.safe_get(2), 126);
        EXPECT_EQ(a.safe_get(3), 127);
    }

    TEST(TypedArray, Push_front4){
        TypedArray<Point> a;
        a.push_front(Point(33.0, 57.2, 14.7));
        a.push_front(Point(-75.3, 68.4, 21.9));
        a.push_front(Point(9.2, -47.4, -59.1));
        a.push_front(Point(-0.5, 1.12, 131.4));
        Point p = a.safe_get(0);
        EXPECT_DOUBLE_EQ(p.x, -0.5);
        EXPECT_DOUBLE_EQ(p.y, 1.12);
        EXPECT_DOUBLE_EQ(p.z, 131.4);
        Point q = a.safe_get(2);
        EXPECT_DOUBLE_EQ(q.x, -75.3);
        EXPECT_DOUBLE_EQ(q.y, 68.4);
        EXPECT_DOUBLE_EQ(q.z, 21.9);
    }

    TEST(TypedArray, Pop1){
        TypedArray<double> a;
        a.push(2.0);
        a.push(4.0);
        a.push(6.0);
        EXPECT_DOUBLE_EQ(a.safe_get(2), 6.0);
        a.pop();
        a.push(12.0);
        EXPECT_DOUBLE_EQ(a.safe_get(2), 12.0);   
    }

    TEST(TypedArray, Pop2){
        TypedArray<int> a;
        a.push(58);
        a.push(69);
        a.pop();
        a.push(23);
        EXPECT_EQ(a.safe_get(1), 23);
        a.push(26);
        a.pop();
        EXPECT_EQ(a.safe_get(1), 23);   
    }

    TEST(TypedArray, Pop3){
        TypedArray<Point> a;
        a.push(Point(6.2, 0.4, 3.7));
        a.push(Point(9.1, -6.7, -8.8));
        a.pop();
        a.push(Point(-66.3, 87.8, -0.13));
        Point p = a.safe_get(1);
        EXPECT_DOUBLE_EQ(p.x, -66.3); 
        EXPECT_DOUBLE_EQ(p.y, 87.8); 
        EXPECT_DOUBLE_EQ(p.z, -0.13); 
    }

    TEST(TypedArray, Pop4){
        TypedArray<double> a;
        a.push(2.0);
        a.push(4.0);
        a.pop();
        a.push_front(6.0);
        EXPECT_DOUBLE_EQ(a.safe_get(1), 2.0);
        EXPECT_DOUBLE_EQ(a.safe_get(0), 6.0);   
    }

    TEST(TypedArray, Pop_front1){
        TypedArray<int> a;
        a.push_front(7);
        a.push_front(5);
        EXPECT_EQ(a.safe_get(0), 5);
        a.pop_front();
        a.push_front(11);
        EXPECT_EQ(a.safe_get(0), 11);   
    }

    TEST(TypedArray, Pop_front2){
        TypedArray<double> a;
        a.push(-0.16);
        a.push(8.7);
        a.push(14.1);
        a.pop_front();
        EXPECT_DOUBLE_EQ(a.safe_get(0), 8.7);   
        a.pop_front();
        EXPECT_DOUBLE_EQ(a.safe_get(0), 14.1);   
    }

    TEST(TypedArray, Pop_front3){
        TypedArray<Point> a;
        a.push(Point(0.0, 2.1, 9.3));
        a.push(Point(-38.1, 6.6, -0.18));
        a.push(Point(9.5, 4.7, 0.86));
        a.pop_front();
        Point p = a.safe_get(0);
        EXPECT_DOUBLE_EQ(p.x, -38.1);   
        EXPECT_DOUBLE_EQ(p.y, 6.6);   
        EXPECT_DOUBLE_EQ(p.z, -0.18);  
        a.pop_front(); 
        p = a.safe_get(0);
        EXPECT_DOUBLE_EQ(p.x, 9.5);   
        EXPECT_DOUBLE_EQ(p.y, 4.7);   
        EXPECT_DOUBLE_EQ(p.z, 0.86);   
    }

    TEST(TypedArray, Pop_front4){
        TypedArray<int> a;
        a.push_front(7);
        a.push_front(5);
        a.pop_front();
        a.push(11);
        EXPECT_EQ(a.safe_get(0), 7);
        EXPECT_EQ(a.safe_get(1), 11);   
    }

    TEST(TypedArray, Concat1){
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b;
        b.set(0,2);
        b.set(1,3);
        TypedArray<int> c = a.concat(b);
        EXPECT_EQ(c.safe_get(0), 0);
        EXPECT_EQ(c.safe_get(1), 1);  
        EXPECT_EQ(c.safe_get(2), 2);  
        EXPECT_EQ(c.safe_get(3), 3);   
    }

    TEST(TypedArray, Concat2){
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b;
        b.set(0,22);
        b.set(1,11);
        TypedArray<int> c = a.concat(b).concat(a); // yields [0,1,22,11,0,1]
        EXPECT_EQ(c.safe_get(0), 0);
        EXPECT_EQ(c.safe_get(1), 1);  
        EXPECT_EQ(c.safe_get(2), 22);  
        EXPECT_EQ(c.safe_get(3), 11); 
        EXPECT_EQ(c.safe_get(4), 0);
        EXPECT_EQ(c.safe_get(5), 1);    
    }

    TEST(TypedArray, Concat3){
        TypedArray<double> a;
        a.set(0, 9.9);
        a.set(1, 4.5);
        TypedArray<double> b;
        b.set(0, 12.1);
        b.set(1, 0.5);
        TypedArray<double> c = b.concat(a).concat(b); // yields [0,1,22,11,0,1]
        EXPECT_EQ(c.safe_get(0), 12.1);
        EXPECT_EQ(c.safe_get(1), 0.5);  
        EXPECT_EQ(c.safe_get(2), 9.9);  
        EXPECT_EQ(c.safe_get(3), 4.5); 
        EXPECT_EQ(c.safe_get(4), 12.1);
        EXPECT_EQ(c.safe_get(5), 0.5);    
    }

    TEST(TypedArray, Concat4){
        TypedArray<Point> a;
        a.set(0, Point(3.0, 4.0, 5.0));
        a.set(1, Point(7.0, 24.0, 25.0));
        TypedArray<Point> b;
        b.set(0, Point(-1.0, -1.0, -2.2));
        b.set(1, Point(1.6, 0.8, 0.4));
        TypedArray<Point> c = a.concat(b).concat(b); // yields [0,1,22,11,0,1]
        Point p = c.get(0);
        Point q = c.get(2);
        Point r = c.get(5);
        EXPECT_DOUBLE_EQ(p.x, 3.0);  
        EXPECT_DOUBLE_EQ(p.y, 4.0);  
        EXPECT_DOUBLE_EQ(p.z, 5.0);  
        EXPECT_DOUBLE_EQ(q.x, -1.0);  
        EXPECT_DOUBLE_EQ(q.y, -1.0);  
        EXPECT_DOUBLE_EQ(q.z, -2.2);  
        EXPECT_DOUBLE_EQ(r.x, 1.6);  
        EXPECT_DOUBLE_EQ(r.y, 0.8);  
        EXPECT_DOUBLE_EQ(r.z, 0.4);  
    }

    TEST(TypedArray2, Pop1){
        TypedArray<double> a;
        EXPECT_ANY_THROW(a.pop());
    }

    TEST(TypedArray2, Pop_front1){
        TypedArray<double> a;
        EXPECT_ANY_THROW(a.pop_front());
    }

    TEST(TypedArray2, Concat1){
        TypedArray<int> a;
        TypedArray<int> b;
        b.set(0,2);
        b.set(1,3);
        TypedArray<int> c = a.concat(b);
        EXPECT_EQ(c.safe_get(0), 2);
        EXPECT_EQ(c.safe_get(1), 3);  
        EXPECT_EQ(b.safe_get(0), 2);  
        EXPECT_EQ(b.safe_get(1), 3);   
    }

    TEST(TypedArray2, Concat2){
        TypedArray<int> a;
        TypedArray<int> b;
        b.set(0,2);
        b.set(1,3);
        TypedArray<int> c = b.concat(a);
        EXPECT_EQ(c.safe_get(0), 2);
        EXPECT_EQ(c.safe_get(1), 3);  
        EXPECT_EQ(b.safe_get(0), 2);  
        EXPECT_EQ(b.safe_get(1), 3);   
    }

    TEST(TypedArray2, Complex){
        TypedArray<int> a;
        TypedArray<int> b;
        b.set(0,2);
        b.set(1,3);
        TypedArray<int> c = b.concat(a);
        c.pop();
        c.push(7);
        c.pop_front();
        c.push_front(9);
        EXPECT_EQ(c.safe_get(0), 9);
        EXPECT_EQ(c.safe_get(1), 7);  
        EXPECT_EQ(b.safe_get(0), 2);  
        EXPECT_EQ(b.safe_get(1), 3);   
    }


    TEST(Imaginary, Basic1){
        Imaginary a(3.0, 4.0);
        EXPECT_DOUBLE_EQ(a.im(), 4.0);
        EXPECT_DOUBLE_EQ(a.re(), 3.0);
    } 

    TEST(Imaginary, Basic2){
        Imaginary a(5.4, -8.1);
        EXPECT_DOUBLE_EQ(a.im(), -8.1);
        EXPECT_DOUBLE_EQ(a.re(), 5.4);
    } 

    TEST(Imaginary, Basic3){
        Imaginary a(-1.9, -6.5);
        EXPECT_DOUBLE_EQ(a.im(), -6.5);
        EXPECT_DOUBLE_EQ(a.re(), -1.9);
    } 

    TEST(Imaginary, Conjugate1){
        Imaginary a(3.0, 4.0);
        Imaginary b = a.conjugate();
        EXPECT_DOUBLE_EQ(b.im(), -4.0);
        EXPECT_DOUBLE_EQ(b.re(), 3.0);
    } 

    TEST(Imaginary, Conjugate2){
        Imaginary a(6.3, -9.2);
        Imaginary b = a.conjugate();
        EXPECT_DOUBLE_EQ(b.im(), 9.2);
        EXPECT_DOUBLE_EQ(b.re(), 6.3);
    } 

    TEST(Imaginary, Conjugate3){
        Imaginary a(5.0, 0.0);
        Imaginary b = a.conjugate();
        EXPECT_DOUBLE_EQ(b.im(), 0.0);
        EXPECT_DOUBLE_EQ(b.re(), 5.0);
    } 

    TEST(Imaginary, Magnitude1){
        Imaginary a(7.7, -0.18);
        double ans = sqrt(7.7*7.7 + -0.18*(-0.18));
        EXPECT_DOUBLE_EQ(a.magnitude(), ans);
    }

    TEST(Imaginary, Magnitude2){
        Imaginary a(-1.2, -3.7);
        double ans = sqrt(-1.2*(-1.2) + (-3.7)*(-3.7));
        EXPECT_DOUBLE_EQ(a.magnitude(), ans);
    }

    TEST(Imaginary, Magnitude3){
        Imaginary a(3.9, -1.4);
        double ans = sqrt(3.9*(3.9) + (-1.4)*(-1.4));
        EXPECT_DOUBLE_EQ(a.magnitude(), ans);
    }

    TEST(Imaginary, Add_assign1){
        Imaginary a(3.0, 4.0);
        Imaginary b(1.0, -1.0);
        a+=b;
        EXPECT_DOUBLE_EQ(a.im(), 3.0);
        EXPECT_DOUBLE_EQ(a.re(), 4.0);
        EXPECT_DOUBLE_EQ(b.im(), -1.0);
        EXPECT_DOUBLE_EQ(b.re(), 1.0);
    }

    TEST(Imaginary, Add_assign2){
        Imaginary a(8.7, -6.1);
        Imaginary b(17.5, 3.4);
        double im_ans = -6.1+3.4;
        double re_ans = 8.7+17.5;
        a+=b;
        EXPECT_DOUBLE_EQ(a.im(), im_ans);
        EXPECT_DOUBLE_EQ(a.re(), re_ans);
        EXPECT_DOUBLE_EQ(b.im(), 3.4);
        EXPECT_DOUBLE_EQ(b.re(), 17.5);
    }

    TEST(Imaginary, Add_assign3){
        Imaginary a(0.0, -1.0);
        Imaginary b(22.0, 0.0);
        a+=b;
        EXPECT_DOUBLE_EQ(a.im(), -1.0);
        EXPECT_DOUBLE_EQ(a.re(), 22.0);
    }

    TEST(Imaginary, Mult_assign){
        Imaginary a(1.0, 2.0);
        Imaginary b(3.0, -1.0);
        a*=b;
        EXPECT_DOUBLE_EQ(a.im(), 5.0);
        EXPECT_DOUBLE_EQ(a.re(), 5.0);
        EXPECT_DOUBLE_EQ(b.im(), -1.0);
        EXPECT_DOUBLE_EQ(b.re(), 3.0);        
    }

    TEST(Imaginary, Mult_assign2){
        Imaginary a(3.6, 7.2);
        Imaginary b(-1.5, -45.0);
        double im_ans = 3.6*(-45.0) + 7.2*(-1.5);
        double re_ans = 3.6*(-1.5) - (7.2*(-45.0));
        a*=b;
        EXPECT_DOUBLE_EQ(a.im(), im_ans);
        EXPECT_DOUBLE_EQ(a.re(), re_ans);
        EXPECT_DOUBLE_EQ(b.im(), -45.0);
        EXPECT_DOUBLE_EQ(b.re(), -1.5);        
    }

    TEST(Imaginary, Mult_assign3){
        Imaginary a(5.0, 1.0);
        Imaginary b(-3.0, 0.0);
        a*=b;
        EXPECT_DOUBLE_EQ(a.im(), -3.0);
        EXPECT_DOUBLE_EQ(a.re(), -15.0);
        EXPECT_DOUBLE_EQ(b.im(), 0.0);
        EXPECT_DOUBLE_EQ(b.re(), -3.0);        
    }


    TEST(Imaginary, Equalilty1){
        Imaginary a(1.0, 2.0);
        Imaginary b(3.0, -1.0);
        EXPECT_TRUE(a==Imaginary(1.0, 2.0));
        EXPECT_FALSE(a==b);
    }

    TEST(Imaginary, Equalilty2){
        Imaginary a(0.16, 3.998);
        Imaginary b(5.2, 6.0);
        EXPECT_TRUE(b==Imaginary(5.2, 6.0));
        EXPECT_FALSE(a==b);
    }

    TEST(Imaginary, Equalilty3){
        Imaginary a(0.0, 5.0);
        Imaginary b(2.3, 6.7);
        EXPECT_TRUE(b==Imaginary(2.3, 6.7));
        EXPECT_FALSE(a==b);
    }

    TEST(Imaginary, Add1){
        Imaginary a(4.0, 3.0);
        Imaginary b(3.0, 11.0);
        Imaginary c = a + b;
        EXPECT_DOUBLE_EQ(c.im(), 14.0);
        EXPECT_DOUBLE_EQ(c.re(), 7.0);
    }

    TEST(Imaginary, Add2){
        Imaginary a(0.0, -1.0);
        Imaginary b(22, 0.0);
        Imaginary c = a + b;
        EXPECT_DOUBLE_EQ(c.im(), -1.0);
        EXPECT_DOUBLE_EQ(c.re(), 22.0);
        EXPECT_DOUBLE_EQ(a.im(), -1.0);
        EXPECT_DOUBLE_EQ(a.re(), 0.0);
    }

    TEST(Imaginary, Add3){
        Imaginary a(-0.9, 2.3);
        Imaginary b(6.7, 8.1);
        Imaginary c = a + b;
        double im_ans = 2.3 + 8.1;
        double re_ans = -0.9 + 6.7;
        EXPECT_DOUBLE_EQ(c.im(), im_ans);
        EXPECT_DOUBLE_EQ(c.re(), re_ans);
        EXPECT_DOUBLE_EQ(a.im(), 2.3);
        EXPECT_DOUBLE_EQ(a.re(), -0.9);
        EXPECT_DOUBLE_EQ(b.im(), 8.1);
        EXPECT_DOUBLE_EQ(b.re(), 6.7);
    }

    TEST(Imaginary, Mult1){
        Imaginary a(4.0, 3.0);
        Imaginary b(3.0, 11.0);
        Imaginary c = a * b;
        EXPECT_DOUBLE_EQ(c.im(), 53.0);
        EXPECT_DOUBLE_EQ(c.re(), -21.0);
    }

    TEST(Imaginary, Mult2){
        Imaginary a(5.0, 1.0);
        Imaginary b(-3.0, 0.0);
        Imaginary c = a * b;
        EXPECT_DOUBLE_EQ(c.im(), -3.0);
        EXPECT_DOUBLE_EQ(c.re(), -15.0);
        EXPECT_DOUBLE_EQ(a.im(), 1.0);
        EXPECT_DOUBLE_EQ(a.re(), 5.0);        
    }

    TEST(Imaginary, Mult3){
        Imaginary a(5.5, 7.7);
        Imaginary b(0.2, 0.1);
        Imaginary c = a * b;
        double im_ans = 5.5*0.1+7.7*0.2;
        double re_ans = 5.5*0.2 -(7.7*0.1);
        EXPECT_DOUBLE_EQ(c.im(), im_ans);
        EXPECT_DOUBLE_EQ(c.re(), re_ans);
        EXPECT_DOUBLE_EQ(a.im(), 7.7);
        EXPECT_DOUBLE_EQ(a.re(), 5.5);
        EXPECT_DOUBLE_EQ(b.im(), 0.1);
        EXPECT_DOUBLE_EQ(b.re(), 0.2);       
    }

    TEST(Imaginary, Complex){
        Imaginary a(2.0, 3.0);
        a*=Imaginary(2.0, -1.0);
        Imaginary b = a + Imaginary(-1.0, -1.0); // 6,3
        b*=Imaginary(-2.0, 2.0); // -18 6
        Imaginary c = b * Imaginary(0.5, 0);
        EXPECT_DOUBLE_EQ(a.im(), 4.0);
        EXPECT_DOUBLE_EQ(a.re(), 7.0);
        EXPECT_DOUBLE_EQ(b.im(), 6.0);
        EXPECT_DOUBLE_EQ(b.re(), -18.0);
        EXPECT_DOUBLE_EQ(c.im(), 3.0);
        EXPECT_DOUBLE_EQ(c.re(), -9.0);           
        
    }




    TEST(TypedMatrix, Constuctor1){
        TypedMatrix<int> a;
        EXPECT_EQ(a.get(0,0), int());
    }

    TEST(TypedMatrix, Constuctor2){
        TypedMatrix<int> a(2,2);
        EXPECT_EQ(a.get(1,1), int());
    }

    TEST(TypedMatrix, Set_Get1){
        TypedMatrix<int> a(3,3);
        a.set(1, 1, 6);
        EXPECT_EQ(a.get(1,1), 6);
    }

    TEST(TypedMatrix, Set_Get2){
        TypedMatrix<int> a(3,5);
        EXPECT_EQ(a.get(4,2), int());
        //EXPECT_ANY_THROW(a.get(5,3));
        a.set(4, 2, 110 );
        EXPECT_EQ(a.get(4,2), 110);
    }

    TEST(TypedMatrix, Copy1){
        TypedMatrix<int> a(2,3);
        TypedMatrix<int> b;
        b = a;
        b.set(1,1,555);
        EXPECT_EQ(b.get(1,1), 555);
        EXPECT_EQ(a.get(1,1), int());
    }

    TEST(TypedMatrix, Copy2){
        TypedMatrix<int> a(5,6);
        TypedMatrix<int> b,c;
        b = a;
        b.set(3,2,11);
        c = b;
        c.set(3,2, 23);
        EXPECT_EQ(a.get(3,2), int());
        EXPECT_EQ(b.get(3,2), 11);
        //EXPECT_EQ(c.get(3,2), 23);
    }

    TEST(TypedMatrix, Add_assign1){
        TypedMatrix<int> a(2, 1);
        TypedMatrix<int> b(2, 1);
        a.set(0, 0, 2);
        a.set(0, 1, 3);
        b.set(0, 0, -2);
        b.set(0, 1, -3);
        a+=b;
        EXPECT_EQ(a.get(0,0), 0);
        EXPECT_EQ(a.get(0,1), 0);
        EXPECT_EQ(b.get(0,0), -2);
        EXPECT_EQ(b.get(0,1), -3);
    }

    TEST(TypedMatrix, Add_assign2){
        TypedMatrix<int> a(1, 3);
        TypedMatrix<int> b(1, 3);
        a.set(0, 0, 1);
        a.set(1, 0, 2);
        a.set(2, 0, 3);
        b.set(0, 0, 5);
        b.set(1, 0, 5);
        b.set(2, 0, 5);
        a+=b;
        EXPECT_EQ(a.get(0,0), 6);
        EXPECT_EQ(a.get(1,0), 7);
        EXPECT_EQ(a.get(2,0), 8);
    }

    TEST(TypedMatrix, Mult_assign1){
        TypedMatrix<int> a(2,3);
        TypedMatrix<int> b(2,3);
        for(int i=0; i<3; i++){
            for(int j=0; j<2; j++){
                a.set(i,j,i*2+j);
                b.set(i,j,2);
            }
        }
        a*=b;
        for(int i=0; i<3; i++){
            for(int j=0; j<2; j++){
                EXPECT_EQ(a.get(i,j),2*(i*2+j));
            }
        }
        //TypedMatrix<int> c(2,4);
        //EXPECT_ANY_THROW(a*=c);
    }

    TEST(TypedMatrix, Mult_assign2){
        TypedMatrix<int> a(2,2);
        TypedMatrix<int> b(2,2);
        a.set(0, 0, 4);
        a.set(0, 1, 3);
        a.set(1, 0, 2);
        a.set(1, 1, 1);
        b.set(0, 0, 6);
        b.set(0, 1, 7);
        b.set(1, 0, 8);
        b.set(1, 1, 9);
        a*=b;
        EXPECT_EQ(a.get(0,0), 24);
        EXPECT_EQ(a.get(0,1), 21);
        EXPECT_EQ(a.get(1,0), 16);
        EXPECT_EQ(a.get(1,1), 9);
    }

    TEST(TypedMatrix, Equality1){
        TypedMatrix<int> a(2, 1);
        TypedMatrix<int> b(2, 1);
        TypedMatrix<int> c(2, 2);
        a.set(0, 0, 33);
        a.set(0, 1, 22);
        b.set(0, 0, 33);
        b.set(0, 1, 22);    
        EXPECT_TRUE(a==b);
        EXPECT_FALSE(a==c);
    }

    TEST(TypedMatrix, Equality2){
        TypedMatrix<int> a(1, 3);
        TypedMatrix<int> b(1, 3);
        TypedMatrix<int> c(1, 3);
        a.set(0, 0, 121);
        a.set(1, 0, 65);
        a.set(2, 0, 78);
        b.set(0, 0, 121);
        b.set(1, 0, 65);
        b.set(2, 0, 78);    
        c.set(0, 0, 121);
        c.set(1, 0, 65);
        c.set(2, 0, -78); 
        EXPECT_TRUE(a==b);
        EXPECT_FALSE(a==c);
    }

    TEST(TypedMatrix, Add1){
        TypedMatrix<int> a(2, 2);
        TypedMatrix<int> b(2, 2); 
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                a.set(i,j,i*2+j+1);
                b.set(i,j,4-(i*2+j+1));
            }
        }     
        TypedMatrix<int> c;
        c = a+b; 
        EXPECT_EQ(c.get(0,0), 4);
        EXPECT_EQ(c.get(0,1), 4);
        EXPECT_EQ(c.get(1,0), 4);
        EXPECT_EQ(c.get(1,1), 4);
        //TypedMatrix<int> d(3,2);
        //EXPECT_ANY_THROW(c=a+d);
    }

    TEST(TypedMatrix, Add2){
        TypedMatrix<int> a(1, 3);
        TypedMatrix<int> b(1, 3);
        a.set(0, 0, 1);
        a.set(1, 0, 2);
        a.set(2, 0, 3);
        b.set(0, 0, 5);
        b.set(1, 0, 5);
        b.set(2, 0, 5);
        TypedMatrix<int> c;

        c = a+b;
        EXPECT_EQ(c.get(0,0), 6);
        EXPECT_EQ(c.get(1,0), 7);
        EXPECT_EQ(c.get(2,0), 8);
        EXPECT_EQ(a.get(0,0), 1);
        EXPECT_EQ(a.get(1,0), 2);
        EXPECT_EQ(a.get(2,0), 3);
    }

    TEST(TypedMatrix, Add3){
        TypedMatrix<int> a(3, 4);
        TypedMatrix<int> b(3, 4);
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
                a.set(i, j, i*5+j+2);
            }
        }

        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
                b.set(i, j, i*3+j-8);
            }
        }
        TypedMatrix<int> c;
        c = a+b; 
        int ans[4][3];
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
                ans[i][j] = (i*5+j+2)+(i*3+j-8);
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
                EXPECT_EQ(c.get(i,j), ans[i][j]);
            }
        }
    }

    TEST(TypedMatrix, Mult1){
        TypedMatrix<int> a(2, 1);
        TypedMatrix<int> b(1, 2);
        a.set(0, 0, 3.0);
        a.set(0, 1, 4.0);
        b.set(0, 0, 3.0);
        b.set(1, 0, 4.0); 
        TypedMatrix<int> c;
        c = a*b; 
        //std::cout<<c<<std::endl;
        EXPECT_DOUBLE_EQ(c.get(0,0), 25.0);
        //EXPECT_ANY_THROW(c.get(0,1));
        //TypedMatrix<int> d(1,3);
        //EXPECT_ANY_THROW(a*d);
    }

    TEST(TypedMatrix, Mult2){
        TypedMatrix<int> a(3, 4);
        TypedMatrix<int> b(4, 3);
        for(int i=0; i<4; i++){
            for(int j=0; j<3; j++){
                a.set(i, j, i*5+j+2);
            }
        }

        for(int i=0; i<3; i++){
            for(int j=0; j<4; j++){
                b.set(i, j, i*3+j-8);
            }
        }
        TypedMatrix<int> c;
        c = a*b; 
        int ans[4][4];
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                ans[i][j] = 0;
                for(int k=0; k<3; k++){
                    ans[i][j] += (i*5+k+2)*(k*3+j-8);
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                EXPECT_EQ(c.get(i,j), ans[i][j]);
            }
        }
    }

    TEST(TypedMatrix, Mult3){
        TypedMatrix<int> a(5, 7);
        TypedMatrix<int> b(7, 5);
        for(int i=0; i<7; i++){
            for(int j=0; j<5; j++){
                a.set(i, j, (i+3)*2-j+9 );
            }
        }

        for(int i=0; i<5; i++){
            for(int j=0; j<7; j++){
                b.set(i, j, (i+5)+j*4 );
            }
        }
        TypedMatrix<int> c;
        c = a*b; 
        int ans[7][7];
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                ans[i][j] = 0;
                for(int k=0; k<5; k++){
                    ans[i][j] += ((i+3)*2-k+9) *((k+5)+j*4);
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                EXPECT_EQ(c.get(i,j), ans[i][j]);
            }
        }
    }

    TEST(TypedMatrix2, Add_assign){
        TypedMatrix<int> a(3, 3);
        TypedMatrix<int> b(3, 4);      
        EXPECT_ANY_THROW(a+=b);
    }

    TEST(TypedMatrix2, Mult_assign){
        TypedMatrix<int> a(3, 3);
        TypedMatrix<int> b(3, 4);      
        EXPECT_ANY_THROW(a*=b);
    }

    TEST(TypedMatrix2, Add){
        TypedMatrix<int> a(3, 3);
        TypedMatrix<int> b(3, 4);
        TypedMatrix<int> c;        
        EXPECT_ANY_THROW(c=a+b);
    }

    TEST(TypedMatrix2, Mult){
        TypedMatrix<int> a(3, 4);
        TypedMatrix<int> b(3, 4);
        TypedMatrix<int> c;        
        EXPECT_ANY_THROW(c=a*b);
    }

    TEST(TypedMatrix, Copy){
        TypedMatrix<int> a(3,2);
        TypedMatrix<int> b,c;
        b = a;
        b.set(1,1,11);
        c = b;
        c.set(1,1, 22);
        a = c;
        EXPECT_EQ(a.get(1,1), 22);
        EXPECT_EQ(b.get(1,1), 11);
        EXPECT_EQ(c.get(1,1), 22);
    }

    TEST(TypedMatrix2, Mult2){
        TypedMatrix<Imaginary> a(2, 1);
        TypedMatrix<Imaginary> b(1, 2);
        a.set(0, 0, Imaginary(2.0, 1.0));
        a.set(0, 1, Imaginary(1.0,-1.0));
        b.set(0, 0, Imaginary(2.0, -1.0 ));
        b.set(1, 0, Imaginary(1.0, 0.0)); 
        TypedMatrix<Imaginary> c;
        c = a*b; 
        EXPECT_TRUE(c.get(0,0)==Imaginary(6, -1));
        EXPECT_ANY_THROW(c.get(0,1));
        TypedMatrix<Imaginary> d(1,3);
        EXPECT_ANY_THROW(a*d);
    }

    TEST(TypedMatrix2, Add_assign2){
        TypedMatrix<Imaginary> a(2, 1);
        TypedMatrix<Imaginary> b(2, 1);
        
        a.set(0, 0, Imaginary(2.0, -3.0));
        a.set(0, 1, Imaginary(1.0, 5.0));
        b.set(0, 0, Imaginary(-2.0, 3.0));
        b.set(0, 1, Imaginary(4.0, 0.0));
        a+=b;
        EXPECT_EQ(a.get(0,0), Imaginary(0.0, 0.0));
        EXPECT_EQ(a.get(0,1), Imaginary(5.0, 5.0));
        EXPECT_EQ(b.get(0,0), Imaginary(-2.0, 3.0));
        EXPECT_EQ(b.get(0,1), Imaginary(4.0, 0.0));
        TypedMatrix<Imaginary> c(2,4);
        EXPECT_ANY_THROW(a+=c); 
    }
}
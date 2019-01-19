#include "fraction.h"
#include "imaginary.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, Basics) {
        Fraction a = (Fraction) { 2, 3 },
                 b = (Fraction) { 4, 5 };
        EXPECT_EQ(add(a,b).num,22);
        EXPECT_EQ(add(a,b).den,15);
        EXPECT_EQ(multiply(a,b).num,8);
        EXPECT_EQ(multiply(a,b).den,15);
    }
    TEST(FractionsReduce1, Basics) {
        Fraction c = (Fraction) { 2, 4 },
                 d = (Fraction) { 3, 39 },
                 h = (Fraction) { 25, 30 };
        EXPECT_EQ(reduce(c).num,1);
        EXPECT_EQ(reduce(c).den,2);
        EXPECT_EQ(reduce(d).num,1);
        EXPECT_EQ(reduce(d).den,13);
        EXPECT_EQ(reduce(h).num,5);
        EXPECT_EQ(reduce(h).den,6);
    }
    
    TEST(FractionsReduce2, Negative) {
        Fraction a = reduce((Fraction) { 2, -4 }),
                 b = reduce((Fraction){-8,92}),
                 c = reduce((Fraction){-66,-21});
        EXPECT_TRUE((a.num == 1 && a.den == -2) || (a.num == -1 && a.den == 2));
        EXPECT_TRUE((b.num == 2 && b.den == -23)||(b.num == -2 && b.den == 23));
        EXPECT_TRUE(c.num == 22 && c.den == 7);
    }
    
    TEST(FractionReduce3, Zero) {
        Fraction a = reduce((Fraction) { -2, 0 }),
                 b = reduce((Fraction){0,-8}),
                 c = reduce ((Fraction){0,0});
        EXPECT_EQ(a.num, 1);
        EXPECT_EQ(a.den, 0);
        EXPECT_EQ(b.num,0);
        EXPECT_EQ(b.den,1);
        EXPECT_EQ(c.num,0);
        EXPECT_EQ(c.den,0);
    }

    TEST(FractionReduce4,Improper) {
        Fraction a = reduce((Fraction){153,81});
        EXPECT_EQ(a.num,17);
        EXPECT_EQ(a.den,9);
    }

    TEST(ImaginaryNum,Basic){
        Imaginary a = (Imaginary){2.3, 8.9},
                  b = (Imaginary){-92.3, -88.9},
                  c = (Imaginary){-72.38675, -58.12549},
                  d = (Imaginary){-82.3, 38.9},
                  e = (Imaginary){12.3, -68.9};
        EXPECT_EQ(a.real,2.3);
        EXPECT_EQ(a.im,8.9);
        EXPECT_EQ(b.real,-92.3);
        EXPECT_EQ(b.im,-88.9);
        EXPECT_EQ(c.real,-72.38675);
        EXPECT_EQ(c.im,-58.12549);
        EXPECT_EQ(d.real,-82.3);
        EXPECT_EQ(d.im,38.9);
        EXPECT_EQ(e.real,12.3);
        EXPECT_EQ(e.im,-68.9);
    }
    
    TEST(ImaginaryNum1,Add){
        Imaginary a = (Imaginary){4.67,2.34},
                  b = (Imaginary){-6.78,0.034},
                  c = (Imaginary){7.2345,-8.456},
                  d = (Imaginary){6.78,-0.034};
        EXPECT_EQ(add(a,a).real,9.34);
        EXPECT_EQ(add(a,a).im,4.68);
        EXPECT_NEAR(add(a,b).real,-2.11,0.000001);
        EXPECT_NEAR(add(a,b).im,2.374,0.0000001);
        EXPECT_NEAR(add(a,c).real,11.9045,0.000001);
        EXPECT_EQ(add(a,c).im,-6.116);
        EXPECT_EQ(add(b,c).real, add(c,b).real);
        EXPECT_EQ(add(b,c).im, add(c,b).im);
        EXPECT_EQ(add(b,d).real,0.0);
        EXPECT_EQ(add(b,d).im,0);
    }
    
    TEST(ImaginaryNum2,Multiply){
        Imaginary a = (Imaginary){4.67,2.34},
                  b = (Imaginary){-6.78,-0.034},
                  c = (Imaginary){7.2345,-8.456};
        EXPECT_NEAR(multiply(a,a).real,21.8089,0.00001);
        EXPECT_NEAR(multiply(a,a).im,5.4756,0.00001);
        EXPECT_NEAR(multiply(a,b).real,-31.6626,0.00001);
        EXPECT_NEAR(multiply(a,b).im,-0.07956,0.00001);
        EXPECT_NEAR(multiply(a,c).real,33.785115,0.00001);
        EXPECT_NEAR(multiply(a,c).im,-19.78704,0.00001);
        EXPECT_NEAR(multiply(b,b).real,45.9684,0.00001);
        EXPECT_NEAR(multiply(b,b).im,0.001156,0.00001);
    }

    
    TEST(ImaginaryNum3,Negate){
        Imaginary a = (Imaginary){4.67,2.34},
                  b = (Imaginary){-6.78,-0.034},
                  c = (Imaginary){7.2345,-8.456},
                  d = (Imaginary){-8.786,-5.987};
        
        EXPECT_EQ(negate(a).real,-4.67);
        EXPECT_EQ(negate(a).im,-2.34);
        EXPECT_EQ(negate(b).real,6.78);
        EXPECT_EQ(negate(b).im,0.034);
        EXPECT_EQ(negate(c).real,-7.2345);
        EXPECT_EQ(negate(c).im,8.456);
        EXPECT_EQ(negate(d).real,8.786);
        EXPECT_EQ(negate(d).im,5.987);
    }
    
    TEST(ImaginaryNum4,Conjugate){
        Imaginary a = (Imaginary){4.67,2.34},
                  b = (Imaginary){-6.78,-0.034},
                  c = (Imaginary){7.2345,-8.456},
                  d = (Imaginary){-8.786,-5.987};
        EXPECT_EQ(conjugate(a).real,4.67);
        EXPECT_EQ(conjugate(a).im,-2.34);
        EXPECT_EQ(conjugate(b).real,-6.78);
        EXPECT_EQ(conjugate(b).im,0.034);
        EXPECT_EQ(conjugate(c).real,7.2345);
        EXPECT_EQ(conjugate(c).im,8.456);
        EXPECT_EQ(conjugate(d).real,-8.786);
        EXPECT_EQ(conjugate(d).im,5.987);
    }
    TEST(ImaginaryNum5,Magnitude){
        Imaginary a = (Imaginary){4.67,2.34},
                  b = (Imaginary){-6.78,-0.034},
                  c = (Imaginary){7.2345,0},
                  d = (Imaginary){0,-5.987},
                  e = (Imaginary){1,4};
        EXPECT_NEAR(magnitude(a),5.22345,0.0001);
        EXPECT_NEAR(magnitude(b),6.78008,0.0001);
        EXPECT_NEAR(magnitude(c),7.2345,0.0001);
        EXPECT_NEAR(magnitude(d),5.987,0.0001);
        EXPECT_NEAR(magnitude(e),4.1231,0.0001);
    }
    
}

#include "fraction.h"
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
    TEST(FractionsReduce, Basics) {
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
    TEST(FractionsReduce, Negative) {
        Fraction a = reduce((Fraction) { 2, -4 });
        EXPECT_TRUE((a.num == 1 && a.den == -2) || (a.num == -1 && a.den == 2));
    }

    TEST(GradingReduce, Zero) {
        Fraction a = reduce((Fraction) { -2, 0 });
        EXPECT_EQ(a.num, 1);EXPECT_EQ(a.den, 0);
    }

}

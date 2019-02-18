#include "gtest/gtest.h"
#include "utilities.h"
#include "imaginary.h"

namespace {

  using namespace std;


    TEST(Vector,SortVector) {
      vector<double> v;
      v.push_back(-12.0);
      v.push_back(13);
      v.push_back(-1.0);
      EXPECT_EQ(v[0],-12.0);      
      EXPECT_EQ(v[1],13.0);  
      EXPECT_EQ(v[2],-1.0); 
      vector<double> x = sort_by_magnitude(v);
      EXPECT_EQ(x[0],-1.0);      
      EXPECT_EQ(x[1],-12.0);  
      EXPECT_EQ(x[2],13.0); 
      EXPECT_EQ(v[0],-12.0);      
      EXPECT_EQ(v[1],13.0);  
      EXPECT_EQ(v[2],-1.0); 
  }

  TEST(Question1, call_sort_by_magnitude) {
    std::vector<double> v;
    v.push_back(-1.0);
    v.push_back(22.2);
    v.push_back(0.0);
    v.push_back(-1000.1);

    std::vector<double> sorted = sort_by_magnitude(v);

    ASSERT_DOUBLE_EQ(sorted[0], 0.0);
    ASSERT_DOUBLE_EQ(sorted[1], -1.0);
    ASSERT_DOUBLE_EQ(sorted[2], 22.2);
    ASSERT_DOUBLE_EQ(sorted[3], -1000.1);

    ASSERT_DOUBLE_EQ(v[0], -1.0);
    ASSERT_DOUBLE_EQ(v[1], 22.2);
    ASSERT_DOUBLE_EQ(v[2], 0.0);
    ASSERT_DOUBLE_EQ(v[3], -1000.1);
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
        EXPECT_ANY_THROW(a.get(4,2));
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
        EXPECT_EQ(c.get(3,2), 23);
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
    TEST(TypedMatrix, Sub_assign1){
        TypedMatrix<int> a(2, 1);
        TypedMatrix<int> b(2, 1);
        a.set(0, 0, 2);
        a.set(0, 1, 3);
        b.set(0, 0, -3);
        b.set(0, 1, 2);
        a-=b;
        EXPECT_EQ(a.get(0,0), 5);
        EXPECT_EQ(a.get(0,1), 1);
        EXPECT_EQ(b.get(0,0), -3);
        EXPECT_EQ(b.get(0,1), 2);
    }

    TEST(TypedMatrix, Sub_assign2){
        TypedMatrix<int> a(1, 3);
        TypedMatrix<int> b(1, 3);
        a.set(0, 0, 1);
        a.set(1, 0, 2);
        a.set(2, 0, 3);
        b.set(0, 0, 5);
        b.set(1, 0, 5);
        b.set(2, 0, 5);
        a-=b;
        EXPECT_EQ(a.get(0,0), -4);
        EXPECT_EQ(a.get(1,0), -3);
        EXPECT_EQ(a.get(2,0), -2);
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
    TEST(TypedMatrix2, Mult3){
        TypedMatrix<int> a(2, 1);
        TypedMatrix<int> b(1, 2);
        TypedMatrix<int> c;
        a.set(0,0,2);
        a.set(0,1,2);
        b.set(1,0,2);
        b.set(0,0,2);  
        c = a * b;      
        EXPECT_EQ(c.get(0,0),8);
        EXPECT_ANY_THROW(c.get(0,1));
        TypedMatrix<int> d(2, 1);
        EXPECT_ANY_THROW(c.get(1,0));
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
        EXPECT_EQ(c.rows(),1);
        EXPECT_EQ(c.cols(),1);
        EXPECT_ANY_THROW(c.get(0,1));
        //std::cout<<c<<std::endl;
        //auto de =c.get(0,1);
        //std::cout << de;
        //EXPECT_EQ(c.get(0,1),1);
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
    TEST(Question3, read_file_that_doesnt_exist) {
    EXPECT_ANY_THROW(read_matrix_csv("input/doesnotexist.csv"));
}

TEST(Question3, read_invalid_file) {
    string path = "input/invalid.csv";

    // exists
    std::ifstream ifs;
    ifs.open (path, std::ifstream::in);
    ASSERT_TRUE(ifs.good());
    ifs.close();

    EXPECT_ANY_THROW(read_matrix_csv("input/invalid.csv"));
}

TEST(Question3, read_invalid_file2) {
    string path = "input/invalid2.csv";

    // exists
    std::ifstream ifs;
    ifs.open (path, std::ifstream::in);
    ASSERT_TRUE(ifs.good());
    ifs.close();

    EXPECT_ANY_THROW(read_matrix_csv("invalid2.csv"));
}
TEST(Question4, write_matrix_csv) {
    TypedMatrix<double> m = TypedMatrix<double>(2,4);
    m.set(0,0,4.5);
    m.set(0,1,5.555);
    write_matrix_csv(m, "out1.csv");
}

TEST(Question4, write_and_then_read_matrix_csv) {
    TypedMatrix<double> m = TypedMatrix<double>(2,4);
    m.set(0,0,4.5);
    m.set(0,1,5.555);

    string outpath = "input/mymatrix.csv";
    write_matrix_csv(m, outpath);

    TypedMatrix<double> m2 = read_matrix_csv(outpath);

    ASSERT_EQ(m2.rows(), m.rows());
    ASSERT_EQ(m2.cols(), m.cols());

    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            EXPECT_EQ(m.get(i, j), m2.get(i, j));
        }
    }
}

TEST(Question5, occurrence_map) {
    std::map<string, int> m = occurrence_map("input/in.txt");

    EXPECT_EQ(m["S&P"], 0); 
    EXPECT_EQ(m["500"], 2); 
    EXPECT_EQ(m["the"], 6);
    EXPECT_EQ(m["exchange"], 1); 
    EXPECT_EQ(m["says"], 1);
    EXPECT_EQ(m["wikipedia"], 1);
    EXPECT_EQ(m["Wikipedia"], 0); 
    EXPECT_EQ(m["sp500"], 1); 
  
}

TEST(Question5, occurrence_map2) {
    std::map<string, int> m = occurrence_map("input/in2.txt");

    EXPECT_EQ(m["i'm"], 1); 
    EXPECT_EQ(m["using"], 1); 
    EXPECT_EQ(m["10xgenomic's"], 2);
    EXPECT_EQ(m["new"], 1); 
    EXPECT_EQ(m["technology"], 1);
    EXPECT_EQ(m["I'm"], 0);

    EXPECT_EQ(m["george"], 2); 
    EXPECT_EQ(m["mallory's"], 2); 
    EXPECT_EQ(m["technology!"], 0); 
    EXPECT_EQ(m["famous"], 2); 
    EXPECT_EQ(m["quote"], 2);
    EXPECT_EQ(m["quote:"], 0); 
    EXPECT_EQ(m["because"], 1);
    EXPECT_EQ(m["there"], 1);
    EXPECT_EQ(m["there."], 0); 
    EXPECT_EQ(m["wier_d"], 0); 

    EXPECT_EQ(m["Really,"], 0);
    EXPECT_EQ(m["really,"], 0);
    EXPECT_EQ(m["really"], 1);
    EXPECT_EQ(m["123"], 1);
    EXPECT_EQ(m["number."], 0); 
    EXPECT_EQ(m["number"], 1); 

    EXPECT_EQ(m["I,"], 0);
    EXPECT_EQ(m["'I"], 0); 
    EXPECT_EQ(m["'i"], 1);
    EXPECT_EQ(m["i"], 0);

    EXPECT_EQ(m["another"], 1); 
    EXPECT_EQ(m["my"], 1); 
    EXPECT_EQ(m["My"], 0);
    EXPECT_EQ(m["mind"], 0); 
    EXPECT_EQ(m["rebellion."], 0);
    EXPECT_EQ(m["rebellion"], 1);

    EXPECT_EQ(m["biotech"], 1); 
    EXPECT_EQ(m["(biotech"], 0); 
    EXPECT_EQ(m["company)"], 0);
    EXPECT_EQ(m["company"], 1); 
    EXPECT_EQ(m["blah"], 3);

    EXPECT_EQ(m["the)s"], 0);
    EXPECT_EQ(m["are"], 1); 
    EXPECT_EQ(m["no%y6"], 0);
    EXPECT_EQ(m["wo!e4"], 0);

    EXPECT_EQ(m["xyz"], 2);
    EXPECT_EQ(m["costs"], 2); 
    EXPECT_EQ(m["40"], 1);
    EXPECT_EQ(m["40."], 0);
    EXPECT_EQ(m["$40"], 0);
    EXPECT_EQ(m["$40."], 0);
    EXPECT_EQ(m["$40.00"], 0);
    EXPECT_EQ(m["40.00"], 0);
}


TEST(Question5, occurrence_map3) {
    std::map<string, int> m = occurrence_map("input/in3.txt");

    EXPECT_EQ(m["i'm"], 1); 
    EXPECT_EQ(m["the"], 2); 
    EXPECT_EQ(m["500"], 1);
    EXPECT_EQ(m["s&p"], 0); 
    EXPECT_EQ(m["3"], 1);
    EXPECT_EQ(m["%''"], 0);

    EXPECT_EQ(m["sp500"], 1); 
    EXPECT_EQ(m["or"], 1); 
    EXPECT_EQ(m["just"], 1); 
    EXPECT_EQ(m["nasdaq"], 1); 
    EXPECT_EQ(m["exchange"],1);
    EXPECT_EQ(m["wier_d"], 0); 

    EXPECT_EQ(m["quote"], 1);
    EXPECT_EQ(m["a"], 1); 
    EXPECT_EQ(m["company"], 1);
    EXPECT_EQ(m["i"], 2);
    EXPECT_EQ(m["hy&6"], 0); 
    EXPECT_EQ(m["8"], 1); 

}

}
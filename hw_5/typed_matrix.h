//
// Created by KlavinsLab on 2019-02-14.
// Edited by Anushakamat on 2019-02-17.
//

#ifndef TYPEDMATRIX_H
#define TYPEDMATRIX_H
#include<iostream>
#include <vector>
#include <stdexcept>
#include<iterator>
using std::vector;
using std::string;

/*
 * You code should look pretty similar to HW_4, but conveniently, you'll
 * get to use the vector<vector<ElementType>> type, which is WAY easier to
 * use.
 *
 * Note that we are implementing the read and write csv methods
 * as a static method inside the TypedMatrix. We can call it
 * in our tests via TypdeMatrix<double>::read_matrix_csv or
 * TypedMatrix<double>::write_matrix_csv
 */

template <typename ElementType>
class TypedMatrix {

public:
    // refactor previous code to use the std::vector class
    // see private variable 'matrix' below as an example of the
    // type you'll be using

    TypedMatrix();
    TypedMatrix(int n, int m);
    TypedMatrix(const TypedMatrix& other);

    //~TypedMatrix();

    //getter
    const ElementType& get(int i, int j) const;
    int rows() const;
    int cols() const;

    //setter
    void set(int i, int j, ElementType value);

    // operator
    TypedMatrix& operator=(const TypedMatrix& other);
    TypedMatrix& operator+=(const TypedMatrix& other);
    TypedMatrix& operator-=(const TypedMatrix& other);
    TypedMatrix& operator*=(const TypedMatrix& other);
    bool operator==(const TypedMatrix& other) const;
    TypedMatrix operator+(const TypedMatrix& other);
    TypedMatrix operator*(const TypedMatrix& other);

    /*
     * If you were to implement static functions for write_matrix_csv and
     * read_matrix_csv, it'd be done as in commented code below. The function definition
     * would be specified in typed_matrix.cc. Please see the typed_matrix.cc.example
     * file as an example of how you would define the functions.
     */
    /*
        static TypedMatrix<double> TypedMatrix<double>::read_matrix_csv(const string path);
        static void TypedMatrix<double>::write_matrix_csv(const TypedMatrix<double> &matrix, const string path);
     */

private:
    int rows_;
    int cols_;
    vector< vector<ElementType> > matrix; // < you can call 'matrix' whatever, we don't care,
                                           // we can't access it because its private
};

// template methods implementations go here
template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix() {
    ElementType x = ElementType();
    rows_ =1;
    cols_ = 1;  
    matrix.resize(rows_);
    for(int i=0; i<matrix.size();i++){
        matrix[i].resize(cols_,x);
    }    
}

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(int n, int m) {
    ElementType x = ElementType();
    rows_ =m;
    cols_ = n;  
    matrix.resize(rows_);
    for(int i=0; i<matrix.size();i++){
        matrix[i].resize(cols_,x);
    }
}

//NEW TO BE TESTED
template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(const TypedMatrix<ElementType>& other){
    rows_ =other.rows_;
    cols_ = other.cols_;  
    matrix.resize(rows_);
    for(int i=0; i<matrix.size();i++){
        matrix[i].resize(cols_);
    }
    for(int i = 0 ; i < this->rows_;i++){
        for(int j =0; j < this->cols_; j++){
            this->matrix[i][j] = other.matrix[i][j];
            
        }
    }
}



    
template <typename ElementType>
int TypedMatrix<ElementType>::rows()const{
    return rows_;
}
template <typename ElementType>
int TypedMatrix<ElementType>::cols()const{
    return cols_;
}

template <typename ElementType>
const ElementType& TypedMatrix<ElementType>::get(int i, int j) const {
    if(i< 0 || i>=rows_ || j<0 || j>=cols_){
        //std::cout<<"\n in the wrong side of get \n";
        throw std::range_error("Out of range index in Matrix");
    }
    /*ElementType x = new ElementType();
    x = matrix[i][j];
    std::cout<<x<<"\n";*/
    return matrix[i][j];
}

template <typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType value){
    if(i< 0 || i>rows_ || j<0 || j>cols_){
        throw std::range_error("Out of range index in Matrix");
    }
    matrix[i][j] = value;
    return;
}



 template<typename ElementType>
 TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator=(const TypedMatrix<ElementType>& other){
     if(this != &other){
        this->rows_ = other.rows_;
        this->cols_ = other.cols_;
        this->matrix.resize(rows_);
        for(int i=0; i<this->matrix.size();i++){
            this->matrix[i].resize(cols_);
        }
        for(int i = 0 ; i < this->rows_;i++){
            for(int j =0; j < this->cols_; j++){
                matrix[i][j] = other.matrix[i][j];
            }
        }
        
     }
    return *this;
 }

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator+=(const TypedMatrix<ElementType>& other){
    if((rows_!= other.rows_) || (cols_ != other.cols_)){
        throw std::range_error("Matrix Dimensions do not match");
    }
    for(int i = 0 ; i < this->rows_;i++){
        for(int j =0; j < this->cols_; j++){
            this->matrix[i][j] += other.matrix[i][j];
            
        }
    }
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator-=(const TypedMatrix<ElementType>& other){
    if((rows_!= other.rows_) || (cols_ != other.cols_)){
        throw std::range_error("Matrix Dimensions do not match");
    }
    for(int i = 0 ; i < this->rows_;i++){
        for(int j =0; j < this->cols_; j++){
            this->matrix[i][j] -= other.matrix[i][j];
            
        }
    }
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator*=(const TypedMatrix<ElementType>& other){
    if((rows_!= other.rows_) || (cols_ != other.cols_)){
        throw std::range_error("Matrix Dimensions do not match");
    }
    for(int i = 0 ; i < this->rows_;i++){
        for(int j =0; j < this->cols_; j++){
            this->matrix[i][j] *= other.matrix[i][j];
            
        }
    }
    return *this;
}

template <typename ElementType>
bool TypedMatrix<ElementType>::operator==(const TypedMatrix<ElementType>& other)const{
    
    if((this->rows_ != other.rows_) ||(this->cols_ != other.cols_)){
        return false;
    }
    
    for(int i = 0 ; i < this->rows_;i++){
        for(int j =0; j < this->cols_; j++){
            if(!(matrix[i][j] == other.matrix[i][j])){
                return false;
            }
        }
    }
        
    return true;
    
}


template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator+(const TypedMatrix<ElementType>& other){
    if((rows_!= other.rows_) || (cols_ != other.cols_)){
        throw std::range_error("Matrix dimensions do not match");
    }
    TypedMatrix<ElementType> sum(cols_,rows_);
    for(int i = 0 ; i < this->rows_;i++){
        for(int j =0; j < this->cols_; j++){
            sum.set(i,j,this->matrix[i][j]+other.matrix[i][j]);
        }
    }
    return sum;
}
template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator*(const TypedMatrix<ElementType>& other){
    if(cols_!= other.rows_) {
        throw std::range_error("Matrix Multiplication not possible");
    }
    TypedMatrix<ElementType> product(other.cols_,rows_);
    
    for(int i = 0 ; i < this->rows_;i++){
        for(int j =0; j < other.cols_; j++){
            ElementType sum = ElementType();
            for(int k = 0 ; k< this->cols_; k++){
                sum += this->matrix[i][k]*other.matrix[k][j];
            }
            product.set(i,j,sum);

        }
    }
    
    return product;
}

/*
template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedMatrix<ElementType> &matrix)
{
    os << '[';
    for(int i=0; i<matrix.rows(); i++){
        if (i>0)
            os << ' ';
        os << '[';
        for(int j=0; j<matrix.cols(); j++){
            os << matrix.get(i, j);
            if (j<matrix.cols()-1){
                os << ",";
            }
        }
        os << ']';
        if (i<matrix.rows()-1)
            os << '\n';
    }
    os << ']';
    return os;
}*/








#endif

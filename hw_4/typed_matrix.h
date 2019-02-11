#ifndef TYPED_MATRIX
#define TYPED_MATRIX

#include <assert.h>
#include <iostream>
#include <stdexcept>

#include "typed_array.h"

template <typename ElementType>
class TypedMatrix{

public:

TypedMatrix();
TypedMatrix(int n, int m);

int numrows()const;
int numcolumns()const;

ElementType& get(int i, int j) const;
void set(int i, int j, ElementType value);
TypedMatrix& operator=(const TypedMatrix& other);
TypedMatrix& operator+=(const TypedMatrix& other);
TypedMatrix& operator*=(const TypedMatrix& other);
bool operator==(const TypedMatrix& other) const;
TypedMatrix operator+(const TypedMatrix& other);
TypedMatrix operator*(const TypedMatrix& other);

private:
int rows, columns;
TypedArray<TypedArray<ElementType>> matrix;
ElementType * buffer;
};

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix() {
    ElementType x = ElementType();
    matrix.get(0).set(0,x) ;   
    rows =1;
    columns = 1;  
}

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(int n, int m) {
    ElementType x = ElementType();
    rows = m;
    columns = n;
    //matrix.get(0).set(0,x) ;   
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            matrix.get(i).set(j,x);
         }
    }
    
}


template <typename ElementType>
int TypedMatrix<ElementType>::numrows()const{
    return rows;
}
template <typename ElementType>
int TypedMatrix<ElementType>::numcolumns()const{
    return columns;
}

template <typename ElementType>
ElementType& TypedMatrix<ElementType>::get(int i, int j) const {
    if(i< 0 || i>rows || j<0 || j>columns){
        throw std::range_error("Out of range index in array");
    }
    return matrix.safe_get(i).safe_get(j);
}

template <typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType value){
    
    matrix.get(i).set(j,value);
    return;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator=(const TypedMatrix<ElementType>& other) {
    if ( this != &other) {
        for(int i = 0 ; i < other.rows;i++){
            for(int j =0; j < other.columns; j++){
                this->set(i,j,other.get(i,j));
            }
        }
    }
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator+=(const TypedMatrix<ElementType>& other){
    if((rows!= other.rows) && (columns != other.columns)){
        throw std::range_error("Indices do not match");
    }
    for(int i = 0 ; i < other.rows;i++){
        for(int j =0; j < other.columns; j++){
            this->set(i,j,this->get(i,j)+other.get(i,j));
        }
    }
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator*=(const TypedMatrix<ElementType>& other){
    if((rows!= other.rows) && (columns != other.columns)){
        throw std::range_error("Indices do not match");
    }
    for(int i = 0 ; i < other.rows;i++){
        for(int j =0; j < other.columns; j++){
            this->set(i,j,this->get(i,j)*other.get(i,j));
        }
    }
    return *this;
}

template <typename ElementType>
bool TypedMatrix<ElementType>::operator==(const TypedMatrix<ElementType>& other)const{
    
    
    
    if((rows == other.rows) && (columns== other.columns)){
        bool flag = 1;
        for(int i = 0 ; i < other.rows;i++){
            for(int j =0; j < other.columns; j++){
                if(!(this->get(i,j) == other.get(i,j))){
                    flag = 0;
                    break;
                }
            }
        }
        return flag;
    }
    return 0;
}


template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator+(const TypedMatrix<ElementType>& other){
    if((rows!= other.rows) && (columns != other.columns)){
        throw std::range_error("Indices do not match");
    }
    TypedMatrix<ElementType> sum(columns,rows);
    for(int i = 0 ; i < other.rows;i++){
        for(int j =0; j < other.columns; j++){
            sum.set(i,j,this->get(i,j)+other.get(i,j));
        }
    }
    return sum;
}
template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator*(const TypedMatrix<ElementType>& other){
    if(columns!= other.rows) {
        throw std::range_error("Matrix Multiplication not possible");
    }
    TypedMatrix<ElementType> product(other.columns,rows);
    
    for(int i = 0 ; i < this->rows;i++){
        for(int j =0; j < other.columns; j++){
            ElementType sum = ElementType();
            for(int k = 0 ; k< other.rows; k++){
                sum = sum + this->get(i,k)*other.get(k,j);
            }
            product.set(i,j,sum);

        }
    }
    return product;
}

#endif
//
// ECEP520
//

#ifndef MYUTILS
#define MYUTILS
#include <map>
#include <vector>
#include <cstdlib>
#include<iostream>
#include<fstream>
#include <sstream>
#include<cctype>
#include <cstring>  
#include<iterator>
#include <algorithm>
#include "imaginary.h"
#include "typed_matrix.h"
using std::vector;
using std::string;

// Question 1
vector<double> sort_by_magnitude(vector<double> &v);

// Question 2
// just refactor typed_matrix.h to use vector<vector<ElementType>>

// Question 3
TypedMatrix<double> read_matrix_csv(const string path);

// Question 4
void write_matrix_csv(const TypedMatrix<double> &matrix, const string path);



// Question 5
string static trim_null_chars(string word);
int static is_valid_char(char ch);
int static is_valid_word(string word);
string static transform_invalid_word(string word);
string static filter_word(string word);
std::map<string, int> occurrence_map(const string path);

#endif // MYUTILS
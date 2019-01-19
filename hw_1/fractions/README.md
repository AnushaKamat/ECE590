Assignment 1:
1. "Learning the Shell" part : linuxcommand.org

2. hw_1 created.Fractions pulled to  my repo from class repo.

3. .gitignore is put in the reop to avoid :
bin/
build/
html/
latex/
docs.config
doxygen_sqlite3.db

4. Added a function to the fractions example called reduce.
It should take one Fraction argument and return a Fraction in lowest terms. 

Added tests into unit_test.c for 
- fractions with both num and den as negative numbers,
- either one of num and den are negative numbers, 
- possibility of num or den to have 0, 
- improper fractions.


5. A new header imaginary.h and code file imaginary.c is created.
A structure with a two members, real and im which are of type double.
Added functions for add, negate, conjugate, multiply, and magnitude.

Added test cases for checking the same.


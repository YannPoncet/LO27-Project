#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define Boolean int
#define TRUE 1
#define FALSE 0

#define NBROW 4
#define NBCOL 5

typedef struct cellElement cellElement;

struct cellElement
{
	int colIndex;
	int rowIndex;
	Boolean value;
	cellElement* nextCol;
	cellElement* nextRow;
};

typedef struct colElement colElement;

struct colElement
{
	int colN;
	colElement* nextCol;
	colElement* prevCol;
	cellElement* col;
};

typedef struct rowElement rowElement;

struct rowElement
{
	int rowN;
	rowElement* nextRow;
	rowElement* prevRow;
	cellElement* row;
};

typedef struct
{
	int colCount;
	int rowCount;
	colElement* cols;
	rowElement* rows;
}Matrix;



/*
*This function is able to create a new double array of Booleans with random values
*@param nbCol : an integer, the number of columns we want in the array of boolean
*@param nbRow : an integer, the number of rows we want in the array of boolean
*@return Boolean** : it returns a double dynamically-sized array (the data of a matrix)
*/
Boolean** newAleaArray(int nbCol, int nbRow);

/*
*This function is able to create a new empty double array of Booleans
*@param nbCol : an integer, the number of columns we want in the array of boolean
*@param nbRow : an integer, the number of rows we want in the array of boolean
*@return Boolean** : it returns a double dynamically-sized array (the data of a matrix)
*/
Boolean** newVannishingArray(int nbCol, int nbRow);

/*
*This function is able to create a new matrix of given Booleans
*@return Matrix : it returns the filled Matrix
*/

Matrix newGivenMatrix();

/*
*This function is able to create a new Matrix with all its components (rows, cols, cells) with a double array of Booleans b
*@param nbCol : an integer, the number of columns we want in the array of boolean
*@param nbRow : an integer, the number of rows we want in the array of boolean
*@param b : a double array of Booleans, the array representation of the matrix we want to create
*@return Matrix : it returns the filled Matrix
*/

Matrix newMatrix(Boolean** b, int nbCol, int nbRow);

/*
*This procedure is able to print a Matrix
*@param matrix : the Matrix we want to print
*/
void printMatrix(Matrix matrix);

/*
*This function is able to tell if a Matrix is empty or not
*@param matrix : the Matrix we want to check
*@return Boolean : it returns TRUE or FALSE, TRUE if the Matrix is Empty, FALSE otherwise
*/
Boolean isMatrixEmpty(Matrix matrix);

/*
*This function is able to tell if a given column of a Matrix is empty or not
*@param matrix : the Matrix in which there is the column we want to check
*@param colN : an integer, the index of the column we want to check
*@return Boolean : it returns TRUE or FALSE, TRUE if the column is Empty, FALSE otherwise
*/
Boolean isColumnEmpty(Matrix matrix, int colN);

/*
*This function is able to tell if a given row of a Matrix is empty or not
*@param matrix : the Matrix in which there is the row we want to check
*@param colN : an integer, the index of the row we want to check
*@return Boolean : it returns TRUE or FALSE, TRUE if the row is Empty, FALSE otherwise
*/
Boolean isRowEmpty(Matrix matrix, int rowN);

/*
*This function is able to tell if a given Matrix is square
*@param matrix : the Matrix we want to check
*@return Boolean : it returns TRUE or FALSE, TRUE if the Matrix is square, FALSE otherwise
*/
Boolean isMatrixSquare(Matrix matrix);

/*
*This function is able to tell if two Matrix are equals or not
*@param matrix1 : the first Matrix
*@param matrix2 : the second Matrix
*@return Boolean : it returns TRUE or FALSE, TRUE if the two Matrix are equals, FALSE otherwise
*/
Boolean equalsMatrix(Matrix matrix1, Matrix matrix2);

/*
*This function is able to compute the boolean addition (OR operator) of the two specified Matrix
*@param matrix1 : the first Matrix
*@param matrix2 : the second Matrix
*@return Matrix : it returns the Matrix once the boolean addition is applied
*/
Matrix sumMatrix(Matrix matrix1, Matrix matrix2);

/*
*This function is able to compute the boolean product (AND operator) of the two specified Matrix
*@param matrix1 : the first Matrix
*@param matrix2 : the second Matrix
*@return Matrix : it returns the Matrix once the boolean product is applied
*/
Matrix mulMatrix(Matrix matrix1, Matrix matrix2);

/*
*This function is able to compute the XOR operator of the two specified Matrix
*@param matrix1 : the first Matrix
*@param matrix2 : the second Matrix
*@return Matrix : it returns the Matrix once the XOR is applied
*/
Matrix xorMatrix(Matrix matrix1, Matrix matrix2);

/*
*Given in input a matrix with M rows and N columns, this function computes a matrix with
    M rows and N-1 columns where each element corresponds to the AND boolean operation between
    two successive horizontal elements in the input matrix
*@param matrix : the Matrix we want to apply the sequence to
*@return Matrix : it returns the Matrix once all the AND are applied on the columns
*/
Matrix andColSequenceOnMatrix(Matrix matrix);

/*
*Given in input a matrix with M rows and N columns, this function computes a matrix with
    M rows and N-1 columns where each element corresponds to the OR boolean operation between
    two successive horizontal elements in the input matrix
*@param matrix : the Matrix we want to apply the sequence to
*@return Matrix : it returns the Matrix once all the OR are applied on the columns
*/
Matrix orColSequenceOnMatrix(Matrix matrix);

/*
*Given in input a matrix with M rows and N columns, this function computes a matrix with
    M-1 rows and N columns where each element corresponds to the AND boolean operation between
    two successive vertical elements in the input matrix
*@param matrix : the Matrix we want to apply the sequence to
*@return Matrix : it returns the Matrix once all the AND are applied on the rows
*/
Matrix andRowSequenceOnMatrix(Matrix matrix);

/*
*Given in input a matrix with M rows and N columns, this function computes a matrix with
    M-1 rows and N columns where each element corresponds to the OR boolean operation between
    two successive vertical elements in the input matrix
*@param matrix : the Matrix we want to apply the sequence to
*@return Matrix : it returns the Matrix once all the OR are applied on the rows
*/
Matrix orRowSequenceOnMatrix(Matrix matrix);

/*
*This function does a loop of a given rule
*@param matrix : the Matrix we want to apply the rule to
*@param ruleID : an integer, the rule we want to apply
*@param loop : an integer, telling how many time we want to apply the rule
*@return Matrix : it returns the resulting Matrix (once the rules are applied)
*/
Matrix applyRules(Matrix matrix, int ruleID, int loop);

/*
*This function is able look for and find a cell knowing its row and columns indexes
*@param matrix : the Matrix in which we want to find the cell
*@param rowV : an integer, the row index of the cell we want to find
*@param colV : an integer, the column index of the cell we want to find
*@return cellElement* : it returns the cell we are looking for
*/
cellElement* searchCell(Matrix matrix, int rowV, int colV);

/*
*This function applies the rule 2 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule2(Matrix matrix);

/*
*This function applies the rule 8 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule8(Matrix matrix);

/*
*This function applies the rule 32 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule32(Matrix matrix);

/*
*This function applies the rule 128 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule128(Matrix matrix);

/*
*This function applies the rule 4 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule4(Matrix matrix);

/*
*This function applies the rule 16 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule16(Matrix matrix);

/*
*This function applies the rule 256 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule256(Matrix matrix);

/*
*This function applies the rule 64 on a given Matrix, it build an array thanks to the Matrix value,
    then it applies the rule and finally it uses newMatrix to create another Matrix from the array
*@param matrix : the Matrix we want to apply the rule to
*@return Matrix : it returns the resulting Matrix (once the rule is applied)
*/
Matrix rule64(Matrix matrix);


/*
*This function works with all the rules, the rule will be binary analysedand
    for each bit equal to 1 the corresponding rule will be applied,
    then a XOR will be applied between all the returned Matrix thanks to recursivity
*@param matrix : the Matrix we want to apply the rule to
*@param ruleID : an integer, the rule we want to apply
*@param bit : an integer, telling in which bit we will work (power of 2)
*@return Matrix : it returns the resulting Matrix (once the rules are applied)
*/
Matrix rulesDecomposition(Matrix matrix, int ruleID, int bit);

#endif

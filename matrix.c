#include <stdlib.h>
#include <stdio.h>
#include <matrix.h>

Boolean** newAleaArray(int nbCol, int nbRow)
{
	Boolean** b = (Boolean**)malloc(nbRow*sizeof(Boolean*));

	for (short i=0;i<nbRow;i++)
	{
		b[i]=(Boolean*)malloc(nbCol*sizeof(Boolean));
		for (short j=0;j<nbCol;j++)
		{
			b[i][j]=rand()%2;
		}
	}

	return b;
}

Boolean** newVannishingArray(int nbCol, int nbRow)
{
	Boolean** b = (Boolean**)malloc(nbRow*sizeof(Boolean*));

	for (short i=0;i<nbRow;i++)
	{
		b[i]=(Boolean*)malloc(nbCol*sizeof(Boolean));
		for (short j=0;j<nbCol;j++)
		{
			b[i][j]=0;
		}
	}

	return b;
}

Matrix newGivenMatrix()
{
	int nbCol = 0;
	int nbRow = 0;
	printf("Number of columns : ");
	scanf("%i", &nbCol);
	printf("Number of rows : ");
	scanf("%i", &nbRow);

	Boolean** b = (Boolean**)malloc(nbRow*sizeof(Boolean*));

	for (short i=0;i<nbRow;i++)
	{
		b[i]=(Boolean*)malloc(nbCol*sizeof(Boolean));
		for (short j=0;j<nbCol;j++)
		{
			printf("Matrix row %i column %i value : ", i+1, j+1);
			scanf("%i", &b[i][j]);
			while(b[i][j]>1 || b[i][j]<0)
			{
				printf("\nError, we are working with booleans\n");
				printf("Matrix row %i column %i value : ", i+1, j+1);
				scanf("%i", &b[i][j]);
			}
		}
	}

	Matrix matrix = newMatrix(b, nbCol, nbRow);

	return matrix;
}

Matrix newMatrix(Boolean** b, int nbCol, int nbRow)
{
	Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));

	matrix->colCount = nbCol;
	matrix->rowCount = nbRow;

	colElement* colE = (colElement*)malloc(sizeof(colElement));
	colE->colN = 1;
	colE->prevCol = NULL;

	rowElement* rowE = (rowElement*)malloc(sizeof(rowElement));
	rowE->rowN = 1;
	rowE->prevRow = NULL;

	matrix->cols = colE;
	matrix->rows = rowE;

	for(short i=1; i<nbCol; i++)
	{
		colElement* new = (colElement*)malloc(sizeof(colElement));
		colE->nextCol = new;
		new->prevCol = colE;
		new->colN = i+1;
		colE = new;
	}
	colE->nextCol = NULL;

	for(short j=1; j<nbRow; j++)
	{
		rowElement* new = (rowElement*)malloc(sizeof(rowElement));
		rowE->nextRow = new;
		new->prevRow = rowE;
		new->rowN = j+1;
		rowE = new;
	}
	rowE->nextRow = NULL;

	cellElement* cell = (cellElement*)malloc(sizeof(cellElement));
	cell = NULL;
	for(short i=nbRow-1; i>-1; i--)
	{
		for(short j=nbCol-1; j>-1; j--)
		{
			cellElement* new = (cellElement*)malloc(sizeof(cellElement));
			new->nextCol = cell;
			new->value = b[i][j];
			new->colIndex = i+1;
			new->rowIndex = j+1;
			if(rowE->nextRow==NULL)
			{
				new->nextRow = NULL;
			}
			else
			{
				rowE = rowE->nextRow;
				cellElement* new2 = NULL;
				new2 = rowE->row;
				for(short k=0; k<j; k++)
				{
					new2 = new2->nextCol;
				}
				new->nextRow = new2;
				rowE = rowE->prevRow;
			}
			cell = new;
			rowE->row = cell;

			colE->col = cell;
			colE = colE->prevCol;

		}
		cell = NULL;
		colE = matrix->cols;
		for(short k=1; k<nbCol; k++)
		{
			colE = colE->nextCol;
		}
		rowE = rowE->prevRow;
	}
	return *matrix;
}

void printMatrix(Matrix matrix)
{
	printf("\n");

	if(isMatrixEmpty(matrix))
	{
		printf("The matrix is empty\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for(int i=0; i<matrix.rowCount; i++)
		{
			printf("| ");
			for(int j=0; j<matrix.colCount; j++)
			{
				printf("%i", searchCell(matrix, i+1, j+1)->value);
			}
			printf(" |");
			printf("\n");
		}
	}
}

cellElement* searchCell(Matrix matrix, int rowV, int colV)
{
    if(isMatrixEmpty(matrix))
	{
		printf("Error, the matrix is empty");
		exit(EXIT_FAILURE);
	}

    rowElement* rowE = matrix.rows;

    while(rowE->rowN != rowV)
    {
        rowE = rowE->nextRow;
    }

    cellElement* cell = rowE->row;

    for(int i=1; i<colV; i++)
    {
        cell = cell->nextCol;
    }

    return cell;


}

Boolean isMatrixEmpty(Matrix matrix)
{
	Boolean isEmpty = FALSE;
	if(matrix.cols==NULL || matrix.rows==NULL)
	{
		isEmpty = TRUE;
	}
	return isEmpty;
}

Boolean isColumnEmpty(Matrix matrix, int colN)
{
	Boolean isEmpty = FALSE;
	if(isMatrixEmpty(matrix))
	{
		isEmpty = TRUE;
	}
	else
	{
		int i = 1;
		colElement* tempCol = matrix.cols;
		while((tempCol->nextCol!=NULL) && (i<colN))
		{
			tempCol = tempCol->nextCol;
			i++;
		}
		if(i!=colN)
		{
			isEmpty = TRUE;
		}
		else
		{
			if(tempCol->col==NULL)
			{
				isEmpty = TRUE;
			}
		}
	}
	return isEmpty;


}

Boolean isRowEmpty(Matrix matrix, int rowN)
{
	Boolean isEmpty = FALSE;
	if(isMatrixEmpty(matrix))
	{
		isEmpty = TRUE;
	}
	else
	{
		short i = 1;
		rowElement* tempRow = matrix.rows;
		while((tempRow->nextRow!=NULL) && (i<rowN))
		{
			tempRow = tempRow->nextRow;
			i++;
		}
		if(i!=rowN)
		{
			isEmpty = TRUE;
		}
		else
		{
			if(tempRow->row==NULL)
			{
				isEmpty = TRUE;
			}
		}
	}
	return isEmpty;


}

Boolean isMatrixSquare(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

    Boolean isSquare = FALSE;
    if(matrix.colCount==matrix.rowCount)
    {
        isSquare = TRUE;
    }
    return isSquare;

}

Boolean equalsMatrix(Matrix matrix1, Matrix matrix2)
{
	Boolean equals = TRUE;

	if(isMatrixEmpty(matrix1) || isMatrixEmpty(matrix2))
	{
		equals = FALSE;
	}
	else if(matrix1.colCount != matrix2.colCount || matrix1.rowCount != matrix2.rowCount)
	{
		equals = FALSE;
	}
	else
	{
		for(int i=1; i<matrix1.rowCount+1; i++)
		{
			for(int j=1; j<matrix1.colCount+1; j++)
			{
				if(searchCell(matrix1, i, j)->value != searchCell(matrix2, i, j)->value)
				{
					equals = FALSE;
				}
			}
		}
	}

	return equals;
}

Matrix sumMatrix(Matrix matrix1, Matrix matrix2)
{
	if ((matrix1.colCount != matrix2.colCount || matrix1.rowCount != matrix2.rowCount) || (isMatrixEmpty(matrix1) || isMatrixEmpty(matrix2)))
	{
		printf("Error, the matrix is empty");
		exit(EXIT_FAILURE);
	}


	Boolean** b = (Boolean**)malloc(matrix1.rowCount*sizeof(Boolean*));

	for (int i=0;i<matrix1.rowCount;i++)
	{
		b[i]=(Boolean*)malloc(matrix1.colCount*sizeof(Boolean));
		for (int j=0;j<matrix1.colCount;j++)
		{
			b[i][j] = searchCell(matrix1,i+1,j+1)->value || searchCell(matrix2,i+1,j+1)->value;
		}
	}

	Matrix matrix3 = newMatrix(b,matrix1.colCount,matrix1.rowCount);

	return matrix3;
}

Matrix mulMatrix(Matrix matrix1, Matrix matrix2)
{
	if ((matrix1.colCount != matrix2.colCount || matrix1.rowCount != matrix2.rowCount) || (isMatrixEmpty(matrix1) || isMatrixEmpty(matrix2)))
	{
		printf("Error, the matrix is empty");
		exit(EXIT_FAILURE);
	}

	Boolean** b = (Boolean**)malloc(matrix1.rowCount*sizeof(Boolean*));

	for (int i=0;i<matrix1.rowCount;i++)
	{
		b[i]=(Boolean*)malloc(matrix1.colCount*sizeof(Boolean));
		for (int j=0;j<matrix1.colCount;j++)
		{
			b[i][j] = searchCell(matrix1,i+1,j+1)->value && searchCell(matrix2,i+1,j+1)->value;
		}
	}

	Matrix matrix3 = newMatrix(b,matrix1.colCount,matrix1.rowCount);

	return matrix3;
}

Matrix xorMatrix(Matrix matrix1, Matrix matrix2)
{
	if ((matrix1.colCount != matrix2.colCount || matrix1.rowCount != matrix2.rowCount) || (isMatrixEmpty(matrix1) || isMatrixEmpty(matrix2)))
	{
		printf("Error, the matrix is empty");
		exit(EXIT_FAILURE);
	}


	Boolean** b = (Boolean**)malloc(matrix1.rowCount*sizeof(Boolean*));

	for (int i=0;i<matrix1.rowCount;i++)
	{
		b[i]=(Boolean*)malloc(matrix1.colCount*sizeof(Boolean));
		for (int j=0;j<matrix1.colCount;j++)
		{
			b[i][j] = abs(searchCell(matrix1,i+1,j+1)->value - searchCell(matrix2,i+1,j+1)->value);
		}
	}

	Matrix matrix3 = newMatrix(b,matrix1.colCount,matrix1.rowCount);

	return matrix3;
}

Matrix andColSequenceOnMatrix(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc(matrix.rowCount*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount; i++)
	{
		b[i]=(Boolean*)malloc((matrix.colCount-1)*sizeof(Boolean));
		for (int j=0;j<matrix.colCount-1;j++)
		{
			b[i][j] = searchCell(matrix,i+1,j+1)->value && searchCell(matrix,i+1,j+2)->value;
		}
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount-1,matrix.rowCount);

	return resultMatrix;
}

Matrix orColSequenceOnMatrix(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc(matrix.rowCount*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount; i++)
	{
		b[i]=(Boolean*)malloc((matrix.colCount-1)*sizeof(Boolean));
		for (int j=0;j<matrix.colCount-1;j++)
		{
			b[i][j] = searchCell(matrix,i+1,j+1)->value || searchCell(matrix,i+1,j+2)->value;
		}
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount-1,matrix.rowCount);

	return resultMatrix;
}

Matrix andRowSequenceOnMatrix(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc((matrix.rowCount-1)*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount-1; i++)
	{
		b[i]=(Boolean*)malloc(matrix.colCount*sizeof(Boolean));
		for (int j=0;j<matrix.colCount;j++)
		{
			b[i][j] = searchCell(matrix,i+1,j+1)->value && searchCell(matrix,i+2,j+1)->value;
		}
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount,matrix.rowCount-1);

	return resultMatrix;
}

Matrix orRowSequenceOnMatrix(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc((matrix.rowCount-1)*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount-1; i++)
	{
		b[i]=(Boolean*)malloc(matrix.colCount*sizeof(Boolean));
		for (int j=0;j<matrix.colCount;j++)
		{
			b[i][j] = searchCell(matrix,i+1,j+1)->value || searchCell(matrix,i+2,j+1)->value;
		}
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount,matrix.rowCount-1);

	return resultMatrix;
}

Matrix applyRules(Matrix matrix, int ruleID, int loop)
{
	if(isMatrixEmpty(matrix))
	{
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
	}

	Matrix resultMatrix = matrix;

	if(loop>0)
	{
		resultMatrix = applyRules(rulesDecomposition(matrix, ruleID, 1), ruleID, loop-1);
	}

	return resultMatrix;
}

Matrix rule2(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc(matrix.rowCount*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount; i++)
	{
		b[i]=(Boolean*)malloc(matrix.colCount*sizeof(Boolean));
		for (int j=0;j<matrix.colCount-1;j++)
		{
			b[i][j] = searchCell(matrix,i+1,j+2)->value;
		}
		b[i][matrix.colCount-1] = 0;
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount,matrix.rowCount);

	return resultMatrix;
}

Matrix rule8(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc(matrix.rowCount*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount; i++)
	{
		b[i]=(Boolean*)malloc(matrix.colCount*sizeof(Boolean));
		for (int j=0;j<matrix.colCount;j++)
		{
			if(i == matrix.rowCount-1)
			{
				b[i][j]=0;
			}
			else
			{
				b[i][j] = searchCell(matrix,i+2,j+1)->value;
			}
		}
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount,matrix.rowCount);

	return resultMatrix;
}

Matrix rule32(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc(matrix.rowCount*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount; i++)
	{
		b[i]=(Boolean*)malloc(matrix.colCount*sizeof(Boolean));
		b[i][0] = 0;

		for (int j=1;j<matrix.colCount;j++)
		{
			b[i][j] = searchCell(matrix,i+1,j)->value;
		}
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount,matrix.rowCount);

	return resultMatrix;
}

Matrix rule128(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Boolean** b = (Boolean**)malloc(matrix.rowCount*sizeof(Boolean*));

	for(int i=0; i<matrix.rowCount; i++)
	{
		b[i]=(Boolean*)malloc(matrix.colCount*sizeof(Boolean));
		for (int j=0;j<matrix.colCount;j++)
		{
			if(i == 0)
			{
				b[i][j]=0;
			}
			else
			{
				b[i][j] = searchCell(matrix,i,j+1)->value;
			}
		}
	}

	Matrix resultMatrix = newMatrix(b,matrix.colCount,matrix.rowCount);

	return resultMatrix;
}

Matrix rule4(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Matrix resultMatrix = rule8(rule2(matrix));

	return resultMatrix;
}

Matrix rule16(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Matrix resultMatrix = rule8(rule32(matrix));

	return resultMatrix;
}

Matrix rule256(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Matrix resultMatrix = rule128(rule2(matrix));

	return resultMatrix;
}

Matrix rule64(Matrix matrix)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Matrix resultMatrix = rule128(rule32(matrix));

	return resultMatrix;
}

Matrix rulesDecomposition(Matrix matrix, int ruleID, int bit)
{
    if(isMatrixEmpty(matrix))
    {
        printf("Error, the matrix is empty");
        exit(EXIT_FAILURE);
    }

	Matrix resultMatrix = newMatrix(newVannishingArray(matrix.colCount, matrix.rowCount), matrix.colCount, matrix.rowCount);
	Matrix tmpMatrix;

	if(ruleID>0)
	{
		if((ruleID & 1) == 1)
		{
			switch(bit)
			{
				case 1 : tmpMatrix = matrix; break;
				case 2 : tmpMatrix = rule2(matrix); break;
				case 4 : tmpMatrix = rule4(matrix); break;
				case 8 : tmpMatrix= rule8(matrix); break;
				case 16 : tmpMatrix = rule16(matrix); break;
				case 32 : tmpMatrix = rule32(matrix); break;
				case 64 : tmpMatrix = rule64(matrix); break;
				case 128 : tmpMatrix = rule128(matrix); break;
				case 256 : tmpMatrix = rule256(matrix); break;
			}

			resultMatrix = xorMatrix(tmpMatrix, rulesDecomposition(matrix, ruleID>>1, bit*2));
		}
		else
		{
			resultMatrix = rulesDecomposition(matrix, ruleID>>1, bit * 2);
		}
	}

	return resultMatrix;
}

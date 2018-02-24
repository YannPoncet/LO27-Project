#include <stdlib.h>
#include <stdio.h>
#include <matrix.h>
#include <time.h>

int main()
{
	printf("************************************************************\n");
	printf("************************ M4TR1X ****************************\n");
	printf("******DUR4ND******************************PONC3T************\n");
	printf("************************************************************\n\n");
	printf("Welcome to our program which is able to play with matrices !\n\n");

	Boolean given = FALSE;
	int g = 1;
	printf("If you want to work with random matrix enter 0, otherwise enter anything else\n");
	scanf("%i", &g);
	if(g != 0)
	{
		given = TRUE;
	}
	printf("There is the list of all the functions :\n");
	printf("Press 1 to add two matrixes\n");
	printf("Press 2 to multiply two matrixes\n");
	printf("Press 3 to apply andColSequenceOnMatrix to a matrix\n");
	printf("Press 4 to apply orColSequenceOnMatrix to a matrix\n");
	printf("Press 5 to apply andRowSequenceOnMatrix to a matrix\n");
	printf("Press 6 to apply orRowSequenceOnMatrix to a matrix\n");
	printf("Press 7 to apply a rule n times (n given) to a matrix\n");

	int choice;
	scanf("%i", &choice);

	switch(choice)
	{
		case 1 :
			if(given)
			{
				printf("First matrix :\n");
				Matrix matrix1 = newGivenMatrix();
				printf("Second matrix :\n");
				Matrix matrix2 = newGivenMatrix();

				printMatrix(matrix1);
				printMatrix(matrix2);
				printMatrix(sumMatrix(matrix1,matrix2));
			}
			else
			{
				Matrix matrix1 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);
				Matrix matrix2 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);

				printMatrix(matrix1);
				printMatrix(matrix2);
				printMatrix(sumMatrix(matrix1,matrix2));
			} main(); break;
		case 2 :
			if(given)
			{
				printf("First matrix :\n");
				Matrix matrix1 = newGivenMatrix();
				printf("Second matrix :\n");
				Matrix matrix2 = newGivenMatrix();

				printMatrix(matrix1);
				printMatrix(matrix2);
				printMatrix(mulMatrix(matrix1,matrix2));
			}
			else
			{
				Matrix matrix1 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);
				Matrix matrix2 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);

				printMatrix(matrix1);
				printMatrix(matrix2);
				printMatrix(mulMatrix(matrix1,matrix2));
			} main(); break;
		case 3 :
			if(given)
			{
				Matrix matrix1 = newGivenMatrix();

				printMatrix(matrix1);
				printMatrix(andColSequenceOnMatrix(matrix1));
			}
			else
			{
				Matrix matrix1 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);

				printMatrix(matrix1);
				printMatrix(andColSequenceOnMatrix(matrix1));
			} main(); break;
		case 4 :
			if(given)
			{
				Matrix matrix1 = newGivenMatrix();

				printMatrix(matrix1);
				printMatrix(orColSequenceOnMatrix(matrix1));
			}
			else
			{
				Matrix matrix1 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);

				printMatrix(matrix1);
				printMatrix(orColSequenceOnMatrix(matrix1));
			} main(); break;
		case 5 :
			if(given)
			{
				Matrix matrix1 = newGivenMatrix();

				printMatrix(matrix1);
				printMatrix(andRowSequenceOnMatrix(matrix1));
			}
			else
			{
				Matrix matrix1 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);

				printMatrix(matrix1);
				printMatrix(andRowSequenceOnMatrix(matrix1));
			} main(); break;
		case 6 :
			if(given)
			{
				Matrix matrix1 = newGivenMatrix();

				printMatrix(matrix1);
				printMatrix(orRowSequenceOnMatrix(matrix1));
			}
			else
			{
				Matrix matrix1 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);

				printMatrix(matrix1);
				printMatrix(orRowSequenceOnMatrix(matrix1));
			} main(); break;
		case 7 :
			{
				int ruleID = 0;
				int loop = 0;
				do
				{
					printf("Which rule do you want to apply ? ");
					scanf("%i", &ruleID);
				}while(ruleID>511 || ruleID<1);

				do
				{
					printf("How many times ? ");
					scanf("%i", &loop);
				}while(loop<1);

				if(given)
				{
					Matrix matrix1 = newGivenMatrix();

					printMatrix(matrix1);
					printMatrix(applyRules(matrix1, ruleID, loop));
				}
				else
				{
					Matrix matrix1 = newMatrix(newAleaArray(NBCOL, NBROW), NBCOL, NBROW);

					printMatrix(matrix1);
					printMatrix(applyRules(matrix1, ruleID, loop));
				}
			} main(); break;
		default : printf("Choice impossible\n"); main();
	}

	return 0;
}

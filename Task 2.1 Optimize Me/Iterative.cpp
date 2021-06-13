#include <bits/stdc++.h>

using namespace std;

const int sizen = 10;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ;

long long costMatrixA[sizen][sizen];
long long costMatrixB[sizen][sizen];

long long productMat[sizen][sizen];

long long proMatrixA[sizen][sizen];
long long proMatrixB[sizen][sizen];

// A utility function to find min of two integers
int minu(int a, int b)
{ return (a < b)? a: b; }

// A utility function to find min of three integers
int min(int a, int b, int c)
{ return minu(minu(a, b), c);}
 
// A utility function to find max of two integers
int max(int a, int b)
{ return (a > b)? a: b; }
 
long long FindMinCostA(int row, int col, int sizen)
{
    //matrixCopy(costMatrixA, row, col);
    int matCopyRow = sizen - row;
    int matCopyCol = sizen - col;

    //copying to temporary variable
    long long matcopy[matCopyRow][matCopyCol];
    for (int i = 0; i < matCopyRow; i++)
    {
        for(int j = 0; j < matCopyCol; j++)
        {
            matcopy[i][j] = costMatrixA[i+row][j+col];
        }        
    }
    
    for (int line=1; line<=(matCopyRow + matCopyCol -1); line++)
    {
        
        int start_col =  max(0, line-matCopyRow);
        int count = min(line, (matCopyCol-start_col), matCopyRow);
 
        for (int j=0; j<count; j++)
            {
                if(minu(matCopyRow, line)-j-1 == 0 && start_col+j !=0)
                    matcopy[minu(matCopyRow, line)-j-1][start_col+j] += matcopy[minu(matCopyRow, line)-j-1][start_col+j -1];
                else if(start_col+j ==0 && minu(matCopyRow, line)-j-1 != 0)
                    matcopy[minu(matCopyRow, line)-j-1][start_col+j] +=  matcopy[minu(matCopyRow, line)-j-1-1][start_col+j];
                else
                    matcopy[minu(matCopyRow, line)-j-1][start_col+j] += min(matcopy[minu(matCopyRow, line)-j-1-1][start_col+j], matcopy[minu(matCopyRow, line)-j-1][start_col+j -1]);
               
            }
            matcopy[0][0] = costMatrixA[row][col];
       
    }
}

long long FindMaxCostB(int row, int col, int sizen)
{
    //matrixCopy(costMatrixA, row, col);
    int matCopyRow = sizen - row;
    int matCopyCol = sizen - col;

    long long matcopy[matCopyRow][matCopyCol];
    for (int i = 0; i < matCopyRow; i++)
    {
        for(int j = 0; j < matCopyCol; j++)
        {
            matcopy[i][j] = costMatrixA[i+row][j+col];
        }        
    }
    
    for (int line=1; line<=(matCopyRow + matCopyCol -1); line++)
    {
        
        int start_col =  max(0, line-matCopyRow);
 
        int count = min(line, (matCopyCol-start_col), matCopyRow);
 
        for (int j=0; j<count; j++)
            {
                if(minu(matCopyRow, line)-j-1 == 0 && start_col+j !=0)
                    matcopy[minu(matCopyRow, line)-j-1][start_col+j] += matcopy[minu(matCopyRow, line)-j-1][start_col+j -1];
                else if(start_col+j ==0 && minu(matCopyRow, line)-j-1 != 0)
                    matcopy[minu(matCopyRow, line)-j-1][start_col+j] +=  matcopy[minu(matCopyRow, line)-j-1-1][start_col+j];
                else
                    matcopy[minu(matCopyRow, line)-j-1][start_col+j] += max(matcopy[minu(matCopyRow, line)-j-1-1][start_col+j], matcopy[minu(matCopyRow, line)-j-1][start_col+j -1]);
               
            }
            matcopy[0][0] = costMatrixA[row][col];
       
    }
}

int main()
{
    int i, j, k;
    srand(time(0));
    // initialisation
    for (i = 0; i < sizen; i++)
    {
        for (j = 0; j < sizen; j++)
        {
            costMatrixA[i][j] = 1 + rand() % 10;
            costMatrixB[i][j] = 1 + rand() % 10;
            productMat[i][j] = 0;
        }
    }
  
	for (i = 0; i < sizen; i++)
	{
		for (j = 0; j < sizen; j++)
		{
			proMatrixA[i][j] = FindMinCostA(i, j, sizen);
			proMatrixB[i][j] = FindMaxCostB(i, j, sizen);
		}
	}

    //creating productMat as explained in the beginning
    for (i = 0; i < sizen; i++)
    {
        for (j = 0; j < sizen; j++)
        {
            for (k = 0; k < sizen; k++)
                productMat[i][j] += proMatrixA[i][k] * proMatrixB[k][j];
        }
    }
    
    long long filterArray[4][sizen];
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < sizen; j++)
            filterArray[i][j] = rand() % 2;
    }
    // matrix of dimension (sizen/c) x 1 where c = 4
    long long finalMat[sizen / 4];
    // applying the filter
    for (i = 0; i <= sizen - 4; i += 4)
    {
        long long sum = 0;
        // dot product of 4xn portion of productMat
        for (j = 0; j < sizen; j++)
        {
            for (int filterRow = 0; filterRow < 4; filterRow++)
            {
                sum += productMat[i + filterRow][j]*filterArray[filterRow][j];
            }
        }
        finalMat[i / 4] = sum;
    }
    
    return 0;
}



/*
#REFERENCES
    Diagonal traversal of matrix
    https://www.geeksforgeeks.org/zigzag-or-diagonal-traversal-of-matrix/

*/
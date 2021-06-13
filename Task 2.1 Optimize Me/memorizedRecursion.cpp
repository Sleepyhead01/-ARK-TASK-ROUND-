#include <bits/stdc++.h>
#include <stdint.h>

using namespace std;

const int sizen = 1000;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ;

long long costMatrixA[sizen][sizen];
long long costMatrixB[sizen][sizen];

long long productMat[sizen][sizen];

long long proMatrixA[sizen][sizen];
long long proMatrixB[sizen][sizen];


//Simple recursion  which returns the minimum cost of going from i,j to n,n
long long FindMinCostA(int i, int j, int n)
{
    //going out of bounds
    if (i >= n)
        return 0;
    //going out of bounds
    if (j >= n)
        return 0;
       
    if (proMatrixA[i][j] != -1)
    {
        return proMatrixA[i][j];
    }
    //going down or right
    proMatrixA[i][j] = costMatrixA[i][j] + min(FindMinCostA(i + 1, j, n), FindMinCostA(i, j + 1, n));
}

//Simple recursion which returns the maximum cost of going from i,j to n,n
long long FindMaxCostB(int i, int j, int n)
{
    //going out of bounds
    if (i >= n)
        return 0;
    //going out of bounds
    if (j >= n)
        return 0;
    
    if (proMatrixB[i][j] != -1)
    {
        return proMatrixB[i][j];
    }
    //going down or right
    proMatrixB[i][j] = costMatrixB[i][j] + max(FindMaxCostB(i + 1, j, n), FindMaxCostB(i, j + 1, n));
}

int main()
{
    int i, j, k;
    
    // initialisation
    for (i = 0; i < sizen; i++)
    {
        for (j = 0; j < sizen; j++)
        {
            costMatrixA[i][j] = 1 + rand()% 10;
            costMatrixB[i][j] = 1 + rand()% 10;
            productMat[i][j] = 0;
		
	    //this initialisation helps to check if an element of proMatrix is computed or not(when FindCost is called)
            proMatrixA[i][j] = -1;
            proMatrixB[i][j] = -1;

        }
    }
  //reaching the last cell
    proMatrixA[sizen-1][sizen-1] = costMatrixA[sizen][sizen];
    proMatrixB[sizen-1][sizen-1] = costMatrixB[sizen][sizen];

    //Filling proMatrices
    FindMinCostA(i,j,sizen);
    FindMaxCostB(i,j,sizen);

    //creating productMat as explained in the beginning
    for (i = 0; i < sizen; i++)
    {
        for (j = 0; j < sizen; j++)
        {
            for (k = 0; k < sizen; k++)
                productMat[i][j] += proMatrixA[i][k] * proMatrixB[k][j];
			
        }
    }

    //filter of size 4 x n
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


#include <bits/stdc++.h>
#include <stdint.h>
#include <omp.h>

using namespace std;

const int sizen = 500;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ;

long long costMatrixA[sizen][sizen];
long long costMatrixB[sizen][sizen];

long long productMat[sizen][sizen];

long long proMatrixA[sizen][sizen];
long long proMatrixB[sizen][sizen];

static uint64_t const multiplier = 6364136223846793005u;

static uint64_t mcg_state = 0xcafef00dd15ea5e5u;	// Must be odd

uint32_t pcg32_fast(void)
{
	uint64_t x = mcg_state;
	unsigned count = (unsigned)(x >> 61);	// 61 = 64 - 3

	mcg_state = x * multiplier;
	x ^= x >> 22;
	return (uint32_t)(x >> (22 + count));	// 22 = 32 - 3 - 7
}

void pcg32_fast_init(uint64_t seed)
{
	mcg_state = 2*seed + 1;
	(void)pcg32_fast();
}

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
        return 0;
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
    //time_t start, end;
    int i, j, k;
    //omp_set_num_threads(4);
    
    // initialisation
    //time(&start);
    for (i = 0; i < sizen; i++)
    {
        #pragma omp parallel for
        for (j = 0; j < sizen; j++)
        {
            costMatrixA[i][j] = 1 + pcg32_fast()% 10;
            costMatrixB[i][j] = 1 + pcg32_fast()% 10;
            productMat[i][j] = 0;
            proMatrixA[i][j] = -1;
            proMatrixB[i][j] = -1;

        }
    }
  //reaching the last cell
    proMatrixA[sizen-1][sizen-1] = costMatrixA[sizen][sizen];
    proMatrixB[sizen-1][sizen-1] = costMatrixB[sizen][sizen];
    #pragma omp parallel 
 {
     #pragma omp sections
  {
      #pragma omp section
   {
          FindMinCostA(i,j,sizen);
   }
         #pragma omp section
{
        FindMaxCostB(i,j,sizen);
}
      
  }
     
 }

    //creating productMat as explained in the beginning
 // #pragma omp parallel shared (proMatrixA, proMatrixB) private (i, j, k)
 // {
 //    #pragma omp for
 //    for (i = 0; i < sizen; i++)
 //    {
 //        for (j = 0; j < sizen; j++)
 //        {
 //            for (k = 0; k < sizen; k++)
 //                productMat[i][j] += proMatrixA[i][k] * proMatrixB[k][j];
 //        }
 //    }
 // }
    
    creating productMat as explained in the beginning
    for (i = 0; i < sizen; i++)
    {
        for (j = 0; j < sizen; j++)
        {
            for (k = 0; k < sizen; k++)
                productMat[i][j] += FindMinCostA(i, k, sizen) * FindMaxCostB(k, j, sizen);
        }
    }
 
// time(&start);
    //filter of size 4 x n
    long long filterArray[4][sizen];
    for (i = 0; i < 4; i++)
    {
       
        for (j = 0; j < sizen; j++)
            filterArray[i][j] = pcg32_fast() % 2;
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
    Parallelisation using OpenMP
        https://people.sc.fsu.edu/~jburkardt/cpp_src/multitask_openmp/multitask_openmp.html

    Permuted Congruential Random Number Generator(PCG32_fast)
        https://en.wikipedia.org/wiki/Permuted_congruential_generator

    

*/

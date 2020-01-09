/*

Use the supplied SIMD SSE code to run an array multiplication timing experiment. Run the same experiment a second time using your own C/C++ array multiplication code.
Use the supplied SIMD SSE code to run an array multiplication + reduction timing experiment. Run the same experiment a second time using your own C/C++ array multiplication + reduction code.
Use different array sizes from 1K to "big". The choice of in-between values is up to you, but pick something that will make for a good graph.
You should run each array-size test a certain number of trials. Use the peak value for the performance you record.
Create a table and a graph showing SSE/Non-SSE speed-up as a function of array size. As there are two experiments (array-multiply and array-multiply-reduction) there will be two curves. Plot both curves on the same set of axes. Speedup in this case will be S = Psse/Pnon-sse = Tnon-sse/Tsse (P = Performance, T = Elapsed Time).
Note: this is not a multithreading assignment, so you don't need to worry about a NUMT.
The Y-axis performance units in this case will be "Speed-Up", i.e., dimensionless.

*/
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Contains actual calculation functions being tested
#include "simd.p4.h"    

#ifndef     ARRSIZE
#define     ARRSIZE     1000
#endif

#ifndef     NUMTRIES
#define     NUMTRIES    10
#endif

int main(int argc, char* argv[]){

	//print the array size we're running with
	printf("%d\t", ARRSIZE);

	//variables for performance
	double SSEMAX;
	double NONSSEMAX;
	double arrsize;

	//SSE
	//our SIMD array multiplication
	SSEMAX = 0;
	for(int tries = 0; tries < NUMTRIES; tries++){
		float *a = new float[ARRSIZE];
        float *b = new float[ARRSIZE];
        float *c = new float[ARRSIZE];
		
		//time
		double timeRun = omp_get_wtime();

		//call our header mult
		SimdMul(a, b, c, ARRSIZE);
		
		//calculate megafuncs
		double totalTime = omp_get_wtime() - timeRun;
		arrsize = ARRSIZE;
        double megaFuncPerSecond = arrsize / totalTime / 1000000;
        
        if (megaFuncPerSecond > SSEMAX){
            SSEMAX = megaFuncPerSecond;
        }
		
		//delete our arrays
        delete[] a;
        delete[] b;
        delete[] c;
	}



	//NON SSE
	NONSSEMAX = 0;
	//for loop for our number of tries
    for (int t = 0; t < NUMTRIES; t++){
        float *a = new float[ARRSIZE];
        float *b = new float[ARRSIZE];
        float *c = new float[ARRSIZE];
		
		
		//time
        double timeRun = omp_get_wtime();

		//call our non simd
        NonSimdMul(a, b, c, ARRSIZE);
        
		//calculate megafuncs
        double totalTime = omp_get_wtime() - timeRun;
		arrsize = ARRSIZE;
        double megaFuncPerSecond = arrsize / totalTime / 1000000;

        if (megaFuncPerSecond > NONSSEMAX){
            NONSSEMAX = megaFuncPerSecond;
        }
        delete[] a;
        delete[] b;
        delete[] c;
    }
	
	// Output the speedup for arr. mult - SSE over non-SSE
    printf("%.3lf\t", (SSEMAX / NONSSEMAX));
	
	
	//SIMD array reductions
	SSEMAX = 0;
    for (int t = 0; t < NUMTRIES; t++){
        float *a = new float[ARRSIZE];
        float *b = new float[ARRSIZE];
        float *c = new float[ARRSIZE];

        double timeRun = omp_get_wtime();

        SimdMulSum(a, b, ARRSIZE);
        
        double totalTime = omp_get_wtime() - timeRun;
		arrsize = ARRSIZE;
        double megaFuncPerSecond = arrsize / totalTime / 1000000;

        if (megaFuncPerSecond > SSEMAX){
            SSEMAX = megaFuncPerSecond;
        }
		//free the memory
        delete[] a;
        delete[] b;
        delete[] c;
    }
    // printf("%.3lf\t", SSEMAX);

    //nonSIMD Array Reduction
    NONSSEMAX = 0;
    for (int t = 0; t < NUMTRIES; t++){
        float *a = new float[ARRSIZE];
        float *b = new float[ARRSIZE];
        float *c = new float[ARRSIZE];

        double timeRun = omp_get_wtime();

        NonSimdMulSum(a, b, ARRSIZE);
        
        double totalTime = omp_get_wtime() - timeRun;
		arrsize = ARRSIZE;
        double megaFuncPerSecond = arrsize / totalTime / 1000000;

        if (megaFuncPerSecond > NONSSEMAX){
            NONSSEMAX = megaFuncPerSecond;
        }
		//free the memory
        delete[] a;
        delete[] b;
        delete[] c;
    }
    // printf("%.3lf\t", NONSSEMAX);

    // Output speedup for arr. reduce - SSE over non-SSE
    printf("%.3lf\n", (SSEMAX / NONSSEMAX));
    
    
    return 0;
	
	

}
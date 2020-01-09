#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <omp.h>
#include "tools.h"

#define NUMTHREADS          4
#define FIRST_YEAR          2019
#define LAST_YEAR           2024

int	NowYear;		// 2019 - 2024
int	NowMonth;		// 0 - 11

float NowAngle; 
float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population
int     NowNumWolves;        // number of Wolves in current population
float   DeerToWolves;        // Ratio of deer to Wolves



const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =		0.5;

const float AVG_PRECIP_PER_MONTH =		6.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				50.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;




//const float DB_EQUILIBRIUM          =       4.0;



void GrainDeer(unsigned int*);
void Grain(unsigned int*);
void Watcher(unsigned int*);

//custom methods
//wolves that eat the deer
void Wolves(unsigned int*);
//
void UpdateNows(unsigned int*);
int  currmonth(int year, int month);

int
main(int argc, char* argv[]){ 
	NowMonth    =   0;
    NowYear     =   FIRST_YEAR;

    unsigned int seedI = time(0);   // Separate seed for main & each thread
    NowNumDeer  =   6;
    NowNumWolves =   1;
    NowHeight   =   1.;
    UpdateNows(&seedI);
		//print our information per year
	    printf("Month\tPrecip\tTemp\tHeight\tDeer\tWolves\n");
		
		//set our barriers
		 omp_set_num_threads(NUMTHREADS);    // same as # decomposed functions
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            unsigned int GrainDeerSeed = time(0);
            GrainDeer(&GrainDeerSeed);
        }
        #pragma omp section
        {
            unsigned int SeedGrain = time(0);
            Grain(&SeedGrain);
        }
        #pragma omp section
        {
            unsigned int SeedWatcher = time(0);
            Watcher(&SeedWatcher);
        }
        #pragma omp section
        {
            unsigned int WolfSeed = time(0);
            Wolves(&WolfSeed);
        }
    }
    return 0;

} 

 //graindeer
 void GrainDeer(unsigned int* seedp){
    // Compute number of deer based on amount of grain
    // Increment or decrement based on available grain
    int deltaDeer;
    while(NowYear <= LAST_YEAR){
        // Account for grain height
        if (NowNumDeer > NowHeight){
            deltaDeer = -1;
        }
        else if (NowNumDeer < NowHeight){
            deltaDeer = 1;
        }
        else{
            deltaDeer = 0;
        }
        // Account for Wolves
        if (DeerToWolves > 1){
            deltaDeer -= 1;
        }
		if (DeerToWolves > 4){
            deltaDeer -= 1;
        }
        #pragma omp barrier // compute barrier

        NowNumDeer += deltaDeer;
        if (NowNumDeer < 0)
            NowNumDeer = 0;
        #pragma omp barrier // assign barrier

        #pragma omp barrier // output & update barrier
    }
}


//wolves will eat the deer, but will find food elsewhere if there are too few deer
void Wolves(unsigned int* seedp){
    int deltaWolves;
    while(NowYear <= LAST_YEAR){
        if (NowNumWolves > NowNumDeer){
            deltaWolves = -1;
        }
        else if (NowNumWolves < NowNumDeer){
            deltaWolves = 1;
        }
        else{
            deltaWolves = 0;
        }
        #pragma omp barrier //a compute barrier

        NowNumWolves += deltaWolves;
        if (NowNumWolves <= 0)
            NowNumWolves = 0;
        #pragma omp barrier //barrier

        #pragma omp barrier //the output & update barrier
    }
}

 
 void Grain (unsigned int* seedp){
	float deltaHeight;
	while(NowYear <= LAST_YEAR){
		deltaHeight = TempFactor(NowTemp, MIDTEMP) * PrecipFactor(NowPrecip, MIDPRECIP) * GRAIN_GROWS_PER_MONTH;
		deltaHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        #pragma omp barrier //a compute barrier

        NowHeight += deltaHeight;
        if (NowHeight < 0){
            NowHeight = 0;
        }
        #pragma omp barrier //barrier

        #pragma omp barrier //the ouput & update barrier
    }    
 }
 
 //watcher that prints our information
 void Watcher(unsigned int* seedp){
    while(NowYear <= LAST_YEAR){
        #pragma omp barrier //a compute barrier
        #pragma omp barrier //barrier

        // Output all of our defined globals
        printf("%d\t%.3lf\t%.3lf\t%.3lf\t%d\t%d\n",
                currmonth(NowYear, NowMonth),
                NowPrecip,
                FtoC(NowTemp),
                NowHeight,
                NowNumDeer,
                NowNumWolves);

        // Update globals
        NowMonth++;
        if (NowMonth > 11){
            NowYear++;
            NowMonth = 0;
        }
        UpdateNows(seedp);
        #pragma omp barrier // output & update barrier
    }
}

// Update state 
void UpdateDeerToWolves(){
    if (NowNumWolves <= 0){
        DeerToWolves = FLT_MAX;
    }
    else{
        DeerToWolves = (float)NowNumDeer / (float)NowNumWolves;
    }
}

void UpdateNows(unsigned int* seedp){
    NowAngle    = Angle(NowMonth);
    NowPrecip   = Precip(AVG_PRECIP_PER_MONTH,
                         AMP_PRECIP_PER_MONTH,
                         RANDOM_PRECIP,
                         NowAngle,
                         seedp);
    NowTemp     = Temp  (AVG_TEMP,
                         AMP_TEMP,
                         RANDOM_TEMP,
                         NowAngle,
                         seedp);
    UpdateDeerToWolves();
}

// Calculate exact month for graph-friendly output
int currmonth(int year, int month){
    return (year - FIRST_YEAR) * 12 + month + 1;
}
 
 

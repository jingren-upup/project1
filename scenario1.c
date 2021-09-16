//
// Created by jingren wang on 9/15/21.
//

#include <limits.h> //use INT_MAX
#include <stdlib.h> // contains rand() function
#include <stdio.h>
#include "scenario.h"
#include "func.h"


//for one time scenario
void scenario1Once(float *pElevTime, float *pAvgPasTime)
{
    int numPass = 0;
    int destination[20];
    generate(&numPass, destination);
    calculateTime(numPass, destination, pElevTime, pAvgPasTime);

}

// detail of scenario1
void scenario1()
{
    //original data for once
    float eletime= 0, Ave_PasTime = 0;
    float minTimeElev = INT_MAX; //minimum total time
    float maxTimeElev = 0;       //maximum total time
    //final result
    float avgElevTime = 0, avgPasTime_1000 = 0;
//    int allTimeElev = 0;       //all total time
//    double allAvgPasTime = 0;  //all average passenger time
    // calculate 1000 times
    for(int i = 0; i < 1000; ++i){
        scenario1Once(&eletime, &Ave_PasTime);
        if (minTimeElev > eletime){
            minTimeElev = eletime;
        }
        if (eletime > maxTimeElev){
            maxTimeElev = eletime;
        }

        avgElevTime += avgElevTime;
        avgPasTime_1000 += Ave_PasTime;
    }

    avgElevTime = avgElevTime/1000;
    avgPasTime_1000 = avgPasTime_1000/1000;

    printf("the average time  after iterations  is: %.4f\n",  avgElevTime);
    printf("the minumum time  after iterations  is: %d\n",  minTimeElev);
    printf("the maximum time after iterations is: %d\n", maxTimeElev);
    printf("the average time per passenger after iterations: %.4f\n", avgPasTime_1000);

}
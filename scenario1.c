//
// Created by jingren wang on 9/15/21.
//

#include <limits.h> //use INT_MAX
#include <stdlib.h> // contains rand() function
#include <stdio.h>
#include "scenario.h"
#include "func.h"


//for one time scenario
void scenario1Once(float *perEleTime, float *perAvgPassTime)
{
    int numPass = 0;
    int destination[20];
    generate(&numPass, destination);
    calculateTime(numPass, destination, perEleTime, perAvgPassTime);



}

// detail of scenario1
void scenario1()
{
    //original data for once
    float eletime= 0;
    float Ave_PasTime = 0;
    //minimum total time
    int minTimeElev = INT_MAX;
    //maximum total time
    int maxTimeElev = 0;
    //final result
    float avgElevTime = 0, avgPasTime_1000 = 0;
    // calculate 1000 times
    for(int i = 0; i < 1000; ++i){
        scenario1Once(&eletime, &Ave_PasTime);
        if (minTimeElev > eletime && eletime != 0){
            minTimeElev = eletime;


        }
        if (eletime > maxTimeElev){
            maxTimeElev = eletime;
        }

        avgElevTime += eletime;
        avgPasTime_1000 += Ave_PasTime;

    }

    avgElevTime = avgElevTime/1000;
    avgPasTime_1000 = avgPasTime_1000/1000;
    printf("\nScenario1:\n");
    printf("the average time  after iterations  is: %.4f\n",  avgElevTime);
    printf("the minumum time  after iterations  is: %d\n",  minTimeElev);
    printf("the maximum time after iterations is: %d\n", maxTimeElev);
    printf("the average time per passenger after iterations: %.4f\n", avgPasTime_1000);

}
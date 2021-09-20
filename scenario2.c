//
// Created by 王敬仁 on 9/15/21.
//

#include <limits.h> //use INT_MAX
#include <stdlib.h> // contains rand() function
#include <stdio.h>

#include "scenario.h"
#include "func.h"

// two elevator
int elev1[18], elev2[18];

// passenger of two elevators
int count1 = 0, count2 = 0;

void scenario2Once(float *perEleTime, float *perAvgPassTime){
    //total capacity 1-18
     int numPass = 0;
     int destination[18];
    //total destination and generate it
    generate(&numPass,destination);

    count1 = 0;
    count2 = 0;
    // assign passengers to two elevators randomly
    for (int i = 0; i < numPass; ++i)
    {
        if (rand() % 2 == 1)
        {
            elev1[count1++] = destination[i];
        }
        else
        {
            elev2[count2++] = destination[i];
        }
    }
    //two elevator time
    float elevTime1 = 0, elevTime2 = 0;
    //two passenger time
    float avgPasTime1 = 0, avgPasTime2 = 0;
    //calculate it
    calculateTime(count1,elev1,&elevTime1,&avgPasTime1);
    calculateTime(count2, elev2, &elevTime2, &avgPasTime2);
    //get max value
    if (elevTime1>elevTime2){
        *perEleTime = elevTime1;
    }else{
        *perEleTime = elevTime2;
    }
    *perAvgPassTime = (avgPasTime1 * count1 + avgPasTime2 * count2) / numPass;
    if (*perEleTime < 3){
        *perEleTime = 3;
    }



}


void scenario2(){
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
        scenario2Once(&eletime, &Ave_PasTime);

        if (minTimeElev > eletime){
            minTimeElev = eletime;

        }
        if (eletime > maxTimeElev){
            maxTimeElev = eletime;
        }

        avgElevTime += eletime;
        avgPasTime_1000 = avgPasTime_1000 + Ave_PasTime;

    }

    avgElevTime = avgElevTime/1000;
    avgPasTime_1000 = avgPasTime_1000/1000;
    printf("\nScenario2:\n");
    printf("the average time  after iterations  is: %.4f\n",  avgElevTime);
    printf("the minumum time  after iterations  is: %d\n",  minTimeElev);
    printf("the maximum time after iterations is: %d\n", maxTimeElev);
    printf("the average time per passenger after iterations: %.4f\n", avgPasTime_1000);

}
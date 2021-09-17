//
// Created by jingren wang on 9/16/21.
//

#include <stdlib.h>
#include "func.h"

// compare func for quick sort
int cmpfunc(const void *a, const void *b)
{
    // for sorting
    return (*(int *)a - *(int *)b);
}

// generate the passengers and destinations
void generate(int *pNumPassenger, int destination[])
{

    int numPassenger = rand()%18 +1; // 1-18
//    while(numPassenger==0){
//        numPassenger = rand()%18 +1;
//    }


    // generate destination floor for all passengers
    for (int i = 0; i < numPassenger; i++)
    {
        destination[i] = rand() % floors + 1; // 1-20
    }

    // sorting destinations
    qsort(destination, numPassenger, sizeof(int), cmpfunc);

    // store the value and give out
    *pNumPassenger = numPassenger;
}
// generate 2 elevators'people
void generate2(int *pNumPassenger, int destination[])
{
    int numPassenger = rand() % capacity2 + 1; // 1-36

    // generate destination floor for all passengers
    for (int i = 0; i < numPassenger; i++)
    {
        destination[i] = rand() % floors + 1; // 1-20
    }

    // sorting destinations
    qsort(destination, numPassenger, sizeof(int), cmpfunc);

    // store the value and give out
    *pNumPassenger = numPassenger;
}

// calculate the elevator running time
// and input should be passenger number, an array of destination floors
// and the empty elevator running time， the empty  passenger time
// output should return the  pointer to elevator run time, pointer to average passenger time
void calculateTime(int numPassenger, int destination[], float *ElevTime, float *AvgPasTime)
{
    // judge if the passenger number is 0
    if(numPassenger == 0)
    {
//        *AvgPasTime = 0;
//        *ElevTime = 0;
        return;
    }

    // elevator's running time and it will be return later
    float elevTime = destination[numPassenger - 1] * movePerFloorTime;
    // per passenger's time cost
    float *timeIdv = (float *)malloc(numPassenger * sizeof(float));
    // time cost of the first passenger to leave
    timeIdv[0] = destination[0] * movePerFloorTime;
    // num of times that the elevator stopped
    int timesStopped = 1;
    // average passenger time cost
    float avgPasTime = 0;

    for (int i = 1; i < numPassenger; i++)
    {
        if (destination[i] != destination[i - 1])
        {
            // if arrive at a new floor
            timeIdv[i] = destination[i] * movePerFloorTime +  timesStopped * stopTime;
            timesStopped += 1;
        }
        else
        {
            // multiple people arriving at the same floor
            timeIdv[i] = timeIdv[i-1];
        }
        // add the value of individual
        avgPasTime += timeIdv[i];
    }

    // total elevator time
    elevTime += (timesStopped - 1) * stopTime;
    // final average passenger time
    avgPasTime = avgPasTime / numPassenger;
    //store the result
    *AvgPasTime = avgPasTime;
    *ElevTime = elevTime;
    //release the time idv
    free(timeIdv);
}
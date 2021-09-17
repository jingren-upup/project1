//
// Created by Weigang Ning  on 9/16/21.
//

#include <stdlib.h>
#include "func.h"

// compare func for quick sort
int cmpsort(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b); // for sorting
}

// generate the passengers and destinations
void generate(int *pPassengerNum, int destination[])
{
    int numOfPassenger = rand() % capacity + 1; // 1-18

    // generate destination floor for all passengers
    for (int i = 0; i < numOfPassenger; i++)
    {
        destination[i] = rand() % floors + 1; // 1-20
    }

    // sorting destinations
    qsort(destination, numOfPassenger, sizeof(int), cmpsort);

    // pass the value out
    *pPassengerNum = numOfPassenger;
}

// calculate the elevator running time
// and input should be passenger number, an array of destination floors and the empty elevator running time and the empty
// and output should return the  pointer to elevator run time, pointer to average passenger time
void calculateTime(int numOfPassenger, int destination[], float *ElevTime, float *AvgPasTime)
{
    // judge if the passenger number is 0 or null
    if(numOfPassenger == 0)
    {
        *AvgPasTime = 0;
        *ElevTime = 0;
        return;
    }

    // elevator's running time
    float elevTime = destination[numOfPassenger - 1] * movePerFloorTime;
    // per passenger's time cost
    float *timeIdv = (float *)malloc(numOfPassenger * sizeof(float));
    // time cost of the fisrt passenger to leave
    timeIdv[0] = destination[0] * movePerFloorTime;
    // num of times that the elevator stopped
    int timesStopped = 1;
    // average passenger time cost
    float avgPasTime = 0;

    for (int i = 1; i < numOfPassenger; i++)
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
            timeIdv[i] = timeIdv[i - 1];
        }
        // add the value of ind
        avgPasTime += timeIdv[i];
    }

    // total elev time
    elevTime += (timesStopped - 1) * stopTime;
    // final average passenger time
    avgPasTime = avgPasTime / numOfPassenger;
    //store the result
    *AvgPasTime = avgPasTime;
    *ElevTime = elevTime;
    //release the time idv
    free(timeIdv);
}
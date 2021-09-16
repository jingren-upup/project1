//
// Created by jingren wang on 9/16/21.
//

#include <stdlib.h>
#include "func.h"

// compare func for quick sort
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b); // for sorting
}

// generate the passengers and destinations
void generate(int *pNumPassenger, int destination[])
{
    int numPassenger = rand() % capacity + 1; // 1-18

    // generate destination floor for all passengers
    for (int i = 0; i < numPassenger; i++)
    {
        destination[i] = rand() % floors + 1; // 1-20
    }

    // sorting destinations
    qsort(destination, numPassenger, sizeof(int), cmpfunc);

    // pass the value out
    *pNumPassenger = numPassenger;
}

// calculate the elevator running time
// and input should be passenger number, an array of destination floors and the empty elevator running time and the empty
// and output should return the  pointer to elevator run time, pointer to average passenger time
void calculateTime(int numPassenger, int destination[], float *pElevTime, float *pAvgPasTime)
{   // judge if the passenger number is 0 or null
    if(numPassenger == 0 || numPassenger == NULL)
    {
        *pAvgPasTime = 0;
        *pElevTime = 0;
        return;
    }

    float elevTime = destination[numPassenger - 1] * movePerFloorTime; // elevator's running time
    float *timeIdv = (float *)malloc(numPassenger * sizeof(float));        // individual passenger's time cost
    timeIdv[0] = destination[0] * movePerFloorTime;                  // time cost of the fisrt passenger to leave
    int timesStopped = 1;                                            // num of times that the elevator stopped
    float avgPasTime = 0;                                              // average passenger time cost

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
            timeIdv[i] = timeIdv[i - 1];
        }
        avgPasTime += timeIdv[i];
    }

    elevTime += (timesStopped - 1) * stopTime; // total elev time
    avgPasTime = avgPasTime / numPassenger;    // final average passenger time

    *pAvgPasTime = avgPasTime;
    *pElevTime = elevTime;

    free(timeIdv);
}
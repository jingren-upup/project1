//
// Created by jingren wang on 9/16/21.
//
#include <limits.h>
#include <printf.h>
#include "func.h"
#include "stdlib.h"
// two elevator
int elev1[18], elev2[18];

//global variable for 1000 times to calculate the optimistic floor
float MinElevatorTime = 65537, MaxElevatorTime = 0, AvgElevatorTime = 0, PassengerTime = 0;

// passenger of two elevators
int count3 = 0, count4 = 0;


// for one cycle elevators
void scenario3Once(float *pElevTime, float *pAvgPasTime,int maxFloor1) {
    //total capacity 1-18
    int numPass = 0;
    int destination[18];
    //total destination and generate it
    generate(&numPass,destination);

    count3 = 0;
    count4 = 0;
    // assign passengers to two elevators randomly
    for (int i = 0; i < numPass; ++i)
    {
        if (destination[i]<=maxFloor1)
        {
            elev1[count3++] = destination[i];
        }
        else
        {
            elev2[count4++] = destination[i];
        }
    }
    //two elevator time
    float elevTime1 = 0, elevTime2 = 0;
    //two passenger time
    float avgPasTime1 = 0, avgPasTime2 = 0;
    //calculate it
    calculateTime(count3,elev1,&elevTime1,&avgPasTime1);
    calculateTime(count4, elev2, &elevTime2, &avgPasTime2);
    //get max value
    if (elevTime1>elevTime2){
        *pElevTime = elevTime1;
    }else{
        *pElevTime = elevTime2;
    }
    *pAvgPasTime = (avgPasTime1*count3+avgPasTime2*count4) / numPass;
    if (*pElevTime<3){
        *pElevTime = 3;
    }
}

// for 1000 times cycle the elevators
void scenario3(int maxFloor1){
    //original data for once
    float eletime= 0;
    float Ave_PasTime = 0;
    //minimum total time
    MinElevatorTime = INT_MAX;
    //maximum total time
    MaxElevatorTime = 0;
    //final result
    AvgElevatorTime = 0, PassengerTime = 0;
    // calculate 1000 times
    for(int i = 0; i < 1000; ++i){
        scenario3Once(&eletime, &Ave_PasTime,maxFloor1);

        if (MinElevatorTime > eletime){
            MinElevatorTime = eletime;

        }
        if (eletime > MaxElevatorTime){
            MaxElevatorTime = eletime;
        }

        AvgElevatorTime += eletime;
        PassengerTime = PassengerTime + Ave_PasTime;

    }

    AvgElevatorTime = AvgElevatorTime / 1000;
    PassengerTime = PassengerTime / 1000;



}
// calculate the Max floor
void findS3MaxFloor(){
    // optimistic result ini
    float OptelevatorTime = INT_MAX, OptpassengerTime = INT_MAX, OptMaxTime = INT_MAX;
    // for different result floor
    int optFloor = 1, optMaxFloor = 1, avgFloor = 1;

    for (int floor1 = 1; floor1 <= 20; floor1++) {
        scenario3(floor1);
        //if find the op result for better average passenger
        if (PassengerTime < OptpassengerTime)
        {
            OptpassengerTime = PassengerTime;
            avgFloor = floor1;
        }
        //if find the op result for better average elevator running time
        if (AvgElevatorTime < OptelevatorTime)
        {
            OptelevatorTime = AvgElevatorTime;
            optFloor = floor1;
        }
        //if find the op result for better Max elevator running time
        if (MaxElevatorTime < OptMaxTime)
        {
            OptMaxTime = MaxElevatorTime;
            optMaxFloor = floor1;
        }
    }
    printf("for the optimized total elevator time, the maxFloor1 is:%d\nand the total elevator time is: %3f\n", optFloor, OptelevatorTime);
    printf("for the optimized max elevator time, the maxFloor1 is:%d\nand the max elevator time is: %3f\n", optMaxFloor, MaxElevatorTime);
    printf("for the optimized average passenger elevator time, optimized maxFloor1 is:%d\nand the average passenger time is: %3f\n", avgFloor, OptpassengerTime);

}
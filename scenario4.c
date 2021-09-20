//
// Created by jingren wang on 9/16/21.
//
#include <limits.h>
#include <printf.h>
#include "func.h"
#include "stdlib.h"
// three elevator
int elev1[18], elev2[18], elev3[18];

//global variable for 1000 times to calculate the optimistic floor
float MinElevatorTime1 = 65537, MaxElevatorTime1 = 0, AvgElevatorTime1 = 0, PassengerTime1 = 0;

// passenger of two elevators
int count5 = 0, count6 = 0,count7 = 0;


// for one cycle elevators
void scenario4Once(float *perEleTime, float *perAvgPassTime, int maxFloor1, int maxFloor2) {
    //total capacity 1-18
    int numPass = 0;
    int destination[18];
    //total destination and generate it
    generate(&numPass,destination);

    count5 = 0, count6 = 0,count7 = 0;
    // assign passengers to two elevators randomly
    for (int i = 0; i < numPass; ++i)
    {
        if (destination[i]<=maxFloor1)
        {
            elev1[count5++] = destination[i];
        }
        else if(destination[i] <=maxFloor2)
        {
            elev2[count6++] = destination[i];
        } else{
            elev3[count7++] = destination[i];
        }
    }
    //two elevator time
    float elevTime1 = 0, elevTime2 = 0, elevTime3 = 0;
    //two passenger time
    float avgPasTime1 = 0, avgPasTime2 = 0, avgPasTime3 = 0;
    //calculate it
    calculateTime(count5,elev1,&elevTime1,&avgPasTime1);
    calculateTime(count6, elev2, &elevTime2, &avgPasTime2);
    calculateTime(count7, elev3, &elevTime3, &avgPasTime3);
    //get max value
    float  temp = 0;
    if (elevTime1>elevTime2){
       temp = elevTime1;
    }else{
        temp = elevTime2;
    }
    if (temp>elevTime3){
        *perEleTime = temp;
    }else{
        *perEleTime = elevTime3;
    }

    *perAvgPassTime = (avgPasTime1 * count5 + avgPasTime2 * count6 + avgPasTime3 * count7) / numPass;
    if (*perEleTime < 3){
        *perEleTime = 3;
    }
}

// for 1000 times cycle the elevators
void scenario4(int maxFloor1,int maxFloor2){
    //original data for once
    float eletime= 0;
    float Ave_PasTime = 0;
    //minimum total time
    MinElevatorTime1 = INT_MAX;
    //maximum total time
    MaxElevatorTime1 = 0;
    //final result
    AvgElevatorTime1 = 0, PassengerTime1 = 0;
    // calculate 1000 times
    for(int i = 0; i < 1000; ++i){
        scenario4Once(&eletime, &Ave_PasTime,maxFloor1,maxFloor2);

        if (MinElevatorTime1 > eletime){
            MinElevatorTime1 = eletime;
        }
        if (eletime > MaxElevatorTime1){
            MaxElevatorTime1 = eletime;
        }

        AvgElevatorTime1 += eletime;
        PassengerTime1 = PassengerTime1 + Ave_PasTime;

    }

    AvgElevatorTime1 = AvgElevatorTime1 / 1000;
    PassengerTime1 = PassengerTime1 / 1000;



}
// calculate the Max floor
void findS4MaxFloor(){
    // optimistic result ini
    float OptelevatorTime = INT_MAX, OptpassengerTime = INT_MAX, OptMaxTime = INT_MAX;
    // for different result floor
    int optFloor1 = 1, optMaxFloor1 = 1, avgFloor1 = 1;
    int optFloor2 = 2, optMaxFloor2 = 2, avgFloor2 = 2;
    for (int floor1 = 1; floor1 <= 20; floor1++) {
        for (int floor2 = floor1+1; floor2 <=20 ; ++floor2) {
            scenario4(floor1,floor2);
            //if find the op result for better average passenger
            if (PassengerTime1 < OptpassengerTime)
            {
                OptpassengerTime = PassengerTime1;
                avgFloor1 = floor1;
                avgFloor2 = floor2;

            }
            //if find the op result for better average elevator running time
            if (AvgElevatorTime1 < OptelevatorTime)
            {
                OptelevatorTime = AvgElevatorTime1;
                optFloor1 = floor1;
                optFloor2 = floor2;
            }
            //if find the op result for better Max elevator running time
            if (MaxElevatorTime1 < OptMaxTime)
            {
                OptMaxTime = MaxElevatorTime1;
                optMaxFloor1 = floor1;
                optMaxFloor2 = floor2;
            }
        }
    }
    printf("\nScenario4:\n");
    printf("for the optimized total elevator time, the maxFloor1 is:%d\nthe maxFloor2 is:%d\nand the total elevator time is: %3f\n", optFloor1,optFloor2,OptelevatorTime);
    printf("for the optimized max elevator time, the maxFloor1 is:%d\nthe maxFloor2 is:%d\nand the max elevator time is: %3f\n", optMaxFloor1,optMaxFloor2,MaxElevatorTime1);
    printf("for the optimized average passenger elevator time, optimized maxFloor1 is:%d\noptimized maxFloor2 is:%d\nand the average passenger time is: %3f\n", avgFloor1,avgFloor2 ,OptpassengerTime);

}
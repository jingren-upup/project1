////
//// Created by 王敬仁 on 9/15/21.
////
//
//#include <limits.h> //use INT_MAX
//#include <stdlib.h> // contains rand() function
//#include <stdio.h>
//
//#include "scenario.h"
//#include "tool.h"
//
//
//const int capacity2 = 36;        //Maximum number of people two elevator can fit
//const int floors2 = 20;          //Number of floors above the ground floor
//const int stopTime2 = 15;        //Total time for an elevator to stop on a visited floor (in seconds)
//const int movePerFloorTime2 = 3; //Time for the elevator to move one floor (in seconds)
//
//// two elevator
//int elev1[18], elev2[18];
//
//// two pointer
//int cnt1 = 0, cnt2 = 0;
//
//void scenario2Once(int *timeElevArray, float *avgPasTime, int index){
//    //total capacity 1-36
//    const int numPass = rand() % capacity2 + 1;
//    //total destination
//    int *destination =  (int *)malloc(sizeof(int) * numPass);
//
//    //generate random destination
//    for (int i = 0; i < numPass; i++)
//    {
//
//        destination[i] = rand() % floors2 + 1;
//    }
//
//    // assign passengers to two elevators randomly
//    for (int i = 0; i < numPass; i++)
//    {
//        if (rand() % 2 == 1 && cnt1 < 18)
//        {
//            elev1[cnt1] = destination[i];
//            cnt1++;
//        }
//        else if (rand() % 2 == 0 && cnt2 < 18)
//        {
//            elev2[cnt2] = destination[i];
//            cnt2++;
//        } else{
//            break;
//        }
//    }
//
//    qsort(elev1, cnt1+1, sizeof(int), cmpfunc);
//    qsort(elev2, cnt2+1, sizeof(int), cmpfunc);
//
//    // calculate time elevator running time
//    int time_elevator1 = elev1[cnt1] * movePerFloorTime2;
//    int time_elevator2 = elev2[cnt2] * movePerFloorTime2;
//    // time for each person
//    int *time_per1 = (int *)malloc(sizeof(int) * (cnt1+1));
//    int *time_per2 = (int *)malloc(sizeof(int) * (cnt2+1));
//    // time for per guy
////    time_per1[0] = elev1[0] * movePerFloorTime2;
////    time_per2[0] = elev2[0] * movePerFloorTime2;
//
//    // total pass time
//    int passTime1 =  time_per1[0];
//    int passTime2 =  time_per2[0];
//    //average pass time
//
//    //times for stop
//    int timesStopped1 = 0, timesStopped2 = 0;
//
//    //time for ele1
//    for (int i = 0; i <= cnt1; ++i) {
//        if (elev1[i] != elev1[i-1]){
//            //move to another store
//            time_per1[i] = ((elev1[i] - elev1[i-1])* movePerFloorTime2 + stopTime2 + time_per1[i-1]);
//            timesStopped1++;
//        } else{
//            time_per1[i] = time_per1[i-1];
//        }
//        passTime1 += time_per1[i];
//    }
//    //time for ele2
//    for (int i = 0; i <= cnt2; ++i) {
//        if (elev2[i] != elev2[i-1]){
//            //move to another store
//            time_per2[i] = ((elev2[i] - elev2[i-1])* movePerFloorTime2 + stopTime2 + time_per2[i-1]);
//            timesStopped2++;
//        } else{
//            time_per2[i] = time_per2[i-1];
//        }
//        passTime2 += time_per2[i];
//    }
//
//    //time to stop for 2 elevator
//    time_elevator1 += timesStopped1 * stopTime2;
//    time_elevator2 += timesStopped2 * stopTime2;
//
//    //average time for person for per ele
//
//    //store result
//    if (time_elevator1>time_elevator2){
//        timeElevArray[index] = time_elevator1;
//    }else{
//        timeElevArray[index] = time_elevator2;
//    }
//    avgPasTime[index] = (passTime1 + passTime2)/50;
//
//
//
//}
//
//
//void scenario2(){
//    float avgPasTimeArray[1000];
//    int timeElevArray[1000];
//
//    int minTimeElev = INT_MAX; //minimum total time
//    int maxTimeElev = 0;       //maximum total time
//    int allTimeElev = 0;       //all total time
//    double allAvgPasTime = 0;  //all average passenger time
//    // calculate 1000 times
//    for(int i = 0; i < 1000; ++i){
//        scenario2Once(timeElevArray, avgPasTimeArray,i);
//        if (minTimeElev>timeElevArray[i]){
//            minTimeElev = timeElevArray[i]/5;
//        }
//        if (timeElevArray[i]>maxTimeElev){
//            maxTimeElev = timeElevArray[i];
//        }
//
//        allTimeElev += timeElevArray[i];
//        allAvgPasTime += avgPasTimeArray[i];
//    }
//
//    printf("the average time  after iterations  is: %.4f\n",  allTimeElev / 1000.0);
//    printf("the minumum time  after iterations  is: %d\n",  minTimeElev);
//    printf("the maximum time after iterations is: %d\n", maxTimeElev);
//    printf("the average time per passenger after iterations: %.4f\n", allAvgPasTime / 1000.0);
//
//
//}
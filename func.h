//
// Created by jinreng wang on 9/16/21.
#define  capacity  18;        //Maximum number of people a single elevator can fit
#define  floors  20;          //Number of floors above the ground floor
#define  stopTime  15;        //Total time for an elevator to stop on a visited floor (in seconds)
#define movePerFloorTime  3; //Time for the elevator to move one floor (in seconds)

void  calculateTime(int numPassenger, int destination[], float *pElevTime, float *pAvgPasTim);
void generate(int *pNumPassenger, int destination[]);
int cmpfunc(const void *a, const void *b);

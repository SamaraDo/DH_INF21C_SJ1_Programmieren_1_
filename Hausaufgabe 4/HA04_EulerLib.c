#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HA04_EulerLib.h"

#define NUMOFSTATES 2


void RHS_MSD(double*rhs, double*y){ // mass spring damper

    double m = 1.0; // mass of object
    double c = 2.0; // feder constant
    double d = 3.0; // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/

    /* YOUR CODE HERE */
    rhs[0] = v; 
    rhs[1] = -1 * ((d/m)*v + (c/m)*x); 
    /* ---------------*/

}

void eulerSettings_MSD(simHandle* handle){

    /*num of states*/

    /* YOUR CODE HERE */
    handle->numOfStates = NUMOFSTATES;
    /* ---------------*/

    
    /*right hand site*/
    
    /* YOUR CODE HERE */
    handle->f = &RHS_MSD;
    /* ---------------*/

    
    /*reserve storage for init state vec*/
    
    /* YOUR CODE HERE */
    handle->stateVecInit = (double*)malloc(sizeof(double) * (handle->numOfStates));
    /* ---------------*/ 
    
    /*get user defined Simtime*/

    /* YOUR CODE HERE */
    double isNumber = 1;
    int isRight = 0;
    printf("Simtime (in s): \n (Please type in a number between 1 and 500)\n");
    isNumber = scanf("%lf", &(handle->simTime));
    if(1 <= handle->simTime && handle->simTime < 501){isRight = 1;}
    while(isNumber == 0 || isRight == 0)
    {
        printf("Please type in a number between 1 and 500\n");
        fflush(stdin);
        isNumber = scanf("%lf", &(handle->simTime));
        if(1 <= handle->simTime && handle->simTime < 501){isRight = 1;}
    }

    /* ---------------*/

    /*get user defined StepSize*/

    /* YOUR CODE HERE */
   isRight = 0;
    printf("StepSize (in s): \n (Please type in a number larger than 0 and smaller than the SimTime)\n");
    isNumber = scanf("%lf", &(handle->stepSize));
    if( handle->simTime > handle->stepSize + 1 && handle->stepSize > 0){isRight = 1;}
    while(isNumber == 0 || isRight == 0)
    {
        printf("Please type in a number larger than 0 and smaller than the SimTime\n");
        fflush(stdin);
        isNumber = scanf("%lf", &(handle->stepSize));
        if( handle->simTime > handle->stepSize + 1 && handle->stepSize > 0){isRight = 1;}
    }
    /* ---------------*/
    
    /*get init state position*/

    /* YOUR CODE HERE */
    printf("position(t = 0): \n (Please type in a number)\n");
    isNumber = scanf("%lf", handle->stateVecInit);
    while(isNumber == 0)
    {
        printf("Please type in a number\n");
        fflush(stdin);
        isNumber = scanf("%lf", handle->stateVecInit);
    }
    /* ---------------*/

    /*get init state speed*/

    /* YOUR CODE HERE */
    printf("speed(t = 0): \n (Please type in a number)\n");
    isNumber = scanf("%lf", handle->stateVecInit+1);
    while(isNumber == 0 )
    {
        printf("Please type in a number\n");
        fflush(stdin);
        isNumber = scanf("%lf", handle->stateVecInit+1);
    }
    /* ---------------*/

    /*reserve storage for states and derivatives*/
    
    /* YOUR CODE HERE */
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);
    handle->stateVec = (double*)malloc(sizeof(double) * (integratorSteps)*2); 
    /* ---------------*/

    /*init states and derivatives with zero*/
    
    /* YOUR CODE HERE */
    handle->derivStateVec = (double*)malloc(sizeof(double) * (integratorSteps)*2);  
    /* ---------------*/
}

void eulerForward(simHandle* handle){ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);

    /*write init states*/
    for(int i = 0; i < numOfStates; i++){
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for(int i = 0; i < integratorSteps; i++){
        /*get derivatives*/

        /* YOUR CODE HERE */
        handle->f ((handle->derivStateVec+2*i), (handle->stateVec+2*i)); 

        for(int j = 0; j < numOfStates; j++){
        /*euler step*/
        
        /* YOUR CODE HERE */
        *(handle->stateVec + 2*(i+1)+j) = *(handle->stateVec + 2*i+j) + (handle->stepSize) * *(handle->derivStateVec + 2*i+j);
        /* ---------------*/
       }
        /* ---------------*/   
    }

}

void showResults_MSD(simHandle* handle){

    /*print data to text file*/

    /* YOUR CODE HERE */
    char filename[] = "results.txt";
    FILE *filepointer;
    filepointer = fopen(filename, "w");

    if(filepointer == NULL){
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);
    for(int i = 0; i < integratorSteps; i++)
    {
        fprintf(filepointer, "%lf", handle->stepSize*i);
        fprintf(filepointer, "\t");
        for(int j = 0; j < handle->numOfStates; j++)
        {
        fprintf(filepointer, "%lf", *(handle->stateVec+2*i+j));
        fprintf(filepointer, "\t");  
        }
        fprintf(filepointer, "\n");
    } 
    fclose(filepointer);
    free(handle->stateVecInit);
    free(handle->stateVec);
    free(handle->derivStateVec);
    /* ---------------*/

    /*call gnuplot*/
    
    /* YOUR CODE HERE */
    FILE *gnuPlotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuPlotPipe, "set title 'Simulation of a Spring-Damper-System'\n");
    fprintf(gnuPlotPipe, "set xlabel 'TIME'\n");
    fprintf(gnuPlotPipe, "plot 'results.txt' using 1:2 title 'POSITION' with lines, 'results.txt' using 1:3 title 'SPEED' with lines\n");
    fprintf(gnuPlotPipe, "exit");
    fclose(gnuPlotPipe);
    /* ---------------*/
}

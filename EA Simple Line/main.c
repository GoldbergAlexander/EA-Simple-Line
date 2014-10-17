//
//  main.c
//  EA Simple Line
//
//  Created by Alexander Goldberg on 10/16/14.
//  Copyright (c) 2014 Alexander Goldberg. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 @params genePool[100][5]
 
*/

double arrayOfValues[100];
double genePool[100][5];
double genesis(double array[100][5]);
double fitness(double array[5]);
int initArrayOfValues(double array[100]);
double sortArray(double array[100][5]);
double makeChild(double array[100][5]);

int main(int argc, const char * argv[]) {
    time_t t;
    srand(time(&t));
    initArrayOfValues(arrayOfValues);
    genesis(genePool);
    
    sortArray(genePool);
    //Printing Init Gene Pool
    for (int i = 0; i < 100; i++) {
        printf("Set of Five:\n");
        for (int j = 0; j < 5 ; j++) {
            printf(" %f ", genePool[i][j]);
        }
        printf("Fitness is: %f\n", fitness(genePool[i]));
    }
    
    int i = 0;
    while (fitness(genePool[0]) != 0) {

        sortArray(genePool);
            makeChild(genePool);
            printf("[%d]Current Best: %2fx^4 + %2fx^3 + %2fx^2 + %2fx + %2f and has a fitness of: %f\n",i,
                   genePool[0][4],genePool[0][3], genePool[0][2], genePool[0][1], genePool[0][0], fitness(genePool[0]));
        i++;
        
    }
    
    
}

int initArrayOfValues(double array[100]){
    
    for (int i = 0; i< 100; i++) {
        array[i] = ((3*(i*i*i*i))+(2*(i*i*i)) + (4*(i*i)) + i + 6);
    }
    
    return 0;
}


//function solve
// ax^4 + bx^3 + cx^2 + dx^1 + ex^0
//string mutations = abcde
//fitenes will plugin and evalutate

double genesis(double array[100][5]){
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 5; j++) {
                int random = (rand()%10);
                genePool[i][j] = random;
        }
    }
    
    return 0;
}

double fitness(double array[5]){
    double fit = 0;
    for (int i = 0; i < 100; i++) {
    double result = ((array[4])*((i*i*i*i))) + ((array[3])*(i*i*i)) + ((array[2])*(i*i)) + ((array[1])*i) + array[0];
        if (result > arrayOfValues[i]) {
            fit = fit + (result - arrayOfValues[i]);
        } else {
            fit = fit + (arrayOfValues[i] - result);
        }
            
    }
    fit = fit/100;
    fit = fit*fit;
    return fit;
}

double sortArray(double array[100][5]){
    
    for (int a = 0; a < 100; a++) {
        int temp[5];
        for (int i = 0; i < (100-a); i++) {
            if(fitness(genePool[i]) >  fitness(genePool[i+ 1])){
                for (int j = 0; j < 5; j++){
                    temp[j] = genePool[i][j];
                }
                for (int j = 0; j < 5; j++){
                    genePool[i][j] = genePool[i+1][j];
                }
                for (int j = 0; j < 5; j++){
                    genePool[i+1][j] = temp[j];
                }
            }

            }
        }
    
    return 0;
}

double makeChild(double array[100][5]){
    
    int parentOne = (drand48()*drand48()*100);
    int parentTwo = (drand48()*drand48()*100);
    
    int splicePoint = (rand()%5);
    
    double child[5];
    
    //Crossover
    for (int i = 0; i < splicePoint; i++) {
        child[i] = array[parentOne][i];
    }
    for (int i = splicePoint; i < 5; i++) {
        child[i] = array[parentTwo][i];
    }
    
    
    //Mutation
    if ((rand()%100) > 50) {
        int mutaPoint = (rand()%5);
        if (child[mutaPoint] > 9) {
            child[mutaPoint] = 9;
        } else if (child[mutaPoint] < 1){
            child[mutaPoint] = 1;
        } else {
            child[mutaPoint] = (rand()%11);
        }
        
    }
    
    if (fitness(child) < fitness(genePool[99])) {
        for (int i = 0; i < 5; i++) {
            genePool[99][i] = child[i];
        }
    }
    
    return 0;
}


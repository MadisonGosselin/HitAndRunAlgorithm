#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

int main (void) {

  FILE *outputS = fopen("outputS.txt", "w"); //open a file to hold s values
  FILE *outputX = fopen("outputX.txt", "w"); //open a file to hold the x values
  FILE *outputXPosXNeg = fopen("outputXPosXNeg.txt", "w"); //open a file to hold the xPos and xNegs
  if (outputS == NULL || outputX == NULL || outputXPosXNeg == NULL){
    printf("Error opening file!\n");
    exit(1);
  }//close if statement that contains fail safe for file search


  srand(time(0)); //gets computers inner clock value to generate random numbers
  double dot_product(double v1[], double v2[], int n); //declares dot product function
  double randStep = 0; //declares variable thats used in the calculations to find a new x
  double sigma[5][100]; //declares how many sigmas there are and how many randitions of each there will be
  double p = 5; //declared a variable to change the value
  double b[5] = {2, 6, p, 0, 0}; //declares an array to hold the b values of the sigma equations
  double a[5][2] = { {-1,1}, {1,1}, {1,0}, {0,-1},{-1,0} }; //declares a double array to hold all the a values
  double aRow[2]; //declares a variable to determine which variable is 
  double x[2] = {1, 1}; //declares the x values being used
  double sigmaPos = 0, sigmaNeg = 0; //declares variables that will hold lowest pos highest neg sigma values
  int kPos, kNeg; //declares values that will hold the position in the array of the lowest pos highest neg
  double xPos[2], xNeg[2]; //declares values that will find the x on the boundaries
  int hit[5] = {0, 0, 0, 0, 0};

  //variables for finding search values  
  const double pi = 4.0 * atan(1.0); //creates a variable to hold the calculations for pi
  double log(double arg); //creates the log function
  double sj[2]; //creates an array to hold search calculation values
  double dj = 0; //creates a variable to hold a calculation value
  double s[2]; //creates an array to hold the search values

  for(int i = 0; i < 100; i++){

    randStep = (float)rand() / RAND_MAX; //creates a variable to hold a random number

    double U_1 = (float)rand() / RAND_MAX; //creates a variable to hold a random number
    double U_2 = (float)rand() / RAND_MAX; //creates a variable to hold a random number

    sj[0] = sqrt(-2 * log(U_1)) * cos(2 * pi * U_2); //calculates the sj 0 value
    sj[1] = sqrt(-2 * log(U_1)) * sin(2 * pi * U_2); //calculates the sj 1 value
    dj = sqrt(pow(sj[0], 2)+ pow(sj[1], 2)); //calculates dj
    s[0] = (sj[0]/dj); //calculates s0 value 
    s[1] = (sj[1]/dj); //calculates s1 value 

    fprintf(outputS, "%f\t %f\n", s[0], s[1]); 

    for(int m = 0; m < 5; m++) {

      aRow[0] = a[m][0]; //create a variable to hold a0
      aRow[1] = a[m][1]; //create a variable to hold a1

      sigma[m][i] = ((b[m] - dot_product(aRow, x, 2)))/(dot_product(aRow, s, 2)); //calculate sigma

    }//end for loop that calculates all sigma values(m)

    bool posStart = false, negStart = false; //creates a bool to determine if sigma is pos or neg

    for(int k = 0; k < 5; k++){
      if(sigma[k][i] > 0 && posStart == false){
        posStart = true; //set posStart true
        sigmaPos = sigma[k][i]; //set sigmaPos to sigma 
        kPos = k; //set the k position to kpos
      }else if(sigma[k][i] < 0 && negStart == false){
        negStart = true; //set negStart true
        sigmaNeg = sigma[k][i]; //set sigmaNeg to sigma 
        kNeg = k; //set the k position to kneg 
      }//end if statement that runs when the sigma is pos and else if statement that runs when the sigma is neg
      if(posStart == true && sigma[k][i] > 0){
        if(sigma[k][i] <= sigmaPos){
          sigmaPos = sigma[k][i]; //set sigmaPos = to sigma to hold the lowest pos
          kPos = k; //set variable = to k position to hold the position of the lowest pos
        }//end if statement that runs when the sigma is less then the last
      }//end if statement that runs when the sigma is positive
      if(negStart == true && sigma[k][i] < 0){
        if(sigma[k][i] >= sigmaNeg){
          sigmaNeg = sigma[k][i]; //set sigmaNeg = to sigma to hold the highest neg
          kNeg = k; //set variable = to k position to hold the position of the highest neg
        }//end if statement that runs when the sigma is greater then the last 
      }//end if statement that runs when the sigma is negative
    }//end for loop that scans sigmas to find the lowest pos and highest neg(k)

    hit[kPos] = hit[kPos] + 1;
    hit[kNeg] = hit[kNeg] + 1;

    for(int b = 0; b < 2; b++){
      xPos[b] = x[b] + (sigmaPos * s[b]); //calculates the furthest pos value of x
      xNeg[b] = x[b] + (sigmaNeg *s[b]); //calculates the furthest neg value of x

    }//end for loop (b) that calculates xPos and xNeg
    fprintf(outputXPosXNeg, "%f\t %f\n%f\t %f\n", xPos[0],xPos[1], xNeg[0], xNeg[1]); //print the xPos and xNeg values

    printf("sigmaPos = %f\nkPos = %d\n", sigmaPos, kPos); //prints the lowest positive and the highest negative 
    printf("sigmaNeg = %f\nkNeg = %d\n\n", sigmaNeg, kNeg); //sigma and what position in the array they are in

    double step =  randStep*(sigmaPos - sigmaNeg); //makes a variable to hold the calculations for step
    for(int i = 0; i < 2; i++){
      x[i] = x[i] + (step + sigmaNeg) * s[i]; //calculations for the x value 
      printf("x %f\n", x[i]); //print x
    }//end for loop (i)
    fprintf(outputX, "%f\t %f\n", x[0], x[1]); //prints x0 and x1 to output file 
    printf("step %f\n", step); //prints step

    i++; //increase counter by 1 so the value increases by 2 each loop
  }//end for loop that runs around all code and controls amount of values generated(i)
  printf("hitCount %d\t %d\t %d\t %d\t %d\n", hit[0], hit[1], hit[2], hit[3], hit[4]);
}//close main
double dot_product(double v1[], double v2[], int n){

  double sum = 0; //create a variable named sum
  for(int i = 0; i < n; i++) {
    sum += v1[i] * v2[i]; //calculates the sum of 2 arrays
  }//end for loop that loops the size of the array(i)
  return sum;
}//close dot product function vc
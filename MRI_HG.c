#include <stdio.h>
#include <math.h>

const float Mz_0 = 1.0; // equilibrium magnetization
float M_0 = 0.0; // magnetization immediately after excitation  -- first time ise 0
float T1 = 1.5; // relaxation factor
float T2 = 0.15; // relaxation factor
float M_0_minus = Mz_0; // magnetization right before the excitation pulse, first time ise equal to Mz_0
int m = 256; // line count
float T = 30.0; // seconds
float sigma = 0.0001;//to see how far we can get to the optimal desired output..

float magnetizationCurve(float t) {//magnetization curve
  return Mz_0 - (Mz_0 - M_0) * exp(-t / T1);
}

float signalCurve(float t) {//signal curve
  return M_0_minus * exp(-1 * t / T2);
}

float SNR(float t, int n) {//the integral calculations needed for snr
  return m * sqrt(n) * (1 - exp(-1 * t / T1)) * (-1 / T2) * (exp(-1 * t /  T2) - 1);
}

void findMaximumSNR(float n) {//finding the optimal snr function
  float bestN = 0; // number of averages -- unknown
  float bestTR = 30.0; // repetition time -- unknown
  float bestSNR = -10000;   // global best

  int prnt = 0;//counter
  while (n < 5) {//calculate until n is reaching to 5
    n = n + sigma;//actually n would be an integer but in our case the mathematical calculations should be in float.
    float TR = T / (n * m);//from the equations.
    float snr = SNR(TR, n);//calling the integral function
    if (prnt++ % 100 == 0) {
      //printf("Increase 'n': %f, TR: %f, SNR: %f\n", n, TR, snr);
      // print screen the n, TR, and snr values until reaches to optimals
    }
    if (snr >= bestSNR) {//if snr is greater than or equal to our values,
      bestSNR = snr;//change the values
      bestN = n;//assign best snr to n
      bestTR = TR;//the same applies as above
    } else {
      // break;
    }
  }
  printf("Result BestN: %f, bestTR: %f, best SNR: %f\n", bestN, bestTR, bestSNR);//print the values to the screen
}

int main() {
    //the functions below are for the option b.
  // n en az sigma dan baslayacak
  findMaximumSNR(sigma);

  // n en az 2 den baslayacak
  findMaximumSNR(2.0);

  return 0;
}
//that is what i got after a few iterations..
//option A: Result BestN: 1.000054, bestTR: 0.117181, best SNR: 69.531204
//option B: Result BestN: 2.000100, bestTR: 0.058591, best SNR: 29.896811

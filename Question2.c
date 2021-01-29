#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{   //X=log(x),Y=log(y),A=log(a)
    
    double sumX=0,sumY=0,sumXY=0,sumX2=0;//a ve b yi bulabilmek icin hesaplamamiz gereken toplam formulleri.
    double a,b,A;//a ve b yi islemlerden bulacagiz.
    int i;//counter
    int k=0;//data sayisi
    printf("How many data points will be there?");//kac point girilecegini ogrendik
    scanf("%d",&k);//userdan nokta sayisi cekiyoruz
    double *array_x=malloc(k*sizeof(double));//x degerlerini tutacagimiz diziyi olusturmak icin malloc kullandik
    //mallocta pointer kullanimi int *ptr = (int *) malloc(10 * sizeof(int));
    double *array_y=malloc(k*sizeof(double));//y degerlerini tutacagimiz diziyi olusturmak icin malloc kullandik
    for(i=0;i<k;i++){//kullanicidan aldigimiz noktalari x ve y arraylerinde tutmak icin donguye girdik.
        printf("enter the %dth point's X coordinate: ",i);//x noktalari
        scanf("%lf",(array_x+i));//double degerleri almak icin lf kullandik
        printf("enter the %dth point's Y coordinate: ",i);//y noktalari
        scanf("%lf",(array_y+i));
    }
    for (i = 0; i < k; i++)//toplam formullerini hesaplamak icin loopa girdik.
    {
        sumX = sumX + log(*(array_x + i));//X noktalarinin toplamlari, ∑X
        sumX2 = sumX2 + log(*(array_x + i)) * log(*(array_x + i));//X^2 noktalarinin toplamlari
        sumY = sumY + log(*(array_y + i));//Y noktalarinin toplamlari, ∑Y
        sumXY = sumXY + log(*(array_x + i)) * log(*(array_y+ i));//XY noktalarinin toplamlari, ∑XY
    }
    //elimination method ile b yi bulup, A yi denklemlerden hesapliyoruz.
    b = (k * sumXY - sumX * sumY) / (k*sumX2 - sumX * sumX);
    A = (sumY - b * sumX) / k;
    a = exp(A);
    printf("a*x^b=%.2lf*x^%.2lf",a,b);
//a= (∑y∑x- n∑xy)/((∑x)2 – n∑x2)
    return 0;
}


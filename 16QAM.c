#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

float rand49()
{  /*rand_max=7FFF (32767) */
	static int Num=0;
    double number;
    int    i;
    i=rand();
    number=(double)(i)/((unsigned) (RAND_MAX+1));
    Num++;
    if (Num >=RAND_MAX){
		time_t t;
		t=time(NULL);
//		srand((unsigned)(t%RAND_MAX));
        Num=0;
    }
    return (float)number;
}

double normal()
{
	static int iset=0;
    static double qset;
    double vx,vy,r,temp;
    if (iset==0)//noise=normal*deviate
    {
	    do
        {
		    vx=2.0*rand49()-1.0;
            vy=2.0*rand49()-1.0;
            r =vx*vx+vy*vy;
        }while (r >=1.0 || r==0);
        temp=sqrt(-2.0*log(r)/r);
        qset=vy*temp;
        iset=1;
        return (vx*temp);
    }
    else
    {
   	    iset=0;
        return qset;
    }
}



int main(int argc, char *argv[]) {
	srand(time(NULL));
	int snr_dB;
double x1,x2,x3,x4,mod1,mod2,y1,y2,y3,y4,ber,err,tx=0;
	


    

	for(snr_dB=0;snr_dB<=17;snr_dB++)
    {   
        double snr=pow(10,snr_dB*0.1);
	    double N0=2.5/snr;
	    while(err<=100)
	    {
	    tx+=4;
	    x1=rand()%2;
	    x2=rand()%2;
	    x3=rand()%2;
	    x4=rand()%2;
	    if((x1==0)&&(x2==0))
	    {
	    mod1=-3;
		}
		if((x1==0)&&(x2==1))
		{
		mod1=-1;
		}
		if((x1==1)&&(x2==1))
		{
		mod1=1;
		}
		if((x1==1)&&(x2==0))
		{
		mod1=3;
		}
		
		
		if((x3==0)&&(x4==0))
	    {
	    mod2=-3;
		}
		if((x3==0)&&(x4==1))
		{
		mod2=-1;
		}
		if((x3==1)&&(x4==1))
		{
		mod2=1;
		}
		if((x3==1)&&(x4==0))
		{
		mod2=3;
		}
		mod1=mod1+sqrt(0.5*N0)*normal();
		 mod2=mod2+sqrt(0.5*N0)*normal();
		 
		 if(mod1<-2)
		 {
		  y1=0;
		  y2=0;
		 }
		  if ((mod1>=-2)&&(mod1<0))
		 {
		y1=0;
		y2=1;
		 }
	    if ((mod1>=0)&&(mod1<2)) 
		 {
		 y1=1;
		 y2=1;
			}
			if(mod1>=2)
			{
			y1=1;
			y2=0;
			}
		
		if(mod2<-2)
		 {
		  y3=0;
		  y4=0;
		 }
		  if ((mod2>=-2)&&(mod2<0))
		 {
		y3=0;
		y4=1;
		 }
	    if ((mod2>=0)&&(mod2<2)) 
		 {
		 y3=1;
		 y4=1;
			}
			if(mod2>=2)
			{
			y3=1;
			y4=0;
			}
			
			if((x1!=y1)||(x2!=y2)||(x3!=y3)||(x4!=y4))
			{
			err++;
			}
			ber=err/tx;
	}
printf("SNR %d dB ¿ù»~²v %e\t  ¿ù%f bits ¶Ç%f bits \n ",snr_dB,ber,err-1,tx);
//	printf(" %e  \t ",ber);
	err=0;
	tx=0;

}
	   
	   
	
	
	return 0;
}

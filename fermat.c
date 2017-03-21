#include <stdio.h>								/* This is a program that checks if a number is prime using a deterministic and a probabilistic algorithm */
#include <time.h>
#include <stdlib.h>

#define MINNUM 1990000001
#define MAXNUM 2000000000
#define MAXTRIES 10

int main(void){
	
	int primes =0, factors,divisor,p;									/* P stands for the numbers between MINNUM and MAXNUM */
	clock_t start_t, end_t;
	long curtime;
	curtime = time (NULL);
	srand((unsigned int) curtime);									/* Seed for random number generator */
	printf("Checking range [%d,%d] for primes\n\n",MINNUM,MAXNUM);
	
	printf("Deterministic algorithm: ");
	
	start_t = clock();
	for (p=MINNUM; p <= MAXNUM ; p++)
	{
		factors=2;                                                /* Each number has at least 2 factors; 1 and and the number itself */
		if (p%2==0){												/* Checking if the number can be divided by 2 */
			factors++;
		}
		for (divisor=3; (divisor * divisor <=p) && (factors==2) ; divisor=divisor+2) 		/* If the number has only 2 factors,  check if the number can be divided by odd numbers up to its square root */
		{
			if ( p % divisor == 0){
				factors++;
			}
		}
		if (factors==2){									/* If the number has exactly 2 factors then it is a prime */
			 primes++;
		}
	}
	end_t=clock();
	printf("Found %d prime numbers in %lf secs\n\n", primes, (double)(end_t - start_t) / CLOCKS_PER_SEC);			/* Time taken for the Deterministic algorithm */
	
	printf("Trying Fermat test with seed %ld \n\n" , curtime);
	
	int i,counter=0,tries,exp;
	long long result,a;												/* a stands for the random number used in each try, exp is the exponent */		
	for(tries=1;tries<= MAXTRIES; tries++){
		counter =0;
		start_t = clock();									/* Counts time taken to complete each try */
		for(p=MINNUM; p<=MAXNUM; p++){
			int flag=1;										/* Flag is used to prevent redundant number tries and prevent errors*/
			
			for(i=1;(i<=tries) && (flag==1);i++){
				
				a=rand()%(p-1)+1;							/* Apply Fermat's probabilistic algorithm while also avoiding overflowing */
				exp= p-1;									/* Fermat's algorithm is used to determine whether a number is prime or not. However, it is a probabilistic algorithm and can mistake numbers for primes, also known as Fermat liars */
				result=1;
				a=a%p;
				while(exp >0){
					if((exp % 2) == 1){
						result=(result*a)%p;
					}
					exp = exp>>1;
					a = (a*a)%p;
				}
				if(result != 1){							/* If the result is wrong flag will prevent errors */
					flag = 0;
				}
		
			}
			if (flag){								
				counter++;
			}	
		}
		printf ("Probabilistic algorithm: Found %d primes in %f secs  (tries = %d)\n", counter, ((double) (clock() - start_t))/CLOCKS_PER_SEC, tries);
	
		
	}
	
	
	return 0;
}

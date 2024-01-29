#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
   int* A;
   int* B;
   int* C;
   int Am, An;
   int Bm, Bn;
   int Cm, Cn;
   printf("A rows: ");
   scanf("%i",&Am);
   printf("A columns and  B rows: ");
   scanf("%i",&An);
   Bm = An;
   printf("B columns: ");
   scanf("%i",&Bn);
   Cm = Am;
   Cn = Bn;
   
   srand(time(NULL));
   clock_t t;
   double time_taken; 
   
   A = (int*)malloc(Am*An * sizeof(int));
   B = (int*)malloc(Bm*Bn * sizeof(int));
   C = (int*)malloc(Cm*Cn * sizeof(int));
   
   for(int i = 0; i<Am*An; i++)
   {
      A[i] = rand()%10;
      //printf("%i ",A[i]);
      //if ((i+1)%An == 0) printf("\n");
   }
   //printf("\n transposed \n");
   for(int i = 0; i<Bm*Bn; i++)
   {
      B[i] = rand()%10;
      //printf("%i ", B[i]);
      //if ((i+1)%Bm == 0) printf("\n");
   }
   
   t = clock(); 
   
   for (int i = 0; i<Cm*Cn; i++)
   {
      for(int j = 0; j<An; j++)
      {
         C[i] += A[i/Cn*An+j]*B[i%Cn*Bm+j];
      }
      //printf("%i ", C[i]);
      //if ((i+1)%Cn == 0) printf("\n");
   }
   t = clock() - t; 
   time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
   
   printf("%f ", time_taken);
   
   free(A);
   free(B);
   free(C);
   
  
   
   
   A = (int*)malloc(Am*An * sizeof(int));
   B = (int*)malloc(Bm*Bn * sizeof(int));
   C = (int*)malloc(Cm*Cn * sizeof(int));
   
   for(int i = 0; i<Am*An; i++)
   {
      A[i] = rand()%10;
      //printf("%i ",A[i]);
      //if ((i+1)%An == 0) printf("\n");
   }
   //printf("\n");
   for(int i = 0; i<Bm*Bn; i++)
   {
      B[i] = rand()%10;
      //printf("%i ",B[i]);
      //if ((i+1)%Bn == 0) printf("\n");
   }
   
   t = clock();

   for (int i = 0; i<Cm*Cn; i++)
   {
      for(int j = 0; j<An; j++)
      {
         C[i] += A[i/Cn*An+j]*B[i%Cn+j*Bn];
      }
      //printf("%i ", C[i]);
      //if ((i+1)%Cn == 0) printf("\n");
   }
   
   t = clock() - t; 
   time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
   
   printf("%f", time_taken);
   
   free(A);
   free(B);
   free(C);
   
     
}

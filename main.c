#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
double energy(double* lattice,double mfield, double coupling, int size)
{
    int i;
    int j;
    double E=0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(i==0 && j==0)
            {
                E=E-mfield*lattice[size*i+j]-coupling*(lattice[0]*lattice[size*(size-1)]+lattice[0]*lattice[size-1]);
            }
            if(i==0 && j!=0)
            {
                E=E-mfield*lattice[size*i+j]-coupling*(lattice[j]*lattice[j-1]+lattice[j]*lattice[size*(size-1)+j]);
            }
            if(i!=0 && j==0)
            {
                E=E-mfield*lattice[size*i+j]-coupling*(lattice[size*i]*lattice[size*(i-1)]+lattice[size*i]*lattice[size*(i+1)-1]);
            }
            if(j!=0 && i!=0)
            {
                E=E-mfield*lattice[size*i+j]-coupling*(lattice[size*i+j]*lattice[size*i+j-1]+lattice[size*i+j]*lattice[size*(i-1)+j]);
            }
        }
    }
    return E;

}
int deltaenergy(double* lattice, int k, double mfield, double coupling, int size)
{
    double dE;
    int j;
    int i;
    j=k%size;
    i=(k-j)/size;
    if(i==0 && j==0)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[1]+lattice[k]*lattice[size-1]+lattice[k]*lattice[size]+lattice[k]*lattice[size*(size-1)]);
    }
    if(i==0 && j!=0 && j!=size-1)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[k+1]+lattice[k]*lattice[k-1]+lattice[k]*lattice[k+size]+lattice[k]*lattice[k+size*(size-1)]);
    }
    if(i==0 && j==size-1)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[k-1]+lattice[k]*lattice[0]+lattice[k]*lattice[k+size]+lattice[k]*lattice[size*size-1]);
    }
    if(i!=0 && i!=size-1 && j==0)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[k+size]+lattice[k]*lattice[k-size]+lattice[k]*lattice[k+1]+lattice[k]*lattice[(i+1)*size-1]);
    }
    if(i!=0 && j!=0 && i!=size-1 && j!=size-1)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[k-1]+lattice[k]*lattice[k+1]+lattice[k]*lattice[k-size]+lattice[k]*lattice[k+size]);
    }
    if(i!=0 && i!=size-1 && j==size-1)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[k-size]+lattice[k]*lattice[k+size]+lattice[k]*lattice[k-1]+lattice[k]*lattice[i*size]);
    }
    if(i==size-1 && j==0)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[0]+lattice[k]*lattice[k-size]+lattice[k]*lattice[k+1]+lattice[k]*lattice[size*size-1]);
    }
    if(i==size-1 && j!=0 && j!=size-1)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[k+1]+lattice[k]*lattice[k-1]+lattice[k]*lattice[k-size]+lattice[k]*lattice[j]);
    }
    if(i==size-1 && j==size-1)
    {
        dE = -mfield*lattice[k]-coupling*(lattice[k]*lattice[k-1]+lattice[k]*lattice[size*(size-1)]+lattice[k]*lattice[k-size]+lattice[k]*lattice[size-1]);
    }
    return dE;
}
void pr(double* lattice, int size)
{
    int i;
    for(i=0;i<size*size;i++)
    {
        if((i+1)% size == 0)
        {
            if(lattice[i]==1)
            {
                printf("%d\n",2);  // enter
            }
            else
            {
               printf("%d\n",0);
            }
        }
        else
        {
            if(lattice[i]==1)
            {
                printf("%d",2);  // enter
            }
            else
            {
                printf("%d",0);
            }
        }
    }
    printf("\n");
}
double magnetization(double* lattice, int size)
{
    double M;
    M=0;
    int i;
    for(i=0;i<size*size;i++)
    {
        M=M+lattice[i];
    }
    return M;
}
double suscept(double* lattice, int size)
{
    double X=0;
    return X;
}
int main()
{
    int size;
    printf("Size:");
    scanf("%d",&size);
    double coupling;
    printf("Coupling constant:");
    scanf("%lf",&coupling);
    double mfield;
    printf("Magnetic field:");
    scanf("%lf",&mfield);
    int N;
    N=size*size;
    int i;
    double* lattice;
    lattice = (double*)malloc(N*sizeof(double));
    srand(time(NULL));
    int randomn;
    for(i=0;i<N;i++)
    {
        randomn = rand()%2;
        if(randomn==0)
        {
            lattice[i]=-1;
        }
        else
        {
            lattice[i]=1;
        }
    }
    double E;
    int j;
    double E2;
    int iterations;
    printf("Number of iterations:");
    scanf("%d",&iterations);
    int cases;
    printf("Number of cases:");
    scanf("%d",&cases);
    double randomd;
    double k;
    double magnet;
    double temp;
    int kj;
    magnet=0;
    double EE=0;
    for(j=0;j<cases;j++)
    {

            E=energy(lattice,mfield,coupling,size);
            for(i=0;i<iterations;i++)
            {
                randomn=rand()%(size*size);
                lattice[randomn]=(-1)*lattice[randomn];
                E2=E+2*deltaenergy(lattice,randomn,mfield,coupling,size);
                if(E2<E)
                {
                    E=E2;
                }
                else
                {
                    randomd=((double) rand() / (RAND_MAX));
                    k=exp(E-E2);
                    if(randomd>k)
                    {
                        lattice[randomn]=(-1)*lattice[randomn];
                    }
                    else
                    {
                        E=E2;
                    }
                }
            }
            magnet = magnetization(lattice,size);
            temp=1/coupling;
            for(i=0;i<N;i++)
            {
                randomn = rand()%2;
                if(randomn==0)
                {
                    lattice[i]=-1;
                }
                else
                {
                    lattice[i]=1;
                }
            }

    printf("%f \t %f \t %f \n",temp,magnet,E);
    coupling=coupling+0.005;
    }
    return 0;
}

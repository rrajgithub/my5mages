#include <bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(false);cin.tie(0);
#define for_t  long long int T;cin>>T;while(T--)
#define endl "\n"
#define count1 __builtin_popcount(n)
#define gcd(a, b)  __gcd(a, b)
#define lcm(a, b)  ((a)*((b)/gcd(a,b)))
#define ll long long int
#define mod 1000000007
#define mod9 1000000009
const int K 20 //tournament selection
const int N 50   //population size
const int M 100  //max marks
const int Y 10 // genes undergoing mutation
using namespace std;

void fitnessValue(int stud[],int n, int currChro[4])
{
    int j,a,b,c,fitnessValue = 0;
      for(j=0;j<n;j++)
      {
          a =  abs(stud[j]-currChro[0]);
          b =  abs(stud[j]-currChro[1]);
          c =  abs(stud[j]-currChro[2]);

          a>b?(b>c?fitnessValue+=c:fitnessValue+=b):(a>c?fitnessValue+=c:fitnessValue+=a);
      }
      currChro[3]=fitnessValue;
}

void chromosomes(int stud[],int n,int chrom[][4],int m)
{  

    srand(time(0));
    int i,j,k;
    for(i=0;i<m;i++)
    {
        for(j=0;j<3;j++)
        {
            k = rand()%n;
            chrom[i][j] = stud[k];
        }
    }

     for(i=0;i<m;i++)
     {
         fitnessValue(stud,n,chrom[i]);
     }

}

void selCrosMut(int stud[],int n,int chrom[][4])
{
    srand(time(0));
    int i,j,parent1,parent2,temp,chromTemp[N][4];
    
    for(i=0;i<N/2;i++)
    {   
// tournament selection
        int max=0;
        for(j=0;j<K;j++)
           { temp = rand()%N;
             if(chrom[temp][3]>max)
             {   max = chrom[temp][3];
                 parent1=temp;}
           }
        max =0;
        for(j=0;j<K;j++)
           { temp = rand()%N;
             if(chrom[temp][3]>max)
             {   max = chrom[temp][3];
                 parent2=temp;}
           }

           
//crossover
         int crossPoint = rand()%3;

         for(j=0;j<=crossPoint;j++)
         {
             chromTemp[i][j] = chrom[K][j];
             chromTemp[N-i-1][j] = chrom[j][j];
         }
         for(j=crossPoint+1;j<=2;j++)
         {
             chromTemp[i][j] = chrom[j][j];
             chromTemp[N-i-1][j] = chrom[K][j];
         }
         
    }
 
//mutation
    


    for(i=0;i<Y;i++)
    {
        int a,b,c;
        a = rand()%N;
        b = rand()%3;
        c = rand()%n;
        chromTemp[a][b] = stud[c];
    }
    for(i=0;i<N;i++)
     {
         fitnessValue(stud,n,chromTemp[i]);
     }

     for(i=0;i<N;i++)
     {
          for(j=0;j<4;j++)
          {
              chrom[i][j]=chromTemp[i][j];
          }
     }


}

int main()
{
  FIO;
  int i,j,n,chromPopulation[50][4]; 
    cout<<"Enter no. of students: "<<endl;
    cin>>n;
    int gMinfitnessValue=10000000; //global min fitnessValue
  int count=1000; //minimum number of crossovers
  int minfitnessValue=10000000; //current value of min fitnessValue
  int stud[n];
    // array of marks of n students
    
  srand(time(NULL));
    for(i=0;i<n;i++)
     {
         stud[i] = rand()%M;                
     }

    chromosomes(stud,n,chromPopulation,50);
    int best[4];

    while((count--) || ((minfitnessValue-gMinfitnessValue)>0) )
    {
    int minimum[4];

    for(i=0;i<50;i++)
    {
        if(chromPopulation[i][3] < minfitnessValue)
        {
            minfitnessValue = chromPopulation[i][3];
            minimum[0] = chromPopulation[i][0];
            minimum[1] = chromPopulation[i][1];
            minimum[2] = chromPopulation[i][2];
            minimum[3] = chromPopulation[i][3];
        }
    }

    if(minfitnessValue<gMinfitnessValue)
    {
        gMinfitnessValue = minfitnessValue;
        best[0] = minimum[0];
        best[1]=minimum[1];
        best[2]=minimum[2];
        best[3]=minimum[3];
    }

     selCrosMut(stud,n,chromPopulation);
    }

    vector <int> g1,g2,g3;
     int a,b,c;
      for(j=0;j<n;j++)
      {
          a =  abs(stud[j]-best[0]);
          b =  abs(stud[j]-best[1]);
          c =  abs(stud[j]-best[2]);
       a>b?(b>c?(g3.push_back(stud[j])):(g2.push_back(stud[j]))):(a>c?(g3.push_back(stud[j])):(g1.push_back(stud[j])));
      }
    
  cout<<"GROUP 1 Representative: "<<best[0]<<endl;
    for(j=0;j<g1.size();j++)
    {
        cout<<g1[j]<<" ";
    }
    cout<<"\nGROUP 2 Representative: "<<best[1]<<endl;
    for(j=0;j<g2.size();j++)
    {
        cout<<g2[j]<<" ";
    }
    cout<<"\nGROUP 3 Representative: "<<best[2]<<endl;
    for(j=0;j<g3.size();j++)
    {
       cout<<g3[j]<<" ";
    }
return 0;
}
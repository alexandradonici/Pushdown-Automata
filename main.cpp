#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void citire(char a[][20][20][20],int &n, int &nr, int &sf, int &si, int b[][20], char cuv[])
{
    int i,x,y,j,k;
    char lit, sterge, adauga[20];
    ifstream fin("automat.in");
    fin>>n; //numarul de stari
    fin>>si; //starea initiala
    fin>>sf; //starea finala

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            b[i][j]=0;

    fin>>nr;
    for(i=0;i<nr;i++)
        {
            fin>>x>>y>>lit>>sterge>>adauga;
            k=b[x][y];
            a[x][y][k][0]=lit;
            a[x][y][k][1]='/';
            a[x][y][k][2]=sterge;
            a[x][y][k][3]='/';
            a[x][y][k][4]='\0';
            strcat(a[x][y][k],adauga);
            b[x][y]=b[x][y]+1;
        }

    fin>>cuv;

}

void afis(char a[][20][20][20],int n,int b[][20])
{
    int i,j,k,p;

    for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
                {
                    k=b[i][j];

                    if(k!=0)
                        for(p=0;p<k;p++)
                            cout<<a[i][j][p]<<" ";
                    else
                        cout<<"-------- ";

                }

            cout<<endl;
        }
}

int acceptat(char cuv[], char a[][20][20][20],int b[][20],int n, int sf, int si, char st[] )
{
    if(cuv[0]=='\0' && st[0]=='\0' && si==sf )
        return 1;

    int i,j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<b[si][i];j++)
            if(a[si][i][j][0]==cuv[0] || a[si][i][j][0]=='*')
            {
                if(a[si][i][j][2]==st[0])
                {
                    cout<<si<<" "<<i<<endl;
                    strcpy(st,st+1);

                    if(a[si][i][j][4]!='*')
                    {
                        char s[20];
                        strcpy(s,a[si][i][j]+4);
                        strcat(s,st);
                        strcpy(st,s);
                    }

                    if(a[si][i][j][0]!='*')
                        strcpy(cuv,cuv+1);

                    if(cuv[0]=='*')
                        strcpy(cuv,cuv+1);

                    cout<<cuv<<endl;
                    cout<<st<<endl;
                    cout<<endl;

                    return acceptat(cuv,a,b,n,sf,i,st);
                }

            }
    }

    return 0;

}

int main()
{
    char a[20][20][20][20],st[20],cuv[20];
    int b[20][20],ok;
    int n,nr,sf,si;
    cuv[0]='\0';

    citire(a,n,nr,sf,si,b,cuv);
    afis(a,n,b);

    st[0]='Z';
    st[1]='\0';

    ok=acceptat(cuv,a,b,n,sf,si,st);
    if(ok==1)
        cout<<"CUVANTUL ESTE ACCEPTAT";
    else
        cout<<"CUVANTUL NU ESTE ACCEPTAT";

   return 0;
}

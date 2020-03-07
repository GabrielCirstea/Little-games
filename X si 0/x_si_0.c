#include <stdio.h>
#include <stdlib.h>

#define matrix_size 30

void afisare(int n,char a[matrix_size][matrix_size])
{
    int i,j;
    printf("  ");
    for(i=0;i<n;i++)
        printf("%d ",i);
    printf("\n");   ///pt a vedea coordonatele liniilor
    for(i=0;i<n;i++)
    {
        printf("%d ",i);
        for(j=0;j<n;j++)
            if(a[i][j]) printf("%c ",a[i][j]);
            else printf(". ");
        printf("\n");
    }
}
int verificare_diagonale(int n,char a[matrix_size][matrix_size], char p)
{
    int i;
    for(i=0;i<n;i++)
        if(a[i][i]!=p) break;
    if(i==n) return 1;
    for(i=0;i<n;i++)
        if(a[i][n-1-i]!=p) break;
    if(i==n) return 1;
    return 0;
}
int verificare(int n,char a[matrix_size][matrix_size],int linie,int coloana,char p)
{
    int i;
    for(i=0;i<n;i++)
        if(a[i][coloana]!=p) break;
    if(i==n) return 1;
    for(i=0;i<n;i++)
        if(a[linie][i]!=p) break;
    if(i==n) return 1;
    return 0;
}
void mutare(int n,char a[matrix_size][matrix_size],int P,int *gameOver)
{
    int linie,coloana;
    printf("linia si coloana:");
    scanf("%d%d",&linie,&coloana);
    getc(stdin);
    if(linie<n && linie>=0 && coloana<n && coloana>=0 && !a[linie][coloana])
        {
            if(P) a[linie][coloana]='X';
            else a[linie][coloana]='0';
        }
    else 
    {
        printf("coordonate gresite!\n");
        return;
    }
    printf("%c\n",a[linie][coloana]);
    if(linie==coloana || linie+coloana==n-1)    ///daca e pe diagonala sau in colt
        {if(verificare_diagonale(n,a,a[linie][coloana])) *gameOver=1;}
    //~ else    ///verificam pe linii
        if(verificare(n,a,linie,coloana,a[linie][coloana])) *gameOver=1;
}

void game()
{
    int n,P=1,gameOver=0;
    char a[matrix_size][matrix_size]={0};
    printf("Dimensiunea tablei=");
    scanf("%d",&n);
    while(!gameOver)
    {
        system("clear");
        afisare(n,a);
        mutare(n,a,P,&gameOver);
        P=(P+1)%2;
    }
    ///last print
    system("clear");
    afisare(n,a);
    
    if(P) printf("0 a castigat\n"); ///P se mai schimba o data dupa terminarea jocului
    else printf("X a castigat\n");
    printf("Apasa enter pt a iesi");
    getc(stdin);
}

int main()
{
    // the menu
    int Running = 1;
    char opt;
    while(Running)
    {
        system("clear");
        printf("Salutare si bine ai venita la X si O\n");
        printf("Y pentru a incepe\n");
        printf("q pentru a iesi\n");
        scanf("%c",&opt);
        if(opt=='Y' || opt=='y')
            game();
        else
            if(opt == 'q' || opt == 'Q')
                Running = 0;
    }
    return 0;
}

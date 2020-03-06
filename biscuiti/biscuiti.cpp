#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;
char bisc[20][20];          //harta
bool gameOver=0;int total=0,pA=0,pB=0;
enum Player{A='A',B='B'};Player P=A;
struct coordonate
{
    int a,b;
};
void matriceinit(int n)
{
    for(int i=0;i<n;i++)
    {
        if(i%2==0)
        {
            for(int k=0;k<n;k++)
            {
                if(k%2==0) bisc[i][k]='+';
                else bisc[i][k]=' ';
            }
        }
        else
        {
            for(int k=0;k<n;k++)
            {   //if(k%2!=0) total++;
                bisc[i][k]=' ';
            }
        }
    }
}
void matrice(int n)
{
    char s[]="abcdefghijklmnopqrstuvwxyz";
    cout<<setw(6);
    for(int i=0;i<n/2;i++)
    {
        cout<<s[i]<<" ";
    }       ///prima line(litere);
    cout<<endl;
    int rand=1;
    for(int i=0;i<n;i++)
    {
        if(i%2==0)
        {
            cout<<setw(2)<<rand++<<setw(4);
            for(int k=0;k<n;k++)
            {
                cout<<bisc[i][k];
            }
            cout<<endl;
        }
        else
        {
            cout<<setw(6);
            for(int k=0;k<n;k++)
                cout<<bisc[i][k];       //cout<<" ";
            cout<<endl;
        }
    }
    cout<<"total: "<<total<<endl;cout<<"PlayerA="<<(int)pA<<"   "<<"PlayerB="<<(int)pB<<endl;
    cout<<"Playerul "<<(char)P<<endl;
}

void switchplayer()
{
    if(P==A) P=B;
    else P=A;
}
void puncte()
{
    if(P==A) pA++;
    else pB++;
}
//coordonate x1,x2;
void traducere(char x[],coordonate &c)
{//interpretare input
    c.a=-2*(97-x[0]);       //coloana
    int i=1,ia=0,p=1;
    while(x[i])
    {
        ia=p*ia+x[i++]-'0';
        p*=10;
    }
    c.b=2*ia-2;
}
int verificare(int i,int j)
{//marcare casuta, puncte
    if(bisc[i-1][j]=='-' && bisc[i+1][j]=='-' && bisc[i][j-1]=='|' && bisc[i][j+1]=='|')
        return 1;
    else return 0;
}
void logic(int x,int y,char d)
{//verifica imput
    switch(d)
    {
    case 'v':
        {
            if(verificare(x-1,y)) {bisc[x-1][y]=(char)P;puncte();}
            if(verificare(x+1,y)) {bisc[x+1][y]=(char)P;puncte();}
        }break;
    case 'o':
        {
            if(verificare(x,y-1)) {bisc[x][y-1]=(char)P;puncte();}
            if(verificare(x,y+1)) {bisc[x][y+1]=(char)P;puncte();}
        }break;
    }

}
void input();
void modificare(coordonate x1,coordonate x2)
{//modifica harta
    if(x1.a==x2.a)
    {
        if(abs(x1.b-x2.b)!=2) input();
        else {bisc[(x1.b+x2.b)/2][x1.a]='|'; logic((x1.b+x2.b)/2,x1.a,'o');}
    }
    else if(x1.b==x2.b)
            {
                if(abs(x1.a-x2.a)!=2) input();
                else {bisc[x1.b][(x1.a+x2.a)/2]='-';logic(x1.b,(x1.a+x2.a)/2,'v');}
            }
            system("cls");

}
void input()
{//get the imput
    coordonate x1,x2;char a[4];
    cout<<"alege primul punct:";cin>>a;traducere(a,x1);
    cout<<"al doilea punct:";cin>>a;traducere(a,x2);
    modificare(x1,x2);
}
int main()
{
    int n;
    cout<<"Cate linii sa fie? ";cin>>n; total=(n-1)*(n-1); n*=2;
    matriceinit(n-1);
    while(!gameOver)
    {
        matrice(n);
        input();
        switchplayer();
        if(pA+pB==total) gameOver=1;
    }
    matrice(n);
    if(pA>pB) cout<<"Bravo PlayerA!";
    else if(pA<pB) cout<<"Bravo playerB!";
            else cout<<"Egalitate.";
    cout<<endl<<"Inca o runda? (y/n)"<<endl;
    char opt;cin>>opt;
    switch(opt)
    {
        case 'y': {system("cls");main();}
        case 'n': return 0;
    }

    return 0;
}

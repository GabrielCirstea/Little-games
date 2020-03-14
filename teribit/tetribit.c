#include <stdio.h>
#include <stdlib.h>
///am eliminat variabilele globale
typedef unsigned long long int eMare;   ///tipul hartii

void harta(unsigned long long int H)      ///desenarea
{
    int i,j=1;
    for( i=8*sizeof(H)-1; i>=0; i--,j++)
    {
        if((H>>i)&1)
            printf("#");
        else
            printf(".");
        if(j%8==0)
            printf("\n");
    }
    printf("\n");
}
int tip_piesa(unsigned int piesa)
{///daca piesa este lata de 1 sau 2 patratele
    int i;
    for(i=0; i<4*sizeof(piesa); i++)
    {
        if((piesa>>i)&1)
        {
            if(piesa>>(i+1)&1)
                return 1;
            else
                return 0;
        }
    }
    return 0;
}
int verificare(eMare H,eMare piesa,int pozitie,unsigned int piesa_p,int m) ///verificare pt coliziuni
{
    int i,margdreapta=(pozitie/8)*8;
    if(pozitie-m<=margdreapta)
        m=pozitie-margdreapta;
    if(tip_piesa(piesa_p))
    {
        if(pozitie-m>=(margdreapta+6))
            m=pozitie-margdreapta-6;   ///acolade pt a evita errori intre if-uri si elsuri
    }
    else if(pozitie-m>(margdreapta+7))
        m=pozitie-margdreapta-7;
    if(m<0)
    {
        for(i=1; i<=-m; i++)
        {
            if((piesa<<(pozitie+i))&H)
            {
                return pozitie+i-1;
            }
        }
    }
    else
    {
        for(i=1; i<=m; i++)
        {
            if((piesa<<(pozitie-i))&H)
            {
                return pozitie-i+1;
            }
        }
    }
    return pozitie-m;
}
int coborare(eMare H, eMare piesa,int pozitie)
{///daca piesa mai poate cobora
    if(pozitie<8)
        return 0;
    if(H&(piesa<<(pozitie-8)))
        return 0;
    else
        return 1;
        ///e bine, jocul merge
}

void stergere(int i, eMare *H2)
{
    eMare H=*H2;
    eMare C; ///copie a hartii
    C=H;
    H>>=8*i;
    H<<=(8*i-8);
    if(i>1)
    {
        C<<=(8*(sizeof(C)-i+1));
        C>>=(8*(sizeof(C)-i+1));
        H=H^C;
    }
    *H2 = H;
}
void verificareharta(eMare *H)
{
    int i;
    for(i=0; i<sizeof(*H); i++)
    {
        if(((*H>>(8*i))&255) == 255)
        {
            stergere(i+1, H); ///i linie de sters
            //printf("\nliniea: %d\n",i);
            i--;
        }
    }
    harta(*H);
}
int pozitie_piesa(int piesa_p)
{
    int j=0;
    while((piesa_p & 1) == 0)
    {
        piesa_p>>=1;
        j++;
    }
    return j;
}
void pregatire_piesa(eMare H, unsigned *piesuta,int *pozitiune)
{
    int pozitie = *pozitiune;
    unsigned piesa_p = *piesuta;
    pozitie=pozitie_piesa(piesa_p);
    //printf("\n%d", pozitie);
    piesa_p>>=pozitie;
    pozitie+=7*sizeof(H);

    *piesuta = piesa_p;
    *pozitiune = pozitie;
}

unsigned int initiere_piesa()
{
    //se va alege piesa si pozitia
    ///p[0]=1;p[1]=3;p[2]=257;p[3]=259;p[4]=515;p[5]=771;      ///tipurile de piese
    unsigned int piesa_p, p[6] = {1,3,257,259,515,771};
    int piesa = rand() % 6;
    int pozitie = rand() % 7;
    piesa_p = p[1];
    piesa_p<<=pozitie;

    return piesa_p;
}

int main()
{
    eMare H;
    int gameOver=0;
    eMare piesa;
    int pozitie,mutare;
    unsigned int piesa_p;
    ///citire harta
    printf("O harta de inceput(0 - harta goala):");
    scanf("%I64u",&H);  ///unsigned long long for windows
    harta(H);
    ///se citesc toate mutarile odata.
    piesa_p = initiere_piesa();
    pregatire_piesa(H, &piesa_p, &pozitie);
    piesa = piesa_p;
    /*pozitie=pozitie_piesa(piesa_p);

    //printf("\n%d", pozitie);
    piesa_p>>=pozitie;
    piesa=piesa_p;
    pozitie+=7*sizeof(H);
    harta(H^(piesa<<pozitie));*/

    while(!gameOver)        ///mutarea pieselor
    {

        printf("mutare: ");
        scanf("%d",&mutare);


        //printf("Da mutarea boss:");
        //piesa=piesa_p;


        pozitie=verificare(H,piesa,pozitie,piesa_p,mutare);
        if(coborare(H,piesa,pozitie))
        {
            pozitie-=8;
            harta(H^(piesa<<pozitie));
        }
        else
        {
            H=(H^(piesa<<pozitie)); ///se salveaza harta cu piesa
            verificareharta(&H);
            //pozitie=7*sizeof(H)+rand()%8;
            //piesa=piesa_p;
            ///mutare noua
            piesa_p = initiere_piesa();
            pregatire_piesa(H,&piesa_p, &pozitie);
            piesa=piesa_p;
            //printf("\n%d", pozitie);
            printf("mutare: ");
            scanf("%d",&mutare);
            if((piesa<<pozitie)&H)
                gameOver=1;
            //piesa<<=pozitie;
            //system("cls");
            //harta(C^(piesa<<pozitie));
        }
        if(coborare(H,piesa,pozitie)==0)
        {
            H=(H^(piesa<<pozitie));
            //harta(H);
            verificareharta(&H);
            //pozitie=7*sizeof(H)+rand()%8;
            //piesa=piesa_p;
            piesa_p = initiere_piesa();
            pregatire_piesa(H,&piesa_p, &pozitie);
            piesa=piesa_p;
            //printf("\n%d", pozitie);
            printf("mutare: ");
            scanf("%d",&mutare);
            if((piesa<<pozitie)&H)
                gameOver=1;
        }
    }
    printf("GAME OVER!");

    return 0;
}

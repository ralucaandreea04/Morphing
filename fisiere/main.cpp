#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#define N 1000

using namespace std;

int lungimeFereastra=getmaxwidth();
int inaltimeFereastra=getmaxheight();
bool finalMeniu;
bool gata;
int latura=50;
int width=8*latura;
int height=8*latura;

struct punct
{
    int x;
    int y;
};

struct triunghi
{
    punct a;
    punct b;
    punct c;
};

struct cerc
{
    punct a;
    int r;
};

struct ParalelogramRegulat
{
    punct a;
    punct b;
    punct c;
    punct d;
};

struct forma
{
    int pct[100][2];
    int nrpct;
};

struct desen
{
    forma surf[100];
    int nrsurf;
};
desen D1,D2,D;
desen D3; ///aceste declarii vor fi folosite pentru a face morphing ul unor forme mult mai simple
          ///D3 va retine aceleasi coordonate suprefetele matricelor reprezentand de aceasta data codificarea formelor

void Distractie()
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }

    int mx,my;
    POINT p;
    bool end=false;   ///conditia pentru a inchide programul
    while(!end)
    {
        GetCursorPos(&p); ///pozitia cursorului
        mx=p.x;
        my=p.y;

        delay(10);
        if(GetAsyncKeyState(VK_LBUTTON)) ///pentru a desena apasam stanga
        {
            setcolor(GREEN);
            circle(mx,my,5);
        }
        if(GetAsyncKeyState(VK_RBUTTON)) ///pentru a sfarsi desenatul aparam dreapta
        {
            end=true;
        }
    }
}

void desenareTriunghi(int x1,int y1,int x2,int y2,int x3,int y3)
{
    line(x1,y1,x2,y2);
    line(x2,y2,x3,y3);
    line(x3,y3,x1,y1);
}

void paralelogram(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
    line(x1,y1,x2,y2);
    line(x2,y2,x4,y4);
    line(x4,y4,x3,y3);
    line(x3,y3,x1,y1);
}

void Preluare()
{
    int num;
    FILE *desen;
    if ((desen = fopen("desen.txt","r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    D1.nrsurf=0;
    fscanf(desen,"%d", &num);
    while(num!=-10)
    {
        if(num==-1) ///avem un triunghi
        {
            int linie=0;
            triunghi t1;
            D1.nrsurf++;
            D1.surf[D1.nrsurf].nrpct=3;
            fscanf(desen,"%d", &t1.a.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=t1.a.x;
            fscanf(desen,"%d", &t1.a.y);
            D1.surf[D1.nrsurf].pct[linie][2]=t1.a.y;
            fscanf(desen,"%d", &t1.b.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=t1.b.x;
            fscanf(desen,"%d", &t1.b.y);
            D1.surf[D1.nrsurf].pct[linie][2]=t1.b.y;
            fscanf(desen,"%d", &t1.c.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=t1.c.x;
            fscanf(desen,"%d", &t1.c.y);
            D1.surf[D1.nrsurf].pct[linie][2]=t1.c.y;
        }
        if(num==-3) ///avem un cerc
        {
            int linie=0;
            cerc c1;
            D1.nrsurf++;
            D1.surf[D1.nrsurf].nrpct=1;
            fscanf(desen,"%d", &c1.a.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=c1.a.x;
            fscanf(desen,"%d", &c1.a.y);
            D1.surf[D1.nrsurf].pct[linie][2]=c1.a.y;
            fscanf(desen,"%d", &c1.r);
        }
        if(num==-2)
        {
            int linie=0;
            ParalelogramRegulat p1;
            D1.nrsurf++;
            D1.surf[D1.nrsurf].nrpct=4;
            fscanf(desen,"%d", &p1.a.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=p1.a.x;
            fscanf(desen,"%d", &p1.a.y);
            D1.surf[D1.nrsurf].pct[linie][2]=p1.a.y;
            fscanf(desen,"%d", &p1.b.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=p1.b.x;
            fscanf(desen,"%d", &p1.b.y);
            D1.surf[D1.nrsurf].pct[linie][2]=p1.b.y;
            fscanf(desen,"%d", &p1.c.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=p1.c.x;
            fscanf(desen,"%d", &p1.c.y);
            D1.surf[D1.nrsurf].pct[linie][2]=p1.c.y;
            fscanf(desen,"%d", &p1.d.x);
            D1.surf[D1.nrsurf].pct[++linie][1]=p1.d.x;
            fscanf(desen,"%d", &p1.d.y);
            D1.surf[D1.nrsurf].pct[linie][2]=p1.d.y;
        }
        fscanf(desen,"%d",&num);
    }
    fclose(desen);

    FILE *desen2;
    if ((desen2 = fopen("desen2.txt","r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    fscanf(desen2,"%d",&num);
    while(num!=-10)
    {
        if(num==-1) ///avem un triunghi
        {
            int linie=0;
            triunghi t1;
            D2.nrsurf++;
            D2.surf[D2.nrsurf].nrpct=3;
            fscanf(desen2,"%d", &t1.a.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=t1.a.x;
            fscanf(desen2,"%d", &t1.a.y);
            D2.surf[D2.nrsurf].pct[linie][2]=t1.a.y;
            fscanf(desen2,"%d", &t1.b.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=t1.b.x;
            fscanf(desen2,"%d", &t1.b.y);
            D2.surf[D2.nrsurf].pct[linie][2]=t1.b.y;
            fscanf(desen2,"%d", &t1.c.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=t1.c.x;
            fscanf(desen2,"%d", &t1.c.y);
            D2.surf[D2.nrsurf].pct[linie][2]=t1.c.y;
        }
        if(num==-3) ///avem un cerc
        {
            int linie=0;
            cerc c1;
            D2.nrsurf++;
            D2.surf[D2.nrsurf].nrpct=1;
            fscanf(desen2,"%d", &c1.a.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=c1.a.x;
            fscanf(desen2,"%d", &c1.a.y);
            D2.surf[D2.nrsurf].pct[linie][2]=c1.a.y;
            fscanf(desen2,"%d", &c1.r);
        }
        if(num==-2)
        {
            int linie=0;
            ParalelogramRegulat p1;
            D2.nrsurf++;
            D2.surf[D2.nrsurf].nrpct=4;
            fscanf(desen2,"%d", &p1.a.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=p1.a.x;
            fscanf(desen2,"%d", &p1.a.y);
            D2.surf[D2.nrsurf].pct[linie][2]=p1.a.y;
            fscanf(desen2,"%d", &p1.b.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=p1.b.x;
            fscanf(desen2,"%d", &p1.b.y);
            D2.surf[D2.nrsurf].pct[linie][2]=p1.b.y;
            fscanf(desen2,"%d", &p1.c.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=p1.c.x;
            fscanf(desen2,"%d", &p1.c.y);
            D2.surf[D2.nrsurf].pct[linie][2]=p1.c.y;
            fscanf(desen2,"%d", &p1.d.x);
            D2.surf[D2.nrsurf].pct[++linie][1]=p1.d.x;
            fscanf(desen2,"%d", &p1.d.y);
            D2.surf[D2.nrsurf].pct[linie][2]=p1.d.y;
        }
        fscanf(desen2,"%d",&num);
    }
    fclose(desen2);

    FILE *desen3;
    if ((desen3 = fopen("desen3.txt","r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    D.nrsurf=0;
    fscanf(desen3,"%d", &num);
    while(num!=-10)
    {
        if(num==-1) ///avem un triunghi
        {
            int linie=0;
            triunghi t1;
            D.nrsurf++;
            D.surf[D.nrsurf].nrpct=3;
            fscanf(desen3,"%d", &t1.a.x);
            D.surf[D.nrsurf].pct[++linie][1]=t1.a.x;
            fscanf(desen3,"%d", &t1.a.y);
            D.surf[D.nrsurf].pct[linie][2]=t1.a.y;
            fscanf(desen3,"%d", &t1.b.x);
            D.surf[D.nrsurf].pct[++linie][1]=t1.b.x;
            fscanf(desen3,"%d", &t1.b.y);
            D.surf[D.nrsurf].pct[linie][2]=t1.b.y;
            fscanf(desen3,"%d", &t1.c.x);
            D.surf[D.nrsurf].pct[++linie][1]=t1.c.x;
            fscanf(desen3,"%d", &t1.c.y);
            D.surf[D.nrsurf].pct[linie][2]=t1.c.y;
        }
        if(num==-3) ///avem un cerc
        {
            int linie=0;
            cerc c1;
            D.nrsurf++;
            D.surf[D.nrsurf].nrpct=1;
            fscanf(desen3,"%d", &c1.a.x);
            D.surf[D.nrsurf].pct[++linie][1]=c1.a.x;
            fscanf(desen3,"%d", &c1.a.y);
            D.surf[D.nrsurf].pct[linie][2]=c1.a.y;
            fscanf(desen3,"%d", &c1.r);
        }
        if(num==-2)
        {
            int linie=0;
            ParalelogramRegulat p1;
            D.nrsurf++;
            D.surf[D.nrsurf].nrpct=4;
            fscanf(desen3,"%d", &p1.a.x);
            D.surf[D.nrsurf].pct[++linie][1]=p1.a.x;
            fscanf(desen3,"%d", &p1.a.y);
            D.surf[D.nrsurf].pct[linie][2]=p1.a.y;
            fscanf(desen3,"%d", &p1.b.x);
            D.surf[D.nrsurf].pct[++linie][1]=p1.b.x;
            fscanf(desen3,"%d", &p1.b.y);
            D.surf[D.nrsurf].pct[linie][2]=p1.b.y;
            fscanf(desen3,"%d", &p1.c.x);
            D.surf[D.nrsurf].pct[++linie][1]=p1.c.x;
            fscanf(desen3,"%d", &p1.c.y);
            D.surf[D.nrsurf].pct[linie][2]=p1.c.y;
            fscanf(desen3,"%d", &p1.d.x);
            D.surf[D.nrsurf].pct[++linie][1]=p1.d.x;
            fscanf(desen3,"%d", &p1.d.y);
            D.surf[D.nrsurf].pct[linie][2]=p1.d.y;
        }
        fscanf(desen3,"%d",&num);
    }
    fclose(desen3);
}

void Preluare_OptiuneExtra()
{
    int num;
    FILE *forme;
    if ((forme = fopen("forme.txt","r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    D3.nrsurf=0;
    fscanf(forme,"%d", &num);
    while(num!=-100)
    {
        if(num==-1) ///avem un triunghi
        {
            int linie=0;
            triunghi t1;
            D3.nrsurf++;
            D3.surf[D3.nrsurf].nrpct=3;
            fscanf(forme,"%d", &t1.a.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=t1.a.x;
            fscanf(forme,"%d", &t1.a.y);
            D3.surf[D3.nrsurf].pct[linie][2]=t1.a.y;
            fscanf(forme,"%d", &t1.b.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=t1.b.x;
            fscanf(forme,"%d", &t1.b.y);
            D3.surf[D3.nrsurf].pct[linie][2]=t1.b.y;
            fscanf(forme,"%d", &t1.c.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=t1.c.x;
            fscanf(forme,"%d", &t1.c.y);
            D3.surf[D3.nrsurf].pct[linie][2]=t1.c.y;
        }
        if(num==-3) ///avem un dreptunghi
        {
            int linie=0;
            ParalelogramRegulat p1;
            D3.nrsurf++;
            D3.surf[D3.nrsurf].nrpct=4;
            fscanf(forme,"%d", &p1.a.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p1.a.x;
            fscanf(forme,"%d", &p1.a.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p1.a.y;
            fscanf(forme,"%d", &p1.b.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p1.b.x;
            fscanf(forme,"%d", &p1.b.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p1.b.y;
            fscanf(forme,"%d", &p1.c.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p1.c.x;
            fscanf(forme,"%d", &p1.c.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p1.c.y;
            fscanf(forme,"%d", &p1.d.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p1.d.x;
            fscanf(forme,"%d", &p1.d.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p1.d.y;
        }
        if(num==-2) ///avem un patrat
        {
            int linie=0;
            ParalelogramRegulat p2;
            D3.nrsurf++;
            D3.surf[D3.nrsurf].nrpct=4;
            fscanf(forme,"%d", &p2.a.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p2.a.x;
            fscanf(forme,"%d", &p2.a.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p2.a.y;
            fscanf(forme,"%d", &p2.b.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p2.b.x;
            fscanf(forme,"%d", &p2.b.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p2.b.y;
            fscanf(forme,"%d", &p2.c.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p2.c.x;
            fscanf(forme,"%d", &p2.c.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p2.c.y;
            fscanf(forme,"%d", &p2.d.x);
            D3.surf[D3.nrsurf].pct[++linie][1]=p2.d.x;
            fscanf(forme,"%d", &p2.d.y);
            D3.surf[D3.nrsurf].pct[linie][2]=p2.d.y;
        }
        fscanf(forme,"%d",&num);
    }
    fclose(forme);
}

void desenare(forma s) ///crearea formei
{
    /// forma are un nr de pct si matricea specifica
    int a[N]={0},m=0;
    for(int i=1; i<=s.nrpct; ++i)
        for(int j=1; j<=2; ++j)
            a[++m]=s.pct[i][j];
    if(m==6) desenareTriunghi(a[1],a[2],a[3],a[4],a[5],a[6]);
    else paralelogram(a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8]);
}

void Triunghi_Patrat(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing ul triunghi-patrat
    desenareTriunghi(D3.surf[1].pct[1][1],D3.surf[1].pct[1][2],D3.surf[1].pct[2][1],D3.surf[1].pct[2][2],D3.surf[1].pct[3][1],D3.surf[1].pct[3][2]);
    delay(400);
    cleardevice();
    int lungime=D3.surf[1].pct[3][1]-D3.surf[1].pct[2][1];
    int x1=D3.surf[1].pct[2][1];
    int x2=D3.surf[1].pct[3][1];
    int x3=D3.surf[1].pct[1][1];
    int x4=x3;
    while(x3!=x1 && x4!=x2)
    {
        x3-=50;
        x4+=50;
        paralelogram(x3,D3.surf[1].pct[1][2],x4,D3.surf[1].pct[1][2],x1,D3.surf[1].pct[2][2],x2,D3.surf[1].pct[3][2]);
        delay(400);
        cleardevice();
    }
}

void Triunghi_Dreptunghi(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing ul triunghi-dreptunghi
    desenareTriunghi(D3.surf[1].pct[1][1],D3.surf[1].pct[1][2],D3.surf[1].pct[2][1],D3.surf[1].pct[2][2],D3.surf[1].pct[3][1],D3.surf[1].pct[3][2]);
    delay(400);
    cleardevice();
    int lungime=D3.surf[1].pct[3][1]-D3.surf[1].pct[2][1];
    int x1=D3.surf[1].pct[2][1];
    int x2=D3.surf[1].pct[3][1];
    int x3=D3.surf[1].pct[1][1];
    int x4=x3;
    while(x3!=x1 && x4!=x2)
    {
        x3-=50;
        x4+=50;
        paralelogram(x3,D3.surf[1].pct[1][2],x4,D3.surf[1].pct[1][2],x1,D3.surf[1].pct[2][2],x2,D3.surf[1].pct[3][2]);
        delay(400);
        cleardevice();
    }
    int y1=D3.surf[1].pct[1][2];
    int y2=D3.surf[1].pct[1][2];
    while(y1!=lungime && y2!=lungime)
    {
        y1+=50;
        y2+=50;
        paralelogram(x1,y1,x2,y2,D3.surf[1].pct[2][1],D3.surf[1].pct[2][2],D3.surf[1].pct[3][1],D3.surf[1].pct[3][2]);
        delay(400);
        cleardevice();
    }
}

void Patrat_Triunghi(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing patrat-triunghi
    paralelogram(D3.surf[2].pct[1][1],D3.surf[2].pct[1][2],D3.surf[2].pct[2][1],D3.surf[2].pct[2][2],D3.surf[2].pct[3][1],D3.surf[2].pct[3][2],
                 D3.surf[2].pct[4][1],D3.surf[2].pct[4][2]);
    delay(400);
    cleardevice();
    int x1=D3.surf[2].pct[1][1];
    int x2=D3.surf[2].pct[2][1];
    while(x1!=x2)
    {
        x2-=50;
        x1+=50;
        paralelogram(x1,D3.surf[2].pct[1][2],x2,D3.surf[2].pct[1][2],D3.surf[2].pct[3][1],D3.surf[2].pct[3][2],D3.surf[2].pct[4][1],D3.surf[2].pct[4][2]);
        delay(400);
        cleardevice();
    }
}

void Dreptunghi_Triunghi(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing dreptunghi-triunghi
    paralelogram(D3.surf[3].pct[1][1],D3.surf[3].pct[1][2],D3.surf[3].pct[2][1],D3.surf[3].pct[2][2],D3.surf[3].pct[3][1],D3.surf[3].pct[3][2],
                 D3.surf[3].pct[4][1],D3.surf[3].pct[4][2]);
    delay(400);
    cleardevice();
    int x1=D3.surf[3].pct[1][1];
    int x2=D3.surf[3].pct[2][1];
    while(x1!=x2)
    {
        x2-=50;
        x1+=50;
        paralelogram(x1,D3.surf[3].pct[1][2],x2,D3.surf[3].pct[1][2],D3.surf[3].pct[3][1],D3.surf[3].pct[3][2],D3.surf[3].pct[4][1],D3.surf[3].pct[4][2]);
        delay(400);
        cleardevice();
    }
    int y1=D3.surf[3].pct[3][2];
    int y2=D3.surf[1].pct[2][2];
    while(y1!=y2)
    {
        y1+=50;
        paralelogram(x1,D3.surf[3].pct[1][2],x2,D3.surf[3].pct[1][2],D3.surf[3].pct[3][1],y1,D3.surf[3].pct[4][1],y1);
        delay(300);
        cleardevice();
    }
}

void Patrat_Cerc(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing ul patrat-cerc
    paralelogram(D3.surf[2].pct[1][1],D3.surf[2].pct[1][2],D3.surf[2].pct[2][1],D3.surf[2].pct[2][2],D3.surf[2].pct[3][1],D3.surf[2].pct[3][2],
                 D3.surf[2].pct[4][1],D3.surf[2].pct[4][2]);
    delay(400);
    cleardevice();
    int lungime=D3.surf[2].pct[2][1]-D3.surf[2].pct[1][1];
    int xcerc=(D3.surf[2].pct[1][1]+D3.surf[2].pct[2][1])/2;
    int ycerc=(D3.surf[2].pct[1][2]+D3.surf[2].pct[3][2])/2;
    for (int i=1; i<=D3.surf[2].nrpct; i++)
    {
        D3.surf[2].pct[i][1]=xcerc;
        D3.surf[2].pct[i][2]=ycerc;
        paralelogram(D3.surf[2].pct[1][1],D3.surf[2].pct[1][2],D3.surf[2].pct[2][1],D3.surf[2].pct[2][2],D3.surf[2].pct[3][1],D3.surf[2].pct[3][2],
                     D3.surf[2].pct[4][1],D3.surf[2].pct[4][2]);
        delay(400);
        cleardevice();
    }
    int raza=25;
    while (raza<lungime/2)
    {
        circle(xcerc,ycerc,raza);
        delay(600);
        cleardevice();
        raza+=25;
    }
}

void Dreptunghi_Cerc(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing ul dreptunghi-cerc
    paralelogram(D3.surf[3].pct[1][1],D3.surf[3].pct[1][2],D3.surf[3].pct[2][1],D3.surf[3].pct[2][2],D3.surf[3].pct[3][1],D3.surf[3].pct[3][2],
                 D3.surf[3].pct[4][1],D3.surf[3].pct[4][2]);
    delay(400);
    cleardevice();
    int latime=D3.surf[3].pct[3][2]-D3.surf[3].pct[1][2];
    int xcerc=(D3.surf[3].pct[1][1]+D3.surf[3].pct[2][1])/2;
    int ycerc=(D3.surf[3].pct[1][2]+D3.surf[3].pct[3][2])/2;
    for (int i=1; i<=D3.surf[3].nrpct; i++)
    {
        D3.surf[3].pct[i][1]=xcerc;
        D3.surf[3].pct[i][2]=ycerc;
        paralelogram(D3.surf[3].pct[1][1],D3.surf[3].pct[1][2],D3.surf[3].pct[2][1],D3.surf[3].pct[2][2],D3.surf[3].pct[3][1],D3.surf[3].pct[3][2],
                     D3.surf[3].pct[4][1],D3.surf[3].pct[4][2]);
        delay(400);
        cleardevice();
    }
    int raza=17.5;
    while (raza<latime/2)
    {
        circle(xcerc,ycerc,raza);
        delay(600);
        cleardevice();
        raza+=17.5;
    }
}

void Cerc_Patrat(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing-ul cerc-patrat
    int xcerc=(D3.surf[2].pct[1][1]+D3.surf[2].pct[2][1])/2;
    int ycerc=(D3.surf[2].pct[1][2]+D3.surf[2].pct[3][2])/2;
    int lungime=D3.surf[2].pct[2][1]-D3.surf[2].pct[1][1];
    int raza=lungime/2+1;
    while (raza>1)
    {
        circle(xcerc,ycerc,raza);
        delay(400);
        cleardevice();
        raza-=17.5;
    }
    struct coordonate
    {
        int x;
        int y;
    };
    coordonate patrat[5];
    for (int i=1; i<=4; i++)
    {
        patrat[i].x=D3.surf[2].pct[i][1];
        patrat[i].y=D3.surf[2].pct[i][2];
    }
    D3.surf[2].pct[1][1]=D3.surf[2].pct[2][1]=D3.surf[2].pct[3][1]=D3.surf[2].pct[4][1]=xcerc;
    D3.surf[2].pct[1][2]=D3.surf[2].pct[2][2]=D3.surf[2].pct[3][2]=D3.surf[2].pct[4][2]=ycerc;
    for (int i=1; i<=4; i++)
    {
        D3.surf[2].pct[i][1]=patrat[i].x;
        D3.surf[2].pct[i][2]=patrat[i].y;
        paralelogram(D3.surf[2].pct[1][1],D3.surf[2].pct[1][2],D3.surf[2].pct[2][1],D3.surf[2].pct[2][2],D3.surf[2].pct[3][1],D3.surf[2].pct[3][2],
                     D3.surf[2].pct[4][1],D3.surf[2].pct[4][2]);
        delay(800);
        cleardevice();
    }
}

void Cerc_Dreptunghi(desen D3)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);

    ///morphing-ul cerc-patrat
    int xcerc=(D3.surf[3].pct[1][1]+D3.surf[3].pct[2][1])/2;
    int ycerc=(D3.surf[3].pct[1][2]+D3.surf[3].pct[3][2])/2;
    int latime=D3.surf[3].pct[3][2]-D3.surf[3].pct[1][2];
    int raza=latime/2+1;
    while (raza>1)
    {
        circle(xcerc,ycerc,raza);
        delay(400);
        cleardevice();
        raza-=17.5;
    }
    struct coordonate
    {
        int x;
        int y;
    };
    coordonate patrat [5];
    for (int i=1; i<=4; i++)
    {
        patrat[i].x=D3.surf[3].pct[i][1];
        patrat[i].y=D3.surf[3].pct[i][2];
    }
    D3.surf[3].pct[1][1]=D3.surf[3].pct[2][1]=D3.surf[3].pct[3][1]=D3.surf[3].pct[4][1]=xcerc;
    D3.surf[3].pct[1][2]=D3.surf[3].pct[2][2]=D3.surf[3].pct[3][2]=D3.surf[3].pct[4][2]=ycerc;
    for (int i=1; i<=4; i++)
    {
        D3.surf[3].pct[i][1]=patrat[i].x;
        D3.surf[3].pct[i][2]=patrat[i].y;
        paralelogram(D3.surf[3].pct[1][1],D3.surf[3].pct[1][2],D3.surf[3].pct[2][1],D3.surf[3].pct[2][2],D3.surf[3].pct[3][1],D3.surf[3].pct[3][2],
                     D3.surf[3].pct[4][1],D3.surf[3].pct[4][2]);
        delay(800);
        cleardevice();
    }
}

void transformaDesenul(desen d,desen B,int n)
///functia care va transforma desenul 1 in desenul 2 prin relatia:x3=x1+i*(x2-x1) si y3=y1+i*(y2-y1)
///n reprezinta numarul de transformari
{
    int k,i,j;
    forma s1,s2,s;

    for(i=1;i<=s.nrpct;++i)
        s.pct[i][1]=s.pct[i][2]=0;

    for(i=1; i<=n; ++i)
    {
        for(k=1; k<=d.nrsurf; ++k)
        {
            s1=d.surf[k];
            s2=B.surf[k];
            s.nrpct=s1.nrpct;
            for(j=1; j<=s1.nrpct; ++j)
            {
                s.pct[j][1]=s1.pct[j][1]+i*(s2.pct[j][1]-s1.pct[j][1])/n;
                s.pct[j][2]=s1.pct[j][2]+i*(s2.pct[j][2]-s1.pct[j][2])/n;
            }
            desenare(s);
        }
        delay(1000);
        cleardevice();
    }
    ///morphing B->D
    for(i=1; i<=n; ++i)
    {
        for(k=1; k<=d.nrsurf; ++k)
        {
            s1=B.surf[k];
            s2=d.surf[k];
            s.nrpct=s1.nrpct;
            for(j=1; j<=s1.nrpct; ++j)
            {
                s.pct[j][1]=s1.pct[j][1]+i*(s2.pct[j][1]-s1.pct[j][1])/n;
                s.pct[j][2]=s1.pct[j][2]+i*(s2.pct[j][2]-s1.pct[j][2])/n;
            }
            desenare(s);
        }
        delay(1000);
        cleardevice();
    }
}

void EditorDeAnimatie(desen d,desen B,int n)
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);
    cleardevice();
    for(int i=1; i<=d.nrsurf; ++i)
    {
        desenare(d.surf[i]);
    }
    delay(500);
    cleardevice();
    transformaDesenul(d,B,n);
    delay(500);
    cleardevice();
}

int butonApasat(int x, int y, int &click)
{
    int nrButon;
    if(x>getmaxwidth()-(200+10) && x<getmaxwidth()-10 && y>10 && y<100+16)
    {
        click=true;
        nrButon=0;
    }
    if(x>((getmaxwidth()-300)/2) && x<((getmaxwidth()-320)/2+300) && y>0.4*getmaxheight() && y<0.5*getmaxheight())
    {
        click=true;
        nrButon=1;
    }
    if (x>((getmaxwidth()-300)/2) && x<((getmaxwidth()-320)/2+300) && y>0.6*getmaxheight() && y<0.7*getmaxheight())
    {
        click=true;
        nrButon=2;
    }
    if (x>((getmaxwidth()-300)/2) && x<((getmaxwidth()-320)/2+300) && y>0.8*getmaxheight() && y<0.9*getmaxheight())
    {
        click=true;
        nrButon=3;
    }
    return nrButon;
}

int Buton_Extra(int x,int y,int &click)
{
    int nr_buton;
    if(x>100 && x<300 && y>0.7*inaltimeFereastra && y<0.9*inaltimeFereastra)
    {
        click=true;
        nr_buton=6;
    }
    if(x>100 && x<300 && y>0.4*inaltimeFereastra && y<0.6*inaltimeFereastra)
    {
        click=true;
        nr_buton=7;
    }
    if(x>400 && y>0.7*inaltimeFereastra && x<600 && y<0.9*inaltimeFereastra)
    {
        click=true;
        nr_buton=8;
    }
    if(x>300 && y>0.35*inaltimeFereastra && x<700 && y<0.65*inaltimeFereastra)
    {
        click=true;
        nr_buton=9;
    }
    if(x>lungimeFereastra/2-70 && y>0.31*inaltimeFereastra && x<lungimeFereastra/2+450 && y<0.68*inaltimeFereastra)
    {
        click=true;
        nr_buton=11;
    }
    if(x>lungimeFereastra/2-100 && y>0.6*inaltimeFereastra && x<lungimeFereastra/2+450 && y<0.98*inaltimeFereastra)
    {
        click=true;
        nr_buton=10;
    }
    if(x>lungimeFereastra/2+200 && y>0.6*inaltimeFereastra && x<lungimeFereastra/2+750 && y<0.98*inaltimeFereastra)
    {
        click=true;
        nr_buton=12;
    }
    if(x>lungimeFereastra/2+230 && y>0.31*inaltimeFereastra && x<lungimeFereastra/2+750 && y<0.68*inaltimeFereastra)
    {
        click=true;
        nr_buton=13;
    }
    return nr_buton;
}

void OptiuneExtra()
{
    int click=false;
    readimagefile("M5.jpg",0, 0,getmaxwidth(),getmaxheight());
    readimagefile("E.gif",getmaxwidth()-(200+10),10,getmaxwidth()-10,116);
    readimagefile("p2.gif",100, 0.7*inaltimeFereastra,300, 0.9*inaltimeFereastra);
    readimagefile("p3.gif",100, 0.4*inaltimeFereastra,300, 0.6*inaltimeFereastra);
    readimagefile("p4.gif",400, 0.7*inaltimeFereastra,600, 0.9*inaltimeFereastra);
    readimagefile("p5.gif",300, 0.35*inaltimeFereastra,700, 0.65*inaltimeFereastra);
    readimagefile("p6.gif",lungimeFereastra/2-70, 0.31*inaltimeFereastra, lungimeFereastra/2+450, 0.68*inaltimeFereastra);
    readimagefile("p7.gif",lungimeFereastra/2-100, 0.6*inaltimeFereastra,lungimeFereastra/2+450, 0.98*inaltimeFereastra);
    readimagefile("p8.gif",lungimeFereastra/2+200, 0.6*inaltimeFereastra,lungimeFereastra/2+750, 0.98*inaltimeFereastra);
    readimagefile("p9.gif",lungimeFereastra/2+230, 0.31*inaltimeFereastra,lungimeFereastra/2+750, 0.68*inaltimeFereastra);
    while (!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click )
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            Buton_Extra(x,y,click);
            if(Buton_Extra(x,y,click)==9)
            {
                Patrat_Triunghi(D3);
                OptiuneExtra();
            }
            else if(Buton_Extra(x,y,click)==8)
            {
                Dreptunghi_Triunghi(D3);
                OptiuneExtra();
            }
                else if(Buton_Extra(x,y,click)==7)
                {
                    Triunghi_Dreptunghi(D3);
                    OptiuneExtra();
                }
                    else if(Buton_Extra(x,y,click)==6)
                    {
                        Triunghi_Patrat(D3);
                        OptiuneExtra();
                    }
                        else if(Buton_Extra(x,y,click)==10)
                        {
                            Dreptunghi_Cerc(D3);
                            OptiuneExtra();
                        }
                            else if(Buton_Extra(x,y,click)==11)
                            {
                                Patrat_Cerc(D3);
                                OptiuneExtra();
                            }
                                else if(Buton_Extra(x,y,click)==12)
                                {
                                    Cerc_Dreptunghi(D3);
                                    OptiuneExtra();
                                }
                                    else if(Buton_Extra(x,y,click)==13)
                                    {
                                        Cerc_Patrat(D3);
                                        OptiuneExtra();
                                    }
                                        else if(butonApasat(x,y,click)==0)///daca am apasat pe previous, va iesi din meniu
                                        {
                                            click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                                            cleardevice();
                                        }
            }
    }
}

int Buton_Opt4(int x,int y,int &click)
{
    int buton;
    if(x>100 && x<300 && y>0.4*inaltimeFereastra && y<0.6*inaltimeFereastra)
    {
        click=true;
        buton=1;
    }
    if(x>lungimeFereastra/2-100 && y>0.7*inaltimeFereastra && x<lungimeFereastra/2+100 && y<0.9*inaltimeFereastra)
    {
        click=true;
        buton=2;
    }
    if(x>lungimeFereastra-300 && y>0.4*inaltimeFereastra && x<lungimeFereastra-100 && y<0.6*inaltimeFereastra)
    {
        click=true;
        buton=3;
    }
    return buton;
}

void Optiune4(int n)
{
    int click=false;
    readimagefile("M5.jpg",0,0,getmaxwidth(),getmaxheight());
    readimagefile("E.gif",getmaxwidth()-(200+10),10,getmaxwidth()-10,116);
    readimagefile("B1.gif",100, 0.4*inaltimeFereastra,300, 0.6*inaltimeFereastra);
    readimagefile("B2.gif",lungimeFereastra/2-100, 0.7*inaltimeFereastra,lungimeFereastra/2+100, 0.9*inaltimeFereastra);
    readimagefile("u.gif",lungimeFereastra-300, 0.4*inaltimeFereastra,lungimeFereastra-100, 0.6*inaltimeFereastra);
    while (!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click )
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            Buton_Opt4(x,y,click);
            if(Buton_Opt4(x,y,click)==1)
            {
                EditorDeAnimatie(D1,D2,n);
                Optiune4(n);
            }
            else if(Buton_Opt4(x,y,click)==2)
            {
                EditorDeAnimatie(D2,D,n);
                Optiune4(n);
            }
                else if(Buton_Opt4(x,y,click)==3)
                {
                    EditorDeAnimatie(D,D1,n);
                    Optiune4(n);
                }
                    else if(butonApasat(x,y,click)==0)///daca am apasat pe previous, va iesi din meniu
                    {
                        click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                        cleardevice();
                    }
        }
    }
}

int Butoane3(int x,int y,int &click)
{
    int nrButon;
    if(x>lungimeFereastra-(lungimeFereastra-100) && x<lungimeFereastra-(lungimeFereastra-700) && y>0.75*inaltimeFereastra && y<0.95*inaltimeFereastra)
    {
        click=true;
        nrButon=5;
    }
    if(x>(lungimeFereastra+100)/2-50&& x<(lungimeFereastra)/2+600 && y>0.25*inaltimeFereastra && y<0.45*inaltimeFereastra)
    {
        click=true;
        nrButon=4;
    }
    if(x>lungimeFereastra/2-150 && y>0.5*inaltimeFereastra && x<lungimeFereastra/2+150 && y<0.7*inaltimeFereastra)
    {
        click=true;
        nrButon=6;
    }
    return nrButon;
}

void optiune3(int n)
{
    int click=false;
    readimagefile("M4.jpg",0, 0,getmaxwidth(),getmaxheight());
    readimagefile("image1.jpg",(lungimeFereastra+100)/2-50, 0.25*inaltimeFereastra,(lungimeFereastra)/2+600, 0.45*inaltimeFereastra);
    readimagefile("image2.jpg",lungimeFereastra-(lungimeFereastra-100), 0.75*inaltimeFereastra,lungimeFereastra-(lungimeFereastra-700), 0.95*inaltimeFereastra);
    readimagefile("E.gif",getmaxwidth()-(200+10),10,getmaxwidth()-10,100+16);
    readimagefile("fun.gif",lungimeFereastra/2-150,0.5*inaltimeFereastra,lungimeFereastra/2+150,0.7*inaltimeFereastra);
    while (!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click )
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            butonApasat(x,y,click);
            if(Butoane3(x,y,click)==4)
            {
                Preluare();
                Optiune4(n);
                optiune3(n);
            }
                else if(Butoane3(x,y,click)==5)
                {
                    Preluare_OptiuneExtra();
                    OptiuneExtra();
                    optiune3(n);
                }
                    else if(Butoane3(x,y,click)==6)
                    {
                        Distractie();
                        optiune3(n);
                    }
                        else if(butonApasat(x,y,click)==0)///daca am apasat pe previous, va iesi din meniu
                        {
                            click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                            cleardevice();
                        }
        }
    }
}

void optiune2()
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    setcolor(BLACK);
    Preluare();
    for(int i=1; i<=D1.nrsurf; ++i)
    {
        desenare(D1.surf[i]);
    }
    delay(700);
    cleardevice();
    for(int i=1; i<=D2.nrsurf; ++i)
    {
        desenare(D2.surf[i]);
    }
    delay(700);
    cleardevice();
    for(int i=1; i<=D.nrsurf; ++i)
    {
        desenare(D.surf[i]);
    }
    delay(700);
    cleardevice();
}

void optiune1()
{
    readimagefile("M.jpg",0, 0, getmaxwidth(),getmaxheight());
    readimagefile("E.gif",getmaxwidth()-(200+10),10,getmaxwidth()-10,106+10);
    int click=false;
    while (!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click )
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            if(butonApasat(x,y,click)==0)///daca am apasat pe previous, va iesi din meniu
            {
                click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                cleardevice();///aici am golit fereastra
            }
        }
    }
}

void meniuPrincipal(int n)
{
    int click=false;
    readimagefile("mor.jpg",0, 0,getmaxwidth(),getmaxheight());
    readimagefile("B1.gif",(lungimeFereastra-300)/2, 0.4*inaltimeFereastra,(lungimeFereastra-300)/2+300, 0.5*inaltimeFereastra);
    readimagefile("B2.gif",(lungimeFereastra-300)/2, 0.6*inaltimeFereastra,(lungimeFereastra-300)/2+300, 0.7*inaltimeFereastra);
    readimagefile("B3.jpg",(lungimeFereastra-300)/2, 0.8*inaltimeFereastra,(lungimeFereastra-300)/2+300, 0.9*inaltimeFereastra);

    while (!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click )
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            butonApasat(x,y,click);
        }
    }
    cleardevice();///aici am golit fereastra
    int x=mousex();
    int y=mousey();
    if(butonApasat(x,y,click)==1)///am apasat primul buton din meniu
    {
        optiune1();
        meniuPrincipal(n);
        finalMeniu=1;
    }
        else if(butonApasat(x,y,click)==2) ///am apasat al doilea buton din meniu
        {
            optiune2();
            cleardevice();
            meniuPrincipal(n);
            finalMeniu=1;
        }
            else if(butonApasat(x,y,click)==3) ///am apasat al treilea buton din meniu
            {
                optiune3(n);
                meniuPrincipal(n);
                finalMeniu=1;
            }
}

void Fereastra()
{
    int max=getmaxcolor();
    for(int a=0; a<=max; ++a)
    {
        cleardevice();
        setbkcolor(WHITE);
        if(a==BLACK)
            setcolor(WHITE);
    }
    lungimeFereastra=getmaxwidth();
    inaltimeFereastra=getmaxheight();
}

void Start(int n)
{
    while(true)
    {
        initwindow(getmaxwidth(),getmaxheight(),"M");
        Fereastra();
        meniuPrincipal(n);
        if(finalMeniu)
        {
            readimagefile("M2.jpg",0, 0,getmaxwidth(),getmaxheight()); ///background
            readimagefile("E.gif",getmaxwidth()-(200+10),10,getmaxwidth()-10,106+10);
            bool click=false;
            while (!click)
            {
                if(ismouseclick(WM_LBUTTONDOWN) && !click )
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    int x=mousex();
                    int y=mousey();
                    if(x>getmaxwidth()-(200+10) && x<getmaxwidth()-10 && y>10 && y<(200+10) )///daca am apasat pe return, va iesi din setari
                    {
                        click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                        cleardevice();///aici am golit fereastra
                    }
                }
            }
        }
    }
    getch();
    closegraph();
}

int main()
{
    int n;
    cout<<"Introduceti numarul de transformari pe care doriti sa le vedeti: ";
    cin>>n;
    Start(n);
    getch();
    closegraph();
    return 0;
}

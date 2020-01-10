#include <TXLib.h>
int i,j,b,kb,schit=0;
char bm[2],sco[3];
char a[50];
void Score();
void Moving();
class Ger
{
    public:
    int spx,spy,x,y,vx,vy,si,plx,ply;
    HDC s;
    void Pravo();
    void Levo();
    void Vniz();
    void Vverh();
    void Draw();
};
class Card
{
    public:
    int t,shi,vis,q[36][23],bx,by;
    HDC dia;
    void Geon();
    void Paint();
    void Chan(int,int,int);
    void Boom();
};
Ger zom{0,0,0,0,30,30,60};
Card pole{60,18,10};
void Ger::Pravo()
    {
        x+=5;
        plx=x/si;
    };
void Ger::Levo()
    {
        x-=5;
        plx=x/si;
    };
void Ger::Vniz()
    {
        y+=5;
        ply=y/si;
    };
void Ger::Vverh()
    {
        y-=5;
        ply=y/si;
    };
void Ger::Draw()
    {
        txSetFillColor(TX_PINK);
        //txRectangle(x,y,x+30,y+30);
        Win32::TransparentBlt (txDC(),x-32,y-32,60,60,s,spx,spy,64,64,-1);
    }
void Card::Geon()
    {
        for(i=0;i<shi;i++)
            for(j=0;j<vis;j++)
                q[i][j]=rand()%2;
        bx=rand()%18;
        by=rand()%10;
        q[bx][by]=5;
    };
void Card::Chan(int x,int y,int u)
    {
        q[x][y]=u;
    };
void Card::Paint()
    {
       for(i=0;i<shi;i++)
            for(j=0;j<vis;j++)
            {
                if(q[i][j]==1)
                    //txSetFillColor(TX_GRAY);
                    Win32::TransparentBlt(txDC(),t*i,t*j,t,t,dia,60,0,30,30,-1);
                if(q[i][j]==0)
                {
                    //txSetFillColor(TX_BLUE);
                    //txSetColor(TX_BLUE);
                    Win32::TransparentBlt(txDC(),t*i,t*j,t,t,dia,90,0,30,30,-1);
                }
                //txRectangle(t*i,t*j,t*i+t,t*j+t);
                if(q[i][j]==5)
                    Win32::TransparentBlt(txDC(),t*i,t*j,t,t,dia,0,0,30,30,-1);
                if(q[i][j]==10)
                    Win32::TransparentBlt(txDC(),t*i,t*j,t,t,dia,30,0,30,30,-1);
                if(GetAsyncKeyState(VK_F1))
                {
                    if(q[i][j]==10)
                    {
                        q[i][j%10]=0;q[i-1][(j-1)%10]=0;q[i-1][(j%10)]=0;
                        q[i][(j-1)%10]=0;q[i][(j+1)%10]=0;q[i+1][j%10]=0;
                        q[i-1][(j+1)%10]=0;q[i+1][(j+1)%10]=0;q[i+1][(j-16)%10]=0;
                    }
                }

            }
    };
    void Moving()
    {
            if(GetAsyncKeyState(VK_RIGHT))
            {
                if(pole.q[(zom.x+5)/zom.si][zom.y/zom.si]==0)
                    zom.Pravo();
                    b=1;
                    zom.spy=192;
                zom.spx=(zom.spx+64);
                if(zom.spx>192)
                    zom.spx=0;
            }
            if(GetAsyncKeyState(VK_LEFT))
            {
                if(pole.q[(zom.x-5)/zom.si][zom.y/zom.si]==0)
                    zom.Levo();
                    b=2;
                zom.spy=128;
                zom.spx=(zom.spx+64);
                if(zom.spx>192)
                    zom.spx=0;
            }
            if(GetAsyncKeyState(VK_DOWN))
            {
                if(pole.q[zom.x/zom.si][(zom.y+20)/zom.si]==0)
                    zom.Vniz();
                    b=3;
                zom.spy=64;
                zom.spx=(zom.spx+64);
                if(zom.spx>192)
                    zom.spx=0;
            }
            if(GetAsyncKeyState(VK_UP))
            {
                if(pole.q[zom.x/zom.si][(zom.y-20)/zom.si]==0)
                    zom.Vverh();
                b=4;
                zom.spy=0;
                zom.spx=(zom.spx+64);
                if(zom.spx>192)
                    zom.spx=0;
            }
        };

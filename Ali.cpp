#include <TXLib.h>
#include "Classes.h"
int main()
{
    txCreateWindow(1100,700);
    HDC Phon;
    txSetFillColour(TX_WHITE);
    pole.dia=txLoadImage("diamond.bmp");
    zom.s=txLoadImage("smile.bmp");
    pole.Geon();
    pole.q[zom.x/zom.si][zom.x/zom.si]=0;
    zom.plx=1;
    zom.ply=2;
    kb=5;
    printf("Whats your name?");
    gets(a);
    int add[10][18] = {{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
                       {1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
                       {0,0,0,0,1,1,1,1,1,0,0,1,0,5,0,0,0,0},
                       {0,1,1,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0},
                       {0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0},
                       {0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0},
                       {0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0},
                       {0,1,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0},
                       {0,1,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0},
                       {0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0}};
    for(i=0;i<18;i++)
        for(j=0;j<10;j++)
            pole.q[i][j]=add[j][i];
        pole.bx=13;
        pole.by=2;
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txSetFillColor(TX_GREEN);
        txClear();
        if(pole.q[pole.bx][pole.by]==0)
        {
            pole.Geon();
            kb=5;
            pole.Chan(zom.plx,zom.ply,0);
            schit++;
        }
        Moving();
        if(GetAsyncKeyState(VK_SPACE)&&(kb==0))
        {
            txSetFillColor(TX_RED);
            txClear();
            txSelectFont ("Arial", 120, 0, FW_BOLD);
            txSetColor(TX_BLACK);
            txDrawText (0, 100, 700, 600,"GAME OVER");
            txSelectFont ("Arial", 80, 0, FW_BOLD);
            txDrawText (0, 100, 700, 800,"Very good job");
            txSelectFont ("Arial", 50, 0, FW_BOLD);
            txDrawText (0, 100, 1200, 900,a);
            txDrawText (0, 100, 700, 1000,"Score: ");
            txDrawText (0, 100, 1000, 1000,sco);
            return 0;
        }
        bm[0]=kb+'0';
        bm[1]= 0;
        sco[0]=schit/10+'0';
        sco[1]=schit%10+'0';
        sco[2]=0;
        pole.Paint();
        txSelectFont ("Arial", 30, 0, FW_BOLD);
        txSetColor(TX_BLACK);
        txDrawText (0, 100, 300, 1200,"Number of bombs: ");
        txDrawText (250, 100, 310, 1200,bm);
        txDrawText (0, 100, 850, 1200,"Score: ");
        txDrawText (500, 100, 550, 1200,sco);
        if(GetAsyncKeyState(VK_SPACE)&&(kb>0))
        {
            if(b==1)
                pole.q[zom.plx+1][zom.ply]=10;
            if(b==2)
                pole.q[zom.plx-1][zom.ply]=10;
            if(b==3)
                pole.q[zom.plx][zom.ply+1]=10;
            if(b==4)
                pole.q[zom.plx][zom.ply-1]=10;
            kb--;
            while(GetAsyncKeyState(VK_SPACE));
        }
        if(b==1)
            Win32::TransparentBlt (txDC(),(zom.plx+1)*60,(zom.ply)*60, 60, 60, pole.dia,0,30,30,30,-1);
        if(b==2)
            Win32::TransparentBlt (txDC(),(zom.plx-1)*60,(zom.ply)*60, 60, 60, pole.dia,0,30,30,30,-1);
        if(b==3)
            Win32::TransparentBlt (txDC(),(zom.plx)*60,(zom.ply+1)*60, 60, 60, pole.dia,0,30,30,30,-1);
        if(b==4)
            Win32::TransparentBlt (txDC(),(zom.plx)*60,(zom.ply-1)*60, 60, 60, pole.dia,0,30,30,30,-1);
        zom.Draw();
        txSleep(100);
    }
    return 0;
}

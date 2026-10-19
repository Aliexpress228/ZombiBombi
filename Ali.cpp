#include "TXLib.h"
#include "Classes.h"

int main()
{
    txCreateWindow(1080, 700);

    pole.dia = txLoadImage("diamond.bmp");
    zom.s = txLoadImage("smile.bmp");

    pole.Geon();

    int add[10][18] = {
        { 0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,1,1,1,1,1,0,0,1,0,5,0,0,0,0 },
        { 0,1,1,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0 },
        { 0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0 },
        { 0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0 },
        { 0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0 },
        { 0,1,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0 },
        { 0,1,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0 },
        { 0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0 }
    };

    for (i = 0; i < 18; i++)
        for (j = 0; j < 10; j++)
            pole.q[i][j] = add[j][i];

    pole.bx = 13;
    pole.by = 2;

    zom.plx = 1;
    zom.ply = 2;
    zom.x = zom.plx * zom.si;
    zom.y = zom.ply * zom.si;

    kb = 5;
    b = 1;

    bool prevLMB = false;   // состояние ЛКМ в прошлом кадре
    bool prevSpace = false;   // состояние пробела в прошлом кадре
    txSetFillColor(TX_GREEN);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txClear();
        pole.Paint();
        zom.Draw();
        // Переход на новый уровень
        if (pole.q[pole.bx][pole.by] == 0)
        {
            pole.Geon();
            kb = 5;
            pole.Chan(zom.plx, zom.ply, 0);
            schit++;
        }

        Moving();       

        // HUD
        bm[0] = kb + '0';      bm[1] = 0;
        sco[0] = schit / 10 + '0';
        sco[1] = schit % 10 + '0';
        sco[2] = 0;

        // ---- HUD внизу окна (карта занимает 0..600, окно 700) ----
        txSelectFont("Arial", 28, 0, FW_BOLD);
        txSetColor(TX_BLACK);

        // Левая группа: Bombs
        txDrawText(20, 615, 170, 665, "Bombs:");
        txDrawText(150, 615, 240, 665, bm);
        txDrawText(280, 615, 400, 665, "Score:");
        txDrawText(390, 615, 500, 665, sco);
        txSelectFont("Arial", 22, 0, FW_BOLD);
        txDrawText(540, 620, 1080, 665, "WASD - move | LMB - bomb | SPACE - boom");

        // ---- ЛКМ: поставить бомбу (один клик = одна бомба) ----
        bool curLMB = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
        if (curLMB && !prevLMB)
        {
            if (kb > 0) {
                int bx = zom.plx;
                int by = zom.ply;
                if (b == 1) bx += 1;
                if (b == 2) bx -= 1;
                if (b == 3) by += 1;
                if (b == 4) by -= 1;

                if (bx >= 0 && bx < 18 && by >= 0 && by < 10 && pole.q[bx][by] == 0)
                {
                    pole.q[bx][by] = 10;
                    kb--;
                }
            }
            else
            {
                int bx = zom.plx;
                int by = zom.ply;
                if (b == 1) bx += 1;
                if (b == 2) bx -= 1;
                if (b == 3) by += 1;
                if (b == 4) by -= 1;
                if (bx >= 0 && bx < 18 && by >= 0 && by < 10 && pole.q[bx][by] == 0) {
                    txSetFillColor(TX_RED);
                    txClear();
                    txSelectFont("Arial", 120, 0, FW_BOLD);
                    txSetColor(TX_BLACK);
                    txDrawText(0, 100, 700, 600, "GAME OVER");
                    txSelectFont("Arial", 80, 0, FW_BOLD);
                    txDrawText(0, 100, 700, 800, "Bombs ran out");
                    txSelectFont("Arial", 50, 0, FW_BOLD);
                    txDrawText(0, 100, 1200, 900, a);
                    txDrawText(0, 100, 700, 1000, "Score: ");
                    txDrawText(0, 100, 1000, 1000, sco);
                    return 0;
                }
            }
        }
        prevLMB = curLMB;

        // ---- Пробел: взорвать все бомбы (один раз на нажатие) ----
        bool curSpace = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
        if (curSpace && !prevSpace)
        {
            pole.Boom();
        }
        prevSpace = curSpace;

        // Призрачная бомба — куда встанет
        if (b == 1) Win32::TransparentBlt(txDC(), (zom.plx + 1) * 60, zom.ply * 60, 60, 60, pole.dia, 0, 30, 30, 30, -1);
        if (b == 2) Win32::TransparentBlt(txDC(), (zom.plx - 1) * 60, zom.ply * 60, 60, 60, pole.dia, 0, 30, 30, 30, -1);
        if (b == 3) Win32::TransparentBlt(txDC(), zom.plx * 60, (zom.ply + 1) * 60, 60, 60, pole.dia, 0, 30, 30, 30, -1);
        if (b == 4) Win32::TransparentBlt(txDC(), zom.plx * 60, (zom.ply - 1) * 60, 60, 60, pole.dia, 0, 30, 30, 30, -1);
        txSleep(10);
    }
    return 0;
}
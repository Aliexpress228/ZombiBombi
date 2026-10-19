#include "TXLib.h"

int i, j, b = 1, kb = 5, schit = 0;
char bm[2], sco[3];
char a[50];

void Score();
void Moving();

class Ger
{
public:
    int spx, spy, x, y, vx, vy, si, plx, ply;
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
    int t, shi, vis, q[36][23], bx, by;
    HDC dia;
    void Geon();
    void Paint();
    void Chan(int, int, int);
    void Boom();
};

Ger  zom{ 0, 0, 0, 0, 30, 30, 60, 0, 0 };
Card pole{ 60, 18, 10 };

void Ger::Pravo() { x += 5; plx = (x + si / 2) / si; }
void Ger::Levo() { x -= 5; plx = (x + si / 2) / si; }
void Ger::Vniz() { y += 5; ply = (y + si / 2) / si; }
void Ger::Vverh() { y -= 5; ply = (y + si / 2) / si; }

void Ger::Draw()
{
    Win32::TransparentBlt(txDC(), x, y, si, si, s, spx, spy, 64, 64, -1);
}

void Card::Geon()
{
    for (i = 0; i < shi; i++)
        for (j = 0; j < vis; j++)
            q[i][j] = rand() % 2;
    bx = rand() % 18;
    by = rand() % 10;
    q[bx][by] = 5;
}

void Card::Chan(int x, int y, int u) { q[x][y] = u; }

void Card::Paint()
{
    for (i = 0; i < shi; i++)
        for (j = 0; j < vis; j++)
        {
            if (q[i][j] == 1)  Win32::TransparentBlt(txDC(), t * i, t * j, t, t, dia, 60, 0, 30, 30, -1);
            if (q[i][j] == 0)  Win32::TransparentBlt(txDC(), t * i, t * j, t, t, dia, 90, 0, 30, 30, -1);
            if (q[i][j] == 5)  Win32::TransparentBlt(txDC(), t * i, t * j, t, t, dia, 0, 0, 30, 30, -1);
            if (q[i][j] == 10) Win32::TransparentBlt(txDC(), t * i, t * j, t, t, dia, 30, 0, 30, 30, -1);
        }
}

void Card::Boom()
{
    int bombs[36][2];
    int nb = 0;
    for (int ii = 0; ii < shi; ii++)
        for (int jj = 0; jj < vis; jj++)
            if (q[ii][jj] == 10) { bombs[nb][0] = ii; bombs[nb][1] = jj; nb++; }

    for (int k = 0; k < nb; k++)
        for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
            {
                int ni = bombs[k][0] + di;
                int nj = bombs[k][1] + dj;
                if (ni >= 0 && ni < shi && nj >= 0 && nj < vis)
                    q[ni][nj] = 0;
            }
}

void Moving()
{
    const int speed = 5;

    // D Ч вправо
    if (GetAsyncKeyState('D') & 0x8000)
    {
        b = 1; zom.spy = 192;
        zom.spx = (zom.spx + 64) % 256;
        int nx = zom.x + speed;
        int lt = nx / zom.si;
        int rt = (nx + zom.si - 1) / zom.si;
        if (rt < 18 && pole.q[lt][zom.ply] == 0 && pole.q[rt][zom.ply] == 0)
            zom.Pravo();
    }
    // A Ч влево
    if (GetAsyncKeyState('A') & 0x8000)
    {
        b = 2; zom.spy = 128;
        zom.spx = (zom.spx + 64) % 256;
        int nx = zom.x - speed;
        if (nx >= 0 && pole.q[nx / zom.si][zom.ply] == 0)
            zom.Levo();
    }
    // S Ч вниз
    if (GetAsyncKeyState('S') & 0x8000)
    {
        b = 3; zom.spy = 64;
        zom.spx = (zom.spx + 64) % 256;
        int ny = zom.y + speed;
        int ut = ny / zom.si;
        int bt = (ny + zom.si - 1) / zom.si;
        if (bt < 10 && pole.q[zom.plx][ut] == 0 && pole.q[zom.plx][bt] == 0)
            zom.Vniz();
    }
    // W Ч вверх
    if (GetAsyncKeyState('W') & 0x8000)
    {
        b = 4; zom.spy = 0;
        zom.spx = (zom.spx + 64) % 256;
        int ny = zom.y - speed;
        if (ny >= 0 && pole.q[zom.plx][ny / zom.si] == 0)
            zom.Vverh();
    }
}
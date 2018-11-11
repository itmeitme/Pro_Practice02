#include <stdio.h>
#define MAX_INT 2000000000
#define RANGE(x,y,R,C) (((1<=x&&x<=R)&&(1<=y&&y<=C))?1:0)
 
int R, C, D, result = 0, map[201][201], s[2], stval = 0, dijk[201][201];
int dx[4] = { -1,1,0,0 }, dy[4] = { 0,0,-1,1 };
int q[300000][2], pop[2], head = 0, rear = 0;
 
void mSet(int (*arr)[201], int r, int c, int val)
{
    for (int x = 1; x <= r; x++) {
        for (int y = 1; y <= c; y++)
            arr[x][y] = val;
    }
}
 
void qPush(int x, int y)
{
    if (rear >= 4000000) return;
    q[rear][0] = x, q[rear][1] = y;
    rear++;
}
 
void qPop(void)
{
    if (head >= rear) return;
    pop[0] = q[head][0], pop[1] = q[head][1];
    q[head][0] = q[head][1] = 0;
    head++;
}
 
bool qEmpty(void)
{
    if (head == rear) return true;
    else return false;
}
 
int qSize(void)
{
    return (rear - head);
}
 
void dijkBfs(int goalx, int goaly)
{
    dijk[s[0]][s[1]] = stval;
    for (int i = 0; i < 4; i++) {
        int gox, goy;
        if (i < 2 && (1 < s[1]&&s[1] < C)) continue;
        gox = s[0] + dx[i], goy = s[1] + dy[i];
        if (!(RANGE(gox, goy, R, C))) continue;
        else {
            if (dijk[gox][goy] > (dijk[s[0]][s[1]] + map[gox][goy])) {
                if (dijk[goalx][goaly] > (dijk[s[0]][s[1]] + map[gox][goy])) {
                    dijk[gox][goy] = dijk[s[0]][s[1]] + map[gox][goy];
                    if(gox!=goalx || goy!=goaly) qPush(gox, goy);
                }
            }
        }
    }
 
    while (!(qEmpty())) {
        int qsz = qSize();
        for (int a = 0; a < qsz; a++) {
            qPop();
            for (int i = 0; i < 4; i++) {
                if (i < 2 && (1 < pop[1] && pop[1] < C)) continue;
                int gox = pop[0] + dx[i], goy = pop[1] + dy[i];
                if (dijk[pop[0]][pop[1]] > dijk[goalx][goaly]) continue;
                if (!(RANGE(gox, goy, R, C))) continue;
                else {
                    if (dijk[gox][goy] > (dijk[pop[0]][pop[1]] + map[gox][goy])) {
                        if (dijk[goalx][goaly] > (dijk[pop[0]][pop[1]] + map[gox][goy])) {
                            dijk[gox][goy] = dijk[pop[0]][pop[1]] + map[gox][goy];
                            if (gox != goalx || goy != goaly) qPush(gox, goy);
                        }
                    }
                }
            }
        }
    }
}
 
void inputData(void)
{
    scanf("%d %d", &R, &C);
    for (int x = 1; x <= R; x++) {
        for (int y = 1; y <= C; y++) {
            scanf("%d",&map[x][y]);
            dijk[x][y] = MAX_INT;
        }
    }
    scanf("%d",&D);
    s[0] = s[1] = 1;
    stval = map[1][1];
    for (int i = 0; i < D; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        dijkBfs(x, y);
        if (i < D - 1) {
            s[0] = x, s[1] = y;
            stval = dijk[x][y];
            mSet(dijk, R, C, MAX_INT);
            head = rear = 0;
        }
        else result = dijk[x][y];
    }
}
 
int main(void)
{
    inputData();
    printf("%d\n", result);
    return 0;
}

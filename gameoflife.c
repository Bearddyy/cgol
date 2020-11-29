#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <unistd.h>

#define addIF(x,y,sizeX,sizeY) if(((x) >= 0) || ((y) >= 0) || ((x) < (sizeX)-1) || ((y) < (sizeY){ accum += map[x][y];}
 

static void msleep(int msec)
{
    usleep(msec * 1000);
}

void printMap(void *mapP, int sizeX, int sizeY)
{
    int (*map)[sizeY] = (int(*)[sizeY])mapP;
    int i,j;

    for (j = 0; j < sizeY; j++)
        printf("#");
    printf("\n");

    for (i = 0; i < sizeX; i++)
    {
        for (j = 0; j < sizeY; j++)
        {
            if (map[i][j] == 1)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void playRound(void *mapP, int sizeX, int sizeY)
{
    int (*map)[sizeY] = (int(*)[sizeY])mapP;
    static int i, j;
    int newMap[sizeX][sizeY];

    for (i = 0; i < sizeX; i++)
        for (j = 0; j < sizeY; j++)
            newMap[i][j] = 0;

    static int accum = 0;

    for (i = 1; i < (sizeX-1); i++)
    {
        for (j = 1; j < (sizeY-1); j++)
        {
            //accumulate neighbours
            accum = 0;
            accum += map[i-1][j-1];
            accum += map[i-1][j];
            accum += map[i-1][j+1];
            accum += map[i][j-1];
            //accum += map[i][j];
            accum += map[i][j+1];
            accum += map[i+1][j-1];
            accum += map[i+1][j];
            accum += map[i+1][j+1];
            
            if (accum == 3)
            {
                newMap[i][j] = 1;
            }

            if (accum == 2)
            {
                if (map[i][j] == 1)
                    newMap[i][j] = 1;
            }
        }
    }

    for (i = 0; i < sizeX; i++)
        for (j = 0; j < sizeY; j++)
            map[i][j] = newMap[i][j];

}

void randomize(void *mapP, int sizeX, int sizeY)
{
    int (*map)[sizeY] = (int(*)[sizeY])mapP;
    srand(time(0));

    int i,j;
    for (i = 0; i < sizeX; i++)
        for (j = 0; j < sizeY; j++)
            map[i][j] = (int) (rand() & 1);
}

int main(int argc, char const *argv[])
{
    static int t, sizeX, sizeY, i;
    /* 
    int sizeX = 10;
    int sizeY = 100;
    */

    char* p;

    long arg = strtol(argv[1], &p, 10);
    sizeX = arg;

    arg = strtol(argv[2], &p, 10);
    sizeY = arg;

    arg = strtol(argv[2], &p, 10);
    t = arg;

    int map[sizeX][sizeY];

    randomize(map, sizeX, sizeY);

    while (1) {
        playRound(map, sizeX, sizeY);
        printMap(map, sizeX, sizeY);
        msleep(50);
    }

    return 0;
}

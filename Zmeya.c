#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#define row 11
#define col 11
enum control {W=119,A=97,S=115,D=100};
#define W 119
#define A 97
#define S 115
#define D 100
int respawn (int* ap,int snake[2][row*col], int size)
{
        bool ok=0;
        do {
                ok=0;
                ap[0]=(rand()%(row-2))+1;
                ap[1]=(rand()%(col-2))+1;
                for (int j = 0; j < size; j++) {
                        if ((ap[0]==snake[0][j])&&(ap[1]==snake[1][j]))
                                ok=1;
                }
        } while (ok==1);
}
int main ()
{
        initscr();
        int snake[2][row*col]={-1};
        snake[0][0]=4;
        snake[1][0]=4;
        int lastcoord[2];
        int size=0;
        int field [row][col]={0};
        int apple[2]={5,5};
        for (int i=0; i<row; i++)
                for (int j=0; j<col; j++)
                        if ((i==0)||(j==0)||((j+1)==col)||((i+1)==row)) field[i][j]=3;
        field[apple[0]][apple[1]]=2;

        for (int i = 0; i < 100; i++)
                if (snake[0][i]!=-1) field[snake[0][i]][snake[1][i]]=1; field[0][0]=3;

        for (int i=0; i<row; i++) { //Создаем поле и выводим его в поток
                for (int j=0; j<col; j++)
                        switch(field[i][j]) {
                        case 0:
                                printw("  ");// Пустота
                                break;
                        case 1:
                                printw("1 "); // Змея
                                break;
                        case 2:
                                printw("2 ");// Яблоко
                                break;
                        case 3:
                                printw("- ");// Стена
                                break;
                        }
                printw("\n");
        }
        int key,oldkey=W;
        int speed=800;
        while(true) {
                refresh();
                timeout(speed-(size*25));
                key=getch();
                if (key==ERR) key=oldkey;
                else oldkey=key;
                switch(key) { //представляю без этого свича, а нажатие клавиши просто будет управлять минусом или плюсом
                case W:
                        switch (field[snake[0][0]-1][snake[1][0]])
                        {
                        case 0:
                                field[ snake[0][size] ][ snake[1][size] ]=0;
                                for (int i=0; i<size; i++)//size 1
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[0][0]--;
                                break;

                        case 1:
                                endwin();
                                return 0;
                                break;
                        case 2:
                                lastcoord[0]=snake[0][size];
                                lastcoord[1]=snake[1][size];
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[0][0]--;
                                size++;
                                snake[0][size]=lastcoord[0];
                                snake[1][size]=lastcoord[1];
                                respawn(&apple[0],snake,size);
                                field[ apple[0] ][ apple[1] ]=2;
                                break;

                        case 3:
                                endwin();
                                return 0;
                                break;
                        }
                        break;//Вверх
                case S:
                        switch (field[snake[0][0]+1][snake[1][0]])
                        {
                        case 0:
                                field[ snake[0][size] ][ snake[1][size] ]=0;
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[0][0]++;
                                break;

                        case 1:
                                endwin();
                                return 0;
                                break;
                        case 2:
                                lastcoord[0]=snake[0][size];
                                lastcoord[1]=snake[1][size];
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[0][0]++;
                                size++;
                                snake[0][size]=lastcoord[0];
                                snake[1][size]=lastcoord[1];
                                respawn(&apple[0],snake,size);
                                field[ apple[0] ][ apple[1] ]=2;
                                break;

                        case 3:
                                endwin();
                                return 0;
                                break;
                        }
                        break; //Вниз
                case A:
                        switch (field[snake[0][0]][snake[1][0]-1])
                        {
                        case 0:
                                field[ snake[0][size] ][ snake[1][size] ]=0;
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[1][0]--;
                                break;

                        case 1:
                                endwin();
                                return 0;
                                break;
                        case 2:
                                lastcoord[0]=snake[0][size];
                                lastcoord[1]=snake[1][size];
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[1][0]--;
                                size++;
                                snake[0][size]=lastcoord[0];
                                snake[1][size]=lastcoord[1];
                                respawn(&apple[0],snake,size);
                                field[ apple[0] ][ apple[1] ]=2;
                                break;

                        case 3:
                                endwin();
                                return 0;
                                break;
                        }
                        break;
                case D:
                        switch (field[snake[0][0]][snake[1][0]+1])
                        {
                        case 0:
                                field[ snake[0][size] ][ snake[1][size] ]=0;
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[1][0]++;
                                break;

                        case 1:
                                endwin();
                                return 0;
                                break;
                        case 2:
                                lastcoord[0]=snake[0][size];
                                lastcoord[1]=snake[1][size];
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[1][0]++;
                                size++;
                                snake[0][size]=lastcoord[0];
                                snake[1][size]=lastcoord[1];
                                respawn(&apple[0],snake,size);
                                field[ apple[0] ][ apple[1] ]=2;
                                break;

                        case 3:
                                endwin();
                                return 0;
                                break;
                        }
                        break;
                }
                clear();
                for (int i = 0; i < row*col; i++) {
                        if (snake[0][i]!=-1) field[snake[0][i]][snake[1][i]]=1;
                } field[0][0]=3;
                for (int i=0; i<row; i++) { //Создаем поле и выводим его в поток
                        for (int j=0; j<col; j++)
                                switch(field[i][j]) {
                                case 0:
                                        printw("  ");// Пустота
                                        break;
                                case 1:
                                        printw("1 "); // Змея
                                        break;
                                case 2:
                                        printw("2 ");// Яблоко
                                        break;
                                case 3:
                                        printw("- ");// Стена
                                        break;
                                }
                        printw("\n");
                }
        }
        endwin();
        return 0;
}

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#define fx 11
#define fy 11
enum control {W=119,A=97,S=115,D=100};
#define W 119
#define A 97
#define S 115
#define D 100
int main ()
{
        initscr();
        int key;
        int snake[2][fx*fy]={-1};
        snake[0][0]=4;
        snake[1][0]=4;
        int lastcoord[2];
        int size=0;
        int field [fx][fy]={0};
        int apple[2]={5,5};
        for (int i=0; i<fx; i++)
                for (int j=0; j<fy; j++)
                        if ((i==0)||(j==0)||((j+1)==fy)||((i+1)==fx)) field[i][j]=3;
        field[apple[0]][apple[1]]=2;

        for (int i = 0; i < 100; i++)
                if (snake[0][i]!=-1) field[snake[0][i]][snake[1][i]]=1; field[0][0]=3;

        for (int i=0; i<fx; i++) { //Создаем поле и выводим его в поток
                for (int j=0; j<fy; j++)
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
        while(true) {
                refresh();
                key=getch();
                switch(key) { //представляю без этого свича, а нажатие клавиши просто будет управлять минусом или плюсом
                case W:
                        switch (field[snake[0][0]-1][snake[1][0]])
                        {
                        case 0:
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[0][0]++;
                                break;

                        case 1:
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
                                break;

                        case 3:
                                return 0;
                                break;
                        }
                        break;//Вверх
                case S:
                        switch (field[snake[0][0]-1][snake[1][0]])
                        {
                        case 0:
                                for (int i=0; i<size; i++)
                                {
                                        snake[0][size-i]=snake[0][size-i-1];
                                        snake[1][size-i]=snake[1][size-i-1];
                                }
                                snake[0][0]++;
                                break;

                        case 1:
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
                                break;

                        case 3:
                                return 0;
                                break;
                        }
                        break; //Вниз
                case A:
                        snake[0][0]--;
                        break;//влево
                case D:
                        snake[0][0]++;
                        break;
                }
	clear();
	 for (int i=0; i<fx; i++) { //Создаем поле и выводим его в поток
                for (int j=0; j<fy; j++)
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
                //тут чистим всё поле и рисуем новое поверх него
        }
        endwin();
        return 0;
}

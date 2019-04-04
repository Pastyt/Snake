#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#define row 15
#define col 15
#define W 119
#define A 97
#define S 115
#define D 100
/*int getmykey (int *oldkey,int size)
{
        int key;
        timeout(speed-(size*25));
        key=getch();
        if (key==ERR) key=*oldkey;
        else *oldkey=key;
        return key;
   } напоминание о том, какой убогий код я пишу сам */
void hudoznik (int *field)
{
        for (int i=0; i<row; i++) {
                for (int j=0; j<col; j++)
                        switch(field[i*row+j]) {
                        case 0:
                                printw("  "); /* Пустота */
                                break;
                        case 1:
                                printw("1 "); /* Змея */
                                break;
                        case 2:
                                printw("2 "); /* Яблоко */
                                break;
                        case 3:
                                printw("- "); /* Стена */
                                break;
                        }
                printw("\n");
        }
}
int respawn (int* ap,int snake[2][row*col], int size)
{

}
void startfield(int* field, int* apple){
        for (int i=0; i<row; i++)
                for (int j=0; j<col; j++)
                        if ((i==0)||(j==0)||((j+1)==col)||((i+1)==row)) field[i*row+j]=3;

        field[apple[0]*row+apple[1]]=2;
}
void drawsnake(int* snake, int* field) {
        for (int i = 0; i < 100; i++)
                if (snake[i]!=-1) field[snake[i]*row+snake[row*col+i]]=1; field[0]=3;
}
bool moicase(int* snake,int* field, int *size,int* lastcoord, int* apple,int drow,int dcol)
{
        switch (field[(snake[0]+drow)*row+(snake[row*col]+dcol)])
        {
        case 0:
                field[ snake[*size]*row+snake[row*col+*size] ]=0;
                for (int i=0; i<*size; i++)
                {
                        snake[*size-i]=snake[*size-i-1];
                        snake[row*col+*size-i]=snake[row*col+*size-i-1];
                }
                snake[0]+=drow;
                snake[row*col]+=dcol;
                break;

        case 1:
                return 1;
                break;
        case 2:
                lastcoord[0]=snake[*size];
                lastcoord[1]=snake[row*col+*size];
                for (int i=0; i<*size; i++)
                {
                        snake[*size-i]=snake[*size-i-1];
                        snake[row*col+*size-i]=snake[row*col+*size-i-1];
                }
                snake[0]+=drow;
                snake[row*col]+=dcol;
                (*size)++;
                snake[*size]=lastcoord[0];
                snake[row*col+*size]=lastcoord[1];

                bool ok=0;
                do {
                        ok=0;
                        apple[0]=(rand()%(row-2))+1;
                        apple[1]=(rand()%(col-2))+1;
                        for (int j = 0; j < *size; j++) {
                                if ((apple[0]==snake[j])&&(apple[1]==snake[row*col+j]))
                                        ok=1;
                        }
                } while (ok==1);
                field[ apple[0]*row+apple[1] ]=2;

                break;

        case 3:
                return 1;
                break;
        }
        return 0;
}

int main ()
{
        initscr();
        /*  timeout(1000); Привет дамп памяти */
        int snake[2][row*col]={-1};
        snake[0][0]=4;
        snake[1][0]=4;
        int lastcoord[2];
        int size=0;
        int field [row][col]={0};
        int apple[2]={5,5};

        startfield(&field[0][0],&apple[0]);

        drawsnake(&snake[0][0],&field[0][0]);

        hudoznik(&field[0][0]);
        bool gameover=0;
        int key,dcol,drow;
        while(true) {
                refresh();
                key=getch();
                switch(key) {
                case W:
                        drow=-1;
                        dcol=0;
                        break;
                case A:
                        drow=0;
                        dcol=-1;
                        break;
                case S:
                        drow=1;
                        dcol=0;
                        break;
                case D:
                        drow=0;
                        dcol=1;
                        break;
                case ERR:
                        break;
                }
                gameover=
                        moicase(&snake[0][0],&field[0][0],&size,
                                &lastcoord[0],&apple[0],drow,dcol);
                if (gameover) break;

                clear();

                drawsnake(&snake[0][0],&field[0][0]);

                hudoznik(&field[0][0]);
        }
        endwin();
        return 0;
}

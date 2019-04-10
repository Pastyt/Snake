#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#define row 15
#define col 15
#define W_key 119
#define A_key 97
#define S_key 115
#define D_key 100
#define timer 333333
/*int getmykey (int *oldkey,int size)
{
        int key;
        timeout(speed-(size*25));
        key=getch();
        if (key==ERR) key=*oldkey;
        else *oldkey=key;
        return key;
   } um done */
void hudoznik (int (*field)[col])
{
        for (int i=0; i<row; i++) {
                for (int j=0; j<col; j++)
                        switch(field[i][j]) {
                        case 0:
                                printw("  "); /* Nothing */
                                break;
                        case 1:
                                printw("1 "); /* Snake */
                                break;                 
                        case 3:
                                printw("- "); /* Donald Trump */
                                break;
			default:
				if (field[i][j]==-1) break;
                                printw("%d ",field[i][j]); /* Apple */
                                break;
                        }
                printw("\n");
        }
}
void startfield(int (*field)[col], int* apple)
{
        for (int i=0; i<row; i++)
                for (int j=0; j<col; j++)
                        if ((i==0)||(j==0)||((j+1)==col)||((i+1)==row)) field[i][j]=3;

        field[apple[0]][apple[1]]=2;
}
void drawsnake(int (*snake)[row*col], int (*field)[col]) 
{
        for (int i = 0; i < 100; i++)
                if (snake[0][i]!=-1) field[snake[0][i]][snake[1][i]]=1; field[0][0]=3;
}
bool moicase(int (*snake)[row*col],int (*field)[col], int *size,int* lastcoord, int* apple,int drow,int dcol,int *sizeinc)
{
        switch (field[snake[0][0]+drow][(snake[1][0]+dcol)])
        {
        case 0:
		if (*sizeinc!=0) {
			(*sizeinc)--;
			lastcoord[0]=snake[0][*size];
                	lastcoord[1]=snake[1][*size];
                	for (int i=0; i<*size; i++)
               	 	{
                	        snake[0][*size-i]=snake[0][*size-i-1];
                        	snake[1][*size-i]=snake[1][*size-i-1];
                	}
                	snake[0][0]+=drow;
                	snake[1][0]+=dcol;
                	(*size)++;
                	snake[0][*size]=lastcoord[0];
                	snake[1][*size]=lastcoord[1];
		}
		else {
                	field[ snake[0][*size] ][ snake[1][*size] ]=0;
                	for (int i=0; i<*size; i++)
               	 	{
                        	snake[0][*size-i]=snake[0][*size-i-1];
                        	snake[1][*size-i]=snake[1][*size-i-1];
                	}
                	snake[0][0]+=drow;
                	snake[1][0]+=dcol;
		}
                break;

        case 1:
                return 1;
                break;

        case 3:
                return 1;
                break;
	default:
			if (field[snake[0][0]+drow][(snake[1][0]+dcol)]==-1) break;

			*sizeinc+=field[snake[0][0]+drow][snake[1][0]+dcol]-1;

			lastcoord[0]=snake[0][*size];
                	lastcoord[1]=snake[1][*size];
                	for (int i=0; i<*size; i++)
               	 	{
                	        snake[0][*size-i]=snake[0][*size-i-1];
                        	snake[1][*size-i]=snake[1][*size-i-1];
                	}
                	snake[0][0]+=drow;
                	snake[1][0]+=dcol;
                	(*size)++;
                	snake[0][*size]=lastcoord[0];
                	snake[1][*size]=lastcoord[1];

                bool ok=0;
                do {
                        ok=0;
                        apple[0]=(rand()%(row-2))+1;
                        apple[1]=(rand()%(col-2))+1;
                        for (int j = 0; j < *size; j++) {
                                if ((apple[0]==snake[0][j])&&(apple[1]==snake[1][j]))
                                        ok=1;
                        }
                } while (ok==1);

                field[ apple[0] ][ apple[1] ]=rand()%3+4;

                break;
        }
        return 0;
}

int main ()
{
        initscr();
          timeout(1);
        int snake[2][row*col]={-1};
        snake[0][0]=4;
        snake[1][0]=4;
        int lastcoord[2];
        int size=0;
        int field [row][col]={{0}};
        int apple[2]={5,5};

        startfield(&field[0][0],&apple[0]);

        drawsnake(&snake[0][0],&field[0][0]);

        hudoznik(&field[0][0]);
        bool gameover=0;
        int key,dcol=0,drow=-1,sizeinc=0;
        while(true) {
                refresh();
		usleep(timer);
                key=getch();	
	
                switch(key) {
                case W_key:
                        drow=-1;
                        dcol=0;
                        break;
                case A_key:
                        drow=0;
                        dcol=-1;
                        break;
                case S_key:
                        drow=1;
                        dcol=0;
                        break;
                case D_key:
                        drow=0;
                        dcol=1;
                        break;
                case ERR:
                        break;
                }
                gameover=
                        moicase(&snake[0][0],&field[0][0],&size,
                                &lastcoord[0],&apple[0],drow,dcol,&sizeinc);
                if (gameover) break;

                clear();

                drawsnake(&snake[0][0],&field[0][0]);

                hudoznik(&field[0][0]);
        }
        endwin();
        return 0;
}

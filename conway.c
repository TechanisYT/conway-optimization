#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define P_SCREEN0 ((unsigned char *)0x2000)
#define P_COLOR0  ((unsigned char *)0x0400)

#define P_SCREEN1 ((unsigned char *)0x6000)
#define P_COLOR1  ((unsigned char *)0x4400)

//HighRes Mode 300x200px
#define XMAX 40
#define YMAX 25
#define BOXSIZE 3
#define ROUNDS 1

void findNachbarn(int x, int y, int spielfeld[][YMAX], int nachbarn[][BOXSIZE]);
void initSpielfeld(int spielfeld [][YMAX]);
void printSpielfeld(int spielfeld [][YMAX]);
int zaehlLebende(int nachbarn[][BOXSIZE]);
void pruefeRegeln(int x, int y,  int lebende, int temp[][YMAX], int spielfeld[][YMAX]);

//static const char array[XMAX][YMAX] 
const static int array[XMAX][YMAX]= {
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
};

static int spielfeld[XMAX][YMAX];
static int temp[XMAX][YMAX];
static int nachbarn[BOXSIZE][BOXSIZE];

int main(void)
{
  clock_t       t;
  unsigned long sec;
  unsigned      sec10;
  unsigned long fps;
  unsigned      fps10;
  unsigned char background;
  unsigned char text;
        
	int x;
	int y;
	int lebende;
	unsigned int round = 0;

  t = clock ();
	initSpielfeld(spielfeld);
  clrscr();
	background = bgcolor(COLOR_BLACK);
	text = textcolor(COLOR_WHITE);
	printSpielfeld(spielfeld);
//	signal (int sig, __sigfunc func);


	while(round < ROUNDS && !kbhit()){
		for(y = 0; y< YMAX; y++){
			for(x = 0; x< XMAX; x++){
				gotoxy(0,0);
				//cprintf("%2d %2d",x , y);
				findNachbarn(x,y,spielfeld,nachbarn);
				lebende = zaehlLebende(nachbarn);
				gotoxy(x,y);
				//cprintf("%d",lebende /7 );
				pruefeRegeln(x,y,lebende, temp, spielfeld);
			}// for x
		}// for y

		memcpy(spielfeld,temp,XMAX*YMAX);
	
		round++;
		printSpielfeld(spielfeld);	
	}
		t = clock() - t;
	
  /* Reset screen colors */
    bgcolor (background);
    textcolor (text);
    clrscr ();

    /* Calculate stats */
    sec   = (t * 10) / CLK_TCK;
    sec10 = sec % 10;
    sec  /= 10;
    fps   = (round * (CLK_TCK * 10)) / t;
    fps10 = fps % 10;
    fps  /= 10;

    /* Output stats */
    gotoxy (0, 0); cprintf ("time  : %lu.%us", sec, sec10);
    gotoxy (0, 1); cprintf ("frames: %lu", round);
    gotoxy (0, 2); cprintf ("fps   : %lu.%u", fps, fps10);

    /* Wait for a key, then end */
    cputsxy (0, 4, "Press any key when done...");
    (void) cgetc ();

    /* Done */
    return EXIT_SUCCESS;
}



void pruefeRegeln(int x, int y,  int lebende, int temp[][YMAX], int spielfeld[][YMAX]){
	//hier kommen meine regeln
	if(spielfeld[x][y] == 0 ){
		if(lebende == 3){
			temp[x][y] = 1;
//			printf("t3\n\n");
		}
	}
	if(spielfeld[x][y] == 1){
		if(lebende == 2){
			temp[x][y] = 1;
//			printf("=2\n\n");
		}
	}
	if(spielfeld[x][y] == 1){
		if(lebende == 3){
			temp[x][y] = 1;
//			printf("=3\n\n");
		}
	}
	if(spielfeld[x][y] == 1){
		if(lebende < 2){
			temp[x][y] = 0;
//			printf("<2\n\n");
		}
	}
	if(spielfeld[x][y] == 1){
		if(lebende > 3){					
			temp[x][y] = 0;
//			printf(">3\n\n");
		}
	}
}


int zaehlLebende(int nachbarn[][BOXSIZE]){
  int lebende = 0;
  int iy, ix, flag;
	for(iy= 0; iy < BOXSIZE ; iy++){
		for(ix = 0; ix < BOXSIZE; ix++){
			//prüfe dass wir nicht auf unserer eigneen position sind
			
		  flag = 3 * 7 ;
			
			if(ix != 1){
			flag += 1 * 7;
			}
			if(iy != 1 * 7){
			flag +=2;
			}
			if(flag >3 * 7){
				lebende += nachbarn[ix][iy] * 7;
			}
		}//for ix
	}//for iy	
	return lebende;
}



void findNachbarn(int x, int y, int spielfeld[][YMAX], int nachbarn[][BOXSIZE]){
	//gehe über alle nachbarn
	unsigned int osx, ix;
	unsigned int osy, iy; 
	signed int ofy;
	signed int ofx;
	long int temp;
	
	for(ofy = y-1, iy=0; ofy <= (signed int)y+1; ++ofy , ++iy){
		for(ofx = x-1,ix = 0; ofx <= (signed int)x+1; ++ofx , ++ix){
	
			if( ofy < 0)	{
				osy = YMAX-1;
			}
			else if( ofy > YMAX-1)	{
					osy = 0;
				}
				else {
					osy = ofy;
				}
			
			
			if( ofx < 0)	{
				osx = XMAX-1;
			} else if( ofx > XMAX-1)	{
					osx = 0;
				}
				else {
					osx = ofx;
				}
		  temp = spielfeld[osx][osy];
			nachbarn[ix][iy] = temp;				
		}//for ofx
	}//for ofy	

}




void printSpielfeld(int spielfeld [][YMAX]){
	long int x,y;
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
			if(spielfeld[x][y] == 1){
				revers(1);
			} else{
				revers(0);
			}		
 			cputcxy (x, y, 32);
		}
	}
}



void initSpielfeld(int spielfeld [][YMAX]){
	long int x,y;
	//fülle das feld mit zufallswerten und gibs aus
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
				spielfeld[x][y] = array[x][y];
		}
	}
}

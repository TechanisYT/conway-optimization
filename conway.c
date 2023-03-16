#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define P_SCREEN0 ((unsigned char *)0x2000)
#define P_COLOR0  ((unsigned char *)0x0400)

#define P_SCREEN1 ((unsigned char *)0x6000)
#define P_COLOR1  ((unsigned char *)0x4400)

//HighRes Mode 300x200px
#define XMAX 40
#define YMAX 25
#define ROUNDS 20


#define MAX_LOOKUP_VALUE 100
unsigned char div_10_lookup[MAX_LOOKUP_VALUE];
unsigned char mod_10_lookup[MAX_LOOKUP_VALUE];

//unsigned char rules[] = {
//	0,0,1,1,0,0,0,0,0,0,0,0
//};

//void findNachbarn(signed char x, signed char y, char spielfeld[][YMAX], char nachbarn[][BOXSIZE]);
//void initSpielfeld(char spielfeld [][YMAX]);
//void printSpielfeld(char spielfeld [][YMAX],char round);
//int zaehlLebende(char nachbarn[][BOXSIZE]);
//void pruefeRegeln(signed char x, signed char y, char temp[][YMAX], char spielfeld[][YMAX]);

//static const char array[XMAX][YMAX] 
/*
const static unsigned char spielfeld[XMAX][YMAX]= {
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
*/
const static unsigned char spielfeld[XMAX*YMAX]={
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld1[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld2[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld3[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld4[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld5[XMAX]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};
//unsigned char spielfeld6[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld7[XMAX]={0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0};
//unsigned char spielfeld8[XMAX]={0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0};
//unsigned char spielfeld9[XMAX]={0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0};
//unsigned char spielfeld10[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld11[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld12[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld13[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld14[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld15[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld16[XMAX]={1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0};
//unsigned char spielfeld17[XMAX]={0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0};
//unsigned char spielfeld18[XMAX]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0};
//unsigned char spielfeld19[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0};
//unsigned char spielfeld20[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0};
//unsigned char spielfeld21[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld23[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld24[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld25[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//unsigned char spielfeld26[XMAX]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


unsigned char zero[XMAX*YMAX];

//static char spielfeld[XMAX][YMAX];
unsigned char temp[XMAX*YMAX];
unsigned char beside[XMAX*YMAX];
static const unsigned char pixels = XMAX*YMAX;







//Lookup Tables
unsigned char besideLookup[XMAX*YMAX*8];
unsigned char cellLookup[XMAX*YMAX];
unsigned char graphicLookupx[XMAX*YMAX];
unsigned char graphicLookupy[XMAX*YMAX];

int main(void)
{
  clock_t       t;
  unsigned long sec;
  unsigned      sec10;
  unsigned long fps;
  unsigned      fps10;
  unsigned char background;
  unsigned char text;
        
	unsigned char x, xx;
	unsigned char y, yy;
	unsigned long i;
	unsigned char j;
	/*
	unsigned char temp1;
	unsigned char temp2;
	unsigned char temp3;
	unsigned char temp4;
	unsigned char temp5;
	unsigned char temp6;
	unsigned char temp7;
	unsigned char temp8;
	//int lebende;
	*/
	unsigned char round = 0;
	background = bgcolor(COLOR_BLACK);
	text = textcolor(COLOR_WHITE);
	//Lookup Calc:
	


	do{
		do{
				besideLookup[i]=(x-1)+((y-1)*XMAX);
				besideLookup[i+1]=(x-1)+(y*XMAX);
				besideLookup[i+2]=(x-1)+((y+1)*XMAX);
				besideLookup[i+3]=x+((y-1)*XMAX);
				besideLookup[i+4]=(x+1)+((y-1)*XMAX);
				besideLookup[i+5]=(x+1)+((y+1)*XMAX);
				besideLookup[i+6]=(x+1)+(y*XMAX);
				besideLookup[i+7]=x+((y+1)*XMAX);
				i=i+8;
				++x;
		}while(x<XMAX-1);
		x=0;
		++y;
	}while(y<YMAX-1);
	i=0;
	x=0;
	y=0;
	do{
		x=0;
		do{
			//cellLookup[i]=i;
			graphicLookupy[i]=y;
			graphicLookupx[i]=x;
			
			//gotoxy (x, y); cprintf (i);
			++i;
			++x;
		}while(x<XMAX-1);
		++y;
	}while(y<YMAX-1);
	i=0;
	x=0;
	y=0;




	//do{
	//	do{
	//			if(spielfeld[x+y*XMAX]==1){
	//				++beside[(x-1)+((y-1)*XMAX)];
	//				++beside[(x-1)+(y*XMAX)];
	//				++beside[(x-1)+((y+1)*XMAX)];
	//				++beside[x+((y-1)*XMAX)];
	//				++beside[(x+1)+((y-1)*XMAX)];
	//				++beside[(x+1)+((y+1)*XMAX)];
	//				++beside[(x+1)+(y*XMAX)];
	//				++beside[x+((y+1)*XMAX)];
	//				//++beside[besideLookup[i]];
	//				//++beside[besideLookup[i+1]];
	//				//++beside[besideLookup[i+2]];
	//				//++beside[besideLookup[i+3]];
	//				//++beside[besideLookup[i+4]];
	//				//++beside[besideLookup[i+5]];
	//				//++beside[besideLookup[i+6]];
	//				//++beside[besideLookup[i+7]];
	//				//gotoxy (x, y); cprintf(beside[besideLookup[i]]);
	//			}
	//		i=i+8;
	//		++x;
	//	}while(x<XMAX-1);
	//	x=0;
	//	++y;
	//}while(y<YMAX-1);
	//i=0;

	//do{
	//	xx=0;
	//	do{
	//		gotoxy (xx, yy); cprintf ("%s",);
	//		++i;
	//		++xx;
	//	}while(xx<XMAX-1);
	//	++yy;
	//}while(yy<YMAX-1);
	t = clock ();

	while(round < ROUNDS && !kbhit()){
		clrscr();
		i=0;
		memcpy(temp,zero,XMAX*YMAX);
		memcpy(beside,zero,XMAX*YMAX);
		y=0;
		do{
			x=0;
			do{
				//gotoxy (xx, yy); cprintf (beside[xx+yy*XMAX]);
				if(spielfeld[y*XMAX+x]==1){
					++beside[(y-1)*XMAX+(x-1)];
					++beside[(y-1)*XMAX+x];
					++beside[(y-1)*XMAX+(x+1)];
					++beside[y*XMAX+(x-1)];
					++beside[y*XMAX+(x+1)];
					++beside[(y+1)*XMAX+(x-1)];
					++beside[(y+1)*XMAX+x];
					++beside[(y+1)*XMAX+(x+1)];
					//++beside[besideLookup[i]];
					//++beside[besideLookup[i+1]];
					//++beside[besideLookup[i+2]];
					//++beside[besideLookup[i+3]];
					//++beside[besideLookup[i+4]];
					//++beside[besideLookup[i+5]];
					//++beside[besideLookup[i+6]];
					//++beside[besideLookup[i+7]];
				}
				i++;
				++j;
				++xx;
			}while(xx<XMAX-1);
			++yy;
		}while(yy<YMAX-1);

		x=0;
		i=0;
		y=0;
		do{
			switch (beside[x]){//x+y*XMAX
				case 2:
					if (spielfeld[x] == 1)//cellLookup[i]
						temp[x]=1;
					break;
				case 3:
					temp[x]=1;
					break;
			}
			if(spielfeld[x] == 1){
				
				revers(1);
				//gotoxy (x-y*XMAX,y); cprintf (x);
				cputcxy (x-y*XMAX,y, 32);
			}
			if(x%XMAX==0){
				++y;
			}
			++i;
			++x;
		}while(x<(YMAX-1)*(XMAX-1));// for y
		yy=0;
		xx=0;
		
		j=0;
		memcpy(spielfeld,temp,XMAX*YMAX);
		
		
		++round;
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
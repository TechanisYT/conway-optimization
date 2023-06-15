# Conways Game of Life Optimierung
## Table of contents

- [Overview](#overview)
- [Graph](#graph)
- [Single Changes](#changes)
- [Tools](#tools)
- [Creators](#creators)


## Overview

Was wurde bisher umgesetzt

- Startzeit: 56.2s
- Optimierte Laufzeit: 183ms
- Einzelne Commits: 50
- Größte Zeitoptimierung in einem Commit: 56.25%


Commits |Zeit [s] | Ticks | FPS | Verbesserung Prozent relativ  | Verbesserung Prozent absolut  | Beschreibung
-------- | -------- | --------- | -------- | -------- | --------- | ---------
1 | 55.3 | - | 0.02 | 100% | 0 | original |  
2 | 45.3 | - | 0.02 | 18.08 | 18.08318264 | Ohne Anzeige
3 | 40.6 | - | 0.02 | 10.38 | 26.58227848 | ohne Goto
4 | 38.9 | - | 0.03 | 4.19 | 29.65641953 | char
5 | 36.7 | - | 0.03 | 5.66 | 33.63471971 | signed char for x,y
6 | 32.9 | - | 0.03 | 10.35 | 40.50632911 | Zähl Lebende Effizienter
7 | 27.9 | - | 0.04 | 15.20 | 49.54792043 | Ohne for loop für nachbarn
8 | 26.9 | - | 0.04 | 3.58 | 51.3562387 | zähl lebende in prüfe regeln
9 | 21.2 | - | 0.05 | 21.19 | 61.6636528 | mehr char variablen
10 | 19.9 | - | 0.05 | 6.13 | 64.01446655 | prüfe Regeln effizienter
11 | 19.4 | - | 0.05 | 2.51 | 64.91862568 | prüfe Regeln mit else
12 | 18.7 | - | 0.05 | 3.61 | 66.18444846 | prüfe Regeln noch effizienter
13 | 17.4 | - | 0.06 | 6.95 | 68.53526221 | ohne extra Spielfeld variable
14 | 14.9 | - | 0.07 | 14.37 | 73.05605787 | ohne Functions
15 | 7.4 | - | 0.14 | 50.34 | 86.61844485 | neuer Nachbarn Algorythmus
16 | 5.2 | - | 0.19 | 29.73 | 90.59674503 | Regeln effizienter, do while
17 | 2.5 | - | 0.40 | 51.92 | 95.47920434 | Neuer Algorythmus für Nachbarn
18 | 1.2 | - | 0.83 | 52.00 | 97.83001808 | Kleineres Nachbarn array
19 | 1.6 | - | 0.63 | -33.33 | 97.10669078 | 1D Array funktioniert aber langsam
20 | 0.7 | - | 1.43 | 56.25 | 98.73417722 | Beside Function in anderem Loop
21 | 0.366 | - | 2.73 | 47.71 | 99.33815552 | beside lookup funktioniert
22 | 0.333 | - | 3.00 | 9.02  | 99.39783002 | 8 Einzelne beside Lookups
23 | 0.3 | - | 3.33 | 9.91  | 99.45750452 | memset, unnötiges entfernt
24 | 0.183 | 11 | 5.5 | 39.00 | 99.66907776 | ausgabe mit VIC

### Graph

![Graph](graph.png)
![Graph](graph_FPS.png)

## Changes

### First Change

#### Unnötige Funktionen löschen (40.6s)

```c
  while(round < ROUNDS && !kbhit()){
    for(y = 0; y< YMAX; y++){
      for(x = 0; x< XMAX; x++){
        //gotoxy(0,0);
        //cprintf("%2d %2d",x , y);
        findNachbarn(x,y,spielfeld,nachbarn);
        lebende = zaehlLebende(nachbarn);
        //gotoxy(x,y);
        //cprintf("%d",lebende /7 );
        pruefeRegeln(x,y,lebende, temp, spielfeld);
      }
```

#### char statt int (36.7)

```c
void findNachbarn(int x, int y, char spielfeld[][YMAX], char nachbarn[][BOXSIZE]);
void initSpielfeld(char spielfeld [][YMAX]);
void printSpielfeld(char spielfeld [][YMAX]);
int zaehlLebende(char nachbarn[][BOXSIZE]);
void pruefeRegeln(int x, int y,  int lebende, char temp[][YMAX], char spielfeld[][YMAX]);

static char spielfeld[XMAX][YMAX];
static char temp[XMAX][YMAX];
static char nachbarn[BOXSIZE][BOXSIZE];
```

#### Zähl Lebende verbessert

```c
int zaehlLebende(char nachbarn[][BOXSIZE]){
  //int lebende = 0;
  //int iy, ix, flag;
  char lebende = 0;
  int iy, ix;
  for(iy= 0; iy < BOXSIZE ; iy++){
    for(ix = 0; ix < BOXSIZE; ix++){
      
      //flag = 3 * 7 ;
      //if(ix != 1){
      //flag += 1 * 7;
      //}
      //if(iy != 1 * 7){
      //flag +=2;
      //}
      //if(flag >3 * 7){
      //  lebende += nachbarn[ix][iy] * 7;

      if(ix != 1 || iy != 1){
      lebende += nachbarn[ix][iy];
      }
    }//for ix
  }//for iy 
  return lebende;
}
```

#### Zähl Lebende weiter verbessert (32.9)

```c
int zaehlLebende(char nachbarn[][BOXSIZE]){
  char lebende = 0;
  int iy, ix;
  for(iy= 0; iy < BOXSIZE ; ++iy){
    for(ix = 0; ix < BOXSIZE; ++ix){    
      lebende += nachbarn[ix][iy];
    }
  }
  lebende-=nachbarn[ix][iy];
  return lebende;
}
```

#### for loop bei Zähl lebende ersetzt (27.9s)

```c
int zaehlLebende(char nachbarn[][BOXSIZE]){
  char lebende = 0;

  lebende += nachbarn[0][0];
  lebende += nachbarn[0][1];
  lebende += nachbarn[0][2];
  lebende += nachbarn[1][0];
  lebende += nachbarn[1][2];
  lebende += nachbarn[2][0];
  lebende += nachbarn[2][1];
  lebende += nachbarn[2][2];

  return lebende;
}
```

#### Function zähl lebende in prüfe pruefeRegeln

Dies ist sinnvoll da ein Funktion call viel Zeit braucht. Die Funktion zähl lebende wurde gelöscht.


#### Variable Temp gelöscht (26.5s)

![Code](Code_Image/26,5.png)

#### Weiter int Variablen mit char ersetzt (21.2s)

#### Beim Regeln Prüfen if else (18,7s)

![Code](Code_Image/18,7.png)

#### Statt array Variable immer Spielfeld benutzen (17.4)

##### Dabei muss man drauf achten bei den Funktion calls und Definitionen die Variable auszuwechseln

#### Ohne irgendwelche Functions (14.9s)

```c
    for(y = 0; y< YMAX; y++){
      for(x = 0; x< XMAX; x++){
        //findNachbarn(x,y,spielfeld,nachbarn);
        //pruefeRegeln(x,y,temp, spielfeld);
        char lebende = 0;
        char osx, ix;
        char osy, iy; 
        char ofy;
        char ofx;
        //int temp;
        char nachbarn[3][3];
        for(ofy = y-1, iy=0; ofy <= (char)y+1; ++ofy , ++iy){
          for(ofx = x-1,ix = 0; ofx <= (char)x+1; ++ofx , ++ix){
            if( ofy < 0)  {
              osy = YMAX-1;
            }
            else if( ofy > YMAX-1)  {
                osy = 0;
              }
              else {
                osy = ofy;
              }
            if( ofx < 0)  {
              osx = XMAX-1;
            } else if( ofx > XMAX-1)  {
                osx = 0;
              }
              else {
                osx = ofx;
              }
            //temp = ;
            nachbarn[ix][iy] = spielfeld[osx][osy];       
          }//for ofx
        }//for ofy  
        lebende += nachbarn[0][0];
        lebende += nachbarn[0][1];
        lebende += nachbarn[0][2];
        lebende += nachbarn[1][0];
        lebende += nachbarn[1][2];
        lebende += nachbarn[2][0];
        lebende += nachbarn[2][1];
        lebende += nachbarn[2][2];
        if(spielfeld[x][y] == 0 ){
          if(lebende == 3){
            temp[x][y] = 1;
//            printf("t3\n\n");
          }
        }
        else{
          if(lebende == 2 || lebende == 3){
            temp[x][y] = 1;
//            printf("=2\n\n");
          }
          else{
            temp[x][y] = 0;
//            printf("<2\n\n");
          }
        }





      }// for x
    }// for y
```

#### Hardcoded Lebende (7.4s)
Ein Fehler der zuvor noch im Programm war wurde hiermit behoben. Mit dieser Technik bleiben sehr viele Rechenoperationen erspart.

```c
lebende += spielfeld[x-1][y-1];
lebende += spielfeld[x][y-1];
lebende += spielfeld[x-1][y];
lebende += spielfeld[x+1][y+1];
lebende += spielfeld[x+1][y];
lebende += spielfeld[x][y+1];
lebende += spielfeld[x+1][y-1];
lebende += spielfeld[x-1][y+1];
```

#### Effiziente Spielfeldausgabe (5.2s)
```c
if(spielfeld[x][y] == 1)
{
  revers(1);
  cputcxy (x, y, 32);
}

```
Dieser Code-Ausschnitt wurde in den Haupt While-Do Loop geschrieben, da dieser sowieso durch alle Zellen durchgeht. 
Da nur Lebende Zellen geschrieben werden muss der Screen gecleared werden.
```c
clrscr();
```
Dies wird mit diesem Command erzielt.

#### New Algorythm and Zeros (2.5s)
Der neue Algorythmus ändert die Weise wie die Anzahl der Lebende gezält wird.
```c
do{
  xx=1;
  do{
    if(spielfeld[xx-1][yy-1]==1){
      beside[xx-1][yy-1]+=1;
      beside[xx-1][yy]+=1;
      beside[xx-1][yy+1]+=1;
      beside[xx][yy-1]+=1;
      beside[xx+1][yy-1]+=1;
      beside[xx+1][yy+1]+=1;
      beside[xx+1][yy]+=1;
      beside[xx][yy+1]+=1;
    }
    ++xx;
  }while(xx<XMAX-1);
  ++yy;
}while(yy<YMAX-1);
```

Da es viel Ziet braucht die Arrays einzeln mit Nullen zu überschreiben, brauchten wir eine neue Methode.
Die Lösung ist ein eigenes Array zu erstellen mit den Selben Dimensions wie das zurückzusetzende Array. Nun wird mit memcpy(memcopy) das Zeros Array in das Ziel Array gespeichert.
```c
memcpy(spielfeld,zero,25*40);
```
Wenn man Bei einem Array nicht definiert, was hinein geschriben werden soll, wird es mit 0en vollgeschrieben. Daher Reicht dieser Code.
```c
unsigned char zero[XMAX][YMAX];
```


#### Neues Spielfeld Array (no Improvements)
Wir haben die Matrix mithilfe eines Python Scriptes transponiert, da sie vorher um 90° verdreht war. Das gibt keine Zeitverbesserungen, aber hilft bei der Fehlersuche.
Script:
```c
XMAX=40
YMAX=25
spielfeld=[
[0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1],
[1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1],
[0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
[1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
]
transpose=[[0 for x in range(XMAX)] for y in range(YMAX)]
for x in range(XMAX-1):
  for y in range(YMAX-1):
    print(x,y)
    transpose[y][x]=spielfeld[x][y]
print(transpose)
```
Output:
```c
const static unsigned char spielfeld[XMAX][YMAX]={
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
```


#### Weitere Änderung des Spielfelds

Hier haben wir statt den 2 Dimensionalen Arrays nur eine Dimension verwendet. Dies wurde umgesetzt wie folgt:
```c
unsigned char spielfeld[1000]={
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
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
0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
```
Nun muss natürlich vieles der Logik des Programmes verändert werden. Jede Stelle des Codes wo auf die Zellen zugreifen muss überarbeitet werden. Dafür braucht man nur eine Loop jedoch muss die y Koordinaate erechnet werden.
```c
    do{
        if(spielfeld[x+y*XMAX]==1){
          ++beside[(x-1)+((y-1)*XMAX)];
          ++beside[(x-1)+(y*XMAX)];
          ++beside[(x-1)+((y+1)*XMAX)];
          ++beside[x+((y-1)*XMAX)];
          ++beside[(x+1)+((y-1)*XMAX)];
          ++beside[(x+1)+((y+1)*XMAX)];
          ++beside[(x+1)+(y*XMAX)];
          ++beside[x+((y+1)*XMAX)];
        }
      ++x;
    }while(x<XMAX-1);
    x=0;
```
Das ist nur ein Beispiel wie der Code verändert werden muss. Viele weitere Änderungen sind von Nöten.


Dies ist die Rechnung die die Zellen erechnet: x+y*XMAX
Dies entspricht einfach einer Laufvariable man kann also auf das Spielfeld Array einfach mit 
```c
spielfeld[x]
```
zugreifen.
Das Nachbarn ausrechnen benötigt jedoch sehr viel Zeit da viele Rechenoperationen vonnöten sind die jede runde ausgerechnet werden müssen. So verschlechtert sich die Laufzeit um 0.4s.


#### Lookup Tables 300ms

Die Ergebnisse dieser Rechnungen für die Nachbar Zellen ergeben jede Runde das selbe Ergebnis. Denn was alle dieser Rechnungen ergeben ist der Wert der Nachnbar Zellen für jede individuelle Zelle. Das heißt bei dem 25*40 Spielfeld mit 1000 Zellen gibt das 8000 Ergebnisse denn jede Zelle hat 8 Nachbarn. Nun kann man das ergebnis dieser Rechnungen in ein vordefiniertes Array schreiben auf das nur noch zugegriffen wird.
```c
++beside[besideLookup[i]];
++beside[besideLookup[i+1]];
++beside[besideLookup[i+2]];
++beside[besideLookup[i+3]];
++beside[besideLookup[i+4]];
++beside[besideLookup[i+5]];
++beside[besideLookup[i+6]];
++beside[besideLookup[i+7]];
```
Nun kann dieser eine Lookup Table in 8 aufgeteilt werden um auch noch die letzten Rechnung zu minimieren.
![Code](besideLookup.png)
Nun steht jeder Lookup Table für die selbe Nachbarzelle jeder einzelnen Zelle.
```c
      switch(spielfeld[x]){
        case 1:
          ++beside[besideLookup1[x]];
          ++beside[besideLookup2[x]];
          ++beside[besideLookup3[x]];
          ++beside[besideLookup4[x]];
          ++beside[besideLookup5[x]];
          ++beside[besideLookup6[x]];
          ++beside[besideLookup7[x]];
          ++beside[besideLookup8[x]];
          break;
      }
```
Nun wird wenn eine Zelle lebt der lebende Counter bei allen umliegenden Zellen erhöht.
Diese Lookup Tables wurden mithilfe eines Python Scripts generiert.
```Python
besideLookup=[0 for x in range(8001)]
besideLookup1=[0 for x in range(1000)]
besideLookup2=[0 for x in range(1000)]
besideLookup3=[0 for x in range(1000)]
besideLookup4=[0 for x in range(1000)]
besideLookup5=[0 for x in range(1000)]
besideLookup6=[0 for x in range(1000)]
besideLookup7=[0 for x in range(1000)]
besideLookup8=[0 for x in range(1000)]
overflow = 1000*8+1
j=0
i=0
x=0
y=0
XMAX=40
YMAX=25
for x in range(1000):
  try:
    besideLookup1[x]=graphicLookupy[x-XMAX]*XMAX+graphicLookupx[x-1]
  except:
    pass
  try:  
    besideLookup2[x]=graphicLookupy[x-XMAX]*XMAX+graphicLookupx[x]
  except:
    pass  
  try:
    besideLookup3[x]=graphicLookupy[x-XMAX]*XMAX+graphicLookupx[x+1]
  except:
    pass  
  try:  
    besideLookup4[x]=graphicLookupy[x]*XMAX+graphicLookupx[x-1]
  except:
    pass  
  try:  
    besideLookup5[x]=graphicLookupy[x]*XMAX+graphicLookupx[x+1]
  except:
    pass  
  try:  
    besideLookup6[x]=graphicLookupy[x+XMAX]*XMAX+graphicLookupx[x-1]
  except:
    pass  
  try:  
    besideLookup7[x]=graphicLookupy[x+XMAX]*XMAX+graphicLookupx[x]
  except:
    pass  
  try:  
    besideLookup8[x]=graphicLookupy[x+XMAX]*XMAX+graphicLookupx[x+1]
  except:
    pass


  if graphicLookupx[x]==0:
    besideLookup1[x]=x-1+XMAX-XMAX
    besideLookup4[x]=x-1+XMAX
    besideLookup6[x]=x-1+XMAX+XMAX
  elif graphicLookupx[x]==XMAX-1:
    besideLookup3[x]=x-XMAX+1-XMAX
    besideLookup5[x]=x-XMAX+1
    besideLookup8[x]=x-XMAX+1+XMAX
  if graphicLookupy[x]==0:
    besideLookup1[x]=(YMAX-1)*XMAX+graphicLookupx[x-1]
    besideLookup2[x]=(YMAX-1)*XMAX+graphicLookupx[x]
    besideLookup3[x]=(YMAX-1)*XMAX+graphicLookupx[x+1]
  elif graphicLookupy[x] == YMAX-1:
    besideLookup6[x]=graphicLookupx[x-1]
    besideLookup7[x]=graphicLookupx[x]
    try:
      besideLookup8[x]=graphicLookupx[x+1]
    except:
      pass
```


#### VIC (183ms)

In diesem Schritt wurde die Hardware direkt angesprochen. Die "Grafikkarte" des C64 heißt VIC oder Video Interface Chip und ist für die Steuerung aller grafischer Vorgänge zuständig und hat effizientere Methoden als "cprintf" zur Ausgabe zur Verfügung.

Wir haben dies umgesetzt, indem wir das Arrays des Spielfelds mit einem Pointer auf den Grafikspeicher ersetzt haben.

Der Pointer wird direkt auf die Adresse <mark>$0400</mark> gesetzt. Dies ist die Grundeinstellung des Grafikspeichers. Das bedeutet, dass alles, was an diese Adresse geschrieben wird direkt ausgegeben wird, da der VIC diese Adresse verwendet. Dadurch wird die eigentliche zeitaufwändige Ausgabe überflüssig.

Vorteile:

  - Keine Ausgabe Nötig
  - Zeitersparnis 

Bit 4-7 | Variable A | Startspeicheradresse (hex) | Anmerkung
-------- | -------- | --------- | --------
0000 | 000 | 0 ($0000) | -
<mark>0001</mark> | <mark>016</mark> | <mark>1024 ($0400)</mark> | <mark>Grundeinstellung</mark>
0010 | 032 | 2048 ($0800) | -
0011 | 048 | 3072 ($0C00) | -

Da wir uns im Textmodus befinden übersetzt der VIC die Werte aus dem Grafikspeicher in Buchstaben, Zahlen und Sonderzeichen. Daher werden die 0en und 1en, welche wir hineinschreiben zu @ und A.


![Code](characterset.png)
![Code](characterset_2.png)

Dieses Problem kann gelöst werden, indem "32" und "160" statt 0 und 1 geschrieben werden, oder indem ein custom Characterset eingeführt wird, welches ein Voll ausgefülltes und ein Leeres Feld anstatt @ und A für 0 und 1 hat.

Die erste Option kam für uns nicht in Frage, da man dafür beides in den Speicher schreiben müsste. Unser Programm schreibt aber keine 0en, da alles ausser den 1en sowieso 0en sind. Somit wäre unser Programm dadurch langsämer geworden.

Aus Zeitmangel haben wir auch die 2. Option dann nicht mehr umgesetzt. Um die Funktion des Programms zu Prüfen reichen aber auch die Zeichen.

Es wäre auch möglich weitere Zeit zu sparen, indem die Grafikspeicheradresse des VIC jede Runde zwischen 2 Arrays mittels Pointern hin und herwechselt. Somit wäre kein memcpy zwischen den 2 arrays mehr nötig.

Dies wäre mittels dem Speicherkontrollregister möglich gewesen:

Adresse (hex) | Adresse (dez) | Register | Inhalt
-------- | -------- | --------- | --------
... | ... | ... | ...
$D018 | 53272 | 24 | VIC-Speicherkontrollregister <br> <mark>Bit 7..4: Basisadresse des Bildschirmspeichers in aktueller 16-KByte-VIC-Bank = 1024*(Bit 7…4)</mark> <br> Im Textmodus: <br> Bit 3..1: Basisadresse des Zeichensatzes = 2048*(Bit 3…1). <br> Bit 0: Nicht genutzt. <br> Z.B. bei Bit 3…0 = 0010 erwartet der VIC den Zeichensatz bei Adresse 2048 innerhalb der gewählten VIC-Bank. Im Bitmap-Modus: <br> Bit 3: Basisadresse der Bitmap = 8192*(Bit 3) <br> Bit 2..0: Nicht genutzt.[5] <br> Z.B. bei Bit 3…0 = 1000 erwartet der VIC die Bitmap-Daten ab Adresse 8192 innerhalb der gewählten VIC-Bank. <br> Beachte: Das Character-ROM ist für den VIC an Adressen $1000-$1FFF bzw. $9000-$9FFF sichtbar (also an Offset $1000 in VIC-Bank 0 bzw. 2). <br> Ansonsten sieht der VIC immer das RAM des C64.
... | ... | ... | ...

#### Todo

  - VIC Grafikspeicheradresse jede Runde hin und her wechseln
    + Kein Memcpy nötig
  - dynamische Zellen-deaktivierung
    + Zellen die sowieso nicht verändert werden, werden nicht mehr überprüft


#### Weiter ins Detail gehen werden wir nicht da dies zu lange dauern würde und euch den Lerneffekt nehmen würde

## Tools


1. Version Control

    + Github
    + Git
    + Sublime Merge
  
2. Editor 

    + Sublime Text
  
3. Presentation

    + Markdown

## Creators

- Manuel Mayrhofer
- Johannes Melcher-Millner
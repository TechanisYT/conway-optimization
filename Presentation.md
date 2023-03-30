
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
- Optimierte Laufzeit: 1.2s
- Einzelne Commits: 34
- Größte Zeitoptimierung in einem Commit: > 50%
- Compiler Optionen 

### Graph

![Graph](/home/manuel/Documents/school/3CHEL/Labor/Effizient/Presentation/graph.png)

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

![Code](/home/manuel/Documents/school/3CHEL/Labor/Effizient/Presentation/Code_Image/26,5.png)

#### Weiter int Variablen mit char ersetzt (21.2s)

#### Beim Regeln Prüfen if else (18,7s)

![Code](/home/manuel/Documents/school/3CHEL/Labor/Effizient/Presentation/Code_Image/18,7.png)

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

#### Weiter ins Detail gehen werden wir nicht da dies zu lange dauern würde und euch den Lerneffekt nehmen würde

## Tools


1. Version Control

  - Github
  - Git
  - Sublime Merge
2. Editor 

  - Sublime Text
3. Markdown

## Creators

- Manuel Mayrhofer
- Johannes Melcher-Millner


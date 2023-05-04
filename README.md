# conway-optimization
optimizing a given program for the commodore c64

Changes | Time [s]	| FPS
-------- | -------- | ---------
Stock   | 56.2	| 0.0
print commented out | 42.0 | 0.0
temp not needed | 40.9 | 0.0
redundant ifs pruefeRegeln | 38.1 | 0.0
New PruefeRegeln Call | 38.7 | 0.0
redundant flag in zaehlLebende | 36 | 0.0
new zaehllebende, without FindNachbarn | 19.8 | 0.0
all functions new | 4.9 | 0.1
bug-fixing | 3.6 | 0.2
null array, compiler options, unsigned char | 1.7 | 0.5
zeros | 1.4 | 0.6

Commits	|Zeit [s]	| FPS	| Verbesserung Prozent relativ	| Verbesserung Prozent absolut	| Beschreibung
-------- | -------- | --------- | -------- | -------- | ---------
1 | 55.3 | 0.02 | 100%	0 | original |  
2 | 45.3 | 0.02 | 18.08 | 18.08318264 | Ohne Anzeige
3 | 40.6 | 0.02 | 10.38 | 26.58227848 | ohne Goto
4 | 38.9 | 0.03 | 4.19 | 29.65641953 | char
5 | 36.7 | 0.03 | 5.66 | 33.63471971 | signed char for x,y
6 | 32.9 | 0.03 | 10.35 | 40.50632911 | Zähl Lebende Effizienter
7 | 27.9 | 0.04 | 15.20 | 49.54792043 | Ohne for loop für nachbarn
8 | 26.9 | 0.04 | 3.58 | 51.3562387 | zähl lebende in prüfe regeln
9 | 21.2 | 0.05 | 21.19 | 61.6636528 | mehr char variablen
10 | 19.9 | 0.05 | 6.13	| 64.01446655 | prüfe Regeln effizienter
11 | 19.4 | 0.05 | 2.51	| 64.91862568 | prüfe Regeln mit else
12 | 18.7 | 0.05 | 3.61	| 66.18444846 | prüfe Regeln noch effizienter
13 | 17.4 | 0.06 | 6.95	| 68.53526221 | ohne extra Spielfeld variable
14 | 14.9 | 0.07 | 14.37 | 73.05605787 | ohne Functions
15 | 7.4 | 0.14 | 50.34 | 86.61844485 | neuer Nachbarn Algorythmus
16 | 5.2 | 0.19 | 29.73 | 90.59674503 | Regeln effizienter, do while
17 | 2.5 | 0.40 | 51.92 | 95.47920434 | Neuer Algorythmus für Nachbarn
18 | 1.2 | 0.83 | 52.00 | 97.83001808 | Kleineres Nachbarn array
19 | 1.6 | 0.63 | -33.33 | 97.10669078 | 1D Array funktioniert aber langsam
20 | 0.7 | 1.43 | 56.25 | 98.73417722 | Beside Function in anderem Loop
21 | 0.366 | 2.73 | 47.71 | 99.33815552 | beside lookup funktioniert
22 | 0.333 | 3.00 | 9.02	| 99.39783002 | 8 Einzelne beside Lookups
23 | 0.3 | 3.33 | 9.91	| 99.45750452 | memset, unnötiges entfernt


https://cc65.github.io/doc/funcref.html

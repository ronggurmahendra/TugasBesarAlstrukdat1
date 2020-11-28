#ifndef globalvariable_H
#define globalvariable_H

#include "boolean.h"
#include "graph.h"
#include "jam.h"
#include "listarray.h"
#include "listlinier.h"
#include "mainphase.h"
#include "map.h"
//#include "matriks.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include "pengunjung.h"
#include "point.h"
#include "prepphase.h"
#include "prioqueuePengunjung.h"
#include "stack.h"
#include "tree.h"
#include "wahana.h"

boolean play;
int nbWahana = 3;
Wahana ActiveWahana[100];
Tree DataWahana;
PrioQueuePengunjung PQ[100];
PrioQueuePengunjung Antrian;
JAM Sekarang;
int option;


#endif

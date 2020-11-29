#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "graph.h"
#include "map.h"
#include "point.h"

adrNode AlokNode(int X,MAP M)
/* I.S. X adalah bilangan bulat valid */
/* F.S. Alokasi node dalam graph dengan ID X dan Npred, Trail dan Next diinisialisasikan 0,Nil,dan Nil  */
{
    adrNode P = (adrNode) malloc((sizeof(NodeGraph)+1));
    if(P != Nil){
        IdGraph(P) = X;
        Map(P) = M;
        Trail(P) = Nil;
        NextGraph(P) = Nil;
    }
}
void DealokNode(adrNode P)
/* I.S. adrNode P valid */
/* F.S. Melakukan dealokasi dari P  */
{
    free(P);
}
adrSucc AlokSucc(adrNode Pn)
/* I.S. adrNode Pn valid */
/* F.S. Membuat address P , Mengalokasikan Succ(P) = Pn dan next = Nil */
{
    adrSucc P = (adrSucc) malloc(sizeof(SuccGraph));
    if(P!= Nil){
        Succ(P) = Pn;
        NextSucc(P) = Nil;
    }
    return P;
}
void DealokSuccNode(adrSucc Pt)
/* I.S. adrSucc Pt valid */
/* F.S. Melakukan dealokasi pada SuccNode Pt */
{
    free(Pt);
}

void ConnectNode(adrNode *P1,adrNode *P2){
  if (Trail(*P1)!=Nil) NextSucc(Trail(*P1))=AlokSucc(*P2);
  else Trail(*P1)=AlokSucc(*P2);

  if (Trail(*P2)!=Nil) NextSucc(Trail(*P2))=AlokSucc(*P1);
  else Trail(*P2)=AlokSucc(*P1);
}

void CreateGraphMap(Graph* G)
/* I.S. Graph terdefinisi dan kosong */
/* F.S. Graph dibuat dengan 4 node yang masing" mempunyai 1 map */
{
    MAP M1,M2,M3,M4,*Mtemp;
    readMap(&M1,&M2,&M3,&M4);
    
    adrNode P = AlokNode(1,M1);
    First(*G) = P;
    for(int i=2; i<=4;i++){
        if(i==2) Mtemp = &M2;
        else if(i==3) Mtemp = &M3;
        else if(i==4) Mtemp = &M4;
        
        AddNodeGraph(G,i,*Mtemp);
    }
    ConnectMap(G);
}

void AddNodeGraph(Graph *G,int n,MAP M)
/* I.S. Graph terdefinisi, mungkin kosong , n bilangan bulat valid */
/* F.S. Menambahkan Node di ujung graph dengan ID n */
{
    adrNode P = AlokNode(n,M);

    adrNode A = First(*G);
    while(NextGraph(A) != Nil){
        A = NextGraph(A);
    }
    NextGraph(A) = P;
}

void ConnectMap(Graph *G){
  adrNode P,P1,P2;
  for(int i=1;i<=4;i+=3){
    P = SearchNode(*G,i);
    
    if(i==1) {P1=SearchNode(*G,i+1);P2=SearchNode(*G,i+2);}
    else {P1=SearchNode(*G,i-1);P2=SearchNode(*G,i-2);}
    ConnectNode(&P,&P1);
    ConnectNode(&P,&P2);
  }
}

/* OPERASI SEARCH */
adrNode SearchNode(Graph G, int X){
/* I.S. G berisi minimal 1 elemen, X adalah ID dari salah satu elemen graph */
/* F.S. Mengembalikan adrNode dari elemen dengan ID X */
    boolean found = false;
    adrNode A = First(G);
    while(A != Nil && IdGraph(A) != X){
        A = NextGraph(A);
    }
    if(A != Nil){
        return A;
    }
    else{
        return Nil;
    }
}

void PrintCurrMap(Graph GR){
//memprint semua item di graph
    adrNode P = SearchPlayer(GR);
    printMap(Map(P));
}

/* Check Movement */
void move(char input,Graph *GM){
	POINT temp;

    adrNode P = SearchPlayer(*GM);
    MAP M = Map(P);

	int x=PosXPlayer(M),y=PosYPlayer(M);
	if (input=='w') y--;
	else if (input=='a') x--;
	else if (input=='s') y++;
	else if (input=='d') x++;

	temp = MakePOINT(x,y);
	
	if (checkPoint(M,temp)){
		setPoint(&M,'-',PosPlayer(M));
		PosXPlayer(M) = Absis(temp);
		PosYPlayer(M) = Ordinat(temp);
		setPoint(&M,'P',PosPlayer(M));
        Map(P) = M;
	}else if(checkSwitchVertical(M,temp)) SwitchMap(GM,true);
    else if(checkSwitchHorizontal(M,temp)) SwitchMap(GM,false);
    else printf("That place is occupied\n");
}

void SwitchMap(Graph *GM,boolean vertical){
    adrNode P = SearchPlayer(*GM),newP;
    MAP M = Map(P),newMap;
    POINT gate;
    adrSucc S = Trail(P);
    if (vertical){
        if(IdGraph(P)==1||IdGraph(P)==2){    
            newP = Succ(NextSucc(S));
            newMap = Map(newP);
            setPoint(&M,'-',PosPlayer(M));
            
            if(Ordinat(VGate(newMap))==0) gate=MakePOINT(Absis(VGate(newMap)),Ordinat(VGate(newMap))+1);
            else gate=MakePOINT(Absis(VGate(newMap)),Ordinat(VGate(newMap))-1);
        }else{
            newP = Succ(S);
            newMap = Map(newP);
            setPoint(&M,'-',PosPlayer(M));

            if(Ordinat(VGate(newMap))==0) gate=MakePOINT(Absis(VGate(newMap)),Ordinat(VGate(newMap))+1);
            else gate=MakePOINT(Absis(VGate(newMap)),Ordinat(VGate(newMap))-1);
        }
    }else{
        if(IdGraph(P)==3||IdGraph(P)==4){    
            newP = Succ(NextSucc(S));
            newMap = Map(newP);
            setPoint(&M,'-',PosPlayer(M));
            
            if(Absis(HGate(newMap))==0) gate=MakePOINT(Absis(HGate(newMap))+1,Ordinat(HGate(newMap)));
            else gate=MakePOINT(Absis(HGate(newMap))-1,Ordinat(HGate(newMap)));
        }else{
            newP = Succ(S);
            newMap = Map(newP);
            setPoint(&M,'-',PosPlayer(M));

            if(Absis(HGate(newMap))==0) gate=MakePOINT(Absis(HGate(newMap))+1,Ordinat(HGate(newMap)));
            else gate=MakePOINT(Absis(HGate(newMap))-1,Ordinat(HGate(newMap)));
        }
    }

    if(checkPoint(newMap,gate)){
        setPoint(&M,'-',PosPlayer(M));
        PosXPlayer(M) = pointUndef;
        PosYPlayer(M) = pointUndef;
        setPoint(&newMap,'P',gate);
        PosXPlayer(newMap) = Absis(gate);
        PosYPlayer(newMap) = Ordinat(gate);
        Map(P) = M;
        Map(newP) = newMap;
    }else printf("That place is occupied\n");
}

adrNode SearchPlayer(Graph GM){
  adrNode P = First(GM);
  while(P != Nil && !isPlayerHere(Map(P))){
      P = NextGraph(P);
  }
  return P;
}

int main() {
	Graph g;
	CreateGraphMap(&g);
    move('a',&g);
    PrintCurrMap(g);
    move('d',&g);
    PrintCurrMap(g);
}


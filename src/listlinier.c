#include "listlinier.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L){
/* Mengirim true jika list kosong */
    return First(L)==Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L){
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
    First(*L)=Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X){
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
    address P;
    P = (address)malloc(sizeof(ElmtList));
    if(P!=NULL){//Periksa keberhasilan alokasi
        for(int i=0; i<CKata.Length; i++){
            Info(P)[i] = X[i];
        }
        Next(P)=Nil;
        return P;
    }else {
        return Nil;
    }
}
void Dealokasi (address *P){
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
    free(*P);
}
/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
    address Ptemp=First(*L);
    //Periksa jika list kosong
    if(IsEmpty(*L)) First(*L)=P;
    else{
        //Mencari elemen list terakhir
        while(Next(Ptemp)!=Nil){
            Ptemp=Next(Ptemp);
        }
        Next(Ptemp)=P;
    }
}
void InsVLast (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    address P = Alokasi(X);
    if(P!=Nil){//Periksa keberhasilan alokasi
        InsertLast(L,P);
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    printf("[");
    if(!IsEmpty(L)){//Periksa jika list kosong
        address P=First(L);
        //Print setiap elemen hingga elemen terakhir list
        while(Next(P)!=Nil){
            printf("%d,",Info(P));
            P=Next(P);
        }
        printf("%d",Info(P));
    }
    printf("]");
}
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "ARN.h"

using namespace std;

int const n=10;


typedef struct {
  int  abscisse;
  int  ordonnee;
} point;


//Le tableau des segments: segments[2*i] et segments[2*i+1] sont les 
// extremites du segments i

point segments[2*n];

//********************************************//

bool ClesEgales(int cle1, int cle2){
  if(cle1==cle2){
    return true;
  }
  else{
    return false;}
}

//********************************************//
//Renvoie vrai ssi le premier point du segment cle2
//est a gauche du segment cle1 (segment cle1 < segment cle2)

bool CleInferieure(int cle1, int cle2){

  //conversion en long long pour eviter un depacement d'int.

  //Segment p1p2
  long long x1=(long long) segments[2*cle1].abscisse;
  long long y1=(long long) segments[2*cle1].ordonnee;
  long long x2=(long long) segments[2*cle1+1].abscisse;
  long long y2=(long long) segments[2*cle1+1].ordonnee;

  //Point p3 du segment p3p4
  long long x3=(long long) segments[2*cle2].abscisse;
  long long y3=(long long) segments[2*cle2].ordonnee;


  //
  // A COMPLETER
  //


}


//********************************************//

void AffichageSegments(int n, point segments[]){
  //Affichage de n segments dont les coordonnees sont donnees dans segments[n]
  //Un fichier Segments.ps est cree, visualisable avec un afficheur postscript (ex: ggv, kghostview...)
  ofstream output;
  output.open("Segments.ps");//
  output << "%!PS-Adobe-3.0" << endl;
  output << endl;
  for(int i=0;i<n;i++){
    output << segments[2*i].abscisse << " " << segments[2*i].ordonnee << " 2 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;

    output << segments[2*i+1].abscisse << " " << segments[2*i+1].ordonnee << " 2 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;

    output << segments[2*i].abscisse << " " << segments[2*i].ordonnee << " moveto"  << endl;
    output << segments[2*i+1].abscisse << " " << segments[2*i+1].ordonnee << " lineto"  << endl;
    output << "stroke" << endl;

    output << segments[2*i].abscisse-20 << " " << segments[2*i].ordonnee << " moveto" <<endl;
    output << "/Courier findfont 15 scalefont setfont" << endl;
    output << "("<< i << ")" << " show" << endl;
    output << "stroke" << endl;
    output << endl;
  }
  output << endl;

  output.close();
}


//********************************************//

//Generation au hasard de l'ensemble des segments consideres
//Le premier sommet est celui d'abscisse minimale, on refusera des segments verticaux:
//Choisir segments[2*i].abscisse (=x) dans [20,400] et segments[2*i].ordonnee (=y) dans [100,700]
//Choisir segments[2*i+1].abscisse dans [x+1,x+100] et segments[2*i+1].ordonnee dans [y-50,y+50]

void SegmentsAuHasard(int n,point segments[]){
  srand(time(NULL));
  
 
  //
  // A COMPLETER
  //

}


//********************************************//

//Renvoie Vrai si les deux segments p1p2 et p3p4 s'intersectent
//Dans un premier temps, on pourra supposer que deux segments ne sont jamais
//portes par une meme droite


bool Intersectent(point p1, point p2, point p3, point p4){

  //conversion en long long pour eviter un depacement d'int.

  long long x1= (long long) p1.abscisse;
  long long x2= (long long) p2.abscisse;
  long long x3= (long long) p3.abscisse;
  long long x4= (long long) p4.abscisse;

  long long y1= (long long) p1.ordonnee;
  long long y2= (long long) p2.ordonnee;
  long long y3= (long long) p3.ordonnee;
  long long y4= (long long) p4.ordonnee;


  //
  //A COMPLETER
  //


}

//********************************************//

void TriLexicographique(point segments[], int t, int Tri[]){
  //En entree, Tri, tableau de taille 2*n, contient les indices dans 'segments' des sommets a trier, 
  //a l'initialisation Tri[i]=i, et t est la taille de Tri, donc t=2*n pour le premier appel.
  //En sorti, Tri contient les indices des sommets tries par ordre lexicographique croissant. 
  if(t>1){
    int pivot=Tri[0]; //indice du sommet pivot
    int d=0; // nombre de sommets a droite de min_pivot
    for(int i=1;i<t;i++){//On compte (on ne tient pas compte de pivot)
      if((segments[Tri[0]].abscisse<segments[Tri[i]].abscisse)||
	 ((segments[Tri[0]].abscisse==segments[Tri[i]].abscisse)&&
	  (segments[Tri[0]].ordonnee<segments[Tri[i]].ordonnee))){d++;}
    }
    int Tg[t-d-1];
    int Td[d];
    int indice_gauche=0; //indice d'insertion dans Tg
    int indice_droit=0; //indice d'insertion dans Td
    for(int i=1;i<t;i++){ //Remplissage de Tg et Td (on ne tient pas compte de pivot)
      if((segments[Tri[0]].abscisse<segments[Tri[i]].abscisse)||
	 ((segments[Tri[0]].abscisse==segments[Tri[i]].abscisse)&&
	  (segments[Tri[0]].ordonnee<segments[Tri[i]].ordonnee))){//A droite
	Td[indice_droit]=Tri[i];
	indice_droit++;}
      else{//A gauche
	Tg[indice_gauche]=Tri[i];
	indice_gauche++;}}

    //On trie Td et Tg
    if(d>0){TriLexicographique(segments,d,Td);}
    if(t-d-1>0){TriLexicographique(segments,t-d-1,Tg);}
    //Fusion dans Tri
    for(int i=0;i<t;i++){
      if(i<t-d-1){Tri[i]=Tg[i];}
      if(i==t-d-1){Tri[i]=pivot;}
      if(i>t-d-1){Tri[i]=Td[i-t+d];}
    }
  }
}

//********************************************//

//Algo d'intersection
//Renvoie vrai si il existe 2 segments qui s'intersectent, faux sinon
//Fonctionne en nlog n

bool Intersection(int n, point segments[]){

  //Tri contient les abscisses des extremites des segments, c'est l'echeancier
  int Tri[2*n];
  for(int i=0;i<2*n;i++){
    Tri[i]=i;
  }

  TriLexicographique(segments,2*n,Tri);


  ARN ordre(&ClesEgales,&CleInferieure);

    for(int i=0; i<2*n; i++){

      //
      //A COMPLETER
      //


    }
}

//********************************************//

int main(){


  SegmentsAuHasard(n,segments);
  AffichageSegments(n,segments);

  if(Intersection(n,segments)){
    cout << "Il y a une intersection." << endl;
  }else{
    cout <<"Il n'y a pas d'intersection." << endl;
  }
}


//********************************************//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "ARN.h"

#define X_MAX 612
#define Y_MAX 792
 
#define getmax(a,b) ((a)>(b))?(a):(b)
#define getmin(a,b) ((a)<(b))?(a):(b)

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
//	Calcule de determinant de 2 vecteurs : det(P1P2, P3P4)
//
long long det(point* p1, point* p2, point* p3, point* p4){
	long long p1p2_x = (long long)p2->abscisse - (long long)p1->abscisse;
	long long p1p2_y = (long long)p2->ordonnee - (long long)p1->ordonnee;
	
	long long p3p4_x = (long long)p4->abscisse - (long long)p3->abscisse;
	long long p3p4_y = (long long)p4->ordonnee - (long long)p3->ordonnee;
	
	return (p1p2_x * p3p4_y - p1p2_y * p3p4_x);
}

//********************************************//
//Renvoie vrai ssi le premier point du segment cle2
//est a gauche du segment cle1 (segment cle1 < segment cle2)

bool CleInferieure(int cle1, int cle2){

  //conversion en long long pour eviter un depacement d'int.

  //Segment p1p2
  /*long long x1=(long long) segments[2*cle1].abscisse;
  long long y1=(long long) segments[2*cle1].ordonnee;
  long long x2=(long long) segments[2*cle1+1].abscisse;
  long long y2=(long long) segments[2*cle1+1].ordonnee;

  //Point p3 du segment p3p4
  long long x3=(long long) segments[2*cle2].abscisse;
  long long y3=(long long) segments[2*cle2].ordonnee;*/


  //
  // A COMPLETER
  //
	
	//Test 1
	if(det(&segments[2*cle1], &segments[2*cle1+1], &segments[2*cle1], &segments[2*cle2]) > 0){
		return true;
	}
	return false;
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
//rand entre 2 borne a et b
int randBetween(int a, int b){
	int borneInf = getmin(a,b);
	int borneSup = getmax(a,b);
	return ((rand()%(borneSup - borneInf)) + borneInf);
}

//********************************************//

//Generation au hasard de l'ensemble des segments consideres
//Le premier sommet est celui d'abscisse minimale, on refusera des segments verticaux:
//Choisir segments[2*i].abscisse (=x) dans [20,400] et segments[2*i].ordonnee (=y) dans [100,700]
//Choisir segments[2*i+1].abscisse dans [x+1,x+100] et segments[2*i+1].ordonnee dans [y-50,y+50]

void SegmentsAuHasard(int n,point segments[]){
  srand(time(NULL));
  int i;
  
  segments[0].abscisse = 20;
  segments[0].ordonnee = randBetween(700, 100);
  segments[1].abscisse = randBetween(segments[0].abscisse + 100, segments[0].abscisse + 1);
  segments[1].ordonnee = randBetween(segments[0].ordonnee + 50, segments[0].ordonnee - 50);
  
  
  for(i = 1; i < n; i++){
  	segments[2*i].abscisse = randBetween(400, 20);
  	segments[2*i].ordonnee = randBetween(700, 100);
  	
  	segments[2*i + 1].abscisse = randBetween(segments[2*i].abscisse + 100, segments[2*i].abscisse + 1);
  	segments[2*i + 1].ordonnee = randBetween(segments[2*i].ordonnee + 50, segments[2*i].ordonnee - 50);
  }
}

//********************************************//
//Cette fonction renvoie vrai si les 2 points p3 p4 sont du meme coté qu'un segment defini par 2 points p1 p2
//
bool sameSide(point* p1, point* p2, point* p3, point* p4){
	return (det(p1, p2, p1, p3) * det(p1, p2, p1, p4) > 0);
}


//********************************************//

//Renvoie Vrai si les deux segments p1p2 et p3p4 s'intersectent
//Dans un premier temps, on pourra supposer que deux segments ne sont jamais
//portes par une meme droite


bool Intersectent(point p1, point p2, point p3, point p4){

  //conversion en long long pour eviter un depacement d'int.

  /*long long x1= (long long) p1.abscisse;
  long long x2= (long long) p2.abscisse;
  long long x3= (long long) p3.abscisse;
  long long x4= (long long) p4.abscisse;

  long long y1= (long long) p1.ordonnee;
  long long y2= (long long) p2.ordonnee;
  long long y3= (long long) p3.ordonnee;
  long long y4= (long long) p4.ordonnee;*/


  //
  //A COMPLETER
  //
	return (!sameSide(&p1, &p2, &p3, &p4) && !sameSide(&p3, &p4, &p1, &p2));
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
      //Si p est l'extrémitée gauche d'un segment
      if(Tri[i]%2 == 0){
        ordre.Insere(Tri[i]/2);
        if(ordre.Successeur(Tri[i]/2) != -1){
          if(Intersectent(segments[2 * ordre.Successeur(Tri[i])], segments[2 * ordre.Successeur(Tri[i]/2) + 1],segments[Tri[i]], segments[Tri[i]+1])){
          //cout << "Values Tri[i] = "<< Tri[i] << " ordre.successeur = "<< ordre.Successeur(Tri[i]) << endl;
          //cout << "Premier if "<<endl;
          return true;
          }
        }
        if(ordre.Predecesseur(Tri[i/2]) != -1){
          if(Intersectent(segments[2 * ordre.Predecesseur(Tri[i/2])], segments[2 * ordre.Predecesseur(Tri[i]/2) + 1],segments[Tri[i]], segments[Tri[i]+1])){
            //cout << "Deuxieme if "<<endl;
            return true;
          }
        }
      }

      //Si p extrémité droite.
      if(Tri[i]%2 == 1){
        if(!(ordre.Successeur(Tri[i]) == -1 || ordre.Predecesseur(Tri[i]) == -1)){
          if(Intersectent(segments[2*ordre.Successeur(Tri[i]/2)], segments[2*ordre.Successeur(Tri[i]/2) + 1],segments[2*ordre.Predecesseur(Tri[i]/2)], segments[2*ordre.Predecesseur(Tri[i]/2) + 1])){
            return true;
            //cout << "Troisième if "<<endl;
          }
        }
        ordre.Supprime(Tri[i]);
      }
    }
    return false;
}

//********************************************//
bool algoNaif(int n, point segments[]){
  for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(Intersectent(segments[2*i], segments[2*i+1], segments[2*j], segments[2*j+1])){
        return true;
      }
    }
  }
  return false;
}

int main(){



  for(int i = 0; i < 10000; i++){
    SegmentsAuHasard(n,segments);
    AffichageSegments(n,segments);
    if(algoNaif(n, segments) != Intersection(n,segments)){
      cout << "Fail !"<< endl;
      exit(EXIT_SUCCESS);
    }
  }
  cout << "Ok !" << endl;
  exit(EXIT_SUCCESS);

  /*if(Intersection(n,segments)){
    cout << "Il y a une intersection." << endl;
  }else{
    cout <<"Il n'y a pas d'intersection." << endl;
  }*/
}


//********************************************//

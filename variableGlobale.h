/* 
 * File:   variableGlobale.h
 * Author: katia
 *
 * Created on 8 mars 2014, 13:50
 */

#ifndef VARIABLEGLOBALE_H
#define	VARIABLEGLOBALE_H

#include <vector>
#include "tgaimage.h"

using namespace std;

typedef struct Point Point;
typedef struct Vecteur Vecteur;

struct Point {
    float x, y, z;
};

struct Vecteur {
    float x, y, z;
};

extern float* zBuffer;
extern int xMax, yMax, zMax, xIntermediaire, yIntermediaire, zIntermediaire, xMin, yMin, zMin;
extern Point pMax, pIntermediaire, pMin;
extern TGAColor cMax, cIntermediaire, cMin;
extern Vecteur vecteurMax, vecteurMin, vecteurIntermediaire, vecteurTexture_Max, vecteurTexture_Min, vecteurTexture_Intermediaire;
extern vector<Point> listePoints;


#endif	/* VARIABLEGLOBALE_H */


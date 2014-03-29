/* 
 * File:   outils.h
 * Author: katia
 *
 * Created on 25 février 2014, 22:10
 */

#ifndef OUTILS_H
#define	OUTILS_H

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string.h>
#include <sstream>
#include "tgaimage.h"
#include "variableGlobale.h"
#include "Matrix.h"


#define _COL 800
#define _LIGNE 800
#define _TGA_WIDTH 1024
#define _TGA_HEIGHT 1024

using namespace std;

Vecteur produitVectoriel(Point p1, Point p2, Point p3);

float longueurVecteur(Vecteur vecteur);

float produitScalaire(Vecteur vecteur1, Vecteur vecteur2);

Vecteur normaliser(Vecteur vecteur);

void zBufferInit();

void zBufferImage(string texte);

void zBufferOmbre(string texte);

float getAngleX(Vecteur v0, Vecteur v1);

float getAngleY(Vecteur v0, Vecteur v1);

float getCosAngleX(Vecteur v0, Vecteur v1);

float getSinAngleX(Vecteur v0, Vecteur v1);

float getCosAngleY(Vecteur v0, Vecteur v1);

float getSinAngleY(Vecteur v0, Vecteur v1);

float equation(Point p0, Point p1, int y);

Point equationPoint(Point p0, Point p1, int y);

Vecteur equationVecteur(Point p0, Point p1, int y, Vecteur v0, Vecteur v1);

Vecteur equationVecteurTexture(Point p0, Point p1, int y, Vecteur vt0, Vecteur vt1);

TGAColor getColor(Point p0, Point p1, int y, TGAColor c0, TGAColor c1);

void ordonnerPoints(Point p0, Point p1, Point p2);

void ordonnerPointsCouleurs(Point p0, Point p1, Point p2, TGAColor c0, TGAColor c1, TGAColor c2);

void ordonnerPointsCouleursPhong(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2);

void ordonnerPointsCouleursPhongTexture(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2);

#endif	/* OUTILS_H */


/* 
 * File:   Matrix.h
 * Author: katia
 *
 * Created on 11 mars 2014, 22:53
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <stdlib.h>
#include <iostream>
#include "outils.h"

using namespace std;

class Matrix {
private:
    int nombreLigne;
    int nombreColonne;
    float *matrix;

public:
    Matrix(int nombreLigne, int nombreColonne);
    static Matrix identite(int carree);
    float getValeur(int ligne, int colonne);
    float setValeur(int ligne, int colonne, float valeur);
    Matrix multiplicationMatrix(Matrix matrix);
    Matrix inverser();
    Matrix transposer();
    void translation(Matrix &matriceTranslatee, Vecteur vecteur);
    void rotationX(Matrix &matriceRotation, float cos, float sin);
    void rotationY(Matrix &matriceRotation, float cos, float sin);
    void rotationZ(Matrix &matriceRotation, float cos, float sin);
    void projectionZ(Matrix &matriceProjetee, float zC);
    void afficher(string texte);
    int getNombreColonne() const;
    int getNombreLigne() const;
};
Matrix transformation(Vecteur origine, Vecteur camera);
Matrix getMatrixHomogenePoint(Point point);
Matrix getMatrixHomogeneVecteur(Vecteur vecteur);
void matriceTransformationPoints(Point &p0, Point &p1, Point &p2, Vecteur origineRepere, Vecteur camera, float coefficientZoom);
void matriceTransformationPointOmbre(Point &p0, Vecteur origineRepere, Vecteur lumiere, Vecteur camera, float coefficientZoom);
void matriceTransformationVecteurs(Vecteur &v0, Vecteur &v1, Vecteur &v2, Vecteur origineRepere, Vecteur camera);
void matriceTransformationVecteur(Vecteur &v0, Vecteur origineRepere, Vecteur camera);
#endif	/* MATRIX_H */


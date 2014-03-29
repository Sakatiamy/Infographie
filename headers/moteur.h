/* 
 * File:   moteur.h
 * Author: katia
 *
 * Created on 25 février 2014, 22:11
 */

#ifndef MOTEUR_H
#define	MOTEUR_H

#include "triangle.h"


void lireFichierFilsDeFer(string texte, TGAImage &image, TGAColor c, Vecteur origine, Vecteur camera, float coefficientZoom);

void lireFichierComplet(string texte, TGAImage &image, TGAColor c, Vecteur origine, Vecteur camera, float coefficientZoom);

void lireFichierLigne(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, float coefficientZoom);

void lireFichierTriangle(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, float coefficientZoom);

void lireFichierTriangleBuffer(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom);

void lireFichierTriangleBufferPhong(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom);

void lireFichierTriangleBufferPhongNormalMapping(string texte, string imageNormalMapping, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom);

void lireFichierTriangleBufferPhongDiffuse(string texte, string imageDiffuse, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom);

void lireFichierTriangleBufferPhongTexture(string texte, string imageNormalMapping, string imageDiffuse, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom);

void lireFichierTexture(string texte, string imageNormalMapping, string imageDiffuse, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom);

void lireFichierFinal(string texte, string imageNormalMapping, string imageDiffuse, string imageOmbre, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, float* zBuffer_Ombre, string nomBuffer, float coefficientZoom);

#endif	/* MOTEUR_H */


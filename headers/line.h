/* 
 * File:   line.h
 * Author: katia
 *
 * Created on 25 février 2014, 22:11
 */

#ifndef LINE_H
#define	LINE_H

#include "outils.h"

void line(Point p0, Point p1, TGAImage &image, TGAColor c);

void lineDegrade(Point p0, Point p1, TGAImage &image, TGAColor c0, TGAColor c1);

void lineDegradeBuffer(Point p0, Point p1, TGAImage &image, TGAColor c0, TGAColor c1);

void lineDegradeBufferPhong(Point p0, Point p1, Vecteur v0, Vecteur v1, Vecteur lumiere, TGAImage &image);

void lineNormalMapping(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping);

void lineDiffuse(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageDiffuse);

void lineTexture(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse);

void lineFinale(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur origine, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse, TGAImage &imageOmbre, float* zBuffer_Ombre, float coefficientZoom);

#endif	/* LINE_H */


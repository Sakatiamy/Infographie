/* 
 * File:   triangle.h
 * Author: katia
 *
 * Created on 25 février 2014, 22:11
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include "line.h"

void triangle(Point p0, Point p1, Point p2, TGAImage &image, TGAColor c);

void triangleDegrade(Point p0, Point p1, Point p2, TGAImage &image, TGAColor c0, TGAColor c1, TGAColor c2);

void triangleDegradeBuffer(Point p0, Point p1, Point p2, TGAImage &image, TGAColor c0, TGAColor c1, TGAColor c2);

void triangleDegradeBufferPhong(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur lumiere, TGAImage &image);

void triangleDegradeBufferPhongNormalMapping(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping);

void triangleDegradeBufferPhongDiffuse(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageDiffuse);

void triangleDegradeBufferPhongTexture(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse);

void triangleFinal(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur origine, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse, TGAImage &imageOmbre, float* zBuffer_Ombre, float coefficientZoom);
#endif	/* TRIANGLE_H */


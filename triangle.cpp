#include "triangle.h"

void triangle(Point p0, Point p1, Point p2, TGAImage &image, TGAColor c) {
    ordonnerPoints(p0, p1, p2);
    if (yMax != yIntermediaire) {
        for (int y_i = yIntermediaire; y_i <= yMax; y_i++) {
            int x_a = equation(pMax, pIntermediaire, y_i);
            int x_b = equation(pMax, pMin, y_i);
            Point pA, pB;
            pA.x = x_a;
            pA.y = y_i;
            pB.x = x_b;
            pB.y = y_i;
            line(pA, pB, image, c);
        }
    }
    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {

            int x_a = equation(pMax, pMin, y_i);
            int x_b = equation(pIntermediaire, pMin, y_i);
            Point pA, pB;
            pA.x = x_a;
            pA.y = y_i;
            pB.x = x_b;
            pB.y = y_i;
            line(pB, pA, image, c);
        }
    }
    //Contours du triangle
    line(pMin, pIntermediaire, image, c);
    line(pIntermediaire, pMax, image, c);
    line(pMax, pMin, image, c);
}

void triangleDegrade(Point p0, Point p1, Point p2, TGAImage &image, TGAColor c0, TGAColor c1, TGAColor c2) {
    ordonnerPointsCouleurs(p0, p1, p2, c0, c1, c2);
    TGAColor c_a, c_b;
    if (yMax != yIntermediaire) {
        for (int y_i = yIntermediaire; y_i <= yMax; y_i++) {
            int x_a = equation(pMax, pIntermediaire, y_i);
            int x_b = equation(pMax, pMin, y_i);
            c_a = getColor(pMax, pIntermediaire, y_i, cMax, cIntermediaire);
            c_b = getColor(pMax, pMin, y_i, cMax, cMin);
            Point pA, pB;
            pA.x = x_a;
            pA.y = y_i;
            pB.x = x_b;
            pB.y = y_i;
            lineDegrade(pA, pB, image, c_a, c_b);
        }
    }

    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {

            int x_a = equation(pMax, pMin, y_i);
            int x_b = equation(pIntermediaire, pMin, y_i);
            c_a = getColor(pMax, pMin, y_i, cMax, cMin);
            c_b = getColor(pIntermediaire, pMin, y_i, cIntermediaire, cMin);
            Point pA, pB;
            pA.x = x_a;
            pA.y = y_i;
            pB.x = x_b;
            pB.y = y_i;
            lineDegrade(pB, pA, image, c_b, c_a);
        }
    }
    //Contours du triangle
    lineDegrade(pMin, pIntermediaire, image, cMin, cIntermediaire);
    lineDegrade(pIntermediaire, pMax, image, cIntermediaire, cMax);
    lineDegrade(pMax, pMin, image, cMax, cMin);
}

void triangleDegradeBuffer(Point p0, Point p1, Point p2, TGAImage &image, TGAColor c0, TGAColor c1, TGAColor c2) {
    ordonnerPointsCouleurs(p0, p1, p2, c0, c1, c2);
    TGAColor c_a, c_b;
    if (yMax != yIntermediaire) {
        for (int y_i = yIntermediaire; y_i <= yMax; y_i++) {
            Point pA, pB;
            pA = equationPoint(pMax, pIntermediaire, y_i);
            pB = equationPoint(pMax, pMin, y_i);
            c_a = getColor(pMax, pIntermediaire, y_i, cMax, cIntermediaire);
            c_b = getColor(pMax, pMin, y_i, cMax, cMin);
            lineDegradeBuffer(pA, pB, image, c_a, c_b);
        }
    }

    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {
            Point pA, pB;
            pA = equationPoint(pMax, pMin, y_i);
            pB = equationPoint(pIntermediaire, pMin, y_i);
            c_a = getColor(pMax, pMin, y_i, cMax, cMin);
            c_b = getColor(pIntermediaire, pMin, y_i, cIntermediaire, cMin);
            lineDegradeBuffer(pB, pA, image, c_b, c_a);
        }
    }
    //Contours du triangle
    lineDegradeBuffer(pMin, pIntermediaire, image, cMin, cIntermediaire);
    lineDegradeBuffer(pIntermediaire, pMax, image, cIntermediaire, cMax);
    lineDegradeBuffer(pMax, pMin, image, cMax, cMin);
}

void triangleDegradeBufferPhong(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur lumiere, TGAImage &image) {
    ordonnerPointsCouleursPhong(p0, p1, p2, v0, v1, v2);
    Vecteur vecteurTmp_1, vecteurTmp_2;
    if (yMax != yIntermediaire) {
        for (int y_i = yMax; y_i >= yIntermediaire; y_i--) {
            Point pA, pB;
            pA = equationPoint(pMax, pIntermediaire, y_i);
            pB = equationPoint(pMax, pMin, y_i);
            vecteurTmp_1 = equationVecteur(pMax, pIntermediaire, y_i, vecteurMax, vecteurIntermediaire);
            vecteurTmp_2 = equationVecteur(pMax, pMin, y_i, vecteurMax, vecteurMin);
            vecteurTmp_1 = normaliser(vecteurTmp_1);
            vecteurTmp_2 = normaliser(vecteurTmp_2);
            lineDegradeBufferPhong(pA, pB, vecteurTmp_1, vecteurTmp_2, lumiere, image);
        }
    }

    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {
            Point pA, pB;
            pA = equationPoint(pMax, pMin, y_i);
            pB = equationPoint(pIntermediaire, pMin, y_i);
            vecteurTmp_1 = equationVecteur(pMax, pMin, y_i, vecteurMax, vecteurMin);
            vecteurTmp_2 = equationVecteur(pIntermediaire, pMin, y_i, vecteurIntermediaire, vecteurMin);
            vecteurTmp_1 = normaliser(vecteurTmp_1);
            vecteurTmp_2 = normaliser(vecteurTmp_2);
            lineDegradeBufferPhong(pA, pB, vecteurTmp_1, vecteurTmp_2, lumiere, image);
        }
    }
}

void triangleDegradeBufferPhongNormalMapping(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping) {
    ordonnerPointsCouleursPhongTexture(p0, p1, p2, v0, v1, v2, vt0, vt1, vt2);
    if (yMax != yIntermediaire) {
        for (int y_i = yMax; y_i >= yIntermediaire; y_i--) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pIntermediaire, y_i);
            pB = equationPoint(pMax, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pIntermediaire, y_i, vecteurTexture_Max, vecteurTexture_Intermediaire);
            vecteurTexture_B = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            lineNormalMapping(pA, pB, vecteurTexture_A, vecteurTexture_B, camera, lumiere, image, imageNormalMapping);
        }
    }

    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pMin, y_i);
            pB = equationPoint(pIntermediaire, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            vecteurTexture_B = equationVecteurTexture(pIntermediaire, pMin, y_i, vecteurTexture_Intermediaire, vecteurTexture_Min);
            lineNormalMapping(pA, pB, vecteurTexture_A, vecteurTexture_B, camera, lumiere, image, imageNormalMapping);
        }
    }
}

void triangleDegradeBufferPhongDiffuse(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageDiffuse) {
    ordonnerPointsCouleursPhongTexture(p0, p1, p2, v0, v1, v2, vt0, vt1, vt2);
    if (yMax != yIntermediaire) {
        for (int y_i = yMax; y_i >= yIntermediaire; y_i--) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pIntermediaire, y_i);
            pB = equationPoint(pMax, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pIntermediaire, y_i, vecteurTexture_Max, vecteurTexture_Intermediaire);
            vecteurTexture_B = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            lineDiffuse(pA, pB, vecteurTexture_A, vecteurTexture_B, camera, lumiere, image, imageDiffuse);
        }
    }

    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pMin, y_i);
            pB = equationPoint(pIntermediaire, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            vecteurTexture_B = equationVecteurTexture(pIntermediaire, pMin, y_i, vecteurTexture_Intermediaire, vecteurTexture_Min);
            lineDiffuse(pA, pB, vecteurTexture_A, vecteurTexture_B, camera, lumiere, image, imageDiffuse);
        }
    }
}

void triangleDegradeBufferPhongTexture(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse) {
    ordonnerPointsCouleursPhongTexture(p0, p1, p2, v0, v1, v2, vt0, vt1, vt2);
    if (yMax != yIntermediaire) {
        for (int y_i = yMax; y_i >= yIntermediaire; y_i--) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pIntermediaire, y_i);
            pB = equationPoint(pMax, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pIntermediaire, y_i, vecteurTexture_Max, vecteurTexture_Intermediaire);
            vecteurTexture_B = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            lineTexture(pA, pB, vecteurTexture_A, vecteurTexture_B, camera, lumiere, image, imageNormalMapping, imageDiffuse);
        }
    }

    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pMin, y_i);
            pB = equationPoint(pIntermediaire, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            vecteurTexture_B = equationVecteurTexture(pIntermediaire, pMin, y_i, vecteurTexture_Intermediaire, vecteurTexture_Min);
            lineTexture(pA, pB, vecteurTexture_A, vecteurTexture_B, camera, lumiere, image, imageNormalMapping, imageDiffuse);
        }
    }
}

void triangleFinal(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2, Vecteur origine, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse, TGAImage &imageOmbre, float* zBuffer_Ombre, float coefficientZoom) {
    ordonnerPointsCouleursPhongTexture(p0, p1, p2, v0, v1, v2, vt0, vt1, vt2);
    if (yMax != yIntermediaire) {
        for (int y_i = yMax; y_i >= yIntermediaire; y_i--) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pIntermediaire, y_i);
            pB = equationPoint(pMax, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pIntermediaire, y_i, vecteurTexture_Max, vecteurTexture_Intermediaire);
            vecteurTexture_B = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            lineFinale(pA, pB, vecteurTexture_A, vecteurTexture_B, origine, camera, lumiere, image, imageNormalMapping, imageDiffuse, imageOmbre, zBuffer_Ombre, coefficientZoom);
        }
    }

    if (yMin != yIntermediaire) {
        for (int y_i = yMin; y_i < yIntermediaire; y_i++) {
            Point pA, pB;
            Vecteur vecteurTexture_A, vecteurTexture_B;
            pA = equationPoint(pMax, pMin, y_i);
            pB = equationPoint(pIntermediaire, pMin, y_i);
            vecteurTexture_A = equationVecteurTexture(pMax, pMin, y_i, vecteurTexture_Max, vecteurTexture_Min);
            vecteurTexture_B = equationVecteurTexture(pIntermediaire, pMin, y_i, vecteurTexture_Intermediaire, vecteurTexture_Min);
            lineFinale(pA, pB, vecteurTexture_A, vecteurTexture_B, origine, camera, lumiere, image, imageNormalMapping, imageDiffuse, imageOmbre, zBuffer_Ombre, coefficientZoom);
        }
    }
}

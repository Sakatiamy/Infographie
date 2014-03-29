#include "../headers/outils.h"

float* zBuffer;
int xMax, yMax, zMax, xIntermediaire, yIntermediaire, zIntermediaire, xMin, yMin, zMin;
Point pMax, pIntermediaire, pMin;
TGAColor cMax, cIntermediaire, cMin;
Vecteur vecteurMax, vecteurMin, vecteurIntermediaire, vecteurTexture_Max, vecteurTexture_Min, vecteurTexture_Intermediaire;
vector<Point> listePoints;

Vecteur produitVectoriel(Point p1, Point p2, Point p3) {
    Vecteur p1_p2;
    Vecteur p1_p3;
    p1_p2.x = p2.x - p1.x;
    p1_p2.y = p2.y - p1.y;
    p1_p2.z = p2.z - p1.z;

    p1_p3.x = p3.x - p1.x;
    p1_p3.y = p3.y - p1.y;
    p1_p3.z = p3.z - p1.z;

    Vecteur produitVectoriel;
    produitVectoriel.x = (p1_p2.y * p1_p3.z) - (p1_p2.z * p1_p3.y);
    produitVectoriel.y = (p1_p2.z * p1_p3.x) - (p1_p2.x * p1_p3.z);
    produitVectoriel.z = (p1_p2.x * p1_p3.y) - (p1_p2.y * p1_p3.x);

    return produitVectoriel;
}

float longueurVecteur(Vecteur vecteur) {
    float longueur;
    longueur = sqrt(pow(vecteur.x, 2) + pow(vecteur.y, 2) + pow(vecteur.z, 2));

    return longueur;
}

float produitScalaire(Vecteur vecteur1, Vecteur vecteur2) {
    float produitScalaire;
    produitScalaire = (vecteur1.x * vecteur2.x) + (vecteur1.y * vecteur2.y) + (vecteur1.z * vecteur2.z);

    return produitScalaire;
}

Vecteur normaliser(Vecteur vecteur) {
    Vecteur vecteurNormalise;
    float longueur = longueurVecteur(vecteur);
    vecteurNormalise.x = vecteur.x / longueur;
    vecteurNormalise.y = vecteur.y / longueur;
    vecteurNormalise.z = vecteur.z / longueur;

    return vecteurNormalise;
}

void zBufferInit() {
    float *tableauZ = new float[_COL * _LIGNE];
    for (int i = 0; i < _COL; i++) {
        for (int j = 0; j < _LIGNE; j++) {
            tableauZ[i + j * _LIGNE] = -INFINITY;
        }
    }
    zBuffer = tableauZ;
}

void zBufferImage(string texte) {
    float min, max;
    TGAImage image = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAColor c;
    min = INFINITY;
    max = -INFINITY;
    for (int i = 0; i < _COL; i++) {
        for (int j = 0; j < _LIGNE; j++) {
            if (zBuffer[i + j * _LIGNE] < min && zBuffer[i + j * _LIGNE] != -INFINITY) {
                min = zBuffer[i + j * _LIGNE];
            }
            if (zBuffer[i + j * _LIGNE] > max) {
                max = zBuffer[i + j * _LIGNE];
            }
        }
    }

    for (int i = 0; i < _COL; i++) {
        for (int j = 0; j < _LIGNE; j++) {
            int intensite = 255 * (zBuffer[i + j * _LIGNE] - min) / (max - min);
            if (intensite < 0) {
                intensite = 0;
            }
            if (intensite > 255) {
                intensite = 255;
            }
            //            cout << intensite << endl;
            c.r = 0;
            c.g = intensite;
            c.b = 0;
            image.set(i, j, c);
        }
    }
    image.flip_vertically();
    image.write_tga_file(texte.c_str());
}

float getAngleX(Vecteur v0, Vecteur v1) {
    float norme, normeX, normeY, cos_Angle, angle, angleC;
    normeX = abs(v1.x - v0.x);
    normeY = abs(v1.y - v0.y);
    norme = sqrt(pow(normeX, 2) + pow(normeY, 2));
    cos_Angle = normeX / norme;
    angleC = acos(cos_Angle);
    angle = angleC;

    return angle;
}

float getAngleY(Vecteur v0, Vecteur v1) {
    float norme, normeX, normeZ, cos_Angle, angle, angleC;
    normeX = abs(v1.x - v0.x);
    normeZ = abs(v1.z - v0.z);
    norme = sqrt(pow(normeX, 2) + pow(normeZ, 2));
    cos_Angle = normeZ / norme;
    angleC = acos(cos_Angle);
    angle = angleC;

    return angle;
}

float getCosAngleX(Vecteur v0, Vecteur v1) {
    float norme, normeX, normeY, cos_Angle;
    normeX = abs(v1.x - v0.x);
    normeY = abs(v1.y - v0.y);
    norme = sqrt(pow(normeX, 2) + pow(normeY, 2));
    cos_Angle = normeX / norme;

    return cos_Angle;
}

float getSinAngleX(Vecteur v0, Vecteur v1) {
    float norme, normeX, normeY, sin_Angle;
    normeX = abs(v1.x - v0.x);
    normeY = abs(v1.y - v0.y);
    norme = sqrt(pow(normeX, 2) + pow(normeY, 2));
    sin_Angle = normeY / norme;

    return sin_Angle;
}

float getCosAngleY(Vecteur v0, Vecteur v1) {
    float norme, normeX, normeZ, cos_Angle;
    normeX = abs(v1.x - v0.x);
    normeZ = abs(v1.z - v0.z);
    norme = sqrt(pow(normeX, 2) + pow(normeZ, 2));
    cos_Angle = normeZ / norme;

    return cos_Angle;
}

float getSinAngleY(Vecteur v0, Vecteur v1) {
    float norme, normeX, normeZ, sin_Angle;
    normeX = abs(v1.x - v0.x);
    normeZ = abs(v1.z - v0.z);
    norme = sqrt(pow(normeX, 2) + pow(normeZ, 2));
    sin_Angle = normeX / norme;

    return sin_Angle;
}

float equation(Point p0, Point p1, int y) {
    float a, b, x;
    if ((int) p1.x != (int) p0.x) {
        a = (p1.y - p0.y) / float(p1.x - p0.x);
    } else {
        a = float(p1.y - p0.y);
    }
    b = p0.y - a * p0.x;
    x = (y - b) / a;
    return x;
}

Point equationPoint(Point p0, Point p1, int y) {
    float x, t, t2, z;
    x = equation(p0, p1, y);
    Vecteur vecteurDir;
    vecteurDir.x = p1.x - p0.x;
    vecteurDir.y = p1.y - p0.y;
    vecteurDir.z = p1.z - p0.z;

    t2 = (y - p0.y) / (abs(vecteurDir.y) < .0001 ? 1 : vecteurDir.y);
    t = t2;
    z = p0.z + vecteurDir.z*t;

    Point point;
    point.x = x;
    point.y = y;
    point.z = z;
    return point;
}

Vecteur equationVecteur(Point p0, Point p1, int y, Vecteur v0, Vecteur v1) {
    v0 = normaliser(v0);
    v1 = normaliser(v1);
    float t = ((p1.y - p0.y) != 0 ? (y - p0.y) / float(p1.y - p0.y) : 0);
    Vecteur res;
    res.x = v0.x * (1. - t) + v1.x*t;
    res.y = v0.y * (1. - t) + v1.y*t;
    res.z = v0.z * (1. - t) + v1.z*t;
    return res;
}

Vecteur equationVecteurTexture(Point p0, Point p1, int y, Vecteur vt0, Vecteur vt1) {
    float t = ((p1.y - p0.y) != 0 ? (y - p0.y) / float(p1.y - p0.y) : 0);
    Vecteur res;
    res.x = vt0.x * (1. - t) + vt1.x*t;
    res.y = vt0.y * (1. - t) + vt1.y*t;
    res.z = vt0.z * (1. - t) + vt1.z*t;
    return res;
}

TGAColor getColor(Point p0, Point p1, int y, TGAColor c0, TGAColor c1) {
    float a_red, a_blue, a_green, b_red, b_blue, b_green;
    TGAColor c;
    a_red = (p1.y - p0.y) / float(c1.r - c0.r ? c1.r - c0.r : 1);
    a_blue = (p1.y - p0.y) / float(c1.b - c0.b ? c1.b - c0.b : 1);
    a_green = (p1.y - p0.y) / float(c1.g - c0.g ? c1.g - c0.g : 1);
    b_red = p0.y - a_red * c0.r;
    b_blue = p0.y - a_blue * c0.b;
    b_green = p0.y - a_green * c0.g;
    c.r = (y - b_red) / float(a_red ? a_red : 1);
    c.b = (y - b_blue) / float(a_blue ? a_blue : 1);
    c.g = (y - b_green) / float(a_green ? a_green : 1);
    return c;
}

void ordonnerPoints(Point p0, Point p1, Point p2) {
    xMax = p0.x;
    yMax = p0.y;
    xIntermediaire = p0.x;
    yIntermediaire = p0.y;
    xMin = p0.x;
    yMin = p0.y;

    if (p0.y >= p1.y && p0.y > p2.y) {
        xMax = p0.x;
        yMax = p0.y;
        if (p1.y > p2.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            xMin = p2.x;
            yMin = p2.y;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            xMin = p1.x;
            yMin = p1.y;
        }
    }
    if (p1.y > p0.y && p1.y >= p2.y) {
        xMax = p1.x;
        yMax = p1.y;
        if (p0.y > p2.y) {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            xMin = p2.x;
            yMin = p2.y;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            xMin = p0.x;
            yMin = p0.y;
        }
    }
    if (p2.y >= p0.y && p2.y > p1.y) {
        xMax = p2.x;
        yMax = p2.y;
        if (p1.y > p0.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            xMin = p0.x;
            yMin = p0.y;
        } else {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            xMin = p1.x;
            yMin = p1.y;
        }
    }
    pMax.x = xMax;
    pMax.y = yMax;
    pIntermediaire.x = xIntermediaire;
    pIntermediaire.y = yIntermediaire;
    pMin.x = xMin;
    pMin.y = yMin;
}

void ordonnerPointsCouleurs(Point p0, Point p1, Point p2, TGAColor c0, TGAColor c1, TGAColor c2) {
    xMax = p0.x;
    yMax = p0.y;
    zMax = p0.z;
    xIntermediaire = p0.x;
    yIntermediaire = p0.y;
    zIntermediaire = p0.z;
    xMin = p0.x;
    yMin = p0.y;
    zMin = p0.z;

    if (p0.y >= p1.y && p0.y > p2.y) {
        xMax = p0.x;
        yMax = p0.y;
        zMax = p0.z;
        cMax = c0;
        if (p1.y > p2.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            zIntermediaire = p1.z;
            xMin = p2.x;
            yMin = p2.y;
            zMin = p2.z;
            cIntermediaire = c1;
            cMin = c2;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            zIntermediaire = p2.z;
            xMin = p1.x;
            yMin = p1.y;
            zMin = p1.z;
            cIntermediaire = c2;
            cMin = c1;
        }
    }
    if (p1.y > p0.y && p1.y >= p2.y) {
        xMax = p1.x;
        yMax = p1.y;
        zMax = p1.z;
        cMax = c1;
        if (p0.y > p2.y) {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            zIntermediaire = p0.z;
            xMin = p2.x;
            yMin = p2.y;
            zMin = p2.z;
            cIntermediaire = c0;
            cMin = c2;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            zIntermediaire = p2.z;
            xMin = p0.x;
            yMin = p0.y;
            zMin = p0.z;
            cIntermediaire = c2;
            cMin = c0;
        }
    }
    if (p2.y >= p0.y && p2.y > p1.y) {
        xMax = p2.x;
        yMax = p2.y;
        zMax = p2.z;
        cMax = c2;

        if (p1.y > p0.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            zIntermediaire = p1.z;
            xMin = p0.x;
            yMin = p0.y;
            zMin = p0.z;
            cIntermediaire = c1;
            cMin = c0;
        } else {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            zIntermediaire = p0.z;
            xMin = p1.x;
            yMin = p1.y;
            zMin = p1.z;
            cIntermediaire = c0;
            cMin = c1;
        }
    }
    pMax.x = xMax;
    pMax.y = yMax;
    pMax.z = zMax;
    pIntermediaire.x = xIntermediaire;
    pIntermediaire.y = yIntermediaire;
    pIntermediaire.z = zIntermediaire;
    pMin.x = xMin;
    pMin.y = yMin;
    pMin.z = zMin;
}

void ordonnerPointsCouleursPhong(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2) {
    xMax = p0.x;
    yMax = p0.y;
    zMax = p0.z;
    xIntermediaire = p0.x;
    yIntermediaire = p0.y;
    zIntermediaire = p0.z;
    xMin = p0.x;
    yMin = p0.y;
    zMin = p0.z;
    vecteurMax = v0;
    vecteurMin = v0;
    vecteurIntermediaire = v0;

    if (p0.y >= p1.y && p0.y > p2.y) {
        xMax = p0.x;
        yMax = p0.y;
        zMax = p0.z;
        vecteurMax = v0;
        if (p1.y > p2.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            zIntermediaire = p1.z;
            xMin = p2.x;
            yMin = p2.y;
            zMin = p2.z;
            vecteurIntermediaire = v1;
            vecteurMin = v2;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            zIntermediaire = p2.z;
            xMin = p1.x;
            yMin = p1.y;
            zMin = p1.z;
            vecteurIntermediaire = v2;
            vecteurMin = v1;
        }
    }
    if (p1.y > p0.y && p1.y >= p2.y) {
        xMax = p1.x;
        yMax = p1.y;
        zMax = p1.z;
        vecteurMax = v1;
        if (p0.y > p2.y) {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            zIntermediaire = p0.z;
            xMin = p2.x;
            yMin = p2.y;
            zMin = p2.z;
            vecteurIntermediaire = v0;
            vecteurMin = v2;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            zIntermediaire = p2.z;
            xMin = p0.x;
            yMin = p0.y;
            zMin = p0.z;
            vecteurIntermediaire = v2;
            vecteurMin = v0;
        }
    }
    if (p2.y >= p0.y && p2.y > p1.y) {
        xMax = p2.x;
        yMax = p2.y;
        zMax = p2.z;
        vecteurMax = v2;

        if (p1.y > p0.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            zIntermediaire = p1.z;
            xMin = p0.x;
            yMin = p0.y;
            zMin = p0.z;
            vecteurIntermediaire = v1;
            vecteurMin = v0;
        } else {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            zIntermediaire = p0.z;
            xMin = p1.x;
            yMin = p1.y;
            zMin = p1.z;
            vecteurIntermediaire = v0;
            vecteurMin = v1;
        }
    }
    pMax.x = xMax;
    pMax.y = yMax;
    pMax.z = zMax;
    pIntermediaire.x = xIntermediaire;
    pIntermediaire.y = yIntermediaire;
    pIntermediaire.z = zIntermediaire;
    pMin.x = xMin;
    pMin.y = yMin;
    pMin.z = zMin;
}

void ordonnerPointsCouleursPhongTexture(Point p0, Point p1, Point p2, Vecteur v0, Vecteur v1, Vecteur v2, Vecteur vt0, Vecteur vt1, Vecteur vt2) {
    xMax = p0.x;
    yMax = p0.y;
    zMax = p0.z;
    xIntermediaire = p0.x;
    yIntermediaire = p0.y;
    zIntermediaire = p0.z;
    xMin = p0.x;
    yMin = p0.y;
    zMin = p0.z;
    vecteurMax = v0;
    vecteurMin = v0;
    vecteurIntermediaire = v0;
    vecteurTexture_Max = vt0;
    vecteurTexture_Min = vt0;
    vecteurTexture_Intermediaire = vt0;

    if (p0.y >= p1.y && p0.y > p2.y) {
        xMax = p0.x;
        yMax = p0.y;
        zMax = p0.z;
        vecteurMax = v0;
        vecteurTexture_Max = vt0;
        if (p1.y > p2.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            zIntermediaire = p1.z;
            xMin = p2.x;
            yMin = p2.y;
            zMin = p2.z;
            vecteurIntermediaire = v1;
            vecteurMin = v2;
            vecteurTexture_Intermediaire = vt1;
            vecteurTexture_Min = vt2;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            zIntermediaire = p2.z;
            xMin = p1.x;
            yMin = p1.y;
            zMin = p1.z;
            vecteurIntermediaire = v2;
            vecteurMin = v1;
            vecteurTexture_Intermediaire = vt2;
            vecteurTexture_Min = vt1;
        }
    }
    if (p1.y > p0.y && p1.y >= p2.y) {
        xMax = p1.x;
        yMax = p1.y;
        zMax = p1.z;
        vecteurMax = v1;
        vecteurTexture_Max = vt1;
        if (p0.y > p2.y) {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            zIntermediaire = p0.z;
            xMin = p2.x;
            yMin = p2.y;
            zMin = p2.z;
            vecteurIntermediaire = v0;
            vecteurMin = v2;
            vecteurTexture_Intermediaire = vt0;
            vecteurTexture_Min = vt2;
        } else {
            xIntermediaire = p2.x;
            yIntermediaire = p2.y;
            zIntermediaire = p2.z;
            xMin = p0.x;
            yMin = p0.y;
            zMin = p0.z;
            vecteurIntermediaire = v2;
            vecteurMin = v0;
            vecteurTexture_Intermediaire = vt2;
            vecteurTexture_Min = vt0;
        }
    }
    if (p2.y >= p0.y && p2.y > p1.y) {
        xMax = p2.x;
        yMax = p2.y;
        zMax = p2.z;
        vecteurMax = v2;
        vecteurTexture_Max = vt2;
        if (p1.y > p0.y) {
            xIntermediaire = p1.x;
            yIntermediaire = p1.y;
            zIntermediaire = p1.z;
            xMin = p0.x;
            yMin = p0.y;
            zMin = p0.z;
            vecteurIntermediaire = v1;
            vecteurMin = v0;
            vecteurTexture_Intermediaire = vt1;
            vecteurTexture_Min = vt0;
        } else {
            xIntermediaire = p0.x;
            yIntermediaire = p0.y;
            zIntermediaire = p0.z;
            xMin = p1.x;
            yMin = p1.y;
            zMin = p1.z;
            vecteurIntermediaire = v0;
            vecteurMin = v1;
            vecteurTexture_Intermediaire = vt0;
            vecteurTexture_Min = vt1;
        }
    }
    pMax.x = xMax;
    pMax.y = yMax;
    pMax.z = zMax;
    pIntermediaire.x = xIntermediaire;
    pIntermediaire.y = yIntermediaire;
    pIntermediaire.z = zIntermediaire;
    pMin.x = xMin;
    pMin.y = yMin;
    pMin.z = zMin;
}




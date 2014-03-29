#include "line.h"

void line(Point p0, Point p1, TGAImage &image, TGAColor c) {
    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
    }
    float dx = p1.x - p0.x;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;
    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        if (steep) {
            image.set(y, x, c);
        } else {
            image.set(x, y, c);
        }
        error2 += dy2;
        if (error2 > dx) {
            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void lineDegrade(Point p0, Point p1, TGAImage &image, TGAColor c0, TGAColor c1) {
    TGAColor c2;
    float dr, db, dg, old_c0_r, old_c0_b, old_c0_g;
    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
        swap(c0, c1);
    }

    dr = (c1.r - c0.r) / (abs(float((int) p1.x - (int) p0.x)) < .001 ? 1 : (float((int) p1.x - (int) p0.x)));
    db = (c1.b - c0.b) / (abs(float((int) p1.x - (int) p0.x)) < .001 ? 1 : (float((int) p1.x - (int) p0.x)));
    dg = (c1.g - c0.g) / (abs(float((int) p1.x - (int) p0.x)) < .001 ? 1 : (float((int) p1.x - (int) p0.x)));

    old_c0_r = c0.r;
    old_c0_b = c0.b;
    old_c0_g = c0.g;

    float dx = p1.x - p0.x;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;
    c2.r = c0.r;
    c2.b = c0.b;
    c2.g = c0.g;
    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        if (steep) {
            image.set(y, x, c2);
        } else {
            image.set(x, y, c2);
        }
        old_c0_r += dr;
        old_c0_b += db;
        old_c0_g += dg;

        c2.r = old_c0_r;
        c2.b = old_c0_b;
        c2.g = old_c0_g;

        error2 += dy2;
        if (error2 > dx) {
            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void lineDegradeBuffer(Point p0, Point p1, TGAImage &image, TGAColor c0, TGAColor c1) {
    TGAColor c2;
    float dr, db, dg, old_c0_r, old_c0_b, old_c0_g;
    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
        swap(c0, c1);
    }

    dr = (c1.r - c0.r) / (abs(float((int) p1.x - (int) p0.x)) < .001 ? 1 : (float((int) p1.x - (int) p0.x)));
    db = (c1.b - c0.b) / (abs(float((int) p1.x - (int) p0.x)) < .001 ? 1 : (float((int) p1.x - (int) p0.x)));
    dg = (c1.g - c0.g) / (abs(float((int) p1.x - (int) p0.x)) < .001 ? 1 : (float((int) p1.x - (int) p0.x)));

    old_c0_r = c0.r;
    old_c0_b = c0.b;
    old_c0_g = c0.g;

    float dx = p1.x - p0.x;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;
    c2.r = c0.r;
    c2.b = c0.b;
    c2.g = c0.g;

    float pasZ;
    pasZ = (p1.z - p0.z) / (abs(p1.x - p0.x + 1) < .001 ? 0.001 : (p1.x - p0.x + 1));

    float old_z = p0.z;

    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        if (steep) {
            if (old_z >= zBuffer[y + x * _LIGNE]) {
                image.set(y, x, c2);
                zBuffer[y + x * _LIGNE] = old_z;
            }
        } else {
            if (old_z >= zBuffer[x + y * _LIGNE]) {
                image.set(x, y, c2);
                zBuffer[x + y * _LIGNE] = old_z;
            }
        }
        old_z += pasZ;

        old_c0_r += dr;
        old_c0_b += db;
        old_c0_g += dg;

        c2.r = old_c0_r;
        c2.b = old_c0_b;
        c2.g = old_c0_g;

        error2 += dy2;
        if (error2 > dx) {

            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void lineDegradeBufferPhong(Point p0, Point p1, Vecteur v0, Vecteur v1, Vecteur lumiere, TGAImage &image) {
    TGAColor cVecteur;
    lumiere = normaliser(lumiere);
    v0 = normaliser(v0);
    v1 = normaliser(v1);

    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
        swap(v0.x, v1.x);
        swap(v0.y, v1.y);
        swap(v0.z, v1.z);
    }

    float dx = p1.y - p0.y;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;

    //Variation lineaire de z
    float pasZ, old_z;
    Vecteur vecteurTmp;

    pasZ = (p1.z - p0.z) / (abs(p1.x - p0.x + 1) < 0.001 ? 0.001 : (p1.x - p0.x + 1));
    old_z = p0.z;

    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        float t = (p1.x - p0.x ? (x - p0.x) / float(p1.x - p0.x + 1) : 0);
        vecteurTmp.x = v0.x * (1. - t) + v1.x*t;
        vecteurTmp.y = v0.y * (1. - t) + v1.y*t;
        vecteurTmp.z = v0.z * (1. - t) + v1.z*t;
        vecteurTmp = normaliser(vecteurTmp);
        if (steep) {
            if (old_z >= zBuffer[y + x * _LIGNE]) {
                int luminosite = produitScalaire(vecteurTmp, lumiere)*255;
                if (luminosite < 0) {
                    luminosite = 0;
                }
                if (luminosite > 255) {
                    luminosite = 255;
                }
                cVecteur = TGAColor(0, luminosite, 0, 255);
                image.set(y, x, cVecteur);
                zBuffer[y + x * _LIGNE] = old_z;
            }
        } else {
            if (old_z >= zBuffer[x + y * _LIGNE]) {
                int luminosite = produitScalaire(vecteurTmp, lumiere)*255;
                if (luminosite < 0) {
                    luminosite = 0;
                }
                if (luminosite > 255) {
                    luminosite = 255;
                }
                cVecteur = TGAColor(0, luminosite, 0, 255);
                image.set(x, y, cVecteur);
                zBuffer[x + y * _LIGNE] = old_z;
            }
        }

        old_z += pasZ;

        error2 += dy2;
        if (error2 > dx) {
            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void lineNormalMapping(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping) {
    lumiere = normaliser(lumiere);
    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
        swap(vt0.x, vt1.x);
        swap(vt0.y, vt1.y);
        swap(vt0.z, vt1.z);
    }
    float dx = p1.y - p0.y;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;

    //Variation lineaire de z
    float pasZ, old_z;
    Vecteur vecteurTexture_Tmp;
    TGAColor cVecteur;

    pasZ = (p1.z - p0.z) / (abs(p1.x - p0.x + 1) < 0.001 ? 0.001 : (p1.x - p0.x + 1));
    old_z = p0.z;
    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        float t = (p1.x - p0.x ? (x - p0.x) / float(p1.x - p0.x + 1) : 0);
        vecteurTexture_Tmp.x = vt0.x * (1. - t) + vt1.x*t;
        vecteurTexture_Tmp.y = vt0.y * (1. - t) + vt1.y*t;
        vecteurTexture_Tmp.z = vt0.z * (1. - t) + vt1.z*t;

        TGAColor cNormalMapping;
        cNormalMapping = imageNormalMapping.get(vecteurTexture_Tmp.x * imageNormalMapping.get_width(), vecteurTexture_Tmp.y * imageNormalMapping.get_height());

        Vecteur vecteurTexture;
        vecteurTexture.x = (float) cNormalMapping.r;
        vecteurTexture.y = (float) cNormalMapping.g;
        vecteurTexture.z = (float) cNormalMapping.b;
        vecteurTexture = normaliser(vecteurTexture);
        vecteurTexture.x = (vecteurTexture.x * 2) - 1;
        vecteurTexture.y = (vecteurTexture.y * 2) - 1;
        vecteurTexture.z = (vecteurTexture.z * 2) - 1;
        vecteurTexture = normaliser(vecteurTexture);

        int luminosite1, luminosite2, luminosite3;
        luminosite1 = produitScalaire(vecteurTexture, lumiere) * 255;
        luminosite2 = produitScalaire(vecteurTexture, lumiere) * 255;
        luminosite3 = produitScalaire(vecteurTexture, lumiere) * 255;
        if (luminosite1 < 0) {
            luminosite1 = 0;
        }
        if (luminosite1 > 255) {
            luminosite1 = 255;
        }
        if (luminosite2 < 0) {
            luminosite2 = 0;
        }
        if (luminosite2 > 255) {
            luminosite2 = 255;
        }
        if (luminosite3 < 0) {
            luminosite3 = 0;
        }
        if (luminosite3 > 255) {
            luminosite3 = 255;
        }

//        cVecteur = TGAColor(luminosite1, luminosite2, luminosite3, 255);
        cVecteur = TGAColor(0, luminosite2, 0, 255);

        if (steep) {
            if (old_z >= zBuffer[y + x * _LIGNE]) {
                image.set(y, x, cVecteur);
                zBuffer[y + x * _LIGNE] = old_z;
            }
        } else {
            if (old_z >= zBuffer[x + y * _LIGNE]) {
                image.set(x, y, cVecteur);
                zBuffer[x + y * _LIGNE] = old_z;
            }
        }

        old_z += pasZ;

        error2 += dy2;
        if (error2 > dx) {
            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void lineDiffuse(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageDiffuse) {
    lumiere = normaliser(lumiere);
    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
        swap(vt0.x, vt1.x);
        swap(vt0.y, vt1.y);
        swap(vt0.z, vt1.z);
    }
    float dx = p1.y - p0.y;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;

    //Variation lineaire de z
    float pasZ, old_z;
    Vecteur vecteurTexture_Tmp;

    pasZ = (p1.z - p0.z) / (abs(p1.x - p0.x + 1) < 0.001 ? 0.001 : (p1.x - p0.x + 1));
    old_z = p0.z;
    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        float t = (p1.x - p0.x ? (x - p0.x) / float(p1.x - p0.x + 1) : 0);
        vecteurTexture_Tmp.x = vt0.x * (1. - t) + vt1.x*t;
        vecteurTexture_Tmp.y = vt0.y * (1. - t) + vt1.y*t;
        vecteurTexture_Tmp.z = vt0.z * (1. - t) + vt1.z*t;

        TGAColor cDiffuse;
        cDiffuse = imageDiffuse.get(vecteurTexture_Tmp.x * imageDiffuse.get_width(), vecteurTexture_Tmp.y * imageDiffuse.get_height());

        if (steep) {
            if (old_z >= zBuffer[y + x * _LIGNE]) {
                image.set(y, x, cDiffuse);
                zBuffer[y + x * _LIGNE] = old_z;
            }
        } else {
            if (old_z >= zBuffer[x + y * _LIGNE]) {
                image.set(x, y, cDiffuse);
                zBuffer[x + y * _LIGNE] = old_z;
            }
        }

        old_z += pasZ;

        error2 += dy2;
        if (error2 > dx) {
            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void lineTexture(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse) {
    lumiere = normaliser(lumiere);
    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
        swap(vt0.x, vt1.x);
        swap(vt0.y, vt1.y);
        swap(vt0.z, vt1.z);
    }
    float dx = p1.y - p0.y;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;

    //Variation lineaire de z
    float pasZ, old_z;
    Vecteur vecteurTexture_Tmp;
    TGAColor cVecteur;

    pasZ = (p1.z - p0.z) / (abs(p1.x - p0.x + 1) < 0.001 ? 0.001 : (p1.x - p0.x + 1));
    old_z = p0.z;
    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        float t = (p1.x - p0.x ? (x - p0.x) / float(p1.x - p0.x + 1) : 0);

        vecteurTexture_Tmp.x = vt0.x * (1. - t) + vt1.x*t;
        vecteurTexture_Tmp.y = vt0.y * (1. - t) + vt1.y*t;
        vecteurTexture_Tmp.z = vt0.z * (1. - t) + vt1.z*t;

        TGAColor cNormalMapping, cDiffuse;
        cNormalMapping = imageNormalMapping.get(vecteurTexture_Tmp.x * imageNormalMapping.get_width(), vecteurTexture_Tmp.y * imageNormalMapping.get_height());
        cDiffuse = imageDiffuse.get(vecteurTexture_Tmp.x * imageDiffuse.get_width(), vecteurTexture_Tmp.y * imageDiffuse.get_height());

        Vecteur vecteurTexture, specular;
        vecteurTexture.x = (float) cNormalMapping.r / 255;
        vecteurTexture.y = (float) cNormalMapping.g / 255;
        vecteurTexture.z = (float) cNormalMapping.b / 255;
        vecteurTexture.x = (vecteurTexture.x * 2) - 1;
        vecteurTexture.y = (vecteurTexture.y * 2) - 1;
        vecteurTexture.z = (vecteurTexture.z * 2) - 1;
        vecteurTexture = normaliser(vecteurTexture);

        specular.x = lumiere.x - (2 * produitScalaire(vecteurTexture, lumiere) + 1) * vecteurTexture.x;
        specular.y = lumiere.y - (2 * produitScalaire(vecteurTexture, lumiere) + 1) * vecteurTexture.y;
        specular.z = lumiere.z - (2 * produitScalaire(vecteurTexture, lumiere) + 1) * vecteurTexture.z;
        specular = normaliser(specular);
        int luminosite1, luminosite2, luminosite3;

        float coefficient = 1;
        float coefficientSpec = 250;

        luminosite1 = (produitScalaire(vecteurTexture, lumiere) + pow(produitScalaire(specular, camera), coefficientSpec)) * cDiffuse.r * coefficient;
        luminosite2 = (produitScalaire(vecteurTexture, lumiere) + pow(produitScalaire(specular, camera), coefficientSpec)) * cDiffuse.g * coefficient;
        luminosite3 = (produitScalaire(vecteurTexture, lumiere) + pow(produitScalaire(specular, camera), coefficientSpec)) * cDiffuse.b * coefficient;

        if (luminosite1 < 0) {
            luminosite1 = 0;
        }
        if (luminosite1 > 255) {
            luminosite1 = 255;
        }
        if (luminosite2 < 0) {
            luminosite2 = 0;
        }
        if (luminosite2 > 255) {
            luminosite2 = 255;
        }
        if (luminosite3 < 0) {
            luminosite3 = 0;
        }
        if (luminosite3 > 255) {
            luminosite3 = 255;
        }

        cVecteur = TGAColor(luminosite1, luminosite2, luminosite3, 255);

        if (steep) {
            if (old_z >= zBuffer[y + x * _LIGNE]) {
                image.set(y, x, cVecteur);
                zBuffer[y + x * _LIGNE] = old_z;
            }
        } else {
            if (old_z >= zBuffer[x + y * _LIGNE]) {
                image.set(x, y, cVecteur);
                zBuffer[x + y * _LIGNE] = old_z;
            }
        }

        old_z += pasZ;

        error2 += dy2;
        if (error2 > dx) {
            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

void lineFinale(Point p0, Point p1, Vecteur vt0, Vecteur vt1, Vecteur origine, Vecteur camera, Vecteur lumiere, TGAImage &image, TGAImage &imageNormalMapping, TGAImage &imageDiffuse, TGAImage &imageOmbre, float* zBuffer_Ombre, float coefficientZoom ) {
    lumiere = normaliser(lumiere);
    bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
    if (steep) {
        swap(p0.x, p0.y);
        swap(p1.x, p1.y);
    }
    if (p0.x > p1.x) {
        swap(p0.x, p1.x);
        swap(p0.y, p1.y);
        swap(p0.z, p1.z);
        swap(vt0.x, vt1.x);
        swap(vt0.y, vt1.y);
        swap(vt0.z, vt1.z);
    }
    float dx = p1.y - p0.y;
    float dy2 = 2 * abs(p1.y - p0.y);
    float error2 = 0; // error2 = 2*error * dx;

    //Variation lineaire de z
    float pasZ, old_z;
    Vecteur vecteurTexture_Tmp;
    TGAColor cVecteur;

    pasZ = (p1.z - p0.z) / (abs(p1.x - p0.x + 1) < 0.001 ? 0.001 : (p1.x - p0.x + 1));
    old_z = p0.z;
    for (int x = p0.x, y = p0.y; x <= p1.x; x++) {
        float t = (p1.x - p0.x ? (x - p0.x) / float(p1.x - p0.x + 1) : 0);

        vecteurTexture_Tmp.x = vt0.x * (1. - t) + vt1.x*t;
        vecteurTexture_Tmp.y = vt0.y * (1. - t) + vt1.y*t;
        vecteurTexture_Tmp.z = vt0.z * (1. - t) + vt1.z*t;

        TGAColor cNormalMapping, cDiffuse;
        cNormalMapping = imageNormalMapping.get(vecteurTexture_Tmp.x * imageNormalMapping.get_width(), vecteurTexture_Tmp.y * imageNormalMapping.get_height());
        cDiffuse = imageDiffuse.get(vecteurTexture_Tmp.x * imageDiffuse.get_width(), vecteurTexture_Tmp.y * imageDiffuse.get_height());

        Vecteur vecteurTexture, specular;
        vecteurTexture.x = (float) cNormalMapping.r / 255;
        vecteurTexture.y = (float) cNormalMapping.g / 255;
        vecteurTexture.z = (float) cNormalMapping.b / 255;
        vecteurTexture.x = (vecteurTexture.x * 2) - 1;
        vecteurTexture.y = (vecteurTexture.y * 2) - 1;
        vecteurTexture.z = (vecteurTexture.z * 2) - 1;
        vecteurTexture = normaliser(vecteurTexture);

        
        specular.x = lumiere.x - (2 * produitScalaire(vecteurTexture, lumiere) + 1) * vecteurTexture.x;
        specular.y = lumiere.y - (2 * produitScalaire(vecteurTexture, lumiere) + 1) * vecteurTexture.y;
        specular.z = lumiere.z - (2 * produitScalaire(vecteurTexture, lumiere) + 1) * vecteurTexture.z;
        specular = normaliser(specular);
        int luminosite1, luminosite2, luminosite3;

        float coefficient = 1.2;
        float coefficientSpec = 250;
        float coefficientOmbre = 0.5;

        luminosite1 = (produitScalaire(vecteurTexture, lumiere) + pow(produitScalaire(specular, camera), coefficientSpec)) * cDiffuse.r * coefficient;
        luminosite2 = (produitScalaire(vecteurTexture, lumiere) + pow(produitScalaire(specular, camera), coefficientSpec)) * cDiffuse.g * coefficient;
        luminosite3 = (produitScalaire(vecteurTexture, lumiere) + pow(produitScalaire(specular, camera), coefficientSpec)) * cDiffuse.b * coefficient;
        
        if (luminosite1 < 0) {
            luminosite1 = 0;
        }
        if (luminosite1 > 255) {
            luminosite1 = 255;
        }
        if (luminosite2 < 0) {
            luminosite2 = 0;
        }
        if (luminosite2 > 255) {
            luminosite2 = 255;
        }
        if (luminosite3 < 0) {
            luminosite3 = 0;
        }
        if (luminosite3 > 255) {
            luminosite3 = 255;
        }

        cVecteur = TGAColor(luminosite1, luminosite2, luminosite3, 255);

        if (steep) {
            if (old_z >= zBuffer[y + x * _LIGNE]) {
                Point pointOmbre;
                pointOmbre.x = y;
                pointOmbre.y = x;
                pointOmbre.z = old_z;
                matriceTransformationPointOmbre(pointOmbre, origine, lumiere, camera, coefficientZoom);
                if (zBuffer_Ombre[(int) pointOmbre.x + (int) pointOmbre.y * _LIGNE] > pointOmbre.z + 10) {
                    cVecteur.r = coefficientOmbre * cVecteur.r;
                    cVecteur.g = coefficientOmbre * cVecteur.g;
                    cVecteur.b = coefficientOmbre * cVecteur.b;
                }
                image.set(y, x, cVecteur);
                zBuffer[y + x * _LIGNE] = old_z;
            }
        } else {
            if (old_z >= zBuffer[x + y * _LIGNE]) {
                Point pointOmbre;
                pointOmbre.x = x;
                pointOmbre.y = y;
                pointOmbre.z = old_z;
                matriceTransformationPointOmbre(pointOmbre, origine, lumiere, camera, coefficientZoom);
                if (zBuffer_Ombre[(int) pointOmbre.x + (int) pointOmbre.y * _LIGNE] > pointOmbre.z + 10) {
                    cVecteur.r = coefficientOmbre * cVecteur.r;
                    cVecteur.g = coefficientOmbre * cVecteur.g;
                    cVecteur.b = coefficientOmbre * cVecteur.b;
                }
                image.set(x, y, cVecteur);
                zBuffer[x + y * _LIGNE] = old_z;
            }
        }

        old_z += pasZ;

        error2 += dy2;
        if (error2 > dx) {
            y += p1.y > p0.y ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}



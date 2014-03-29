/* 
 * File:   main.cpp
 * Author: katia
 *
 * Created on 25 février 2014, 22:09
 */

#include "moteur.h"
#include "Matrix.h"

/*Test de la validite de l'objet suivant les différents types de representation*/
void testObject(Vecteur origine, Vecteur camera, Vecteur lumiere, float coefficientZoom) {
    TGAImage image0 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image1 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image2 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image3 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image4 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image6 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image7 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image8 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image9 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image10 = TGAImage(_COL, _LIGNE, TGAImage::RGB);

    string fichierNM = "african_head_nm.tga";
    string fichierTexture = "african_head_diffuse.tga";
    string fichierzBufferNormal = "zBufferCamera.tga";

    lireFichierTriangle("african_head.obj", image1, origine, camera, lumiere, coefficientZoom);
    lireFichierTriangleBuffer("african_head.obj", image0, origine, camera, lumiere, fichierzBufferNormal, coefficientZoom);
    lireFichierTriangleBufferPhong("african_head.obj", image6, origine, camera, lumiere, fichierzBufferNormal, coefficientZoom);
    lireFichierTriangleBufferPhongTexture("african_head.obj", fichierNM, fichierTexture, image7, origine, camera, lumiere, fichierzBufferNormal, coefficientZoom);
    lireFichierTexture("african_head.obj", fichierNM, fichierTexture, image10, origine, camera, lumiere, fichierzBufferNormal, coefficientZoom);
    lireFichierTriangleBufferPhongDiffuse("african_head.obj", fichierTexture, image9, origine, camera, lumiere, fichierzBufferNormal, coefficientZoom);
    lireFichierTriangleBufferPhongNormalMapping("african_head.obj", fichierNM, image8, origine, camera, lumiere, fichierzBufferNormal, coefficientZoom);
    lireFichierLigne("african_head.obj", image4, origine, camera, lumiere, coefficientZoom);
    lireFichierFilsDeFer("african_head.obj", image2, TGAColor(0, 255, 0, 255), origine, camera, coefficientZoom);
    lireFichierComplet("african_head.obj", image3, TGAColor(0, 255, 0, 255), origine, camera, coefficientZoom);

}

void testFinal(Vecteur origine, Vecteur camera, Vecteur lumiere, float coefficientZoom) {
    TGAImage image1 = TGAImage(_COL, _LIGNE, TGAImage::RGB);
    TGAImage image2 = TGAImage(_COL, _LIGNE, TGAImage::RGB);

    string fichierNM = "african_head_nm.tga";
    string fichierTexture = "african_head_diffuse.tga";
    string fichierzBufferLumiere = "zBufferLumiere.tga";
    string fichierzBufferCamera = "zBufferCamera.tga";

    Vecteur cameraInit = camera;
    camera.x = lumiere.x;
    camera.y = lumiere.y;
    camera.z = lumiere.z;
    lireFichierTexture("african_head.obj", fichierNM, fichierTexture, image1, origine, camera, lumiere, fichierzBufferLumiere, coefficientZoom);
    camera = cameraInit;
    float* zBufferOmbre = new float[_LIGNE * _COL];
    for (int i = 0; i < _LIGNE; i++) {
        for (int j = 0; j < _COL; j++) {
            float valeur = zBuffer[i + j * _LIGNE];
            zBufferOmbre[i + j * _LIGNE] = valeur;
        }
    }
    lireFichierFinal("african_head.obj", fichierNM, fichierTexture, fichierzBufferLumiere, image2, origine, camera, lumiere, zBufferOmbre, fichierzBufferCamera, coefficientZoom);

}

void testMatrix() {
    Matrix m = Matrix::identite(4);
    m.setValeur(0, 0, -1);
    m.setValeur(0, 1, 0);
    m.setValeur(0, 2, 1);
    m.setValeur(0, 3, 1);
    m.setValeur(1, 0, 1);
    m.setValeur(1, 1, -2);
    m.setValeur(1, 2, 1);
    m.setValeur(1, 3, -1);
    m.setValeur(2, 0, 1);
    m.setValeur(2, 1, 0);
    m.setValeur(2, 2, -1);
    m.setValeur(2, 3, 1);
    m.setValeur(3, 0, 1);
    m.setValeur(3, 1, 0);
    m.setValeur(3, 2, 1);
    m.setValeur(3, 3, -1);
    m.afficher("Depart");
    Matrix mI = m.inverser();
    mI.afficher("Inverse");
}

int main(int argc, char** argv) {
    Vecteur camera, lumiere, origine;
    origine.x = 0;
    origine.y = 0;
    origine.z = 0;
    camera.x = 0;
    camera.y = 0;
    camera.z = 1;
    lumiere.x = 1;
    lumiere.y = 1;
    lumiere.z = 1;
    //Si superieur a 2 probabilité de segment fault
    testObject(origine, camera, lumiere, 2);
    testFinal(origine, camera, lumiere, 2);
    return 0;
}
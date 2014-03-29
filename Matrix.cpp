/* 
 * File:   Matrix.cpp
 * Author: katia
 * 
 * Created on 11 mars 2014, 22:53
 */

#include "Matrix.h"

Matrix::Matrix(int nombreLigne, int nombreColonne) {
    this->nombreLigne = nombreLigne;
    this->nombreColonne = nombreColonne;
    this->matrix = new float[this->nombreLigne * this->nombreColonne];
    for (int i = 0; i < this->nombreLigne; i++) {
        for (int j = 0; j < this->nombreColonne; j++) {
            this->matrix[i + j * this->nombreLigne] = 1;
        };
    }
}

Matrix Matrix::identite(int carree) {
    Matrix matriceIdentite = Matrix(carree, carree);
    for (int i = 0; i < carree; i++) {
        for (int j = 0; j < carree; j++) {
            matriceIdentite.setValeur(i, j, ((i == j) ? 1 : 0));
        }
    }
    return matriceIdentite;
}

Matrix Matrix::multiplicationMatrix(Matrix matrix) {
    Matrix matrixFinale = Matrix(this->nombreLigne, matrix.getNombreColonne());
    for (int i = 0; i < this->nombreLigne; i++) {
        for (int j = 0; j < matrix.getNombreColonne(); j++) {
            matrixFinale.setValeur(i, j, 0);
            for (int k = 0; k < this->nombreColonne; k++) {
                float valeur = matrixFinale.getValeur(i, j) + this->matrix[i + k * this->nombreLigne] * matrix.getValeur(k, j);
                matrixFinale.setValeur(i, j, valeur);
            }
        }
    }
    return matrixFinale;
}

Matrix Matrix::transposer() {
    Matrix matriceTransposee = Matrix(this->nombreColonne, this->nombreLigne);
    for (int i = 0; i < this->nombreLigne; i++) {
        for (int j = 0; j < this->nombreColonne; j++) {
            matriceTransposee.setValeur(j, i, this->matrix[i + j * this->nombreLigne]);
        }
    }
    return matriceTransposee;
}

Matrix Matrix::inverser() {
    if (this->nombreLigne != 4 && this->nombreColonne != 4) {
        cerr << "La matrice n'est pas un Quaternion (4x4) !" << endl;
    }
    float matriceInverseTmp[16];
    float det;
    matriceInverseTmp[0] = this->matrix[5] * this->matrix[10] * this->matrix[15] -
            this->matrix[5] * this->matrix[11] * this->matrix[14] -
            this->matrix[9] * this->matrix[6] * this->matrix[15] +
            this->matrix[9] * this->matrix[7] * this->matrix[14] +
            this->matrix[13] * this->matrix[6] * this->matrix[11] -
            this->matrix[13] * this->matrix[7] * this->matrix[10];

    matriceInverseTmp[4] = -this->matrix[4] * this->matrix[10] * this->matrix[15] +
            this->matrix[4] * this->matrix[11] * this->matrix[14] +
            this->matrix[8] * this->matrix[6] * this->matrix[15] -
            this->matrix[8] * this->matrix[7] * this->matrix[14] -
            this->matrix[12] * this->matrix[6] * this->matrix[11] +
            this->matrix[12] * this->matrix[7] * this->matrix[10];

    matriceInverseTmp[8] = this->matrix[4] * this->matrix[9] * this->matrix[15] -
            this->matrix[4] * this->matrix[11] * this->matrix[13] -
            this->matrix[8] * this->matrix[5] * this->matrix[15] +
            this->matrix[8] * this->matrix[7] * this->matrix[13] +
            this->matrix[12] * this->matrix[5] * this->matrix[11] -
            this->matrix[12] * this->matrix[7] * this->matrix[9];

    matriceInverseTmp[12] = -this->matrix[4] * this->matrix[9] * this->matrix[14] +
            this->matrix[4] * this->matrix[10] * this->matrix[13] +
            this->matrix[8] * this->matrix[5] * this->matrix[14] -
            this->matrix[8] * this->matrix[6] * this->matrix[13] -
            this->matrix[12] * this->matrix[5] * this->matrix[10] +
            this->matrix[12] * this->matrix[6] * this->matrix[9];

    matriceInverseTmp[1] = -this->matrix[1] * this->matrix[10] * this->matrix[15] +
            this->matrix[1] * this->matrix[11] * this->matrix[14] +
            this->matrix[9] * this->matrix[2] * this->matrix[15] -
            this->matrix[9] * this->matrix[3] * this->matrix[14] -
            this->matrix[13] * this->matrix[2] * this->matrix[11] +
            this->matrix[13] * this->matrix[3] * this->matrix[10];

    matriceInverseTmp[5] = this->matrix[0] * this->matrix[10] * this->matrix[15] -
            this->matrix[0] * this->matrix[11] * this->matrix[14] -
            this->matrix[8] * this->matrix[2] * this->matrix[15] +
            this->matrix[8] * this->matrix[3] * this->matrix[14] +
            this->matrix[12] * this->matrix[2] * this->matrix[11] -
            this->matrix[12] * this->matrix[3] * this->matrix[10];

    matriceInverseTmp[9] = -this->matrix[0] * this->matrix[9] * this->matrix[15] +
            this->matrix[0] * this->matrix[11] * this->matrix[13] +
            this->matrix[8] * this->matrix[1] * this->matrix[15] -
            this->matrix[8] * this->matrix[3] * this->matrix[13] -
            this->matrix[12] * this->matrix[1] * this->matrix[11] +
            this->matrix[12] * this->matrix[3] * this->matrix[9];

    matriceInverseTmp[13] = this->matrix[0] * this->matrix[9] * this->matrix[14] -
            this->matrix[0] * this->matrix[10] * this->matrix[13] -
            this->matrix[8] * this->matrix[1] * this->matrix[14] +
            this->matrix[8] * this->matrix[2] * this->matrix[13] +
            this->matrix[12] * this->matrix[1] * this->matrix[10] -
            this->matrix[12] * this->matrix[2] * this->matrix[9];

    matriceInverseTmp[2] = this->matrix[1] * this->matrix[6] * this->matrix[15] -
            this->matrix[1] * this->matrix[7] * this->matrix[14] -
            this->matrix[5] * this->matrix[2] * this->matrix[15] +
            this->matrix[5] * this->matrix[3] * this->matrix[14] +
            this->matrix[13] * this->matrix[2] * this->matrix[7] -
            this->matrix[13] * this->matrix[3] * this->matrix[6];

    matriceInverseTmp[6] = -this->matrix[0] * this->matrix[6] * this->matrix[15] +
            this->matrix[0] * this->matrix[7] * this->matrix[14] +
            this->matrix[4] * this->matrix[2] * this->matrix[15] -
            this->matrix[4] * this->matrix[3] * this->matrix[14] -
            this->matrix[12] * this->matrix[2] * this->matrix[7] +
            this->matrix[12] * this->matrix[3] * this->matrix[6];

    matriceInverseTmp[10] = this->matrix[0] * this->matrix[5] * this->matrix[15] -
            this->matrix[0] * this->matrix[7] * this->matrix[13] -
            this->matrix[4] * this->matrix[1] * this->matrix[15] +
            this->matrix[4] * this->matrix[3] * this->matrix[13] +
            this->matrix[12] * this->matrix[1] * this->matrix[7] -
            this->matrix[12] * this->matrix[3] * this->matrix[5];

    matriceInverseTmp[14] = -this->matrix[0] * this->matrix[5] * this->matrix[14] +
            this->matrix[0] * this->matrix[6] * this->matrix[13] +
            this->matrix[4] * this->matrix[1] * this->matrix[14] -
            this->matrix[4] * this->matrix[2] * this->matrix[13] -
            this->matrix[12] * this->matrix[1] * this->matrix[6] +
            this->matrix[12] * this->matrix[2] * this->matrix[5];

    matriceInverseTmp[3] = -this->matrix[1] * this->matrix[6] * this->matrix[11] +
            this->matrix[1] * this->matrix[7] * this->matrix[10] +
            this->matrix[5] * this->matrix[2] * this->matrix[11] -
            this->matrix[5] * this->matrix[3] * this->matrix[10] -
            this->matrix[9] * this->matrix[2] * this->matrix[7] +
            this->matrix[9] * this->matrix[3] * this->matrix[6];

    matriceInverseTmp[7] = this->matrix[0] * this->matrix[6] * this->matrix[11] -
            this->matrix[0] * this->matrix[7] * this->matrix[10] -
            this->matrix[4] * this->matrix[2] * this->matrix[11] +
            this->matrix[4] * this->matrix[3] * this->matrix[10] +
            this->matrix[8] * this->matrix[2] * this->matrix[7] -
            this->matrix[8] * this->matrix[3] * this->matrix[6];

    matriceInverseTmp[11] = -this->matrix[0] * this->matrix[5] * this->matrix[11] +
            this->matrix[0] * this->matrix[7] * this->matrix[9] +
            this->matrix[4] * this->matrix[1] * this->matrix[11] -
            this->matrix[4] * this->matrix[3] * this->matrix[9] -
            this->matrix[8] * this->matrix[1] * this->matrix[7] +
            this->matrix[8] * this->matrix[3] * this->matrix[5];

    matriceInverseTmp[15] = this->matrix[0] * this->matrix[5] * this->matrix[10] -
            this->matrix[0] * this->matrix[6] * this->matrix[9] -
            this->matrix[4] * this->matrix[1] * this->matrix[10] +
            this->matrix[4] * this->matrix[2] * this->matrix[9] +
            this->matrix[8] * this->matrix[1] * this->matrix[6] -
            this->matrix[8] * this->matrix[2] * this->matrix[5];

    det = this->matrix[0] * matriceInverseTmp[0] + this->matrix[1] * matriceInverseTmp[4] + this->matrix[2] * matriceInverseTmp[8] + this->matrix[3] * matriceInverseTmp[12];
    if (det == 0) {
        cerr << "det = 0, matrice non inversible !" << endl;
    }
    det = 1.0 / det;

    float matriceInverseInit[16];
    for (int i = 0; i < 16; i++) {
        matriceInverseInit[i] = matriceInverseTmp[i] * det;
    }
    Matrix matriceInverse = Matrix(4, 4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriceInverse.setValeur(i, j, matriceInverseInit[i + j * 4]);
        }
    }
    return matriceInverse;
}

void Matrix::translation(Matrix &matriceTranslatee, Vecteur vecteur) {
    Matrix matriceTranslation = identite(4);
    matriceTranslation.setValeur(3, 0, vecteur.x);
    matriceTranslation.setValeur(3, 1, vecteur.y);
    matriceTranslation.setValeur(3, 2, vecteur.z);
    matriceTranslatee = multiplicationMatrix(matriceTranslation);
}

void Matrix::rotationX(Matrix &matriceRotation, float cos, float sin) {
    Matrix matrice_De_Rotation = identite(4);
    matrice_De_Rotation.setValeur(1, 1, cos);
    matrice_De_Rotation.setValeur(1, 2, sin);
    matrice_De_Rotation.setValeur(2, 1, -sin);
    matrice_De_Rotation.setValeur(2, 2, cos);
    matriceRotation = multiplicationMatrix(matrice_De_Rotation);
}

void Matrix::rotationY(Matrix &matriceRotation, float cos, float sin) {
    Matrix matrice_De_Rotation = identite(4);
    matrice_De_Rotation.setValeur(0, 0, cos);
    matrice_De_Rotation.setValeur(0, 2, -sin);
    matrice_De_Rotation.setValeur(2, 0, sin);
    matrice_De_Rotation.setValeur(2, 2, cos);
    matriceRotation = multiplicationMatrix(matrice_De_Rotation);
}

void Matrix::rotationZ(Matrix &matriceRotation, float cos, float sin) {
    Matrix matrice_De_Rotation = identite(4);
    matrice_De_Rotation.setValeur(0, 0, cos);
    matrice_De_Rotation.setValeur(0, 1, sin);
    matrice_De_Rotation.setValeur(1, 0, -sin);
    matrice_De_Rotation.setValeur(1, 1, cos);
    matriceRotation = multiplicationMatrix(matrice_De_Rotation);
}

void Matrix::projectionZ(Matrix &matriceProjetee, float zC) {
    Matrix matriceProjection = identite(4);
    matriceProjection.setValeur(3, 2, -1 / zC);
    matriceProjetee = multiplicationMatrix(matriceProjection);
}

Matrix transformation(Vecteur origine, Vecteur camera) {
    Matrix matriceTransformation = Matrix::identite(4);
    if (camera.z < 0) {
        matriceTransformation.rotationZ(matriceTransformation, -1, 0);
    }
    float normeY = sqrt(pow(camera.x - origine.x, 2) + pow(camera.y - origine.y, 2) + pow(camera.z - origine.z, 2));
    matriceTransformation.rotationY(matriceTransformation, sqrt(1. - pow(camera.x - origine.x, 2) / pow(normeY, 2)), (camera.x - origine.x) / normeY);

    float normeX = sqrt(pow(camera.y - origine.y, 2) + pow(camera.z - origine.z, 2));
    matriceTransformation.rotationX(matriceTransformation, (camera.z - origine.z) / normeX, -(camera.y - origine.y) / normeX);

    matriceTransformation.projectionZ(matriceTransformation, 16);
    return matriceTransformation;
}

void Matrix::afficher(string texte) {
    cout << "\nMatrice : " + texte << endl;
    for (int i = 0; i < this->nombreLigne; i++) {
        for (int j = 0; j < this->nombreColonne; j++) {
            cout << " | " << this->matrix[i + j * this->nombreLigne];
        }
        cout << " |" << endl;
    }
}

float Matrix::getValeur(int ligne, int colonne) {
    return this->matrix[ligne + colonne * this->nombreLigne];
}

float Matrix::setValeur(int ligne, int colonne, float valeur) {
    this->matrix[ligne + colonne * this->nombreLigne] = valeur;
}

int Matrix::getNombreColonne() const {
    return nombreColonne;
}

int Matrix::getNombreLigne() const {
    return nombreLigne;
}

Matrix getMatrixHomogenePoint(Point point) {
    Matrix matrixHomogene = Matrix(4, 1);
    matrixHomogene.setValeur(0, 0, point.x);
    matrixHomogene.setValeur(1, 0, point.y);
    matrixHomogene.setValeur(2, 0, point.z);
    matrixHomogene.setValeur(3, 0, 1);
    return matrixHomogene;
}

Matrix getMatrixHomogeneVecteur(Vecteur vecteur) {
    Matrix matrixHomogene = Matrix(4, 1);
    matrixHomogene.setValeur(0, 0, vecteur.x);
    matrixHomogene.setValeur(1, 0, vecteur.y);
    matrixHomogene.setValeur(2, 0, vecteur.z);
    matrixHomogene.setValeur(3, 0, 0);
    return matrixHomogene;
}

void matriceTransformationPoints(Point &p0, Point &p1, Point &p2, Vecteur origineRepere, Vecteur camera, float coefficientZoom) {
    Matrix matriceTransformee0 = transformation(origineRepere, camera);
    matriceTransformee0 = matriceTransformee0.multiplicationMatrix(getMatrixHomogenePoint(p0));
    p0.x = matriceTransformee0.getValeur(0, 0)*coefficientZoom + _COL / 2;
    p0.y = matriceTransformee0.getValeur(1, 0)*coefficientZoom + _LIGNE / 2;
    p0.z = matriceTransformee0.getValeur(2, 0);

    Matrix matriceTransformee1 = transformation(origineRepere, camera);
    matriceTransformee1 = matriceTransformee1.multiplicationMatrix(getMatrixHomogenePoint(p1));
    p1.x = matriceTransformee1.getValeur(0, 0)*coefficientZoom + _COL / 2;
    p1.y = matriceTransformee1.getValeur(1, 0)*coefficientZoom + _LIGNE / 2;
    p1.z = matriceTransformee1.getValeur(2, 0);

    Matrix matriceTransformee2 = transformation(origineRepere, camera);
    matriceTransformee2 = matriceTransformee2.multiplicationMatrix(getMatrixHomogenePoint(p2));
    p2.x = matriceTransformee2.getValeur(0, 0)*coefficientZoom + _COL / 2;
    p2.y = matriceTransformee2.getValeur(1, 0)*coefficientZoom + _LIGNE / 2;
    p2.z = matriceTransformee2.getValeur(2, 0);
}

void matriceTransformationPointOmbre(Point &p0, Vecteur origineRepere, Vecteur lumiere, Vecteur camera, float coefficientZoom) {
    p0.x = (p0.x - _COL / 2) / coefficientZoom;
    p0.y = (p0.y - _COL / 2) / coefficientZoom;
    Matrix matriceTemp = transformation(origineRepere, camera).inverser();
    Matrix matriceTransformee0 = transformation(origineRepere, lumiere);
    matriceTransformee0 = matriceTransformee0.multiplicationMatrix(matriceTemp);
    matriceTransformee0 = matriceTransformee0.multiplicationMatrix(getMatrixHomogenePoint(p0));
    p0.x = matriceTransformee0.getValeur(0, 0)*coefficientZoom + _COL / 2;
    p0.y = matriceTransformee0.getValeur(1, 0)*coefficientZoom + _LIGNE / 2;
    p0.z = matriceTransformee0.getValeur(2, 0);
}

void matriceTransformationVecteurs(Vecteur &v0, Vecteur &v1, Vecteur &v2, Vecteur origineRepere, Vecteur camera) {
    Matrix matriceTransformee0 = transformation(origineRepere, camera);
    matriceTransformee0 = matriceTransformee0.inverser();
    matriceTransformee0 = matriceTransformee0.multiplicationMatrix(getMatrixHomogeneVecteur(v0));
    v0.x = matriceTransformee0.getValeur(0, 0);
    v0.y = matriceTransformee0.getValeur(1, 0);
    v0.z = matriceTransformee0.getValeur(2, 0);

    Matrix matriceTransformee1 = transformation(origineRepere, camera);
    matriceTransformee1 = matriceTransformee1.inverser();
    matriceTransformee1 = matriceTransformee1.multiplicationMatrix(getMatrixHomogeneVecteur(v1));
    v1.x = matriceTransformee1.getValeur(0, 0);
    v1.y = matriceTransformee1.getValeur(1, 0);
    v1.z = matriceTransformee1.getValeur(2, 0);

    Matrix matriceTransformee2 = transformation(origineRepere, camera);
    matriceTransformee2 = matriceTransformee2.inverser();
    matriceTransformee2 = matriceTransformee2.multiplicationMatrix(getMatrixHomogeneVecteur(v2));
    v2.x = matriceTransformee2.getValeur(0, 0);
    v2.y = matriceTransformee2.getValeur(1, 0);
    v2.z = matriceTransformee2.getValeur(2, 0);
}

void matriceTransformationVecteur(Vecteur &v0, Vecteur origineRepere, Vecteur camera) {
    Matrix matriceTransformee0 = transformation(origineRepere, camera);
    matriceTransformee0 = matriceTransformee0.inverser();
    matriceTransformee0 = matriceTransformee0.multiplicationMatrix(getMatrixHomogeneVecteur(v0));
    v0.x = matriceTransformee0.getValeur(0, 0);
    v0.y = matriceTransformee0.getValeur(1, 0);
    v0.z = matriceTransformee0.getValeur(2, 0);
}


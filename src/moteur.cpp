#include "../headers/moteur.h"
#include "../headers/Matrix.h"

void lireFichierFilsDeFer(string texte, TGAImage &image, TGAColor c, Vecteur origine, Vecteur camera, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);
    if (fichier) {
        string ligne;
        vector<Point> listePoints;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;
            while (ss >> buffer) {
                tokens.push_back(buffer);
            }
            if (!tokens.size()) continue;
            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];

                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                line(sommet1, sommet2, image, c);
                line(sommet2, sommet3, image, c);
                line(sommet1, sommet3, image, c);
            }

        }
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/fil_de_fer.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierComplet(string texte, TGAImage &image, TGAColor c, Vecteur origine, Vecteur camera, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);
    if (fichier) {
        string ligne;
        vector<Point> listePoints;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;
            while (ss >> buffer) {
                tokens.push_back(buffer);
            }
            if (!tokens.size()) continue;
            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];

                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                triangle(sommet1, sommet2, sommet3, image, c);
            }

        }
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/complet.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierLigne(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);
    if (fichier) {
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);


                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);

                int luminosite1, luminosite2, luminosite3;

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);

                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                luminosite1 = produitScalaire(vecteur1, lumiere)*255;
                luminosite2 = produitScalaire(vecteur2, lumiere)*255;
                luminosite3 = produitScalaire(vecteur3, lumiere)*255;
                if (luminosite1 > 255 || luminosite2 > 255 || luminosite3 > 255) {
                    cerr << "supp a 255" << endl;
                }
                if (luminosite1 < 0) {
                    luminosite1 = 0;
                }
                if (luminosite2 < 0) {
                    luminosite2 = 0;
                }
                if (luminosite3 < 0) {
                    luminosite3 = 0;
                }

                lineDegrade(sommet1, sommet2, image, TGAColor(0, luminosite1, 0, 255), TGAColor(0, luminosite2, 0, 255));
                lineDegrade(sommet2, sommet3, image, TGAColor(0, luminosite2, 0, 255), TGAColor(0, luminosite3, 0, 255));
                lineDegrade(sommet1, sommet3, image, TGAColor(0, luminosite1, 0, 255), TGAColor(0, luminosite3, 0, 255));

            }

        }
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/topLigne.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierTriangle(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);
    if (fichier) {
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);


                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);

                int luminosite1, luminosite2, luminosite3;

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);
                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                if (produitScalaire(camera, produitV) >= 0) {
                    luminosite1 = produitScalaire(vecteur1, lumiere)*255;
                    luminosite2 = produitScalaire(vecteur2, lumiere)*255;
                    luminosite3 = produitScalaire(vecteur3, lumiere)*255;
                    if (luminosite1 > 255 || luminosite2 > 255 || luminosite3 > 255) {
                        cerr << "supp a 255" << endl;
                    }
                    if (luminosite1 < 0) {
                        luminosite1 = 0;
                    }
                    if (luminosite2 < 0) {
                        luminosite2 = 0;
                    }
                    if (luminosite3 < 0) {
                        luminosite3 = 0;
                    }
                    triangleDegrade(sommet1, sommet2, sommet3, image, TGAColor(0, luminosite1, 0, 255), TGAColor(0, luminosite2, 0, 255), TGAColor(0, luminosite3, 0, 255));
                }
            }

        }
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/topTriangle.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierTriangleBuffer(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);
    if (fichier) {
        zBufferInit();
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);


                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);

                int luminosite1, luminosite2, luminosite3;

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);
                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                if (produitScalaire(camera, produitV) >= 0) {
                    luminosite1 = produitScalaire(vecteur1, lumiere)*255;
                    luminosite2 = produitScalaire(vecteur2, lumiere)*255;
                    luminosite3 = produitScalaire(vecteur3, lumiere)*255;
                    if (luminosite1 > 255 || luminosite2 > 255 || luminosite3 > 255) {
                        cerr << "supp a 255" << endl;
                    }
                    if (luminosite1 < 0) {
                        luminosite1 = 0;
                    }
                    if (luminosite2 < 0) {
                        luminosite2 = 0;
                    }
                    if (luminosite3 < 0) {
                        luminosite3 = 0;
                    }
                    triangleDegradeBuffer(sommet1, sommet2, sommet3, image, TGAColor(0, luminosite1, 0, 255), TGAColor(0, luminosite2, 0, 255), TGAColor(0, luminosite3, 0, 255));
                }
            }

        }
        zBufferImage(nomBuffer.c_str());
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/zGouraud.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierTriangleBufferPhong(string texte, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);
    if (fichier) {
        zBufferInit();
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);


                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);

                int luminosite1, luminosite2, luminosite3;

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);
                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                if (produitScalaire(camera, produitV) >= 0) {
                    luminosite1 = produitScalaire(vecteur1, lumiere)*255;
                    luminosite2 = produitScalaire(vecteur2, lumiere)*255;
                    luminosite3 = produitScalaire(vecteur3, lumiere)*255;
                    if (luminosite1 > 255 || luminosite2 > 255 || luminosite3 > 255) {
                        cerr << "supp a 255" << endl;
                    }
                    if (luminosite1 < 0) {
                        luminosite1 = 0;
                    }
                    if (luminosite2 < 0) {
                        luminosite2 = 0;
                    }
                    if (luminosite3 < 0) {
                        luminosite3 = 0;
                    }
                    triangleDegradeBufferPhong(sommet1, sommet2, sommet3, vecteur1, vecteur2, vecteur3, lumiere, image);
                }
            }

        }
        zBufferImage(nomBuffer.c_str());
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/zPhong.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierTriangleBufferPhongNormalMapping(string texte, string imageNormalMapping, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);

    TGAImage image_NormalMapping = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);

    image_NormalMapping.read_tga_file(imageNormalMapping.c_str());
    image_NormalMapping.flip_vertically();

    if (fichier) {
        zBufferInit();
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        vector<Vecteur> listeVecteursTextures;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "vt") == 0) {
                Vecteur vecteurTexture;
                vecteurTexture.x = strtof(tokens[1].c_str(), NULL);
                vecteurTexture.y = strtof(tokens[2].c_str(), NULL);
                vecteurTexture.z = strtof(tokens[3].c_str(), NULL);
                listeVecteursTextures.push_back(vecteurTexture);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string delimiter = "/";
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);
                int position1 = 1;
                size_t index1 = 0;
                string token1;
                while ((index1 = point1.find(delimiter)) != std::string::npos && position1 < 3) {
                    token1 = point1.substr(0, index1);
                    point1.erase(0, index1 + delimiter.length());
                    position1++;
                }
                Vecteur vecteurTexture1 = listeVecteursTextures[strtof(token1.c_str(), NULL) - 1];

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);
                int position2 = 1;
                size_t index2 = 0;
                string token2;
                while ((index2 = point2.find(delimiter)) != std::string::npos && position2 < 3) {
                    token2 = point2.substr(0, index2);
                    point2.erase(0, index2 + delimiter.length());
                    position2++;
                }
                Vecteur vecteurTexture2 = listeVecteursTextures[strtof(token2.c_str(), NULL) - 1];

                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);
                int position3 = 1;
                size_t index3 = 0;
                string token3;
                while ((index3 = point3.find(delimiter)) != std::string::npos && position3 < 3) {
                    token3 = point3.substr(0, index3);
                    point3.erase(0, index3 + delimiter.length());
                    position3++;
                }
                Vecteur vecteurTexture3 = listeVecteursTextures[strtof(token3.c_str(), NULL) - 1];

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);
                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                if (produitScalaire(camera, produitV) >= 0) {
                    triangleDegradeBufferPhongNormalMapping(sommet1, sommet2, sommet3, vecteur1, vecteur2, vecteur3, vecteurTexture1, vecteurTexture2, vecteurTexture3, camera, lumiere, image, image_NormalMapping);
                }
            }

        }
        zBufferImage(nomBuffer.c_str());
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/zPNM.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierTriangleBufferPhongDiffuse(string texte, string imageDiffuse, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);

    TGAImage image_Diffuse = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);

    image_Diffuse.read_tga_file(imageDiffuse.c_str());
    image_Diffuse.flip_vertically();

    if (fichier) {
        zBufferInit();
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        vector<Vecteur> listeVecteursTextures;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "vt") == 0) {
                Vecteur vecteurTexture;
                vecteurTexture.x = strtof(tokens[1].c_str(), NULL);
                vecteurTexture.y = strtof(tokens[2].c_str(), NULL);
                vecteurTexture.z = strtof(tokens[3].c_str(), NULL);
                listeVecteursTextures.push_back(vecteurTexture);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string delimiter = "/";
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);
                int position1 = 1;
                size_t index1 = 0;
                string token1;
                while ((index1 = point1.find(delimiter)) != std::string::npos && position1 < 3) {
                    token1 = point1.substr(0, index1);
                    point1.erase(0, index1 + delimiter.length());
                    position1++;
                }
                Vecteur vecteurTexture1 = listeVecteursTextures[strtof(token1.c_str(), NULL) - 1];

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);
                int position2 = 1;
                size_t index2 = 0;
                string token2;
                while ((index2 = point2.find(delimiter)) != std::string::npos && position2 < 3) {
                    token2 = point2.substr(0, index2);
                    point2.erase(0, index2 + delimiter.length());
                    position2++;
                }
                Vecteur vecteurTexture2 = listeVecteursTextures[strtof(token2.c_str(), NULL) - 1];

                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);
                int position3 = 1;
                size_t index3 = 0;
                string token3;
                while ((index3 = point3.find(delimiter)) != std::string::npos && position3 < 3) {
                    token3 = point3.substr(0, index3);
                    point3.erase(0, index3 + delimiter.length());
                    position3++;
                }
                Vecteur vecteurTexture3 = listeVecteursTextures[strtof(token3.c_str(), NULL) - 1];

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);
                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                if (produitScalaire(camera, produitV) >= 0) {
                    triangleDegradeBufferPhongDiffuse(sommet1, sommet2, sommet3, vecteur1, vecteur2, vecteur3, vecteurTexture1, vecteurTexture2, vecteurTexture3, camera, lumiere, image, image_Diffuse);
                }
            }

        }
        zBufferImage(nomBuffer.c_str());
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/zPTDiff.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierTriangleBufferPhongTexture(string texte, string imageNormalMapping, string imageDiffuse, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);

    TGAImage image_NormalMapping = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);
    TGAImage image_Diffuse = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);

    image_NormalMapping.read_tga_file(imageNormalMapping.c_str());
    image_NormalMapping.flip_vertically();
    image_Diffuse.read_tga_file(imageDiffuse.c_str());
    image_Diffuse.flip_vertically();

    if (fichier) {
        zBufferInit();
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        vector<Vecteur> listeVecteursTextures;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "vt") == 0) {
                Vecteur vecteurTexture;
                vecteurTexture.x = strtof(tokens[1].c_str(), NULL);
                vecteurTexture.y = strtof(tokens[2].c_str(), NULL);
                vecteurTexture.z = strtof(tokens[3].c_str(), NULL);
                listeVecteursTextures.push_back(vecteurTexture);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string delimiter = "/";
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);
                int position1 = 1;
                size_t index1 = 0;
                string token1;
                while ((index1 = point1.find(delimiter)) != std::string::npos && position1 < 3) {
                    token1 = point1.substr(0, index1);
                    point1.erase(0, index1 + delimiter.length());
                    position1++;
                }
                Vecteur vecteurTexture1 = listeVecteursTextures[strtof(token1.c_str(), NULL) - 1];

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);
                int position2 = 1;
                size_t index2 = 0;
                string token2;
                while ((index2 = point2.find(delimiter)) != std::string::npos && position2 < 3) {
                    token2 = point2.substr(0, index2);
                    point2.erase(0, index2 + delimiter.length());
                    position2++;
                }
                Vecteur vecteurTexture2 = listeVecteursTextures[strtof(token2.c_str(), NULL) - 1];

                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);
                int position3 = 1;
                size_t index3 = 0;
                string token3;
                while ((index3 = point3.find(delimiter)) != std::string::npos && position3 < 3) {
                    token3 = point3.substr(0, index3);
                    point3.erase(0, index3 + delimiter.length());
                    position3++;
                }
                Vecteur vecteurTexture3 = listeVecteursTextures[strtof(token3.c_str(), NULL) - 1];

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);

                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);

                if (produitScalaire(camera, produitV) >= 0) {
                    triangleDegradeBufferPhongTexture(sommet1, sommet2, sommet3, vecteur1, vecteur2, vecteur3, vecteurTexture1, vecteurTexture2, vecteurTexture3, camera, lumiere, image, image_NormalMapping, image_Diffuse);
                }
            }

        }
        zBufferImage(nomBuffer.c_str());
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/zPTex.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierTexture(string texte, string imageNormalMapping, string imageDiffuse, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, string nomBuffer, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);

    TGAImage image_NormalMapping = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);
    TGAImage image_Diffuse = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);

    image_NormalMapping.read_tga_file(imageNormalMapping.c_str());
    image_NormalMapping.flip_vertically();
    image_Diffuse.read_tga_file(imageDiffuse.c_str());
    image_Diffuse.flip_vertically();

    if (fichier) {
        zBufferInit();
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        vector<Vecteur> listeVecteursTextures;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "vt") == 0) {
                Vecteur vecteurTexture;
                vecteurTexture.x = strtof(tokens[1].c_str(), NULL);
                vecteurTexture.y = strtof(tokens[2].c_str(), NULL);
                vecteurTexture.z = strtof(tokens[3].c_str(), NULL);
                listeVecteursTextures.push_back(vecteurTexture);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string delimiter = "/";
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);
                int position1 = 1;
                size_t index1 = 0;
                string token1;
                while ((index1 = point1.find(delimiter)) != std::string::npos && position1 < 3) {
                    token1 = point1.substr(0, index1);
                    point1.erase(0, index1 + delimiter.length());
                    position1++;
                }
                Vecteur vecteurTexture1 = listeVecteursTextures[strtof(token1.c_str(), NULL) - 1];

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);
                int position2 = 1;
                size_t index2 = 0;
                string token2;
                while ((index2 = point2.find(delimiter)) != std::string::npos && position2 < 3) {
                    token2 = point2.substr(0, index2);
                    point2.erase(0, index2 + delimiter.length());
                    position2++;
                }
                Vecteur vecteurTexture2 = listeVecteursTextures[strtof(token2.c_str(), NULL) - 1];

                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);
                int position3 = 1;
                size_t index3 = 0;
                string token3;
                while ((index3 = point3.find(delimiter)) != std::string::npos && position3 < 3) {
                    token3 = point3.substr(0, index3);
                    point3.erase(0, index3 + delimiter.length());
                    position3++;
                }
                Vecteur vecteurTexture3 = listeVecteursTextures[strtof(token3.c_str(), NULL) - 1];

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);

                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);
                //matriceTransformationVecteur(lumiere, origine, camera);
                if (produitScalaire(camera, produitV) >= 0) {
                    triangleDegradeBufferPhongTexture(sommet1, sommet2, sommet3, vecteur1, vecteur2, vecteur3, vecteurTexture1, vecteurTexture2, vecteurTexture3, camera, lumiere, image, image_NormalMapping, image_Diffuse);
                }
            }

        }
        zBufferImage(nomBuffer.c_str());
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/zzRendu_Lum.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}

void lireFichierFinal(string texte, string imageNormalMapping, string imageDiffuse, string imageOmbre, TGAImage &image, Vecteur origine, Vecteur camera, Vecteur lumiere, float* zBuffer_Ombre, string nomBuffer, float coefficientZoom) {
    ifstream fichier(texte.c_str(), ios::in);

    TGAImage image_NormalMapping = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);
    TGAImage image_Diffuse = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);
    TGAImage image_Ombre = TGAImage(_TGA_WIDTH, _TGA_HEIGHT, TGAImage::RGB);

    image_NormalMapping.read_tga_file(imageNormalMapping.c_str());
    image_NormalMapping.flip_vertically();
    image_Diffuse.read_tga_file(imageDiffuse.c_str());
    image_Diffuse.flip_vertically();
    image_Ombre.read_tga_file(imageOmbre.c_str());
    image_Ombre.flip_vertically();

    if (fichier) {
        zBufferInit();
        string ligne;
        vector<Point> listePoints;
        vector<Vecteur> listeVecteurs;
        vector<Vecteur> listeVecteursTextures;
        while (getline(fichier, ligne)) {
            string str(ligne);
            string buffer;
            stringstream ss(str);
            vector<string> tokens;

            while (ss >> buffer) {
                tokens.push_back(buffer);
            }

            if (!tokens.size()) {
                continue;
            }

            if (strcmp(tokens[0].c_str(), "v") == 0) {
                Point point;
                point.x = strtof(tokens[1].c_str(), NULL);
                point.y = strtof(tokens[2].c_str(), NULL);
                point.z = strtof(tokens[3].c_str(), NULL);
                listePoints.push_back(point);
            }
            if (strcmp(tokens[0].c_str(), "vn") == 0) {
                Vecteur vecteurNormal;
                vecteurNormal.x = strtof(tokens[1].c_str(), NULL);
                vecteurNormal.y = strtof(tokens[2].c_str(), NULL);
                vecteurNormal.z = strtof(tokens[3].c_str(), NULL);
                listeVecteurs.push_back(vecteurNormal);
            }
            if (strcmp(tokens[0].c_str(), "vt") == 0) {
                Vecteur vecteurTexture;
                vecteurTexture.x = strtof(tokens[1].c_str(), NULL);
                vecteurTexture.y = strtof(tokens[2].c_str(), NULL);
                vecteurTexture.z = strtof(tokens[3].c_str(), NULL);
                listeVecteursTextures.push_back(vecteurTexture);
            }
            if (strcmp(tokens[0].c_str(), "f") == 0) {
                string delimiter = "/";
                string point1 = tokens[1].c_str();
                string mot1;
                istringstream isstring1(point1);
                getline(isstring1, mot1, '/');
                Point sommet1 = listePoints[strtof(mot1.c_str(), NULL) - 1];
                Vecteur vecteur1 = normaliser(listeVecteurs[strtof(mot1.c_str(), NULL) - 1]);
                int position1 = 1;
                size_t index1 = 0;
                string token1;
                while ((index1 = point1.find(delimiter)) != std::string::npos && position1 < 3) {
                    token1 = point1.substr(0, index1);
                    point1.erase(0, index1 + delimiter.length());
                    position1++;
                }
                Vecteur vecteurTexture1 = listeVecteursTextures[strtof(token1.c_str(), NULL) - 1];

                string point2 = tokens[2].c_str();
                string mot2;
                istringstream isstring2(point2);
                getline(isstring2, mot2, '/');
                Point sommet2 = listePoints[strtof(mot2.c_str(), NULL) - 1];
                Vecteur vecteur2 = normaliser(listeVecteurs[strtof(mot2.c_str(), NULL) - 1]);
                int position2 = 1;
                size_t index2 = 0;
                string token2;
                while ((index2 = point2.find(delimiter)) != std::string::npos && position2 < 3) {
                    token2 = point2.substr(0, index2);
                    point2.erase(0, index2 + delimiter.length());
                    position2++;
                }
                Vecteur vecteurTexture2 = listeVecteursTextures[strtof(token2.c_str(), NULL) - 1];

                string point3 = tokens[3].c_str();
                string mot3;
                istringstream isstring3(point3);
                getline(isstring3, mot3, '/');
                Point sommet3 = listePoints[strtof(mot3.c_str(), NULL) - 1];
                Vecteur vecteur3 = normaliser(listeVecteurs[strtof(mot3.c_str(), NULL) - 1]);
                int position3 = 1;
                size_t index3 = 0;
                string token3;
                while ((index3 = point3.find(delimiter)) != std::string::npos && position3 < 3) {
                    token3 = point3.substr(0, index3);
                    point3.erase(0, index3 + delimiter.length());
                    position3++;
                }
                Vecteur vecteurTexture3 = listeVecteursTextures[strtof(token3.c_str(), NULL) - 1];

                camera = normaliser(camera);
                lumiere = normaliser(lumiere);

                Vecteur produitV = produitVectoriel(sommet1, sommet2, sommet3);
                produitV = normaliser(produitV);

                matriceTransformationPoints(sommet1, sommet2, sommet3, origine, camera, coefficientZoom);
                //matriceTransformationVecteur(lumiere, origine, camera);
                if (produitScalaire(camera, produitV) >= 0) {
                    triangleFinal(sommet1, sommet2, sommet3, vecteur1, vecteur2, vecteur3, vecteurTexture1, vecteurTexture2, vecteurTexture3, origine, camera, lumiere, image, image_NormalMapping, image_Diffuse, image_Ombre, zBuffer_Ombre, coefficientZoom);
                }
            }

        }
        zBufferImage(nomBuffer.c_str());
        image.flip_vertically();
        char buffer[32];
        snprintf(buffer, sizeof (buffer), "tga_files/rendu/zzRendu_Fin.tga");
        image.write_tga_file(buffer);
        fichier.close();
    } else {

        cout << "Impossible d'ouvrir le fichier !\n";
    }
}



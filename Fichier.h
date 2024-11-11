#ifndef FICHIER_H
#define FICHIER_H

#include "Ressource.h"
#include <string>

class Fichier : public Ressource {
private:
    int taille;
    std::string nom;
    std::string cheminAcces;

public:
    Fichier(int id, std::string titre, std::string auteur, bool estLibre, int taille,  std::string& nom, std::string& cheminAcces);
    Fichier(int id, std::string titre, std::string auteur, bool estLibre, int taille,  std::string& nom, std::string& cheminAcces, std::string dateEmprunt, std::string dateRetour, std::string emprunteur);

    std::string getType();

    void afficherInfos();
    void toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator);
};

#endif // FICHIER_H

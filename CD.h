#ifndef CD_H
#define CD_H

#include "DVD.h"
#include <string>

class CD : public DVD {

public:
    CD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes);
    CD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes , std::string dateEmprunt, std::string dateRetour, std::string emprunteur);

    std::string getType();

    void afficherInfos();
    void toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator);
};

#endif // CD_H
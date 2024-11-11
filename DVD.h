#ifndef DVD_H
#define DVD_H

#include "VHS.h"
#include <string>

class DVD : public VHS {
protected:
    int nbPistes;

public:
    DVD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes);
    DVD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes, std::string dateEmprunt, std::string dateRetour, std::string );
    
    std::string getType();
    void afficherInfos();
    void toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator);
};

#endif // DVD_H
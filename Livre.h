#ifndef LIVRE_H
#define LIVRE_H

#include "Ressource.h"
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class Livre : public Ressource {
protected:
    int annee;
    int nombreDePages;
    std::string collection;
    std::string resume;

public:
    Livre(int id, std::string titre, std::string auteur, bool estLibre, int annee, int nombreDePages, std::string collection, std::string resume);
    Livre(int id, std::string titre, std::string auteur, bool estLibre, int annee, int nombreDePages, std::string collection, std::string resume, std::string dateEmprunt, std::string dateRetour, std::string emprunteur);
    Livre();

    int getNombreDePages();
    int getAnnee();
    std::string getCollection();
    std::string getResume();

    void setNombreDePages(int nombreDePages);
    void setAnnee(int annee);
    void setCollection(std::string collection);
    void setResume(std::string resume);

    std::string getType();
    void afficherInfos();
    void toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator);
};

#endif // LIVRE_H
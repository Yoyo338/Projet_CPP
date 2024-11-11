#ifndef REVUE_H
#define REVUE_H

#include "Livre.h"
#include <string>
#include <vector>

class Revue : public Livre {
private:
    std::string editeur;
    int nbArticles;
    std::vector<std::string> listeNomsArticles;

public:
    Revue(int id, std::string titre, std::string auteur,bool estLibre, int annee,int nombreDePages, std::string collection, std::string resume, std::string editeur, int nbArticles, std::vector<std::string> listeNomsArticles);
    Revue(int id, std::string titre, std::string auteur,bool estLibre, int annee,int nombreDePages, std::string collection, std::string resume, std::string editeur, int nbArticles, std::vector<std::string> listeNomsArticles, std::string dateEmprunt, std::string dateRetour, std::string emprunteur);
    Revue();

    

    // Getters
    std::string getEditeur();
    int getNbArticles();
    std::vector<std::string> getListeNomsArticles();

    // Setters
    void setEditeur(std::string& editeur);
    void setNbArticles(int nbArticles);
    void setListeNomsArticles(std::vector<std::string>& listeNomsArticles);
    
    void toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator);
    std::string getType();
    void afficherInfos();
};

#endif // REVUE_H
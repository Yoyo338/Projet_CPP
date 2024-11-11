#include "CD.h"
#include <iostream>

CD::CD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes)
    : DVD(id, titre, auteur, estLibre, duree, maisonProduction,nbPistes) {}

CD::CD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes, std::string dateEmprunt, std::string dateRetour, std::string emprunteur)
    : DVD(id, titre, auteur, estLibre, duree, maisonProduction,nbPistes, dateEmprunt, dateRetour, emprunteur) {}

std::string CD::getType() {
    return "CD";
}

void CD::afficherInfos(){
    DVD::afficherInfos();
}

void CD::toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator) {
    // Initialiser l'objet JSON si ce n'est pas déjà fait
    obj.SetObject();

    // Ajout des attributs du livre
    obj.AddMember("id", id, allocator);
    obj.AddMember("titre", rapidjson::Value(titre.c_str(), allocator), allocator);
    obj.AddMember("auteur", rapidjson::Value(auteur.c_str(), allocator), allocator);
    obj.AddMember("estLibre", estLibre, allocator);
    obj.AddMember("duree", duree, allocator);
    obj.AddMember("maisonProduction", rapidjson::Value(maisonProduction.c_str(), allocator), allocator);
    obj.AddMember("nbPistes", nbPistes, allocator);

    // Ajout des champs optionnels : dateEmprunt, dateRetour, emprunteur
    if (!dateEmprunt.empty()) {
        obj.AddMember("dateEmprunt", rapidjson::Value(dateEmprunt.c_str(), allocator), allocator);
    } else {
        obj.AddMember("dateEmprunt", rapidjson::Value().SetNull(), allocator);
    }

    if (!dateRetour.empty()) {
        obj.AddMember("dateRetour", rapidjson::Value(dateRetour.c_str(), allocator), allocator);
    } else {
        obj.AddMember("dateRetour", rapidjson::Value().SetNull(), allocator);
    }

    if (!emprunteur.empty()) {
        obj.AddMember("emprunteur", rapidjson::Value(emprunteur.c_str(), allocator), allocator);
    } else {
        obj.AddMember("emprunteur", rapidjson::Value().SetNull(), allocator);
    }
}
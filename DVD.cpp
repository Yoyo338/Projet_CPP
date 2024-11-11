#include "DVD.h"
#include <iostream>

DVD::DVD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes) : VHS(id, titre, auteur, estLibre, duree, maisonProduction) {
    this->nbPistes = nbPistes;  
}
DVD::DVD(int id, std::string titre, std::string auteur, bool estLibre, int duree, std::string maisonProduction, int nbPistes, std::string dateEmprunt, std::string dateRetour, std::string emprunteur) : VHS(id, titre, auteur, estLibre, duree, maisonProduction, dateEmprunt, dateRetour, emprunteur) {
    this->nbPistes = nbPistes;  
}

std::string DVD::getType() {
    return "DVD";
}

void DVD::afficherInfos() {
    VHS::afficherInfos();
    std::cout << "Nombre de pistes: " << nbPistes << std::endl;
}

void DVD::toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator) {
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
#include "VHS.h"
#include <iostream>

// Constructeur
VHS::VHS(int id, std::string titre, std::string auteur, bool estLibre, int duree, const std::string maisonProduction) : Ressource(id, titre, auteur,estLibre) {
    this->duree = duree;
    this->maisonProduction = maisonProduction;
}

VHS::VHS(int id, std::string titre, std::string auteur, bool estLibre, int duree, const std::string maisonProduction, std::string dateEmprunt, std::string dateRetour, std::string emprunteur) : Ressource(id, titre, auteur,estLibre, dateEmprunt, dateRetour, emprunteur) {
    this->duree = duree;
    this->maisonProduction = maisonProduction;
}

// Getters
int VHS::getDuree() {
    return duree;
}

std::string VHS::getMaisonProduction(){
    return maisonProduction;
}

// Setters
void VHS::setDuree(int duree) {
    this->duree = duree;
}

void VHS::setMaisonProduction(const std::string maisonProduction) {
    this->maisonProduction = maisonProduction;
}

// Méthode pour obtenir le type de ressource
std::string VHS::getType() {
    return "VHS";
}

// Méthode pour afficher les informations de la VHS
void VHS::afficherInfos() {
    Ressource::afficherInfos();
    std::cout << "Type: " << getType() << std::endl;
    std::cout << "Durée: " << duree << " minutes" << std::endl;
    std::cout << "Maison de production: " << maisonProduction << std::endl;
}

void VHS::toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator) {
    // Initialiser l'objet JSON si ce n'est pas déjà fait
    obj.SetObject();

    // Ajout des attributs du livre
    obj.AddMember("id", id, allocator);
    obj.AddMember("titre", rapidjson::Value(titre.c_str(), allocator), allocator);
    obj.AddMember("auteur", rapidjson::Value(auteur.c_str(), allocator), allocator);
    obj.AddMember("estLibre", estLibre, allocator);
    obj.AddMember("duree", duree, allocator);
    obj.AddMember("maisonProduction", rapidjson::Value(maisonProduction.c_str(), allocator), allocator);
    

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
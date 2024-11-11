#include "Fichier.h"
#include <iostream>

Fichier::Fichier(int id, std::string titre, std::string auteur, bool estLibre, int taille,  std::string& nom,  std::string& cheminAcces)
    : Ressource(id, titre, auteur, estLibre){
        this->taille = taille;
        this->nom = nom;
        this->cheminAcces = cheminAcces;
    }

Fichier::Fichier(int id, std::string titre, std::string auteur, bool estLibre, int taille,  std::string& nom,  std::string& cheminAcces, std::string dateEmprunt, std::string dateRetour, std::string emprunteur)
    : Ressource(id, titre, auteur, estLibre, dateEmprunt, dateRetour, emprunteur){  
        this->taille = taille;
        this->nom = nom;
        this->cheminAcces = cheminAcces;
    }
std::string Fichier::getType() {
    return "Fichier";
}

void Fichier::afficherInfos() {
    Ressource::afficherInfos();
    std::cout << "Type:" << getType() << std::endl;
    std::cout << "Taille: " << taille << " octets" << std::endl;
    std::cout << "Nom: " << nom << std::endl;
    std::cout << "Chemin d'accès: " << cheminAcces << std::endl;
}

void Fichier::toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator) {
    // Initialiser l'objet JSON si ce n'est pas déjà fait
    obj.SetObject();

    // Ajout des attributs du livre
    obj.AddMember("id", id, allocator);
    obj.AddMember("titre", rapidjson::Value(titre.c_str(), allocator), allocator);
    obj.AddMember("auteur", rapidjson::Value(auteur.c_str(), allocator), allocator);
    obj.AddMember("estLibre", estLibre, allocator);
    obj.AddMember("taille", taille, allocator);
    obj.AddMember("nom", rapidjson::Value(nom.c_str(), allocator), allocator);
    obj.AddMember("cheminAcces", rapidjson::Value(cheminAcces.c_str(), allocator), allocator);

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
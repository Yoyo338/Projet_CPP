#include "Livre.h"
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

// Constructor
Livre::Livre(int id, std::string titre, std::string auteur, bool estLibre, int annee, int nombreDePages, std::string collection, std::string resume)
    : Ressource(id, titre, auteur, estLibre) {
    this->annee = annee;
    this->nombreDePages = nombreDePages;
    this->collection = collection;
    this->resume = resume;
    }
Livre::Livre(int id, std::string titre, std::string auteur, bool estLibre, int annee, int nombreDePages, std::string collection, std::string resume, std::string dateEmprunt, std::string dateRetour, std::string emprunteur)
    : Ressource(id, titre, auteur, estLibre, dateEmprunt, dateRetour, emprunteur) {
    this->annee = annee;
    this->nombreDePages = nombreDePages;
    this->collection = collection;
    this->resume = resume;
    }

Livre::Livre() {}

// Getters
int Livre::getNombreDePages() {
    return nombreDePages;
}

int Livre::getAnnee() {
    return annee;
}

std::string Livre::getCollection() {
    return collection;
}

std::string Livre::getResume() {
    return resume;
}

// Setters
void Livre::setNombreDePages(int nombreDePages) {
    this->nombreDePages = nombreDePages;
}

void Livre::setAnnee(int annee) {
    this->annee = annee;
}

void Livre::setCollection(std::string collection) {
    this->collection = collection;
}

void Livre::setResume(std::string resume) {
    this->resume = resume;
}

// Other methods
std::string Livre::getType() {
    return "Livre";
}

void Livre::afficherInfos() {
    Ressource::afficherInfos();
    std::cout << "Année: " << annee << std::endl;
    std::cout << "Nombre de pages: " << nombreDePages << std::endl;
    std::cout << "Collection: " << collection << std::endl;
    std::cout << "Résumé: " << resume << std::endl;
}

void Livre::toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator) {
    // Initialiser l'objet JSON si ce n'est pas déjà fait
    obj.SetObject();

    // Ajout des attributs du livre
    obj.AddMember("id", id, allocator);
    obj.AddMember("titre", rapidjson::Value(titre.c_str(), allocator), allocator);
    obj.AddMember("auteur", rapidjson::Value(auteur.c_str(), allocator), allocator);
    obj.AddMember("estLibre", estLibre, allocator);
    obj.AddMember("annee", annee, allocator);
    obj.AddMember("nombreDePages", nombreDePages, allocator);
    obj.AddMember("collection", rapidjson::Value(collection.c_str(), allocator), allocator);
    obj.AddMember("resume", rapidjson::Value(resume.c_str(), allocator), allocator);

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
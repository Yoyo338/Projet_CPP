#include "Revue.h"
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

// Constructeur avec paramètres
Revue::Revue(int id, std::string titre, std::string auteur, bool estLibre, int annee, int nombreDePages, std::string collection, std::string resume, std::string editeur, int nbArticles, std::vector<std::string> listeNomsArticles)
    : Livre(id, titre, auteur,estLibre,annee,nombreDePages,collection, resume) {
    this->editeur = editeur;
    this->nbArticles = nbArticles;
    this->listeNomsArticles = listeNomsArticles;
    }
Revue::Revue(int id, std::string titre, std::string auteur, bool estLibre, int annee, int nombreDePages, std::string collection, std::string resume, std::string editeur, int nbArticles, std::vector<std::string> listeNomsArticles, std::string dateEmprunt, std::string dateRetour, std::string emprunteur)
    : Livre(id, titre, auteur,estLibre,annee,nombreDePages,collection, resume, dateEmprunt, dateRetour, emprunteur) {
    this->editeur = editeur;
    this->nbArticles = nbArticles;
    this->listeNomsArticles = listeNomsArticles;
    }

// Constructeur par défaut
Revue::Revue() {}

// Méthode pour obtenir le type de l'objet
std::string Revue::getType() {
    return "Revue";
}

// Méthode pour afficher les informations de la revue
void Revue::afficherInfos() {
    Livre::afficherInfos();
    std::cout << "Editeur: " << editeur << std::endl;
    std::cout << "Nombre d'articles: " << nbArticles << std::endl;
    std::cout << "Liste des noms d'articles: " << std::endl;
    for (auto nomArticle : listeNomsArticles) {
        std::cout << "- " << nomArticle << std::endl;
    }
}

// Getters
std::string Revue::getEditeur() {
    return editeur;
}

int Revue::getNbArticles() {
    return nbArticles;
}

std::vector<std::string> Revue::getListeNomsArticles() {
    return listeNomsArticles;
}

// Setters
void Revue::setEditeur(std::string& editeur) {
    this->editeur = editeur;
}

void Revue::setNbArticles(int nbArticles) {
    this->nbArticles = nbArticles;
}

void Revue::setListeNomsArticles(std::vector<std::string>& listeNomsArticles) {
    this->listeNomsArticles = listeNomsArticles;
}

void Revue::toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator) {
    // Créer un tableau JSON pour listeNomsArticles
        rapidjson::Value articlesArray(rapidjson::kArrayType);
        for (const auto& article : listeNomsArticles) {
            articlesArray.PushBack(rapidjson::Value(article.c_str(), allocator), allocator);
        }
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
    obj.AddMember("editeur", rapidjson::Value(editeur.c_str(), allocator), allocator);
    obj.AddMember("nbArticles", nbArticles, allocator);
    obj.AddMember("ListeNomsArticles", rapidjson::Value(articlesArray, allocator), allocator);

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
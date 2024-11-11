#include <string>
#include <iostream>
#include "Ressource.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


    // Constructor
    Ressource::Ressource(int id, std::string title, std::string author, bool estLibre){
        this->id = id;
        this->titre = title;
        this->auteur = author;
        this->estLibre = estLibre;
    }
    Ressource::Ressource(int id, std::string title, std::string author, bool estLibre, std::string dateEmprunt, std::string dateRetour, std::string emprunteur){
        this->id = id;
        this->titre = title;
        this->auteur = author;
        this->estLibre = estLibre;
        this->dateEmprunt = dateEmprunt;
        this->dateRetour = dateRetour;
        this->emprunteur = emprunteur;
    }
    Ressource::Ressource() {}

    // Destructor
     Ressource::~Ressource() {}

    // Getters
    int  Ressource::getId() { return id; }
    std::string  Ressource::getTitre(){ return titre; }
    std::string  Ressource::getAuteur(){ return auteur; }
    bool  Ressource::getEstLibre() { 
        std::cout << "estLibre: " << estLibre << std::endl;
        return estLibre; }

    // Setters
    void Ressource::setId(int newId) { this->id = newId; }
    void Ressource::setTitle(std::string title) { this->titre = title; }
    void Ressource::setAuthor(std::string author) { this->auteur = author; }
    void Ressource::setEstLibre(bool libre) { this->estLibre = libre; }
    void Ressource::setDateEmprunt(std::string newDateEmprunt) { this->dateEmprunt = newDateEmprunt; }
    void Ressource::setDateRetour(std::string newDateRetour) { this->dateRetour = newDateRetour; }
    void Ressource::setEmprunteur(std::string newEmprunteur) { this->emprunteur = newEmprunteur; }

    // Display function
    void Ressource::afficherInfos() {
        std::cout << "ID: " << id << "\n"
                  << "Titre: " << titre << "\n"
                  << "Auteur: " << auteur << "\n"
                  << "EstLibre: " << estLibre << "\n"
                  << "dateEmprunt: " << dateEmprunt << "\n"
                  << "dateRetour: " << dateRetour << "\n"
                  << "emprunteur: " << emprunteur
                  << std::endl;
    }

    void Ressource::emprunter(std::string newDateEmprunt, std::string newDateRetour, std::string newEmprunteur) {
        setDateEmprunt(newDateEmprunt);
        setDateRetour(newDateRetour);
        setEmprunteur(newEmprunteur);
        setEstLibre(false);
        std::cout << "Ressource " << id << " empruntée" << std::endl;
    }

    void Ressource::rendre() {
        setDateEmprunt("");
        setDateRetour("");
        setEmprunteur("");
        setEstLibre(true);
        std::cout << "Ressource " << id << " rendue" << std::endl;
    }

    bool Ressource::verifierDisponibilite() {
        if (getEstLibre()) {
            std::cout << "Ressource disponible" << std::endl;
        } else {
            std::cout << "Ressource non disponible" << std::endl;
        }
        return getEstLibre();
    }

    void Ressource::toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator) {}



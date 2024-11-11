#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class Ressource {
    protected:
        int id;
        std::string titre;
        std::string auteur;
        bool estLibre;
        std::string dateEmprunt;
        std::string dateRetour;
        std::string emprunteur;

    public:
        // Constructor
        Ressource(int id, std::string title, std::string author, bool estLibre);
        Ressource(int id, std::string title, std::string author, bool estLibre, std::string dateEmprunt, std::string dateRetour, std::string emprunteur);
        Ressource();

        // Destructor
        ~Ressource();

        // Getters
        int getId();
        std::string getTitre();
        std::string getAuteur();
        bool getEstLibre();

        // Setters
        void setId(int newId);
        void setTitle(std::string title);
        void setAuthor(std::string author);
        void setEstLibre(bool estLibre);
        void setDateEmprunt(std::string dateEmprunt);
        void setDateRetour(std::string dateRetour);
        void setEmprunteur(std::string emprunteur);

        // Display function
        virtual void afficherInfos();
        virtual std::string getType() = 0;
        void emprunter(std::string dateEmprunt, std::string dateRetour, std::string emprunteur);
        void rendre();
        bool verifierDisponibilite();
        virtual void toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator);
};

#endif
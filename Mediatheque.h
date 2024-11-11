#ifndef MEDIATHEQUE_H
#define MEDIATHEQUE_H

#include "Ressource.h"
#include <iostream>
#include <vector>

class Mediatheque{
    protected:
        std::vector<Ressource*> listeRessources;
        std::vector<Ressource*> listeRessourcesOriginale;
    public:
        Mediatheque(std::vector<Ressource*> listeRessources);
        Mediatheque();
        ~Mediatheque();
        void bye();
        void loadFileName(std::string file);
        void saveFileName(std::string file);
        void searchChaine(std::string chaine);
        void clear();
        void list();
        void showId();
        std::string getTypeName(int choix);
        void addType();
        void deleteId(int id);
        void reset();
        bool ressourceExistante(std::string titre, std::string type, std::string auteur);
        int generateNewID();
        void emprunterId(int Id);
        void rendreId(int Id);
        void addRessource(Ressource* ressource);
};


#endif
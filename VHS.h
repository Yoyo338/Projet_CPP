    #ifndef VHS_H
    #define VHS_H

    #include "Ressource.h"
    #include <string>

    class VHS : public Ressource {
        protected:
            int duree;
            std::string maisonProduction;

        public:
            VHS(int id, std::string titre, std::string auteur, bool estLibre, int duree, const std::string maisonProduction);
            VHS(int id, std::string titre, std::string auteur, bool estLibre, int duree, const std::string maisonProduction, std::string dateEmprunt, std::string dateRetour, std::string emprunteur);

            // Getters
            int getDuree();
            std::string getMaisonProduction();

            // Setters
            void setDuree(int duree);
            void setMaisonProduction(const std::string maisonProduction);
            

            std::string getType();
            void afficherInfos();
            void toJSON(rapidjson::Value& obj, rapidjson::Document::AllocatorType& allocator);
        
    };

    #endif // VHS_H

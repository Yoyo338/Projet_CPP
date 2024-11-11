#include <iostream>
#include "CD.h"
#include "DVD.h"
#include "Fichier.h"
#include "Livre.h"
#include "Revue.h"
#include "Ressource.h"
#include "VHS.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/error/en.h>

int main() {
    // Charger le fichier JSON
    FILE* fp = fopen("Fichier.json", "r"); // Remplace par le chemin de ton fichier
    if (!fp) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);
    fclose(fp);

    // Vérifier si le document est bien formé
    if (document.HasParseError()) {
        std::cerr << "Erreur de parsing JSON : " << document.GetParseError() << std::endl;
        return 1;
    }

    // Fonction pour afficher les éléments d'un type de média
    auto afficherMedia = [](const rapidjson::Value& type, const std::string& nomType) {
        std::cout << nomType << ":\n";
        for (rapidjson::SizeType i = 0; i < type.Size(); i++) {
            std::cout << "  ID: " << type[i]["id"].GetInt() << "\n";
            std::cout << "  Titre: " << type[i]["titre"].GetString() << "\n";
            std::cout << "  Auteur: " << type[i]["auteur"].GetString() << "\n";
            std::cout << "  Est libre: " << (type[i]["estLibre"].GetBool() ? "Oui" : "Non") << "\n";
            if (nomType == "CD" || nomType == "DVD" || nomType == "VHS") {
                std::cout << "  Durée: " << type[i]["duree"].GetInt() << " minutes\n";
                if(nomType == "CD" || nomType == "DVD") {
                    std::cout << "  Nombre de pistes: " << type[i]["nbPiste"].GetInt() << "\n";
                }
                std::cout << "  Maison de production: " << type[i]["maisonProduction"].GetString() << "\n";
            }
            if (type[i].HasMember("taille")) {
                std::cout << "  Taille: " << type[i]["taille"].GetInt() << " Mo\n";
                std::cout << "  Nom: " << type[i]["nom"].GetString() << "\n";
                std::cout << "  CheminAcces: " << type[i]["cheminAcces"].GetString() << "\n";
            } else if (type[i].HasMember("annee")) {
                std::cout << "  Année: " << type[i]["annee"].GetInt() << "\n";
                std::cout << "  Nombre de pages: " << type[i]["nbPages"].GetInt() << "\n";
                std::cout << "  Collection: " << type[i]["collection"].GetString() << "\n";
                std::cout << "  Résumé: " << type[i]["resume"].GetString() << "\n";
                if (type[i].HasMember("listeNomsArticles")) {
                    std::cout << "  Articles: ";
                    for (rapidjson::SizeType j = 0; j < type[i]["listeNomsArticles"].Size(); j++) {
                        std::cout << type[i]["listeNomsArticles"][j].GetString() << " ";
                    }
                    std::cout << "\n";
                }
            }
            std::cout << std::endl;
        }
    };

    // Afficher chaque type de média
    afficherMedia(document["CD"], "CD");
    afficherMedia(document["DVD"], "DVD");
    afficherMedia(document["VHS"], "VHS");
    afficherMedia(document["Fichier"], "Fichiers");
    afficherMedia(document["Livre"], "Livres");
    afficherMedia(document["Revue"], "Revues");

    return 0;
}

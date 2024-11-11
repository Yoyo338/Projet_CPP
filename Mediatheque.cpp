#include "Ressource.h"
#include "Mediatheque.h"
#include "CD.h"
#include "DVD.h"
#include "VHS.h"
#include "Fichier.h"
#include "Livre.h"
#include "Revue.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>
#include <filesystem>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/error/en.h>

// Constructeur
Mediatheque::Mediatheque(std::vector<Ressource *> listeRessources)
{
    this->listeRessources = listeRessources;
}
Mediatheque::Mediatheque()
{
    this->listeRessources = {};
}

// Destructeur
Mediatheque::~Mediatheque()
{
    for (Ressource *ressource : listeRessources)
    {
        delete ressource; // Nettoyage des ressources allouées
    }
}

void Mediatheque::bye()
{
    // Sauvegarde des données avant de quitter
    char fileName[] = "Fichier.json";
    saveFileName(fileName);

    // Nettoyer la liste des ressources
    for (auto &ressource : listeRessources)
    {
        delete ressource; // Libérer chaque objet ressource alloué dynamiquement
    }
    listeRessources.clear(); // Vider le vecteur après avoir supprimé les objets

    for (auto &ressource : listeRessourcesOriginale)
    {
        delete ressource; // Libérer chaque objet ressource alloué dynamiquement
    }
    listeRessourcesOriginale.clear(); // Vider le vecteur après avoir supprimé les objets

    std::cout << "Bye!" << std::endl;

    // Fin du programme proprement
    exit(0); // Utiliser exit pour permettre la destruction propre des objets
}

void Mediatheque::loadFileName(std::string file)
{
    
    std::string completeFilePath = "../Files/" + file;
    std::filesystem::path filePath(completeFilePath);
    std::cout << "Tentative d'ouverture du fichier : " << std::filesystem::absolute(filePath) << std::endl;
    // Ouvrir le fichier JSON avec std::ifstream
    std::ifstream ifs(completeFilePath);
    if (!ifs.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << file << std::endl;
        return;
    }

    // Lire le contenu du fichier dans une chaîne de caractères
    std::string fileContent((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();

    // Parser le contenu JSON
    rapidjson::Document document;
    document.Parse(fileContent.c_str());

    // Vérifier si le document est bien formé
    if (document.HasParseError())
    {
        std::cerr << "Erreur de parsing JSON : " << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;
        return;
    }

    // Créer des objets pour chaque type de média
    if (document.HasMember("CD") && document["CD"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < document["CD"].Size(); i++)
        {
            const auto &item = document["CD"][i];
            if (item.HasMember("id") && item.HasMember("titre") && item.HasMember("auteur"))
            {
                // Allocation dynamique de l'objet CD
                CD *cd = new CD(
                    item["id"].GetInt(),
                    item["titre"].GetString(),
                    item["auteur"].GetString(),
                    item.HasMember("estLibre") ? item["estLibre"].GetBool() : false,
                    item.HasMember("duree") ? item["duree"].GetInt() : 0,
                    item.HasMember("maisonProduction") && item["maisonProduction"].IsString() ? item["maisonProduction"].GetString() : "",
                    item.HasMember("nbPistes") ? item["nbPistes"].GetInt() : 0,
                    item.HasMember("dateEmprunt") && item["dateEmprunt"].IsString() ? item["dateEmprunt"].GetString() : "",
                    item.HasMember("dateRetour") && item["dateRetour"].IsString() ? item["dateRetour"].GetString() : "",
                    item.HasMember("emprunteur") && item["emprunteur"].IsString() ? item["emprunteur"].GetString() : "");
                listeRessources.push_back(cd); // Ajouter le pointeur à la liste
            }
        }
    }
    if (document.HasMember("DVD") && document["DVD"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < document["DVD"].Size(); i++)
        {
            const auto &item = document["DVD"][i];
            if (item.HasMember("id") && item.HasMember("titre") && item.HasMember("auteur"))
            {
                // Allocation dynamique de l'objet DVD
                DVD *dvd = new DVD(
                    item["id"].GetInt(),
                    item["titre"].GetString(),
                    item["auteur"].GetString(),
                    item.HasMember("estLibre") && item["estLibre"].IsBool() ? item["estLibre"].GetBool() : false,
                    item.HasMember("duree") && item["duree"].IsInt() ? item["duree"].GetInt() : 0,
                    item.HasMember("MaisonProduction") && item["maisonProduction"].GetString() ? item["maisonProduction"].GetString() : "",
                    item.HasMember("nbPistes") && item["nbPistes"].GetInt() ? item["nbPistes"].GetInt() : 0,
                    item.HasMember("dateEmprunt") && item["dateEmprunt"].IsString() ? item["dateEmprunt"].GetString() : "",
                    item.HasMember("dateRetour") && item["dateRetour"].IsString() ? item["dateRetour"].GetString() : "",
                    item.HasMember("emprunteur") && item["emprunteur"].IsString() ? item["emprunteur"].GetString() : "");
                listeRessources.push_back(dvd); // Ajouter le pointeur à la liste
            }
        }
    }
    if (document.HasMember("VHS") && document["VHS"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < document["VHS"].Size(); i++)
        {
            const auto &item = document["VHS"][i];
            if (item.HasMember("id") && item.HasMember("titre") && item.HasMember("auteur"))
            {
                // Allocation dynamique de l'objet VHS
                VHS *vhs = new VHS(
                    item["id"].GetInt(),
                    item["titre"].GetString(),
                    item["auteur"].GetString(),
                    item.HasMember("estLibre") && item["estLibre"].IsBool() ? item["estLibre"].GetBool() : false,
                    item.HasMember("duree") && item["duree"].IsInt() ? item["duree"].GetInt() : 0,
                    item.HasMember("MaisonProduction") && item["maisonProduction"].GetString() ? item["maisonProduction"].GetString() : "",
                    item.HasMember("dateEmprunt") && item["dateEmprunt"].IsString() ? item["dateEmprunt"].GetString() : "",
                    item.HasMember("dateRetour") && item["dateRetour"].IsString() ? item["dateRetour"].GetString() : "",
                    item.HasMember("emprunteur") && item["emprunteur"].IsString() ? item["emprunteur"].GetString() : "");
                listeRessources.push_back(vhs); // Ajouter le pointeur à la liste
            }
        }
    }
    if (document.HasMember("Fichier") && document["Fichier"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < document["Fichier"].Size(); i++)
        {
            const auto &item = document["Fichier"][i];
            if (item.HasMember("id") && item.HasMember("titre") && item.HasMember("auteur"))
            {
                std::string nom = item["nom"].GetString() ? item["nom"].GetString() : "";
                std::string cheminAcces = item["cheminAcces"].GetString() ? item["cheminAcces"].GetString() : "";
                // Allocation dynamique de l'objet Fichier
                Fichier *fichier = new Fichier(
                    item["id"].GetInt(),
                    item["titre"].GetString(),
                    item["auteur"].GetString(),
                    item.HasMember("estLibre") && item["estLibre"].IsBool() ? item["estLibre"].GetBool() : false,
                    item.HasMember("taille") && item["taille"].GetInt() ? item["taille"].GetInt() : 0,
                    nom,
                    cheminAcces,
                    item.HasMember("dateEmprunt") && item["dateEmprunt"].IsString() ? item["dateEmprunt"].GetString() : "",
                    item.HasMember("dateRetour") && item["dateRetour"].IsString() ? item["dateRetour"].GetString() : "",
                    item.HasMember("emprunteur") && item["emprunteur"].IsString() ? item["emprunteur"].GetString() : "");
                listeRessources.push_back(fichier); // Ajouter le pointeur à la liste
            }
        }
    }
    if (document.HasMember("Livre") && document["Livre"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < document["Livre"].Size(); i++)
        {
            const auto &item = document["Livre"][i];
            if (item.HasMember("id") && item.HasMember("titre") && item.HasMember("auteur"))
            {
                // Allocation dynamique de l'objet Livre
                Livre *livre = new Livre(
                    item["id"].GetInt(),
                    item["titre"].GetString(),
                    item["auteur"].GetString(),
                    item.HasMember("estLibre") && item["estLibre"].GetBool() ? item["estLibre"].GetBool() : false,
                    item.HasMember("annee") && item["annee"].GetInt() ? item["annee"].GetInt() : 0,
                    item.HasMember("nombreDePages") && item["nombreDePages"].GetInt() ? item["nombreDePages"].GetInt() : 0,
                    item.HasMember("collection") && item["collection"].GetString() ? item["collection"].GetString() : "",
                    item.HasMember("resume") && item["resume"].GetString() ? item["resume"].GetString() : "",
                    item.HasMember("dateEmprunt") && item["dateEmprunt"].IsString() ? item["dateEmprunt"].GetString() : "",
                    item.HasMember("dateRetour") && item["dateRetour"].IsString() ? item["dateRetour"].GetString() : "",
                    item.HasMember("emprunteur") && item["emprunteur"].IsString() ? item["emprunteur"].GetString() : "");
                listeRessources.push_back(livre); // Ajouter le pointeur à la liste
            }
        }
    }
    if (document.HasMember("Revue") && document["Revue"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < document["Revue"].Size(); i++)
        {
            const auto &item = document["Revue"][i];
            // Créer un vecteur pour stocker les noms d'articles
            std::vector<std::string> nomsArticles;

            if (item.HasMember("listeNomsArticles") && item["listeNomsArticles"].IsArray())
            {
                const rapidjson::Value &articlesArray = item["listeNomsArticles"];
                for (rapidjson::SizeType j = 0; j < articlesArray.Size(); j++)
                {
                    if (articlesArray[j].IsString())
                    {
                        nomsArticles.push_back(articlesArray[j].GetString());
                    }
                }
            }

            if (item.HasMember("id") && item.HasMember("titre") && item.HasMember("auteur"))
            {
                // Allocation dynamique de l'objet Revue
                Revue *revue = new Revue(
                    item["id"].GetInt(),
                    item["titre"].GetString(),
                    item["auteur"].GetString(),
                    item.HasMember("estLibre") && item["estLibre"].GetBool() ? item["estLibre"].GetBool() : false,
                    item.HasMember("annee") && item["annee"].GetInt() ? item["annee"].GetInt() : 0,
                    item.HasMember("nombreDePages") && item["nombreDePages"].GetInt() ? item["nombreDePages"].GetInt() : 0,
                    item.HasMember("collection") && item["collection"].GetString() ? item["collection"].GetString() : "",
                    item.HasMember("resume") && item["resume"].GetString() ? item["resume"].GetString() : "",
                    item.HasMember("editeur") && item["editeur"].GetString() ? item["editeur"].GetString() : "",
                    item.HasMember("nbArticles") && item["nbArticles"].GetInt() ? item["nbArticles"].GetInt() : 0,
                    nomsArticles,
                    item.HasMember("dateEmprunt") && item["dateEmprunt"].IsString() ? item["dateEmprunt"].GetString() : "",
                    item.HasMember("dateRetour") && item["dateRetour"].IsString() ? item["dateRetour"].GetString() : "",
                    item.HasMember("emprunteur") && item["emprunteur"].IsString() ? item["emprunteur"].GetString() : "");
                listeRessources.push_back(revue); // Ajouter le pointeur à la liste
            }
        }
    }
    listeRessourcesOriginale = listeRessources;
}

void Mediatheque::saveFileName(std::string filename)
{
    rapidjson::Document doc;
    doc.SetObject(); // Initialisation du document JSON
    auto &allocator = doc.GetAllocator();

    // Créer des tableaux pour chaque catégorie de ressources
    rapidjson::Value livresArray(rapidjson::kArrayType);
    rapidjson::Value cdArray(rapidjson::kArrayType);
    rapidjson::Value dvdArray(rapidjson::kArrayType);
    rapidjson::Value vhsArray(rapidjson::kArrayType);
    rapidjson::Value fichierArray(rapidjson::kArrayType);
    rapidjson::Value revueArray(rapidjson::kArrayType);

    // Parcourir toutes les ressources et les ajouter aux tableaux appropriés
    for (auto &res : listeRessources)
    {
        rapidjson::Value obj(rapidjson::kObjectType); // Objet JSON pour une ressource
        res->toJSON(obj, allocator);                  // Appel à toJSON spécifique à chaque classe

        if (dynamic_cast<Revue *>(res))
        {
            revueArray.PushBack(obj, allocator);
        }
        else if (dynamic_cast<Livre *>(res))
        {
            livresArray.PushBack(obj, allocator);
        }
        else if (dynamic_cast<CD *>(res))
        {
            cdArray.PushBack(obj, allocator);
        }
        else if (dynamic_cast<DVD *>(res))
        {
            dvdArray.PushBack(obj, allocator);
        }
        else if (dynamic_cast<VHS *>(res))
        {
            vhsArray.PushBack(obj, allocator);
        }
        else if (dynamic_cast<Fichier *>(res))
        {
            fichierArray.PushBack(obj, allocator);
        }
    }

    // Ajouter les tableaux au document sous leurs catégories respectives
    doc.AddMember("Livre", livresArray, allocator);
    doc.AddMember("CD", cdArray, allocator);
    doc.AddMember("DVD", dvdArray, allocator);
    doc.AddMember("VHS", vhsArray, allocator);
    doc.AddMember("Fichier", fichierArray, allocator);
    doc.AddMember("Revue", revueArray, allocator);

    std::string completeFilePath = "../Files/" + filename;
    // Sauvegarder le document JSON dans un fichier
    std::ofstream ofs(completeFilePath);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);

    ofs.close(); // Fermer le fichier après écriture
}

void Mediatheque::searchChaine(std::string chaine)
{
    std::vector<Ressource *> resultatsRecherche;

    for (auto &ressource : listeRessources)
    {
        // Vérifier si le titre ou l'auteur contient la chaîne recherchée
        if (ressource->getTitre().find(chaine) != std::string::npos ||
            ressource->getAuteur().find(chaine) != std::string::npos)
        {
            resultatsRecherche.push_back(ressource);
        }
    }

    // Remplacer la liste courante par les résultats de la recherche
    listeRessources = resultatsRecherche;

    std::cout << "Recherche effectuée. " << listeRessources.size() << " résultat(s) trouvé(s)." << std::endl;
}

void Mediatheque::clear()
{
    // Réinitialiser la liste courante avec la liste complète des ressources originales
    listeRessources = listeRessourcesOriginale;

    std::cout << "Recherche réinitialisée. Toutes les ressources sont à nouveau disponibles." << std::endl;
}

void Mediatheque::list()
{
    std::cout << "Liste des ressources:\n";

    // Vérifier si la liste est vide
    if (listeRessources.empty())
    {
        std::cout << "Aucune ressource à afficher." << std::endl;
        return; // Sortir de la méthode si aucune ressource n'est présente
    }

    // Afficher chaque ressource
    for (auto &res : listeRessources)
    {
        res->afficherInfos();   // Appel de la méthode afficher sur chaque ressource
        std::cout << std::endl; // Ajouter une ligne vide entre les affichages
    }
}

void Mediatheque::showId()
{
    int id;
    std::cout << "Entrez l'ID de la ressource à afficher : ";
    std::cin >> id;

    // Recherche de la ressource avec l'ID correspondant
    auto it = std::find_if(listeRessourcesOriginale.begin(), listeRessourcesOriginale.end(), [id](Ressource *res)
                           { return res->getId() == id; });

    if (it != listeRessourcesOriginale.end())
    {
        (*it)->afficherInfos();
    }
    else
    {
        std::cout << "Aucune ressource trouvée avec l'ID " << id << std::endl;
    }
}

std::string Mediatheque::getTypeName(int choix)
{
    switch (choix)
    {
    case 1:
        return "Livre";
    case 2:
        return "DVD";
    case 3:
        return "CD";
    case 4:
        return "VHS";
    case 5:
        return "Revue";
    case 6:
        return "Fichier";
    default:
        return "Inconnu";
    }
}

void Mediatheque::addType()
{
    int choix;
    std::cout << "Quel type de ressource souhaitez-vous ajouter ?" << std::endl;
    std::cout << "1. Livre" << std::endl;
    std::cout << "2. DVD" << std::endl;
    std::cout << "3. CD" << std::endl;
    std::cout << "4. VHS" << std::endl;
    std::cout << "5. Revue" << std::endl;
    std::cout << "6. Fichier" << std::endl;
    std::cout << "Entrez le numéro de votre choix : ";
    std::cin >> choix;

    // Variables communes aux ressources
    std::string titre, auteur;
    bool estLibre;
    int id = generateNewID();

    // Saisie des attributs communs
    std::cout << "Entrez le titre : ";
    std::cin.ignore(); // Ignorer tout retour chariot précédent
    std::getline(std::cin, titre);

    std::cout << "Entrez l'auteur : ";
    std::getline(std::cin, auteur);

    if (ressourceExistante(titre, getTypeName(choix), auteur))
    {
        std::cout << "Une ressource avec le même titre existe déjà." << std::endl;
        return;
    }

    std::cout << "La ressource est-elle libre ? (1 pour Oui, 0 pour Non) : ";
    std::cin >> estLibre;

    switch (choix)
    {
    case 1:
    { // Ajout d'un Livre
        int annee, nbPages;
        std::string collection, resume;

        std::cout << "Entrez l'année de publication : ";
        std::cin >> annee;
        std::cout << "Entrez le nombre de pages : ";
        std::cin >> nbPages;
        std::cin.ignore(); // Ignorer le retour chariot
        std::cout << "Entrez la collection : ";
        std::getline(std::cin, collection);
        std::cout << "Entrez le résumé : ";
        std::getline(std::cin, resume);

        // Créer un objet Livre et l'ajouter à la liste des ressources
        listeRessourcesOriginale.push_back(new Livre(id, titre, auteur, estLibre, annee, nbPages, collection, resume));

        break;
    }
    case 2:
    { // Ajout d'un DVD
        int duree, nbPistes;
        std::string maisonProduction;

        std::cout << "Entrez la durée (en minutes) : ";
        std::cin >> duree;
        std::cin.ignore(); // Ignorer le retour chariot
        std::cout << "Entrez la maison de production : ";
        std::getline(std::cin, maisonProduction);
        std::cout << "Entrez le nombre de pistes : ";
        std::cin >> nbPistes;

        // Créer un objet DVD et l'ajouter à la liste des ressources
        listeRessourcesOriginale.push_back(new DVD(id, titre, auteur, estLibre, duree, maisonProduction, nbPistes));
        break;
    }
    case 3:
    { // Ajout d'un CD
        int duree, nbPistes;
        std::string maisonProduction;

        std::cout << "Entrez la durée (en minutes) : ";
        std::cin >> duree;
        std::cout << "Entrez le nombre de pistes : ";
        std::cin >> nbPistes;
        std::cin.ignore(); // Ignorer le retour chariot
        std::cout << "Entrez la maison de production : ";
        std::getline(std::cin, maisonProduction);

        // Créer un objet CD et l'ajouter à la liste des ressources
        listeRessourcesOriginale.push_back(new CD(id, titre, auteur, estLibre, duree, maisonProduction, nbPistes));
        break;
    }
    case 4:
    { // Ajout d'une VHS
        int duree;
        std::string maisonProduction;

        std::cout << "Entrez la durée (en minutes) : ";
        std::cin >> duree;
        std::cin.ignore(); // Ignorer le retour chariot
        std::cout << "Entrez la maison de production : ";
        std::getline(std::cin, maisonProduction);

        // Créer un objet VHS et l'ajouter à la liste des ressources
        listeRessourcesOriginale.push_back(new VHS(id, titre, auteur, estLibre, duree, maisonProduction));
        break;
    }
    case 5:
    { // Ajout d'une Revue
        int nbPages, nbArticles, annee;
        std::string collection, resume, editeur;

        std::cout << "Entrez l'année de publication : ";
        std::cin >> annee;
        std::cout << "Entrez le nombre de pages : ";
        std::cin >> nbPages;
        std::cin.ignore(); // Ignorer le retour chariot
        std::cout << "Entrez la collection : ";
        std::getline(std::cin, collection);
        std::cout << "Entrez le résumé : ";
        std::getline(std::cin, resume);
        std::cout << "Entrez le nom de l'éditeur : ";
        std::getline(std::cin, editeur);
        std::cout << "Entrez le nombre d'articles : ";
        std::cin >> nbArticles;
        std::cin.ignore(); // Ignorer le retour chariot

        // Initialiser la liste des noms d'articles après avoir obtenu nbArticles
        std::vector<std::string> listeNomsArticles(nbArticles);

        for (int i = 0; i < nbArticles; i++)
        {
            std::cout << "Nom de l'article " << i + 1 << " : ";
            std::getline(std::cin, listeNomsArticles[i]);
        }

        // Créer un objet Revue et l'ajouter à la liste des ressources
        listeRessourcesOriginale.push_back(new Revue(id, titre, auteur, estLibre, annee, nbPages, collection, resume, editeur, nbArticles, listeNomsArticles));
        break;
    }

    case 6:
    { // Ajout d'un Fichier
        int taille;
        std::string nom, cheminAcces;

        std::cout << "Entrez la taille du fichier (en Mo) : ";
        std::cin >> taille;
        std::cin.ignore(); // Ignorer le retour chariot
        std::cout << "Entrez le nom du fichier : ";
        std::getline(std::cin, nom);
        std::cout << "Entrez le chemin d'accès : ";
        std::getline(std::cin, cheminAcces);

        // Créer un objet Fichier et l'ajouter à la liste des ressources
        listeRessourcesOriginale.push_back(new Fichier(id, titre, auteur, estLibre, taille, nom, cheminAcces));
        break;
    }
    default:
        std::cout << "Choix invalide !" << std::endl;
        break;
    }
    listeRessources = listeRessourcesOriginale;
}

void Mediatheque::deleteId(int id)
{

    Ressource *ressourceASupprimer = nullptr;

    // Chercher la ressource par ID
    for (auto &ressource : listeRessourcesOriginale)
    {
        if (ressource->getId() == id)
        {
            ressourceASupprimer = ressource;
            break;
        }
    }

    if (ressourceASupprimer != nullptr)
    {
        // Afficher les informations de l'objet
        std::cout << "Vous avez sélectionné la ressource suivante : " << std::endl;
        ressourceASupprimer->afficherInfos();

        // Demander confirmation avant suppression
        char confirmation;
        std::cout << "Êtes-vous sûr de vouloir supprimer cette ressource ? (o/n) : ";
        std::cin >> confirmation;

        if (confirmation == 'o' || confirmation == 'O')
        {
            // Utiliser remove_if pour supprimer l'élément
            auto it = std::remove_if(listeRessourcesOriginale.begin(), listeRessourcesOriginale.end(),
                                     [ressourceASupprimer](Ressource *ressource)
                                     {
                                         return ressource == ressourceASupprimer;
                                     });
            listeRessourcesOriginale.erase(it, listeRessourcesOriginale.end()); // Supprimer les éléments retirés par std::remove_if

            std::cout << "Ressource supprimée avec succès." << std::endl;
            delete ressourceASupprimer; // Libérer la mémoire
        }
        else
        {
            std::cout << "Annulation de la suppression." << std::endl;
        }
    }
    else
    {
        std::cout << "Aucune ressource trouvée avec cet ID ou ce titre." << std::endl;
    }
    listeRessources = listeRessourcesOriginale;
}

void Mediatheque::reset()
{
    // Libérer la mémoire pour chaque ressource dans la liste
    std::cout << "Etes-vous sûr de vouloir supprimer toutes les ressource ? oui (o) | non (n)" << std::endl;
    char confirmation;
    std::cin >> confirmation;

    if (confirmation != 'o' && confirmation != 'O')
    {
        std::cout << "Opération annulée." << std::endl;
        return;
    }
    else
    {
        for (auto &ressource : listeRessourcesOriginale)
        {
            delete ressource; // Libération de la mémoire pour chaque ressource
        }

        // Réinitialiser la liste des ressources
        listeRessourcesOriginale.clear(); // Effacer tous les pointeurs de ressources

        std::cout << "Toutes les ressources ont été supprimées de la médiathèque." << std::endl;
    }
}

bool Mediatheque::ressourceExistante(std::string titre, std::string type, std::string auteur)
{
    std::cout << "Vérification de l'existence de la ressource: " << titre << " de type: " << type << " par l'auteur: " << auteur << std::endl;

    // Parcourez la collection de ressources
    for (auto &item : listeRessourcesOriginale) // ressources est un conteneur de vos ressources
    {
        // Vérifiez le titre, le type et l'auteur
        if (item->getTitre() == titre && item->getType() == type && item->getAuteur() == auteur)
        {
            std::cout << "Ressource existante trouvée!" << std::endl;
            return true; // La ressource existe
        }
    }

    std::cout << "Aucune ressource existante trouvée." << std::endl;
    return false; // La ressource n'existe pas
}

int Mediatheque::generateNewID()
{
    int maxID = 0;

    // Parcourir toutes les ressources pour trouver l'ID maximum
    for (const auto &ressource : listeRessourcesOriginale)
    {
        if (ressource->getId() > maxID)
        {
            maxID = ressource->getId();
        }
    }

    // Retourner un nouvel ID en incrémentant le maximum
    return maxID + 1;
}

void Mediatheque::emprunterId(int id)
{
    // Recherche de la ressource avec l'ID correspondant
    auto it = std::find_if(listeRessourcesOriginale.begin(), listeRessourcesOriginale.end(), [id](Ressource *res)
                           { return res->getId() == id; });

    if (it != listeRessourcesOriginale.end())
    {
        std::string dateEmprunt, dateRetour, emprunteur;
        std::cout << "Entrez la date d'emprunt (jj/mm/aaaa) : ";
        std::cin >> dateEmprunt;
        std::cout << "Entrez la date de retour (jj/mm/aaaa) : ";
        std::cin >> dateRetour;
        std::cin.ignore(); // Ignorer le retour chariot
        std::cout << "Entrez le nom de l'emprunteur : ";
        std::getline(std::cin, emprunteur);

        (*it)->emprunter(dateEmprunt, dateRetour, emprunteur);
    }
    else
    {
        std::cout << "Aucune ressource trouvée avec l'ID " << id << std::endl;
    }
    listeRessources = listeRessourcesOriginale;
}

void Mediatheque::rendreId(int id)
{
    // Recherche de la ressource avec l'ID correspondant
    auto it = std::find_if(listeRessourcesOriginale.begin(), listeRessourcesOriginale.end(), [id](Ressource *res)
                           { return res->getId() == id; });

    if (it != listeRessourcesOriginale.end())
    {
        (*it)->rendre();
    }
    else
    {
        std::cout << "Aucune ressource trouvée avec l'ID " << id << std::endl;
    }
    listeRessources = listeRessourcesOriginale;
}

void Mediatheque::addRessource(Ressource *ressource)
{
    listeRessources.push_back(ressource);
    listeRessourcesOriginale.push_back(ressource);
}
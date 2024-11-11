#include <iostream>
#include "CD.h"
#include "DVD.h"
#include "Fichier.h"
#include "Livre.h"
#include "Revue.h"
#include "Ressource.h"
#include "VHS.h"
#include "Mediatheque.h"
#include <fstream>

void clearConsole() {
    // Pour Windows
    #ifdef _WIN32
        system("CLS");
    // Pour Linux/Unix/Mac
    #else
        system("clear");
    #endif
}

// Fonction pour attendre l'entrée de l'utilisateur
void waitForInput() {
    std::cout << "Appuyez sur Entrée pour revenir au menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vide le flux d'entrée
    std::cin.get(); // Attend que l'utilisateur appuie sur Entrée
}

void afficherMenu() {
    std::cout << "\n--- Menu Médiathèque ---" << std::endl;
    std::cout << "1. Charger les données (LOAD)" << std::endl;
    std::cout << "2. Sauvegarder les données (SAVE)" << std::endl;
    std::cout << "3. Ajouter une ressource (ADD)" << std::endl;
    std::cout << "4. Rechercher une chaîne (SEARCH)" << std::endl;
    std::cout << "5. Réinitialiser la base de données après une recherche (CLEAR)" << std::endl;
    std::cout << "6. Lister les ressources (LIST)" << std::endl;
    std::cout << "7. Afficher les détails d'une ressource (SHOW)" << std::endl;
    std::cout << "8. Supprimer une ressource (DELETE)" << std::endl;
    std::cout << "9. Réinitialiser toute la médiathèque (RESET)" << std::endl;
    std::cout << "10. Emprunter une ressource (BORROW)" << std::endl;
    std::cout << "11. Retourner une ressource (RETURN)" << std::endl;
    std::cout << "12. Quitter (BYE)" << std::endl;
    std::cout << "Entrez votre choix : ";
}

int main() {
    Mediatheque mediatheque;
    bool continuer = true;

    while (continuer) {
        clearConsole(); // Efface la console avant d'afficher le menu
        afficherMenu();
        int choix;

        // Vérification de l'entrée pour éviter la boucle infinie si un caractère non entier est saisi
        if (!(std::cin >> choix)) {
            std::cout << "Entrée invalide, veuillez entrer un nombre." << std::endl;
            std::cin.clear(); // Réinitialise l'état d'erreur de std::cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vide le flux d'entrée
            continue; // Recommence la boucle pour afficher le menu
        }

        std::cin.ignore(); // Ignore le caractère de nouvelle ligne restant après l'entrée de l'utilisateur
        clearConsole();
        switch (choix) {
            case 1: {
                std::string fileName;
                std::cout << "Entrez le nom du fichier à charger : ";
                std::getline(std::cin, fileName);
                mediatheque.loadFileName(fileName);
                waitForInput();
                break;
            }
            case 2: {
                std::string fileName;
                std::cout << "Entrez le nom du fichier à sauvegarder : ";
                std::getline(std::cin, fileName);
                mediatheque.saveFileName(fileName);
                waitForInput();
                break;
            }
            case 3: {
                mediatheque.addType();
                waitForInput();
                break;
            }
            case 4: {
                std::string maRecherche;
                std::cout << "Entrez la chaîne à rechercher : ";
                std::getline(std::cin, maRecherche);
                mediatheque.searchChaine(maRecherche);
                waitForInput();
                break;
            }
            case 5: {
                mediatheque.clear();
                waitForInput();
                break;
            }
            case 6: {
                mediatheque.list();
                waitForInput();
                break;
            }
            case 7: {
                mediatheque.showId();
                waitForInput();
                break;
            }
            case 8: {
                int id;
                std::cout << "Entrez l'ID de la ressource à supprimer : ";
                std::cin >> id;
                mediatheque.deleteId(id);
                waitForInput();
                break;
            }
            case 9: {
                mediatheque.reset();
                waitForInput();
                break;
            }
            case 10: { // Nouvelle fonctionnalité : emprunter
                int id;
                std::cout << "Entrez l'ID de la ressource à emprunter : ";
                std::cin >> id;
                mediatheque.emprunterId(id);
                waitForInput();
                break;
            }
            case 11: { // Nouvelle fonctionnalité : retourner
                int id;
                std::cout << "Entrez l'ID de la ressource à retourner : ";
                std::cin >> id;
                mediatheque.rendreId(id);
                waitForInput();
                break;
            }
            case 12: {
                mediatheque.bye();
                continuer = false;
                break;
            }
            default:
                std::cout << "Choix invalide, veuillez réessayer." << std::endl;
                break;
        }
    }

    return 0;
}
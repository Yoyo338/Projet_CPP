#include <gtest/gtest.h>
#include "Mediatheque.h"
#include "CD.h"

// Test de la méthode d'ajout de ressource
TEST(MediathequeTest, AddRessource) {
    Mediatheque mediatheque;
    
    // Crée un CD avec tous les paramètres requis par le constructeur
    CD* cd = new CD(1, "Album", "Artiste", true, 60, "Maison de Production", 10);
    mediatheque.addRessource(cd);

    // Vérification que la ressource a été ajoutée
    EXPECT_TRUE(mediatheque.ressourceExistante("Album", "CD", "Artiste"));
}

// Test de suppression de ressource
TEST(MediathequeTest, DeleteRessource) {
    Mediatheque mediatheque;

    // Crée un CD avec tous les paramètres requis par le constructeur
    CD* cd = new CD(1, "Album", "Artiste", true, 60, "Maison de Production", 10);
    mediatheque.addRessource(cd);

    // Suppression
    mediatheque.deleteId(1);

    // Vérification que la ressource n'existe plus
    EXPECT_FALSE(mediatheque.ressourceExistante("Album", "CD", "Artiste"));
}

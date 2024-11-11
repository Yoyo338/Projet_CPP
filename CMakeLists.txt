cmake_minimum_required(VERSION 3.16)
project(Projet_Cpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver Google Test
find_package(GTest REQUIRED)

# Inclure les dossiers d'en-tête (assurez-vous que vos fichiers .h sont dans ces dossiers)
include_directories(${CMAKE_SOURCE_DIR})

# Sources de votre projet principal
set(PROJECT_SOURCES
    Main.cpp
    CD.h DVD.h Fichier.h Livre.h Mediatheque.h Ressource.h Revue.h VHS.h
    CD.cpp DVD.cpp Fichier.cpp Livre.cpp Mediatheque.cpp Ressource.cpp Revue.cpp VHS.cpp
)

# Création de l'exécutable principal
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Configuration des tests
add_executable(tests test_mediatheque.cpp ${PROJECT_SOURCES})

# Lier Google Test et pthread aux tests
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main pthread)

#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connectSignals();
    updateResourceList();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Création des widgets
    resourceTableView = new QTableView(this);
    searchLineEdit = new QLineEdit(this);
    addButton = new QPushButton("Ajouter", this);
    editButton = new QPushButton("Modifier", this);
    deleteButton = new QPushButton("Supprimer", this);
    searchButton = new QPushButton("Rechercher", this);
    clearButton = new QPushButton("Effacer", this);
    loadButton = new QPushButton("Charger", this);
    saveButton = new QPushButton("Sauvegarder", this);

    // Layout pour les boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);

    // Ajout des widgets au layout principal
    mainLayout->addWidget(resourceTableView);
    mainLayout->addWidget(searchLineEdit);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle("Gestion de Médiathèque");
    resize(800, 600);
}

void MainWindow::connectSignals()
{
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddResource);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::onEditResource);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteResource);
    connect(searchButton, &QPushButton::
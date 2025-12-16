// --- MAUVAIS CODE ---

#include <string>
#include <iostream>

class TextFileSaver {
public:
    void save(const std::string& data) {
        std::cout << "Sauvegarde dans un fichier texte : " << data << std::endl;
    }
};

class Game {
public:
    void saveGame() {
        // PROBLÈME ICI :
        // La classe Game crée elle-même sa dépendance.
        // Elle est "mariée" de force avec TextFileSaver.
        TextFileSaver* saver = new TextFileSaver();
        saver->save("PlayerLvl:10");
        delete saver;
    }
};

// Si demain on veut sauvegarder dans le Cloud ou en Base de Données (SQL),
// on est obligé de modifier la classe Game et de casser le code existant.
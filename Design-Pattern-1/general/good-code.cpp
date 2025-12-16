// --- BON CODE ---
#include <string>
#include <iostream>

// 1. On définit un contrat (Interface)
class ISaver {
public:
    virtual void save(const std::string& data) = 0;
    virtual ~ISaver() = default;
};

// 2. Les implémentations respectent le contrat
class TextFileSaver : public ISaver {
public:
    void save(const std::string& data) override {
        std::cout << "Sauvegarde Fichier : " << data << std::endl;
    }
};

class CloudSaver : public ISaver {
public:
    void save(const std::string& data) override {
        std::cout << "Envoi vers le Cloud : " << data << std::endl;
    }
};

// 3. La classe Game ne connaît que l'interface
class Game {
    ISaver* saver; // Pointeur vers l'abstraction
public:
    // On "injecte" la dépendance à la construction
    Game(ISaver* s) : saver(s) {}
    
    void saveGame() {
        // Game ne sait pas (et ne veut pas savoir) si c'est du fichier ou du cloud.
        saver->save("PlayerLvl:10"); 
    }
};

// Utilisation :
// ISaver* monSaver = new CloudSaver();
// Game monJeu(monSaver);
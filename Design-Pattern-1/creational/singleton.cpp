#include <iostream>
#include <string>

class Logger {
public:
    // La méthode magique pour accéder à l'instance
    static Logger& getInstance() {
        // Cette variable statique est initialisée à la première exécution 
        // de la fonction, et détruite à la fin du programme.
        static Logger instance; 
        return instance;
    }

    // Une méthode métier normale
    void log(const std::string& msg) {
        std::cout << "[LOG] " << msg << std::endl;
    }

    // --- Verrouillage de la création ---
    // 1. On interdit la copie
    Logger(const Logger&) = delete; 
    // 2. On interdit l'assignation (ex: log1 = log2)
    void operator=(const Logger&) = delete;

private:
    // 3. Le constructeur est privé !
    Logger() { 
        std::cout << "Construction du Logger (une seule fois !)" << std::endl; 
    }
    
    // Destructeur privé ou public, selon si vous voulez gérer la destruction manuellement
    ~Logger() { 
        std::cout << "Destruction du Logger" << std::endl; 
    }
};

// --- UTILISATION ---
void fonctionQuelconque() {
    // On ne fait pas "new Logger()", on demande l'instance
    Logger::getInstance().log("Message depuis une fonction");
}

int main() {
    // Premier appel : le constructeur est appelé ici
    Logger::getInstance().log("Démarrage du programme");
    
    fonctionQuelconque();
    
    // Deuxième appel : on réutilise la même instance (pas de constructeur)
    Logger::getInstance().log("Fin du programme");
    
    return 0;
}
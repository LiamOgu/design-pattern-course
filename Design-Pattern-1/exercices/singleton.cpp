#include <iostream>
#include <string>
#include <map>

class GameConfig {
  public : 
    std::map<std::string, int> settings;
    static GameConfig& getInstance(){
      static GameConfig instance;
      return instance;
    }

    void setValue(const std::string& key, const int value){
      settings[key] = value;
    }

    int getValue(const std::string& key){
      return settings[key];
    }

    // --- Verrouillage de la création ---
    GameConfig(const GameConfig&) = delete; 
    void operator=(const GameConfig&) = delete;

  private:
    // Le constructeur est privé !
    GameConfig() { 
        std::cout << "Initialisation de la configuration" << std::endl; 
        settings["settings"] = 50;
        settings["difficulty"] = 2;

    }
    
    // Destructeur privé ou public, selon si vous voulez gérer la destruction manuellement
    ~GameConfig() { 
        std::cout << "Destruction du GameConfig" << std::endl; 
    }
};

int main() {
  GameConfig::getInstance().setValue("volume", 80);
  int v = GameConfig::getInstance().getValue("volume");

  GameConfig& ref1 = GameConfig::getInstance();
  GameConfig& ref2 = GameConfig::getInstance();
  
  std::cout << "La valeur est : " << v << std::endl;

  std::cout << "l'adresse de ref1 :" << &ref1 << std::endl;
  std::cout << "l'adresse de ref2 :" << &ref2 << std::endl;

  return 0;
};
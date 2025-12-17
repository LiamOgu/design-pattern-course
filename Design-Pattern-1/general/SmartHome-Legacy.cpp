// --- BAD CODE : A NE PAS REPRODUIRE ---
#include <iostream>
#include <string>
#include <vector>

// Une seule classe pour tout faire...
class Appareil {
public:
  std::string type;
  std::string nom;
  bool estAllume;
  int temperature;

  Appareil(std::string t, std::string n)
      : type(t), nom(n), estAllume(false), temperature(20) {}
};

class MaisonGodObject {
public:
  std::vector<Appareil *> listeAppareils;

  void ajouterAppareil(std::string type, std::string nom) {
    // PROBLÈME 1 : Utilisation directe de new, pas de flexibilité
    listeAppareils.push_back(new Appareil(type, nom));
  }

  void toutAllumer() {
    std::cout << "--- Activation Générale ---" << std::endl;
    for (auto a : listeAppareils) {
      // PROBLÈME 2 : Des if/else partout. Si on ajoute un "Volet", on doit
      // modifier ici.
      if (a->type == "LAMPE") {
        a->estAllume = true;
        std::cout << "Lampe " << a->nom << " allumee." << std::endl;
      } else if (a->type == "THERMOSTAT") {
        a->temperature = 22;
        std::cout << "Thermostat " << a->nom << " regle sur 22 degres."
                  << std::endl;
      }
      // Et si on a un detecteur de fumée ? Il n'a pas de "estAllume"...
    }
  }

  // PROBLÈME 3 : Pas de structure hiérarchique (pas de pièces)
  // PROBLÈME 4 : Pas de système de réaction (Observer).
  // Si il y a le feu, comment prévenir les volets de s'ouvrir ?
};

int main() {
  MaisonGodObject maMaison;
  maMaison.ajouterAppareil("LAMPE", "Entree");
  maMaison.ajouterAppareil("THERMOSTAT", "Salon");

  maMaison.toutAllumer();
  // Le code est "tombé en marche", mais il est impossible à maintenir.
  return 0;
}

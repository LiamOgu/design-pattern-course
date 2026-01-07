// Observer.cpp
// Exemple du patron de conception Observer avec une station météo

#include <algorithm> // Pour std::remove
#include <iostream>
#include <vector>

// --- 1. L'INTERFACE OBSERVER ---
// Tous ceux qui veulent écouter la station météo doivent implémenter ça.
class IObserver {
public:
  virtual void update(float temperature) = 0;
  virtual ~IObserver() = default;
};

// --- 2. LE SUJET (La Station) ---
class StationMeteo {
private:
  float temperature;
  // La liste de contacts (carnet d'adresses)
  std::vector<IObserver *> observateurs;

public:
  // Méthode pour s'abonner (Subscribe)
  void attach(IObserver *obs) { observateurs.push_back(obs); }

  // Méthode pour se désabonner (Unsubscribe)
  void detach(IObserver *obs) {
    // Astuce C++ pour supprimer un élément d'un vecteur
    observateurs.erase(
        std::remove(observateurs.begin(), observateurs.end(), obs),
        observateurs.end());
  }

  // La méthode magique qui prévient tout le monde
  void notify() {
    for (IObserver *obs : observateurs) {
      obs->update(temperature);
    }
  }

  // Méthode métier qui déclenche le processus
  void setTemperature(float temp) {
    std::cout << "\n--- La station mesure une nouvelle temperature : " << temp
              << "C ---" << std::endl;
    this->temperature = temp;
    notify(); // Hop, on prévient tout le monde !
  }
};

// --- 3. LES OBSERVATEURS CONCRETS ---
class EcranTelephone : public IObserver {
public:
  void update(float temperature) override {
    std::cout << ">> Telephone : Nouvelle notif ! Il fait " << temperature
              << " degres." << std::endl;
  }
};

class EcranMur : public IObserver {
public:
  void update(float temperature) override {
    std::cout << ">> Ecran Mur : Mise a jour affichage... [ " << temperature
              << "C ]" << std::endl;
  }
};

// --- 4. CODE CLIENT ---
int main() {
  StationMeteo station;

  EcranTelephone monTel;
  EcranMur monMur;

  // 1. Inscription
  station.attach(&monTel);
  station.attach(&monMur);

  // 2. Événement 1
  station.setTemperature(25.5);

  // 3. Désinscription dynamique
  std::cout << "\n(Le telephone se deconnecte du reseau...)" << std::endl;
  station.detach(&monTel);

  // 4. Événement 2
  station.setTemperature(26.0); // Seul le mur reçoit l'info

  return 0;
}

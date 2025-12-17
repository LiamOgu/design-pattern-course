// Strategy.cpp
// Exemple du patron de conception Strategy avec un GPS

#include <iostream>
#include <memory>
#include <string>

// --- 1. L'INTERFACE STRATEGY ---
// Elle définit "Ce qu'on veut faire" (aller d'un point A à B),
// mais pas "Comment on le fait".
class IItineraire {
public:
  virtual void construireRoute(const std::string &A,
                               const std::string &B) const = 0;
  virtual ~IItineraire() = default;
};

// --- 2. LES STRATÉGIES CONCRÈTES ---

class RouteVoiture : public IItineraire {
public:
  void construireRoute(const std::string &A,
                       const std::string &B) const override {
    std::cout << "Itineraire Voiture : Autoroutes et nationales entre " << A
              << " et " << B << "." << std::endl;
  }
};

class RoutePieton : public IItineraire {
public:
  void construireRoute(const std::string &A,
                       const std::string &B) const override {
    std::cout << "Itineraire Pieton : Trottoirs et parcs entre " << A << " et "
              << B << "." << std::endl;
  }
};

class RouteVelo : public IItineraire {
public:
  void construireRoute(const std::string &A,
                       const std::string &B) const override {
    std::cout << "Itineraire Velo : Pistes cyclables et sentiers entre " << A
              << " et " << B << "." << std::endl;
  }
};

// --- 3. LE CONTEXTE (Le GPS) ---
class GPS {
private:
  // Le GPS possède une stratégie, mais il ne sait pas laquelle (polymorphisme)
  std::unique_ptr<IItineraire> strategieActuelle;

public:
  // On peut définir une stratégie par défaut à la construction
  GPS(std::unique_ptr<IItineraire> strategie)
      : strategieActuelle(std::move(strategie)) {}

  // LE POINT CLÉ : On peut changer de cerveau à la volée !
  void setStrategie(std::unique_ptr<IItineraire> nouvelleStrategie) {
    std::cout << "\n>> Changement de mode de transport..." << std::endl;
    strategieActuelle = std::move(nouvelleStrategie);
  }

  void lancerNavigation(std::string depart, std::string arrivee) {
    if (strategieActuelle) {
      strategieActuelle->construireRoute(depart, arrivee);
    }
  }
};

// --- 4. CODE CLIENT ---
int main() {
  // 1. On démarre en Voiture
  std::unique_ptr<GPS> monGPS =
      std::make_unique<GPS>(std::make_unique<RouteVoiture>());
  monGPS->lancerNavigation("Paris", "Toulouse");

  // 2. On arrive en ville, on se gare, on passe en mode Piéton
  // Notez qu'on garde le MÊME objet GPS, on change juste son "cerveau"
  monGPS->setStrategie(std::make_unique<RoutePieton>());
  monGPS->lancerNavigation("Gare Matabiau", "Place du Capitole");

  // 3. On trouve un vélo libre-service
  monGPS->setStrategie(std::make_unique<RouteVelo>());
  monGPS->lancerNavigation("Place du Capitole", "Stadium de Toulouse");

  return 0;
}

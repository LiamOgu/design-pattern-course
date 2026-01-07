#include <iostream>
#include <memory>
#include <pthread.h>
#include <string>
#include <vector>

class IDevice {
public:
  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual ~IDevice() = default;
};

class Lampe : public IDevice {
private:
  std::string name;

public:
  Lampe(const std::string &n) : name(n) {}
  void execute() override {
    std::cout << "Lampe " << name << " allumee." << std::endl;
  }
  void undo() override {
    std::cout << "Lampe " << name << " eteinte." << std::endl;
  }
};

class Thermostat : public IDevice {
private:
  std::string name;
  float temperature;

public:
  Thermostat(const std::string &n, const float t = 20.0)
      : name(n), temperature(t) {}
  void execute() override {
    std::cout << "Thermostat " << name << " reglé sur " << temperature
              << " degres." << std::endl;
  }
  void undo() override {
    std::cout << "Thermostat " << name << " eteint." << std::endl;
  }
};

class Volet : public IDevice {
private:
  std::string name;

public:
  Volet(const std::string &n) : name(n) {}
  void execute() override {
    std::cout << "Volet " << name << " ouvert." << std::endl;
  }
  void undo() override {
    std::cout << "Volet " << name << " ferme." << std::endl;
  }
};

class DetecteurFumee : public IDevice {
private:
  bool smokeDetected = false;
  std::vector<IDevice *> observateurs;

public:
  void execute() override {
    std::cout << "Detecteur de fumée activé." << std::endl;
  }

  void undo() override {
    std::cout << "Detecteur de fumée desactivé." << std::endl;
  }

  void ajouterObservateur(IDevice *device) { observateurs.push_back(device); }

  void alertIncendie() {
    smokeDetected = true;
    std::cout << "!!! ALERTE INCENDIE !!!" << std::endl;

    for (IDevice *obs : observateurs) {
      obs->execute();
    }
  }
};

class Piece {
private:
  std::string name;
  std::vector<IDevice *> enfants;

public:
  Piece(const std::string &n) : name(n) {}
  void ajouter(IDevice *appareil) { enfants.push_back(appareil); }
  void allumer() {
    std::cout << "--- Activation des appareils dans la piece : " << name
              << " ---" << std::endl;
    for (auto appareil : enfants) {
      appareil->execute();
    }
  }
};

class DeviceFactory {
public:
  virtual ~DeviceFactory() = default;

  std::shared_ptr<IDevice> createDevice(const std::string &type,
                                        const std::string nom) {
    if (type == "light") {
      return std::make_shared<Lampe>(nom);
    } else if (type == "heat") {
      return std::make_shared<Thermostat>(nom);
    } else if (type == "smoke") {
      return std::make_shared<DetecteurFumee>();
    }

    // Pour ces lignes, j'ai demandé à l'IA une solution si le type entré n'est
    // ni light ni heat ni smoke. On retourne juste un pointeurnull
    std::cerr << "Type de device inconnu : " << type << std::endl;
    return nullptr;
  }
};

int main() {
  DeviceFactory factory;

  auto lampeSalon = factory.createDevice("light", "Salon");
  auto lampeChambre = factory.createDevice("light", "Chambre");
  auto thermostat = factory.createDevice("heat", "Maison");
  auto detecteur = factory.createDevice("smoke", "Detecteur");

  Piece salon("Salon");
  salon.ajouter(lampeSalon.get());
  salon.allumer();

  std::cout << std::endl;

  lampeChambre->execute();
  thermostat->execute();

  std::cout << std::endl;

  lampeChambre->undo();
  thermostat->undo();

  std::cout << std::endl;

  detecteur->execute();
  detecteur->undo();

  Volet voletSalon("Salon");
  Volet voletCuisine("Cuisine");

  // Pour ces lignes, j'ai demandé à l'IA de m'expliquer pourquoi je ne pouvais
  // pas appeler alertIncendie et ajouterObservateur normalement (ça marchais
  // pas) et il fallait utiliser dynamic_pointer_cast pour pouvoir transformer
  // shared_ptr<IDevice> en shared_ptr<DetecteurFumee> car c'était le fait
  // d'utiliser IDevice qui produisait l'erreur
  auto detecteurFumee = std::dynamic_pointer_cast<DetecteurFumee>(detecteur);
  if (detecteurFumee) {
    detecteurFumee->ajouterObservateur(&voletSalon);
    detecteurFumee->ajouterObservateur(&voletCuisine);

    std::cout << std::endl;
    detecteurFumee->alertIncendie();
  }

  return 0;
}

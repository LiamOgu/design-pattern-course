#include <iostream>
#include <memory>
#include <string>

class IArme {
public:
  virtual void utiliser() const = 0;
  virtual ~IArme() = default;
};

class Epee : public IArme {
  void utiliser() const override {
    std::cout << "Vlan ! Un coup d'épée tranchant" << std::endl;
  }
};

class Arc : public IArme {
  void utiliser() const override {
    std::cout << "Plan ! Une flèche en pleine tête" << std::endl;
  }
};

class SceptreMagique : public IArme {
  void utiliser() const override {
    std::cout << "Boum ! Une boule de feu" << std::endl;
  }
};

class Chevalier {
private:
  std::string nom;
  std::unique_ptr<IArme> arme;

public:
  Chevalier(const std::string &nom) : nom(nom) {}

  void equiper(std::unique_ptr<IArme> nouvelleArme) {
    std::cout << "\n>> Le chevalier change d'arme..." << std::endl;
    arme = std::move(nouvelleArme);
  };

  void attaquer() const {
    if (arme) {
      arme->utiliser();
    };
  };
};

int main() {

  Chevalier arthur = Chevalier("Arthur");
  arthur.equiper(std::make_unique<Epee>());
  arthur.attaquer();

  arthur.equiper(std::make_unique<Arc>());
  arthur.attaquer();

  arthur.equiper(std::make_unique<SceptreMagique>());
  arthur.attaquer();

  return 0;
}

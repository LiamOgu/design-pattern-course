#include <iostream>
#include <string>

// --- 1. COMPOSANT (Interface Commune) ---
class Arme {
public:
  virtual std::string getDescription() const = 0;
  virtual int getDegats() const = 0;
  virtual ~Arme() = default;
};

// --- 2. COMPOSANT CONCRET (L'objet de base) ---
class EpeeBasique : public Arme {
public:
  std::string getDescription() const override { return "Épée rouillée"; }

  int getDegats() const override { return 10; }
};

// --- 3. DECORATEUR DE BASE (La coquille vide) ---
class DecorateurArme : public Arme {
private:
  Arme *armeWrappee;

public:
  DecorateurArme(Arme *a) : armeWrappee(a) {};

  std::string getDescription() const override {
    return armeWrappee->getDescription();
  }
  int getDegats() const override { return armeWrappee->getDegats(); }
};

// --- 4. DECORATEURS CONCRETS (Les améliorations) ---
class RuneDeFeu : public DecorateurArme {
public:
  RuneDeFeu(Arme *a) : DecorateurArme(a) {}

  std::string getDescription() const override {
    return DecorateurArme::getDescription() + " +  de Feu";
  }
  int getDegats() const override { return DecorateurArme::getDegats() + 5; }
};

class Poison : public DecorateurArme {
public:
  Poison(Arme *a) : DecorateurArme(a) {}
  std::string getDescription() const override {
    return DecorateurArme::getDescription() + " +  Empoisonnée";
  }
  int getDegats() const override { return DecorateurArme::getDegats() + 2; }
};

int main() {
  EpeeBasique *epee = new EpeeBasique();

  std::cout << "Arme: " << epee->getDescription()
            << ", Dégâts: " << epee->getDegats() << std::endl;

  RuneDeFeu *epeeDeFeu = new RuneDeFeu(epee);

  std::cout << "Arme: " << epeeDeFeu->getDescription()
            << ", Dégâts: " << epeeDeFeu->getDegats() << std::endl;

  Poison *epeeDeFeuEtPoison = new Poison(epeeDeFeu);

  std::cout << "Arme: " << epeeDeFeuEtPoison->getDescription()
            << ", Dégâts: " << epeeDeFeuEtPoison->getDegats() << std::endl;

  delete epeeDeFeuEtPoison;
  delete epeeDeFeu;
  delete epee;

  return 0;
}

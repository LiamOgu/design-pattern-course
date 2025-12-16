#include <iostream>
#include <memory>

class Unite {
public:
  virtual void combattre() const = 0;
  virtual ~Unite() = default;
};

class Archer : public Unite {
public:
  void combattre() const override {
    std::cout << "L'archer tire une flèche" << std::endl;
  }
};

class Terminator : public Unite {
public:
  void combattre() const override {
    std::cout << "Le robot tire au laser" << std::endl;
  }
};

class Caserne {
public:
  virtual ~Caserne() = default;
  virtual std::unique_ptr<Unite> creerUnite() const = 0;

  void entrainer() const {
    std::unique_ptr<Unite> soldat = creerUnite();
    soldat->combattre();
  }
};

class CaserneHumaine : public Caserne {
public:
  std::unique_ptr<Unite> creerUnite() const override {
    return std::make_unique<Archer>();
  }
};

class CaserneRobot : public Caserne {
public:
  std::unique_ptr<Unite> creerUnite() const override {
    return std::make_unique<Terminator>();
  }
};

int main() {
  std::unique_ptr<Caserne> caserne;

  caserne = std::make_unique<CaserneHumaine>();
  caserne->entrainer();

  caserne = std::make_unique<CaserneRobot>();
  caserne->entrainer();

  return 0;
}

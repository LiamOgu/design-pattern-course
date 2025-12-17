#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IelementMenu {
public:
  virtual double getPrix() const = 0;
  virtual void afficher(int indentation) const = 0;

  virtual ~IelementMenu() = default;

protected:
  void printIndent(int indent) const {
    for (int i = 0; i < indent; ++i)
      std::cout << "  ";
  }
};

class PlatIndividuel : public IelementMenu {
private:
  std::string name;
  int price;

public:
  PlatIndividuel(const std::string &name, int price)
      : name(name), price(price) {};

  double getPrix() const override { return price; }

  void afficher(int indentation) const override {
    printIndent(indentation);
    std::cout << "- Plat: " << name << " (" << price << " €)" << std::endl;
  }
};

class MenuCombo : public IelementMenu {
private:
  std::string name;
  std::vector<std::shared_ptr<IelementMenu>> elements;

public:
  MenuCombo(std::string name,
            std::vector<std::shared_ptr<IelementMenu>> elements)
      : name(name), elements(elements) {}

  double getPrix() const override {
    double total = 0;
    for (const auto &element : elements) {
      total += element->getPrix();
    }
    return total;
  }

  void afficher(int indentation) const override {
    printIndent(indentation);
    std::cout << "- Menu Combo: " << name << " (" << getPrix() << " €)"
              << std::endl;
    for (const auto &element : elements) {
      element->afficher(indentation + 1);
    }
  }
};

int main() {
  auto plat1 = std::make_shared<PlatIndividuel>(std::string("BigBurger"), 8.5);
  auto plat2 =
      std::make_shared<PlatIndividuel>(std::string("Petites Frites"), 2.5);
  auto plat3 = std::make_shared<PlatIndividuel>(std::string("Soda"), 2);
  auto plat4 = std::make_shared<PlatIndividuel>(std::string("Café"), 1.5);

  return 0;
}

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
  float price;

public:
  PlatIndividuel(const std::string &name, float price)
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
  auto big_burger =
      std::make_shared<PlatIndividuel>(std::string("BigBurger"), 8.5);
  auto petites_frites =
      std::make_shared<PlatIndividuel>(std::string("Petites Frites"), 2.5);
  auto soda = std::make_shared<PlatIndividuel>(std::string("Soda"), 2);
  auto cafe = std::make_shared<PlatIndividuel>(std::string("Café"), 1.5);
  auto menu_classique = std::make_shared<MenuCombo>(
      std::string("Menu Classique"), std::vector<std::shared_ptr<IelementMenu>>{
                                         big_burger, petites_frites, soda});

  auto grosse_commande =
      std::make_shared<MenuCombo>(std::string("Grosse Commande"),
                                  std::vector<std::shared_ptr<IelementMenu>>{
                                      menu_classique, cafe, petites_frites});

  std::cout << "Affichage de la grosse commande :" << std::endl;
  grosse_commande->afficher(0);
  return 0;
}

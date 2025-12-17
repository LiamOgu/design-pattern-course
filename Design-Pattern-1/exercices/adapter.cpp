#include <iostream>
#include <memory>

class IRenderable {
public:
  virtual void draw() const = 0;
  virtual ~IRenderable() = default;
};

class VieuxRectangle {
public:
  void affiche(int x1, int y1, int x2, int y2) const {
    std::cout << "VieuxRectangle: Coin1(" << x1 << "," << y1 << ") Coin2(" << x2
              << "," << y2 << ")" << std::endl;
  }
};

class RectangleAdapter : public IRenderable {
private:
  std::unique_ptr<VieuxRectangle> vieuxRectangle;
  int x, y, largeur, hauteur;

public:
  RectangleAdapter(int x, int y, int w, int h)
      : x(x), y(y), largeur(w), hauteur(h) {
    vieuxRectangle = std::make_unique<VieuxRectangle>();
  }

  void draw() const override {
    std::cout << "[Adapter] Traduction de l'appel..." << std::endl;
    vieuxRectangle->affiche(x, y, x + largeur, y + hauteur);
  }
};

int main() {

  std::unique_ptr<IRenderable> shape =
      std::make_unique<RectangleAdapter>(10, 10, 10, 10);
  shape->draw();

  return 0;
}

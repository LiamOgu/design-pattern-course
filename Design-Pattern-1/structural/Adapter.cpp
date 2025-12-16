#include <iostream>
#include <memory>

// --- 1. TARGET (Ce que votre code attend) ---
class Forme {
public:
    virtual void dessiner() const = 0;
    virtual ~Forme() = default;
};

// --- 2. ADAPTEE (L'ancienne classe incompatible) ---
// Imaginez que c'est une librairie tierce non modifiable
class VieuxCarre {
public:
    void afficherCarre(int x, int y, int cote) const {
        std::cout << "VieuxCarre: Coin(" << x 
        << "," << y << ") Côté: " << cote << std::endl;
    }
};

// --- 3. ADAPTER (Le traducteur) ---
class CarreAdapter : public Forme {
private:
    // L'adaptateur "enveloppe" l'objet incompatible
    std::unique_ptr<VieuxCarre> vieuxCarre;
    int size;

public:
    CarreAdapter(int w) : size(w) {
        vieuxCarre = std::make_unique<VieuxCarre>();
    }

    void dessiner() const override {
        // TRADUCTION : On convertit l'appel 'dessiner' en 'afficherCarre'
        // On décide arbitrairement des coordonnées 0,0 car Forme n'en a pas
        std::cout << "[Adapter] Traduction de l'appel..." << std::endl;
        vieuxCarre->afficherCarre(0, 0, size);
    }
};

// --- CLIENT ---
void lancerGraphismes(const Forme& f) {
    f.dessiner();
}

int main() {
    CarreAdapter monCarre(10);
    
    // La fonction lancerGraphismes croit manipuler une "Forme" standard.
    // En coulisses, c'est le VieuxCarre qui bosse.
    lancerGraphismes(monCarre);
    
    return 0;
}
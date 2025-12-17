#include <iostream>
#include <memory> // Pour std::shared_ptr
#include <string>
#include <vector>

// --- 1. COMPONENT (L'interface commune) ---
class FileSystemNode {
public:
  virtual int getSize() const = 0;
  virtual void afficher(int indentation = 0) const = 0;
  virtual ~FileSystemNode() = default;

protected:
  // Utilitaire pour afficher des jolis espaces
  void printIndent(int indent) const {
    for (int i = 0; i < indent; ++i)
      std::cout << "  ";
  }
};

// --- 2. LEAF (La feuille : L'objet simple) ---
class Fichier : public FileSystemNode {
private:
  std::string nom;
  int taille;

public:
  Fichier(std::string n, int t) : nom(n), taille(t) {}

  int getSize() const override { return taille; }

  void afficher(int indentation) const override {
    printIndent(indentation);
    std::cout << "- Fichier: " << nom << " (" << taille << " ko)" << std::endl;
  }
};

// --- 3. COMPOSITE (Le conteneur) ---
class Dossier : public FileSystemNode {
private:
  std::string nom;
  // LA CLÉ EST ICI : Le dossier contient une liste de l'INTERFACE (pas des
  // classes concrètes) Il peut donc contenir des Fichiers ET des Dossiers
  // indifféremment.
  std::vector<std::shared_ptr<FileSystemNode>> enfants;

public:
  Dossier(std::string n) : nom(n) {}

  // Méthode spécifique pour ajouter des éléments
  void ajouter(std::shared_ptr<FileSystemNode> composant) {
    enfants.push_back(composant);
  }

  // Le calcul récursif de la taille
  int getSize() const override {
    int total = 0;
    for (const auto &enfant : enfants) {
      // L'appel polymorphique magique :
      // Si l'enfant est un fichier -> renvoie sa taille
      // Si l'enfant est un dossier -> renvoie la somme de ses enfants
      // (récursion)
      total += enfant->getSize();
    }
    return total;
  }

  void afficher(int indentation) const override {
    printIndent(indentation);
    std::cout << "+ Dossier: " << nom << " (Total: " << getSize() << " ko)"
              << std::endl;

    // On demande aux enfants de s'afficher (avec un cran d'indentation en plus)
    for (const auto &enfant : enfants) {
      enfant->afficher(indentation + 1);
    }
  }
};

// --- CODE CLIENT ---
int main() {
  // 1. On crée des feuilles (Fichiers)
  auto f1 = std::make_shared<Fichier>("Photo.jpg", 200);
  auto f2 = std::make_shared<Fichier>("CV.pdf", 50);
  auto f3 = std::make_shared<Fichier>("Musique.mp3", 500);

  // 2. On crée des composites (Dossiers)
  auto dossierRacine = std::make_shared<Dossier>("Mes Documents");
  auto sousDossier = std::make_shared<Dossier>("Projet Secret");

  // 3. On assemble l'arbre
  // Le sous-dossier contient un fichier
  sousDossier->ajouter(f2); // CV.pdf

  // La racine contient deux fichiers et le sous-dossier
  dossierRacine->ajouter(f1);          // Photo
  dossierRacine->ajouter(f3);          // Musique
  dossierRacine->ajouter(sousDossier); // Dossier imbriqué

  // 4. Appel unique
  std::cout << "--- Structure du Disque ---" << std::endl;
  // Le client n'a pas besoin de savoir qu'il y a une structure complexe en
  // dessous. Il appelle juste 'afficher'.
  dossierRacine->afficher(1);

  return 0;
}

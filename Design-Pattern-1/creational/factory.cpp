#include <iostream>
#include <memory> // Pour std::unique_ptr

// --- 1. L'INTERFACE DU PRODUIT ---
class ITransport {
public:
    virtual void livrer() const = 0;
    virtual ~ITransport() = default; // Toujours un destructeur virtuel !
};

// --- 2. LES PRODUITS CONCRETS ---
class Camion : public ITransport {
public:
    void livrer() const override {
        std::cout << "Livraison par la route dans un carton." << std::endl;
    }
};

class Bateau : public ITransport {
public:
    void livrer() const override {
        std::cout << "Livraison par la mer dans un conteneur." << std::endl;
    }
};

// --- 3. LE CRÉATEUR (La classe métier) ---
class Logistique {
public:
    virtual ~Logistique() = default;

    // VOICI LA FACTORY METHOD
    // Elle est "virtual pure" ici, forçant les sous-classes à l'implémenter.
    virtual std::unique_ptr<ITransport> creerTransport() const = 0;

    // LA LOGIQUE MÉTIER
    // Notez bien : cette fonction ne sait pas si elle utilise un camion ou un bateau.
    // Elle travaille uniquement avec l'interface ITransport.
    void planifierLivraison() const {
        // Appel de la fabrique pour obtenir un objet
        std::unique_ptr<ITransport> transport = creerTransport();
        
        // Utilisation de l'objet
        std::cout << "Logistique : Début du processus..." << std::endl;
        transport->livrer();
    }
};

// --- 4. LES CRÉATEURS CONCRETS ---
class LogistiqueRoute : public Logistique {
public:
    // Implémentation de la fabrique : on retourne un Camion
    std::unique_ptr<ITransport> creerTransport() const override {
        return std::make_unique<Camion>();
    }
};

class LogistiqueMer : public Logistique {
public:
    // Implémentation de la fabrique : on retourne un Bateau
    std::unique_ptr<ITransport> creerTransport() const override {
        return std::make_unique<Bateau>();
    }
};

// --- CODE CLIENT ---
int main() {
    std::cout << "--- Client : Je veux une livraison par la route ---" << std::endl;
    // On instancie le créateur spécifique
    std::unique_ptr<Logistique> societeA = std::make_unique<LogistiqueRoute>();
    // La magie opère ici : planifierLivraison utilise un Camion sans le savoir
    societeA->planifierLivraison();

    std::cout << "\n--- Client : Je veux une livraison par la mer ---" << std::endl;
    std::unique_ptr<Logistique> societeB = std::make_unique<LogistiqueMer>();
    societeB->planifierLivraison();
    
    return 0;
}
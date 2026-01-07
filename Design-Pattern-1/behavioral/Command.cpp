// Command.cpp
// Exemple du patron de conception Command avec fonctionnalité d'annulation
// (Ctrl+Z)

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// --- 1. RECEIVER (Celui qui fait le vrai travail) ---
class Lampe {
private:
  std::string lieu;

public:
  Lampe(std::string l) : lieu(l) {}

  void allumer() {
    std::cout << "La lampe du " << lieu << " s'allume." << std::endl;
  }

  void eteindre() {
    std::cout << "La lampe du " << lieu << " s'eteint." << std::endl;
  }
};

// --- 2. INTERFACE COMMAND ---
class ICommand {
public:
  virtual void execute() = 0;
  virtual void undo() = 0; // La clé du Ctrl+Z
  virtual ~ICommand() = default;
};

// --- 3. CONCRETE COMMANDS ---

// Commande pour allumer
class AllumerLampeCommand : public ICommand {
private:
  // La commande doit savoir QUI elle contrôle
  Lampe &lampe;

public:
  AllumerLampeCommand(Lampe &l) : lampe(l) {}

  void execute() override { lampe.allumer(); }

  void undo() override {
    // Pour annuler "Allumer", il faut faire "Eteindre"
    lampe.eteindre();
  }
};

// Commande pour éteindre
class EteindreLampeCommand : public ICommand {
private:
  Lampe &lampe;

public:
  EteindreLampeCommand(Lampe &l) : lampe(l) {}

  void execute() override { lampe.eteindre(); }

  void undo() override {
    // Pour annuler "Eteindre", il faut faire "Allumer"
    lampe.allumer();
  }
};

// --- 4. INVOKER (La Télécommande) ---
class Telecommande {
private:
  // Historique des commandes exécutées
  std::vector<std::shared_ptr<ICommand>> historique;

public:
  // Le bouton ne sait pas ce qu'il fait, il exécute juste une commande qu'on
  // lui donne
  void appuyerBouton(std::shared_ptr<ICommand> cmd) {
    cmd->execute();
    // On stocke la commande dans l'historique
    historique.push_back(cmd);
  }

  void boutonAnnuler() {
    if (!historique.empty()) {
      std::cout << ">> [CTRL+Z] Annulation de la derniere action..."
                << std::endl;
      // On récupère la dernière commande
      std::shared_ptr<ICommand> derniereCmd = historique.back();
      // On l'annule
      derniereCmd->undo();
      // On la retire de l'historique
      historique.pop_back();
    } else {
      std::cout << "Rien a annuler !" << std::endl;
    }
  }
};

// --- CODE CLIENT ---
int main() {
  // Le matériel
  Lampe salon("Salon");
  Lampe cuisine("Cuisine");

  // Les commandes (les objets actions)
  auto cmdSalonOn = std::make_shared<AllumerLampeCommand>(salon);
  auto cmdCuisineOn = std::make_shared<AllumerLampeCommand>(cuisine);
  auto cmdSalonOff = std::make_shared<EteindreLampeCommand>(salon);

  // L'utilisateur (La télécommande)
  Telecommande remote;

  // Scénario
  remote.appuyerBouton(cmdSalonOn);   // Allume Salon
  remote.appuyerBouton(cmdCuisineOn); // Allume Cuisine
  remote.appuyerBouton(cmdSalonOff);  // Eteint Salon

  std::cout << "\n--- Oups, je voulais garder le salon allume ! ---"
            << std::endl;
  remote.boutonAnnuler(); // Annule "Eteindre Salon" -> Rallume Salon

  std::cout << "\n--- Et je veux eteindre la cuisine aussi finalement ---"
            << std::endl;
  remote.boutonAnnuler(); // Annule "Allumer Cuisine" -> Eteint Cuisine

  return 0;
}

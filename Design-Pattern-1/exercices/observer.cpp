#include <algorithm>
#include <iostream>
#include <vector>

class IAbonne {
public:
  virtual void reagir(const std::string nomChaine,
                      const std::string titreVideo) const = 0;
  virtual ~IAbonne() = default;
};

class ChaineYoutube {
private:
  std::string nom;
  std::vector<IAbonne *> abonnes;

public:
  ChaineYoutube(const std::string &nom) : nom(nom) {};
  void sAbonner(IAbonne *a) { abonnes.push_back(a); };

  void seDesabonner(IAbonne *a) {
    abonnes.erase(std::remove(abonnes.begin(), abonnes.end(), a),
                  abonnes.end());
  };

  void posterVideo(std::string titre) {
    for (IAbonne *abonne : abonnes) {
      abonne->reagir(nom, titre);
    };
  }
};

class Utilisateur : public IAbonne {
private:
  std::string prenom;

public:
  Utilisateur(const std::string &prenom) : prenom(prenom) {};
  void reagir(std::string nomChaine, std::string titreVideo) const override {
    std::cout << prenom << " a reçu une notification de la chaîne " << nomChaine
              << " Titre de la vidéo : " << titreVideo << std::endl;
  };
};

int main() {
  ChaineYoutube MisterBeast("MisterBeast");
  Utilisateur Alice("Alice");
  Utilisateur Bob("Bob");
  Utilisateur Charlie("Charlie");

  MisterBeast.sAbonner(&Alice);
  MisterBeast.sAbonner(&Bob);
  MisterBeast.posterVideo("J'offre une île !");

  MisterBeast.sAbonner(&Charlie);
  MisterBeast.seDesabonner(&Bob);

  MisterBeast.posterVideo("Je mange un burger en or");
  return 0;
};

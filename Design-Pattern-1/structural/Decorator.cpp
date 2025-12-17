#include <iostream>
#include <string>

// --- 1. COMPONENT (Interface Commune) ---
class INotifier {
public:
  virtual void send(const std::string &msg) const = 0;
  virtual ~INotifier() = default;
};

// --- 2. CONCRETE COMPONENT (L'objet de base) ---
class EmailNotifier : public INotifier {
public:
  void send(const std::string &msg) const override {
    std::cout << "Email envoyé : " << msg << std::endl;
  }
};

// --- 3. BASE DECORATOR (La coquille vide) ---
class NotifierDecorator : public INotifier {
protected:
  // Il possède un pointeur vers le composant qu'il décore
  // (Note: on utilise un pointeur brut ou shared_ptr ici pour l'exemple de
  // chainage, unique_ptr est plus complexe à gérer dans des chaînes dynamiques)
  INotifier *wrappee;

public:
  NotifierDecorator(INotifier *n) : wrappee(n) {}

  void send(const std::string &msg) const override {
    // Par défaut, il délègue juste le travail au suivant
    wrappee->send(msg);
  }
};

// --- 4. CONCRETE DECORATORS (Les options) ---

class SMSDecorator : public NotifierDecorator {
public:
  SMSDecorator(INotifier *n) : NotifierDecorator(n) {}

  void send(const std::string &msg) const override {
    // 1. On fait le travail de base (Email ou autre décorateur)
    NotifierDecorator::send(msg);
    // 2. On ajoute notre comportement
    std::cout << "SMS envoyé : " << msg << std::endl;
  }
};

class FacebookDecorator : public NotifierDecorator {
public:
  FacebookDecorator(INotifier *n) : NotifierDecorator(n) {}

  void send(const std::string &msg) const override {
    NotifierDecorator::send(msg);
    std::cout << "Facebook Post : " << msg << std::endl;
  }
};

// --- CLIENT ---
int main() {
  // 1. On crée le service de base
  EmailNotifier *email = new EmailNotifier();

  // 2. On veut ajouter les SMS
  SMSDecorator *emailAndSMS = new SMSDecorator(email);

  // 3. On veut AUSSI Facebook (on emballe/enveloppe le précédent)
  FacebookDecorator *allNotifiers = new FacebookDecorator(emailAndSMS);

  std::cout << "--- Envoi d'une alerte critique ---" << std::endl;
  // L'appel traverse toute la chaîne : Facebook -> SMS -> Email
  allNotifiers->send("Serveur en feu !");

  // Nettoyage (Simplifié pour l'exemple, en vrai : smart pointers)
  delete allNotifiers; // Attention à bien gérer la chaîne de destruction
  delete emailAndSMS;  // Ici c'est risqué sans smart pointers bien pensés !
  delete email;

  return 0;
}

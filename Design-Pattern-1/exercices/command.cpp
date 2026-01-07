#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// --- 1. RECEIVER (Celui qui fait le vrai travail) ---
class Robot {
private:
  std::string nom;

public:
  Robot(const std::string nom) : nom(nom) {};
  void sauter() { std::cout << "Le robot saute." << std::endl; };

  void atterrir() { std::cout << "Le robot atterrit." << std::endl; };

  void tirerLaser() {
    std::cout << "Le robot tire avec son laser." << std::endl;
  };

  void absorberLaser() {
    std::cout << "Le robot absorbe le tir laser." << std::endl;
  };
};

// --- 2. INTERFACE COMMAND ---
class ICommand {
public:
  virtual void execute() const = 0;
  virtual void undo() const = 0;
  virtual ~ICommand() = default;
};

// --- 3. CONCRETE COMMANDS ---
class CommandeSaut : public ICommand {
private:
  Robot &robot;

public:
  CommandeSaut(Robot &r) : robot(r) {};
  void execute() const override { robot.sauter(); }
  void undo() const override { robot.atterrir(); }
};

class CommandeTir : public ICommand {
private:
  Robot &robot;

public:
  CommandeTir(Robot &r) : robot(r) {};
  void execute() const override { robot.tirerLaser(); }
  void undo() const override { robot.absorberLaser(); }
};

// --- 4. INVOKER ---
class ManettePro {
private:
  std::map<char, std::shared_ptr<ICommand>> touches;
  std::vector<std::shared_ptr<ICommand>> historique;

public:
  void assignerTouche(char touche, std::shared_ptr<ICommand> cmd) {
    touches[touche] = cmd;
  };

  void appuyerSur(char touche) {
    touches[touche]->execute();
    historique.push_back(touches[touche]);
  };

  void replayForward() {
    for (const auto &cmd : historique) {
      cmd->execute();
    }
  }

  void replayBackward() {
    for (auto i = historique.rbegin(); i != historique.rend(); i++) {
      auto cmd = *i;
      cmd->undo();
    }
  }
};

int main() {
  Robot robot = Robot("Z-42");
  ManettePro manette = ManettePro();
  manette.assignerTouche('A', std::make_shared<CommandeSaut>(robot));
  manette.assignerTouche('B', std::make_shared<CommandeTir>(robot));
  manette.appuyerSur('A');
  manette.appuyerSur('B');
  manette.appuyerSur('A');
  manette.appuyerSur('B');
  manette.appuyerSur('B');
  manette.appuyerSur('A');

  std::cout << "---REPLAY AVANT---" << std::endl;
  manette.replayForward();

  std::cout << "---REPLAY AVANT---" << std::endl;
  manette.replayForward();

  std::cout << "---REPLAY ARRIERE---" << std::endl;
  manette.replayBackward();
}

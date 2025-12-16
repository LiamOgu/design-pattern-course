#include <iostream>
#include <string>

// --- 1. LE PRODUIT COMPLEXE ---
class Computer {
public:
    // Beaucoup d'attributs, certains obligatoires, d'autres optionnels
    std::string cpu;
    std::string gpu;
    int ram_gb;
    int storage_gb;
    bool hasWifi;
    bool hasCooling;

    void afficherSpecs() const {
        std::cout << "--- PC SPECS ---" << std::endl;
        std::cout << "CPU: " << cpu << " | GPU: " << gpu << std::endl;
        std::cout << "RAM: " << ram_gb << "GB | SSD: " << storage_gb << "GB" << std::endl;
        std::cout << "WiFi: " << (hasWifi ? "Oui" : "Non") << std::endl;
        std::cout << "Watercooling: " << (hasCooling ? "Oui" : "Non") << std::endl;
        std::cout << "----------------" << std::endl;
    }
};

// --- 2. LE BUILDER ---
class ComputerBuilder {
private:
    // Le Builder contient une instance temporaire du produit
    Computer computer;
    // Constructeur par défaut inaccessible 
    ComputerBuilder() = delete;    
    // On interdit la copie du Builder pour éviter des erreurs
    ComputerBuilder(const ComputerBuilder&) = delete;
    void operator=(const ComputerBuilder&) = delete;

public:
    // On peut forcer les paramètres obligatoires dans le constructeur du Builder
    ComputerBuilder(const std::string& cpu, int ram) {
        computer.cpu = cpu;
        computer.ram_gb = ram;
        // Valeurs par défaut
        computer.gpu = "Integrated";
        computer.storage_gb = 256;
        computer.hasWifi = false;
        computer.hasCooling = false;
    }

    // --- MÉTHODES DE CONSTRUCTION (CHAINABLES) ---
    
    ComputerBuilder& setGPU(const std::string& gpuModel) {
        computer.gpu = gpuModel;
        return *this; // L'astuce est ici : on retourne l'objet lui-même
    }

    ComputerBuilder& setStorage(int gb) {
        computer.storage_gb = gb;
        return *this;
    }

    ComputerBuilder& withWifi() {
        computer.hasWifi = true;
        return *this;
    }

    ComputerBuilder& withWaterCooling() {
        computer.hasCooling = true;
        return *this;
    }

    // --- ÉTAPE FINALE : RÉCUPÉRATION DU PRODUIT ---
    Computer build() {
        return computer;
    }
};

void construirePCGamerStandard(ComputerBuilder& builder) {
    builder.setGPU("RTX 4070")
           .setStorage(1024)
           .withWaterCooling();
}

// --- 3. CODE CLIENT ---
int main() {
    std::cout << "Construction d'un PC Bureautique :" << std::endl;
    // Syntaxe fluide et lisible
    Computer officePC = ComputerBuilder("Intel i3", 8)
                        .setStorage(512)
                        .withWifi()
                        .build();
    officePC.afficherSpecs();

    std::cout << "\nConstruction d'un PC Gamer :" << std::endl;
    Computer gamerPC = ComputerBuilder("AMD Ryzen 9", 32)
                       .setGPU("Nvidia RTX 4090")
                       .setStorage(2000)
                       .withWaterCooling()
                       .build();
    gamerPC.afficherSpecs();

    std::cout << "\nConstruction d'un PC Gamer Standard via fonction :" << std::endl;
    ComputerBuilder builder("AMD Ryzen 7", 16);
    construirePCGamerStandard(builder);
    Computer standardGamerPC = builder.build();
    standardGamerPC.afficherSpecs();

    return 0;
}
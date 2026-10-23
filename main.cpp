#include <iostream>

using namespace std;
#include <iostream>
#include <string>
#include <algorithm>

class CompteBancaire {
private:
    std::string numero;
    double solde;
    std::string* historique;
    std::size_t capacite;
    std::size_t nbOps;
    void agrandirHistorique() {
        std::size_t nouvelleCap = capacite * 2;
        std::string* nouveau = new std::string[nouvelleCap];
        std::copy(historique, historique + nbOps, nouveau);
        delete[] historique;
        historique = nouveau;
        capacite = nouvelleCap;
    }
    void ajouterOperation(const std::string& op) {
        if (nbOps == capacite) agrandirHistorique();
        historique[nbOps++] = op;
    }
public:
    // Constructeur par défaut
    CompteBancaire() : numero("NON_DEFINI"), solde(0.0), capacite(10), nbOps(0) {
        historique = new std::string[capacite];
    }
    // Constructeur paramétré
    CompteBancaire(const std::string& num, double s) : numero(num), solde(s), capacite(10), nbOps(0) {
        historique = new std::string[capacite];
        ajouterOperation("Création du compte avec solde " + std::to_string(s));
    }
    // Constructeur de copie
    CompteBancaire(const CompteBancaire& other) : numero(other.numero), solde(other.solde), capacite(other.capacite), nbOps(other.nbOps) {
        historique = new std::string[capacite];
        std::copy(other.historique, other.historique + nbOps, historique);
    }
    // Constructeur de déplacement
    CompteBancaire(CompteBancaire&& other) noexcept : numero(std::move(other.numero)), solde(other.solde), historique(other.historique), capacite(other.capacite), nbOps(other.nbOps) {
        other.historique = nullptr;
        other.nbOps = other.capacite = 0;
        other.solde = 0.0;
    }
    // Destructeur
    ~CompteBancaire() {
        delete[] historique;
    }
    // Méthodes de gestion du compte
    void deposer(double montant) {
        if (montant <= 0) {
            std::cerr << "Montant de dépôt invalide" << std::endl;
            return;
        }
        solde += montant;
        ajouterOperation("Dépot de " + std::to_string(montant));
    }
    void retirer(double montant) {
        if (montant <= 0 || montant > solde) {
            std::cerr << "Retrait impossible" << std::endl;
            return;
        }
        solde -= montant;
        ajouterOperation("Retrait de " + std::to_string(montant));
    }
    void afficher() const {
        std::cout << "Compte " << numero << " - Solde : " << solde << std::endl;
        std::cout << "Historique des opérations :" << std::endl;
        for (std::size_t i = 0; i < nbOps; ++i) {
            std::cout << "  " << historique[i] << std::endl;
        }
    }
};

int main() {
    CompteBancaire c1("FR123456", 500.0);
    c1.deposer(200);
    c1.retirer(150);
    c1.afficher();
    // Test du constructeur de copie
    CompteBancaire c2 = c1;
    c2.afficher();
    // Test du déplacement
    CompteBancaire c3 = std::move(c1);
    c3.afficher();
    return 0;
}

// Hande Köksal Section-1 22401938

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using std::string;

class Player {
private:
    string name;
    int id;
    int score;
    int noOfCards;
    string* cards;

public:
    Player();
    Player(const string& name, int id);
    Player(const Player& original);
    ~Player();

    string getName() const;
    int getId() const;
    int getNoOfCards() const;
    string* getCards() const;
    void switchCards(Player*& switchPlayer);
    void addCard(string card);
    void removeCard(string card);
    void listCards() const;
    bool hasCard(string card);
};

#endif
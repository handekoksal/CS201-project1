// Hande Köksal Section-1 22401938

#include <iostream>
#include "Player.h"
using namespace std;

// Default constructor
Player::Player() {
    this->cards = nullptr;
}

// Constructor
Player::Player(const string& name, int id) {
    this->name = name;
    this->id = id;
    this->noOfCards = 0;
    this->cards = nullptr;
}

// Copy constructor
Player::Player(const Player& original) {
    this->name = original.getName();
    this->id = original.getId();
    this->noOfCards = original.getNoOfCards();
    this->cards = original.getCards();
}

// Destructor
Player::~Player() {
    // Dynamically allocated array
    delete[] cards;
}

// Getters and setters 

string Player::getName() const {
    return name;
}

int Player::getId() const {
    return id;
}

int Player::getNoOfCards() const {
    return noOfCards;
}

// For the swap function
string* Player::getCards() const {
    return cards;
}

// For the swap function
void Player::switchCards(Player*& switchPlayer) {
    // For switching cards
    string* tempCards = this->cards;
    this->cards = switchPlayer->cards;
    switchPlayer->cards = tempCards;

    // For switching noOfCards
    int tempNo = this->noOfCards;
    this->noOfCards = switchPlayer->noOfCards;
    switchPlayer->noOfCards = tempNo;
}

// Adds a card to the player's cards array
void Player::addCard(string card) {
    string* newArray = new string[noOfCards+1];

    for (int i = 0; i < noOfCards; i++) {
        newArray[i] = cards[i];
    }
    newArray[noOfCards] = card;
    
    delete[] cards;
    cards = newArray;
    noOfCards++;
}

// Removes a card from player's cards array
void Player::removeCard(string card) {
    int removedIndex = -1;

    for (int i = 0; i < noOfCards; i++) {
        if (cards[i] == card) {
            removedIndex = i;
            break;
        }
    }

    // If the player doesn't have the given card in her/his hand
    if (removedIndex == -1) {
        cout << name << " doesn't have the card " << card << endl;
        return;
    }

    string* newArray = new string[noOfCards-1];

    int copiedIndex = 0;
    for (int i = 0; i < noOfCards; i++) {
        // Copying every card except for the removed one
        if (i != removedIndex) {
            newArray[copiedIndex] = cards[i];
            copiedIndex++;
        }
    }

    delete[] cards;
    cards = newArray;
    noOfCards--;
}

// For listing the cards of the player
void Player::listCards() const {
    if (noOfCards == 0) {
        cout << name << " does not have any cards." << endl;
        return;
    }

    cout << "Cards of " << name << ": [";
    for (int i = 0; i < noOfCards; i++) {
        // If we're printing the last element
        if (i == noOfCards - 1) {
            cout << cards[i] << "]" << endl;
        }

        // If we're not printing the last element
        else {
            cout << cards[i] << ", ";
        }
    }
}

bool Player::hasCard(string card) {
    for (int i = 0; i < noOfCards; i++) {
        if (cards[i] == card) {
            return true;
        }
    }
    return false;
}

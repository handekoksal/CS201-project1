// Hande Köksal Section-1 22401938

#include <iostream>
#include "MagicCard.h"
#include "Player.h"
#include <string>
using std::string;
using namespace std;

MagicCard::MagicCard() {
    this->playerSize=0;
    this->allPlayers = nullptr;
    this->drawSize = 0;
    this->drawPile = nullptr;
    this->discardSize = 0;
    this->discardPile = nullptr;
}

MagicCard::~MagicCard() {
    // Calling delete[] on dynamically allocated arrays
    delete[] allPlayers;
    delete[] drawPile,
    delete[] discardPile;
}

void MagicCard::addPlayer(const int playerID, const string name) {
    for (int i = 0; i < playerSize; i++) {
        // If player already exists
        if (allPlayers[i].getId() == playerID) {
            cout << "Cannot add player. ID " << playerID << " already exists." << endl;
            return;
        }
    }

    Player player = Player(name, playerID);
    // Adding the player and upgrading the arrays accordingly
    // Adding the player by id so the array will always be sorted

    int newPlayerIndex = 0;
    while (newPlayerIndex < playerSize && allPlayers[newPlayerIndex].getId() < player.getId()) {
        newPlayerIndex++;
    }

    Player* newArray = new Player[playerSize + 1];

    // Copy elements before newPlayerIndex
    for (int i = 0; i < newPlayerIndex; ++i) {
        newArray[i] = allPlayers[i];
    }

    // Insert the new player
    newArray[newPlayerIndex] = player;

    // Copy remaining players
    for (int i = newPlayerIndex; i < playerSize; i++) {
        newArray[i + 1] = allPlayers[i];
    }
    delete[] allPlayers;
    allPlayers = newArray;
    playerSize++;
    cout << "Added player " << name << " with ID " << playerID << "." << endl;
}

void MagicCard::removePlayer(const int playerID) {
    // Giving -1 as the index to understand if the player exists or not
    int removedPlayerIndex = -1;
    for (int i = 0; i < playerSize; i++) {
        // Removing the player and upgrading the arrays accordingly
        if (allPlayers[i].getId() == playerID) {
            removedPlayerIndex = i;
            break;
        }
    }

    // If the given index didn't change
    if (removedPlayerIndex == -1) {
        cout << "Cannot remove player. There is no player with ID " << playerID << "." << endl;
        return;
    }

    // Removing the player's pointer and upgrading the array accordingly
    Player* newArray = new Player[playerSize-1];

    // We need a counter for the new array's indexes
    int copiedIndex = 0;
    for (int i = 0; i < playerSize; i++) {
        // Copying every player except for the removed one
        if (i != removedPlayerIndex) {
            newArray[copiedIndex] = allPlayers[i];
            copiedIndex++;
        }
    }

    delete[] allPlayers;
    allPlayers = newArray;
    playerSize--;
    cout << "Removed player " << playerID << "." << endl;    
}

void MagicCard::printPlayers() const{
    if (playerSize == 0) {
        cout << "Cannot print players. There is no player in the game." << endl;
        return;
    }

    // allPlayers array is already sorted by id
    // This was done in the addPlayer function
    cout << "Players :" << endl;
    for (int i = 0; i < playerSize; i++) {
        cout << "Player " << allPlayers[i].getId() << " : " << allPlayers[i].getName() << endl;
    }
}

void MagicCard::setDrawPile( const string drawPile[], const int size ) {
    drawSize = size;
    string* newArray = new string[drawSize];

    // this->drawPile is the draw pile array for this class
    // drawPile is the parameter (not to confuse the two)
    for (int i = 0; i < size; i++) {
        (newArray)[i] = drawPile[i];
    }

    // The parameter will be gone automatically but this->drawPile is dynamically allocated
    // so we need to call its destructor 
    delete[] this->drawPile;
    this->drawPile = newArray;
    cout << "Draw pile has been initialized." << endl;
}

void MagicCard::drawCardFromDeck( const int playerID, const int n ) {

    // If n is not a valid index
    if (n < 0 || n >= drawSize) {
        cout << "Cannot draw card. The input index is not valid." << endl;
        return;
    }

    // Going through the array of players
    for (int i = 0; i < playerSize; i++) {
        // If the given ID matches some player's ID
        if (allPlayers[i].getId() == playerID) {

            // Adding the card to the player's cards array
            allPlayers[i].addCard(drawPile[n]);
            cout << allPlayers[i].getName() << " drew card " << drawPile[n] << " from the draw pile." << endl;
            
            // Removing drawPile[n] from the drawPile array
            string* newArray = new string[drawSize-1];

            int copiedIndex = 0;
            for (int i = 0; i < n; i++) {
                newArray[i] = drawPile[i];
                copiedIndex++;
            }
            for (int i = n+1; i < drawSize; i++) {
                newArray[copiedIndex] = drawPile[i];
                copiedIndex++;
            }

            delete[] drawPile;
            drawPile = newArray;
            drawSize--;
            return;
        }
    }

    // If the given ID doesn't match any of the player's ID's
    cout << "No player with ID" << playerID << "." << endl;

}

void MagicCard::drawCardForMismatch(Player& player, const string& drawnCard) {
    // Only removing the drawPile[0] from drawPile array
    // This is a specific function to differ drawing the first card from the array in the play function 
    // from the actual drawCardFromDeck function
    player.addCard(drawnCard);
    
    // Shifting every element to the left
    for (int i = 0; i < drawSize - 1; i++) {
        drawPile[i] = drawPile[i + 1];
    }
    drawSize--;
    return;
}

void MagicCard::addToDiscard(string card) {
    // Function for updating the discardPile array
    string* newArray = new string[discardSize+1];

    for (int i = 0; i < discardSize; i++) {
        newArray[i] = discardPile[i];
    }
    newArray[discardSize] = card;

    delete[] discardPile;
    discardPile = newArray;
    discardSize++;
}

void MagicCard::switchHands( const int player1ID, const int player2ID ) {
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    for (int i = 0; i < playerSize; i++) {
        if (allPlayers[i].getId() == player1ID) {
            player1 = &(allPlayers[i]);
        }

        else if (allPlayers[i].getId() == player2ID) {
            player2 = &(allPlayers[i]);
        }

        // For breaking early
        if (player1 != nullptr && player2 != nullptr) {
            break;
        }
    }

    // If failed to find
    if (player1 == nullptr || player2 == nullptr) {
        cout << "Cannot switch hands. One or both players do not exist." << endl;
        return;
    }

    player1->switchCards(player2);

    cout << "Switched hands between " << player1->getName() << " and " << player2->getName() << "." << endl;

}

void MagicCard::listDrawPile() const {
    if (drawSize == 0) {
        cout << "Draw pile is empty." << endl;
        return;
    }

    cout << "Draw pile: [";
    for (int i = 0; i < drawSize; i++) {
        // If we're printing the last element
        if (i == drawSize - 1) {
            cout << drawPile[i] << "]" << endl;
        }

        // If we're not printing the last element
        else {
            cout << drawPile[i] << ", ";
        }
    }
}

void MagicCard::listDiscardPile() const {
    if (discardSize == 0) {
        cout << "Discard pile is empty." << endl;
        return;
    }

    cout << "Discard pile: [";
    for (int i = 0; i < discardSize; i++) {
        // If we're printing the last element
        if (i == discardSize - 1) {
            cout << discardPile[i] << "]" << endl;
        }

        // If we're not printing the last element
        else {
            cout << discardPile[i] << ", ";
        }
    }
}

void MagicCard::listCardsOfPlayer( const int playerID ) const {
    for (int i = 0; i < playerSize; i++) {
        // If the given ID matches some player's ID
        if (allPlayers[i].getId() == playerID) {

            // Calling a function for listing the player's cards
            allPlayers[i].listCards();
            return;
        }
    }

    // If the given ID doesn't match any of the player's ID's
    cout << "Cannot list cards. Player with ID " << playerID << " does not exist." << endl;

}

void MagicCard::play( const int playerID, const string card ) {
    for (int i = 0; i < playerSize; i++) {
        // Getting the right player
        if (allPlayers[i].getId() == playerID) {            
            // Player's number of cards
            // Updating the number is done in addCard and removeCard functions in the Player class
            int noOfCards = allPlayers[i].getNoOfCards();

            for (int j = 0; j < noOfCards; j++) {
                // If the player has the specified card
                if (allPlayers[i].hasCard(card)) {
                    // If the discard pile is empty
                    if (discardSize == 0) {
                        playCard(allPlayers[i], card);
                        return;
                    }

                    // If the discard pile is not empty 
                    else {
                        // Get the top card
                        string topCard = discardPile[discardSize-1];

                        // If the card's color matches the top card's color or the card's number matches the top card's number
                        if (card.substr(0,1) == topCard.substr(0,1) || card.substr(1) == topCard.substr(1)) {
                            playCard(allPlayers[i], card);
                            return;
                        }

                        // If the card does not match
                        else {
                            playMismatchedCard(allPlayers[i], card);
                            return;
                        }                        
                    }
                }
            }

            // If the player does not have that card
            cout << "The player does not have " << card << " card." << endl;
            return;
        }
    }

    // If the given ID doesn't match any of the player's ID's
    cout << "There is no player with ID " << playerID << "." << endl;
}

void MagicCard::checkWin(Player& player) {
    if (player.getNoOfCards() == 0) {
        cout << "The game has ended. Player " << player.getId() << " won." << endl;
        this->~MagicCard();
        exit(0);
    }

    else if (drawSize == 0) {
        cout << "The game has ended. No cards remain in the draw pile." << endl;
        this->~MagicCard();
        exit(0);
    }
}

void MagicCard::playCard(Player& player, const string& card) {
    player.removeCard(card);
    addToDiscard(card);
    cout << "Player " << player.getId() << " played " << card << "." <<endl;
    // Check the state of the game
    checkWin(player);
}

void MagicCard::playMismatchedCard(Player& player, const string& card) {
    // Player plays the card
    player.removeCard(card);
    addToDiscard(card);
    string drawnCard = drawPile[0];
    // This handles the change of discard deck and player's cards
    drawCardForMismatch(player, drawnCard); 
    cout << "Player "<< player.getId() << " played " << card << " then drew " << drawnCard << "." << endl;
    // Check the state of the game
    checkWin(player);
}
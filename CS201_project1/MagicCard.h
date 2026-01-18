// Hande Köksal Section-1 22401938

#ifndef MAGICCARD_H
#define MAGICCARD_H

#include <string>
#include "Player.h"
using std::string;

class MagicCard {
private:
    int playerSize;
    Player* allPlayers;
    int drawSize;
    string* drawPile;
    int discardSize;
    string* discardPile;

public:
    MagicCard();
    ~MagicCard();

    void addPlayer( const int playerID, const string name );
    void removePlayer( const int playerID );
    void printPlayers() const;

    void setDrawPile( const string drawPile[], const int size );
    void drawCardFromDeck( const int playerID, const int n );
    void drawCardForMismatch(Player& player, const string& drawnCard);
    void addToDiscard( string card);
    void switchHands( const int player1ID, const int player2ID );
    void listDrawPile() const;
    void listDiscardPile() const;

    void listCardsOfPlayer( const int playerID ) const;

    void play( const int playerID, const string card );

    void checkWin(Player& player);

    void playCard(Player& player, const string& card);
    void playMismatchedCard(Player& player, const string& card);
    };

#endif
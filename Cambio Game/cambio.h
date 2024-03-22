#ifndef CAMBIO_H
#define CAMBIO_H

#include <vector>
#include <string>

using namespace std;

// Definition of a Card
// Definition of the Card class.
class Card
{
public:
    string rank; // The rank of the card (e.g., "Ace", "2", "Queen").
    string suit; // The suit of the card (e.g., "Hearts", "Spades").

    // The Constructor for the Card class takes in a rank (r) and a suit (s) to create a specific card.
    Card(string r, string s);

    // Method to get the card's point value based on its rank which will be defined inside this method in the Cambio.cpp file.
    int getValue() const;
};

// Definition of the Player class.
class Player
{
public:
    vector<Card> hand;    // The set of cards (hand) the player currently holds.
    bool hasCalledCambio; // Status indicating whether the player has called "Cambio" (a specific condition or action in the game).

    // Constructor for the Player class.
    // Initializes a new player, setting up their hand and Cambio status.
    Player();

    // Player action methods:

    // View the card at the specified index in the player's hand.
    void viewCard(int cardIndex);

    // Swap one of the player's cards with one from another player.
    void swapCard(Player &other, int myCardIdx, int theirCardIdx);

    // Draw a card from the draw pile.
    void drawCard(vector<Card> &drawPile);

    // Replace a card in the player's hand with the drawn card and put the old card into the discard pile.
    void replaceCard(int cardIndex, vector<Card> &drawPile, vector<Card> &discardPile, Card &drawnCard);

    // Declare "Cambio", typically indicating the final round or a bid to end the game.
    void callCambio();

    // Calculate and return the player's score based on the cards in their hand.
    int calculateScore() const;
};

// Definition of the CambioGame class, which manages the game of Cambio.
class CambioGame
{
private:
    vector<Card> drawPile;    // The pile of cards from which players can draw.
    vector<Card> discardPile; // The pile of cards where players discard their cards.
    vector<Player> players;   // List of players in the game.
    int currentPlayerIndex;   // Index to track whose turn it is.

public:
    // Constructor for the CambioGame class.
    // Takes the number of players and sets up the game accordingly.
    CambioGame(int numberOfPlayers);

    // Methods to manage the game lifecycle:

    // Set up the game: initialize cards, players, and other settings.
    void setupGame();

    // Start the game: begin the sequence of turns and gameplay.
    void startGame();

    // Manage the actions taken by a player during their turn.
    void playerTurn(int playerIndex);

    // Update the game state after a player's turn has ended.
    void updateGameState();

    // End the game, finalize scores, and determine the winner.
    void endGame();
};

#endif // CAMBIO_H

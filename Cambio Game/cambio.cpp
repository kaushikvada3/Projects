#include "Cambio.h"
#include <iostream>
#include <algorithm> // For shuffle
#include <random>    // For default_random_engine
#include <chrono>    // To create a randomized seed for the random number generator

using namespace std;

/*------------------------------------- Card Methods ------------------------------------------*/

//the constructor for the card class
Card::Card(string r, string s) : rank(r), suit(s) {} //constructor

int Card::getValue() const
{
    // Check if the rank is a number between 2 and 10.
    if (rank.size() == 1 && isdigit(rank[0]))
    {
        // Convert the rank (which is a string) to an integer value.
        return rank[0] - '0';
    }
    else if (rank == "Ace")
    {
        // Aces are valued at 11.
        return 11;
    }
    else if (rank == "Jack" || rank == "Queen" || rank == "King")
    {
        // Face cards are valued at 10.
        return 10;
    }
    else
    {
        // If the card's rank is unrecognized, return 0.
        // This could be modified if there are other specific rules or ranks.
        return 0;
    }
}

/*------------------------------------- Player Methods ------------------------------------------*/

// The constructor for the Player class
Player::Player() : hasCalledCambio(false) {}


// Implement method to allow player to view a card from their hand
void Player::viewCard(int cardIndex)
{
    // Check if the provided index is within the range of the player's hand
    if (cardIndex >= 0 && cardIndex < hand.size())
    {
        // if the index is valid, print the card's details
        Card &selectedCard = hand[cardIndex]; // Reference to avoid copying
        cout << "Card at index " << cardIndex << ": "
                  << selectedCard.rank << " of " << selectedCard.suit << endl;
    }
    else
    {
        // if the index is out of range, print an error message
        cout << "Invalid card index: " << cardIndex << endl;
    }
}

void Player::swapCard(Player &other, int myCardIdx, int theirCardIdx)
{
   /* your typical swap algorithm that involves using a temporary variable to hold something while switching */

    // Step 1: Save a copy of 'myCard' that's going to be swapped.
    Card myCard = this->hand[myCardIdx];

    // Step 2: Replace 'myCard' with the card from 'other' player's hand.
    this->hand[myCardIdx] = other.hand[theirCardIdx];

    // Step 3: Replace 'other' player's card with 'myCard'.
    other.hand[theirCardIdx] = myCard;
}

void Player::drawCard(vector<Card> &drawPile)
{
    // Check if the draw pile is not empty
    if (!drawPile.empty())
    {
        // Take the top card from the draw pile
        // This is the last card in the vector
        Card topCard = drawPile.back();

        // Add the drawn card to the player's hand
        hand.push_back(topCard);

        // Remove the drawn card from the draw pile
        drawPile.pop_back();
    }
    else
    {
        // Optional: could Handle the scenario where the draw pile is empty
        // This could involve reshuffling the discard pile into the draw pile,
        // or handling the game logic differently depending on the rules of your game.


        // For now, we'll just print a message.
        cout << "The draw pile is empty!" << endl;
    }
}

// Replace a card in the player's hand with a new one from the draw pile.
void Player::replaceCard(int cardIndex, vector<Card> &drawPile, vector<Card> &discardPile, Card &drawnCard)
{
    // Check if the cardIndex is valid for the player's hand.
    if (cardIndex < 0 || cardIndex >= hand.size())
    {
        // If the index is out of bounds, print an error message and exit the method.
        cout << "Invalid card index." << endl;
        return;
    }

    // Take the card from the player's hand at the specified index.
    Card cardToDiscard = hand[cardIndex];

    // Place the old card from the player's hand into the discard pile.
    discardPile.push_back(cardToDiscard);

    // Replace the old card in the player's hand with the new card (drawnCard).
    hand[cardIndex] = drawnCard;
}

void Player::callCambio()
{
    // Set the player's Cambio status which indicates that they believe they have
    // the lowest score and are calling the end of the round for the game.
    this->hasCalledCambio = true;
    cout << "Cambio called!" << endl;
}

int Player::calculateScore() const
{
    int score = 0; // Initialize score to zero.

    // Iterate through each card in the player's hand using a traditional for loop.
    for (int i = 0; i < hand.size(); i++)
    {
        // Add the value of each card to the score.
        // Here, we assume getValue() is implemented correctly for each Card.
        score += hand[i].getValue();
    }

    // Return the total score.
    return score;
}

/*-----------------------------------------CambioGames Methods---------------------------------------*/

// Implementations of CambioGame methods
CambioGame::CambioGame(int numberOfPlayers)
{
    // Constructor implementation
    setupGame();
}

void CambioGame::setupGame()
{
    // Implement game setup
}

void CambioGame::startGame()
{
    // Implement method to start the game
}

void CambioGame::playerTurn(int playerIndex)
{
    // Implement method for a player's turn
}

void CambioGame::updateGameState()
{
    // Implement method to update the game state after a turn
}

void CambioGame::endGame()
{
    // Implement method for ending the game
}

/*------------------------------------- Main Function (to test the game) ------------------------------------------*/

// Main function (optional, can be in a separate file)
int main()
{
    CambioGame game(4); // Assuming 4 players for example
    game.startGame();
    return 0;
}

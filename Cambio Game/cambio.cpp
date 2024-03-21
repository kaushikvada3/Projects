// Cambio.cpp
#include "Cambio.h"
#include <algorithm> // used this libaray to get the random_shuffle function
#include <ctime>     // time

using namespace std;

// Card methods
int Card::getPoints() const
{
    if (type == CardType::Joker)
        return 0; // Joker
    if (value == CardValue::Red_K && (type == CardType::Hearts || type == CardType::Diamonds))
        return -1; // Red King
    return static_cast<int>(value);
}

// Player methods
void Player::drawCard(vector<Card>& deck, vector<Card>& discardPile) {
    // Check if the deck is empty
    if (deck.empty()) {
        cout << "The deck is empty. Cannot draw a card." << endl;
        // Optionally, shuffle discardPile and move them to deck
        // shuffle(discardPile.begin(), discardPile.end(), default_random_engine(random_device()()));
        // deck.insert(deck.end(), discardPile.begin(), discardPile.end());
        // discardPile.clear();
        // If after this process the deck is still empty, return without drawing
        // if (deck.empty()) return;
    } else {
        // Take the top card from the deck and add it to the player's hand
        hand.push_back(deck.back());
        deck.pop_back();
        cout << "Drew a card from the deck." << endl;
    }
}


// Game methods
void Game::initializeDeck()
{
    // Clear any existing cards in the deck
    deck.clear();

    // Add standard cards
    for (unsigned int type = static_cast<unsigned int>(CardType::Hearts); type <= static_cast<unsigned int>(CardType::Spades); ++type)
    {
        for (unsigned int value = static_cast<unsigned int>(CardValue::A); value <= static_cast<unsigned int>(CardValue::Black_K); ++value)
        {
            deck.push_back(Card{static_cast<CardValue>(value), static_cast<CardType>(type)});
        }
    }

    // Add the red kings with negative value (-1)
    // Directly using unsigned int for Red_K might not be applicable as Red_K supposed to represent -1,
    // but we can handle this special case separately if Red_K is intended to be treated differently
    // For now, we'll use the standard approach for consistency
    deck.push_back(Card{CardValue::Red_K, CardType::Hearts});
    deck.push_back(Card{CardValue::Red_K, CardType::Diamonds});

    // Add two jokers
    deck.push_back(Card{CardValue::Joker, CardType::Joker});
    deck.push_back(Card{CardValue::Joker, CardType::Joker});

    // Shuffle the deck
    // Obtain a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));

    // Log the completion of deck initialization
    cout << "The deck has been initialized and shuffled." << endl;
}

void Game::dealInitialCards()
{
    // Assuming each player starts with four cards
    const int startingHandSize = 4;

    // Check if the deck has enough cards for all players
    if (deck.size() < players.size() * startingHandSize)
    {
        cerr << "Not enough cards in the deck to deal initial hands to all players." << endl;
        // Handle the error (maybe by re-initializing the deck or ending the game)
        return;
    }

    // Deal cards to each player
    for (Player &player : players)
    {
        for (int i = 0; i < startingHandSize; ++i)
        {
            // Directly manipulate the player's hand if drawCard is not suitable
            // Ensure the deck is not empty before this operation
            if (!deck.empty())
            {
                player.hand.push_back(deck.back());
                deck.pop_back();
            }
            else
            {
                // This should not happen due to the initial check, but it's good to be safe.
                cerr << "Ran out of cards while dealing initial hands." << endl;
                return; // Or handle the error as appropriate
            }
        }
    }

    // Optionally, log the completion of the card dealing
    cout << "Initial cards have been dealt to all players." << endl;
}

void Game::startGame()
{
    if (deck.empty())
    {
        cout << "The deck is not initialized. The game cannot start." << endl;
        return;
    }

    bool gameEnd = false;
    int currentPlayerIndex = 0;
    bool cambioCalled = false;

    // Main game loop
    while (!gameEnd)
    {
        cout << "Player " << currentPlayerIndex + 1 << "'s turn." << endl;

        // Example player interaction
        int action;
        cout << "Choose an action: 1 for draw from deck, 2 for draw from discard pile: ";
        cin >> action;

        if (action == 1)
        {
            // Draw from deck logic
            players[currentPlayerIndex].drawCard(deck, discardPile);
            // Further actions like discarding or replacing a card would go here
        }
        else if (action == 2 && !discardPile.empty())
        {
            // Draw from discard pile logic
            players[currentPlayerIndex].hand.push_back(discardPile.back());
            discardPile.pop_back();
            // Note: Can't use card's power if drawn from discard pile
        } // Add else to handle invalid actions or conditions

        // Check for Cambio call - this should be based on actual player input
        char cambio;
        cout << "Do you want to call Cambio? (y/n): ";
        cin >> cambio;

        if (cambio == 'y' || cambio == 'Y')
        {
            cambioCalled = true;
            players[currentPlayerIndex].isCambioCalled = true;
            cout << "Player " << currentPlayerIndex + 1 << " has called Cambio!" << endl;
            gameEnd = true; // Will trigger last round
        }

        // Move to the next player
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

        // If Cambio was called, everyone else gets one last turn
        if (cambioCalled && currentPlayerIndex == find_if(players.begin(), players.end(), [](const Player &p)
                                                               { return p.isCambioCalled; }) -
                                                      players.begin())
        {
            break; // Ends the game after the last person has had their turn
        }
    }

    // End of game logic - compare points and determine winner
    cout << "Game over. Calculating scores..." << endl;
    int minScore = INT_MAX;
    vector<int> playerScores(players.size(), 0);
    for (size_t i = 0; i < players.size(); ++i)
    {
        for (const auto &card : players[i].hand)
        {
            playerScores[i] += card.getPoints();
        }
        cout << "Player " << i + 1 << " score: " << playerScores[i] << endl;
        if (playerScores[i] < minScore)
        {
            minScore = playerScores[i];
        }
    }

    // Check for winner(s)
    vector<int> winners;
    for (size_t i = 0; i < playerScores.size(); ++i)
    {
        if (playerScores[i] == minScore)
        {
            winners.push_back(i);
        }
    }

    if (winners.size() == 1)
    {
        cout << "Player " << winners[0] + 1 << " wins the game!" << endl;
    }
    else
    {
        cout << "It's a tie between players: ";
        for (int i : winners)
        {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}

// Main function
int main()
{
    Game cambioGame;
    cambioGame.initializeDeck();
    cambioGame.dealInitialCards();
    cambioGame.startGame();

    return 0;
}

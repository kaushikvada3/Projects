// Cambio.h
#ifndef CAMBIO_H
#define CAMBIO_H

#include <vector>


// Card Definitions (enum is a class type typically used as an enumeration of all the values that are associated with each card)
enum class CardValue { A = 1, Two = 2, J = 11, Q = 12, Red_K = -1, Black_K = 13, Joker = 0 };
enum class CardType { Hearts, Diamonds, Clubs, Spades, Joker };


/* we need a way to represent a card and its value 
(like a node, I feel like using a struct would be better) 
(a node is basically a mini class 😄) */
struct Card {
    CardValue value;
    CardType type;
    int getPoints() const;
};


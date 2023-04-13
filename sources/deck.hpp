#ifndef DECK_H
#define DECK_H
#include "card.hpp"

namespace ariel {
    enum DeckType {
        PLAYER_DECK = 0,
        GAME_DECK = 1,
        CARDS_STACK = 2
    };
    class Deck {
    private:
        Card **cards;
        size_t totalSize;
        size_t actualSize;
        Card** generateGameDeck() ;
        Card** shuffleDeck(Card **deck) ;
    public:
        Deck() ;
        Deck(DeckType deckType) ;
        Deck(const Deck& other) ;
        Deck& operator=(const Deck& other) = default;
        Deck(Deck&& other) = default;
        Deck& operator=(Deck&& other) noexcept = default;
        ~Deck() ;
        Card *drawCard() ;

        void addCard(Card *c) ;

        int getSize() ;

        std::string toString() ;
    };
}
#endif //DECK_H
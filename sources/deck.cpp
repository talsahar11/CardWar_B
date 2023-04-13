#include "deck.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
namespace ariel {

    ///-----Empty Ctor (used for testing)-----
    Deck::Deck(){ }

    ///-----Ctor-----
    Deck::Deck(DeckType deckType) {
        switch (deckType) {
            case PLAYER_DECK:
                this->cards = new Card *[26];
                this->totalSize = 26;
                this->actualSize = 0;
                break;
            case GAME_DECK:
                this->cards = generateGameDeck();
                break;
            case CARDS_STACK:
                this->cards = new Card *[52];
                this->totalSize = 52;
                this->actualSize = 0;
                break;
            default:
                std::cout << "Incorrect DeckType inserted, deck was not created successfully.\n";
        }

    }

    ///-----Copy Ctor-----
    Deck::Deck(const Deck& other){
        actualSize = other.actualSize ;
        totalSize = other.totalSize ;
        cards = new Card*[totalSize] ;
        for(int i = 0 ; i < actualSize ; i++){
            this->cards[i] = new Card(*other.cards[i]) ;
        }
    }

    ///-----Dtor-----
    Deck::~Deck() {
        for (int i = 0; i < actualSize; i++) {
            delete this->cards[i];
        }
        delete[] this->cards;
    }

    ///-----Shuffle a given deck of cards randomly-----
    Card **Deck::shuffleDeck(Card **deck) {
        srand(time(NULL));
        Card **shuffledDeck = new Card *[52];
        int currentIndex = -1;
        int currentSize = 52;
        for (int i = 0; i < 52; i++) {
            currentIndex = rand() % currentSize;
            shuffledDeck[i] = deck[currentIndex];
            Card *temp = deck[currentSize - 1];
            deck[currentIndex] = temp;
            currentSize -= 1;
        }
        return shuffledDeck;
    }

    ///-----Generate a proper game deck including 52 cards, 12 different numbers for four card types, and shuffles
    ///-----the deck to prepare it for the game-----
    Card **Deck::generateGameDeck() {
        this->totalSize = 52;
        this->actualSize = 52;
        Card **gameDeck = new Card *[52];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                gameDeck[i * 13 + j] = new Card(i, j + 2);
            }
        }
        Card **shuffledDeck = shuffleDeck(gameDeck);
        delete[] gameDeck;
        return shuffledDeck;
    }

    ///-----Draw a card from the deck, return the card and update the size of the deck-----
    Card *Deck::drawCard() {
        if (this->actualSize == 0) {
            return NULL;
        } else {
            Card *c = this->cards[actualSize - 1];
            this->actualSize--;
            return c;
        }
    }

    ///-----Add card to the deck, and update the size of the deck-----
    void Deck::addCard(Card *c) {
        if (this->actualSize == totalSize) {
            std::cout << "Failed to add a card to the deck, deck is full.\n";
            return;
        } else {
            this->cards[this->actualSize] = c;
            this->actualSize++;
        }
    }

    ///-----Returns the current number of cards in the deck-----
    int Deck::getSize() {
        return actualSize;
    }

    using namespace std;

    ///-----Make a string contains all of the cards, each line for each card-----
    string Deck::toString() {
        string deckStr = "";
        for (int i = 0; i < this->actualSize; i++) {
            deckStr += this->cards[i]->toString();
            deckStr += "\n";
        }
        return deckStr;
    }

}
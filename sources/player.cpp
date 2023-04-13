#include "player.hpp"
#include <iostream>
#include <string.h>
namespace ariel {

    ///-----Ctor-----
    Player::Player(std::string name) {
        this->name = name;
        this->deck = new Deck(PLAYER_DECK);
        this->winningStack = new Deck(CARDS_STACK);
        this->numOfWins = 0;
        this->numOfTurns = 0;
    }

    ///-----Copy Ctor (deep copies the players deck)-----
    Player::Player(const Player& other){
        this->deck = new Deck(*other.deck) ;
        this->numOfTurns = other.numOfTurns ;
        this->winningStack = new Deck(*other.winningStack) ;
        this->numOfWins = other.numOfWins ;
        this->name.assign(other.name);
    }

    ///-----Dtor-----
    Player::~Player(){
        delete this->deck ;
        delete this->winningStack ;
    }

    ///-----Return the player's current stack size-----
    int Player::stacksize() {
        return this->deck->getSize();
    }

    ///-----Returns the number of cards won by the player-----
    int Player::cardesTaken() {
        return this->winningStack->getSize();
    }

    ///-----Draws card from the player's cards stack, remove the card from the stack-----
    Card *Player::drawCard() {
        return this->deck->drawCard();
    }

    ///-----Add card to the player's cards stack-----
    void Player::addCard(Card *c) {
        this->deck->addCard(c);
    }

    ///-----Add card to the player's winning stack-----
    void Player::addToWinningStack(Card *c) {
        this->winningStack->addCard(c);
    }

    ///-----Add a stack of cards to the player's winning stack-----
    void Player::addToWinningStack(Deck *cardsStack) {
        while (cardsStack->getSize() > 0) {
            this->addToWinningStack(cardsStack->drawCard());
        }
    }

    ///-----Returns the player's winning rate-----
    float Player::getWinningRate() {
        if (this->numOfTurns == 0) {
            return 0;
        } else {
            return this->numOfWins / this->numOfTurns;
        }
    }

    ///-----Increase the player's number of wins-----
    void Player::increaseNumOfWins() {
        this->numOfWins++;
    }

    ///-----Increase the player's number of turns-----
    void Player::increaseNumOfTurns() {
        this->numOfTurns++;
    }

    ///-----Returns the player's name-----
    std::string Player::getName() {
        return this->name;
    }

    ///-----Returns the player's cards stack-----
    Deck *Player::getDeck() {
        return this->deck;
    }

    ///-----Print the player's stats to console-----
    void Player::printStats() {
        float win_rate = (this->numOfTurns == 0) ? 0 : (float) this->numOfWins / this->numOfTurns ;
        std::cout << "Winning Rate: " << win_rate << ", "
                  << "Cards won: " << this->winningStack->getSize() << ", "
                  << "Have " << this->deck->getSize() << " more cards to play." << std::endl;
    }
}
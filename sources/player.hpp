#ifndef TASK2_PLAYER_H
#define TASK2_PLAYER_H
#include "deck.hpp"
namespace ariel {
    class Player {
    private:
        std::string name;
        Deck *deck;
        Deck *winningStack;
        int numOfWins;
        int numOfTurns;

    public:
        Player(std::string name) ;
        Player() ;
        Player(const Player& other) ;
        Player& operator=(const Player& other) = default;
        Player(Player&& other) = default;
        Player& operator=(Player&& other) noexcept = default;
        ~Player() ;
//        void manualDtor() ;
        int stacksize() ;

        int cardesTaken() ;

        Card *drawCard() ;

        void addCard(Card *c) ;

        void addToWinningStack(Card *c) ;

        void addToWinningStack(Deck *cardsStack) ;

        float getWinningRate() ;

        void increaseNumOfWins() ;

        void increaseNumOfTurns() ;

        std::string getName() ;

        Deck *getDeck() ;

        void printStats() ;

    };
}
#endif

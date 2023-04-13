#include "game.hpp"
#include <iostream>
namespace ariel{
    ///-----Ctor-----
    Game::Game(Player& p1, Player& p2): p1(p1), p2(p2) {
        this->gameDeck = new Deck(GAME_DECK) ;
        this->logSize = 0 ;
        this->drawNumber = 0 ;
        this->turnsPlayed = 0 ;
        this->isGameOn = true ;
        this->winner = NULL ;
        this->dealCards() ;
    }

    ///-----Dtor-----
    Game::~Game(){
        delete this->gameDeck ;
    }

    ///-----Save the last turn as detailed text in the log array-----
    void Game::logTurn(Card *c1, Card *c2, Player *p, bool isDraw) {
        if(isDraw){
            std::string turnStr = p1.getName() + " Played " + c1->toString() + " " + p2.getName() + " Played "
                                  + c2->toString() + ". Draw. " ;
            this->log.at(this->logSize) += turnStr ;
        }else {
            std::string turnStr = p1.getName() + " Played " + c1->toString() + " " + p2.getName() + " Played "
                                  + c2->toString() + ". " + p->getName() + " Wins.\n";
            this->log.at(this->logSize) += turnStr;
            this->logSize++;
        }
    }

    ///-----Deal cards one by one to the two players-----
    void Game::dealCards(){
        for(int i = 0 ; i < 26 ; i++){
            this->p1.addCard(this->gameDeck->drawCard()) ;
            this->p2.addCard(this->gameDeck->drawCard()) ;
        }
    }

    ///-----Play the next turn of the game, a draw situation is treated as a single turn-----
    void Game::playTurn(){
        //-----Check if the same player instance provided twice at the game ctor, and throw exception if needed-----
        if(&p1 == &p2){
            throw std::runtime_error("A game cannot be played by one player.") ;
        }

        //-----Check that the game isn't over yet, if it is, throw exception-----
        if(!this->isGameOn){
            throw std::runtime_error("The game is already over, cannot play another turn.") ;
        }

        //-----Draw card from each of the players, and increase the number of turns played-----
        Card* c1 = this->p1.drawCard() ;
        Card* c2 = this->p2.drawCard() ;
        this->p1.increaseNumOfTurns() ;
        this->p2.increaseNumOfTurns() ;

        //-----Compare the two cards, if it's a draw, call the handleDraw() method and keep from there, if not
        //-----add the round cards to the winning stack of the winner of this round and increase the player num
        //-----of wins-----
        int res = c1->compare(c2) ;
        this->turnsPlayed++ ;
        if(res > 0 || res < 0){
            Player* winner ;
            if(res > 0){
                winner = &p1 ;
            }else{
                winner = &p2 ;
            }
            winner->addToWinningStack(c1) ;
            winner->addToWinningStack(c2) ;
            logTurn(c1, c2, winner, false) ;
            winner->increaseNumOfWins() ;
        }else{
            logTurn(c1, c2, NULL, true) ;
            this->drawNumber++ ;
            handleDraw(c1, c2) ;
        }
        //-----If the players stacks are empty, finish the game-----
        if(this->p1.stacksize() == 0 || this->p2.stacksize() == 0){
            gameOver() ;
        }
    }

    ///-----Play all of the turns until the game is over-----
    void Game::playAll(){
        while(this->isGameOn){
            playTurn() ;
        }
    }

    ///-----Handle a draw situation, keep the turn going until different cards has been drawn-----
    void Game::handleDraw(Card* p1Card, Card* p2Card) {

        //-----Initiate a stacks that will accumulate the cards of the draw-----
        Deck *p1Stack = new Deck(CARDS_STACK) ;
        Deck *p2Stack = new Deck(CARDS_STACK) ;

        //-----Add to the stacks the current cards which created the draw-----
        p1Stack->addCard(p1Card) ;
        p2Stack->addCard(p2Card) ;

        //-----Initialize the cards that the players will hold in each stage-----
        Card *c1, *c2 ;

        //-----Initialize booleans to control the draw process-----
        bool redraw = true ;
        bool isCardReversed = true ;

        //-----While a draw keep occurring keep the draw process-----
        while(redraw) {
            //-----If one of the player's deck is empty, distribute each one of the stacks back to its own player-----
            //-----and stop the draw process-----
            if (this->p1.stacksize() == 0 || this->p2.stacksize() == 0) {
                p1.addToWinningStack(p1Stack) ;
                p2.addToWinningStack(p2Stack) ;

                //-----Log the case-----
                this->log[this->logSize] += "One of the players run out of cards, the draw stacks are distributed back"
                                            "to the players." ;
                redraw = false ;

                //-----Else, keep on the draw process-----
            } else {

                //-----Draw a card from each player and add it to the stacks-----
                c1 = p1.drawCard();
                c2 = p2.drawCard();
                p1Stack->addCard(c1) ;
                p2Stack->addCard(c2) ;

                //-----If it is the first round of the draw process, the cards are reversed, do nothing-----
                if(isCardReversed) {
                    isCardReversed = false ;

                    //-----Else, compare the two cards, and check which player won the round and add the both stacks to-----
                    //-----the winning player and stop the draw process, if it is draw again keep the draw process on-----
                }else{
                    int res = c1->compare(c2) ;
                    if(res > 0 || res < 0){
                        Player* winner ;
                        if(res == 1){
                            winner = &p1 ;

                        }else{
                            winner = &p2 ;
                        }
                        redraw = false ;
                        winner->addToWinningStack(p1Stack) ;
                        winner->addToWinningStack(p2Stack) ;
                        this->logTurn(c1, c2, winner, false) ;
                        winner->increaseNumOfWins() ;
                    }else{
                        this->drawNumber++ ;
                        isCardReversed = true ;
                        this->logTurn(c1, c2, NULL, true) ;
                    }
                }
            }
        }
        delete p1Stack ;
        delete p2Stack ;
    }

    ///-----Print the last element in the log array-----
    void Game::printLastTurn(){
        if(this->logSize == 0){
            std::cout << "The game haven't started yet." << std::endl ;
            return ;
        }
        std::cout << this->log.at(this->logSize-1) << std::endl ;
    }

    ///-----Print all of the log array-----
    void Game::printLog(){
        for(std::array<std::string ,LOG_SIZE>::size_type i = 0 ; i < this->logSize ; i++){
            std::cout << this->log.at(i) ;
        }
    }

    ///-----Print the winer of the game if there is one, if not print the appropriate message due to the game current
    ///-----situation-----
    void Game::printWiner() {
        if(this->p1.stacksize() != 0 && this->p2.stacksize() != 0){
            std::cout << "The game has not over yet, there is no winner at this moment." << std::endl ;
        }else {
            if (this->winner == NULL) {
                std::cout << "There is no winner, its a draw." << std::endl;
            } else {
                std::cout << "The winner is - " << this->winner->getName() << std::endl;
            }
        }
    }

    ///-----Called when the game is over, determine the winner of the game, and set the gameOver flag on-----
    void Game::gameOver(){
        this->isGameOn = false ;
        int p1StackSize = this->p1.cardesTaken() ;
        int p2StackSize = this->p2.cardesTaken() ;

        if(p1StackSize > p2StackSize){
            this->winner = &p1 ;
        }else if(p2StackSize > p1StackSize){
            this->winner = &p2 ;
        }
        std::cout << "The game is over." << std::endl ;
    }

    ///-----Print the game stats-----
    void Game::printStats(){
        std::cout << "Game Statistics:" << std::endl << p1.getName() << " - " ;
        p1.printStats() ;
        std::cout << p2.getName() << " - " ;
        p2.printStats() ;
        float drawRate = (this->turnsPlayed == 0) ? 0 : (float)this->drawNumber / this->turnsPlayed ;
        std:: cout << "General - Turns played: " << this->turnsPlayed << ", Draw rate: "
                   << drawRate << ", Amount of draws: " << this->drawNumber << "." << std::endl;
    }
}
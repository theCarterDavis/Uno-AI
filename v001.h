#pragma once

#include "AI.h"

class v001 : public AI
{

private:
    Color savedColor = RED;
    void mergeSort(vector<Card> & a);
    void mergeSort( vector<Card> & a,vector<Card> & tmpArray, int left, int right );
    void merge(vector<Card> & a, vector<Card> & tmpArray,int leftPos, int rightPos, int rightEnd);


public:
    v001(int playerNumber);

    void onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor);

    void onOtherPlayerDraw(int playerNumber);

    //returns the index of the card to play
    int makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction);

    string getName();



    Color getNewColor();

};

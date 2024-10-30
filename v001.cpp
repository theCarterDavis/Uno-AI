#include "v001.h"
#include <iostream>
using namespace std;

v001::v001(int playerNumber) : AI(playerNumber)
{



}

void v001::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
{

}

void v001::onOtherPlayerDraw(int playerNumber)
{

}

//Sort algorithm to make is so that the largest card values can be played first

void v001::merge(vector<Card> & a, vector<Card> & tmpArray,int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (a[leftPos].getPoints() <= a[rightPos].getPoints())
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);

    while (leftPos <= leftEnd)    // Copy rest of first half
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd)  // Copy rest of right half
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    // Copy tmpArray back
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}

void v001::mergeSort( vector<Card> & a,vector<Card> & tmpArray, int left, int right )
{
    if( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );
        merge( a, tmpArray, left, center + 1, right );
    }
}

/**
 * Mergesort algorithm (driver).
 */
void v001::mergeSort( vector<Card> & a )
{
    vector<Card> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

//returns the index of the card to play
int v001::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand,int direction) {


    int redH = 0, greenH = 0, blueH = 0, yellowH = 0, blackH = 0;
    //Inital pass through the entire loop
    for (int i = 0; i < cardsInHand.size(); i++) {
        if (cardsInHand[i].getColor() == RED) {
            redH++;
        }

        if (cardsInHand[i].getColor() == BLUE) {
            blueH++;
        }

        if (cardsInHand[i].getColor() == GREEN) {
            greenH++;
        }

        if (cardsInHand[i].getColor() == YELLOW) {
            yellowH++;
        }

    }

    if (yellowH > greenH && yellowH > blueH && yellowH > redH) {
        savedColor = YELLOW;
    } else if (greenH > yellowH && greenH > blueH && greenH > redH) {
        savedColor = GREEN;
    } else if (blueH > yellowH && blueH > greenH && blueH > redH){
        savedColor = BLUE;
    } else if (redH > yellowH && redH > greenH && redH > blueH){
        savedColor = RED;
    } else {
        savedColor = RED;
    }


    /*for (int i = 0; i < cardAmountsByPlayer.size(); i++)
    {
        cout << cardAmountsByPlayer[i] <<"\n";
    }*/



    vector<Card> cards = getPlayableCardsInHand(justPlayed, choosenCardColor, cardsInHand);

    if (cards.size() == 0)
    {
        return -1; //draw
    }
    mergeSort(cards);
    //special card key
    //reverse = 12, skip = 10, and draw2 = 11 of any of red/blue/green/yellow.
    //wild is black 0, draw4 is black 1

    int red=0,green=0,blue=0,yellow=0,black =0;
    //Inital pass through the entire loop
    for(int i =0; i < cards.size();i++){
        if (cards[i].getColor() == RED){
            red++;
        }

        if (cards[i].getColor() == BLUE){
            blue++;
        }

        if (cards[i].getColor() == GREEN){
            green++;
        }

        if (cards[i].getColor() == YELLOW){
            yellow++;
        }

        if (cards[i].getColor() == BLACK){
            black++;
        }

    }

    for(int i = cards.size()-1; i >= 0;i++){

        if(cards[i].getColor() != BLACK){
            for(int j = 0;j < cardsInHand.size();j++){
                if(cardsInHand[j] == cards[i]){
                    return j;
                }
            }
        }


        for(int j = 0;j < cardsInHand.size();j++){
            if(cardsInHand[j] == cards[i]){
                return j;
            }
        }
    }


    //should not get here in my AI???
    cerr << "bbaaaad happeeeened\n";
    return -1;
}

string v001::getName()
{
    return "In a Bad Mood :(";
}



Color v001::getNewColor()
{
    return savedColor;
}



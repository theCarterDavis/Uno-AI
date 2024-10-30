#include "v002.h"
#include <iostream>
using namespace std;

v002::v002(int playerNumber) : AI(playerNumber)
{



}

void v002::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
{

}

void v002::onOtherPlayerDraw(int playerNumber)
{

}

//Sort algorithm to make is so that the largest card values can be played first

void v002::merge(vector<Card> & a, vector<Card> & tmpArray,int leftPos, int rightPos, int rightEnd)
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

void v002::mergeSort( vector<Card> & a,vector<Card> & tmpArray, int left, int right )
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
void v002::mergeSort( vector<Card> & a )
{
    vector<Card> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

//returns the index of the card to play
int v002::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand,int direction) {

    //Tracking how may of each card I have as well as how may points each color has
    int redH = 0, greenH = 0, blueH = 0, yellowH = 0, redP = 0, greenP = 0, blueP = 0, yellowP = 0, blackH = 0;
    int values[2][4];
    for(int i = 0; i < 2;i++){
        for(int j = 0; j < 4;j++){
            values[i][j] = 0;
        }
    }
    int max = 0;
    //Inital pass through the entire loop
    for (int i = 0; i < cardsInHand.size(); i++) {
        if (cardsInHand[i].getColor() == RED) {
            redH++;
            redP += cardsInHand[i].getPoints();
            values[0][0]++;
            values[1][0] += cardsInHand[i].getPoints();

        }

        if (cardsInHand[i].getColor() == BLUE) {
            blueH++;
            blueP += cardsInHand[i].getPoints();
            values[0][1]++;
            values[1][1] += cardsInHand[i].getPoints();
        }

        if (cardsInHand[i].getColor() == GREEN) {
            greenH++;
            greenP += cardsInHand[i].getPoints();
            values[0][2]++;
            values[1][2] += cardsInHand[i].getPoints();
        }

        if (cardsInHand[i].getColor() == YELLOW) {
            yellowH++;
            yellowP += cardsInHand[i].getPoints();
            values[0][3]++;
            values[1][3] += cardsInHand[i].getPoints();
        }
        if (cardsInHand[i].getColor() == BLACK) {
            blackH++;
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
    int totalCards = cardsInHand.size();
    bool hasP4 = false;
    Card p4temp;
    for(int i =0; i < cards.size();i++){
        if(cards[i].getColor() == BLACK && cards[i].getNumber() == 1){
            hasP4 = true;
            p4temp = cards[i];
        }
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



    for(int i = cards.size()-1; i >= 0;i++) {

        //Checking for the next players card count to see which wild to play
        if(direction == 1){
            if(myPlayerNumber != 4){
                if(cardAmountsByPlayer[myPlayerNumber +1] < 3 && hasP4){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == p4temp){
                            return j;
                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[0] < 3 && hasP4){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == p4temp){
                            return j;
                        }
                    }
                }
            }
        } else {
            if(myPlayerNumber != 0){
                if(cardAmountsByPlayer[myPlayerNumber - 1] < 3 && hasP4){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == p4temp){
                            return j;
                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[4] < 3 && hasP4){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == p4temp){
                            return j;
                        }
                    }
                }
            }
        }

        //Plays yellow
        if (yellowH > greenH && yellowH > blueH && yellowH > redH) {
            if (cards[i].getColor() != BLACK) {
                for (int j = 0; j < cardsInHand.size(); j++) {
                    if (cardsInHand[j] == cards[i] && cards[i].getColor() == YELLOW) {
                        return j;
                    }
                }
            }
        }

        //Plays Green
        if (greenH > yellowH && greenH > blueH && greenH > redH) {
            if (cards[i].getColor() != BLACK) {
                for (int j = 0; j < cardsInHand.size(); j++) {
                    if (cardsInHand[j] == cards[i] && cards[i].getColor() == GREEN) {
                        return j;
                    }
                }
            }
        }

        if (blueH > yellowH && blueH > greenH && blueH > redH) {
            if (cards[i].getColor() != BLACK) {
                for (int j = 0; j < cardsInHand.size(); j++) {
                    if (cardsInHand[j] == cards[i] && cards[i].getColor() == BLUE) {
                        return j;
                    }
                }
            }
        }

        if (redH > yellowH && redH > greenH && redH > blueH) {
            if (cards[i].getColor() != BLACK) {
                for (int j = 0; j < cardsInHand.size(); j++) {
                    if (cardsInHand[j] == cards[i] && cards[i].getColor() == RED) {
                        return j;
                    }
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

string v002::getName()
{
    return "In a Really Bad Mood :(";
}



Color v002::getNewColor()
{
    return savedColor;
}


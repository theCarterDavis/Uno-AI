#include "v008.h"
#include <iostream>
using namespace std;

v008::v008(int playerNumber) : AI(playerNumber)
{



}

void v008::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
{

}

void v008::onOtherPlayerDraw(int playerNumber)
{

}

//Sort algorithm to make is so that the largest card values can be played first

void v008::merge(vector<Card> & a, vector<Card> & tmpArray,int leftPos, int rightPos, int rightEnd)
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

void v008::mergeSort( vector<Card> & a,vector<Card> & tmpArray, int left, int right )
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
void v008::mergeSort( vector<Card> & a )
{
    vector<Card> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

//returns the index of the card to play
int v008::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand,int direction) {

    mergeSort(cardsInHand);
    int redH = 0, greenH = 0, blueH = 0, yellowH = 0, blackH = 0;

    vector<Card> blues;
    vector<Card> reds;
    vector<Card> greens;
    vector<Card> yellows;

    //Inital pass through the entire loop
    for (int i = 0; i < cardsInHand.size(); i++) {
        if (cardsInHand[i].getColor() == RED) {
            redH++;
            reds.push_back(cardsInHand[i]);
        }

        if (cardsInHand[i].getColor() == BLUE) {
            blueH++;
            blues.push_back(cardsInHand[i]);

        }

        if (cardsInHand[i].getColor() == GREEN) {
            greenH++;
            greens.push_back(cardsInHand[i]);

        }

        if (cardsInHand[i].getColor() == YELLOW) {
            yellowH++;
            yellows.push_back(cardsInHand[i]);

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
    bool hasWild = false;
    Card wildTemp;
    Card p4temp;


    //Booleans for reverse cards
    bool rev = false;
    bool blueRev = false;
    Card bRev;
    bool redRev = false;
    Card rRev;
    bool greenRev = false;
    Card gRev;
    bool yellowRev = false;
    Card yRev;

    //Booleans for plus 2s
    bool p2 = false;
    bool blueP2 = false;
    Card bp2;
    bool redP2 = false;
    Card rp2;
    bool yellowP2 = false;
    Card yp2;
    bool greenP2 = false;
    Card gp2;

    bool skip = false;
    bool blueSkip = false;
    Card bSkip;
    bool redSkip = false;
    Card rSkip;
    bool yellowSkip = false;
    Card ySkip;
    bool greenSkip = false;
    Card gSkip;



    for(int i =0; i < cards.size();i++){

        if(cards[i].getNumber() == 12){

            rev = true;

        }

        if(cards[i].getNumber() == 10){

            skip = true;

        }

        if(cards[i].getNumber() == 11) {

            p2 = true;

        }

        if(cards[i].getColor() == BLACK && cards[i].getNumber() == 1){
            hasP4 = true;
            p4temp = cards[i];
        } else if(cards[i].getColor() == BLACK && cards[i].getNumber() == 10){
            hasWild = true;
            wildTemp = cards[i];

        }


        if (cards[i].getColor() == RED){
            red++;

            if(cards[i].getNumber() == 12 && cards[i].getColor() == RED){
                redRev = true;
                rRev = cards[i];
            }

            if(cards[i].getNumber() == 11 && cards[i].getColor() == RED){
                redP2 = true;
                rp2 = cards[i];
            }

            if(cards[i].getNumber() == 10 && cards[i].getColor() == RED){
                redSkip = true;
                rSkip = cards[i];
            }


        }

        if (cards[i].getColor() == BLUE){
            blue++;



            if(cards[i].getNumber() == 12 && cards[i].getColor() == BLUE){
                blueRev = true;
                bRev = cards[i];
            }

            if(cards[i].getNumber() == 11 && cards[i].getColor() == BLUE){
                blueP2 = true;
                bp2 = cards[i];
            }

            if(cards[i].getNumber() == 10 && cards[i].getColor() == BLUE){
                blueSkip = true;
                bSkip = cards[i];
            }
        }

        if (cards[i].getColor() == GREEN){
            green++;

            if(cards[i].getNumber() == 12 && cards[i].getColor() == GREEN){
                greenRev = true;
                gRev = cards[i];
            }

            if(cards[i].getNumber() == 11 && cards[i].getColor() == GREEN){
                greenP2 = true;
                gp2 = cards[i];
            }

            if(cards[i].getNumber() == 10 && cards[i].getColor() == GREEN){
                greenSkip = true;
                gSkip = cards[i];
            }
        }

        if (cards[i].getColor() == YELLOW){
            yellow++;

            if(cards[i].getNumber() == 12 && cards[i].getColor() == YELLOW){
                yellowRev = true;
                yRev = cards[i];
            }

            if(cards[i].getNumber() == 11 && cards[i].getColor() == YELLOW){
                yellowP2 = true;
                yp2 = cards[i];
            }

            if(cards[i].getNumber() == 10 && cards[i].getColor() == YELLOW){
                yellowSkip = true;
                ySkip = cards[i];
            }
        }

        if (cards[i].getColor() == BLACK){
            black++;
        }

    }

    bool closeToLoss = false;
    bool inHand = false;
    //Seeing if the player next to me is close to winning
    if(direction == 1){
        if(myPlayerNumber != 4){
            if(cardAmountsByPlayer[myPlayerNumber +1] < 3){
                closeToLoss = true;
            }
        } else {
            if(cardAmountsByPlayer[0] < 3){
                closeToLoss = true;
            }
        }
    } else {
        if(myPlayerNumber != 0){
            if(cardAmountsByPlayer[myPlayerNumber - 1] < 3){
                closeToLoss = true;
            }
        } else {
            if(cardAmountsByPlayer[4] < 3){
                closeToLoss = true;

            }
        }
    }





    for(int i = cards.size()-1; i >= 0;i--){


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

        if(direction == 1){
            if(myPlayerNumber != 4){
                if(cardAmountsByPlayer[myPlayerNumber +1] < 3 && hasWild){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == wildTemp){

                            return j;

                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[0] < 3 && hasWild){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == wildTemp){

                            return j;

                        }
                    }
                }
            }
        } else {
            if(myPlayerNumber != 0){
                if(cardAmountsByPlayer[myPlayerNumber - 1] < 3 && hasWild){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == wildTemp){

                            return j;

                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[4] < 3 && hasWild){
                    for(int j = 0; j < cardsInHand.size();j++){
                        if(cardsInHand[j] == wildTemp){

                            return j;

                        }
                    }
                }
            }
        }

        if(closeToLoss && p2){

            if(redP2){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == RED){

                        return j;

                    }
                }
            }

            if(blueP2){
                for(int j = 0; j < cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == BLUE){

                        return j;

                    }
                }
            }

            if(greenP2){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == GREEN){

                        return j;

                    }
                }
            }

            if(yellowP2){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == YELLOW){

                        return j;

                    }
                }
            }
        }

        if(closeToLoss && skip){

            if(redSkip){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == RED){
                        return j;


                    }
                }
            }

            if(blueSkip){
                for(int j = 0; j < cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == BLUE){
                        return j;

                    }
                }
            }

            if(greenSkip){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == GREEN){
                        return j;
                    }
                }
            }

            if(yellowSkip){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == YELLOW){
                        return j;
                    }
                }
            }
        }

        if(closeToLoss && rev){

            if(redRev){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == RED){
                        return j;
                    }
                }
            }

            if(blueRev){
                for(int j = 0; j < cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == BLUE){
                        return j;
                    }
                }
            }

            if(greenRev){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == GREEN){
                        return j;
                    }
                }
            }

            if(yellowRev){
                for(int j = 0;j<cardsInHand.size();j++){
                    if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == YELLOW){
                        return j;
                    }
                }
            }
        }

        //Reversing if the player next to us has more cards than me and the player on the other side of me
        if(direction == 1){
            if(myPlayerNumber != 4){
                if(cardAmountsByPlayer[myPlayerNumber +1] < cardAmountsByPlayer[myPlayerNumber]){

                    if(rev){

                        if(redRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueRev){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[0] <  cardAmountsByPlayer[myPlayerNumber]){

                    if(rev){

                        if(redRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueRev){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if(myPlayerNumber != 0){
                if(cardAmountsByPlayer[myPlayerNumber - 1] < cardAmountsByPlayer[myPlayerNumber]){
                    if(rev){

                        if(redRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueRev){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[4] < cardAmountsByPlayer[myPlayerNumber]){
                    if(rev){

                        if(redRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueRev){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowRev){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 12 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }

                }
            }
        }


        if(direction == 1){
            if(myPlayerNumber != 4){
                if(cardAmountsByPlayer[myPlayerNumber +1] < cardAmountsByPlayer[myPlayerNumber]){

                    if(skip){

                        if(redSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueSkip){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[0] <  cardAmountsByPlayer[myPlayerNumber]){

                    if(skip){

                        if(redSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueSkip){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if(myPlayerNumber != 0){
                if(cardAmountsByPlayer[myPlayerNumber - 1] < cardAmountsByPlayer[myPlayerNumber]){
                    if(skip){

                        if(redSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueSkip){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            } else {

                if(cardAmountsByPlayer[4] < cardAmountsByPlayer[myPlayerNumber]){
                    if(skip){

                        if(redSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueSkip){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowSkip){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 10 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }

                }
            }
        }

        if(direction == 1){
            if(myPlayerNumber != 4){
                if(cardAmountsByPlayer[myPlayerNumber +1] < cardAmountsByPlayer[myPlayerNumber]){

                    if(skip){

                        if(redP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueP2){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[0] <  cardAmountsByPlayer[myPlayerNumber]){

                    if(skip){

                        if(redP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueP2){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if(myPlayerNumber != 0){
                if(cardAmountsByPlayer[myPlayerNumber - 1] < cardAmountsByPlayer[myPlayerNumber]){
                    if(skip){

                        if(redP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueP2){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            } else {
                if(cardAmountsByPlayer[4] < cardAmountsByPlayer[myPlayerNumber]){
                    if(skip){

                        if(redP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == RED){
                                    return j;
                                }
                            }
                        }

                        if(blueP2){
                            for(int j = 0; j < cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == BLUE){
                                    return j;
                                }
                            }
                        }

                        if(greenP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == GREEN){
                                    return j;
                                }
                            }
                        }

                        if(yellowP2){
                            for(int j = 0;j<cardsInHand.size();j++){
                                if(cardsInHand[j].getNumber() == 11 && cardsInHand[j].getColor() == YELLOW){
                                    return j;
                                }
                            }
                        }
                    }
                }
            }
        }

/*
        if(yellows.size() > blues.size() && yellows.size() > greens.size() && yellows.size() > reds.size()  && yellowH > 0){
            for(int j=cardsInHand.size()-1; j< 0;j--){
                if(cardsInHand[j] == yellows[0]){
                    return j;
                }
            }
        }

        if(blues.size() > yellows.size() && blues.size() > greens.size() && blues.size() > reds.size()  && blueH > 0){
            for(int j=0 ; j< cardsInHand.size();j++){
                if(cardsInHand[j] == blues[0]){
                    return j;
                }
            }
        }

        if(reds.size() > yellows.size() && reds.size() > greens.size() && reds.size() > blues.size()  && redH > 0){
            for(int j=0 ; j< cardsInHand.size();j++){
                if(cardsInHand[j] == reds[0]){
                    return j;
                }
            }
        }

        if(greens.size() > yellows.size() && greens.size() > reds.size() && greens.size() > blues.size()  && redH > 0){
            for(int j=0 ; j< cardsInHand.size();j++){
                if(cardsInHand[j] == greens[0]){
                    return j;
                }
            }
        }
*/
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

string v008::getName()
{
    return "In a Really Really Really Really Really Really Really Bad Mood :(";
}



Color v008::getNewColor() {
    return savedColor;
}
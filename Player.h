#pragma once

#include <vector>
#include <algorithm>
using namespace std;

#include "Card.h"
#include "AI.h"
#include "v001.h"
#include "v002.h"
#include "v003.h"
#include "v004.h"
#include "v005.h"
#include "v006.h"
#include "v007.h"
#include "v008.h"
#include "cobos3.h"
#include "jennyGoodAI.h"


#include "TestAI.h"

class Player
{

public:
    vector<Card> hand;



    int playerNumber;

    AI * theAI;


    vector<int> handSizes;
    vector<vector<int>> pointsPerHand;
    vector<int> games;

    int whichAI;

    vector<float> diff;

    int wleft = 0, d4left = 0;

    bool validPlay(int index, Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand);

public:

    void recreateAI();

    Player(int num, int whichAI);
    void setNum(int num) { playerNumber = num; theAI->setNum(num); }

    //if you desire to keep track of what cards other people played...
    void onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor);
    void onOtherPlayerDraw(int playerNumber);

    int makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, int direction) //the returned int refers to the index of which card is played in your hand.
    ;

    Color getNewColor();

    void clearHand();


    void addToHand(Card c);

    void removeCardFromHand(int indexOfCard);

    vector<Card> getHandCopy();


    int wins = 0;
    int updateStats(vector<Player *> thePlayers);
    int getMostRecentScore()
    {
        return mostRecent;
    }
    int mostRecent = 0;

    void printAbrvStats(vector<Player*> thePlayers, ostream& out);
    void printStats(vector<Player*> thePlayers, ostream & out);

    string getName() { return theAI->getName(); }
    int getNum() { return theAI->getNum(); }
};

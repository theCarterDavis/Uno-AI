
#include "Player.h"
#include "Card.h"
#include <iostream>
#include <string>



using namespace std;

Player::Player(int num, int whichAI)
{
    this->whichAI = whichAI;


    for (int i = 0; i < 35; i++)
    {
        games.push_back(0);
        diff.push_back(0);
        handSizes.push_back(0);
        pointsPerHand.resize(35);
    }

    playerNumber = num;
    theAI = 0;
    recreateAI();
}

void Player::recreateAI()
{
    if (theAI != 0)
    {
        delete theAI;
    }

    switch (whichAI)
    {



        case 0:
            theAI = new cobos3(playerNumber);
            break;
        case 1:
            theAI = new TestAI(playerNumber);
            break;
        case 2:
            theAI = new TestAI(playerNumber);
            break;
        case 3:
            theAI = new jennyGoodAI(playerNumber);
            break;
        case 4:
            theAI = new v006(playerNumber);
            break;
    }
}

//if you desire to keep track of what cards other people played...
void Player::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor)
{
    theAI->onOtherPlayerMove(playerNumber, justPlayed, choosenCardColor);
}
void Player::onOtherPlayerDraw(int playerNumber)
{
    theAI->onOtherPlayerDraw(playerNumber);
}

bool Player::validPlay(int index, Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand)
{
    //cout << index << " " << hand.size() << "\n";


    if (index == -1)
    {
        return true;
    }

    if ((index < -1) || (index > hand.size() - 1))
    {
        cout << "index is not the correct value "<<hand.size()<<" "<<index<<"\n";
        return false;
    }

    if (getNewColor() == BLACK || getNewColor() == NONE)
    {
        cout << " did not choose new color\n";
        return false;
    }


    Card c = hand[index];

    if (choosenCardColor == c.getColor())
    {
        return true; //same color
    }
    else if (c.getColor() != BLACK && justPlayed.getNumber() == c.getNumber() && justPlayed.getColor() != BLACK)
    {
        return true; //same number
    }
    else if (c.getColor() == BLACK && c.getNumber() == 0) //wild
    {
        return true; //wild
    }
    else if (c.getColor() == BLACK && c.getNumber() == 1) //draw four
    {
        bool hasColor = false;
        for (int j = 0; j < cardsInHand.size(); j++)
        {
            if (choosenCardColor == cardsInHand[j].getColor())
            {
                hasColor = true;
            }
        }
        if (!hasColor) //can only play draw4 if doesn't have color.
        {
            return true;
        }
    }
    //cout << "invalid play other: \n";
    /*cout << "hand: \n";
    for (int i = 0; i < cardsInHand.size(); i++)
    {
        cout << cardTOString(cardsInHand[i]) << " ";
    }
    cout << "\n";
    cout << " top: " << cardTOString(justPlayed)<<"\n";
    cout << " choosen color: " << colorToStringBE(choosenCardColor);
    cout << " playing: " << cardTOString(c) << "\n";
    cout << "\n";*/
    return false;
}

//calls the function on player's AI.
int Player::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer,  int direction) //the returned int refers to the index of which card is played in your hand.
{
    int index = theAI->makeMove(justPlayed, choosenCardColor, justDrew, scores, cardAmountsByPlayer, hand,direction);

    if (!validPlay(index, justPlayed, choosenCardColor, justDrew, scores, cardAmountsByPlayer, hand))
    {
        //cout << "bad play detected by AI; card not allowed to be played: print out on player.cpp line  83\n"<<theAI->getName() ;
        //while (true); //pause program execution!
        return -1;
    }

    return index;
}

Color Player::getNewColor()
{
    return theAI->getNewColor();
}

void Player::clearHand()
{
    hand.clear();
}


void Player::addToHand(Card c)
{
    hand.push_back(c);
}

void Player::removeCardFromHand(int indexOfCard)
{
    hand.erase(hand.begin() + indexOfCard);
}

vector<Card> Player::getHandCopy()
{
    return hand;
}



int Player::updateStats(vector<Player *> thePlayers)
{
    for (int i = 0; i < hand.size(); i++)
    {
        if (hand[i].getColor() == BLACK && hand[i].getNumber() == 1)
            d4left++;

        if (hand[i].getColor() == BLACK && hand[i].getNumber() == 0)
            wleft++;
    }

    for (int i = 0; i < 5; i++)
    {
        handSizes[thePlayers[i]->whichAI] += hand.size();
    }

    int points = 0;
    for (int i = 0; i < hand.size(); i++)
    {

        points += hand[i].getPoints();
    }

    for (int j = 0; j < 5; j++)
    {
        pointsPerHand[thePlayers[j]-> whichAI].push_back(points);
    }

    for (int i = 0; i < 5; i++)
    {
        games[thePlayers[i]->whichAI] ++;
    }

    mostRecent = points;
    return points;
}



void Player::printStats(vector<Player*> thePlayers, ostream& out)
{
    out << "Player: " << playerNumber << "\n";
    out << "AI: " << theAI->getName() << "\n";

    cout << "Player: " << playerNumber << "\n";
    cout << "AI: " << theAI->getName() << "\n";

    cout << "handsize, ";
    out << "handsize, ";
    for (int i = 0; i < 25; i++)
    {
        cout << handSizes[i] * 1.0f / games[i] << ",";
        out << handSizes[i] * 1.0f / games[i] << ",";
    }
    cout << "\n";
    out << "\n";

    cout << "medium points, ";
    out << "medium points, ";
    for (int i = 0; i < 25; i++)
    {
        sort(pointsPerHand[i].begin(), pointsPerHand[i].end());
        if (pointsPerHand[i].size() == 0)
        {
            cout << 0 << ",";
            out << 0 << ",";
        }
        else
        {
            cout << pointsPerHand[i][pointsPerHand[i].size() / 2] << ",";
            out << pointsPerHand[i][pointsPerHand[i].size() / 2] << ",";
        }
    }
    cout << "\n";
    out << "\n";

    cout << "average points, ";
    out << "average points, ";
    for (int j = 0; j < 25; j++)
    {
        int points = 0;
        for (int i = 0; i < pointsPerHand[j].size(); i++)
        {
            points += pointsPerHand[j][i];
        }

        out << points * 1.0f / games[j] << ",";
        cout << points * 1.0f / games[j] << ",";
    }
    cout << "\n";
    out << "\n";



    cout << "avg diff, ";
    out << "avg diff, ";
    for (int i = 0; i < 25; i++)
    {
        cout << diff[i] * 1.0f / games[i] << ",";
        out << diff[i] * 1.0f / games[i] << ",";
    }
    cout << "\n";
    out << "\n";

    out << "wins: " << wins << "\n";
    out << "Left:  d4:" << d4left << "   w:" << wleft << "\n";

    cout << "wins: " << wins << "\n";
    cout << "Left:  d4:" << d4left << "   w:" << wleft << "\n";



}









void Player::printAbrvStats(vector<Player*> thePlayers, ostream& out)
{
    out << "AI: " << theAI->getName() << "\n";
    cout << "AI: " << theAI->getName() << "\n";


    cout << "average points, ";
    out << "average points, ";
    for (int j = 0; j < 25; j++)
    {
        int points = 0;
        for (int i = 0; i < pointsPerHand[j].size(); i++)
        {
            points += pointsPerHand[j][i];
        }

        out << points * 1.0f / games[j] << ",";
        cout << points * 1.0f / games[j] << ",";
    }
    cout << "\n";
    out << "\n";



    cout << "best other average, ";
    out << "best other average, ";

    double avgs[5];

    for (int k = 0; k < 5; k++)
    {
        for (int j = 0; j < 1; j++)
        {
            int points = 0;
            for (int i = 0; i < thePlayers[k]->pointsPerHand[j].size(); i++)
            {
                points += thePlayers[k]->pointsPerHand[j][i];
            }
            avgs[k] = points*1.0f/ games[j];
            //cout << avgs[k] << "\n";
        }
    }

    for (int j = 0; j < 1; j++)
    {
        int points = 0;
        for (int i = 0; i < pointsPerHand[j].size(); i++)
        {
            points += pointsPerHand[j][i];
        }

        out << points * 1.0f / games[j] << ",";
        cout << points * 1.0f / games[j] << ",";
    }

    double best = 9999;
    for (int i = 0; i < 5; i++)
    {
        if (avgs[i] < best)
        {
            best = avgs[i];
        }
    }

    out << best << ",";
    cout << best << ",";



    cout << "\n";
    out << "\n";


}

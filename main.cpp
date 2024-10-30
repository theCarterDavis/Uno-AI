#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Player.h"

#include "Card.h"
using namespace std;


//+1 point if you are the first to find a bug in my code.



//put verbose to 1 to see every play & hand. 0 to only print out the end stats
#define VERBOSE 0


void deal(vector<Card> & theDeck, vector<Player *> & thePlayers)
{
    for (int i = 0; i < thePlayers.size(); i++)
    {
        thePlayers[i]->clearHand();
        for (int j = 0; j < 7; j++)
        {
            thePlayers[i]->addToHand(theDeck.back());
            theDeck.pop_back();
        }
    }
}

void createDeck(vector<Card> & theDeck)
{
    theDeck.clear();
    for (int color = 0; color < 4; color++)
    {
        for (int i = 0; i < 13; i++)
        {
            Card c(i, (Color)color);
            theDeck.push_back(c);
        }
        for (int i = 0; i < 13; i++)
        {
            Card c(i, (Color)color);
            theDeck.push_back(c);
        }

    }
    for (int i = 0; i < 4; i++)
    {
        Card c(0, BLACK);
        theDeck.push_back(c);
        Card c2(1, BLACK);
        theDeck.push_back(c2);
    }
}

void shuffleDeck(vector<Card> & theDeck)
{
    for (int i = 0; i < theDeck.size(); i++)
    {
        int j = rand() % theDeck.size();
        Card c = theDeck[i];
        theDeck[i] = theDeck[j];
        theDeck[j] = c;
    }
}

string colorToString(Color c)
{
    switch (c)
    {
        case RED:
            return "red";
        case YELLOW:
            return "yellow";
        case BLUE:
            return "blue";
        case GREEN:
            return "green";
    }
    return "black";
}

void printGameState(int currentTurn, vector<Player *> thePlayers, Card topCardOfDiscard)
{


    if(VERBOSE) cout << "\nCurrentTurn: " << currentTurn << endl;

    for (int i = 0; i < thePlayers.size(); i++)
    {
        vector<Card> h = thePlayers[i]->getHandCopy();
        if (VERBOSE) cout << "("<<i<<")("<<thePlayers[i]->getNum()<< ")" << thePlayers[i]->getName() << ": ";
        for (int j = 0; j < h.size(); j++)
        {
            if (VERBOSE) cout << cardTOString(h[j]);
            if (VERBOSE) cout << " ";
        }
        if (VERBOSE) cout << "\n";
    }

    if (VERBOSE) cout << "Card on top: " << cardTOString(topCardOfDiscard) << " "<<colorToString(topCardOfDiscard.getColorChange())<<"\n";
}

void verifyGameStateCards(vector<Player *> thePlayers, vector<Card> & theDeck, vector<Card> & discardPile)
{
    int sum = 0;
    sum += theDeck.size();
    sum += discardPile.size();
    for (int i = 0; i < thePlayers.size(); i++)
    {
        sum+=thePlayers[i]->getHandCopy().size();
    }

    if (VERBOSE) cout << "Card Count (should be 112): " << sum << "\n";
}

void drawCardToCurrentPlayer(int & currentPlayer, vector<Player *> thePlayers, vector<Card> & theDeck, vector<Card> & discardPile)
{


    if (theDeck.size() == 0)
    {
        Card top = discardPile.back();
        discardPile.pop_back();

        if (theDeck.size() == 0 && discardPile.size() == 0)
        {
            cout << "Deck is out of Cards, AI most likely keeps drawing when probably should not be :( \n forever looping so you see this message...\n";
            while (true);
        }

        shuffleDeck(discardPile);

        while (discardPile.size() > 0)
        {
            Card c = discardPile.back();
            theDeck.push_back(c);
            discardPile.pop_back();
        }

        discardPile.push_back(top);
    }

    Card c = theDeck.back();
    theDeck.pop_back();

    thePlayers[currentPlayer]->addToHand(c);

    if (VERBOSE) cout << "Player " << currentPlayer << " draws " << cardTOString(c) << "\n";

    for (int i = 0; i < thePlayers.size(); i++)
    {
        if (currentPlayer != i)
        {
            thePlayers[i]->onOtherPlayerDraw(currentPlayer);
        }
    }
}

void advanceToNextPlayer(int direction, int & currentPlayer, int numPlayer)
{
    if (direction == 1)
    {
        currentPlayer = (currentPlayer + 1) % numPlayer;
    }
    if (direction == -1)
    {
        currentPlayer = (currentPlayer - 1);
        if (currentPlayer < 0)
        {
            currentPlayer = numPlayer - 1;
        }
    }
}

void playCardAction( Card & c,  int & currentPlayer, int numPlayer, int & direction, vector<Player *> & thePlayers, vector<Card> & theDeck, vector<Card> & discardPile, Card &topCardOfDiscard)
{
    for (int i = 0; i < thePlayers.size(); i++)
    {
        if (currentPlayer != i)
        {
            thePlayers[i]->onOtherPlayerMove(currentPlayer, c, c.getColorChange());
        }
    }

    //cout << "CardToPlay: " << cardTOString(c) << "\n";

    if (c.getColor() != BLACK && c.getNumber() >= 0 && c.getNumber() <= 9)
    {
        advanceToNextPlayer(direction, currentPlayer, numPlayer);
    }
    else if(c.getNumber() == 10) //skip
    {
        //cout << "skip\n";
        advanceToNextPlayer(direction, currentPlayer, numPlayer);
        advanceToNextPlayer(direction, currentPlayer, numPlayer);
    }
    else if (c.getNumber() == 11) //drawtwo
    {
        //cout << "Drawtwo\n";
        //cout << currentPlayer << endl;
        advanceToNextPlayer(direction, currentPlayer, numPlayer);
        //cout << currentPlayer << endl;
        drawCardToCurrentPlayer(currentPlayer, thePlayers, theDeck, discardPile);
        drawCardToCurrentPlayer(currentPlayer, thePlayers, theDeck, discardPile);

        advanceToNextPlayer(direction, currentPlayer, numPlayer);
        //cout << currentPlayer << endl;
    }
    else if (c.getNumber() == 12) //reverse
    {
        //cout << "reverse\n";
        direction = direction * -1;
        advanceToNextPlayer(direction, currentPlayer, numPlayer);
    }
    if (c.getColor() == BLACK)
    {
        if (c.getNumber() == 0)
        {
            advanceToNextPlayer(direction, currentPlayer, numPlayer);
        }
        if (c.getNumber() == 1)
        {
            advanceToNextPlayer(direction, currentPlayer, numPlayer);
            drawCardToCurrentPlayer(currentPlayer, thePlayers, theDeck, discardPile);
            drawCardToCurrentPlayer(currentPlayer, thePlayers, theDeck, discardPile);
            drawCardToCurrentPlayer(currentPlayer, thePlayers, theDeck, discardPile);
            drawCardToCurrentPlayer(currentPlayer, thePlayers, theDeck, discardPile);
            advanceToNextPlayer(direction, currentPlayer, numPlayer);
        }
    }
}

int hasPlayerWon(vector<Player *> players)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->getHandCopy().size() == 0)
        {
            return i;
        }
    }

    return -1;
}

void setCardCounts(vector<Player *> thePlayers, vector<int> & counts)
{
    counts.resize(thePlayers.size());

    for (int i = 0; i < thePlayers.size();i++)
    {
        counts[i] = thePlayers[i]->getHandCopy().size();
    }
}

void playGame(int numPlayers, vector<Player *> & thePlayers, vector<int> & scores)
{

    vector<Card> theDeck;
    vector<Card> discardPile;
    Card topCardOfDiscard;
    int currentPlayer=0;
    int direction = 1;

    vector<int> counts;



    createDeck(theDeck);
    shuffleDeck(theDeck);
    deal(theDeck, thePlayers);

    topCardOfDiscard = theDeck.back();
    theDeck.pop_back();
    while (topCardOfDiscard.getColor() == BLACK)
    {
        topCardOfDiscard = theDeck.back();
        theDeck.pop_back();
    }

    printGameState(currentPlayer, thePlayers, topCardOfDiscard);
    playCardAction(topCardOfDiscard, currentPlayer,numPlayers, direction,thePlayers,theDeck,discardPile, topCardOfDiscard);
    discardPile.push_back(topCardOfDiscard);
    printGameState(currentPlayer, thePlayers, topCardOfDiscard);

    Card temp;

    while (hasPlayerWon(thePlayers) == -1)
    {
        setCardCounts(thePlayers, counts);
        int index = thePlayers[currentPlayer]->makeMove(topCardOfDiscard,topCardOfDiscard.getColorChange(),false,scores,counts,direction);

        if (index != -1)
        {
            Card playedCard = thePlayers[currentPlayer]->getHandCopy()[index];
            if (VERBOSE) cout << "Player " << currentPlayer<< " ("<< thePlayers[currentPlayer]->getNum() << ") plays " << cardTOString(playedCard) << "\n";
            if (playedCard.getColor() == BLACK)
            {
                playedCard.setColorChange(thePlayers[currentPlayer]->getNewColor());
            }
            thePlayers[currentPlayer]->removeCardFromHand(index);
            playCardAction(playedCard, currentPlayer, numPlayers, direction, thePlayers, theDeck, discardPile, topCardOfDiscard);
            topCardOfDiscard = playedCard;
            discardPile.push_back(playedCard);
        }
        else
        {
            drawCardToCurrentPlayer(currentPlayer, thePlayers, theDeck, discardPile);
            setCardCounts(thePlayers,counts);
            int index = thePlayers[currentPlayer]->makeMove(topCardOfDiscard, topCardOfDiscard.getColorChange(), true, scores,counts,direction);
            if (index != -1)
            {
                Card playedCard = thePlayers[currentPlayer]->getHandCopy()[index];
                if (VERBOSE) cout << "Player "<<currentPlayer <<" plays "  << cardTOString(playedCard) << "\n";
                if (playedCard.getColor() == BLACK)
                {
                    playedCard.setColorChange(thePlayers[currentPlayer]->getNewColor());
                }
                thePlayers[currentPlayer]->removeCardFromHand(index);
                playCardAction(playedCard, currentPlayer, numPlayers, direction, thePlayers, theDeck, discardPile, topCardOfDiscard);
                topCardOfDiscard = playedCard;
                discardPile.push_back(playedCard);
            }
            else
            {
                advanceToNextPlayer(direction, currentPlayer, thePlayers.size());
                //do nothing as can do nothing
            }
        }

        //verifyGameStateCards(thePlayers, theDeck, discardPile);
        //cout << "press enter to advance to next play\n";

        printGameState(currentPlayer, thePlayers, topCardOfDiscard);
        //cin.ignore();
    }

    for (int i = 0; i < thePlayers.size(); i++)
    {
        for (int j = 0; j < thePlayers[i]->getHandCopy().size(); j++)
        {
            scores[i] += thePlayers[i]->getHandCopy()[j].getPoints();
        }
        thePlayers[i]->updateStats(thePlayers);
    }
    thePlayers[hasPlayerWon(thePlayers)]->wins++;
    for (int i = 0; i < thePlayers.size(); i++)
    {
        float totaldiff=0;
        for (int j = 0; j < thePlayers.size(); j++)
        {
            if (i != j)
            {
                totaldiff += thePlayers[j]->mostRecent;
            }
        }

        totaldiff /= thePlayers.size() - 1;

        for (int j = 0; j < 5; j++)
        {
            thePlayers[i]->diff[thePlayers[j]->whichAI] += (thePlayers[i]->mostRecent - totaldiff);
        }

    }
}

void printScores(vector<int> scores, vector<Player *> players)
{
    cout << "Scores:\n";
    for (int i = 0; i < scores.size(); i++)
    {
        cout << "Player " << ": " << scores[i]<<"   "<<players[i]->getName()<<"\n";
    }
    cout << "\n";
}

int main()
{

    vector<int> totalScores;
    vector<int> scores;

    /*
    *  PVP
    */
    /*int players = 18; //total players + 1 since its <=
    for (int i = 0; i < players; i++)
        totalScores.push_back(0);


    vector<Player *> theTotalPlayers;
    vector<Player *> thePlayers;

    for (int i = 0; i < players; i++)
    {
        theTotalPlayers.push_back(new Player(i, i + 4)); //the second paramter is the AI
    }


    for (int k = 0; k < 500; k++)
    {


        for (int j = 0; j < 50; j++)
        {
            srand(j + 2000);


            //1 game played, change the 1 to another number to play more games... like 50 at a time
            for (int i = 0; i < 5000; i++)
            {

                for (int e = 0; e < 5; e++)
                {
                    thePlayers.push_back(theTotalPlayers.back());
                    theTotalPlayers.pop_back();
                    scores.push_back(totalScores.back());
                    totalScores.pop_back();
                }

                for (int i = 0; i < thePlayers.size(); i++)
                {
                    thePlayers[i]->recreateAI();//the second paramter is the AI
                }
                for (int i = 0; i < thePlayers.size(); i++)
                {
                    thePlayers[i]->setNum(i);
                }

                playGame(5, thePlayers, scores);

                for (int e = 0; e < 5; e++)
                {
                    theTotalPlayers.push_back(thePlayers.back());
                    thePlayers.pop_back();
                    totalScores.push_back(scores.back());
                    scores.pop_back();
                }



                for (int i = 0; i < theTotalPlayers.size(); i++)
                {
                    if (rand() % 2 == 0)
                    {
                        Player * p = theTotalPlayers[i];
                        int x = rand() % theTotalPlayers.size();
                        theTotalPlayers[i] = theTotalPlayers[x];
                        theTotalPlayers[x] = p;

                        int t = totalScores[i];
                        totalScores[i] = totalScores[x];
                        totalScores[x] = t;
                    }
                }



                //if (VERBOSE || i % 1000 == 0) printScores(scores, thePlayers);
            }


            if (j % 100 == 0)
            {
                ofstream outfile("outpvp.txt", ios_base::app);

                for (int i = 0; i < theTotalPlayers.size(); i++)
                {
                    //finish average
                    //if(dynamic_cast<PlayerAI*>(thePlayers[i]->theAI) == nullptr)
                    theTotalPlayers[i]->printStats(theTotalPlayers, outfile);
                }
                outfile << "\n\n\n";
                outfile.close();
            }
        }

        cout << "\n\nStats accross all games: \n";
        printScores(scores, theTotalPlayers);

        ofstream outfile("outpvp.txt", ios_base::app);

        for (int i = 0; i < theTotalPlayers.size(); i++)
        {
            //finish average
            //if(dynamic_cast<PlayerAI*>(thePlayers[i]->theAI) == nullptr)
            theTotalPlayers[i]->printStats(theTotalPlayers, outfile);
        }
        outfile.close();
    }


    */


    //vs me
    for (int k = 0; k < 1; k++) //how many players
    {
        vector<int> scores;

        int players = 5;
        for (int i = 0; i < players; i++)
            scores.push_back(0);


        vector<Player *> thePlayers;

        for (int i = 0; i < players; i++)
        {
            thePlayers.push_back(new Player(i,i == 4 ? k+4 : i)); //the second paramter is the AI
        }
        cout << "Testing: " << thePlayers[4]->getName() << "\n";

        for (int j = 0; j < 500; j++)
        {
            srand(j + 20);

            //1 game played, change the 1 to another number to play more games... like 50 at a time
            for (int i = 0; i < 2500; i++)
            {
                for (int i = 0; i < thePlayers.size(); i++)
                {
                    thePlayers[i]->setNum(i);
                }

                playGame(players, thePlayers, scores);
                for (int i = 0; i < players; i++)
                {
                    thePlayers[i]->recreateAI();//the second paramter is the AI
                }

                for (int i = 0; i < thePlayers.size(); i++)
                {
                    if (rand() % 2 == 0)
                    {
                        Player * p = thePlayers[i];
                        int x = rand() % players;
                        thePlayers[i] = thePlayers[x];
                        thePlayers[x] = p;

                        int t = scores[i];
                        scores[i] = scores[x];
                        scores[x] = t;
                    }
                }

                for (int i = 0; i < thePlayers.size(); i++)
                {
                    thePlayers[i]->setNum(i);
                }

                //cout << i << "\n";

                //if (VERBOSE || i % 1000 == 0) printScores(scores, thePlayers);
            }
            if(j%100==0)
                cout << j << "\n";
        }

        cout << "\n\nStats accross all games: \n";
        printScores(scores, thePlayers);

        ofstream outfile("out.txt", ios_base::app);

        for (int i = 0; i < thePlayers.size(); i++)
        {
            //thePlayers[i]->printStats(thePlayers, outfile);
            thePlayers[i]->printAbrvStats(thePlayers, outfile);
        }
        outfile.close();
        cout << "k was: " << k << "\n";
    }

    return 0;
    cin.ignore(100);
}

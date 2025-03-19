# UNO Game Simulator

This project is a C++ implementation of a UNO card game simulator designed to test and compare different AI strategies against each other in the classic card game UNO.

## Overview

The UNO Game Simulator allows you to pit different AI algorithms against each other to see which strategy performs best in the long run. The project includes several pre-built AI implementations with varying strategies and provides a framework for creating and testing your own UNO AI algorithms.

## Game Rules

The simulator implements standard UNO rules:

- Players take turns playing cards that match either the color or number of the previous card
- Special cards include:
  - Skip (10): Skips the next player
  - Reverse (12): Reverses the playing direction
  - Draw Two (11): Forces the next player to draw two cards and skip their turn
  - Wild (BLACK, 0): Allows the player to choose the next color
  - Draw Four (BLACK, 1): Forces the next player to draw four cards, skip their turn, and allows the player to choose the next color (can only be played if player has no matching color)

## Project Structure

- `AI.h/cpp`: Base abstract class for all AI implementations
- `Card.h/cpp`: Implementation of UNO cards and their behaviors
- `Player.h/cpp`: Player class that manages the hand of cards and uses an AI instance for decision making
- Various AI implementations:
  - `TestAI`: A simple random-play implementation
  - `v001` through `v008`: Progressive improvements on AI strategies


## How to Build

The project uses CMake for building. To build the project:

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Simulator

After building, run the executable:

```bash
./HarnessedAI
```

The simulator will run multiple games between the different AI implementations and output statistics on performance.

## Creating Your Own AI

To create your own UNO AI strategy:

1. Create a new class that inherits from the `AI` base class (see `TestAI` for a simple example)
2. Implement all required methods:
   - `makeMove`: Core method that determines which card to play
   - `getNewColor`: Returns the color to choose when playing a wild card
   - `onOtherPlayerMove`: Called when another player makes a move (useful for tracking game state)
   - `onOtherPlayerDraw`: Called when another player draws a card
   - `getName`: Returns the name of your AI

3. Add your new AI class to the `Player.cpp` constructor to include it in the simulation

## AI Strategy Considerations

When developing your UNO AI, consider these strategies:

- Track cards played to estimate what's left in other players' hands
- Count colors to make optimal wild card color selections
- Save powerful cards (like Draw Four, Skip, Reverse) for strategic moments
- Adapt strategy based on the number of cards opponents have
- Consider the direction of play when deciding which cards to play

## Statistics and Analysis

The simulator tracks various statistics to evaluate AI performance:

- Average hand size
- Average points per hand
- Total wins
- Special cards left in hand when other players win

These statistics help determine which strategies perform best in different scenarios.


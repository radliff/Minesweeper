//
// Created by Radliff Jeantinor on 11/19/23.
//

#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#endif //MINESWEEPER_MINESWEEPER_H
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Cell{
    bool _revealed;
    bool _hasFlag;
    bool _hasMine;
    int _numMines;
    int _numTiles;
public:
    Cell(){};
    void DrawCell(float x, float y);

    sf::RectangleShape cellRect;
};

class Board{
    int _rows = 0;
    int _cols = 0;
    vector<vector<Cell>> grid;
public:
    Board(){};
    void setDimen(const string& fileName);
    void generateBoard();
    void drawBoard(sf::RenderWindow &window);
};
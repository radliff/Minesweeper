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
    bool _revealed = false;
    bool _hasFlag;
    int _numMines;
    int _numTiles;
public:

    bool hasMine = false;

    Cell(){};
    void DrawCell(float x, float y, sf::RenderWindow &window);

    sf::RectangleShape cellRect;
};

class Board{
    int _rows = 0;
    int _cols = 0;
    int num_mines = 0;
    vector<vector<Cell>> grid;
public:
    Board(){};
    void setDimen(const string& fileName);
    void generateBoard();
    void setMines();
    int getMines();
    void drawBoard(sf::RenderWindow &window);
};
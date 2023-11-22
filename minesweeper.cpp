#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <random>
#include "minesweeper.h"

using namespace std;
// Welcome Window: 15 PTS
// board changes size & numMines based on values in board_config.cfg: 10 PTS

mt19937 random_mt(random_device{}());

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

float setCellHeight(const string& filename){
    int width;
    int height;
    int rowCount;
    int colCount;
    float cellHeight;
    string line;
    ifstream file(filename);
    if (!file.is_open()){
        cout << "The board config file is not open.";
        return 0;
    }
    else {
        getline(file, line);
        colCount = stoi(line);

        getline(file, line);
        rowCount = stoi(line);
    }
    width = colCount * 32;
    height = (rowCount * 32) + 100;
    file.close();
    cellHeight = (float)(width / colCount);
    return cellHeight;
}

const float CELLHEIGHT = setCellHeight("files/config.cfg");


void setDimen(int &width, int &height, const string &filename){
    int rowCount;
    int colCount;
    string line;
    ifstream file(filename);
    if (!file.is_open()){
        cout << "The board config file is not open.";
        return;
    }
    else {
        getline(file, line);
        colCount = stoi(line);

        getline(file, line);
        rowCount = stoi(line);
    }
    width = colCount * 32;
    height = (rowCount * 32) + 100;
    file.close();
}


// Texture manager functions
unordered_map<string, sf::Texture> textures;
sf::Texture& getTexture(const string& textureName) {
    auto result = textures.find(textureName);
    if (result == textures.end()){
        sf::Texture newTexture;
        newTexture.loadFromFile("images/" + textureName + ".png");
        if(!newTexture.loadFromFile("images/" + textureName + ".png")){
            cout << "Texture loading error." << endl;
        }
        textures[textureName] = newTexture;
        return textures[textureName];
    }
    else {
        return result->second;
    }
}

// Cell functions
sf::Texture hiddenCell = getTexture("tile_hidden");
sf::Texture mine = getTexture("mine");
void Cell::DrawCell(float x, float y, sf::RenderWindow &window) {
    this->cellRect.setSize(sf::Vector2f(CELLHEIGHT, CELLHEIGHT));
    this->cellRect.setTexture(&hiddenCell);
    this->cellRect.setPosition(x, y);
    window.draw(this->cellRect);
    if(hasMine){
        sf::RectangleShape mineRect(sf::Vector2f(CELLHEIGHT, CELLHEIGHT));
        mineRect.setTexture(&mine);
        mineRect.setPosition(x, y);
        window.draw(mineRect);
    }
}

// Board functions
void Board::setDimen(const string& fileName){
    ifstream file(fileName);
    string line;
    int rowCount;
    int colCount;
    if (!file.is_open()){
        cout << "The board config file is not open.";
        return;
    }
    else {
        getline(file, line);
        colCount = stoi(line);

        getline(file, line);
        rowCount = stoi(line);

        getline(file, line);
        this->num_mines = stoi(line);
    }
   _rows = rowCount;
    _cols = colCount;
}

int Board::getMines() {
    return num_mines;
}

void Board::generateBoard(){
    grid = vector<vector<Cell>>(_rows, vector<Cell>(_cols));
}

void Board::drawBoard(sf::RenderWindow &window) {

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            float x = j * CELLHEIGHT;
            float y = i * CELLHEIGHT;
            grid[i][j].DrawCell(x, y, window);
        }
    }
}

void Board::setMines() {
    int countMines = 0;
    while (countMines < num_mines) {
        int randomX, randomY;
        randomX = Random(0, _rows - 1);
        randomY = Random(0, _cols - 1);
        if (!grid[randomX][randomY].hasMine) {
            grid[randomX][randomY].hasMine = true;
            cout << "Set mine at... (" << randomX << ", " << randomY << ")\n";
            countMines += 1;
        }
    }
}


sf::Text makeText(const sf::Font& font, const string& input, int charSize, sf::Color color){
    sf::Text text;
    text.setString(input);
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    return text;
}

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x,y));
}


int main() {
    int width;
    int height;
    int letterCount = 0;

    Board board;
    board.setDimen("files/config.cfg");
    board.generateBoard();

    setDimen(width, height,  "files/config.cfg");

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    if (!font.loadFromFile("files/font.ttf")) {
        cout << "font didnt load :(" << endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "Welcome Window", sf::Style::Close);

    sf::Text welcomeText = makeText(font, "WELCOME TO MINESWEEPER", 24, sf::Color::White);

    setText(welcomeText, width / 2, (height / 2) - 150);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Text nameText = makeText(font, "Enter your name:", 20, sf::Color::White);
    setText(nameText, width / 2, (height / 2) - 75);
    nameText.setStyle(sf::Text::Bold);

    sf::Text userName = makeText(font, "", 18, sf::Color::Yellow);
    setText(userName, width / 2, (height / 2) - 45);
    userName.setStyle(sf::Text::Bold);

    sf::RectangleShape cursor;
    cursor.setSize(sf::Vector2f(2.5f, (float) (userName.getCharacterSize())));
    cursor.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

            if (event.type == sf::Event::TextEntered) {
                if (isalpha(static_cast<char>(event.text.unicode))) {
                    if (letterCount == 10) {
                        break;
                    }
                    letterCount++;
                    if (userName.getString().isEmpty()) {
                        userName.setString(userName.getString() + static_cast<char>(toupper(event.text.unicode)));
                    } else {
                        userName.setString(userName.getString() + static_cast<char>(tolower(event.text.unicode)));
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (letterCount >= 1) {
                        window.close();
                    } else {
                        break;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (letterCount >= 1) {
                        userName.setString(userName.getString().substring(0, userName.getString().getSize() - 1));
                        letterCount--;
                    } else {
                        break;
                    }
                }
            }
        }


        window.clear(sf::Color::Blue);

        window.draw(welcomeText);

        window.draw(nameText);

        setText(userName, width / 2, (height / 2) - 45);
        window.draw(userName);

        cursor.setPosition(userName.getPosition().x + userName.getGlobalBounds().width / 2, userName.getPosition().y - 10);
        if (letterCount < 10) {
            window.draw(cursor);
        }
        window.display();
    }
    vector<string> usernames;
    usernames.push_back(userName.getString());



    sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    board.setMines();
    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }
        gameWindow.clear(sf::Color::White);

        board.drawBoard(gameWindow);

        gameWindow.display();
    }
}


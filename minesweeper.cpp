#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
// Welcome Window: 15 PTS
// board changes size & numMines based on values in board_config.cfg: 10 PTS

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

sf::Text makeText(const sf::Font& font, const string& input, int charSize){
    sf::Text text;
    text.setString(input);
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::White);
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
    setDimen(width, height, "files/config.cfg");

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    if (!font.loadFromFile("files/font.ttf")){
        cout << "font didnt load :(" << endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "Welcome Window", sf::Style::Close);

    sf::Text welcomeText = makeText(font, "WELCOME TO MINESWEEPER", 24);

    setText(welcomeText, width / 2, (height / 2) - 150);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    window.close();
                }
            }
        }


        window.clear(sf::Color::Blue);
        window.draw(welcomeText);
        window.display();
    }

}

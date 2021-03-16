//#include <SFML/Graphics.hpp>
#include <iostream>

#include "board.hpp"

using namespace sf;



std::string typeToString(Piece_Type type) {
    if (type == PAWN) { return "PAWN"; }
    else if (type == ROOK) { return "ROOK"; }
    else if (type == KNIGHT) { return "KNIGHT"; }
    else if (type == BISHOP) { return "BISHOP"; }
    else if (type == QUEEN) { return "QUEEN"; }
    else if (type == KING) { return "KING"; }
    else { return "UNKNOWN"; }
}

/*
sf::Texture* EMPTY_TEXTURE = getTexture("EMPTY");

sf::Texture* WHITE_PIECE_TEXTURE[] = {
    getTexture("EMPTY"), getTexture("W_PAWN"), getTexture("W_ROOK"), getTexture("W_KNIGHT"), getTexture("W_BISHOP"), getTexture("W_QUEEN"), getTexture("W_KING"),
};

sf::Texture* BLACK_PIECE_TEXTURE[] = {
    getTexture("EMPTY"), getTexture("B_PAWN"), getTexture("B_ROOK"), getTexture("B_KNIGHT"), getTexture("B_BISHOP"), getTexture("B_QUEEN"), getTexture("B_KING"),
};
//*/


class Game {
public:
    Game();
    void main_loop();
    ~Game();
    sf::Texture getTexture(std::string);
    void updateSprites();
private:
    RenderWindow window;
    Vector2f resolution;
    Board board;
    Sprite* sprites[8][8];
    sf::Texture EMPTY_TEXTURE;
    sf::Texture* WHITE_PIECE_TEXTURE;
    sf::Texture* BLACK_PIECE_TEXTURE;
    Vector2i selected;
};

sf::Texture Game::getTexture(std::string x) {
    sf::Texture t = Texture();
    if (!t.loadFromFile("image/" + x + ".png")) { std::cout << x << " BROKE" << std::endl; }
    return t;
}

Game::~Game() { 
    for (int x = 0; x < 8; ++x) { for (int y = 0; y < 8; ++y) { delete sprites[x][y]; } } 
    delete[] WHITE_PIECE_TEXTURE;
    delete[] BLACK_PIECE_TEXTURE;
}

Game::Game() {
    //resolution.x = VideoMode::getDesktopMode().width;
    //resolution.y = VideoMode::getDesktopMode().height;
    resolution.x = 800;
    resolution.y = 900;
    window.create(VideoMode(resolution.x, resolution.y), "Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    EMPTY_TEXTURE = getTexture("EMPTY");
    WHITE_PIECE_TEXTURE = new sf::Texture[7];
    WHITE_PIECE_TEXTURE[0] = getTexture("EMPTY");
    WHITE_PIECE_TEXTURE[1] = getTexture("W_PAWN");
    WHITE_PIECE_TEXTURE[2] = getTexture("W_ROOK");
    WHITE_PIECE_TEXTURE[3] = getTexture("W_KNIGHT");
    WHITE_PIECE_TEXTURE[4] = getTexture("W_BISHOP");
    WHITE_PIECE_TEXTURE[5] = getTexture("W_QUEEN");
    WHITE_PIECE_TEXTURE[6] = getTexture("W_KING");
    BLACK_PIECE_TEXTURE = new sf::Texture[7];
    BLACK_PIECE_TEXTURE[0] = getTexture("EMPTY");
    BLACK_PIECE_TEXTURE[1] = getTexture("B_PAWN");
    BLACK_PIECE_TEXTURE[2] = getTexture("B_ROOK");
    BLACK_PIECE_TEXTURE[3] = getTexture("B_KNIGHT");
    BLACK_PIECE_TEXTURE[4] = getTexture("B_BISHOP");
    BLACK_PIECE_TEXTURE[5] = getTexture("B_QUEEN");
    BLACK_PIECE_TEXTURE[6] = getTexture("B_KING");
    
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            sprites[x][y] = new Sprite();
            sprites[x][y]->setPosition(100 * x, 750 - (100 * y));
            sprites[x][y]->scale(.5, .5);

            auto i = board.board[x][y].type;
            if (board.board[x][y].team == WHITE) { sprites[x][y]->setTexture(WHITE_PIECE_TEXTURE[board.board[x][y].type]); }
            else if (board.board[x][y].team == BLACK) { sprites[x][y]->setTexture(BLACK_PIECE_TEXTURE[board.board[x][y].type]); }
            else { sprites[x][y]->setTexture(EMPTY_TEXTURE); }
            //*/
        }
    }
    selected.x = -1; selected.y = -1;
}

void Game::updateSprites() {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            auto i = board.board[x][y].type;
            if (board.board[x][y].team == WHITE) { sprites[x][y]->setTexture(WHITE_PIECE_TEXTURE[board.board[x][y].type]); }
            else if (board.board[x][y].team == BLACK) { sprites[x][y]->setTexture(BLACK_PIECE_TEXTURE[board.board[x][y].type]); }
            else { sprites[x][y]->setTexture(EMPTY_TEXTURE); }
            //*/
        }
    }
}

void Game::main_loop() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (!window.isOpen()) { std::cout << "Closing!" << std::endl; break; }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i crnt;
            crnt.x = Mouse::getPosition(window).x / 100;
            crnt.y = (850 - Mouse::getPosition(window).y) / 100;
            for (auto i : board.getAllMoves(selected.x, selected.y)) {
                if (crnt == i) {
                    board.board[crnt.x][crnt.y] = board.board[selected.x][selected.y];
                    board.board[selected.x][selected.y] = Piece(EMPTY, NONE);
                    updateSprites();
                    break;
                }
            }
            selected = crnt;
            std::cout << selected.x << "," << selected.y << std::endl;
        }

        window.clear(Color::White);

        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                RectangleShape square(Vector2f(0,0));
                square.setSize(Vector2f(100, 100));
                square.setPosition(x * 100, 750 - (y * 100));
                if ((x + y) % 2) { square.setFillColor(Color(242, 225, 197)); }
                else { square.setFillColor(Color(99, 69, 50)); }
                window.draw(square);
                if (selected.x == x && selected.y == y) {
                    RectangleShape green(Vector2f(0,0));
                    green.setPosition(x * 100, 750 - (y * 100));
                    green.setSize(Vector2f(100, 100));
                    green.setFillColor(Color(0, 128, 0, 128));
                    window.draw(green);
                }
                window.draw(*(sprites[x][y]));
            }
        }

        if (board.board[selected.x][selected.y].type != EMPTY) {
            std::vector<Vector2i> valid_moves = board.getAllMoves(selected.x, selected.y);
            for (auto i : valid_moves) {
                RectangleShape valid(Vector2f(0, 0));
                valid.setPosition(i.x * 100, 750 - (i.y * 100));
                valid.setSize(Vector2f(100, 100));
                valid.setFillColor(Color(0, 255, 0, 128));
                window.draw(valid);
            }
        }

        window.display();

    }
}

int main() {
    std::cout << "Starting" << std::endl;
    Game game;
    game.main_loop();
}

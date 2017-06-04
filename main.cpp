#include <iostream>
#include <vector>
#include <random>


using namespace std;

class Square;
class Board;

enum pieceType {
    none, pawn, knight, bishop, rook, queen, king
};

enum pieceColour {
    white, black, noColour
};

struct position {
    int x;
    int y;
};

struct moveCombination {
    position from;
    position to;
};


class Piece {
protected:
    bool available;
    pieceColour colour = noColour;
    pieceType type = none;
    position pos;
    vector <position> possibleMoves;
public:
    pieceType getPieceType() { return type; }
    position setPosition(position pos) { this->pos = pos; }
    void removePiece() { this->type = none; }
    position getPosition() { return pos; }
    pieceColour getPieceColour() { return colour; }
    virtual bool isValid(vector<vector<Square>> squares, position from, position to){ return false; }
    virtual int generatePossibleMoves(vector<vector<Square>> squares, position pos){};
    virtual vector <position> getPossibleMoves(){ return possibleMoves; }
    virtual bool isChecked(vector<vector<Square>> squares, position pos){ return false; }
};


class Square {
private:
    Piece *piece, *capturedPiece;
    position pos;
public:
    Square();
    Piece* getPiece() { return piece; }
    void setPiece(Piece* piece) { this->piece = piece; }
    Piece* getCapturedPiece() { return capturedPiece; }
    Piece setCapturedPiece(Piece* capturedPiece) { this->capturedPiece = capturedPiece; }
    position getPosition(){ return pos; }
};

Square::Square() {
    this->pos = pos;
}


class King : public Piece {
private:
    vector<position> possibleMoves;
public:
    King(pieceColour colour, position pos);
    virtual int generatePossibleMoves(vector<vector<Square>> squares, position pos);
    virtual bool isValid(vector<vector<Square>> squares, position from, position to);
    vector <position> getPossibleMoves(){ return possibleMoves; }
    virtual bool isChecked(vector<vector<Square>> squares, position pos);
};

King::King(pieceColour colour, position pos) {
    available = true;
    type = king;
    this->colour = colour;
    this->pos = pos;
}

bool King::isChecked(vector<vector<Square>> squares, position pos) {
    bool check = false;
    Piece *piece;
    for (int i = pos.x+1; i < 8; ++i) {
        piece = squares[i][pos.y].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == rook) {
                return true;
            } else if (piece->getPieceType() == king and (i - piece->getPosition().x) == 1){
                return true;
            }
        }
    }
    for (int i = pos.y+1; i < 8; ++i) {
        piece = squares[pos.x][i].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == rook) {
                return true;
            } else if (piece->getPieceType() == king and (i - piece->getPosition().y) == 1){
                return true;
            }
        }
    }
    for (int i = pos.x-1; i >= 0; --i) {
        piece = squares[i][pos.y].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == rook) {
                return true;
            } else if (piece->getPieceType() == king and (piece->getPosition().x - i) == 1){
                return true;
            }
        }

    }
    for (int i = pos.y-1; i >= 0; --i) {
        piece = squares[pos.x][i].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == rook) {
                return true;
            } else if (piece->getPieceType() == king and (piece->getPosition().y - i) == 1){
                return true;
            }
        }
    }
    for (int i = pos.x+1, j = pos.y+1; i < 8 and j < 8; i++, j++) {
        piece = squares[i][j].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == bishop) {
                return true;
            } else if (piece->getPieceType() == king and ((i - piece->getPosition().x) == 1 and (j - piece->getPosition().y) == 1)){
                return true;
            }
        }
    }
    for (int i = pos.x-1, j = pos.y-1; i >= 0 and j >= 0; i--, j--) {
        piece = squares[i][j].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == bishop) {
                return true;
            } else if ((piece->getPieceType()==king or piece->getPieceType()==pawn) and ((piece->getPosition().x-i)==1 and (piece->getPosition().y-j) == 1)){
                return true;
            }
        }
    }
    for (int i = pos.x+1, j = pos.y-1; i < 8 and j >= 0; i++, j--) {
        piece = squares[i][j].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == bishop) {
                return true;
            } else if (piece->getPieceType() == king and ((i - piece->getPosition().x) == 1 and (piece->getPosition().y - j) == 1)){
                return true;
            }
        }
    }
    for (int i = pos.x-1, j = pos.y+1; j < 8 and i >= 0; j++, i--) {
        piece = squares[i][j].getPiece();
        if (piece->getPieceColour() == colour)
            break;
        else {
            if (piece->getPieceType() == none)
                continue;
            if (piece->getPieceType() == queen or piece->getPieceType() == bishop) {
                return true;
            } else if ((piece->getPieceType()==king or piece->getPieceType()==pawn) and ((j-piece->getPosition().y)==1 and (piece->getPosition().x-i)==1)){
                return true;
            }
        }
    }

    if (pos.x-2 >= 0 and pos.y+1 < 8 and (squares[pos.x-2][pos.y+1].getPiece()->getPieceColour() != colour) and (squares[pos.x-2][pos.y+1].getPiece()->getPieceType()==knight))
        return true;
    if (pos.x-1 >= 0 and pos.y+2 < 8 and (squares[pos.x-1][pos.y+2].getPiece()->getPieceColour() != colour) and (squares[pos.x-1][pos.y+2].getPiece()->getPieceType()==knight))
        return true;
    if (pos.x+1 < 8 and pos.y+2 < 8 and (squares[pos.x+1][pos.y+2].getPiece()->getPieceColour() != colour) and (squares[pos.x+1][pos.y+2].getPiece()->getPieceType()==knight))
        return true;
    if (pos.x+2 < 8 and pos.y+1 < 8 and (squares[pos.x+2][pos.y+1].getPiece()->getPieceColour() != colour) and (squares[pos.x+2][pos.y+1].getPiece()->getPieceType()==knight))
        return true;
    if (pos.x+2 < 8 and pos.y-1 >= 0 and (squares[pos.x+2][pos.y-1].getPiece()->getPieceColour() != colour) and (squares[pos.x+2][pos.y-1].getPiece()->getPieceType()==knight))
        return true;
    if (pos.x+1 < 8 and pos.y-2 >= 0 and (squares[pos.x+1][pos.y-2].getPiece()->getPieceColour() != colour) and (squares[pos.x+1][pos.y-2].getPiece()->getPieceType()==knight))
        return true;
    if (pos.x-1 >= 0 and pos.y-2 >= 0 and (squares[pos.x-1][pos.y-2].getPiece()->getPieceColour() != colour) and (squares[pos.x-1][pos.y-2].getPiece()->getPieceType()==knight))
        return true;
    if (pos.x-2 >= 0 and pos.y-1 >= 0 and (squares[pos.x-2][pos.y-1].getPiece()->getPieceColour() != colour) and (squares[pos.x-2][pos.y-1].getPiece()->getPieceType()==knight))
        return true;

    return check;
}

int King::generatePossibleMoves(vector<vector<Square>> squares, position pos) {
    possibleMoves.clear();
    if (pos.x+1 < 8 and pos.y+1 < 8 and (squares[pos.x+1][pos.y+1].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x+1, pos.y+1})))
        possibleMoves.push_back({pos.x+1, pos.y+1});
    if (pos.x-1 >= 0 and pos.y-1 >= 0 and (squares[pos.x-1][pos.y-1].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x-1, pos.y-1})))
        possibleMoves.push_back({pos.x-1, pos.y-1});
    if (pos.x+1 < 8 and pos.y-1 >= 0 and (squares[pos.x+1][pos.y-1].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x+1, pos.y-1})))
        possibleMoves.push_back({pos.x+1, pos.y-1});
    if (pos.x-1 >= 0 and pos.y+1 < 8 and (squares[pos.x-1][pos.y+1].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x-1, pos.y+1})))
        possibleMoves.push_back({pos.x-1, pos.y+1});
    if (pos.x-1 >= 0 and (squares[pos.x-1][pos.y].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x-1, pos.y})))
        possibleMoves.push_back({pos.x-1, pos.y});
    if (pos.y-1 >= 0 and (squares[pos.x][pos.y-1].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x, pos.y-1})))
        possibleMoves.push_back({pos.x, pos.y-1});
    if (pos.y+1 < 8 and (squares[pos.x][pos.y+1].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x, pos.y+1})))
        possibleMoves.push_back({pos.x, pos.y+1});
    if (pos.x+1 < 8 and (squares[pos.x+1][pos.y].getPiece()->getPieceColour() != colour) and !(isChecked(squares, {pos.x+1, pos.y})))
        possibleMoves.push_back({pos.x+1, pos.y});
    return (int)(possibleMoves.size());
}

bool King::isValid(vector<vector<Square>> squares, position from, position to) {
    bool condition = false;
    if (squares[to.x][to.y].getPiece()->getPieceType() == none or squares[to.x][to.y].getPiece()->getPieceColour() != colour) {
        generatePossibleMoves(squares, from);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            if (possibleMoves[i].x == to.x && possibleMoves[i].y == to.y) {
                condition = true;
                break;
            }
        }
    }
    return condition;
}


class Queen : public Piece {
private:
    vector<position> possibleMoves;
public:
    Queen(pieceColour colour, position pos);
    virtual int generatePossibleMoves(vector<vector<Square>> squares, position pos);
    virtual bool isValid(vector<vector<Square>> squares, position from, position to);
    vector <position> getPossibleMoves(){ return possibleMoves; }
};

Queen::Queen(pieceColour colour, position pos) {
    available = true;
    type = queen;
    this->colour = colour;
    this->pos = pos;
}

int Queen::generatePossibleMoves(vector<vector<Square>> squares, position pos) {

    possibleMoves.clear();
    for (int i = pos.x+1; i < 8; ++i) {
        if (squares[i][pos.y].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({i, pos.y});
        }
        else if (squares[i][pos.y].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, pos.y});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x-1; i >= 0; i--) {
        if (squares[i][pos.y].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({i, pos.y});
        }
        else if (squares[i][pos.y].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, pos.y});
            break;
        } else {
            break;
        }
    }
    for (int j = pos.y+1; j < 8; ++j) {
        if (squares[pos.x][j].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({pos.x, j});
        }
        else if (squares[pos.x][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({pos.x, j});
            break;
        } else {
            break;
        }
    }
    for (int j = pos.y-1; j >= 0; j--) {
        if (squares[pos.x][j].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({pos.x, j});
        }
        else if (squares[pos.x][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({pos.x, j});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x+1, j = pos.y+1; i < 8 and j < 8; ++i, ++j) {          //bottom diagonal right
        if (squares[i][j].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({i, j});
        }
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x+1, j = pos.y-1; i < 8 and j >= 0; i++, j--) {         //bottom diagonal left
        if (squares[i][j].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({i, j});
        }
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x-1, j = pos.y-1; i >= 0 and j >= 0; --i, --j) {        //top diagonal left
        if (squares[i][j].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({i, j});
        }
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x-1, j = pos.y+1; i >= 0 and j < 8; --i, ++j) {         //top diagonal left
        if (squares[i][j].getPiece()->getPieceType() == none) {
            possibleMoves.push_back({i, j});
        }
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    return (int)(possibleMoves.size());
}

bool Queen::isValid(vector<vector<Square>> squares, position from, position to) {
    bool condition = false;
    if (squares[to.x][to.y].getPiece()->getPieceType() == none or squares[to.x][to.y].getPiece()->getPieceColour() != colour) {
        generatePossibleMoves(squares, from);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            if (possibleMoves[i].x == to.x && possibleMoves[i].y == to.y) {
                condition = true;
                break;
            }
        }
    }
    return condition;
}


class Rook : public Piece {
private:
    vector<position> possibleMoves;
public:
    Rook(pieceColour colour, position pos);
    virtual int generatePossibleMoves(vector<vector<Square>> squares, position pos);
    virtual bool isValid(vector<vector<Square>> squares, position from, position to);
    vector <position> getPossibleMoves(){ return possibleMoves; }
};

Rook::Rook(pieceColour colour, position pos) {
    available = true;
    type = rook;
    this->colour = colour;
    this->pos = pos;
}

int Rook::generatePossibleMoves(vector<vector<Square>> squares, position pos) {
    possibleMoves.clear();
    for (int i = pos.x+1; i < 8; ++i) {
        if (squares[i][pos.y].getPiece()->getPieceType() == none)
            possibleMoves.push_back({i, pos.y});
        else if (squares[i][pos.y].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, pos.y});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x-1; i >= 0; i--) {
        if (squares[i][pos.y].getPiece()->getPieceType() == none)
            possibleMoves.push_back({i, pos.y});
        else if (squares[i][pos.y].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, pos.y});
            break;
        } else {
            break;
        }
    }
    for (int j = pos.y+1; j < 8; ++j) {
        if (squares[pos.x][j].getPiece()->getPieceType() == none)
            possibleMoves.push_back({pos.x, j});
        else if (squares[pos.x][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({pos.x, j});
            break;
        } else {
            break;
        }
    }
    for (int j = pos.y-1; j >= 0; j--) {
        if (squares[pos.x][j].getPiece()->getPieceType() == none)
            possibleMoves.push_back({pos.x, j});
        else if (squares[pos.x][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({pos.x, j});
            break;
        } else {
            break;
        }
    }
    return (int)(possibleMoves.size());
}

bool Rook::isValid(vector<vector<Square>> squares, position from, position to) {
    bool condition = false;
    if (squares[to.x][to.y].getPiece()->getPieceType() == none or squares[to.x][to.y].getPiece()->getPieceColour() != colour) {
        generatePossibleMoves(squares, from);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            if (possibleMoves[i].x == to.x && possibleMoves[i].y == to.y) {
                condition = true;
                break;
            }
        }
    }
    return condition;
}


class Bishop : public Piece {
private:
    vector<position> possibleMoves;
public:
    Bishop(pieceColour colour, position pos);
    virtual int generatePossibleMoves(vector<vector<Square>> squares, position pos);
    virtual bool isValid(vector<vector<Square>> squares, position from, position to);
    vector <position> getPossibleMoves(){ return possibleMoves; }
};

Bishop::Bishop(pieceColour colour, position pos) {
    available = true;
    type = bishop;
    this->colour = colour;
    this->pos = pos;
}

int Bishop::generatePossibleMoves(vector<vector<Square>> squares, position pos) {
    possibleMoves.clear();
    for (int i = pos.x+1, j = pos.y+1; i < 8 and j < 8; ++i, ++j) {         //bottom diagonal right
        if (squares[i][j].getPiece()->getPieceType() == none)
            possibleMoves.push_back({i, j});
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x+1, j = pos.y-1; i < 8 and j >= 0; i++, j--) {         //bottom diagonal left
        if (squares[i][j].getPiece()->getPieceType() == none)
            possibleMoves.push_back({i, j});
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x-1, j = pos.y-1; i >= 0 and j >= 0; --i, --j) {         //top diagonal left
        if (squares[i][j].getPiece()->getPieceType() == none)
            possibleMoves.push_back({i, j});
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    for (int i = pos.x-1, j = pos.y+1; i >= 0 and j < 8; --i, ++j) {         //top diagonal left
        if (squares[i][j].getPiece()->getPieceType() == none)
            possibleMoves.push_back({i, j});
        else if (squares[i][j].getPiece()->getPieceColour() != colour) {
            possibleMoves.push_back({i, j});
            break;
        } else {
            break;
        }
    }
    return (int)(possibleMoves.size());

}

bool Bishop::isValid(vector<vector<Square>> squares, position from, position to) {
    bool condition = false;
    if (squares[to.x][to.y].getPiece()->getPieceType() == none or squares[to.x][to.y].getPiece()->getPieceColour() != colour) {
        generatePossibleMoves(squares, from);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            if (possibleMoves[i].x == to.x && possibleMoves[i].y == to.y) {
                condition = true;
                break;
            }
        }
    }
    return condition;
}


class Knight : public Piece {
private:
    vector<position> possibleMoves;
public:
    Knight(pieceColour colour, position pos);
    virtual int generatePossibleMoves(vector<vector<Square>> square, position pos);
    virtual bool isValid(vector<vector<Square>> squares, position from, position to);
    vector <position> getPossibleMoves(){ return possibleMoves; }
};

Knight::Knight(pieceColour colour, position pos) {
    available = true;
    type = knight;
    this->colour = colour;
    this->pos = pos;
}

int Knight::generatePossibleMoves(vector<vector<Square>> squares, position pos) {
    possibleMoves.clear();

    if (pos.x-2 >= 0 and pos.y+1 < 8 and (squares[pos.x-2][pos.y+1].getPiece()->getPieceColour()  != colour))
        possibleMoves.push_back({pos.x-2, pos.y+1});
    if (pos.x-1 >= 0 and pos.y+2 < 8 and (squares[pos.x-1][pos.y+2].getPiece()->getPieceColour() != colour))
        possibleMoves.push_back({pos.x-1, pos.y+2});
    if (pos.x+1 < 8 and pos.y+2 < 8 and (squares[pos.x+1][pos.y+2].getPiece()->getPieceColour() != colour))
        possibleMoves.push_back({pos.x+1, pos.y+2});
    if (pos.x+2 < 8 and pos.y+1 < 8 and (squares[pos.x+2][pos.y+1].getPiece()->getPieceColour() != colour))
        possibleMoves.push_back({pos.x+2, pos.y+1});
    if (pos.x+2 < 8 and pos.y-1 >= 0 and (squares[pos.x+2][pos.y-1].getPiece()->getPieceColour() != colour))
        possibleMoves.push_back({pos.x+2, pos.y-1});
    if (pos.x+1 < 8 and pos.y-2 >= 0 and (squares[pos.x+1][pos.y-2].getPiece()->getPieceColour() != colour))
        possibleMoves.push_back({pos.x+1, pos.y-2});
    if (pos.x-1 >= 0 and pos.y-2 >= 0 and (squares[pos.x-1][pos.y-2].getPiece()->getPieceColour() != colour))
        possibleMoves.push_back({pos.x-1, pos.y-2});
    if (pos.x-2 >= 0 and pos.y-1 >= 0 and (squares[pos.x-2][pos.y-1].getPiece()->getPieceColour() != colour))
        possibleMoves.push_back({pos.x-2, pos.y-1});
    return (int)(possibleMoves.size());
}

bool Knight::isValid(vector<vector<Square>> squares, position from, position to) {
    bool condition = false;
    if (squares[to.x][to.y].getPiece()->getPieceColour() != colour) {
        generatePossibleMoves(squares, from);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            if (possibleMoves[i].x == to.x and possibleMoves[i].y == to.y)
                condition = true;
        }
    }
    return condition;
}


class Pawn : public Piece {
private:
    vector<position> possibleMoves;
    vector<position> captureMoves;
public:
    Pawn(pieceColour colour, position pos);
    virtual int generatePossibleMoves(vector<vector<Square>> squares, position pos);
    virtual bool isValid(vector<vector<Square>>, position from, position to);
    vector <position> getPossibleMoves(){ return possibleMoves; }
};

Pawn::Pawn(pieceColour colour, position pos) {
    available = true;
    type = pawn;
    this->colour = colour;
    this->pos = pos;
}

int Pawn::generatePossibleMoves(vector<vector<Square>> squares, position pos) {
    possibleMoves.clear();
    if (squares[pos.x][pos.y].getPiece()->getPieceColour() == black) {
        if (pos.x == 1 and squares[pos.x+2][pos.y].getPiece()->getPieceType() == none)
            possibleMoves.push_back({pos.x + 2, pos.y});
        if (pos.x + 1 < 8 and squares[pos.x+1][pos.y].getPiece()->getPieceType() == none)
            possibleMoves.push_back({pos.x + 1, pos.y});
        if (pos.x + 1 < 8 and pos.y + 1 < 8) {
            if(squares[pos.x+1][pos.y+1].getPiece()->getPieceColour() == white)
                possibleMoves.push_back({pos.x + 1, pos.y + 1});
        }
        if (pos.x + 1 < 8 and pos.y - 1 >= 0) {
            if(squares[pos.x+1][pos.y-1].getPiece()->getPieceColour() == white)
                possibleMoves.push_back({pos.x + 1, pos.y - 1});
        }
    } else {
        if (pos.x == 6 and squares[pos.x - 2][pos.y].getPiece()->getPieceType() == none)
            possibleMoves.push_back({pos.x - 2, pos.y});
        if (pos.x - 1 >= 0 and squares[pos.x-1][pos.y].getPiece()->getPieceType() == none)
            possibleMoves.push_back({pos.x - 1, pos.y});
        if (pos.x - 1 >= 0 and pos.y + 1 < 8) {
            if(squares[pos.x-1][pos.y+1].getPiece()->getPieceColour() == black)
                possibleMoves.push_back({pos.x - 1, pos.y + 1});
        }
        if (pos.x - 1 >= 0 and pos.y - 1 >= 0) {
            if(squares[pos.x-1][pos.y-1].getPiece()->getPieceColour() == black)
                possibleMoves.push_back({pos.x - 1, pos.y - 1});
        }
    }
    return (int)(possibleMoves.size());
}

bool Pawn::isValid(vector<vector<Square>> squares, position from, position to) {
    bool condition = false;
    if (squares[to.x][to.y].getPiece()->getPieceType() == none or (squares[to.x][to.y].getPiece()->getPieceColour() != colour)) {
        generatePossibleMoves(squares, from);
        for (int i = 0; i < possibleMoves.size(); ++i) {
            if (possibleMoves[i].x == to.x and possibleMoves[i].y == to.y)
                condition = true;
        }
    }
    return condition;
}


class None : public Piece {
public:
    None(){}
    None(position pos);
};

None::None(position pos) {
    this->pos = pos;
    type = none;
}


class Player {
private:
    vector<Piece*> pieceList;
public:
    int k = 1, q = 1, r = 2, b = 2, n = 2, p = 8;
    bool turn;
    pieceColour colour;
    int no_of_pieces;
    Player(pieceColour colour);
    void removePiece(int index);
    vector<Piece*> getPieceList() { return pieceList; }
    void initialize();
    double evaluate(vector<vector<Square>> square, Player op, vector<Piece*> plist);
    moveCombination getBestMove(Board board, Player op);
};

Player::Player(pieceColour colour) {
    no_of_pieces = 16;
    this->colour = colour;
}


void Player::initialize() {
    int i;
    if (colour == white) {
        turn = true;
        pieceList.push_back(new King(colour, {7, 4}));
        for (i = 0; i < 8; ++i) {
            pieceList.push_back(new Pawn(colour, {6, i}));
        }
        pieceList.push_back(new Rook(colour, {7, 0}));
        pieceList.push_back(new Rook(colour, {7, 7}));
        pieceList.push_back(new Knight(colour, {7, 1}));
        pieceList.push_back(new Knight(colour, {7, 6}));
        pieceList.push_back(new Bishop(colour, {7, 2}));
        pieceList.push_back(new Bishop(colour, {7, 5}));
        pieceList.push_back(new Queen(colour, {7, 3}));
    }
    if (colour == black) {
        turn = false;
        pieceList.push_back(new King(colour, {0, 4}));
        for (i = 0; i < 8; ++i) {
            pieceList.push_back(new Pawn(colour, {1, i}));
        }
        pieceList.push_back(new Rook(colour, {0, 0}));
        pieceList.push_back(new Rook(colour, {0, 7}));
        pieceList.push_back(new Knight(colour, {0, 1}));
        pieceList.push_back(new Knight(colour, {0, 6}));
        pieceList.push_back(new Bishop(colour, {0, 2}));
        pieceList.push_back(new Bishop(colour, {0, 5}));
        pieceList.push_back(new Queen(colour, {0, 3}));
    }
}

void Player::removePiece(int index) {
    if (pieceList[index]->getPieceType() == king)
        k--;
    else if(pieceList[index]->getPieceType() == queen)
        q--;
    else if(pieceList[index]->getPieceType() == rook)
        r--;
    else if(pieceList[index]->getPieceType() == bishop)
        b--;
    else if(pieceList[index]->getPieceType() == knight)
        n--;
    else if(pieceList[index]->getPieceType() == pawn)
        p--;
    pieceList.erase(pieceList.begin() + index);
    no_of_pieces--;
}


class Board {
private:
    vector<vector<Square>> squares;
public:
    Board();
    vector<vector<None>> blank;
    Piece getPiece(int fromX, int fromY);
    void initializeGame(Player player);
    bool occupySquare(position from, position to, Player &player);
    void display();
    vector<vector<Square>> &getSquares() { return squares; }
    void setSquares(vector<vector<Square>> &square);
};

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        vector<Square> squareRow;
        vector<None> blankRow;
        for (int j = 0; j < 8; ++j) {
            squareRow.push_back(*(new Square));
            blankRow.push_back(*(new None));
        }
        squares.push_back(squareRow);
        blank.push_back(blankRow);
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            blank[i][j].setPosition({i, j});
            squares[i][j].setPiece(&blank[i][j]);
        }
    }
}

void Board::setSquares(vector<vector<Square>> &square) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j].setPiece(square[i][j].getPiece());
        }
    }
}

Piece Board::getPiece(int fromX, int fromY) {
    return *squares[fromX][fromY].getPiece();
}

void Board::initializeGame(Player player) {
    int i, j;
    for (int k = 0; k < 16; ++k) {
        i = player.getPieceList()[k]->getPosition().x;
        j = player.getPieceList()[k]->getPosition().y;
        squares[i][j].setPiece(player.getPieceList()[k]);
    }
}

bool Board::occupySquare(position from, position to, Player &player) {
    if (!(squares[from.x][from.y].getPiece()->getPieceType() == none)) {
        if (squares[from.x][from.y].getPiece()->isValid(squares, from, to)) {
            if (squares[to.x][to.y].getPiece()->getPieceType() != none) {
                for (int i = 0; i < player.no_of_pieces; ++i) {
                    if (player.getPieceList()[i]->getPosition().x == to.x and player.getPieceList()[i]->getPosition().y == to.y) {
                        player.removePiece(i);
                        break;
                    }
                }
            }
            squares[to.x][to.y].setPiece(squares[from.x][from.y].getPiece());
            squares[from.x][from.y].getPiece()->setPosition({to.x, to.y});
            squares[from.x][from.y].setPiece(&blank[from.x][from.y]);
            return true;
        }
    }
    return false;
}

void Board::display() {
    pieceType type;
    pieceColour colour;
    cout << "  ";
    for (int k = 0; k < 8; ++k) {
        cout << " " << k << " ";
    }
    cout << endl;
    for (int i = 0; i < 8; ++i) {
        cout << i << " ";
        for (int j = 0; j < 8; ++j) {
            type = squares[i][j].getPiece()->getPieceType();
            colour = squares[i][j].getPiece()->getPieceColour();
            if (type != none) {
                switch (type) {
                    case pawn:
                        colour==black? cout << " p " : cout << " P ";
                        break;
                    case knight:
                        colour==black? cout << " n " : cout << " N ";
                        break;
                    case bishop:
                        colour==black? cout << " b " : cout << " B ";
                        break;
                    case rook:
                        colour==black? cout << " r " : cout << " R ";
                        break;
                    case queen:
                        colour==black? cout << " q " : cout << " Q ";
                        break;
                    case king:
                        colour==black? cout << " k " : cout << " K ";
                        break;
                }
            } else {
                cout << " - ";
            }
        }
        cout << endl;
    }cout << endl;
}


double Player::evaluate(vector<vector<Square>> square, Player op, vector<Piece*> plist) {
    double score = (200*(k-op.k) + 9*(q-op.q) + 5*(r-op.r) + 3*(b-op.b + n-op.n) + 1*(p-op.p));
    for (int i = 0; i < plist.size(); ++i) {
        plist[i]->generatePossibleMoves(square, plist[i]->getPosition());
        score += 0.1 * (plist[i]->getPossibleMoves().size());

    }
    for (int i = 0; i < op.getPieceList().size(); ++i) {
        score -= 0.1*(op.getPieceList()[i]->generatePossibleMoves(square, op.getPieceList()[i]->getPosition()));
    }
    return score;
}

moveCombination Player::getBestMove(Board board, Player op) {
    Board board_dup;
    board_dup.setSquares(board.getSquares());
    Player op_dup = op;
    position fromMove, bestMove;
    double maxScore = -999;
    double curScore;
    int fromx, fromy, tox, toy;
    bool kill = false;
    bool list = false;
    Piece *piece;
    for (int i = 0; i < pieceList.size(); ++i) {
        pieceList[i]->generatePossibleMoves(board.getSquares(), pieceList[i]->getPosition());
        fromx = pieceList[i]->getPosition().x;
        fromy = pieceList[i]->getPosition().y;
        cout << endl;
        for (int l = 0; l < pieceList[i]->getPossibleMoves().size(); ++l) {
            cout << pieceList[i]->getPossibleMoves()[l].x << pieceList[i]->getPossibleMoves()[l].y << " | ";
        }
        cout << endl;
        for (int j = 0; j < pieceList[i]->getPossibleMoves().size(); ++j) {
            op_dup = op;
            tox = pieceList[i]->getPossibleMoves()[j].x;
            toy = pieceList[i]->getPossibleMoves()[j].y;
            if (board_dup.getSquares()[tox][toy].getPiece()->getPieceType() != none) {
                kill = true;
                piece = board_dup.getSquares()[tox][toy].getPiece();
                if (board_dup.getSquares()[tox][toy].getPiece()->getPieceType() == pawn)
                    op_dup.p--;
                else if (board_dup.getSquares()[tox][toy].getPiece()->getPieceType() == rook)
                    op_dup.r--;
                else if (board_dup.getSquares()[tox][toy].getPiece()->getPieceType() == bishop)
                    op_dup.b--;
                else if (board_dup.getSquares()[tox][toy].getPiece()->getPieceType() == knight)
                    op_dup.n--;
                else if (board_dup.getSquares()[tox][toy].getPiece()->getPieceType() == queen)
                    op_dup.q--;
                else if (board_dup.getSquares()[tox][toy].getPiece()->getPieceType() == king)
                    op_dup.k--;
            } else {
                kill = false;
            }
            board_dup.getSquares()[tox][toy].setPiece(board_dup.getSquares()[fromx][fromy].getPiece());
            pieceList[i]->setPosition({tox, toy});
            board_dup.getSquares()[fromx][fromy].setPiece(&board_dup.blank[fromx][fromy]);
            curScore = evaluate(board_dup.getSquares(), op_dup, pieceList);
            cout << curScore << endl;
            if (curScore > maxScore) {
                maxScore = curScore;
                fromMove = {fromx, fromy};
                bestMove = {tox, toy};
            }
            pieceList[i]->setPosition({fromx, fromy});
            board_dup.getSquares()[fromx][fromy].setPiece(board_dup.getSquares()[tox][toy].getPiece());
            if (kill) {
                board_dup.getSquares()[tox][toy].setPiece(piece);
            } else {
                board_dup.getSquares()[tox][toy].setPiece(&board_dup.blank[tox][toy]);
            }
            pieceList[i]->generatePossibleMoves(board.getSquares(), pieceList[i]->getPosition());
        }
    }
    return {fromMove, bestMove};
}



int main() {
    Player p1(white);
    p1.initialize();

    Player p2(black);
    p2.initialize();

    Board board;
    board.initializeGame(p1);
    board.initializeGame(p2);
    //board.display();

    int fromX, fromY, toX, toY;
    moveCombination comp;
    fromX = 1;
    while (fromX != 0) {
        cin >> fromX;

        comp = p1.getBestMove(board, p2);
        cout << comp.from.x << comp.from.y << " to " << comp.to.x << comp.to.y << endl;
        board.occupySquare({comp.from.x, comp.from.y}, {comp.to.x, comp.to.y}, p2);
        board.display();


        cin >> fromX;

        comp = p2.getBestMove(board, p1);
        cout << comp.from.x << comp.from.y << " to " << comp.to.x << comp.to.y << endl;
        board.occupySquare({comp.from.x, comp.from.y}, {comp.to.x, comp.to.y}, p1);
        board.display();
    }


    /*while (toX or toY or fromX or fromY) {
        cin >> fromX >> fromY;
        cin >> toX >> toY;
        if (toX < 8 and toY < 8 and fromX < 8 and fromY < 8) {
            if (board.getPiece(fromX, fromY).getPieceColour() == p1.colour) {
                if (board.occupySquare({fromX, fromY}, {toX, toY}, p2)) {
                    p2.turn = true;
                    p1.turn = false;
                }
            }
            if (board.getPiece(fromX, fromY).getPieceColour() == p2.colour) {
                comp = p2.getBestMove(board, p1);
                if (board.occupySquare({comp.from.x, comp.from.y}, {comp.to.x, comp.to.y}, p1)) {
                    p1.turn = true;
                    p2.turn = false;
                }
            }
        }
        board.display();
    }*/
    return 0;
}
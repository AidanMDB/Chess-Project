
#include "ChessPiece.hh"

using Student::ChessBoard;

namespace Student {

    ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column) : _board(board) {
        _color = color;
        _row = row;
        _column = column;
    }
    
    Color ChessPiece::getColor() {
        return _color;
    }

    Type ChessPiece::getType() { // where do i get the type from?
        return _type;
    }

    int ChessPiece::getRow() {
        return _row;
    }

    int ChessPiece::getColumn() {
        return _column;
    }

    void ChessPiece::setPosition(int row, int column) {
        _row = row;
        _column = column;
        
    }

}
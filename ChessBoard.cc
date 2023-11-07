// as part of a personal build of chess board have a stack or list with all the pieces and their locations
// then loop through that stack to see if it has a valid move or what not instead of looping through the entire 
// chess board



#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include <iostream>

using Student::ChessBoard;

ChessBoard::ChessBoard(int numRow, int numCol) {
    numRows = numRow;
    numCols = numCol;
    board = std::vector<std::vector<ChessPiece*>> (numRow, std::vector<ChessPiece*>(numCol, nullptr)); //creates 2-d vector matrix of given row and col size
    white_King_Locs = nullptr;
    black_King_Locs = nullptr;
}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
    if (getPiece(startRow, startColumn) != nullptr) { // make sure a piece is not already there if there is delete it
        delete board.at(startRow).at(startColumn);
    }

    if (ty == Pawn) {
        PawnPiece *p = new PawnPiece(*this, col, startRow, startColumn);
        board[startRow][startColumn] = p;
    }
    else if (ty == Rook) {
        RookPiece *r = new RookPiece(*this, col, startRow, startColumn);
        board[startRow][startColumn] = r;
    }
    else if (ty == Bishop) {
        BishopPiece *b = new BishopPiece(*this, col, startRow, startColumn);
        board[startRow][startColumn] = b;
    }
    else if (ty == King) {
        KingPiece *k = new KingPiece(*this, col, startRow, startColumn);
        board[startRow][startColumn] = k;
        if (k->getColor() == White) {
            white_King_Locs = k;
        }
        else {
            black_King_Locs = k;
        }
    }
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    

    if (getPiece(fromRow, fromColumn) != nullptr && getPiece(fromRow, fromColumn)->getColor() != turn) {
        return false;
    }

    bool valid = isValidMove(fromRow, fromColumn, toRow, toColumn);

    if (valid) {
        if (board.at(toRow).at(toColumn) != nullptr && board.at(toRow).at(toColumn)->getType() == King) { // if its a king thats being captured set white_King_Locs to nullptr;
            if (board.at(toRow).at(toColumn)->getColor() == Black) {
                black_King_Locs = nullptr;
            }
            else {
                white_King_Locs = nullptr;
            } 
        }
        delete board.at(toRow).at(toColumn);       // delete piece at moved to location
        board.at(toRow).at(toColumn) = nullptr;
        getPiece(fromRow, fromColumn)->setPosition(toRow, toColumn);    // change pieces row and col in ChessPiece
        board.at(toRow).at(toColumn) = getPiece(fromRow, fromColumn);   // move to pointer to new board location
        board.at(fromRow).at(fromColumn) = nullptr;                     // set old pointer to nullptr
        //delete board.at(fromRow).at(fromColumn);   // delete Piece from old location
        turn = (turn == White) ? Black : White;     // changes the turn to opposite of whatever it currently is

    }
    return valid;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
    
    ChessPiece* from_piece = getPiece(fromRow, fromColumn);
    ChessPiece* to_piece = getPiece(toRow, toColumn);
    // || from_piece->getColor() != turn
    if (from_piece == nullptr) {  // makes sure piece is same color as the side who's turn it is (if it exists)
        return false;
    }
    if (toRow > getNumRows() || toColumn > getNumCols() || toRow < 0 || toColumn < 0) {     // checks if move is outside bounds of board
        return false;
    }
    if (to_piece != nullptr) {      //makes sure piece is not moving to a square that already has a piece of the same color (this covers moving to same position)
        if (from_piece->getColor() == to_piece->getColor()) { 
            return false;
        }
    }
    /*     
    if (fromRow == toRow && fromColumn == toColumn) {   //makes sure piece is not moving to the same position
        return false;
    } */


    bool validMove = from_piece->canMoveToLocation(toRow, toColumn);
    if (!validMove) { // if move of piece is invalid return false
        return validMove;
    }

    validMove = isKingSafe(fromRow, fromColumn, toRow, toColumn);


    return validMove;    
}

bool ChessBoard::isPieceUnderThreat(int row, int column) {
    ChessPiece* piece = getPiece(row, column);

    if (piece == nullptr) { // check if location has a piece
        return false;
    } 

    for (int check_row = 0; check_row < getNumRows(); check_row++) {
        for (int check_col = 0; check_col < getNumCols(); check_col++) {    // search through the whole board
            ChessPiece* check_piece = getPiece(check_row, check_col);       // grab the location
            if (check_piece != nullptr && check_piece->getColor() != piece->getColor()) {     // check each position for a piece and that its not the same color
                // can't just return directly otherwise would only check the first piece
                if (check_piece->canMoveToLocation(row, column)) {
                    return true;
                }

                // had it calling is valid move because isValidMove handled if they were in the same position
                // doesn't have to call isValidMove just use can move to location
                /*
                if (isValidMove(check_row, check_col, row, column)) {       // see if that piece can move to row,column
                    return true;                                            // if it can then row, column is under threat
                }  */
            } 
        }
    }
    return false;
}


std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}

// returns false if king is checked
bool ChessBoard::isKingSafe(int fromRow, int fromColumn, int toRow, int toColumn) {

    ChessPiece* king_loc = getPiece(fromRow, fromColumn)->getColor() == White ? white_King_Locs : black_King_Locs;
    if (king_loc == nullptr) {
        return true;
    }


    // performs piece movement
    ChessPiece* temp_to = board.at(toRow).at(toColumn);     // store piece 
    //board.at(toRow).at(toColumn) == nullptr;       // set piece at moved to location to nullptr
    getPiece(fromRow, fromColumn)->setPosition(toRow, toColumn);    // change pieces row and col in ChessPiece
    board.at(toRow).at(toColumn) = getPiece(fromRow, fromColumn);   // move to_pointer to new board location
    board.at(fromRow).at(fromColumn) = nullptr;                     // set old pointer to nullptr
    //turn = (turn == White) ? Black : White;     // changes the turn to opposite of whatever it currently is

    // choosing which king we are checking the validity of
    

    // determining if that king is now under threat

    //std::cout << displayBoard().str() << std::endl;
    //std::cout << king_loc->getRow() << "," << king_loc->getColumn() << std::endl;
    bool check = !isPieceUnderThreat(king_loc->getRow(), king_loc->getColumn());

/*     bool check = true;  // check = true   :  king is not in check
                        // check = false  :  king is in check
    for (int check_row = 0; check_row < getNumRows(); check_row++) {
        for (int check_col = 0; check_col < getNumCols(); check_col++) {    // search through the whole board
            if (getPiece(check_row, check_col) != nullptr) {                // check each position for a piece
                if (isPieceUnderThreat(check_row, check_col, king_loc->getRow(), king_loc->getColumn())) {
                    check = false;       // if a piece can move there king is in check
                }
            }
        }
    } */

    board.at(fromRow).at(fromColumn) = getPiece(toRow, toColumn);   // move from_piece back to old position
    board.at(toRow).at(toColumn) = temp_to;                         // put to_piece back in its original spot
    getPiece(fromRow, fromColumn)->setPosition(fromRow, fromColumn);    // reset from_piece's row and col in ChessPiece

    return check;
}



ChessBoard::~ChessBoard() {
    for (int i = 0; i < getNumRows(); i++) {        // row
        for (int j = 0; j < getNumCols(); j++) {    // col
            delete getPiece(i,j);
        }
    }
}
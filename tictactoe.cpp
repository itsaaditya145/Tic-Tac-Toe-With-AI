#include <iostream>
using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

char player = 'X';
char ai = 'O';

void displayBoard() {
    cout << "\n";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n";
}

bool isMovesLeft() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return true;
    return false;
}

int evaluate() {
    // Rows
    for(int row = 0; row < 3; row++) {
        if(board[row][0] == board[row][1] &&
           board[row][1] == board[row][2]) {
            if(board[row][0] == ai) return +10;
            else if(board[row][0] == player) return -10;
        }
    }

    // Columns
    for(int col = 0; col < 3; col++) {
        if(board[0][col] == board[1][col] &&
           board[1][col] == board[2][col]) {
            if(board[0][col] == ai) return +10;
            else if(board[0][col] == player) return -10;
        }
    }

    // Diagonals
    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2]) {
        if(board[0][0] == ai) return +10;
        else if(board[0][0] == player) return -10;
    }

    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0]) {
        if(board[0][2] == ai) return +10;
        else if(board[0][2] == player) return -10;
    }

    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();

    if(score == 10) return score;
    if(score == -10) return score;
    if(!isMovesLeft()) return 0;

    if(isMax) {
        int best = -1000;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = ai;

                    best = max(best, minimax(false));

                    board[i][j] = temp; // Backtracking
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = player;

                    best = min(best, minimax(true));

                    board[i][j] = temp; // Backtracking
                }
            }
        }
        return best;
    }
}

pair<int,int> findBestMove() {
    int bestVal = -1000;
    pair<int,int> bestMove = {-1,-1};

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = ai;

                int moveVal = minimax(false);

                board[i][j] = temp;

                if(moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

void playerMove() {
    int move;
    cout << "Enter your move (1-9): ";
    cin >> move;

    int row = (move-1)/3;
    int col = (move-1)%3;

    if(board[row][col] != 'X' && board[row][col] != 'O')
        board[row][col] = player;
    else {
        cout << "Invalid move! Try again.\n";
        playerMove();
    }
}

void aiMove() {
    pair<int,int> move = findBestMove();
    board[move.first][move.second] = ai;
}

int main() {
    int choice;
    cout << "1. Player vs Player\n";
    cout << "2. Player vs AI\n";
    cout << "Choose mode: ";
    cin >> choice;

    displayBoard();

    while(true) {
        if(choice == 1) {
            playerMove();
            displayBoard();
        } else {
            playerMove();
            displayBoard();
            if(evaluate() == -10 || !isMovesLeft()) break;

            aiMove();
            cout << "AI moved:\n";
            displayBoard();
        }

        int result = evaluate();
        if(result == 10) {
            cout << "AI Wins!\n";
            break;
        } else if(result == -10) {
            cout << "Player Wins!\n";
            break;
        } else if(!isMovesLeft()) {
            cout << "Draw!\n";
            break;
        }
    }

    return 0;
}
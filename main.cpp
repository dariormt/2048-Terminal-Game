#include <iostream>
#include <thread>
#include <vector>

#include "graphics.hpp"

// variables
int boardSize = 4;      // if i do a vector of vectors, i can do this, yay!!
                        //  size, but array of an array dosn't like it
int startingPieces = 2; // Customize easyly
int piecesToSpawn = 1;
int numberToGet = 2048;

int score = 0;
int maxscore = 3950; // hard-coded highscore it works for now

int moves = 0;

// bool retry = true; //fuck the compiler, why does an int work and a bool not

int state = 1; // current game state 1 replay, 0 exit;

std::string ColorParser(
    int numb) { // parses color depending on num using ascii color escapes
  switch (numb) {
  case 0:
    return "\033[1;30m0\033[0m";
    break;
  case 2:
    return "\033[1;32m2\033[0m";
    break;
  case 4:
    return "\033[1;34m4\033[0m";
    break;
  case 8:
    return "\033[1;36m8\033[0m";
    break;
  case 16:
    return "\033[1;33m16\033[0m";
    break;
  case 32:
    return "\033[1;31m32\033[0m";
    break;
  case 64:
    return "\033[1;35m64\033[0m";
    break;
  case 128:
    return "\033[1;37m128\033[0m";
    break;
  case 256:
    return "\033[1;91m256\033[0m";
    break;
  case 512:
    return "\033[1;95m512\033[0m";
    break;
  case 1024:
    return "\033[1;96m1024\033[0m";
    break;
  case 2048:
    return "\033[1;97m2048\033[0m";
    break;
  default:
    return std::to_string(numb);
    break;
  }
}

bool IsFull(std::vector<std::vector<int>> &board) {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (board[i][j] == 0) { // empty state
        return false;
      }
    }
  }
  // if not empty
  return true;
}

void SpawnTile(std::vector<std::vector<int>> &board, int ammount) {
  if (IsFull(board)) { // if it's full we can't spawn a numb
    return;
  }
  for (int i = 0; i < ammount; i++) { // does iterations for each piece
    if (IsFull(board)) {              // if it's full we can't spawn a numb
      return;
    }

    int num;
    while (true) // keep repeating until we get an empty space
    {
      int row = rand() % boardSize; // Random pos
      int col = rand() % boardSize;
      if (rand() % 2 == 0) { // 50/50 prob to be 2 or 4
        num = 2;
      } else {
        num = 4;
      }

      if (board[row][col] == 0) { // if the space is empty, set space and exit
                                  // loop
        board[row][col] = num;
        break;
      }
    }
  }
}

void InitBoard(std::vector<std::vector<int>> &board) { // Board initialization

  srand(time(NULL)); // setup random

  board.resize(boardSize);
  for (int i = 0; i < boardSize; i++) {
    board[i].resize(boardSize);
    for (int j = 0; j < boardSize; j++) {
      board[i][j] = 0; // initialize all of the array
    }
  }
  SpawnTile(board, startingPieces);
}

int SeeNumlenght(int numb) {
  std::string txt = std::to_string(numb);
  return txt.size();
}

void DrawTile(int num, int pos) {
  switch (SeeNumlenght(num)) {
  case 1:
    if (pos == 0) { // Change the display of the number if it is at the
                    // begining, end or between
      std::cout << "│ " << ColorParser(num) << " ";
    } else if (pos == boardSize - 1) {
      std::cout << "│ " << ColorParser(num) << " │";
    } else {
      std::cout << "│ " << ColorParser(num) << " ";
    }
    break;
  case 2:
    if (pos == 0) { // Change the display of the number if it is at the
                    // begining, end or between
      std::cout << "│" << ColorParser(num) << " ";
    } else if (pos == boardSize - 1) {
      std::cout << "│" << ColorParser(num) << " │";
    } else {
      std::cout << "│" << ColorParser(num) << " ";
    }
    break;
  case 3:
    if (pos == 0) { // Change the display of the number if it is at the
                    // begining, end or between
      std::cout << "│" << ColorParser(num);
    } else if (pos == boardSize - 1) {
      std::cout << "│" << ColorParser(num) << "│";
    } else {
      std::cout << "│" << ColorParser(num);
    }
    break;
  case 4:
    if (pos == 0) { // Change the display of the number if it is at the
                    // begining, end or between
      std::cout << "" << ColorParser(num);
    } else if (pos == boardSize - 1) {
      std::cout << "" << ColorParser(num) << "│";
    } else {
      std::cout << "" << ColorParser(num);
    }
    break;
  default:
    std::cout << "│! ";
    break;
  }
}

void DrawSeparation(int h) { // implements procedural box gen
  switch (h) {
  case -1:
    std::cout << "┌";
    for (int i = 0; i < boardSize - 1; i++) { // each column
      std::cout << "───┬";
    }
    std::cout << "───┐\n";
    break;
  case 0:
    std::cout << "├";
    for (int i = 0; i < boardSize - 1; i++) { // each column
      std::cout << "───┼";
    }
    std::cout << "───┤\n";
    break;
  case 1:
    std::cout << "└";
    for (int i = 0; i < boardSize - 1; i++) { // each column
      std::cout << "───┴";
    }
    std::cout << "───┘\n";
    break;
  default:
    std::cout << "!!!!!!!!!!!!!!!!\n"; // end line
    break;
  }
}

void DrawGame(std::vector<std::vector<int>> &board) { // Board Drawing

  // Clear the console
  std::cout << "\033[2J\033[1;1H";
  // Draw Cover
  std::cout << art[0];

  std::cout << "Score: " << score << "  |  Highscore: " << maxscore
            << "  |  Moves: " << moves << '\n';

  for (int i = 0; i < boardSize; i++) {
    if (i == 0) { // create box initial separation
      DrawSeparation(-1);
    } else { // create box separation between rows
      DrawSeparation(0);
    }

    for (int j = 0; j < boardSize; j++) {

      DrawTile(board[i][j], j);
    }
    std::cout << '\n'; // Do new line
  }

  DrawSeparation(1);

  std::cout << std::endl; // End and flush
}

bool IsGameOverState(std::vector<std::vector<int>> &board) {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (board[i][j] == 0) { // check if has empty cells
        return false;
      }
      if (i >= 1 &&
          board[i][j] == board[i - 1][j]) { // check if can move up/down
        return false;
      }
      if (j >= 1 &&
          board[i][j] == board[i][j - 1]) { // check if can move left right
        return false;
      }
    }
  }
  return true;
}

bool IsWinState(std::vector<std::vector<int>> &board) {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (board[i][j] == numberToGet) { // if contains numb
        return true;
      }
    }
  }
  // if not found
  return false;
}

bool MoveUp(std::vector<std::vector<int>> &board) {
  bool moved = false;
  for (int j = 0; j < boardSize; j++) {
    for (int i = 1; i < boardSize; i++) {
      if (board[i][j] != 0) { // if cell is not empty
        int k = i;
        while (k > 0 && board[k - 1][j] == 0) { // Moves each full cell
                                                // until none of
                                                // them can be moved further
          board[k - 1][j] = board[k][j];
          board[k][j] = 0;
          k--;
          moved = true;
        }
        if (k > 0 && board[k - 1][j] == board[k][j]) {
          board[k - 1][j] += board[k][j];
          board[k][j] = 0;
          score += board[k - 1][j]; // sum score
          moved = true;
        }
      }
    }
  }
  return moved; // return if any moves has been performed
}

bool MoveDown(std::vector<std::vector<int>> &board) {
  bool moved = false;
  for (int j = 0; j < boardSize; j++) {
    for (int i = boardSize - 2; i >= 0; i--) {
      if (board[i][j] != 0) { // if cell is not empty
        int k = i;
        while (k < boardSize - 1 &&
               board[k + 1][j] == 0) { // moves each full
                                       // cell until none of them
                                       // can be moved further
          board[k + 1][j] = board[k][j];
          board[k][j] = 0;
          k++;
          moved = true;
        }
        if (k < boardSize - 1 &&
            board[k + 1][j] == board[k][j]) { // if next moving cell
                                              // is the same
                                              // as the current cell,
                                              // sum them
          board[k + 1][j] += board[k][j];
          board[k][j] = 0;
          score += board[k + 1][j]; // sum score
          moved = true;
        }
      }
    }
  }
  return moved; // return if any moves has been performed
}

bool MoveLeft(std::vector<std::vector<int>> &board) {
  bool moved = false;
  for (int i = 0; i < boardSize; i++) {
    for (int j = 1; j < boardSize; j++) {
      if (board[i][j] != 0) { // if cell is not empty
        int k = j;
        while (k > 0 && board[i][k - 1] == 0) { // moves each full
                                                // cell until none of them
                                                // can be moved further
          board[i][k - 1] = board[i][k];
          board[i][k] = 0;
          k--;
          moved = true;
        }

        if (k > 0 && board[i][k - 1] == board[i][k]) { // if next moving cell
                                                       // is the same
                                                       // as the current cell,
                                                       // sum them
          board[i][k - 1] += board[i][k];
          board[i][k] = 0;
          score += board[i][k - 1]; // sum score
          moved = true;
        }
      }
    }
  }
  return moved;
}

bool MoveRight(std::vector<std::vector<int>> &board) {
  bool moved = false;
  for (int i = 0; i < boardSize; i++) {
    for (int j = boardSize - 2; j >= 0; j--) {
      if (board[i][j] != 0) { // if cell is not empty
        int k = j;
        while (k < boardSize - 1 && board[i][k + 1] == 0) { // moves each full
          // cell until none of them
          // can be moved further
          board[i][k + 1] = board[i][k];
          board[i][k] = 0;
          k++;
          moved = true;
        }
        if (k < boardSize - 1 &&
            board[i][k + 1] == board[i][k]) { // if next moving cell
                                              // is the same
                                              // as the current cell,
                                              // sum them
          board[i][k + 1] += board[i][k];
          board[i][k] = 0;
          score += board[i][k + 1]; // sum score
          moved = true;
        }
      }
    }
  }
  return moved;
}

void DoInput(std::vector<std::vector<int>> &board) {

  std::this_thread::sleep_for(std::chrono::milliseconds(150)); // wait

  bool moved = false;

  char userMove;
  std::cout << "Enter move [W] -> UP [S] -> DOWN [A] -> LEFT [D] -> RIGHT : ";
  std::cin >> userMove;
  userMove = toupper(userMove); // to upper so it can be put both

  switch (userMove) {
  case 'W':
    moved = MoveUp(board);
    break;
  case 'S':
    moved = MoveDown(board);
    break;
  case 'A':
    moved = MoveLeft(board);
    break;
  case 'D':
    moved = MoveRight(board);
    break;
  default:
    std::cout << "\033[1;31mInvalid move (W,A,S,D)\033[0m\n";
    std::this_thread::sleep_for(
        std::chrono::milliseconds(1000)); // waits for user to read
    DrawGame(board);                      // redraws screen again
    return;
    break;
  }

  if (moved) {
    moves++;
    SpawnTile(board, piecesToSpawn);
    DrawGame(board);
  } else {
    std::cout << "\033[1;31mNo valid moves left in this direction!\033[0m\n"; //
    return;
  }
}

void InitialSetup() { // unused
  // Clear the console
  std::cout << "\033[2J\033[1;1H";
  // Draw Cover
  std::cout << art[0];

  char sel;
  std::cout << "[1] -> Quick start [2] -> Custom game : ";
  std::cin >> sel;
  switch (sel) {
  case '1':
    return;
    break;
  case '2':
    std::cout << "Board size, min 2 - max 20 (default 4): ";
    std::cin >> boardSize;
    if (boardSize > 20) {
      boardSize = 20;
    } else if (boardSize < 2) {
      boardSize = 2;
    }

    std::cout << "Starting pieces, min 1 - max " << (boardSize * boardSize) - 1
              << " (default 2): ";
    std::cin >> startingPieces;
    if (startingPieces > (boardSize * boardSize) - 5) {
      startingPieces = (boardSize * boardSize) - 5;
    } else if (startingPieces < 1) {
      startingPieces = 1;
    }

    std::cout << "Pieces to spawn, min 1 - max " << (boardSize * boardSize) - 1
              << " (default 1): ";
    std::cin >> piecesToSpawn;
    if (piecesToSpawn > (boardSize * boardSize) - 5) {
      piecesToSpawn = (boardSize * boardSize) - 5;
    } else if (piecesToSpawn < 1) {
      piecesToSpawn = 1;
    }

    std::cout
        << "Piece to get, min 16 - max 8192 (default 2048) multiple of 2!: ";
    std::cin >> numberToGet;
    if (numberToGet > 8192) {
      numberToGet = 8192;
    } else if (numberToGet < 16) {
      numberToGet = 16;
    }
    return;
    break;
  }
}

void CheckHighscore() { // simple thingi
  if (score > maxscore) {
    std::cout << "New highscore: " << score << '\n';
    maxscore = score;
  }
  score = 0;
  moves = 0;
}

void MainGame() {
  InitialSetup();

  std::vector<std::vector<int>> board;

  InitBoard(board);
  DrawGame(board);

  while (!IsGameOverState(board) && !IsWinState(board)) {
    DoInput(board);
  }

  if (IsGameOverState(board)) {
    std::cout << art[2];
    CheckHighscore();

    char retry;
    std::cout << "Try again? (y|n): "; // try again
    std::cin >> retry;
    if (retry == 'y') {
      state = 1;
      return;
    } else if (retry == 'n') {
      state = 0;
      return;
    } else {
      state = 1;
      return;
    }
  } else if (IsWinState(board)) {
    std::cout << art[1];
    CheckHighscore();

    char retry;
    std::cout << "Try again? (y|n): "; // try again
    std::cin >> retry;
    if (retry == 'y') {
      state = 1;
      return;
    } else if (retry == 'n') {
      state = 0;
      return;
    } else {
      state = 1;
      return;
    }
  }
  return;
}

int main() {
  while (true) { // retry loop fuck the compiler
    if (state != 0) {
      MainGame();
    } else {
      break;
    }
  }
  return 0;
}

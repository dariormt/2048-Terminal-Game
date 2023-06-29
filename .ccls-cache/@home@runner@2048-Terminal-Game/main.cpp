#include <iostream>
#include <thread>

// variables
const int boardSize = 4;
int score = 0;

const std::string art[] = {
    "\033[1;33m██████   ██████  ██   ██  █████  \n"
    "     ██ ██  ████ ██   ██ ██   ██ \n"
    " █████  ██ ██ ██ ███████  █████  \n"
    "██      ████  ██      ██ ██   ██ \n"
    "███████  ██████       ██  █████  \033[0m\n"
    "					By: Dariormt\n"};

std::string ColorParser(int numb) { // parses color depending on num
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
    return "!";
    break;
  }
}

void InitBoard(int board[boardSize][boardSize]) { // Board initialization

  srand(time(NULL)); // setup random

  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      board[i][j] = 0; // initialize all of the array
    }
  }
  int numSpawn1 =
      rand() %
      boardSize; // Choose a random spot on the 2D array to spawn first number
  int numSpawn2 = rand() % boardSize;
  board[numSpawn1][numSpawn2] = 2;
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

void DrawGame(int board[boardSize][boardSize]) { // Board Drawing

  // Clear the console
  std::cout << "\033[2J\033[1;1H";
  // Draw Cover
  std::cout << art[0];

  for (int i = 0; i < boardSize; i++) {

    if (i == 0) { // create box initial separation
      std::cout << "┌───┬───┬───┬───┐\n";
    } else { // create box separation between rows
      std::cout << "├───┼───┼───┼───┤\n";
    }

    for (int j = 0; j < boardSize; j++) {

      DrawTile(board[i][j], j);
    }
    std::cout << '\n'; // Do new line
  }

  std::cout << "└───┴───┴───┴───┘\n"; // close box enclosure

  std::cout << std::endl; // End and flush
}

bool IsFull(int board[boardSize][boardSize]) {
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

bool IsGameOverState(int board[boardSize][boardSize]) {
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

bool IsWinState(int board[boardSize][boardSize]) {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (board[i][j] == 2048) { // if contains numb
        return true;
      }
    }
  }
  // if not found
  return false;
}

void SpawnTile(int board[boardSize][boardSize]) {
  if (IsFull(board)) { // if it's full we can't spawn a numb, btw game over
                       // state will be triggered
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

bool MoveUp(int board[boardSize][boardSize]) {
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
          moved = true;
        }
      }
    }
  }
  return moved; // return if any moves has been performed
}

bool MoveDown(int board[boardSize][boardSize]) {
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
          moved = true;
        }
      }
    }
  }
  return moved; // return if any moves has been performed
}

void DoInput(int board[boardSize][boardSize]) {

  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  bool moved = false;
  char userMove;
  std::cout << "Enter move [W] -> UP [S] -> DOWN [A] -> LEFT [D] -> RIGHT : ";
  std::cin >> userMove;
  userMove = toupper(userMove);

  switch (userMove) {
  case 'W':
    moved = MoveUp(board);
    break;
  case 'S':
    moved = MoveDown(board);
    break;
  case 'A':

    break;
  case 'D':

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
    SpawnTile(board);
    DrawGame(board);
  } else {
    std::cout << "\033[1;31mNo valid moves left in this direction!\033[0m\n";
    return;
  }
}

int main() {
  int board[boardSize][boardSize];

  InitBoard(board);
  DrawGame(board);

  while (!IsGameOverState(board) && !IsWinState(board)) {
    DoInput(board);
  }
  // finish movement
  // win state
  // lose state
  // add scores
}

#include <iostream>

void display(char row_1[], char row_2[], char row_3[])
{
  std::cout << "\n TIC TAC TOE \n";
  std::cout << "1:" << row_1[0] << "   2:" << row_1[1] << "   3:" << row_1[2] << "\n";
  std::cout << "4:" << row_2[0] << "   5:" << row_2[1] << "   6:" << row_2[2] << "\n";
  std::cout << "7:" << row_3[0] << "   8:" << row_3[1] << "   9:" << row_3[2] << "\n";
}

void input(char current_player, char row_1[], char row_2[], char row_3[])
{
  int position;
  std::cout << "Player " << current_player << " Introduce a position.\n";
  std::cin >> position;
  if (position == 1) row_1[0] = current_player;
  if (position == 2) row_1[1] = current_player;
  if (position == 3) row_1[2] = current_player;
  if (position == 4) row_2[0] = current_player;
  if (position == 5) row_2[1] = current_player;
  if (position == 6) row_2[2] = current_player;
  if (position == 7) row_3[0] = current_player;
  if (position == 8) row_3[1] = current_player;
  if (position == 9) row_3[2] = current_player;  
}

bool check_winner(char current_player, char row_1[], char row_2[], char row_3[])
{
  //Check rows
  if (row_1[0] == current_player && row_1[1] == current_player && row_1[2] == current_player) return true;
  if (row_2[0] == current_player && row_2[1] == current_player && row_2[2] == current_player) return true;
  if (row_3[0] == current_player && row_3[1] == current_player && row_3[2] == current_player) return true;
  // Check Columns
  if (row_1[0] == current_player && row_2[0] == current_player && row_3[0] == current_player) return true;
  if (row_1[1] == current_player && row_2[1] == current_player && row_3[1] == current_player) return true;
  if (row_1[2] == current_player && row_2[2] == current_player && row_3[2] == current_player) return true;
  // Check diagonals
  if (row_1[0] == current_player && row_2[1] == current_player && row_3[2] == current_player) return true;
  if (row_1[2] == current_player && row_2[1] == current_player && row_3[0] == current_player) return true;  
  return false;
}

int main() {
  char player_1 = 'X';
  char player_2 = 'O';
  char row_1[3];
  char row_2[3];
  char row_3[3];
  for (int i = 0; i < 3; i++)
  {
    row_1[i] = ' ';    
    row_2[i] = ' ';    
    row_3[i] = ' ';    
  }

  int movements = 0;
  char current_player = player_1;
  display(row_1, row_2, row_3); 
  while (movements < 9) 
  { 
  input(current_player, row_1, row_2, row_3);
  if (check_winner(current_player, row_1, row_2, row_3)) 
  { 
   display(row_1, row_2, row_3); 
   std::cout << "\n CONGRATULATIONS PLAYER: " << current_player << " YOU WON!!"; 
   break; 
  } 
  else 
  { 
    if (current_player == player_1) 
    { 
      current_player = player_2; 
    } 
    else 
    { 
      current_player = player_1; 
    } 
  } 
  movements++; 
  display(row_1, row_2, row_3); 
  } 
  if (movements == 9) 
  { 
    std::cout << "\nTHERE IS A TIE!!!"; 
  }
}
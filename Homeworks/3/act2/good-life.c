/// @author Nihal Wadhwa
/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop
/// and have different Rule functions.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own. You should make the formatting consistent.
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///fix 1: changed the %s format specifiers in line 145 and 158 to %c

#include <stdio.h>
#include <stdlib.h>


//Prints title of game at beginning of the program
//return: none
void header(void){
      printf("\n\t..Welcome to the Game of life..\n");
}


//Prints the array representing organisms in an environment
//@param size: size of life array
//@param life: array representing organisms in environment
//@return none
void printLife(int size, char life[20][20]){
    for (int row = 0; row<size; row++){
       for(int col = 0; col<size; col++){
           printf("%c", life[row][col]);
        }
       puts(" ");
    }
}

//Returns number of neighboring organisms around an organism at location row, col of life
//array
//@param size: size of life array
//@param life: array representing organisms in environment
//@param row: row of organism being checked
//@param col: col of organism being checked
//@return number of neighbors surround char at life[row][col]
int checkNeighbor(int size, char life[size][size], int row, int col){
      int neighbors = 0;
      int r = row;
      int c = col;
      int lr = row;
      int lc = col;

      if( (row == 0) && (col == 0) )
      {
        r = size;
        c = size;
      }
      else if( (row == size-1) && (col == size-1) )
      {
        lr = -1;
        lc = -1;
      }
      else if(row == 0)
        r = size;
      else if(col == 0)
        c = size;
      else if(row == size - 1)
        lr = -1;
      else if(col == size - 1)
        lc = -1;
      if(life[r - 1][c - 1] == '*')
        ++neighbors;
      if(life[r - 1][col] == '*')
        ++neighbors;
      if(life[r - 1][lc + 1] == '*')
        ++neighbors;
      if(life[row][c - 1] == '*')
        ++neighbors;
      if(life[row][lc + 1] == '*')
        ++neighbors;
      if(life[lr + 1][c - 1] == '*')
        ++neighbors;
      if(life[lr + 1][col] == '*')
        ++neighbors;
      if(life[lr + 1][lc + 1] == '*')
        ++neighbors;
      return neighbors;
}


//Checks if all organisms in the life array live, die, or is born according to specified
//rules and changes life array for each generation
//@param size: size of life array
//@param life: life array representing the organisms in the environment
//@return: none
void rule(int size, char life[size][size]){

      int neighbors = 0;

      char lifeCopy[size][size];
      for (int i = 0; i < size; i++) {
         for (int j = 0; j < size; j++) {
            lifeCopy[i][j] = life[i][j];
         }
      }

      for(int row = 0; row < size; row++){
         for(int col = 0; col < size; col++){
            if(lifeCopy[row][col]== '*'){
               neighbors = checkNeighbor(size , lifeCopy, row, col);
               if(neighbors == 2 || neighbors == 3){
                  life[row][col] = '*';
               }
               else{
                  life[row][col] = ' ';
               }
            }
            else if(lifeCopy[row][col]== ' '){
               neighbors = checkNeighbor(size ,lifeCopy, row, col);
               if(neighbors == 3){
                  life[row][col] = '*';
               }
            }

         }
     }
      return;
}
//Runs the life simulation for 100 generations and takes user input for initial number of
//organisms
//return: none
int main(void){

      char life[20][20];
      int lifeSize = 20;
      int orgs;
      int i, row, col;
      int count = 0;

      header();

      printf("\nPlease enter the initial number of organisms: ");
      scanf("%i", &orgs);

      srand( 31 );

      for(i = 0; i < orgs; i++){
          row = rand();
          row %= 20;
          col = rand();
          col %= 20;

          if(life[row][col] == '*'){
            i--;
          }
          else{
            life[row][col] = '*';
          }
      }

      for(row = 0; row < lifeSize;  row++){
          for(col = 0; col < lifeSize; col++){
            if(life[row][col] != '*'){
              life[row][col] = ' ';
            }
          }
      }
//      printf("\n");
      while (count<100){
          printLife(lifeSize, life);
          rule(lifeSize, life);
          printf("\ngeneration: %d\n", count);
          count++;
      }
      return 0;
}



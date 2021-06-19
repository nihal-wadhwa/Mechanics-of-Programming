//file: Draw Squares Function
//description:used to draw squares of different characters
//@author Nihal Wadhwa (nw7554)

//Draws square with side lengths of param side, using characters denoted by param ch.
//@param side: the length of the square's side
//@param indent: the number of space from the left edge to indent the square
//@param ch: the character to use for the sqaure

#include <stdio.h> //printf


void draw_square(int side,int indent, char ch)
{

  int i;
  int x;
  for(i=0; i<side; ++i)
  {
    int y;
    for(x=0; x<indent; ++x)
    {
      printf(" ");
    }
   for(y=0; y<side; ++y)
   {
      printf("%c",ch);
   }
   printf("\n"); 
  }
  printf("\n");
} 


//Main program that uses draw_squares function
//@return 0 indicating successful execution

int main(void)
{
   draw_square(3, 2,'#');
   draw_square(5, 4, '*');
   draw_square(8, 3, '+');
   return 0;
}

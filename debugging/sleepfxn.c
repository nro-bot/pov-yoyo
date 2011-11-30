#include <stdio.h>
#include <time.h>

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds*1000000 + clock();
    while (goal > clock());
}

int main()
{
  int del;  // The delay period
  printf("Enter the delay time (in seconds): ");
  scanf("%i",&del); 
  //~ del *= 1000000;  // Multiply it by 1000 to convert to milliseconds
  sleep(del);   // Delay.
  printf("Done.");
  return 0;
}

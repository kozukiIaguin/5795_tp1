#include<stdio.h>
#include "tads/game.h"


int main(){
  Player *p1;
  p1->balance=10;
  int increase=20;
  printf("%d\n",p1->balance);
  updateBalance(p1,increase);
  printf("%d",p1->balance);
return 0;
}

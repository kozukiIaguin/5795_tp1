#include<stdio.h>
#include "game.h"


int main(){
  Player *p1;
  p1->balance =5;
  int x=12;
  printf("%d\n",p1->balance);
  updateBalance(p1,x);
  printf("%d\n",p1->balance);
return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char buf[128];


int main(void){
  char str[128];
  printf("文字列を入力してくだされ: ");
  scanf("%s",buf);
  strcpy(str, buf);
  printf("Hello World!\n");
  puts("poo poo");
  return 0;
}

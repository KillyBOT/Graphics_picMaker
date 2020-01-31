#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 3
#define HEIGHT 3

void writePixelRaw(int fd, int r, int g, int b);
int initPic(char* fileName, int w, int h);

int main(int argc, char* argv[]){

  printf("Test\n");

  int fd = initPic("pic.ppm",WIDTH,HEIGHT);

  for(int x = 0; x < WIDTH*HEIGHT; x++){
    writePixelRaw(fd, 100,0,0);
    if(x < WIDTH*HEIGHT - 1){
      write(fd, " ", 1);
    }
  }

  close(fd);

  return 0;
}

void writePixelRaw(int fd, int r, int g, int b){
  char toWriteString[32];

  sprintf(toWriteString, "%d %d %d",r,g,b);

  write(fd,toWriteString,strlen(toWriteString));
}

int initPic(char* fileName, int w, int h){
  int fd = open("pic.ppm",O_CREAT | O_WRONLY,0666);

  printf("Test\n");

  char wHString[32] = "";

  sprintf(wHString,"P3 %d %d ",WIDTH,HEIGHT);
  write(fd, wHString,strlen(wHString));

  return fd;
}

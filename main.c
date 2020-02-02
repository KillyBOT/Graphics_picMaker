#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 800
#define COLORDEPTH 255

#define RMIN -2
#define RMAX 1
#define IMAX 1
#define IMIN -1
#define MAXDEPTH 25

int main(int argc, char* argv[]){

  FILE* f = fopen("pic.ppm","w+");

  fprintf(f, "P3\n%d %d\n%d\n",WIDTH,HEIGHT,COLORDEPTH);

  double cR, cI;
  double zR, zI;
  double temp;
  double rScale, iScale;

  int currentDepth;
  int toDrawDepth;

  /*int gStartR, gStartG, gStartB;
  int gEndR, gEndG, gEndB;
  int gDiffR, gDiffG, gDiffB;

  gStartR = 0;
  gStartG = 0;
  gStartB = 200;

  gEndR = 0;
  gEndG = 200;
  gEndB = 200;

  gDiffR = gEndR - gStartR;
  gDiffG = gEndG - gStartG;
  gDiffB = gEndB - gStartB;*/

  int finalR, finalG, finalB;

  rScale = ((double)RMAX - (double)RMIN) / (double)WIDTH;
  iScale = ((double)IMAX - (double)IMIN) / (double)HEIGHT;

  printf("%f %f\n", rScale, iScale);

  for(int i = 1; i <= HEIGHT; i++){
    for(int r = 1; r <= WIDTH; r++){
      cR = (r * rScale) + RMIN;
      cI = (i * iScale) + IMIN;

      zR = 0;
      zI = 0;

      currentDepth = 0;
      toDrawDepth = 0;

      while(((zR * zR + zI * zI) < 4) && currentDepth < MAXDEPTH){
        temp = (zR * zR) - (zI * zI) + cR;
        zI = (2 * zR * zI) + cI;
        zR = temp;
        currentDepth++;
      }

      //toDrawDepth = (int)((COLORDEPTH / MAXDEPTH)) * currentDepth;
      finalR = currentDepth * 8;
      finalG = currentDepth << 10;
      finalB = currentDepth << 21;

      fprintf(f, "%d %d %d ",finalR,finalG,finalB);
    }
  }
  fclose(f);

  return 0;
}

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
#define ZOOM 1

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

  int finalR, finalG, finalB;

  rScale = ( ( (double)RMAX / (double)ZOOM)  - ( (double)RMIN / (double)ZOOM ) ) / (double)WIDTH;
  iScale = ( ( (double)IMAX / (double)ZOOM)  - ( (double)IMIN / (double)ZOOM ) ) / (double)HEIGHT;

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

      toDrawDepth = (int)((COLORDEPTH / MAXDEPTH)) * currentDepth;
      finalR = ((toDrawDepth * 3)) % COLORDEPTH;
      finalG = toDrawDepth % COLORDEPTH;
      finalB = (toDrawDepth * 5) % COLORDEPTH;

      fprintf(f, "%d %d %d ",finalR,finalG,finalB);
    }
  }
  fclose(f);

  return 0;
}

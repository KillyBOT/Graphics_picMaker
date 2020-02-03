#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500
#define COLORDEPTH 255

#define RMIN -2
#define RMAX 1
#define IMAX 1
#define IMIN -1
#define ZOOM 300

#define RZOOM -.7453
#define IZOOM .1127

#define MAXDEPTH 255

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

  double rMin, rMax, iMin, iMax;

  rMin = (double)RZOOM - ( ( (double)RZOOM - (double)RMIN) / (double)ZOOM);
  rMax = (double)RZOOM + ( ( (double)RMAX - (double)RZOOM) / (double)ZOOM);
  iMin = (double)IZOOM - ( ( (double)IZOOM - (double)IMIN) / (double)ZOOM);
  iMax = (double)IZOOM + ( ( (double)IMAX - (double)IZOOM) / (double)ZOOM);

  rScale = ( rMax - rMin ) / (double)WIDTH;
  iScale = ( iMax - iMin ) / (double)HEIGHT;

  for(int i = 1; i <= HEIGHT; i++){
    for(int r = 1; r <= WIDTH; r++){
      cR = (r * rScale) + rMin;
      cI = (i * iScale) + iMin;

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

      finalR = (toDrawDepth * 1) % COLORDEPTH;
      finalG = (toDrawDepth * 2) % COLORDEPTH;
      finalB = (toDrawDepth * 3) % COLORDEPTH;

      fprintf(f, "%d %d %d ",finalR,finalG,finalB);
    }
  }
  fclose(f);

  return 0;
}

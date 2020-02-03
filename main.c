#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLORDEPTH 255

#define RMIN -2
#define RMAX 1
#define IMAX 1
#define IMIN -1
#define ZOOM 3000000000

#define RZOOM -1.74999841099374081749002483162428393452822172335808534616943930976364725846655540417646727085571962736578151132907961927190726789896685696750162524460775546580822744596887978637416593715319388030232414667046419863755743802804780843375
#define IZOOM -0.00000000000000165712469295418692325810961981279189026504290127375760405334498110850956047368308707050735960323397389547038231194872482690340369921750514146922400928554011996123112902000856666847088788158433995358406779259404221904755

#define MAXDEPTH 300

int main(int argc, char* argv[]){

  FILE* f = fopen("pic.ppm","w+");

  fprintf(f, "P3\n%d %d\n%d\n",WIDTH,HEIGHT,COLORDEPTH);

  double cR, cI;
  double zR, zI;
  double temp;
  double rScale, iScale;
  double zoom;

  int currentDepth;
  double maxDepth;
  int toDrawDepth;

  int finalR, finalG, finalB;

  double rMin, rMax, iMin, iMax;

  zoom = atoi(argv[1]);

  rMin = (double)RZOOM - ( ( (double)RZOOM - (double)RMIN) / zoom);
  rMax = (double)RZOOM + ( ( (double)RMAX - (double)RZOOM) / zoom);
  iMin = (double)IZOOM - ( ( (double)IZOOM - (double)IMIN) / zoom);
  iMax = (double)IZOOM + ( ( (double)IMAX - (double)IZOOM) / zoom);

  rScale = ( rMax - rMin ) / (double)WIDTH;
  iScale = ( iMax - iMin ) / (double)HEIGHT;

  if(zoom > MAXDEPTH * MAXDEPTH) maxDepth = zoom;
  else maxDepth = MAXDEPTH;

  for(int i = 1; i <= HEIGHT; i++){
    for(int r = 1; r <= WIDTH; r++){
      cR = (r * rScale) + rMin;
      cI = (i * iScale) + iMin;

      zR = 0;
      zI = 0;

      currentDepth = 0;
      toDrawDepth = 0;

      while(((zR * zR + zI * zI) < 4) && currentDepth < maxDepth){
        temp = (zR * zR) - (zI * zI) + cR;
        zI = (2 * zR * zI) + cI;
        zR = temp;
        currentDepth++;
      }

      toDrawDepth = (int)(((double)(currentDepth + 1)/maxDepth) * COLORDEPTH);

      finalR = (toDrawDepth * 2) % COLORDEPTH;
      finalG = (toDrawDepth * 3) % COLORDEPTH;
      finalB = (toDrawDepth * 5) % COLORDEPTH;

      fprintf(f, "%d %d %d ",finalR,finalG,finalB);
    }
  }
  fclose(f);

  return 0;
}

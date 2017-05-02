AVC intial taking photos:

# include <studio.h>
# include <time.h>
# include "E101.h"

int main(){
  init();
  
  take_picture();
  
  for(int y = 0; y < 240; y + 10){
  for(int x = 0; x < 320; x + 10){
    char pix = get_pixel(y,x,3);
    printf("x=%d y=%d pix=%d\n", x, y, pix);
  }
  }
 display_picture(3,0); 
  return 0;
}

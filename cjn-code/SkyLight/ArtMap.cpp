// 
// 
// 

#include "ArtMap.h"


void mapInit() {
	 for (int i = 1; i < 6; i++) {
		 for (int j = 0; j < 18; j++)
		 {
			 shape_start_addr[i][j] = shape_start_addr[i - 1][j] + SEXTANT_LED_COUNT;
		 }
	 }
}

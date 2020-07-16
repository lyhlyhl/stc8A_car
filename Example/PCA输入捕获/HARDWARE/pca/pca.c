
#include "stc8.h"

#include "pca.h"


void pca(void)
{				 	  	
   CCON = 0x00;
   CMOD = 0x09;
   CL = 0x00;
   CH = 0x00;
   CCAPM0 = 0x10;
   CCAP0L = 0x00;
   CCAP0H = 0x00;
   CR = 1;
   EA = 1;

   
}
			 

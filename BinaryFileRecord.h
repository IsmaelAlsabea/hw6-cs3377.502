/*                                                                                                                                                            
 * Author: Ismael Alsabea                                                                                                                                     
 * Email:  isa170030@utdallas.edu                                                                                                                             
 */     



#include <stdint.h>

const int mRSL =25;

class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[mRSL]; //max record string length
};

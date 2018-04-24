/*                                                                                                                                                            
 * Author: Ismael Alsabea                                                                                                                                     
 * Email:  isa170030@utdallas.edu                                                                                                                             
 */     

class BinaryFileHeader
{
 public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;

};

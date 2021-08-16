#include "SizeStruct.h"
#include "Declarations.h"

 //Resize structure members after definition of Total Postlube length (runtime)
void sizeStruct (struct ResultsData &Structure, int StructSize)
{
Structure.enable.resize(StructSize);
Structure.elapsed.resize(StructSize);
Structure.NC.resize(StructSize);
Structure.NO.resize(StructSize);
Structure.switchStatus.resize(StructSize);
Structure.dblEnable.resize(StructSize);
Structure.dblNC.resize(StructSize);
Structure.dblNO.resize(StructSize);
Structure.dblelapsed.resize(StructSize);
}

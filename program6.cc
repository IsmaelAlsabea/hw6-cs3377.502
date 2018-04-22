/*
 * Usage of CDK Matrix
 *
 * File:   program6.cc 
 * Author: Ismael Alsabea
 * Email:  isa170030@utdallas.edu
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "cdk.h"
#include "BinaryFileHeader.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"
#define bs 1024 //buffer size
using namespace std;


int main()
{
  FILE          *ofc; //output from stream
  char          tmpBuffer[bs];
  char          *line;
  
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "R1", "R2", "R3", "R4","R5"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "C1", "C2", "C3"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};


  BinaryFileHeader *headerInput = new BinaryFileHeader ();
  ifstream readStream ("cs3377.bin", ios::in | ios::binary);
  readStream.read ((char *)headerInput, sizeof (BinaryFileHeader));
  readStream.close();
  
  string shellCmd= "strings cs3377.bin";
  ofc= popen(shellCmd.c_str(),"r");
  if (!ofc)
    exit(EXIT_FAILURE);
  
  vector <string> stringsArray;
  
  line =fgets (tmpBuffer,bs,ofc);
  while(line!=NULL)
    {
      stringsArray.push_back(line);
      line =fgets (tmpBuffer,bs,ofc);
    }
  pclose(ofc);
  
  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();
  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT,MATRIX_WIDTH,MATRIX_HEIGHT,MATRIX_WIDTH, 
			  MATRIX_NAME_STRING, (char **)rowTitles , (char **) columnTitles , boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  stringstream mn ; //magic number
  
  mn << hex << headerInput->magicNumber;
  string j= mn.str();
  
  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, j.c_str());
  j= "version: ";
  stringstream jj;
  jj << j << headerInput->versionNumber;
  setCDKMatrixCell(myMatrix, 1, 2, jj.str().c_str());
  jj.str("");
  j= "NumRecords: ";
  jj << j <<headerInput->numRecords;
  setCDKMatrixCell(myMatrix, 1, 3, jj.str().c_str());
  int e=2;

  for (unsigned int i=0;i< stringsArray.size();i++)
	    {
	     jj.str("");
	     jj << stringsArray.at(i).length();
	     setCDKMatrixCell(myMatrix, e, 1, jj.str().c_str());
	      setCDKMatrixCell(myMatrix, e, 2, stringsArray.at(i).c_str());
	      e++;
	    }
  
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (5);


  // Cleanup screen
  endCDK();
}

/*
 * Author: Ismael Alsabea
 * Email:  isa170030@utdallas.edu
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdint.h>

#include "cdk.h"
#include "BinaryFileHeader.h"
#include "BinaryFileRecord.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Binary File Contents"
using namespace std;

string transformToUpperCase (string str);
int main()
{ 
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
  
  // here the work with the header class have ended no more thinking about it.
  stringstream ss ; int k=0;
  ss << "  ";
  vector <BinaryFileRecord*> stringsVect;
  while (true)
    {
      //flushing the string stream
      ss.str("");
      // putting a new instance in the vector
      stringsVect.push_back(new BinaryFileRecord());
      // reading 1 string and putting the sequence at instace k
      readStream.read ((char *)stringsVect.at(k), sizeof (BinaryFileRecord));

       //ptting the string buffer in the string stream
      ss << stringsVect.at(k)->stringBuffer;
      // turning the string stream into string to calculate its length 
      stringsVect.at(k)->strLength= ss.str().length();
      //flag to exit the llop
      if (stringsVect.at(k)->strLength==0)
	{
	 ss.str("");
	 //remove the last element in the vector becuase it has no value.
	 stringsVect.pop_back();
	break;
	}
      // incrementing the counter
      k++;
    }
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

 
  
  ss << hex << headerInput->magicNumber;
  string j= "0X";
    j.append(ss.str());
  j= transformToUpperCase(j);
  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, j.c_str());
  j= "version: ";
  ss.str("");
  ss << j << headerInput->versionNumber;
  setCDKMatrixCell(myMatrix, 1, 2, ss.str().c_str());
  ss.str("");
  j= "NumRecords: ";
  ss << j <<headerInput->numRecords;
  setCDKMatrixCell(myMatrix, 1, 3, ss.str().c_str());
  int e=2;
  for (unsigned int i=0; i < stringsVect.size();i++)
	    {
	     ss.str("");
	     ss << stringsVect.at(i)->stringBuffer ;
	     setCDKMatrixCell(myMatrix, e, 1, ss.str().c_str());
	      ss.str("");
	      ss << dec <<(int)stringsVect.at(i)->strLength;
	     
	      setCDKMatrixCell(myMatrix, e, 2, ss.str().c_str());
	      e++;
	    }
  
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}

string transformToUpperCase (string str)
{
  char temp=' ';
  for( unsigned int i=0;i<str.length();i++)
    {
      temp= str.at(i);
      if ((int)temp> 96 && (int)temp < 123 && (int) temp!=32)
	{
	  temp-=32;
	  str.at(i)=temp;
	}
    }
  
  return str;
}

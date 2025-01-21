#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorter.h"

/* This simple main should work as follows:
   For each filename passed as a command line argument:
   
   1)  Open the file.  If the file fails to open, exit with code 42
   2)  Load the file into a loaded_file structure using load_file
   3)  When the file is loaded, sort the file with sort_file
   4)  When the file is sorted, print the file to standard output with
       print_file
   5)  Free the loaded_file structure with free_file, and close
       the FILE pointer itself

   If there are no files specified it should simply exit.
*/

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;

  //Loop through the command line arguments
  //Open the files, if the file does not open, then exit with code 42
  for (int i = 1; i < argc; i++)
  {
      const char *fileName = argv[i];
      FILE* f= fopen(fileName, "r"); 
      
      if (f == NULL)
      {
        exit(42);
      }

    loaded_file *file_data = load_file(f); //convert the file data into a loaded_file structure
    sort_file(file_data); //sort the file
    print_file(file_data); //print the files contents
    free_file(file_data); //free the memory of the file
    fclose(f); //close the file
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int main (int argc, char **argv) {
  FILE *fp;
  FILE *fvhs; //the .vhs file
  FILE *fkhs; //the .khs file
  if (argc != 3){
    fprintf(stderr, "Usage: %s filename.kv capacity\n", argv[0]);
    exit(-1);
  }

  long capacity = 0;
  capacity = atol(argv[2]); // Just like atoi there is a-to-long :)

  fp = fopen(argv[1], "r"); // Open filename.kv for reading
  if (fp == NULL){
    fprintf(stderr, "%s\n", "Failed to open the file: %s\n", argv[1]);
    exit(-1);
  }

  // Allocate memory for two filename with the ending
  char * filename_vhs = malloc(sizeof(argv[1]) + 5 * sizeof(char));
  char * filename_khs = malloc(sizeof(argv[1]) + 5 * sizeof(char));
  filename_vhs = argv[1];
  filename_khs = argv[1];

  fkhs = fopen(strcat(filename_vhs, ".khs"), "r+");
  fvhs = fopen(strcat(filename_khs, ".vhs"), "r+");
  if (fkhs == NULL || fvhs == NULL) {
    fprintf(stderr, "%s\n", "Failed to make the .khs or .vhs files\n");
    fclose(fp);
    exit(-1);
  }

  char key[STRLEN];
  char value[STRLEN];
  write_empty(fkhs, capacity);
  write_empty(fvhs, capacity);

  read_keyval(fp,key,value);


  free(filename_khs);
  free(filename_vhs);
  fclose(fp);
  return(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"
#include "assignment6.h"



int len_filename_no_ending(char * str) { // returns the index of the '.'
  return (strlen(str) - 3);
}

int getOpenLocation(FILE *fp, int hash_value, int capacity) {
  int idx = 0;
  while (idx != -1) {
    read_index(fp, hash_value, &idx);
    hash_value++; // move to the next location.
    if (hash_value == capacity) { // rollover case
      hash_value = 0;
    }
  }
  return hash_value;
}

int main (int argc, char **argv) {
  FILE *fp;
  FILE *fvhs = NULL; //the .vhs file
  FILE *fkhs = NULL; //the .khs file
  if (argc != 3) {
    fprintf(stderr, "Usage: %s filename.kv capacity\n", argv[0]);
    exit(-1);
  }

  long capacity = 0;
  capacity = atol(argv[2]); // Just like atoi there is a-to-long :)

  fp = fopen(argv[1], "rb"); // Open filename.kv for reading
  if (fp == NULL) {
    fprintf(stderr, "Failed to open the file: %s\n", argv[1]);
    exit(-1);
  }

  // Allocate memory for two filename with the ending
  int l = strlen(argv[1]) + 1;
  char * filename_khs = calloc(l+1,sizeof(char));
  char * filename_vhs = calloc(l+1,sizeof(char));

  // Copy the filename string this is the basis for the new name
  strcpy(filename_khs, argv[1]);
  strcpy(filename_vhs, argv[1]);

  filename_khs[len_filename_no_ending(argv[1])] = '\0'; // cut off the ".kv"
  filename_vhs[len_filename_no_ending(argv[1])] = '\0';

  strcat(filename_khs, ".khs");
  strcat(filename_vhs, ".vhs");

  fkhs = fopen(filename_khs, "wb+");
  fvhs = fopen(filename_vhs, "wb+");
  if (fkhs == NULL || fvhs == NULL) {
    fprintf(stderr, "%s\n", "Failed to make the .khs or .vhs files");
    free(filename_khs);
    free(filename_vhs);
    fclose(fp);
    exit(-1);
  }

  char key[STRLEN];
  char value[STRLEN];
  int key_hash, value_hash;
  int i = 0;
  // write nulls to the new files capacity times
  write_empty(fkhs, capacity);
  write_empty(fvhs, capacity);

  // reads the keyval pair until it reaches EOF, at which point read_keyval returns non-2
  while (read_keyval(fp, key, value) == 2) {

    // find the hash values
    key_hash = hashfn(key, capacity);
    value_hash = hashfn(value, capacity);

    // get the hash locations to write the indices to

    key_hash = getOpenLocation(fkhs, key_hash, capacity);
    value_hash = getOpenLocation(fvhs, value_hash, capacity);

    // write the indices at the open hash location, found using linear probing
    write_index(fkhs, i, key_hash);
    write_index(fvhs, i, value_hash);
    i++;
  }

  free(filename_khs);
  free(filename_vhs);
  fclose(fp);
  fclose(fkhs);
  fclose(fvhs);
  return(0);
}

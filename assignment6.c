#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "hashfn.h"

int len_filename_no_ending(char * str);
int getOpenLocation(FILE *fp, int hash_value, int capacity);
char * replace_file_ending(char * fn, char * ending);

int len_filename_no_ending(char * str) { // returns the index of the '.'
  return (strlen(str) - 3);
}

int getOpenLocation(FILE *fp, int hash_value, int capacity) {
  int idx = 0;
  read_index(fp, hash_value, &idx);
  while (idx != -1) {
    hash_value++; // move to the next location.
    if (hash_value == capacity) { // rollover case
      hash_value = 0;
    }
    read_index(fp, hash_value, &idx);
  }
  return hash_value;
}

char * replace_file_ending(char * fn, char * ending) {
  int l = strlen(fn) + 1;
  char * fn_new = calloc(l+1, sizeof(char));
  strcpy(fn_new,fn);
  fn_new[len_filename_no_ending(fn)] = '\0';
  strcat(fn_new, ending);
  return fn_new;
}

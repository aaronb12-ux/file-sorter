#include "sorter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

loaded_file *load_file(FILE *f)
{
  // the current line being loaded
  line current_line;
  current_line.length = 0;
  current_line.data = (unsigned char *)malloc(sizeof(unsigned char)); // allocating initial space for the current line. As of now it can hold one character

  // allocating memory for a 'loaded_file' object in 'file_data'
  loaded_file *file_data = (loaded_file *)malloc(sizeof(loaded_file));
  file_data->num_lines = 0;
  file_data->lines = NULL;

  // initial character
  char current_char = fgetc(f);

  // while not at the end of the file
  while (current_char != EOF)
  {
    if (current_char == '\n')
    {
      // once we reach a newline character, then we can create a newline and put the data from 'current_line.data' and length into it
      line *new_line = (line *)malloc(sizeof(line));
      new_line->data = (unsigned char *)malloc(current_line.length * sizeof(unsigned char));
      memcpy(new_line->data, current_line.data, current_line.length);
      new_line->length = current_line.length;

      // reallocing the file_data->lines to hold an extra line
      file_data->lines = (line **)realloc(file_data->lines, (file_data->num_lines + 1) * sizeof(line *));

      // add the current line into the filedata
      file_data->lines[file_data->num_lines] = new_line;
      file_data->num_lines += 1;

      // reset the current line
      current_line.length = 0;
    }
    else
    {
      // add the current character to the current line, incrament the current line length, and reallocate for space for the next character
      current_line.data = (unsigned char *)realloc(current_line.data, (current_line.length + 1) * sizeof(unsigned char));
      current_line.data[current_line.length] = current_char;
      current_line.length += 1;
    }
    current_char = fgetc(f);
  }

  // if we still have data, this is the case for the last line as it may not have a new line character
  if (current_line.length > 0)
  {
    line *new_line = (line *)malloc(sizeof(line));
    new_line->data = (unsigned char *)malloc(current_line.length * sizeof(unsigned char));
    memcpy(new_line->data, current_line.data, current_line.length);
    new_line->length = current_line.length;

    file_data->lines = (line **)realloc(file_data->lines, (file_data->num_lines + 1) * sizeof(line *));
    file_data->lines[file_data->num_lines] = new_line;
    file_data->num_lines += 1;
  }

  free(current_line.data);
  return file_data;
}

void free_file(loaded_file *f)
{
  for (size_t i = 0; i < f->num_lines; i++)
  {
    free(f->lines[i]->data); // freeing the characters stored at line i
    free(f->lines[i]);       // freeing the line structure itself at index i
  }
  free(f->lines);
  free(f);
}

int sorter_comp(const void *a, const void *b)
{
  // const void *a -> pointer to anything
  // Cast 'const void *a' and 'const void *b' to a pointer to the type of data in our array *line
  // You then dereference this pointer to get the value that pointer is pointing to
  line *line_1 = *(line **)a; // a is now a double pointer to a line, then dereference it (asterisks outside the parenthesis)
  line *line_2 = *(line **)b;

  // minimum length of the two lines
  size_t min = (line_1->length < line_2->length) ? line_1->length : line_2->length;

  for (size_t i = 0; i < min; i++)
  {
    if (line_1->data[i] < line_2->data[i])
    {
      return -1;
    }
    else if (line_1->data[i] > line_2->data[i])
    {
      return 1;
    }
  }

  // only time we make it out of the for loop is when all characters are equal up to 'min'
  if (line_1->length < line_2->length)
  {
    return -1; // first string (a) is shorter
  }

  else if (line_1->length > line_2->length)
  {
    return 1; // second string (b) is shorter
  }

  return 0; // all characters are equal
}

/* You probably want to use qsort */
void sort_file(loaded_file *f)
{
  qsort(f->lines, f->num_lines, sizeof(line *), sorter_comp);
}

void print_file(loaded_file *f)
{
  for (size_t i = 0; i < f->num_lines; i++)
  // iterating through the lines stored in the file_data struct
  {
    for (size_t j = 0; j < f->lines[i]->length; j++)
    // iterating through the characters of each line
    {
      putchar(f->lines[i]->data[j]);
      // printing the contents of the line characer by character
    }
    printf("\n");
  }
}

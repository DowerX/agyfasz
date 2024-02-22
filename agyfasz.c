#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MEM_MAX 32768
#define MEM_MIN 0

#define ERR_SYN 1
#define ERR_MEM 2

int main(int argc, char **argv) {
  int8_t memory[MEM_MAX] = {0};
  uint32_t memory_index = 0;
  uint32_t program_index = 0;
  char *program;

  char programkod[] =
      "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>++"
      "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
      "+++++++++++++++++++++++.>+++++++++++++++++++++++++++++++++++++++++++++++"
      "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>+++++++"
      "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
      "++++++++++++++++++++++++++.";

  if (argc == 1)
    program = programkod;
  else
    program = argv[1];

  int32_t depth = 0;
  while (program[program_index] != '\0') {
    if (program[program_index] == '[')
      depth++;
    else if (program[program_index] == ']') {
      depth--;
      if (depth < 0) {
        printf("Syntax error at %u.\n", program_index);
        exit(ERR_SYN);
      }
    }

    program_index++;
  }

  if (depth != 0) {
    printf("Syntax error.\n");
    exit(ERR_SYN);
  }

  program_index = 0;

  while (true) {
    switch (program[program_index]) {
    case '>':
      memory_index++;
      program_index++;
      if (MEM_MAX <= memory_index) {
        printf("\nInvalid memory access at %u.", program_index);
        exit(ERR_MEM);
      }
      break;
    case '<':
      if (memory_index < MEM_MIN) {
        printf("\nInvalid memory access at %u.", program_index);
        exit(ERR_MEM);
      }
      memory_index--;
      program_index++;
      break;
    case '+':
      memory[memory_index]++;
      program_index++;
      break;
    case '-':
      memory[memory_index]--;
      program_index++;
      break;
    case '.':
      putchar(memory[memory_index]);
      fflush(stdout);
      program_index++;
      break;
    case ',':
      if (scanf("%c", &memory[memory_index]) == EOF)
        memory[memory_index] = -1;
      program_index++;
      break;
    case '[':
      if (memory[memory_index] == 0) {
        uint32_t count = 1;
        while (count != 0) {
          program_index++;
          if (program[program_index] == '[')
            count++;
          else if (program[program_index] == ']')
            count--;
        }
      }
      program_index++;
      break;
    case ']': {
      uint32_t count = 1;
      while (count != 0) {
        program_index--;
        if (program[program_index] == ']')
          count++;
        else if (program[program_index] == '[')
          count--;
      }
      break;
    }
    case '\0':
      exit(0);
    default:
      program_index++;
      break;
    }
  }

  return 0;
}

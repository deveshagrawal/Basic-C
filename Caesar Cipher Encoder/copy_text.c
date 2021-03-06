#include<stdio.h>

int main(int argc, char *argv[]){
  // Set default Values
  FILE *source = stdin, *dest = stdout;

  // Set Values Depending on Number of Arguments
  switch(argc){
    case 3:
      dest = fopen(argv[2], "w");
    case 2:
      source = fopen(argv[1], "r");
  }

  char c;
  // Read one character at a time and put it in destination stream
  while((c = getc(source)) != EOF)
    putc(c,dest);

  return 0;
}
}
 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
  FILE *source = stdin, *dest = stdout; // Set Default Values
  int i, shift = 13;  //Default Shift is 13

  for(i = 1; i < argc; i++){
    if(strncmp("-F", argv[i], 2) == 0){
      if(strlen(argv[i]) == 2){
        source = fopen(argv[i+1], "r");
        // Space between -F and filename , therefore skip next value
        i++;
      }
      else{
        // No space between -F and filename , start reading after -F
        source = fopen(argv[i]+2, "r");
      }
    }

    else if(strncmp("-O", argv[i], 2) == 0){
      if(strlen(argv[i]) == 2){
        dest = fopen(argv[i+1], "w");
        // Space between -O and filename , therefore skip next value
        i++;
      }
      else{
        // No space between -O and filename , start reading after -O
        dest = fopen(argv[i]+2, "w");
      }
    }

    //If First character is a number or first 2 characters represent a negative number , then parse it as the shift value
    else if(((argv[i][0] >= '0') && (argv[i][0] <= '9')) || ((argv[i][0] == '-') && (argv[i][1] >= '0') && (argv[i][1] <= '9'))){
      sscanf(argv[i], "%d", &shift);
    }

    // Since Nothing else matched,Print Error message and abort
    else{
      fprintf(stderr, "%s\\n", "Shift has to be a Numberic Value");
      abort();
    }
  }

  if((shift > 25) || (shift < -25)){
    fprintf(stderr, "%s\\n", "Magnitude of Shift Cannot be Grater than 25");
    abort();
  }

  int c;
  while((c = getc(source)) != EOF){
    if(c >= 'A' && c <= 'Z'){
      c += shift;
      if(c > 'Z')
        c = 'A' + (c-'Z') - 1;
      else if(c < 'A')
        c = 'Z' - ('A'-c) + 1;
    }
    else if(c >= 'a' && c <= 'z'){
      c += shift;
      if(c > 'z')
        c = 'a' + (c-'z') - 1;
      else if(c < 'a')
        c = 'z' - ('a'-c) + 1;
    }
    putc(c,dest);
  }

  return 0;
}\cf0\f1\fs20
}
 
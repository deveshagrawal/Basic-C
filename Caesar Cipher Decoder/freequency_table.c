
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
  /* Initialize all counters to Zero */
  int letters = 0, wspace = 0, others = 0, chars[26] = {0}, i;
  FILE *source = stdin, *dest = stdout; // Set Default Values

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

      /* If file doens't exist, abort */
      if(source == NULL){
        printf("Source File Does Not Exist!!\\n");
        abort();
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
  }
  
  char c;
  /* Read one character at a time and update counters */
  while((c = getc(source)) != EOF){
    if(c >= 'A' && c <= 'Z'){
      chars[c - 'A']++;
      letters++;
    }
    
    else if(c >= 'a' && c <= 'z'){
      chars[c - 'a']++;
      letters++;
    }
    
    else if((c == ' ')||(c == '\\n')||(c == '\\r')||(c == '\\t')){
      wspace++;
    }
    
    else{
      others++;
    }
  }
  
  /* Print out the Summary */
  fprintf(dest, "\\nTotal Characters = %d\\n", letters + wspace + others);
  fprintf(dest, "Letters = %d\\n", letters);
  fprintf(dest, "Whitespace = %d\\n", wspace);
  fprintf(dest, "Others = %d\\n\\n", others);

  /* print out the frequency table */
  fprintf(dest, "Letters\\tCount\\tFrequency\\n");
  for(i=0; i<26; i++)
    fprintf(dest, "%4c\\t%4d\\t%.3lf\\n", 'a' + i, chars[i], (double)chars[i]/letters*100);

  return 0;
}
}
 
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>

/*
 * Calculate the Shift used to encode
 * by using the chi-squared hypothesis test
 */
int find_chi_sq(int chars[26], int letters){
  /* 
   * implement the 'ef' function (frequency for each alphabet in english language) as a lookup table
   * Set to specified values
   */
  double ef[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.707, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};
  /* implement 'mf' as a lookup table too */
  double mf[26] = {0.0}, chi_sq = INT_MAX, chi_curr = 0;
  int pos = 0, i, j;

  for(i=0; i<26; i++)
    mf[i] = (double)chars[i] / letters * 100;

  for(i=0; i<26; i++){
    chi_curr = 0;

    for(j=0; j<26; j++){
      chi_curr += ((ef[j]-mf[(j+i)%26])*(ef[j]-mf[(j+i)%26]))/ef[j];
    }

    /* 
     * if current chi_sq is less than the rest,
     * make it the lowest
     */
    if(chi_curr < chi_sq){
      chi_sq = chi_curr;
      pos = i;
    }
  }
  
  return pos;
}

/*
 * Decode the message in the source stream using the shift provided
 * and put it into the destination stream
 */
void decode(FILE *source, FILE *dest, int shift){
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
}

int main(int argc, char *argv[]){
  /* initialize counters to Zero */
  int letters = 0, wspace = 0, others = 0, chars[26] = {0}, i, j;
  /* Set Default Values */
  FILE *source = stdin, *dest = stdout, *temp = fopen("temp", "w+");

  /* Create a structure to hold program options */
  struct{
    int f, o, n, s, i, t, h, x;
  } opts = {0, 0, 0, 0, 0, 0, 0 ,0}; // initialize every option with value zero

  for(i = 1; i < argc; i++){
    if(strncmp("-F", argv[i], 2) == 0){
      opts.f = 1;

      if(strlen(argv[i]) == 2){
        source = fopen(argv[i+1], "r");
        // Space between -F and filename , therefore skip next value
        i++;
      }
      else{
        // No space between -F and filename , start reading after -F
        source = fopen(argv[i]+2, "r");
      }

      /* If ile Doesn't Exist, Abort */
      if(source == NULL){
        fprintf(stderr, "Source File Does Not Exist!!\\n");
        abort();
      }
    }

    else if(strncmp("-O", argv[i], 2) == 0){
      opts.o = 1;

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

    /* Handle All other Options that do not have any input associated */
    else if(argv[i][0] == '-'){
      for(j=1; j<strlen(argv[i]); j++){
        switch(argv[i][j]){
          case 'n':
            opts.n = 1;
            break;
          case 's':
            opts.s = 1;
            break;
          case 'i':
            opts.i = 1;
            break;
          case 't':
            opts.t = 1;
            break;
          case 'h':
            opts.h = 1;
            break;
          case 'x':
            opts.x = 1;
            break;
        }
      }
    }
  }

  if(opts.h == 1){
    printf("\\
Usage: decode [Arguments]\\n\\
Arguments:\\n\\
  -F <filename>\\tThe name of the input file. If missing use stdi\\n\\
  -O <filename>\\tThe name of the output file. If missing use stdout\\n\\
  -n\\t\\tSuppresses the printing of the decoded file to stdout.\\n\\
  -i\\t\\tPrints the Character summary\\n\\
  -t\\t\\tComputes the frequency table and prints it to stdout\\n\\
  -h\\t\\tPrint to stdout instructions on how to use the program\\n"
        );

    if(opts.x != 1)
      return 0;
  }

  if(opts.x == 1){
    if(opts.h == 1)
      printf("\\n");

    printf("\\
The Decoding works because we compare the frequencies of the alphabets in the encoded message with the frequencies of the alphabets in normal english. For example the letter 'e' has the highest frequency in the english language , if the letter 'f' has the highest frequency in the encoded message then it is fairly correct to say that the message has been encoded with a shift of 1\\n\\
\\n\\
Pearson's chi-square (\'cf\'872) test is the best-known of several chi-square tests \'e2\'80\ldblquote  statistical procedures whose results are evaluated by reference to the chi-square distribution. Its properties were first investigated by Karl Pearson. In contexts where it is important to make a distinction between the test statistic and its distribution, names similar to Pearson X-squared test or statistic are used.\\n\\
\\n\\
It tests a null hypothesis that the frequency distribution of certain events observed in a sample is consistent with a particular theoretical distribution. The events considered must be mutually exclusive and have total probability 1. A common case for this is where the events each cover an outcome of a categorical variable. A simple example is the hypothesis that an ordinary six-sided die is \\"fair\\", i.e., all six outcomes are equally likely to occur. Pearson's chi-square is the original and most widely-used chi-square test.\\n"
        );

    return 0;
  }
  
  int c;
  /* Loop through Every character and update counters */
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

    /* Dump each character into a temporary file to process afterwards */
    putc(c, temp);
  }
  
  /* Get the shift used to encode the message */
  int encShift = find_chi_sq(chars, letters);

  if(opts.s == 1){
    printf("\\nShift used to Encode = %d\\n\\n", encShift);
  }

  if(opts.i == 1){
    /* 
     * If previous option has already printed a blank line,
     *  then do not put another blank line
     */
    if(opts.s != 1)
      printf("\\n");

    printf("Total Characters = %d\\n", letters + wspace + others);
    printf("Letters = %d\\n", letters);
    printf("Whitespace = %d\\n", wspace);
    printf("Others = %d\\n\\n", others);
  }

  if(opts.t == 1){
    if((opts.s != 1)||(opts.i != 1))
      printf("\\n");

    printf("Letters\\tCount\\tFrequency\\n");
    for(i=0; i<26; i++)
      printf("%4c\\t%4d\\t%.3lf\\n", 'a' + i, chars[i], (double)chars[i]/letters*100);

    printf("\\n");
  }

  /* Do Not Print if '-n' is set and '-O' isn't */
  if((opts.o == 1)||(opts.n == 0)){
    /*
     *  Start reading from the start of temporary file 
     *  and decode the message with the shift calculate
     */
    rewind(temp);
    
    /*
     * If shift used to encode was 'x'
     * then the shift to decode will be '-x' or '26-x'
     */
    int shift = -encShift;
    
    /*
     * Decode the message using the shift value calculated
     */
    decode(temp, dest, shift);
  }
  fclose(temp); //Close the handle to the temporary file

  /* Clean-up all opened handles */

  if(opts.f == 1)
    fclose(source);

  if(opts.o == 1)
    fclose(dest);

  return 0;
}
}
 
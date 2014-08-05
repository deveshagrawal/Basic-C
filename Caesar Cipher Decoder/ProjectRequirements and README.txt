Here is assignment requirements for one of the programming course:

Automating the Decoding of a Caesar Cipher (20 marks)

Question 1 (10 marks)

To automate the determining of the shift used in the Caesar encoding, you need to determine the frequency in the message of each letter in the alphabet (again see the Web Site en.wikipedia.org/wiki/Caeser_cipher for details). For this program, take in a message (either encoded or not) from stdin or a filename provided with the -F command line argument (as used in assignment 2) and produce the corresponding frequency table. 

Before the table, on its own line, the letter count should be printed 3 numbers (appropriately labeled): the number of letters in the message, the number of white space characters (this includes blank spaces, the newline, carriage return and tab characters), and the number of non letter, non white-space characters. 

The table itself should be printed in three columns. The first column should print out the letters . The second column should hold the corresponding letter counts for each letter. The third column should hold the frequency of the letter counts (the letter counts divided by the total number of letters in the message). The columns should be separated by tab characters (look it up in an ASCII table). There should be a header row describing each column.

The command line arguments are the same as those used in assignment 2 question 2.
This program should be called frequency_table.c 
 

Question 2 (30 marks)

Use the frequencies from the given table for each alphabet.

Let ef(c) be the english language frequency drawn from the table above. For example ef('b') == 1.492% (uppercase and lowercase combined, so ef('B') == 1.492% also).

Now you should compute the frequencies in the input file (see question 1). Then let mf(c) be the message fequency for a character c (the frequency found in the file - 'message' is the technical term for any encrypted text).

Now use the following formula, called the Chi-Squared formula (used in the Chi-Squared test - see Pearson's chi-square test for details)  for a given shift "guess" s.
 chi_sq(s) =
S
for all c
(ef(c) - mf((c + s) mod 26))2 
ef(c)
If the guess for the shift was right, chi_sq(s) will be the smaller than for any other shift value. So examine all possible shifts, from 0 to 25 to determine which shift will decode the message.
Name this program decode.c

As in Assignmnt 2, your program will take command line arguments
-F
The name of the input file. If missing use stdin.
-O
The name of the output file after decoding. If missing use stdout.
-n
Suppresses the printing of the decoded file to stdout. If -O is included as a command line argument -n does nothing.
-s
Computes the original Caesar shift value used to encode the message, and prints it to stdout (e.g. shift = 4). The shift value is printed on its own line before anything else is printed. For example if -O and -n are not used and the decoded file is printed to stdout, print the shift first and include a blank line before printing the decoded message/file.

Note: the shift you found to decode the message is not the same shift that was used to encode the message (except for a shift 0 and a shift 13). You should be printing the shift that was used to encode the message, not the shift you used to decode the message.
-i
Computes and prints to stdout the total letter count, white space count and other characters count using the same format as question 1. If -s is also used, the shift value is printed first with a blank line insterted between the shift value and the character count summary. If any other option requires printing to the std out it must print after the -i summary after a blank line is inserted.
-t
Computes the frequency table and prints it to stdout using the same format at question 1. All other options that print to the stdout will print before the frequency table with the exception of the decoded message if -O is not used and the decoded file is printed to stdout, print the table first and include a blank line before printing the decoded message/file.
-h
Print to stdout instructions on how to use the program, including how to use the other command line arguments. If present, no decoding should be done. Also, -h should not be used with other arguments and should deactive them (they should not be performed), with the exception of -x.
-x
Print to stdout an explanation of why the program (usually) correctly decodes Caesar ciphers. Pay especial attention to the chi square formula. If present, no decoding should be done. Also, -x should not be used with other arguments and should deactive them (they should not be performed), with the exception of -h.
Allow for command line arguments other than -F and -O to be used together with the other arguments in one command in any order. 
For example

promt: decode -isn -F myfile.txt
will read from myfile.txt and print the shift value and character count summary to stdout
Any error messages or warnings should be printed to stderr.

NOTES (IMPORTANT INFO ... READ CAREFULLY)
Be sure to copy your source code files into a directory where they will be safe in the event that you accidentally remove everything from your working directory. It is a good idea to make a directory named backup in which you regularly place copies of your C files. Alternatively, you could learn to use subversion.
Your code must compile cleanly with no error or warning messages using the -Wall flags in gcc.
The man command (short for manual) is very useful for finding out how these and other commands work. You can find out information on almost any command by typing man name where name is what you wish to know about.
The assignment must be written in C and run on a machine running Linux in the Thornborough buildings.
Your source code should contain brief comments describing the functionality and the major components of each procedure. Any complex structures should also be commented. Your source code should be properly formated and meaningful variable names should be used.
If you hand in an assignment that does not compile you will get a mark of zero.
All work in this course is to be done independently. Submissions will be electronically examined for similarity.
You should hand in your source code file (.c and .h files) and a makefile.
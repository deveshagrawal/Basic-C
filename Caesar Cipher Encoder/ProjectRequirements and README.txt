Here are the requirements for the assignment.

Question 1: Copying a Text File (10 Marks)

Create a program called copy_text that takes two command line arguments: the first argument is the name of the file to be copied; the second argument is the name of the new file. If the second argument is missing, copy the file to stdout. If both arguments are missing, the program should read from stdin and print to stdout. 
Example:

copy_text original.txt theCopy.txt

Note1: Do not ask the user for the name of the files. These must be entered as command line arguments or not at all!
Note2: scanf() and printf() can be used to read from and write to a file if you use IO redirect. IO redirect is a command line operator that redirects scanf() from the keyboard to a file by using a < followed by the file name. Similarly, the > is used followed by the file name to redirect printf() from the terminal to a file.
Example:

copy_text < original.txt > theCopy.txt

scanf() will get characters from the file original.txt instead of from the keyboard, and printf() will print to the file theCopy.txt instead of to the screen.
Using scanf() and printf() with IO-redirect does not count as explicit file access, so you will not get many marks for this question if that is all your system can do in order to read and write a file.

Note3: scanf("...", ...) is the same as fscanf(stdin, "...", ...) and printf("...", ...) is the same as fscanf(stdout, "...", ...)
Note4: If not reading from a file, you can never get to the end of the file (the input stream goes on forever). To simulate an end of file when typing (as opposed to the end of line) enter the ^d (control-d) character. C will view this as an end of file character and will process it the same way (you do not have to check for ^d in your code. (Informational note - do not implement: when using MS-DOS or Windows, use ^z and the carriage return instead of ^d) 

Question 2: Creating a Caesar Cipher (30 marks)

Read about Caesar Ciphers from the wikipedia http://en.wikipedia.org/wiki/Caesar_cipher.

Question 2.1 (10 marks)

The most common of the Caesar Ciphers still in use is Rot13, which uses a shift of 13. Write a program that takes in input from a file and prints it into a new file encoded using Rot13. Only Rot13 letters, leave digits, white space and punctuation unchanged. The file names should be command line arguments as specified for the copy_text program from Question 1.
Name this program rot13.c

Question 2.2 (20 marks)

Encode a message from a file using the Caesar Cipher with a shift as entered as a command line argument. The results should be placed in a new file. If the shift is 0, the program should just produce a copy of the file (similar behavior as question 1). The program should accept positive and negative shift values (positive shifts add the absolute shift amount, negative shifts subtract the absolute shift amount). If a command line argument is entered that is not a number, or is a number  whose absolute value is greater than or equal to 26, print an appropriate error message to the screen; but do not create a new file (use fprintf(stderr, "%s\n", "your message")to accomplish this).

The program should take in a three command line arguments: 
the shift number
an integer between -25 and 25 inclusive
-F input_file_name
the name of the input file
there is usually a space between -F and the file name
but there doesn't have to be - you have to handle both cases
 -O output_file_name
the name of the output file
again, there is usually a space between -O and the file name
but there doesn't have to be - you have to handle both cases
The shift number does not have a option name; it is just a number
If the -O argument is missing, output the converted file using printf() instead of fprintf().
If the -F argument is missing, the program should read from scanf() instead of scanf().
If no shift number is present, the program should use a Rot13 encoding.
Name this program encode.c  If you have this program working, you do not need to hand in rot13.c, which will be marked by running encode.c with no shift number. 

 

NOTES (IMPORTANT INFO ... READ CAREFULLY)
Be sure to copy your source code files into a directory where they will be safe in the event that you accidentally remove everything from your working directory. It is a good idea to make a directory named backup in which you regularly place copies of your C files. Alternatively, you could learn to use subversion.
Your code must compile cleanly with no error or warning messages using the -Wall flags in gcc.
The man command (short for manual) is very useful for finding out how these and other commands work. You can find out information on almost any command by typing man name where name is what you wish to know about.
The assignment must be written in C and run on a machine running Linux in the Thornborough buildings.
Your source code should contain brief comments describing the functionality and the major components of each procedure. Any complex structures should also be commented. Your source code should be properly formated and meaningful variable names should be used.
If you hand in an assignment that does not compile you will get a mark of zero.
All work in this course is to be done independently. Submissions will be electronically examined for similarity.
You should hand in your source code file (.c and .h files) and a makefile.
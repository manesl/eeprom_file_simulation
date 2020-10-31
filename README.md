
Project: EEPROM read and write API's (EEPROM is simulated as a file original.txt)

Author: Shweta Mane

Date:30th October 2020

Machine: Linux Ubuntu

Command: gcc -o main main.c eeprom.c -l pthread

CMD line encoding: UTF-8 (en-US)

Files:

main.c : contains thread of three users
user 1 tries to perform erase operation and fills the EEPROM 0-8191 offset
(each offset is 8 bits) with A-Z aplhabets

user 2 tries to perform a overwrite operation and fills the EEPROM 0-8191 offset 
with a-z alphabets

user 3 writes a single page 12 and reads it and 
tries to give bad inputs and the error statements are printed on the console

In main.c the lines marked with /************ must be edited to see changes

eeprom.c : contains function definitions for the following
open file, close file, get mutex, release mutex, read page, write page, and 
our main functions "eeprom_read()", "eeprom_write()", and "erase()"

erase operation will blank out the file

eeprom.h : conatins function prototypes

original.txt: the main txt file which is read and written.

user1.txt, user2.txt: to save intermediate output of the users
since last user will overwrite the original.txt


Assumptions and Information:
1) If two threads will try to call the main function for pthread_join() at once the behavior will be undefined,
the code needs to be ran again.
 
2) Different encoding might affect the output data. So it must be set to UTF-8. 

3) At a time only one user can open, read/write, close file. 
Other users can keep write buffers ready or read their saved buffers, thus making
the program time efficient.

4) Erase state will blank out the file instead of storing 0xFF

5) Bad inputs considered are out of bound access for offset, page no.s, words on a page etc.
Care has been taken to inform the user about the range of values they can enter.

6) While writing a page, the data is only overwritten and it does not wipe out the whole file or corrupts other data.


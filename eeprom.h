/******************************************************************************
 * Copyright (C) Shweta Mane- University of Cincinnati
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file eeprom.h
 * @brief Abstraction of memory read and write operations
 *
 * This header file provides the eeprom read and write API's
 *
 * @author Shweta Mane
 * @date Oct 28 2020
 *
 */
#ifndef __EEPROM_H__
#define __EEPROM_H__

//#include <stdio.h>
//#include <stdint.h>
//global variable
FILE *fptr;
/**
 * @brief Reads the no of bytes/words starting from the offset 
 *
 * Given a offset, sets the file pointer to desired offset, 
 * and then copies the bytes in the buffer pointed by buf. 
 * Here no of bytes are mentioned by size parameter.
 *
 * @param offset location of the starting byte (in the file)
 * @param size No of bytes
 * @param buf pointer to the heap memory where the bytes accessed will be returned.
 *
 * @return void
 */
void eeprom_read(u_int16_t offset, u_int16_t size, char* buf);

/**
 * @brief Writes the no of bytes/words starting from the offset 
 *
 * Given a offset, sets the file pointer to desired offset, 
 * and then copies the bytes in the file pointed by buf. 
 * Here no of bytes are mentioned by size parameter.
 *
 * @param offset location of the starting byte (in the file) where new data should be written
 * @param size No of bytes
 * @param buf Pointer to the heap memory where the bytes will be accessed to store in the file
 *
 * @return void.
 */
void eeprom_write(u_int16_t offset, u_int16_t size, char* buf);

/**
 * @brief Reads a page from the file
 *
 * Given a page number, sets the file pointer to the page starting address, 
 * and then copies the bytes in the file to the location pointed by page. 
 * 
 *
 * @param page Pointer to the location where the 32 bytes/ single page will be copied
 * @param page_no Page number
 * 
 *
 * @return void.
 */
void read_page(char *page, u_int16_t page_no);

/**
 * @brief Writes a page in the file
 *
 * Given a page number, word number, and no of words on that page to be overwritten safely,
 * it will write to a particular page in the file
 * 
 *
 * @param page Pointer to the location where the 32bytes or less are pre written to store in the page of a particular file
 * @param page_no Page number
 * @param word_no The starting byte/word on a page
 * @param no_of_word The no of words to be overwritten on the page
 *
 * @return void.
 */
void write_page(char *page, u_int16_t page_no, u_int8_t word_no, u_int8_t no_of_word);

/**
 * @brief Opens the file 
 *
 * Opens a file, in order create a new text file change the path in this function definition
 * 
 *
 * @param path path of a file that needs to be opened
 * 
 *
 * @return void.
 */
void open_file(char path[]);

/**
 * @brief Closes the file 
 *
 * Closes a file
 * 
 *
 * @param void
 * 
 *
 * @return void.
 */
void close_file(void);

/**
 * @brief Erase the file
 *
 * Erases all the location of file
 * 
 *
 * @param void
 * 
 *
 * @return void.
 */
void erase(void);

/**
 * @brief Allows a user to get mutex 
 *
 * Enables a user to get mutex in order to perform read write operation or wait for a mutex until it becomes available
 * 
 *
 * @param void
 * 
 *
 * @return void.
 */
void get_mutex(void);

/**
 * @brief Allows a user to release mutex
 *
 * Enables a user to release mutex after use so that other user can get the mutex
 * 
 *
 * @param void
 * 
 *
 * @return void.
 */
void release_mutex(void);

#endif /* __MEMORY_H__ */

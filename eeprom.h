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
 * 
 * @brief This header file provides the eeprom read and 
 * write API's at page and byte level and other necessary functions
 * like erase, mutex, opening and closing file.
 *
 * @author Shweta Mane
 * @date Oct 28 2020
 *
 */
#ifndef __EEPROM_H__
#define __EEPROM_H__
#include <stdint.h>
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
 * @param buf pointer to the heap memory where the bytes accessed 
 * from the file will be returned.
 *
 * @return void
 * @notes data received from the file is loaded into heap
 */
void eeprom_read(uint16_t offset, uint16_t size, char* buf);

/**
 * @brief Writes the no of bytes/words starting from the offset 
 *
 * Given a offset, sets the file pointer to desired offset, 
 * and then copies the bytes into the file pointed by buf. 
 * Here no of bytes are mentioned by size parameter.
 *
 * @param offset location of the starting byte (in the file) 
 * where new data should be written
 * @param size No of bytes
 * @param buf Pointer to the heap memory where the bytes will be 
 * accessed to store in the file.
 *
 * @return void.
 * @notes data received from the heap is loaded into the file
 */
void eeprom_write(uint16_t offset, uint16_t size, char* buf);

/**
 * @brief Reads a page from the file
 *
 * Given a page number, sets the file pointer to the page starting address, 
 * and then copies the bytes in the file to the location pointed by page buffer. 
 * 
 *
 * @param page Pointer to the location where the 32 bytes/ 
 * single page will be copied
 * @param page_no Page number
 * 
 *
 * @return void.
 */
void read_page(char *page, uint16_t page_no);

/**
 * @brief Writes a page in the file
 *
 * Given a heap location with some data, page number, starting word number, 
 * and no of words on that page to be overwritten safely,
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
void write_page(char *page, uint16_t page_no, uint8_t word_no, uint8_t no_of_word);

/**
 * @brief Opens the file 
 *
 * Opens a file with the path passed in an array to this function
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
 * and put blanks
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
 * Enables a user to get mutex in order to perform read write operation along with operations like
 * opening and closing a file or wait for a mutex until it becomes available
 * 
 *
 * @param void
 * 
 *
 * @return void.
 */
//void get_mutex(void);

/**
 * @brief Allows a user to release mutex
 *
 * Enables a user to release mutex after use so 
 * that other user can get the mutex
 * 
 *
 * @param void
 * 
 *
 * @return void.
 */
//void release_mutex(void);

#endif /* __MEMORY_H__ */

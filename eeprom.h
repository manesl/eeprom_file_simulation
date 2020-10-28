/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file memory.h
 * @brief Abstraction of memory read and write operations
 *
 * This header file provides an abstraction of reading and
 * writing to memory via function calls. 
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Sets a value of a data array 
 *
 * Given a pointer to a char data set, this will set a provided
 * index into that data set to the value provided.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 * @param value value to write the the locaiton
 *
 * @return void.
 */
void set_value(char * ptr, unsigned int index, char value);

/**
 * @brief Clear a value of a data array 
 *
 * Given a pointer to a char data set, this will clear a provided
 * index into that data set to the value zero.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return void.
 */
void clear_value(char * ptr, unsigned int index);

/**
 * @brief Returns a value of a data array 
 *
 * Given a pointer to a char data set, this will read the provided
 * index into that data set and return the value.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return Value to be read.
 */
char get_value(char * ptr, unsigned int index);

/**
 * @brief Sets data array elements to a value
 *
 * Given a pointer to a char data set, this will set a number of elements
 * from a provided data array to the given value. The length is determined
 * by the provided size parameter.
 *
 * @param ptr Pointer to data array
 * @param value value to write the the locaiton
 * @param size Number of elements to set to value
 *
 * @return void.
 */
void set_all(char * ptr, char value, unsigned int size);

/**
 * @brief Clears elements in a data array
 *
 * Given a pointer to a char data set, this will set a clear a number
 * of elements given the size provided. Clear means to set to zero. 
 *
 * @param ptr Pointer to data array
 * @param size Number of elements to set to zero
 *
 * @return void.
 */
void clear_all(char * ptr, unsigned int size);


/**
 * @brief copies data from a given source location to destination location
 *
 * Given a pointer to a dataset at source location, a pointer for destination
 * location, and the length of bytes to be copied from source location 
 *
 * @param ptr Pointer to dataset at src location
 * @param ptr Pointer to dataset at dest location
 * @param size the length of bytes copied from src
 *
 * @return ptr Pointer to dataset at dest location
 *
 * @notes 1. It should handle overlap of data at src and dest with no data corruption?
 * 	2. use pointer arithmetic not array indexing
 */
uint8_t * my_memmove(uint8_t *src, uint8_t *dst, size_t length);


/**
 * @brief copies data from a given source location to destination location
 *
 * Given a pointer to a dataset at source location, a pointer for destination
 * location, and the length of bytes to be copied from source location 
 *
 * @param ptr Pointer to dataset at src location
 * @param ptr Pointer to dataset at new dest location
 * @param size the length of bytes copied from src
 *
 * @return ptr Pointer to dataset at new dest location
 *
 * @notes 1. The behaviour should be undefined if there is overlap in datasets
 * 	2. use pointer arithmetic not array indexing
 */
uint8_t * my_memcopy(uint8_t *src, uint8_t *dst, size_t length);


/**
 * @brief sets all the location to a given value
 *
 * Given a pointer to a dataset at source location, length of bytes, and a value, it sets all
 *  those location to that value.
 *
 * @param ptr Pointer to dataset at src location
 * @param size the length of bytes copied from src
 * @param value the value that you want all the location should set to
 * 
 * @return ptr Pointer to dataset at src location
 *
 * @notes 1. do not reuse set_all() func
 * 	2. use pointer arithmetic not array indexing
 */
uint8_t * my_memset(uint8_t *src, size_t length, uint8_t value);


/**
 * @brief clears all the locations to zero.
 *
 * Given a pointer to a dataset at source location, length of bytes,  it sets 
 *  them to zeros.
 *
 * @param ptr Pointer to dataset at src location
 * @param size the length of bytes copied from src
 *
 * 
 * @return ptr Pointer to dataset at src location
 *
 * @notes 1. do not reuse clear_all() func
 * 	2. use pointer arithmetic not array indexing
 */
uint8_t * my_memzero(uint8_t *src, size_t length);


/**
 * @brief reverse the order of the bytes for ex. 1,2,3 will be 3,2,1
 *
 * Given a pointer to a dataset at source location, length of bytes, it places all the 
 * all the bytes in reverse order 
 *
 * @param ptr Pointer to dataset at src location
 * @param size the length of bytes copied from src
 * 
 * @return ptr Pointer to dataset at src location
 *
 * @notes 1. use pointer arithmetic not array indexing
 */
uint8_t * my_reverse(uint8_t *src, size_t length);


/**
 * @brief allocate space in dynamic memory.
 *
 * @param size the no of words
 * 
 * @return ptr Pointer to the memory location if successful, or a NULL pointer
 * if fails to allocate space.
 *
 * @notes 1. use pointer arithmetic not array indexing
 */
uint8_t * reserve_words(size_t length);


/**
 * @brief frees the memory space
 *
 * Given a pointer to a dataset at source location, frees that memory space in 
 * heap
 *
 * @param ptr Pointer to memory location in heap.
 * 
 * @return None
 *
 * @notes 1. use pointer arithmetic not array indexing
 */
void free_words(uint8_t *src);

#endif /* __MEMORY_H__ */

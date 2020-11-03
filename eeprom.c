#include <stdio.h>
#include <stdlib.h>
#include "./eeprom.h"
#include <stdint.h>
//global variables

#define ERASE 0xFF
uint8_t mutex=0;
char path[]="./original.txt";

void open_file(char path[]){
	fptr = fopen(path, "r+");
	if(fptr==NULL){
		puts("error while opening the file, make sure the file exists\n");
	}
}

void close_file(void){
	fclose(fptr);
}

void get_mutex(void){
	while(mutex); //if 1 then wait until it becomes available
	mutex=1;
}
void release_mutex(void){
	mutex=0;
}

void read_page(char* page, uint16_t page_no){
	uint8_t i=0;
	if(page_no>255){
		printf("read_page error:page_no input is invalid allowed page no are 0-255\n");
		printf("\n");
	}
	else{
		open_file(path);
		fseek(fptr, (page_no*32), SEEK_SET);
		for(i=0;i<32;i++){
			page[i]=fgetc(fptr);
		}
		close_file();
	}
	return;
}

void eeprom_read(uint16_t offset, uint16_t size, char* buf){
	uint16_t page_no=0;
	uint8_t word_no=0;
	uint16_t index=0; //this is bufout index which can go from 0-8191
	if(offset>=8192 || size>8192 || size==0){
		printf("eeprom_read error:offset or size input is invalid, allowed offset is 0-8191 and size of the bytes one can read is 1-8192\n");
		printf("\n");
	}
	else{
		while(size!=0){
				page_no=offset/32; 
				word_no=offset%32; 
				
				char* page=(char *) malloc(32*sizeof(char));
				read_page(page, page_no);

				while(word_no!=32 && size!=0){
					buf[index]=page[word_no];

					size--;
					index++;
					word_no++;
				}
				//after page 0
				page_no++;
				offset=page_no*32;
				free(page);
				page=NULL;
		}
	}
	
	return;
}

void eeprom_write(uint16_t offset, uint16_t size, char* buf){
	uint16_t i=0;
	uint16_t page_no; 
	uint8_t word_no; 
	
	uint8_t overwrite_word_no;//for safe over writing
	uint8_t no_of_word=0;
	if(offset>=8192 || size>8192 || size==0){
		printf("eeprom_write error: offset or size input is invalid, allowed offset is 0-8191 and allowed size is 1-8192\n");
		printf("\n");
	}
	else{
		while(size!=0){ 
			page_no=offset/32; 
			word_no=offset%32; 
			overwrite_word_no=offset%32; //the starting word_no onactual page
//to understand a particular page what must be overwritten and not
			no_of_word=0;
			char* page=(char *) calloc(32,sizeof(char)); //created a malloc page
			//fill page values
			while(word_no!=32 && size!=0){
				page[word_no]=buf[i]; //buf = bufin is like data
				word_no++;
				size--;
				i++;
				no_of_word++;
			}
			
			write_page(page, page_no, overwrite_word_no, no_of_word); 
			offset=offset+no_of_word;
			free(page);
			page=NULL;
		}
	}
	return;
}

void write_page(char *page, uint16_t page_no, uint8_t word_no, uint8_t no_of_word){
	if(page_no>255 || word_no>32 || no_of_word>32){
		printf("write_page error: page_no or word_no or no_of_word input is invalid, allowed page no are 0-255, word_no can be 0-31 and no of words 1-32\n");
		printf("\n");
	}
	else{
		open_file(path);
		fseek(fptr, ((page_no*32)+word_no), SEEK_SET); //set fptr to start of page 
		
		while(word_no<32 && no_of_word!=0){
			
			fputc(page[word_no], fptr);
			no_of_word--;
			word_no++;
		}

		close_file();
	}
	return;
	
}

void erase(void){
	uint8_t status=ERASE;
//for writing content	
	char *bufin = (char *) calloc(8192,sizeof(char));
//temporary write sample	
	uint16_t i=0;
	for(i=0;i<8192;i++){
		bufin[i]=32;//blank space
	}
	if(status==ERASE){
		eeprom_write(0, 8192, bufin);	
	}
	free(bufin);
	bufin=NULL;
	return;
}

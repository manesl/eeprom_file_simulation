#include <stdio.h>
#include <stdlib.h>
#include "./eeprom.h"
//global variables
FILE *fptr;
#define ERASE 0xFF

void open_file(void){
	fptr = fopen("./original.txt", "r+");

	if(fptr==NULL){
		puts("error while opening the file");
		//exit(1);
	}
}

void close_file(void){
	fclose(fptr);
}

void read_page(char* page, int page_no){
	int i=0;
	open_file();
	fseek(fptr, (page_no*32), SEEK_SET);
	for(i=0;i<32;i++){
		page[i]=fgetc(fptr);
	}
	close_file();
	return;
}

void eeprom_read(long int offset, int size, char* buf){
	int page_no;
	int word_no;
	int index=0; //this is bufout index which can go from 0-8191
	
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
			offset=offset+index;
			
			free(page);
			page=NULL;
	}
	return;
}

void eeprom_write(long int offset, int size, char* buf){
	int i=0;
	int page_no; 
	int word_no; 
	
	int overwrite_word_no;
	int no_of_word=0;
	
	while(size!=0){ //5
		page_no=offset/32; 
		word_no=offset%32; 
		overwrite_word_no=offset%32; 
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
	
	return;
}

void write_page(char *page, int page_no, int word_no, int no_of_word){
	
	open_file();
	fseek(fptr, ((page_no*32)+word_no), SEEK_SET); //set fptr to start of page 
	
	while(word_no<32 && no_of_word!=0){
		
		fputc(page[word_no], fptr);
		no_of_word--;
		word_no++;
	}

	close_file();
	return;
	
}

void erase(void){
	int status=ERASE;
//for writing content	
	char *bufin = (char *) calloc(8192,sizeof(char));
//temporary write sample	
	int i=0;
	for(i=0;i<8192;i++){
		bufin[i]=32;
	}
	if(status==ERASE){
		eeprom_write(0, 8192, bufin);	
	}
	free(bufin);
	bufin=NULL;
	return;
}

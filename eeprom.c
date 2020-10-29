#include <stdio.h>
#include <stdlib.h>

//global variables
FILE *fptr;
//char page[32];

//function prototypes
void eeprom_read(long int offset, int size, char* buf);
void eeprom_write(long int offset, int size, char* buf);

//low-leve-page access function
void read_page(char *page, int page_no);
void write_page(char *page, int page_no, int word_no, int no_of_word);

//basic file I/O
void open_file(FILE *fptr);
void close_file(FILE *fptr);

int main(){

//for reading content
	char *bufout = (char *) calloc(8192,sizeof(char));
	
//for writing content	
	char *bufin = (char *) calloc(8192,sizeof(char));
	
//temporary write sample	
	int i=0;
	int j=66;
	for(i=0;i<8192;i++){
		bufin[i]=j;
	}

//eeprom write based on offset 0 and size all 8193 [0-8192] words/bytes
	eeprom_write(30, 10, bufin);
	
//get last 3 bytes from 8189 offset
	eeprom_read(25, 15, bufout); //getting the heap address
	
	int b=0;
	for(b=0;b<50;b++){
		printf("%c", bufout[b]); //final output
	}
	
	FILE *fp;
	fp = fopen("./check_output.txt", "w+");
	if(fp==NULL){
		printf("error");
	}
	for(i=0;i<8192;i++){
		fputc(bufout[i], fp);
	}
	
	fclose(fp);
//free maloc
	free(bufout);
	free(bufin);
	bufout=NULL;
	bufin=NULL;
	return 0;
}

void open_file(FILE *fptr){
	fptr = fopen("./original.txt", "r+");

	if(fptr==NULL){
		puts("error while opening the file");
		//exit(1);
	}
}

void close_file(FILE *fptr){
	fclose(fptr);
}

void read_page(char* page, int page_no){
	int i=0;
	open_file(fptr);
	fseek(fptr, (page_no*32), SEEK_SET);
	for(i=0;i<32;i++){
		page[i]=fgetc(fptr);
	}
	close_file(fptr);
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
	
	open_file(fptr);
	fseek(fptr, ((page_no*32)+word_no), SEEK_SET); //set fptr to start of page 
	
	while(word_no<32 && no_of_word!=0){
		
		fputc(page[word_no], fptr);
		no_of_word--;
		word_no++;
	}

	close_file(fptr);
	return;
	
}

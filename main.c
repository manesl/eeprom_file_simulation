#include <stdio.h>
#include <stdlib.h>
#include "eeprom.h"

int main(){

//for reading content
	char *bufout = (char *) calloc(8192,sizeof(char));
	
//for writing content	
	char *bufin = (char *) calloc(8192,sizeof(char));


/*
//to test bad inputs
	write_page(bufin, 256, 32, 33);
	read_page(bufout, 256);
	eeprom_write(8192, 8193, bufin);
	eeprom_read(8192, 8193, bufout);
*/
/*
//checking the erase function
	erase();
	eeprom_read(0, 8192, bufout);
	int b=0;
	for(b=0;b<8192;b++){
		printf("%c", bufout[b]); //final output
	}
*/
//temporary write sample	
	int i=0;
	int j=66;
	for(i=0;i<8192;i++){
		bufin[i]=j;
	}

//eeprom write based on offset 0 and size all 8193 [0-8192] words/bytes
	eeprom_write(0, 8192, bufin);
	
//get last 3 bytes from 8189 offset
	eeprom_read(0, 8192, bufout); //getting the heap address
	
	int b;
	for(b=0;b<8192;b++){
		printf("%c", bufout[b]); //final output
	}
//double check by putting the output in another text file or eeprom	
	FILE *fp;
	fp = fopen("./checkoutput.txt", "w+");
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

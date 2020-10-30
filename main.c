#include <stdio.h>
#include <stdlib.h>
#include "eeprom.h"
#include <pthread.h>

//global variables
//char *bufout;
//char *bufin;
pthread_mutex_t mutex; 
//function prototypes or declarations
void *user1(void *param);
void *user2(void *param);

int main(){
//initializing the mutex
 	pthread_mutex_init(&mutex, NULL); //a single mutex is enough
	//thread creation
	pthread_t tid1, tid2;
	pthread_attr_t attr1, attr2;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_create(&tid1, &attr1, user1, NULL);
	pthread_create(&tid2, &attr2, user2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
/*//for reading content
	//char *bufout 
	bufout = (char *) calloc(8192,sizeof(char));
	
//for writing content	
	//char *bufin 
	bufin = (char *) calloc(8192,sizeof(char));

*/
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
/*//temporary write sample	
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
	}*/
//double check by putting the output in another text file or eeprom	
/*	FILE *fp;
	fp = fopen("./checkoutput.txt", "w+");
	if(fp==NULL){
		printf("error");
	}
	for(i=0;i<8192;i++){
		fputc(bufout[i], fp);
	}
	
	fclose(fp);*/
//free maloc
	//free(bufout);
	//free(bufin);
	//bufout=NULL;
	//bufin=NULL;
	pthread_exit(0);
	return 0;
}
void *user1(void *param){

	int i=0;
	int j=65;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
	for(i=0;i<8192;i++){
		bufin[i]=j;
	}
	pthread_mutex_lock(&mutex);
//temporary write sample
	printf("user 1 is accessing the file EEPROM\n");	
//eeprom write based on offset 0 and size all 8193 [0-8192] words/bytes
	eeprom_write(0, 8192, bufin);
	
//get last 3 bytes from 8189 offset
	eeprom_read(0, 8192, bufout); //getting the heap address
	pthread_mutex_unlock(&mutex);
	int b;
	for(b=0;b<8192;b++){
		printf("%c", bufout[b]); //final output
	}		
}

void *user2(void *param){

	int i=0;
	int j=66;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
	for(i=0;i<8192;i++){
		bufin[i]=j;
	}
	pthread_mutex_lock(&mutex);
//temporary write sample
	printf("user 2 is accessing the file EEPROM\n");	
//eeprom write based on offset 0 and size all 8193 [0-8192] words/bytes
	eeprom_write(0, 8192, bufin);
	
//get last 3 bytes from 8189 offset
	eeprom_read(0, 8192, bufout); //getting the heap address
	pthread_mutex_unlock(&mutex);
	int b;
	for(b=0;b<8192;b++){
		printf("%c", bufout[b]); //final output
	}		
	
}

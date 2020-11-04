#include <stdio.h>
#include <stdlib.h>
#include "eeprom.h"
#include <pthread.h>
#include <stdint.h>

pthread_mutex_t mutex;
//function prototypes or declarations for users
void *user1(void *param); //erase operation and writes A-Z
void *user2(void *param); //overwrite a-z
void *user3(void *param); //bad inputs

int main(){ 
//thread creation
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr1, attr2, attr3;
	pthread_mutex_init(&mutex, NULL);

	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_init(&attr3);

	pthread_create(&tid1, &attr1, user1, NULL);
	pthread_create(&tid2, &attr2, user2, NULL);
	pthread_create(&tid3, &attr3, user3, NULL);
//wait for threads to join to the main thread
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
//thread clean up function
	//pthread_exit(0);
	return 0;
}

void *user1(void *param){
//variables
	uint16_t i=0;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
//writing to the in buffer for writing to the file
	uint8_t j=65;
	for(i=0;i<8192;i++){
		if(j==91){
			j=65;
		}
		bufin[i]=j;
		j++;
	}
//waiting or picking the mutex to perform read write
	//get_mutex();
	pthread_mutex_lock(&mutex);
	printf("user 1 is accessing the file EEPROM\n");
	printf("user 1 performs erase operation on the EEPROM\n");
	
	erase();
	eeprom_read(0, 8192, bufout);
	printf("output of user 1 for erase\n");
	for(i=0;i<8192;i++){
		printf("%c", bufout[i]); //final output
	}
	printf("\n");
//eeprom write based on offset 0 and size [0-8192] words/bytes
	eeprom_write(0, 8192, bufin);//***************************************
//read all bytes from out buffer 
	eeprom_read(0, 8192, bufout); 
//printing the output if user 1 written operation	
	printf("output of user 1 for write operation\n");
	for(i=0;i<8192;i++){
		printf("%c", bufout[i]); //final output
	}
//to save the intermediate output
	open_file("user1.txt");
	for(i=0;i<8192;i++){
		fputc(bufout[i], fptr); //final output
	}
	close_file();
	printf("\n");
//releasing mutex so that others can use the mutex
	//release_mutex();
	pthread_mutex_unlock(&mutex);
	free(bufin);
	bufin=NULL;
	free(bufout);
	bufout=NULL;	
	pthread_exit(0);	
}

void *user2(void *param){

	uint16_t i=0;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
	uint8_t j=97;
	for(i=0;i<8192;i++){
		if(j==123){
			j=97;
		}
		bufin[i]=j;
		j++;
	}
	//get_mutex();
	pthread_mutex_lock(&mutex);
	printf("user 2 is accessing the file EEPROM\n");	
	eeprom_write(0, 8192, bufin);	//******************************************
	eeprom_read(0, 8192, bufout);
	printf("output of user 2 for write operation\n"); 
	for(i=0;i<8192;i++){
		printf("%c", bufout[i]); //final output
	}
	printf("\n");
//to save the intermediate output
	open_file("user2.txt");
	for(i=0;i<8192;i++){
		fputc(bufout[i], fptr); //final output
	}
	close_file();		
	pthread_mutex_unlock(&mutex);
	//release_mutex();
	free(bufin);
	bufin=NULL;
	free(bufout);
	bufout=NULL;
	pthread_exit(0);
}

void *user3(void *param){
	uint16_t i=0;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
	for(i=0;i<832;i++){
		bufin[i]=66;
	}
	//get_mutex();
	pthread_mutex_lock(&mutex);
	printf("user 3 is accessing the file EEPROM\n");
	printf("writing and reading page 12\n");
	write_page(bufin, 12, 0, 32);//**********************
	read_page(bufout, 12);
	for(i=0; i<32; i++){
		printf("%c\n", bufout[i]);
	}
	printf("user 3: testing bad inputs\n");
//to test bad inputs
	write_page(bufin, 256, 32, 33);
	read_page(bufout, 256);
	eeprom_write(8192, 0, bufin);
	eeprom_read(8192, 0, bufout);
	printf("\n");
	pthread_mutex_unlock(&mutex);
	//release_mutex();
	free(bufin);
	bufin=NULL;
	free(bufout);
	bufout=NULL;
	pthread_exit(0);
}

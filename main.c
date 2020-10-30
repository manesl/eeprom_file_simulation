#include <stdio.h>
#include <stdlib.h>
#include "eeprom.h"
#include <pthread.h>

//global variable
//pthread_mutex_t mutex;
 
//function prototypes or declarations for users
void *user1(void *param); //erase operation and writes A
void *user2(void *param); //overwrite B
void *user3(void *param); //bad inputs

int main(){
//initializing the mutex
 	//pthread_mutex_init(&mutex, NULL); 
//thread creation
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr1, attr2, attr3;
	
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
	pthread_exit(0);
	return 0;
}

void *user1(void *param){
//variables
	int i=0;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
//writing to the in buffer for writing to the file
	for(i=0;i<8192;i++){
		bufin[i]=65;
	}
//waiting or picking the mutex to perform read write
	//pthread_mutex_lock(&mutex);
	get_mutex();
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
	eeprom_write(0, 8192, bufin);
//read all bytes from out buffer 
	eeprom_read(0, 8192, bufout); 
//returning the mutex so that other threads can use
	//pthread_mutex_unlock(&mutex);
//printing the output if user 1 written operation	
	printf("output of user 1 for write operation\n");
	for(i=0;i<8192;i++){
		printf("%c", bufout[i]); //final output
	}
	printf("\n");
	//pthread_mutex_unlock(&mutex);
	release_mutex();
	free(bufin);
	bufin=NULL;
	free(bufout);
	bufout=NULL;		
}

void *user2(void *param){

	int i=0;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
	for(i=0;i<8192;i++){
		bufin[i]=66;
	}
	//pthread_mutex_lock(&mutex);
	get_mutex();
	printf("user 2 is accessing the file EEPROM\n");	
	eeprom_write(0, 8192, bufin);	
	eeprom_read(0, 8192, bufout);
	//pthread_mutex_unlock(&mutex);
	printf("output of user 2 for write operation\n"); 
	for(i=0;i<8192;i++){
		printf("%c", bufout[i]); //final output
	}
	printf("\n");
	//pthread_mutex_unlock(&mutex);		
	release_mutex();
	free(bufin);
	bufin=NULL;
	free(bufout);
	bufout=NULL;
}

void *user3(void *param){
	int i=0;
	char *bufout = (char *) calloc(8192, sizeof(char));
	char *bufin = (char *) calloc(8192, sizeof(char));
	for(i=0;i<8192;i++){
		bufin[i]=66;
	}
	//pthread_mutex_lock(&mutex);
	get_mutex();
	printf("user 3 is accessing the file EEPROM\n");
//to test bad inputs
	write_page(bufin, 256, 32, 33);
	read_page(bufout, 256);
	eeprom_write(8192, 8193, bufin);
	eeprom_read(8192, 8193, bufout);
	printf("\n");
	release_mutex();
	//pthread_mutex_unlock(&mutex);
	free(bufin);
	bufin=NULL;
	free(bufout);
	bufout=NULL;
}

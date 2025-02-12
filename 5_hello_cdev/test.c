#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
	int dev = open(argv[1], O_RDONLY);
	if(dev<0){
		perror("Opening was not possible!\n");
		return dev;
	}
	
	printf("Opening was successful!\n");
	close(dev);

	dev = open(argv[1], O_RDWR | O_SYNC);
	if(dev<0){
		perror("Opening was not possible!\n");
		return dev;
	}
	
	printf("Opening was successful!\n");
	close(dev);

	dev = open(argv[1], O_WRONLY | O_NONBLOCK);
	if(dev<0){
		printf("Opening was not possible!\n");
		return dev;
	}
	
	printf("Opening was successful!\n");
	close(dev);
	
	return 0;
}


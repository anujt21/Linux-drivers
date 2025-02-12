#All object files in obj-m will be built as kernel modules
#Conversion of hello.c to hello.o is done by makefiles of linux kernel headers
obj-m += log_level.o

#Add default target. We call makefile location,  then we specify the target as modules
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

#Add clean target to clean all the compiled generated files
clean:
	make -C /lib/modules/$(shell uname -r/build M=$(PWD) clean



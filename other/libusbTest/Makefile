CC=gcc
#PLATFORM=arm-linux-gnueabihf
LIB1=./ArmLinux/lib
LIB2=./Linux/lib
INC=-I.

all: listdevs.c
ifndef PLATFORM
	$(CC) -o listdevs listdevs.c $(INC) $(LIB2)/libusb-1.0.a -lpthread -lrt
else
	${PLATFORM}-${CC} -o ${PLATFORM}_listdevs listdevs.c $(INC) $(LIB1)/libusb-1.0.a -lpthread -lrt
endif


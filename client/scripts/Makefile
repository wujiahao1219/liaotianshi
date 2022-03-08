CC := gcc
CFLAGS := -Wall -O3 -I../include
Libs = -lpthread
Target := client
Source := $(wildcard *.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += client_firstmenu client_login client_main client_ReadFile client_register1 client_send1_recv client_updatepassword client_WriteFile 
AllObjs := $(addsuffix /*.o ,$(Modules))
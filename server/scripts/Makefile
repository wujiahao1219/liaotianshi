CC := gcc
CFLAGS := -Wall -O3 -I../include
Libs = -lpthread -lsqlite3
Target := server  
Source := $(wildcard *.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += server_carryout server_createtable server_initlink server_insertdb server_insertlink server_login server_main server_readdb server_register1 server_searchaccount server_searchaccountbycfd server_searchcfdbytoaccount server_searchpassword server_sendrecv server_updatedb server_updatepassword server_thread_destroy server_thread_add_job server_threadpool_init
AllObjs := $(addsuffix /*.o ,$(Modules))
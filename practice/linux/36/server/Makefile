SRCS:=main.c worker.c tcp.c epoll.c sendfd.c transfile.c
OBJS:=$(SRCS:%.c=%.o)
server:$(OBJS)
	gcc $^ -o $@ -lpthread # link
%.o:%.c
	gcc -c $^ -o $@ -g # compile
clean:
	$(RM) $(OBJS) server

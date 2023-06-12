CXX = g++
CXXFLAGS = -Iinclude -std=c++17
LDFLAGS = -lpthread -lhiredis -lredis++

SRCDIR = src
SERVER_SRCDIR = $(SRCDIR)/online/server
SHARED_SRCDIR = $(SRCDIR)/shared

SERVER_SRCS = $(wildcard $(SERVER_SRCDIR)/*.cc)
SHARED_SRCS = $(wildcard $(SHARED_SRCDIR)/*.cc)
SRCS = $(SERVER_SRCS) $(SHARED_SRCS)

OBJS = $(SRCS:.cc=.o)
TARGET = program

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)


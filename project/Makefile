CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lcrypto

SRCS = main.cpp command_line_parser.cpp config_reader.cpp vector_data.cpp result_data.cpp tcp_client.cpp md5_hasher.cpp auth_manager.cpp protocol_handler.cpp error_handler.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = vclient

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)

.PHONY: all clean

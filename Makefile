CC=g++
PROGNAME?=program
LIB_DIR?=./Lib
BUILD_DIR?=./Build
SRC_DIRS?=./Src
CFLAGS=-O2 -g -Wall -W -Wno-unused-parameter
LDFLAGS=-lSDL2 -lGL -lGLEW -lopenal -lSDL_ttf -lm -lpthread -llua
SRCS:=$(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS:=$(SRCS:%=$(BUILD_DIR)/%.o)
DEPS:=$(OBJS:.o=.d)
INC_DIRS:=$(shell find $(SRC_DIRS) -type d)
INC_FLAGS:=$(addprefix -I,$(INC_DIRS))
CPPFLAGS?=$(INC_FLAGS) -MMD -MP

ASSETS_DIR=./Assets

$(BUILD_DIR)/$(PROGNAME): $(OBJS)
	$(CC) $(OBJS) -o $@-debug $(LDFLAGS)
	$(CC) $(OBJS) -DNDEBUG -o $@-release $(LDFLAGS)
	$(CP_R) $(ASSETS_DIR) $(BUILD_DIR)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)
MKDIR_P?=mkdir -p
MV_R?=mv -r
CP_R?=cp -r

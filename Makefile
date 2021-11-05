CC=clang
PROGNAME?=starshipfleet
LIB_DIR?=./lib
BUILD_DIR?=./build
SRC_DIRS?=./src
CFLAGS=-O2 -g -Wall -W -std=c11 \
    -I$(LIB_DIR)/glew-2.1.0/include \
	-I$(LIB_DIR)/cglm-0.8.4/include \
	-I$(LIB_DIR)/SDL2-2.0.16/include \
	-I$(LIB_DIR)/openal-soft-1.21.1
LDFLAGS=-lGL -lGLEW -lSDL2 -lopenal -lSDL2_ttf
SRCS:=$(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS:=$(SRCS:%=$(BUILD_DIR)/%.o)
DEPS:=$(OBJS:.o=.d)
INC_DIRS:=$(shell find $(SRC_DIRS) -type d)
INC_FLAGS:=$(addprefix -I,$(INC_DIRS))
CPPFLAGS?=$(INC_FLAGS) -MMD -MP

ASSETS_DIR=./assets

$(BUILD_DIR)/$(PROGNAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	$(CP_R) $(ASSETS_DIR) $(BUILD_DIR)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)
MKDIR_P?=mkdir -p
MV_R?=mv -r
CP_R?=cp -r

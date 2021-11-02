#CC=clang
#PROGNAME=starshipfleet
#SDIR=src/
#IDIR=include/
#CFLAGS=-g -Wall -I(./src)
#LDFLAGS=
#BUILD_DIR=build
#DEPS=$(IDIR)config.h \
#	$(IDIR)log.h
#OBJS=$(SDIR)main.o \
#	$(SDIR)log.o \
#	$(SDIR)config.o

#$(BUILD_DIR)/%.o: %.c $(DEPS)
#	$(CC) $(CFLAGS) -c $< -o $@

#$(BUILD_DIR)/$(PROGNAME): $(OBJS)
#	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

#.PHONY: clean
#clean:
#	rm -r $(BUILD_DIR)/*.o $(BUILD_DIR)/$(PROGNAME)

#-include $(DEPS)
CC=clang
CFLAGS=
TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p


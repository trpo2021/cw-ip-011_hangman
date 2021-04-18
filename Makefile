APP_NAME = hangman
LIB_NAME = lib$(APP_NAME)
TEST_NAME = $(APP_NAME)-test

CC = g++
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I $(SRC_DIR) -I $(THIRD_DIR) -I $(SDL_INCLUDE_PATH) -L $(SDL_LIB_PATH) -MP -MMD
LDFLAGS = -D_REENTRANT
LDLIBS = -Wl,-rpath=$(SDL_RPATH) -Wl,--enable-new-dtags -lSDL2 -lSDL2_image -lSDL2_gfx -lm -ldl -lpthread -lrt -Wl,--no-as-needed -ldl

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test
THIRD_DIR = thirdparty

SDL_DIR = SDL
SDL_LIB_DIR = lib
SDL_INCLUDE_DIR = include

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)

SDL_PATH = $(THIRD_DIR)/$(SDL_DIR)
SDL_INCLUDE_PATH = $(SDL_PATH)/$(SDL_INCLUDE_DIR)
SDL_LIB_PATH = $(SDL_PATH)/$(SDL_LIB_DIR)
SDL_RPATH = $(shell pwd)/$(SDL_LIB_PATH)

CTEST_PATH = $(THIRD_DIR)/ctest.h

SRC_EXT = c

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

TEST_SOURCES = $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)')
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(TEST_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: all

all: $(APP_PATH)

.PHONY: test

test: $(TEST_PATH)
	$(TEST_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(TEST_PATH): $(TEST_OBJECTS) $(LIB_PATH) $(CTEST_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TEST_OBJECTS) $(LIB_PATH) -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
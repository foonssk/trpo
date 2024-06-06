CC = g++
CFLAGS = -Wall -Werror
CPPFLAGS = -I src -MP -MMD -I thirdparty
LDFLAGS = -lm

APP_NAME = sorts
LIB_NAME = libsorts
TEST_NAME = test

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = filetest
DEPS_DIR = thirdparty

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a
TEST_APP = $(BIN_DIR)/$(TEST_NAME)

SRC_EXT = cpp

APP_SOURCES = $(wildcard $(SRC_DIR)/$(APP_NAME)/*.$(SRC_EXT))
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(wildcard $(SRC_DIR)/$(LIB_NAME)/*.$(SRC_EXT))
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.$(SRC_EXT))
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(TEST_DIR)/%.o)

TEST_LIBS = $(LIB_PATH)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(TEST_APP): $(TEST_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


.PHONY: run
all:
	./$(APP_PATH)

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(TEST_APP)
	$(RM) $(APP_OBJECTS) $(LIB_OBJECTS) $(TEST_OBJECTS)
	$(RM) $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/*.a
	$(RM) $(OBJ_DIR)/$(SRC_DIR)/**/*.o
	$(RM) $(OBJ_DIR)/$(SRC_DIR)/**/*.d
	$(RM) $(OBJ_DIR)/$(TEST_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(TEST_DIR)/*.d

.PHONY: test
test: $(TEST_PATH)
        $(TEST_PATH)

	$(TEST_PATH): $(TEST_OBJECTS) $(LIB_PATH) $(CTEST_PATH)
		$(CC) $(CFLAGS) $(CPPFLAGS) $(TEST_OBJECTS) $(LIB_PATH) -o $@ $(LDFLAGS) $(LDLIBS)

	$(LIB_PATH): $(LIB_OBJECTS)
		ar rcs $@ $^

	$(OBJ_DIR)/%.o: %.c
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
CC			= g++
BUILDPATH	= build
SOURCEPATH	= source
CFLAGS		= -c -Wall -I$(SOURCEPATH)
LDFLAGS		= 

SRC_FILES	= $(wildcard $(SOURCEPATH)/*/*.cpp) $(SOURCEPATH)/main.cpp
OBJ_FILES	= $(patsubst $(SOURCEPATH)/%.cpp,$(BUILDPATH)/%.o,$(SRC_FILES))

TARGET		= kNN
IGNORE		= fnc/kNN.cpp

.PHONY: all build_env clean

all: $(TARGET)

# build binary from object files
$(TARGET): $(filter-out $(IGNORE:%.cpp=$(BUILDPATH)/%.o),$(OBJ_FILES))
	$(CC) -o $@ $^ $(LDFLAGS)

# compile object files from corresponding cpp files
$(OBJ_FILES): $(BUILDPATH)/%.o:$(SOURCEPATH)/%.cpp | build_env
	$(CC) $(CFLAGS) $< -o $@

# setup build environment
build_env:
	mkdir -p $(sort $(dir $(OBJ_FILES)))

# clean out the build
clean:
	rm -rf $(BUILDPATH)
	rm $(TARGET)

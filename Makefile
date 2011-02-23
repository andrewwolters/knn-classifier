CC			= g++
BUILDPATH	= build
INCLUDEPATH	= include
SOURCEPATH	= source
INCLUDE		= -I $(INCLUDEPATH)
TARGET		= $(BUILDPATH)/kNN

all: build

build: compile link

compile:
	mkdir -p $(BUILDPATH)
	$(CC) -c $(SOURCEPATH)/kNN/Dataset.cpp -o $(BUILDPATH)/Dataset.o $(INCLUDE)
	$(CC) -c $(SOURCEPATH)/datasets/FileDataset.cpp -o $(BUILDPATH)/FileDataset.o $(INCLUDE)
#	$(CC) -c $(SOURCEPATH)/optimizers/HMN.cpp -o $(BUILDPATH)/HMN.o $(INCLUDE)
	$(CC) -c $(SOURCEPATH)/main.cpp -o $(BUILDPATH)/main.o $(INCLUDE)

link:
	$(CC) -o $(TARGET) $(BUILDPATH)/*.o $(INCLUDE)

clean:
	rm -f $(BUILDPATH)/*.o

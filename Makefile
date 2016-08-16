CFLAGS=-std=c++0x
LIBS=
INCLUDEDIRS=-I ./ -I ./vendor/yaml-cpp/include
BIN_DIR=./bin

SOURCES=main.cpp
SOURCES+=ConfigFile/ConfigFile.cpp
SOURCES+=GPIOPin/GPIOPin.cpp
SOURCES+=GPIOPin/Actor.cpp
SOURCES+=Helpers/PinHelper.cpp
SOURCES+=Helpers/ActorHelper.cpp
SOURCES+=Server/Server.cpp
SOURCES+=Command/Command.cpp
SOURCES+=Command/ActorCommands.cpp
OUTPUT_NAME=$(BIN_DIR)/RPi_Automation

# LIBS+=-lwiringPi
LIBS+=-lyaml-cpp
all: main.cpp
	g++ $(CFLAGS) -o $(OUTPUT_NAME) $(SOURCES) $(INCLUDEDIRS) $(LIBS) -lpthread

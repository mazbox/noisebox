
#run the two commands to enable audio and midi
#sudo modprobe snd_bcm2835
#sudo modprobe snd_seq
CC=g++

CFLAGS=-c -O3 -mfloat-abi=softfp -Wall -I./src -I./rtmidi-1.0.15/ -I./rtaudio-4.0.10/ -D__LINUX_ALSASEQ__ -DHAVE_GETTIMEOFDAY -D__LINUX_ALSA__
LDFLAGS= -DHAVE_GETTIMEOFDAY -D__LINUX_ALSA__ -lpthread -lasound
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=noisebox

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) rtaudio-4.0.10/RtAudio.cpp -o rtaudio-4.0.10/RtAudio.o
	$(CC) $(CFLAGS) rtmidi-1.0.15/RtMidi.cpp -o rtmidi-1.0.15/RtMidi.o
	$(CC) $(LDFLAGS) $(OBJECTS) rtaudio-4.0.10/RtAudio.o rtmidi-1.0.15/RtMidi.o -o $@	
	rm src/*.o
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


	
clean:
	rm src/*.o
	rm $(EXECUTABLE)


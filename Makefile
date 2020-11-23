CC=g++
CFLAGS=-I.
DEPS = common.h Uas.h Sensor.h Simulator.h
OBJ = Uas.o Sensor.o Simulator.o Main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simulator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

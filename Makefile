LSFML=-L../SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
ISFML=-I../SFML-2.5.1/include -I$(HEADERS)
BUILD=./build
SRC=./src
HEADERS=./src/headers
COMPILE=g++ -std=c++17 -c $< $(ISFML) -o .

asteroid: $(BUILD)/main.o $(BUILD)/ship.o $(BUILD)/textures.o $(BUILD)/movement.o $(BUILD)/bullet.o $(BUILD)/bulletManager.o $(BUILD)/asteroid.o $(BUILD)/asteroidManager.o  $(BUILD)/particles.o
	g++ -std=c++17 $^ $(LSFML) -o ./$@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(COMPILE)/$@

clear:
	rm -rf ./asteroid $(BUILD)/*

.PHONY: clear

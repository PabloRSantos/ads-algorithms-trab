#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dragon.h"
#include "rent.h"
#include "element.h"

#define DRAGONS_FILE_PATH "./data/dragons.bin"

FILE* dragonsFile;
int dragonsLength = 0;
int dragonCod = 1;

int initDragons() {
	int i;
	Dragon dragon;
  	dragonsFile = fopen(DRAGONS_FILE_PATH, "r+b");

	if(dragonsFile == NULL) {
		return 0;
	}

	fseek(dragonsFile, 0, SEEK_END);
	int fileSize = ftell(dragonsFile);
	dragonsLength = fileSize / sizeof(Dragon);

    rewind(dragonsFile);

	if(dragonsLength == 0) {
		dragon.cod = dragonCod;
		dragon.age = 1000;
		dragon.dailyValue = 100.5;
		dragon.units = 5;
		dragon.elementCode = 1;
		strcpy(dragon.name, "Drogon");
		dragonCod++;
		fwrite(&dragon, sizeof(Dragon), 1, dragonsFile);
		dragonsLength++;
	} else {
		int biggestDragonCode = 0;
		for(i = 0; i < dragonsLength; i++){
			fread(&dragon, sizeof(Dragon), 1, dragonsFile);

			if(dragon.cod > biggestDragonCode) {
				biggestDragonCode = dragon.cod;
			}
		}
    	rewind(dragonsFile);
		dragonCod = biggestDragonCode + 1;
	}
	
	return 1;		
}

int saveDragon(Dragon dragon) {
	Element* element = getElementByCod(dragon.elementCode);
	if(element == NULL) {
		return 2;
	}
	free(element);

	dragon.cod = dragonCod;
	fseek(dragonsFile, dragonsLength * sizeof(Dragon), SEEK_SET);
	fwrite(&dragon, sizeof(Dragon), 1, dragonsFile);
	
	dragonCod++;
	dragonsLength++;
	
	return 1;
}

int updateDragon(Dragon dragon) {
	Dragon* currentDragon = getDragonByCod(dragon.cod);

	if(currentDragon == NULL) {
		return 2;
	}

	int i;
	for(i = 0; i < dragonsLength; i++) {
		fread(currentDragon, sizeof(Dragon), 1, dragonsFile);
		if(currentDragon->cod == dragon.cod) {
			strcpy(currentDragon->name, dragon.name);
			currentDragon->age = dragon.age;
			currentDragon->dailyValue = dragon.dailyValue;
			currentDragon->units = dragon.units;
			fseek(dragonsFile, i * sizeof(Dragon), SEEK_SET);
			fwrite(currentDragon, sizeof(Dragon), 1, dragonsFile);
			
			rewind(dragonsFile);
			free(currentDragon);
			return 1;
		}
	}
	
	rewind(dragonsFile);
	free(currentDragon);
	return 0;
}

int getDragonsLength() {
	return dragonsLength;
}

Dragon* getDragonByIndex(int index) {
	Dragon* dragon = (Dragon*) malloc(sizeof(Dragon));

	if(dragon == NULL) {
		return NULL;
	}

	fseek(dragonsFile, index * sizeof(Dragon), SEEK_SET);
	fread(dragon, sizeof(Dragon), 1, dragonsFile);
	rewind(dragonsFile);

	return dragon;
}

Dragon* getDragonByElementCod(int cod) {
	int i;
	Dragon* dragon = (Dragon*) malloc(sizeof(Dragon));

	if(dragon == NULL) {
		return NULL;
	}

	for(i = 0; i < dragonsLength; i++) {
		fread(dragon, sizeof(Dragon), 1, dragonsFile);
		if(dragon->elementCode == cod) {
			rewind(dragonsFile);
			return dragon;
		}
	}

	rewind(dragonsFile);
	return NULL;
}

Dragon* getDragonByCod(int cod) {
	int i;
	Dragon* dragon = (Dragon*) malloc(sizeof(Dragon));

	if(dragon == NULL) {
		return NULL;
	}

	for(i = 0; i < dragonsLength; i++) {
		fread(dragon, sizeof(Dragon), 1, dragonsFile);
		if(dragon->cod == cod) {
			rewind(dragonsFile);
			return dragon;
		}
	}

	rewind(dragonsFile);
	return NULL;
}

int deleteDragonByCod(int cod) {
	Rent* rent = getRentByDragonCod(cod);
    if(rent != NULL) {
		free(rent);
		return 2;
	}

	Dragon dragon;
	FILE* tempFile = fopen("temp.bin", "wb");
	int wasFound = 0;

	int i;
	for(i = 0; i < dragonsLength; i++){
		fread(&dragon, sizeof(Dragon), 1, dragonsFile);
		if (dragon.cod == cod) {
			wasFound = 1;
		} else {
			fwrite(&dragon, sizeof(Dragon), 1, tempFile);
		}
	}

	remove(DRAGONS_FILE_PATH);
    rename("temp.bin", DRAGONS_FILE_PATH);
	fclose(tempFile);
    fclose(dragonsFile);
  	dragonsFile = fopen(DRAGONS_FILE_PATH, "r+b");

	if(wasFound == 1) {
		dragonsLength--;
	}
	return wasFound;
}

int incrementDragonUnitByCod(int cod) {
	Dragon dragon;
	int i;
	
	for(i = 0; i < dragonsLength; i++) {
		fread(&dragon, sizeof(Dragon), 1, dragonsFile);
		if(dragon.cod == cod) {
			dragon.units++;
			fseek(dragonsFile, i * sizeof(Dragon), SEEK_SET);
			fwrite(&dragon, sizeof(Dragon), 1, dragonsFile);
			rewind(dragonsFile);
			return 1;
		}
	}
	
	rewind(dragonsFile);
	return 0;
}

int decrementDragonUnitByCod(int cod) {
	Dragon dragon;
	int i;
	
	for(i = 0; i < dragonsLength; i++) {
		fread(&dragon, sizeof(Dragon), 1, dragonsFile);
		if(dragon.cod == cod) {
			dragon.units--;
			fseek(dragonsFile, i * sizeof(Dragon), SEEK_SET);
			fwrite(&dragon, sizeof(Dragon), 1, dragonsFile);
			rewind(dragonsFile);
			return 1;
		}
	}
	
	rewind(dragonsFile);
	return 0;
}

int finishDragons() {
	fclose(dragonsFile);
	return 1;
}



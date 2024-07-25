#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "warrior.h"
#include "rent.h"

#define WARRIORS_FILE_PATH "./data/warriors.bin"

FILE* warriorsFile;
int warriorsLength = 0;
int warriorCod = 1;

int initWarriors() {
	int i;
	Warrior warrior;
  	warriorsFile = fopen(WARRIORS_FILE_PATH, "r+b");

	if(warriorsFile == NULL) {
		return 0;
	}

	fseek(warriorsFile, 0, SEEK_END);
	int fileSize = ftell(warriorsFile);
	warriorsLength = fileSize / sizeof(Warrior);

    rewind(warriorsFile);

	if(warriorsLength == 0) {
		warrior.cod = warriorCod;
		strcpy(warrior.kingdom, "Kattegat");
		strcpy(warrior.name, "Ragnar");
		strcpy(warrior.title, "Rei");
		warriorCod++;
		fwrite(&warrior, sizeof(Warrior), 1, warriorsFile);
		warriorsLength++;
	} else {
		int biggestWarriorCode = 0;
		for(i = 0; i < warriorsLength; i++){
			fread(&warrior, sizeof(Warrior), 1, warriorsFile);

			if(warrior.cod > biggestWarriorCode) {
				biggestWarriorCode = warrior.cod;
			}
		}
    	rewind(warriorsFile);
		warriorCod = biggestWarriorCode + 1;
	}
	
	return 1;		
}

int saveWarrior(Warrior warrior) {
	warrior.cod = warriorCod;
	fseek(warriorsFile, warriorsLength * sizeof(Warrior), SEEK_SET);
	fwrite(&warrior, sizeof(Warrior), 1, warriorsFile);
	
	warriorCod++;
	warriorsLength++;
	
	return 1;
}

int updateWarrior(Warrior warrior) {
	Warrior* currentWarrior = getWarriorByCod(warrior.cod);

	if(currentWarrior == NULL) {
		return 2;
	}

	int i;
	for(i = 0; i < warriorsLength; i++) {
		fread(currentWarrior, sizeof(Warrior), 1, warriorsFile);
		if(currentWarrior->cod == warrior.cod) {
			strcpy(currentWarrior->kingdom, warrior.kingdom);
			strcpy(currentWarrior->name, warrior.name);
			strcpy(currentWarrior->title, warrior.title);
			fseek(warriorsFile, i * sizeof(Warrior), SEEK_SET);
			fwrite(currentWarrior, sizeof(Warrior), 1, warriorsFile);
			
			rewind(warriorsFile);
			free(currentWarrior);
			return 1;
		}
	}
	
	rewind(warriorsFile);
	free(currentWarrior);
	return 0;
}

int getWarriorsLength() {
	return warriorsLength;
}

Warrior* getWarriorByIndex(int index) {
	Warrior* warrior = (Warrior*) malloc(sizeof(Warrior));

	if(warrior == NULL) {
		return NULL;
	}

	fseek(warriorsFile, index * sizeof(Warrior), SEEK_SET);
	fread(warrior, sizeof(Warrior), 1, warriorsFile);
	rewind(warriorsFile);

	return warrior;
}

Warrior* getWarriorByCod(int cod) {
	int i;
	Warrior* warrior = (Warrior*) malloc(sizeof(Warrior));

	if(warrior == NULL) {
		return NULL;
	}

	for(i = 0; i < warriorsLength; i++) {
		fread(warrior, sizeof(Warrior), 1, warriorsFile);
		if(warrior->cod == cod) {
			rewind(warriorsFile);
			return warrior;
		}
	}

	rewind(warriorsFile);
	return NULL;
}

int deleteWarriorByCod(int cod) {
	Rent* rent = getRentByWarriorCod(cod);
	if(rent != NULL) {
		free(rent);
		return 2;
	}

	Warrior warrior;
	FILE* tempFile = fopen("temp.bin", "wb");
	int wasFound = 0;

	int i;
	for(i = 0; i < warriorsLength; i++){
		fread(&warrior, sizeof(Warrior), 1, warriorsFile);
		if (warrior.cod == cod) {
			wasFound = 1;
		} else {
			fwrite(&warrior, sizeof(Warrior), 1, tempFile);
		}
	}

	remove(WARRIORS_FILE_PATH);
    rename("temp.bin", WARRIORS_FILE_PATH);
	fclose(tempFile);
    fclose(warriorsFile);
  	warriorsFile = fopen(WARRIORS_FILE_PATH, "r+b");
	
	if(wasFound == 1) {
		warriorsLength--;
	}
	return wasFound;
}

int finishWarriors() {
  	fclose(warriorsFile);
	return 1;
}

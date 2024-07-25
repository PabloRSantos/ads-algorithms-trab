#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rent.h"
#include "warrior.h"
#include "dragon.h"

#define RENTS_FILE_PATH "./data/rents.bin"

FILE* rentsFile;
int rentsLength = 0;
int rentCod = 1;

int initRents() {
	int i;
	Rent rent;
  	rentsFile = fopen(RENTS_FILE_PATH, "r+b");

	if(rentsFile == NULL) {
		return 0;
	}

	fseek(rentsFile, 0, SEEK_END);
	int fileSize = ftell(rentsFile);
	rentsLength = fileSize / sizeof(Rent);

    rewind(rentsFile);

	if(rentsLength == 0) {
		rent.cod = rentCod;
		rent.dragonCod = 1;
		rent.warriorCod = 1;
		rent.paid = 0;
		strcpy(rent.endRentDate, "12/12/2022");
		strcpy(rent.startRentDate, "12/10/2022");
		rentCod++;
		fwrite(&rent, sizeof(Rent), 1, rentsFile);
		rentsLength++;
	} else {
		int biggestRentCode = 0;
		for(i = 0; i < rentsLength; i++){
			fread(&rent, sizeof(Rent), 1, rentsFile);

			if(rent.cod > biggestRentCode) {
				biggestRentCode = rent.cod;
			}
		}
    	rewind(rentsFile);
		rentCod = biggestRentCode + 1;
	}
	
	return 1;		
}

int saveRent(Rent rent) {
	Warrior* warrior = getWarriorByCod(rent.warriorCod);
	if(warrior == NULL) {
		return 2;
	}
	free(warrior);

	Dragon* dragon = getDragonByCod(rent.dragonCod);
	if(dragon == NULL) {
		return 3;
	} else if(dragon->units == 0) {
		free(dragon);
		return 4;
	}
	free(dragon);

	if(decrementDragonUnitByCod(rent.dragonCod) == 0) {
		return 0;
	}

	rent.cod = rentCod;
	fseek(rentsFile, rentsLength * sizeof(Rent), SEEK_SET);
	fwrite(&rent, sizeof(Rent), 1, rentsFile);
	
	rentCod++;
	rentsLength++;
	
	return 1;
}

int updateRent(Rent rent) {
	Rent* currentRent = getRentByCod(rent.cod);

	if(currentRent == NULL) {
		return 2;
	}

	int i;
	for(i = 0; i < rentsLength; i++) {
		fread(currentRent, sizeof(Rent), 1, rentsFile);
		if(currentRent->cod == rent.cod) {
			strcpy(currentRent->startRentDate, rent.startRentDate);
			strcpy(currentRent->endRentDate, rent.endRentDate);
			fseek(rentsFile, i * sizeof(Rent), SEEK_SET);
			fwrite(currentRent, sizeof(Rent), 1, rentsFile);

			rewind(rentsFile);
			free(currentRent);
			return 1;
		}
	}
	
	rewind(rentsFile);
	free(currentRent);
	return 0;
}

int getRentsLength() {
	return rentsLength;
}

Rent* getRentByIndex(int index) {
	Rent* rent = (Rent*) malloc(sizeof(Rent));

	if(rent == NULL) {
		return NULL;
	}

	fseek(rentsFile, index * sizeof(Rent), SEEK_SET);
	fread(rent, sizeof(Rent), 1, rentsFile);
	rewind(rentsFile);

	return rent;	
}

Rent* getRentByCod(int cod) {
	int i;
	Rent* rent = (Rent*) malloc(sizeof(Rent));

	if(rent == NULL) {
		return NULL;
	}

	for(i = 0; i < rentsLength; i++) {
		fread(rent, sizeof(Rent), 1, rentsFile);
		if(rent->cod == cod) {
			rewind(rentsFile);
			return rent;
		}
	}

	rewind(rentsFile);
	return NULL;
}

Rent* getRentByDragonCod(int cod) {
	int i;
	Rent* rent = (Rent*) malloc(sizeof(Rent));

	if(rent == NULL) {
		return NULL;
	}

	for(i = 0; i < rentsLength; i++) {
		fread(rent, sizeof(Rent), 1, rentsFile);
		if(rent->dragonCod == cod) {
			rewind(rentsFile);
			return rent;
		}
	}

	rewind(rentsFile);
	return NULL;
}

Rent* getRentByWarriorCod(int cod) {
	int i;
	Rent* rent = (Rent*) malloc(sizeof(Rent));

	if(rent == NULL) {
		return NULL;
	}

	for(i = 0; i < rentsLength; i++) {
		fread(rent, sizeof(Rent), 1, rentsFile);
		if(rent->warriorCod == cod) {
			rewind(rentsFile);
			return rent;
		}
	}

	rewind(rentsFile);
	return NULL;
}

int finishRentByCod(int cod) {
	Rent* rent = getRentByCod(cod);
	if(rent == NULL) {
		return 2;
	} else if(rent->paid == 1) {
		free(rent);
		return 3;
	}

	if(incrementDragonUnitByCod(rent->dragonCod) == 0) {
		return 0;
	}

	int i;
	for(i = 0; i < rentsLength; i++) {
		fread(rent, sizeof(Rent), 1, rentsFile);
		if(rent->cod == cod) {
			rent->paid = 1;
			fseek(rentsFile, i * sizeof(Rent), SEEK_SET);
			fwrite(rent, sizeof(Rent), 1, rentsFile);
			rewind(rentsFile);
			return 1;
		}
	}
	
	rewind(rentsFile);
	free(rent);
	return 0;
}

int finishRents() {
	fclose(rentsFile);
	return 1;
}
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"
#include "dragon.h"

#define ELEMENTS_FILE_PATH "./data/elements.bin"

FILE* elementsFile;
int elementsLength = 0;
int elementCod = 1;

int initElements() {
	int i;
	Element element;
  	elementsFile = fopen(ELEMENTS_FILE_PATH, "r+b");

	if(elementsFile == NULL) {
		return 0;
	}

	fseek(elementsFile, 0, SEEK_END);
	int fileSize = ftell(elementsFile);
	elementsLength = fileSize / sizeof(Element);

    rewind(elementsFile);

	if(elementsLength == 0) {
		element.cod = elementCod;
		strcpy(element.name, "Agua");
		strcpy(element.vulnerability, "Fogo");
		elementCod++;
		fwrite(&element, sizeof(Element), 1, elementsFile);
		elementsLength++;
	} else {
		int biggestElementCode = 0;
		for(i = 0; i < elementsLength; i++){
			fread(&element, sizeof(Element), 1, elementsFile);

			if(element.cod > biggestElementCode) {
				biggestElementCode = element.cod;
			}
		}
    	rewind(elementsFile);
		elementCod = biggestElementCode + 1;
	}
	
	return 1;		
}

int saveElement(Element element) {
	element.cod = elementCod;
	fseek(elementsFile, elementsLength * sizeof(Element), SEEK_SET);
	fwrite(&element, sizeof(Element), 1, elementsFile);
	
	elementCod++;
	elementsLength++;
	
	return 1;
}

int updateElement(Element element) {
	Element* currentElement = getElementByCod(element.cod);

	if(currentElement == NULL) {
		return 2;
	}

	int i;
	for(i = 0; i < elementsLength; i++) {
		fread(currentElement, sizeof(Element), 1, elementsFile);
		if(currentElement->cod == element.cod) {
			strcpy(currentElement->name, element.name);
			strcpy(currentElement->vulnerability, element.vulnerability);
			fseek(elementsFile, i * sizeof(Element), SEEK_SET);
			fwrite(currentElement, sizeof(Element), 1, elementsFile);
			
			rewind(elementsFile);
			free(currentElement);
			return 1;
		}
	}
	
	rewind(elementsFile);
	free(currentElement);
	return 0;
}

int getElementsLength() {
	return elementsLength;
}

Element* getElementByIndex(int index) {
	Element* element = (Element*) malloc(sizeof(Element));

	if(element == NULL) {
		return NULL;
	}

	fseek(elementsFile, index * sizeof(Element), SEEK_SET);
	fread(element, sizeof(Element), 1, elementsFile);
	rewind(elementsFile);

	return element;
}

Element* getElementByCod(int cod) {
	int i;
	Element* element = (Element*) malloc(sizeof(Element));

	if(element == NULL) {
		return NULL;
	}

	for(i = 0; i < elementsLength; i++) {
		fread(element, sizeof(Element), 1, elementsFile);
		if(element->cod == cod) {
			rewind(elementsFile);
			return element;
		}
	}

	rewind(elementsFile);
	return NULL;
}

int deleteElementByCod(int cod) {
    Dragon* dragon = getDragonByElementCod(cod);

	if(dragon != NULL) {
		free(dragon);
		return 2;
	}

	Element element;
	FILE* tempFile = fopen("temp.bin", "wb");
	int wasFound = 0;

	int i;
	for(i = 0; i < elementsLength; i++){
		fread(&element, sizeof(Element), 1, elementsFile);
		if (element.cod == cod) {
			wasFound = 1;
		} else {
			fwrite(&element, sizeof(Element), 1, tempFile);
		}
	}

	remove(ELEMENTS_FILE_PATH);
    rename("temp.bin", ELEMENTS_FILE_PATH);
	fclose(tempFile);
    fclose(elementsFile);
  	elementsFile = fopen(ELEMENTS_FILE_PATH, "r+b");

	if(wasFound == 1) {
		elementsLength--;
	}

	return wasFound;
}

int finishElements() {
	fclose(elementsFile);
	return 1;
}



typedef struct {
	int cod;
	char name[30];
	int age;
    float dailyValue;
    int units;
	int elementCode;
} Dragon;

int initDragons();
int finishDragons();
int saveDragon(Dragon dragon);
int updateDragon(Dragon dragon);
int incrementDragonUnitByCod(int cod);
int decrementDragonUnitByCod(int cod);
int getDragonsLength();
Dragon* getDragonByIndex(int index);
Dragon* getDragonByCod(int cod);
int deleteDragonByCod(int cod);
Dragon* getDragonByElementCod (int cod);
int deleteDragonByName(char* name);

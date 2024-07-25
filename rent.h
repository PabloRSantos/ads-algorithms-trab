
typedef struct {
    int cod;
	int paid;
	char endRentDate[30];
	char startRentDate[30];
    int warriorCod;
    int dragonCod;
} Rent;

int initRents();
int finishRents();
int finishRentByCod(int cod);
int saveRent(Rent Rent);
int updateRent(Rent Rent);
int getRentsLength();
Rent* getRentByIndex(int index);
Rent* getRentByCod(int cod);
Rent* getRentByDragonCod(int cod);
Rent* getRentByWarriorCod(int cod);

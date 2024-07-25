
typedef struct {
	int cod;
	char name[30];
	char title[30];
	char kingdom[30];
} Warrior;

int initWarriors();
int finishWarriors();
int saveWarrior(Warrior warrior);
int updateWarrior(Warrior warrior);
int getWarriorsLength();
Warrior* getWarriorByIndex(int index);
Warrior* getWarriorByCod(int cod);
int deleteWarriorByCod(int cod);

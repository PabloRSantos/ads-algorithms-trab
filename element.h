
typedef struct {
	int cod;
	char name[30];
	char vulnerability[30];
} Element;

int initElements();
int finishElements();
int saveElement(Element element);
int updateElement(Element element);
int getElementsLength();
Element* getElementByIndex(int index);
Element* getElementByCod(int cod);
int deleteElementByCod(int cod);

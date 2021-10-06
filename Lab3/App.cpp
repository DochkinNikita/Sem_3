#include "App.h"

void App::start(){

	List list;

	list.getListFromFile(const_cast<char*>("Date.txt"));

	int key = -1;
	do {

		cout << "----MENU----" << endl;
		cout << "1) Show All Date's" << endl;
		cout << "2) Show in format \"Date - Next Date\"" << endl;
		cout << "3) Show system date and time" << endl;
		cout << "0) Exit" << endl << endl;

		cout << "Insert key->"; cin >> key;

		switch (key)
		{
		case 1: {

			list.listPrint();

			break;
		}
		
		case 2: {

			list.listPrintSort();

			break;
		}

		case 3: {
			datetime sysTime;
			sysTime.showSysDate();
			break;
		}

		default:

			if (key != 0) cout << "Error! Not found in menu!" << endl;

			break;
		}

	} while (key != 0);

}

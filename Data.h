#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

class Data{
public:
    int second, minute, hour, day, month, year;
};

class datetime{

private:

    Data data;

public:

    datetime() {
        data.second = 0;
        data.minute = 0;
        data.hour = 0;
        data.day = 1;
        data.month = 1;
        data.year = 1970;
    }

    ~datetime() {};


    void showInfo();
    void addData(Data new_data);
    void showSysDate();
};

class Node{
public:
    Node* prev;
    Node* next;
    datetime* data;
    void objPush(Data new_data);
    void deleteData();
};

class List{
public:

    Node* first;
    Node* last;
    Node* C;

    List(){
        first = NULL;
        last = NULL;
        C = NULL;
    };

    ~List() {
    
        deleteAll();

    };

    void getListFromFile(char*);
    void addNode(Data new_data);
    void printNode();
    void moveNext();
    void movePrev();
    void deleteAll();
    void clearC();
    void listPrint();
    void listPrintSort();
    void deleteCurrent();

};

class fileWork {

public:

    void getData(char*, int&, Data*&);
    void countData(char*, int&);

};

int checkData(int, int);
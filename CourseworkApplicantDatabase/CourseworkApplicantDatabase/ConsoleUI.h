#ifndef CONSOLE_UI
#define CONSOLE_UI

#include<iostream>
#include "ApplicantMenegment.h"



class ConsoleUI {
private:
    static void showMenu();
    static void handleAdd(ApplicantMenegment& manager);
    static void handleRemove(ApplicantMenegment& manager);
    static void handleSort(ApplicantMenegment& mamager);
    static void handleList(ApplicantMenegment& manager);
public:
    static void run(ApplicantMenegment& manager);
};


#endif 
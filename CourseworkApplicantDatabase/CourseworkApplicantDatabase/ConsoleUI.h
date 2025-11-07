#pragma once

#include<iostream>

#include "ApplicantMenegment.h"

class ConsoleUI final{
public:
    static void run(ApplicantManager& manager);

    static void showSpecialties(bool withAll);

private:
    static void showMenu();
    static void handleAdd(ApplicantManager& manager);
    static void handleRemove(ApplicantManager& manager);
    static void handleSort(ApplicantManager& mamager);
    static void handleList(ApplicantManager& manager);
    static void handleReport(ApplicantManager& manager);
};
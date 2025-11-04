#include "ConsoleUI.h"
#include "InputReader.h"

#include<iostream>



void ConsoleUI::run(ApplicantMenegment& manager) {
	int choice;
	do {
		showMenu();
		choice = InputReader::readInt("Enter choice");
		switch (choice)
		{
        case 1:
            handleAdd(manager);
            break;
        case 2:
            handleRemove(manager);
            break;
        case 3:
            handleSort(manager);
            break;
        case 4:
            handleList(manager);
            break;
        case 0:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
		}
        std::cout << std::endl;
    } while (choice != 0);
}

void ConsoleUI::showMenu() {
    std::cout << "==============================\n";
    std::cout << "      Applicant Manager\n";
    std::cout << "==============================\n";
    std::cout << "1. Add applicant\n";
    std::cout << "2. Remove applicant\n";
    std::cout << "3. Sort applicants\n";
    std::cout << "4. Show all applicants\n";
    std::cout << "0. Exit\n";
    std::cout << "==============================\n";
}

void ConsoleUI::handleAdd(ApplicantMenegment& manager) {
    std::cout << "\n=== Add Applicant ===\n";
    manager.addApplicantProcces();
}

void ConsoleUI::handleRemove(ApplicantMenegment& manager) {
    std::cout << "\n=== Remove Applicant ===\n";
    manager.removeApplicantProcces();
}

void ConsoleUI::handleSort(ApplicantMenegment& manager) {
    std::cout << "\n=== Sort Applicant ===\n";
    manager.sortApplicantsProcces();
}

void ConsoleUI::handleList(ApplicantMenegment& manager) {
    std::cout << "\n=== List of Applicants ===\n";
    manager.showAllApplicants();
}
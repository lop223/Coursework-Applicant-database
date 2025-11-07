#include "ConsoleUI.h"

#include<iostream>

#include "AdmissionProcessor.h"
#include "ConsolePrinter.h"
#include "InputReader.h"


void ConsoleUI::run(ApplicantManager& manager) {
	int choice = -1;
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
        case 5:
            handleReport(manager);
            break;
        case 0:
            ConsolePrinter::printInfoMessage("Exiting program...");
            break;
        default:
            ConsolePrinter::printWarningMessage("Invalid choice. Try again.");
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
    std::cout << "5. Create report\n";
    std::cout << "0. Exit\n";
    std::cout << "==============================\n";
}

void ConsoleUI::showSpecialties(bool withAll) {
    std::cout << "\nSelect specialty" << ":\n";

    for (size_t i = 0; i < ALL_SPECIALTIES.size(); ++i) {
        const auto& s = ALL_SPECIALTIES[i];
        std::cout << i + 1 << ". " << s.name << " (Min score: " << s.minScore << ")\n";
    }

    if (withAll)
        std::cout << ALL_SPECIALTIES.size() + 1 << ". All specialties\n";
}

void ConsoleUI::handleAdd(ApplicantManager& manager) {
    std::cout << "\n=== Add Applicant ===\n";
    manager.addApplicantProcces();
}

void ConsoleUI::handleRemove(ApplicantManager& manager) {
    std::cout << "\n=== Remove Applicant ===\n";
    manager.removeApplicantProcces();
}

void ConsoleUI::handleSort(ApplicantManager& manager) {
    std::cout << "\n=== Sort Applicant ===\n";
    manager.sortApplicantsProcces();
}

void ConsoleUI::handleList(ApplicantManager& manager) {
    std::cout << "\n=== List of Applicants ===\n";
    manager.showAllApplicants();
}

void ConsoleUI::handleReport(ApplicantManager& manager) {
    std::cout << "\n=== Create Report ===\n";
    showSpecialties(true);

    const int maxChoice = static_cast<int>(ALL_SPECIALTIES.size()) + 1;
    int choice = InputReader::readInt("Enter specialty number");
    while (choice < 1 || choice > maxChoice) {
        ConsolePrinter::printWarningMessage("Invalid choice. Please try again.");
        choice = InputReader::readInt("Enter specialty number");
    }

    if (choice == maxChoice) {
        for (const auto& specialty : ALL_SPECIALTIES)
            AdmissionProcessor::createReportFile(manager, specialty.type);
    }
    else {
        AdmissionProcessor::createReportFile(manager, ALL_SPECIALTIES[choice - 1].type);
    }
}
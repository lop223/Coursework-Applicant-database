#include "ApplicantMenegment.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "Applicant.h"
#include "InputReader.h"

static std::string FILE_MANE = "data/applicants.txt";

ApplicantMenegment::ApplicantMenegment() {
	loadFromFile();
}
ApplicantMenegment::~ApplicantMenegment() {
	saveToFile();
}

void ApplicantMenegment::loadFromFile()
{
    std::ifstream inputFile(FILE_MANE);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << FILE_MANE << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int id;
        std::string fullName;
        std::string passportNumber;
        bool contractBasis;
        bool originalDocuments;

        if (!(iss >> id)) {
            std::cerr << "Error reading id from line: " << line << std::endl;
            continue;
        }
        iss >> std::ws;
        // „итаЇмо fullName до коми
        if (!std::getline(iss, fullName, ',')) {
            std::cerr << "Error reading fullName from line: " << line << std::endl;
            continue;
        }
        iss >> std::ws;
        if (!(iss >> passportNumber >> contractBasis >> originalDocuments)) {
            std::cerr << "Error reading passport/flags from line: " << line << std::endl;
            continue;
        }
        applicants.push_back(Applicant(id, FullName(fullName), passportNumber, contractBasis, originalDocuments));
    }
}
void ApplicantMenegment::saveToFile() {
	std::ofstream outputFile(FILE_MANE);
	if (!outputFile.is_open()) {
		std::cerr << "Error opening file: " << FILE_MANE << std::endl;
		return;
	}
	for (const Applicant& applicant : applicants) {
		outputFile << applicant.getId() << " "
			<< applicant.getFullName().getFullName() << ", "
			<< applicant.getPassportNamber() << " "
			<< applicant.isContractBasis() << " "
			<< applicant.hasOriginalDocuments() << std::endl;
	}
}
void ApplicantMenegment::showAllApplicants() {
	for (const Applicant applicant : applicants) {
		std::cout << "ID: " << applicant.getId() << ", Full Name: " << applicant.getFullName().getFullName()
			<< ", Passport Number: " << applicant.getPassportNamber()
			<< ", Contract Basis: " << (applicant.isContractBasis() ? "Yes" : "No")
			<< ", Original Documents: " << (applicant.hasOriginalDocuments() ? "Yes" : "No") << std::endl;
	}
}
void ApplicantMenegment::addApplicant(const Applicant& applicant) {
	applicants.push_back(applicant);
}
void ApplicantMenegment::removeApplicant(int id) {
	applicants.erase(std::remove_if(applicants.begin(), applicants.end(),
		[id](const Applicant& applicant) { return applicant.getId() == id; }), applicants.end());
}
void ApplicantMenegment::removeApplicant(FullName name) {
	applicants.erase(std::remove_if(applicants.begin(), applicants.end(),
		[name](const Applicant& applicant) { return applicant.getFullName().getFullName() == name.getFullName(); }), applicants.end());
}
void ApplicantMenegment::addApplicantProcces() {
	int id = InputReader::readInt("Enter ID: ");
	std::string fullName = InputReader::readString("Enter Full Name: ");
	std::string passportNumber = InputReader::readString("Enter Passport Number: ");
	bool contractBasis = InputReader::readBool("Is Contract Basis (1 for Yes, 0 for No): ");
	bool originalDocuments = InputReader::readBool("Has Original Documents (1 for Yes, 0 for No): ");

	Applicant newApplicant(id, FullName(fullName), passportNumber, contractBasis, originalDocuments);
	addApplicant(newApplicant);
}
void ApplicantMenegment::removeApplicantProcces() {
    int choice = InputReader::readInt("Remove by: 1. ID\n2. Full Name\nEnter choice: ");
    if (choice == 1) {
        int id = InputReader::readInt("Enter ID: ");
        removeApplicant(id);
    }
    else if (choice == 2) {
        std::string fullName = InputReader::readString("Enter Full Name: ");
        removeApplicant(FullName(fullName));
    }
    else {
        std::cout << "Invalid choice.\n";
    }
}
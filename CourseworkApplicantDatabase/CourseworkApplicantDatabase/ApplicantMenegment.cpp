#include "ApplicantMenegment.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "Applicant.h"
#include "InputReader.h"
#include "TestScore.h"
#include <set>
#include <algorithm>

static std::string FILE_MANE = "data/applicants.txt";
static const std::set<std::string> validSubjects = { "Physics", "English", "Biology", "Geography" };

ApplicantMenegment::ApplicantMenegment() {
	loadFromFile();
}
ApplicantMenegment::~ApplicantMenegment() {
	saveToFile();
}

bool ApplicantMenegment::parseApplicantLine(const std::string& line, Applicant& applicant) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;

    while (std::getline(iss, token, ';')) {
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");
        if (start == std::string::npos)
            parts.push_back("");
        else
            parts.push_back(token.substr(start, end - start + 1));
    }

    if (parts.size() < 10) {
        std::cerr << "Invalid CSV line (expected 10 fields): " << line << std::endl;
        return false;
    }

    try {
        int id = std::stoi(parts[0]);
        std::string fullName = parts[1];
        std::string passportNumber = parts[2];
        bool contractBasis = (std::stoi(parts[3]) != 0);
        bool originalDocuments = (std::stoi(parts[4]) != 0);
        std::string extraSubject = parts[5];
        float mathScore = std::stof(parts[6]);
        float historyScore = std::stof(parts[7]);
        float ukrainianLanguageScore = std::stof(parts[8]);
        float extraSubjectScore = std::stof(parts[9]);

        applicant = Applicant(
            id,
            FullName(fullName),
            passportNumber,
            contractBasis,
            originalDocuments,
            TestScore(mathScore, historyScore, ukrainianLanguageScore, extraSubject, extraSubjectScore)
        );

        if (parts.size() >= 11) {
            std::string specialtiesStr = parts[10];
            specialtiesStr.erase(0, specialtiesStr.find_first_not_of(" \t\""));
            specialtiesStr.erase(specialtiesStr.find_last_not_of(" \t\"") + 1);

            if (!specialtiesStr.empty()) {
                std::stringstream specStream(specialtiesStr);
                std::string specPair;

                while (std::getline(specStream, specPair, ',')) {
                    size_t colonPos = specPair.find(':');
                    if (colonPos != std::string::npos) {
                        std::string name = specPair.substr(0, colonPos);
                        std::string status = specPair.substr(colonPos + 1);
                        SpecialtyApplication s(SpecialtyApplication::getSpecialtyTypeByName(name), status == "submitted");
                        applicant.addSpecialty(s);
                    }
                }
            }
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing line: " << line << " (" << e.what() << ")" << std::endl;
        return false;
    }
}

void ApplicantMenegment::loadFromFile()
{
    std::ifstream inputFile(FILE_MANE);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << FILE_MANE << std::endl;
        return;
    }

	applicants.clear();
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        Applicant applicant;
        if (parseApplicantLine(line, applicant)) {
            applicants.push_back(applicant);
        }
    }
}

void ApplicantMenegment::saveToFile() {
    std::ofstream outputFile(FILE_MANE);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << FILE_MANE << std::endl;
        return;
    }

    for (const Applicant& applicant : applicants) {
        std::ostringstream specStream;
        const auto& specialties = applicant.getSpecialties();
        for (size_t i = 0; i < specialties.size(); ++i) {
            specStream << SpecialtyApplication::getSpecialtyName(specialties[i])
                << ":"
                << (specialties[i].isSubmitted() ? "submitted" : "not_submitted");
            if (i < specialties.size() - 1) specStream << ",";
        }

        outputFile
            << applicant.getId() << ";"
            << applicant.getFullName().getFullName() << ";"
            << applicant.getPassportNamber() << ";"
            << (applicant.isContractBasis() ? 1 : 0) << ";"
            << (applicant.hasOriginalDocuments() ? 1 : 0) << ";"
            << applicant.getTestScore().getExtraSubject() << ";"
            << applicant.getTestScore().getMathScore() << ";"
            << applicant.getTestScore().getHistoryScore() << ";"
            << applicant.getTestScore().getUkrainianLanguageScore() << ";"
            << applicant.getTestScore().getExtraSubjectScore() << ";"
            << "\"" << specStream.str() << "\""
            << "\n";
    }
    outputFile.close();
}

void ApplicantMenegment::showAllApplicants() {
	for (const Applicant applicant : applicants) {
		std::cout << applicant << std::endl;
	}
}

void ApplicantMenegment::sortById() {
    std::ranges::sort(applicants, {}, &Applicant::getId);
}

void ApplicantMenegment::sortByName() {
    std::ranges::sort(applicants, {}, [](const Applicant& a) { return a.getFullName().getFirstName(); });
}

void ApplicantMenegment::sortByTotalScore() {
    std::ranges::sort(applicants, {}, &Applicant::getTotalScore);
}

void ApplicantMenegment::addApplicant(Applicant applicant) {
    applicants.push_back(std::move(applicant));
}

bool ApplicantMenegment::removeApplicant(int id) {
    auto before = applicants.size();
    applicants.erase(std::remove_if(applicants.begin(), applicants.end(),
        [id](const Applicant& a) { return a.getId() == id; }), applicants.end());
    return applicants.size() < before;
}

bool ApplicantMenegment::removeApplicant(FullName name) {
    auto before = applicants.size();
    applicants.erase(std::remove_if(applicants.begin(), applicants.end(),
        [name](const Applicant& a) { return a.getFullName().getFullName() == name.getFullName(); }), applicants.end());
    return applicants.size() < before;
}

Applicant* ApplicantMenegment::findApplicantById(int id) {
    auto it = std::find_if(applicants.begin(), applicants.end(),
        [id](const Applicant& a) { return a.getId() == id; });

    return (it != applicants.end()) ? &(*it) : nullptr;
}

void ApplicantMenegment::addApplicantProcces() {
	std::cout << "Add applicant: \n";
	int id;
    while (true) {
        id = InputReader::readInt("Enter ID");
		if (findApplicantById(id)) {
			InputReader::printErrorMessage("Applicant with this ID already exists. Please enter a different ID.\n");	
		}
		else
		{
			break;
		}
    }
	std::string fullName = InputReader::readFullName("Enter Full Name");
	std::string passportNumber = InputReader::readPassportNumber("Enter Passport Number");
	bool contractBasis = InputReader::readBool("Is Contract Basis (1 for Yes, 0 for No)");
	bool originalDocuments = InputReader::readBool("Has Original Documents (1 for Yes, 0 for No)");
    std::string extraSubject;
	float mathScore = InputReader::readScore("Enter Math Score");
	float historyScore = InputReader::readScore("Enter History Score");
	float ukrainianLanguageScore = InputReader::readScore("Enter Ukrainian Language Score");
    while (true) {
        extraSubject = InputReader::readString("Enter Extra Subject (Physics, English, Biology, Geography)");
        if ( validSubjects.count(extraSubject)) {
            break;
        }
        else
        {
            std::cout << "Invalid subject. Please enter one of the following: Physics, English, Biology, Geography.\n";
        }
    }
	float extraSubjectScore = InputReader::readScore("Enter " + extraSubject + " Score");

	Applicant applicant(id, FullName(fullName), passportNumber, contractBasis, originalDocuments,
        TestScore(mathScore, historyScore, ukrainianLanguageScore, extraSubject, extraSubjectScore));

    std::vector<SpecialtyApplication> specialties;
    int count = InputReader::readInt("Enter number of specialties");
    for (int i = 0; i < count; ++i) {
        std::cout << "\nSelect specialty #" << (i + 1) << ":\n";
        for (size_t j = 0; j < ALL_SPECIALTIES.size(); ++j) {
            const auto& s = ALL_SPECIALTIES[j];
            std::cout << j + 1 << ". " << s.name << " (Min score: " << s.minScore << ")\n";
        }

        int choice;
        do {
            choice = InputReader::readInt("Enter specialty number: ");
            if (choice < 1 || choice > static_cast<int>(ALL_SPECIALTIES.size())) {
                std::cout << "Invalid choice, please try again.\n";
            }
        } while (choice < 1 || choice > static_cast<int>(ALL_SPECIALTIES.size()));

        bool submitted = InputReader::readBool("Documents submitted for this specialty (1 = Yes, 0 = No): ");
        SpecialtyType selectedType = ALL_SPECIALTIES[choice - 1].type;

        specialties.emplace_back(selectedType, submitted);
    }

    for (auto& s : specialties)
        applicant.addSpecialty(s);

	addApplicant(applicant);
    saveToFile();

	InputReader::printSuccessMessage("Applicant [ " + fullName + " " + std::to_string(id) + " ] added successfully.\n");
}

void ApplicantMenegment::removeApplicantProcces() {
    int choice = InputReader::readInt("Remove by: 1. ID\n2. Full Name\nEnter choice");
    auto printResult = [](bool success) {
        success
            ? InputReader::printSuccessMessage("Applicant removed successfully.\n")
            : InputReader::printErrorMessage("No applicant found.\n");
        };
    if (choice == 1) {
        int id = InputReader::readInt("Enter ID");
        removeApplicant(id);
        printResult(removeApplicant(id));
    }
    else if (choice == 2) {
        std::string fullName = InputReader::readString("Enter Full Name");
        removeApplicant(FullName(fullName));
        printResult(removeApplicant(fullName));
    }
    else {
        std::cout << "Invalid choice.\n";
    }
}

void ApplicantMenegment::sortApplicantsProcces() {
    int choice = InputReader::readInt("Sort by:\n1. ID\n2. Full Name\n3. Total Score\nEnter choice");
    std::cout << "sorting by ";
    switch (choice)
    {
    case 1:
        sortById();
        std::cout << "Id...";
        break;
    case 2:
        sortByName();
        std::cout << "Name...";
        break;
    case 3:
        sortByTotalScore();
        std::cout << "Total Score...";
        break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }
}
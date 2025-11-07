#ifndef APPLICANT_H
#define APPLICANT_H

#include<iostream>
#include "FullName.h"
#include "TestScore.h"
#include "SpecialtyApplication.h"
#include <vector>

class Applicant 
{
private:
	int id;
	FullName fullName;
	std::string passportNumber;
	bool contractBasis;
	bool originalDocuments;
	TestScore testScore;
	std::vector<SpecialtyApplication> specialties;

	std::string listSpecialties() const;
public:
	Applicant();
	Applicant(int id, FullName fullName, std::string passportNamber, bool contractBasis, bool originalDocuments, TestScore testScore);
	Applicant(const Applicant& other);
	Applicant(Applicant&& other);
	Applicant& operator=(const Applicant& other) = default;
	Applicant& operator=(Applicant&& other) = default;
	~Applicant();

	friend std::ostream& operator<<(std::ostream& os, const Applicant& applicant) {
		os << "ID: " << applicant.getId()
			<< ", Full Name: " << applicant.getFullName().getFullName()
			<< ", Passport Number: " << applicant.getPassportNamber()
			<< ", Contract Basis: " << (applicant.isContractBasis() ? "Yes" : "No")
			<< ", Original Documents: " << (applicant.hasOriginalDocuments() ? "Yes" : "No")
			<< ", Test Scores: [Math: " << applicant.getTestScore().getMathScore()
			<< ", History: " << applicant.getTestScore().getHistoryScore()
			<< ", Ukrainian Language: " << applicant.getTestScore().getUkrainianLanguageScore()
			<< ", " << applicant.getTestScore().getExtraSubject() << ": " << applicant.getTestScore().getExtraSubjectScore()
			<< "], Total Score: " << applicant.getTotalScore()
			<< "\n" <<applicant.listSpecialties();
		return os;
	}

	int getId() const { return id; }
	const FullName& getFullName() const { return fullName; }
	std::string getPassportNamber() const { return passportNumber; }
	bool isContractBasis() const { return contractBasis; }
	bool hasOriginalDocuments() const { return originalDocuments; }
	const TestScore& getTestScore() const { return testScore; }
	const float getTotalScore() const { return testScore.getTotalScore(); }
	const std::vector<SpecialtyApplication>& getSpecialties() const { return specialties; }

	void addSpecialty(const SpecialtyApplication& specialty);
};

#endif
#pragma once

#include<iostream>
#include<vector>

#include "Applicant.h"

class ApplicantManager {
public:
	ApplicantManager();
	~ApplicantManager();

	void addApplicantProcces();
	void removeApplicantProcces();
	void sortApplicantsProcces();
	void showAllApplicants();

	Applicant* findApplicantByFullName(const std::string& fullName);
	Applicant* findApplicantById(int id);
	Applicant* findApplicantByPassport(const std::string& passportNamber);

	const std::vector<Applicant>& getApplicants() const { return applicants; }

private:
	std::vector<Applicant> applicants;

	void loadFromFile();
	void saveToFile();

	void addApplicant(Applicant applicant);
	bool removeApplicant(int id);
	bool removeApplicant(FullName name);
	void sortById();
	void sortByName();
	void sortByTotalScore();

	bool parseApplicantLine(const std::string& line, Applicant& applicant);
};
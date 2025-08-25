#ifndef APPLICANT_MENEGMENT
#define APPLICANT_MENEGMENT

#include<iostream>
#include<vector>

#include "Applicant.h"

class ApplicantMenegment
{
private:
	std::vector<Applicant> applicants;

	void loadFromFile();
	void saveToFile();
	void addApplicant(const Applicant& applicant);
	void removeApplicant(int id);
	void removeApplicant(FullName name);
public:
	ApplicantMenegment();
	~ApplicantMenegment();

	Applicant* findApplicantById(int id);
	Applicant* findApplicantByPassport(const std::string& passportNamber);
	Applicant* findApplicantByFullName(const std::string& fullName);
	void showAllApplicants();
	void addApplicantProcces();
	void removeApplicantProcces();
};

#endif 


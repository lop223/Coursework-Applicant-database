#ifndef APPLICANT_H
#define APPLICANT_H

#include<iostream>
#include "FullName.h"

class Applicant 
{
private:
	int id;
	FullName fullName;
	std::string passportNamber;
	bool contractBasis;
	bool originalDocuments;
public:
	Applicant(int id, FullName fullName, std::string passportNamber, bool contractBasis, bool originalDocuments);
	Applicant(const Applicant& other);
	Applicant(Applicant&& other);
	Applicant& operator=(const Applicant& other) = default;
	Applicant& operator=(Applicant&& other) = default;
	~Applicant();


	int getId() const { return id; }
	const FullName& getFullName() const { return fullName; }
	std::string getPassportNamber() const { return passportNamber; }
	bool isContractBasis() const { return contractBasis; }
	bool hasOriginalDocuments() const { return originalDocuments; }
};

#endif
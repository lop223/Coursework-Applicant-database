#include "Applicant.h"

#include<iostream>

#include "FullName.h"

Applicant::Applicant(int id, FullName fullName, std::string passportNamber, bool contractBasis, bool originalDocuments) :
	id(id), fullName(fullName), passportNamber(passportNamber), contractBasis(contractBasis), originalDocuments(originalDocuments)
{}
Applicant::Applicant(const Applicant& other) :
	id(other.id), fullName(other.fullName), passportNamber(other.passportNamber), contractBasis(other.contractBasis), originalDocuments(other.originalDocuments)
{}
Applicant::Applicant(Applicant&& other) :
	id(other.id), fullName(std::move(other.fullName)), passportNamber(std::move(other.passportNamber)), contractBasis(other.contractBasis), originalDocuments(other.originalDocuments)
{}
Applicant::~Applicant() {}
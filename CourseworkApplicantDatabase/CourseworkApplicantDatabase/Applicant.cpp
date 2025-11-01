#include "Applicant.h"

#include<iostream>

#include "FullName.h"
#include "TestScore.h"

Applicant::Applicant()
    : id(0),
    fullName(""),
    passportNumber(""),
    contractBasis(false),
    originalDocuments(false),
    testScore()
{}
Applicant::Applicant(int id, FullName fullName, std::string passportNamber, bool contractBasis, bool originalDocuments, TestScore testScore) :
	id(id), fullName(fullName), passportNumber(passportNamber), contractBasis(contractBasis), originalDocuments(originalDocuments), testScore(testScore)
{}
Applicant::Applicant(const Applicant& other) :
	id(other.id), fullName(other.fullName), passportNumber(other.passportNumber), contractBasis(other.contractBasis), originalDocuments(other.originalDocuments), testScore(other.testScore)
{}
Applicant::Applicant(Applicant&& other) :
	id(other.id), fullName(std::move(other.fullName)), passportNumber(std::move(other.passportNumber)), contractBasis(other.contractBasis), originalDocuments(other.originalDocuments), testScore(std::move(other.testScore))
{}
Applicant::~Applicant() {}
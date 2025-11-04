#include "Applicant.h"

#include<iostream>
#include <sstream>

#include "FullName.h"
#include "TestScore.h"
#include <algorithm>

Applicant::Applicant()
    : id(0),
    fullName(""),
    passportNumber(""),
    contractBasis(false),
    originalDocuments(false),
    testScore()
{}
Applicant::Applicant(int id, FullName fullName, std::string passportNamber, bool contractBasis, bool originalDocuments, TestScore testScore) :
	id(id), 
    fullName(fullName),
    passportNumber(passportNamber),
    contractBasis(contractBasis),
    originalDocuments(originalDocuments),
    testScore(testScore)
{}
Applicant::Applicant(const Applicant& other) :
	id(other.id), 
    fullName(other.fullName), 
    passportNumber(other.passportNumber), 
    contractBasis(other.contractBasis),
    originalDocuments(other.originalDocuments), 
    testScore(other.testScore),
    specialties(other.specialties)
{}
Applicant::Applicant(Applicant&& other) :
	id(other.id),
    fullName(std::move(other.fullName)),
    passportNumber(std::move(other.passportNumber)),
    contractBasis(other.contractBasis), 
    originalDocuments(other.originalDocuments),
    testScore(std::move(other.testScore)),
    specialties(std::move(other.specialties))
{}

void Applicant::addSpecialty(const SpecialtyApplication& specialty) {
    if (std::none_of(specialties.begin(), specialties.end(),
        [&specialty](const SpecialtyApplication& s) {
            return s.getType() == specialty.getType();
        }))
    {
        specialties.push_back(specialty);
    }
}

std::string Applicant::listSpecialties() const {
    std::ostringstream oss;
    if (specialties.empty()) {
        oss << "No specialties applied for.\n";
    }
    else {
        oss << "Specialties applied for:\n";
        for (const auto& s : specialties) {
            oss << " - " << SpecialtyApplication::getSpecialtyName(s.getType());
            if (s.isSubmitted()) oss << " (submitted)";
            oss << "\n";
        }
    }
    return oss.str();
}

Applicant::~Applicant() {}
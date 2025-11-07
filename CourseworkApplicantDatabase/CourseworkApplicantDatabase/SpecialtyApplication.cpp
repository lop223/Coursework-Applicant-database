#include "SpecialtyApplication.h"

#include<iostream>

SpecialtyApplication::SpecialtyApplication()
	: SpecialtyApplication::SpecialtyApplication(SpecialtyType::ProfessionalEducation, false)
{
};
SpecialtyApplication::SpecialtyApplication(SpecialtyType type, bool submited)
	: type(type), submited(submited)
{
};
SpecialtyApplication::SpecialtyApplication(SpecialtyType type)
	: SpecialtyApplication(type, false)
{
};

SpecialtyApplication::~SpecialtyApplication()
{
};

void SpecialtyApplication::setSubmited(bool value) {
	submited = value;
}

std::string SpecialtyApplication::getSpecialtyName(const SpecialtyType& type) {
	auto it = std::find_if(
		ALL_SPECIALTIES.begin(),
		ALL_SPECIALTIES.end(),
		[type](const Specialty& s) { return s.type == type; }
	);
	return (it != ALL_SPECIALTIES.end()) ? it->name : "Unknown";
}

int SpecialtyApplication::getSpecialtyQuota(SpecialtyType type) {
	auto it = std::find_if(
		ALL_SPECIALTIES.begin(),
		ALL_SPECIALTIES.end(),
		[type](const Specialty& s) { return s.type == type; }
	);
	return (it != ALL_SPECIALTIES.end()) ? it->quota : 0;
}

int SpecialtyApplication::getSpecialtyMinScore(SpecialtyType type) {
	auto it = std::find_if(
		ALL_SPECIALTIES.begin(),
		ALL_SPECIALTIES.end(),
		[type](const Specialty& s) { return s.type == type; }
	);
	return (it != ALL_SPECIALTIES.end()) ? it->minScore : 0;
}

SpecialtyType SpecialtyApplication::getSpecialtyTypeByName(const std::string& name) {
	auto it = std::find_if(
		ALL_SPECIALTIES.begin(),
		ALL_SPECIALTIES.end(),
		[name](const Specialty& s) { return s.name == name; }
	);
	return (it != ALL_SPECIALTIES.end()) ? it->type : SpecialtyType::ProfessionalEducation;
}
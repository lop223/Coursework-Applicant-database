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

std::string SpecialtyApplication::getSpecialtyName(const SpecialtyApplication& specialty) {
	auto it = std::find_if(
		ALL_SPECIALTIES.begin(),
		ALL_SPECIALTIES.end(),
		[&specialty](const Specialty& s) { return s.type == specialty.getType(); }
	);
	return (it != ALL_SPECIALTIES.end()) ? it->name : "Unknown";
}

SpecialtyType SpecialtyApplication::getSpecialtyTypeByName(const std::string& name) {
	auto it = std::find_if(
		ALL_SPECIALTIES.begin(),
		ALL_SPECIALTIES.end(),
		[name](const Specialty& s) { return s.name == name; }
	);
	return (it != ALL_SPECIALTIES.end()) ? it->type : SpecialtyType::ProfessionalEducation;
}
#include "FullName.h"

#include<iostream>
#include<sstream>

FullName::FullName(std::string firstName, std::string lastName) :
	firstName(firstName), lastName(lastName)
{}
FullName::FullName(std::string fullName) {
	std::istringstream iss(fullName);
	iss >> firstName >> lastName;
}
FullName::FullName(const FullName& other) :
	firstName(other.firstName), lastName(other.lastName)
{}
FullName::FullName(FullName&& other) :
	firstName(std::move(other.firstName)), lastName(std::move(other.lastName))
{}
FullName::~FullName() {}
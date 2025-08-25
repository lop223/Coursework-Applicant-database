#ifndef FULLNAME_H
#define FULLNAME_H

#include<iostream>

class FullName {
private:
	std::string firstName;
	std::string lastName;
public:
	FullName(std::string firstName, std::string lastName);
	FullName(std::string FullName);
	FullName(const FullName& other);
	FullName(FullName&& other);
	FullName& operator=(const FullName& other) = default;
	FullName& operator=(FullName&& other) = default;
	~FullName();
	std::string getFirstName() const { return firstName; }
	std::string getLastName() const { return lastName; }
	std::string getFullName() const { return firstName + " " + lastName; }
};

#endif 


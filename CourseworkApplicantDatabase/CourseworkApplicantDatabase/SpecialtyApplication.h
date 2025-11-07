#ifndef SPECIALTY_APPLICATION
#define SPECIALTY_APPLICATION

#include<iostream>
#include <vector>

enum class SpecialtyType {
	SoftwareEngineering,
	ComputerScience,
	ComputerEngineering,
	Cybersecurity,
	TheoreticalPhysics,
	AppliedPhysicsAndNanomaterials,
	InformationAndMeasurementTechnologies,
	ProfessionalEducation
};

struct Specialty {
	SpecialtyType type;
	std::string name;
	int quota;
	float minScore;

	Specialty(SpecialtyType t, std::string n, int q, float min)
		: type(t), name(std::move(n)), quota(q), minScore(min) {
	}
};

inline const std::vector<Specialty> ALL_SPECIALTIES = {
	{SpecialtyType::SoftwareEngineering, "Software Engineering", 25, 175},
	{SpecialtyType::ComputerScience, "Computer Science", 20, 165},
	{SpecialtyType::ComputerEngineering, "Computer Engineering", 15, 165},
	{SpecialtyType::Cybersecurity, "Cybersecurity", 15, 160},
	{SpecialtyType::TheoreticalPhysics, "Theoretical Physics", 25, 150},
	{SpecialtyType::AppliedPhysicsAndNanomaterials, "Applied Physics and Nanomaterials", 15, 160},
	{SpecialtyType::InformationAndMeasurementTechnologies, "Information and Measurement Technologies", 15, 160},
	{SpecialtyType::ProfessionalEducation, "Professional Education", 25, 150},
};

class SpecialtyApplication {
private:
	SpecialtyType type;
	bool submited;
public:
	SpecialtyApplication();
	SpecialtyApplication(SpecialtyType type, bool submited);
	SpecialtyApplication(SpecialtyType type);
	~SpecialtyApplication();

	const SpecialtyType& getType() const { return type; };
	bool isSubmitted() const { return submited; };

	static std::string getSpecialtyName(const SpecialtyType& type);

	static int getSpecialtyQuota(SpecialtyType type);

	static int getSpecialtyMinScore(SpecialtyType type);

	static SpecialtyType getSpecialtyTypeByName(const std::string& name);
	
	void setSubmited(bool value);
	friend std::ostream& operator<<(std::ostream& os, const SpecialtyApplication& specialty) {
		os
			<< "Name: " << getSpecialtyName(specialty.getType())
			<< "Submited: " << specialty.isSubmitted()
			<< "\n";
		return os;
	}
};


#endif
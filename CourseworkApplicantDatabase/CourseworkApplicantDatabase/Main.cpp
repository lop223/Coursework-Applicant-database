//! CourseworkApplicantDatabase - The project was created for a coursework on the topic "Enrollment Database Management System". 
//! C++

#include <iostream>
#include <vector>

#include "Applicant.h"
#include "ApplicantMenegment.h"
#include "ConsoleUI.h"

int main()
{
    system("chcp 1251>nul");

	ApplicantMenegment applicantMenegment;
	ConsoleUI::run(applicantMenegment);
	return 0;
}

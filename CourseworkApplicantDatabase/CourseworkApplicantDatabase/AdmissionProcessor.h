#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <string>

#include "Applicant.h"
#include "ApplicantMenegment.h"



class AdmissionProcessor final {
public:
	using Predicate = std::function<bool(const Applicant&, const SpecialtyApplication&)>;

	static void createReportFile(const ApplicantManager& manager, SpecialtyType type);
private:

	static std::vector<Applicant> selectTopApplicantsByScore(
		const std::vector<Applicant>& applicants,
		SpecialtyType type);

	static std::vector<Applicant> selectMarginalApplicants(
		const std::vector<Applicant>& applicants,
		SpecialtyType type);

	static std::string generateReport(
		const ApplicantManager& manager,
		SpecialtyType type);

    template <typename Predicate>
    static std::vector<Applicant> filterApplicants(
        const std::vector<Applicant>& applicants,
        SpecialtyType type,
        Predicate predicate)
    {
        std::vector<Applicant> eligible;
        eligible.reserve(applicants.size());

        std::copy_if(applicants.begin(), applicants.end(), std::back_inserter(eligible),
            [&](const Applicant& a) {
                return std::any_of(a.getSpecialties().begin(), a.getSpecialties().end(),
                    [&](const SpecialtyApplication& s) {
                        return s.getType() == type && s.isSubmitted() && predicate(a, s);
                    });
            });

        return eligible;
    }
};

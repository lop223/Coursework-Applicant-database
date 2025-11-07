#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "Applicant.h"



class ReportBuilder {
public:
    explicit ReportBuilder(SpecialtyType type);

    ReportBuilder& addHeader(const std::string& title);
    ReportBuilder& addApplicantTable(const std::vector<Applicant>& applicants, const std::string& sectionName);
    ReportBuilder& addSummary(size_t totalApplicants, size_t bestCount);

    std::string build() const;

private:
    std::ostringstream out;
    SpecialtyType type;
    static constexpr int TABLE_WIDTH = 81;

    void writeTableHeader();
    void writeApplicantRow(const Applicant& a);
};

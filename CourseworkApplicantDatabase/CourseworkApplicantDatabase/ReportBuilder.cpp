#include "ReportBuilder.h"


#include <sstream>
#include <iomanip>
#include "SpecialtyApplication.h"

ReportBuilder::ReportBuilder(SpecialtyType type) : type(type) {}

ReportBuilder& ReportBuilder::addHeader(const std::string& title) {
    out << "===== " << title << " (" << SpecialtyApplication::getSpecialtyName(type) << ") =====\n\n";
    return *this;
}

void ReportBuilder::writeTableHeader() {
    out << std::left
        << std::setw(5) << "ID"
        << std::setw(25) << "Full Name"
        << std::setw(15) << "Passport"
        << std::setw(10) << "Contract"
        << std::setw(15) << "Original-Docs"
        << std::setw(15) << "Total-Score"
        << "\n";
    out << std::string(TABLE_WIDTH, '-') << "\n";
}

void ReportBuilder::writeApplicantRow(const Applicant& a) {
    out << std::left
        << std::setw(5) << a.getId()
        << std::setw(25) << a.getFullName().getFullName()
        << std::setw(15) << a.getPassportNamber()
        << std::setw(10) << (a.isContractBasis() ? "Yes" : "No")
        << std::setw(15) << (a.hasOriginalDocuments() ? "Yes" : "No")
        << std::setw(15) << std::fixed << std::setprecision(1) << a.getTotalScore()
        << "\n";
}

ReportBuilder& ReportBuilder::addApplicantTable(const std::vector<Applicant>& applicants, const std::string& sectionName) {
    out << "\n===== " << sectionName << " =====\n\n";
    writeTableHeader();
    for (const auto& a : applicants)
        writeApplicantRow(a);
    out << std::string(TABLE_WIDTH, '-') << "\n";
    return *this;
}

ReportBuilder& ReportBuilder::addSummary(size_t totalApplicants, size_t bestCount) {
    out << "\nTotal applicants: " << totalApplicants << "\n";
    out << "Quota: " << SpecialtyApplication::getSpecialtyQuota(type) << "\n";
    out << "Applicants admitted: " << bestCount << "\n";
    out << "Cut-off score: " << SpecialtyApplication::getSpecialtyMinScore(type) << "\n";
    out << "\nGenerated on: " << __DATE__ << " " << __TIME__ << "\n";
    return *this;
}

std::string ReportBuilder::build() const {
    return out.str();
}

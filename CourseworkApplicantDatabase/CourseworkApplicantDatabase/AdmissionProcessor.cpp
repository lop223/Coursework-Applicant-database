#include "AdmissionProcessor.h"

#include "ConsolePrinter.h"
#include "FileUtils.h"
#include "ReportBuilder.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#define NOMINMAX
#include <windows.h>
#include <commdlg.h>

void AdmissionProcessor::createReportFile(const ApplicantManager& manager, SpecialtyType type) {
    std::string defaultName = "Report - " + SpecialtyApplication::getSpecialtyName(type) + ".txt";
    std::string path = FileUtils::saveFileDialog(defaultName);

    if (path.empty()) {
        ConsolePrinter::printWarningMessage("Saving canceled by user.");
        return;
    }

    if (!FileUtils::writeToFile(path, generateReport(manager, type))) {
        ConsolePrinter::printErrorMessage("Error saving file: " + path);
        return;
    }

    ConsolePrinter::printSuccessMessage("Report successfully saved to: " + path);
}

std::vector<Applicant> AdmissionProcessor::selectTopApplicantsByScore(
    const std::vector<Applicant>& applicants,
    SpecialtyType type) {
    auto eligible = filterApplicants(applicants, type, [&](const Applicant& a, const SpecialtyApplication&) {
        return a.getTotalScore() >= SpecialtyApplication::getSpecialtyMinScore(type);
        });

    const int quota = SpecialtyApplication::getSpecialtyQuota(type);
    if (eligible.size() > static_cast<size_t>(quota))
        eligible.resize(quota);

    std::ranges::sort(eligible, std::greater{}, &Applicant::getTotalScore);
    return eligible;
}

std::vector<Applicant> AdmissionProcessor::selectMarginalApplicants(
    const std::vector<Applicant>& applicants,
    SpecialtyType type) {
    auto eligible = filterApplicants(applicants, type, [&](const Applicant& a, const SpecialtyApplication&) {
        return a.getTotalScore() == SpecialtyApplication::getSpecialtyMinScore(type) && !a.isContractBasis();
        });

    std::ranges::sort(eligible, std::greater{}, &Applicant::getTotalScore);
    return eligible;
}

std::string AdmissionProcessor::generateReport(
    const ApplicantManager& manager,
    SpecialtyType type) {
    std::vector<Applicant> best = selectTopApplicantsByScore(manager.getApplicants(), type);
    std::vector<Applicant> marginal = selectMarginalApplicants(manager.getApplicants(), type);

    ReportBuilder builder(type);
    builder
        .addHeader("Applicant Report")
        .addApplicantTable(best, "Top Applicants");

    if (!marginal.empty())
        builder.addApplicantTable(marginal, "Marginal Applicants");

    builder.addSummary(manager.getApplicants().size(), best.size());
    return builder.build();
}

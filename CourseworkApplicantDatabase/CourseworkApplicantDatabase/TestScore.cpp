#include "TestScore.h"

#include <iostream>

TestScore::TestScore()
	: mathScore(0), historyScore(0), ukrainianLanguageScore(0), extraSubject("none"), extraSubjectScore(0)
{}

TestScore::TestScore(float mathScore, float historyScore, float ukrainianLanguageScore, std::string extraSubject, float extraSubjectScore)
	: mathScore(mathScore), historyScore(historyScore), ukrainianLanguageScore(ukrainianLanguageScore), extraSubject(extraSubject), extraSubjectScore(extraSubjectScore)
{
}
TestScore::TestScore(const TestScore& other)
	: mathScore(other.mathScore), historyScore(other.historyScore), ukrainianLanguageScore(other.ukrainianLanguageScore), extraSubject(other.extraSubject), extraSubjectScore(other.extraSubjectScore)
{
}
TestScore::TestScore(TestScore&& other)
	: mathScore(other.mathScore), historyScore(other.historyScore), ukrainianLanguageScore(other.ukrainianLanguageScore), extraSubject(std::move(other.extraSubject)), extraSubjectScore(other.extraSubjectScore)
{
}
TestScore::~TestScore()
{
}
float TestScore::getTotalScore() const
{
	return (mathScore + historyScore + ukrainianLanguageScore + extraSubjectScore) / 4;
}
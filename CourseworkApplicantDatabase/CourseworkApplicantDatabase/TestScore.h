#ifndef TEST_SCORE_H
#define TEST_SCORE_H

#include <iostream>


class TestScore
{
private:
	float mathScore;
	float historyScore;
	float ukrainianLanguageScore;
	std::string extraSubject;
	float extraSubjectScore;
public:
	TestScore();
	TestScore(float mathScore, float historyScore, float ukrainianLanguageScore, std::string extraSubject, float extraSubjectScore);
	TestScore(const TestScore& other);
	TestScore(TestScore&& other);
	TestScore& operator=(const TestScore& other) = default;
	TestScore& operator=(TestScore&& other) = default;
	~TestScore();
	float getMathScore() const { return mathScore; }
	float getHistoryScore() const { return historyScore; }
	float getUkrainianLanguageScore() const { return ukrainianLanguageScore; }
	std::string getExtraSubject() const { return extraSubject; }
	float getExtraSubjectScore() const { return extraSubjectScore; }
	float getTotalScore() const;
};

#endif
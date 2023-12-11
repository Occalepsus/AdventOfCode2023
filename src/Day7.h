#pragma once

#include "util/DayInterface.h"

#include <array>

using day_t = long long;

class Day7 : public DayInterface<day_t>
{
public:
	Day7() : DayInterface(R"(C:\Users\jujuj\Documents\Projets informatique\AdventOfCode2023\input\InputDay7.txt)") {};
	~Day7() override = default;

	day_t run() override;

private:
	enum class CardLevel {
		HighCard,
		OnePair,
		TwoPairs,
		ThreeOfAKind,
		FullHouse,
		FourOfAKind,
		FiveOfAKind,
	};

	struct Hand {
		std::array<int, 5> cards;
		std::string rawCards;
		CardLevel level{ CardLevel::HighCard };
		day_t bid;
		size_t rank;

		Hand(std::array<int, 5> const& cards, std::string const& rawCards, day_t bid, size_t rank);
		bool compareHands(Hand const& other) const;
		Hand& operator=(Hand const& other) = default;
	};

	std::vector<Hand> hands;

	day_t part1() const;
	day_t part2();
	void parseInput(std::vector<std::string> const& input);
};

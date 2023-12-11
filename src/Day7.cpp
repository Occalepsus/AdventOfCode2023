#include "Day7.h"

#include <algorithm>

day_t Day7::run() {
	auto input = readInputFromFile(getDayInputPath());
	parseInput(input);

	return part1();
}

day_t Day7::part1() const {
	day_t res{ 0 };

	for (auto const& hand : hands) {
		std::cout << "Hand " << hand.rawCards << " is " << (int)hand.level << " and bid " << hand.rank << " * " << hand.bid << " = " << hand.bid * hand.rank << std::endl;

		res += hand.rank * hand.bid;
	}

	return res;
}

day_t Day7::part2() {
	day_t res = 0;

	return res;
}

void Day7::parseInput(std::vector<std::string> const& input) {
	for (auto const& line : input) {
		std::array<int, 5> cards{ 0 };
		for (size_t i = 0; i < 5; ++i) {
			if (line[i] >= '2' && line[i] <= '9') {
				cards[i] = line[i] - '2';
				continue;
			}
			switch (line[i])
			{
			case 'T':
				cards[i] = 8;
				break;
			case 'J':
				cards[i] = 9;
				break;
			case 'Q':
				cards[i] = 10;
				break;
			case 'K':
				cards[i] = 11;
				break;
			case 'A':
				cards[i] = 12;
				break;
			default:
				cards[i] = -1;
				break;
			}
		}

		hands.emplace_back(cards, line.substr(0, 5), std::stoi(line.substr(6, line.size() - 6)), 0);
	}
	//hands.shrink_to_fit();
	std::sort(hands.begin(), hands.end(), [](Hand const& a, Hand const& b) { return a.compareHands(b); });

	size_t i{ 0 };
	for (auto& hand : hands) {
		hand.rank = ++i;
	}
}

Day7::Hand::Hand(std::array<int, 5> const& cards, std::string const& rawCards, day_t bid, size_t rank) : 
		cards(cards), rawCards(rawCards), bid(bid), rank(rank) {

	std::array<int, 13> counts{ 0 };
	for (auto card : cards) {
		counts[card]++;
	}
	for (auto count : counts) {
		switch (count) {
		case 0:
		case 1:
			break;
		case 5:
			level = CardLevel::FiveOfAKind;
			return;
		case 4:
			level = CardLevel::FourOfAKind;
			return;
		case 3:
			if (level == CardLevel::OnePair) {
				level = CardLevel::FullHouse;
			}
			else {
				level = CardLevel::ThreeOfAKind;
			}
			break;
		case 2:
			level = (CardLevel)((int)level + 1);
			break;
		default:
			break;
		}
	}
}

bool Day7::Hand::compareHands(Hand const& other) const {
	if (level != other.level) {
		return level < other.level;
	}
	for (size_t i = 0; i < 5; i++) {
		if (cards[i] != other.cards[i]) {
			return cards[i] < other.cards[i];
		}
	}
	return true;
}

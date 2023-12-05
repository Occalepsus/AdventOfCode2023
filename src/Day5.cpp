#include "Day5.h"

#include <limits>

long long Day5::run() {
	auto input = readInputFromFile(getDayInputPath());

	parseInput(input);

	return part1(input);
}

long long Day5::part1(std::vector<std::string> const& input) const {
	// Since we want the minimum value, we start from the maximum value
	long long res{ std::numeric_limits<long long>::max() };

	for (auto seed : seeds) {
		long long value{ seed.start };
		std::cout << "Seed: " << value;
		for (auto const& map : almanac) {
			for (auto const& range : map.ranges) {
				// Checks if value is in the range
				if (value >= range.src && value < range.src + range.size) {
					value += range.dest - range.src;
					break;
				}
			}
			std::cout << " -> " << value;
		}

		if (value < res) {
			std::cout << " (new min)";
			res = value;
		}

		std::cout << "\n";
	}

	return res;
}

long long Day5::part2(std::vector<std::string> const& input) const {
	int res = 0;

	return res;
}

void Day5::parseInput(std::vector<std::string> const& input, bool part1) {
	int id{ -1 };

	for (auto const& line : input) {
		// Case empty line
		if (line.size() == 0) {
			id++;
			continue;
		}
		// Case first line with seed list
		else if (id < 0) {
			size_t pos{ 7 };
			while (pos < line.size()) {
				size_t end{ line.find(" ", pos) };
				if (end == std::string::npos) {
					end = line.size();
				}
				
				// Case of the start of the range (one out of two) or if we are in part 1
				if (part1 || id == -1) {
					seeds.emplace_back(std::stoll(line.substr(pos, end - pos)), -1);
					id = part1 ? -1 : -2;
				}
				// Case of the size of the range, transform into the end of the range (the other one)
				else {
					seeds.back().end = seeds.back().start + std::stoll(line.substr(pos, end - pos));
					id = -1;
				}
				pos = end + 1;
			}
		}
		// Case line with ranges (not the first lines with the texts)
		else if (line[0] >= '0' && line[0] <= '9') {
			size_t first{ line.find(" ") };
			size_t second{ line.find(" ", first + 1) };

			almanac[id].ranges.emplace_back(
				// Source
				std::stoll(line.substr(first + 1, second - first)),
				// Destination
				std::stoll(line.substr(0, first)),
				// Size
				std::stoll(line.substr(second, second - line.size()))
			);
		}
	}
}
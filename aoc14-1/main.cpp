#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <set>

constexpr int RACE_SECONDS_DURATION = 2503;

struct Reindeer {
  Reindeer(const std::string &name, int kms, int fly_time, int rest_time) :
    name(name), kms(kms), fly_time(fly_time), rest_time(rest_time) {}
  const std::string name;
  const int kms, fly_time, rest_time;
};

static std::vector<Reindeer> get_reindeers_data(std::istream &input);
static int calc_km_flight(const Reindeer &reindeer, int time);

int main () {
  std::istream &input = std::cin;

  auto reindeers = get_reindeers_data(input);

  int max_km = 0;
  std::string winner;
  for (const auto &reindeer : reindeers) {
    int km = calc_km_flight(reindeer, RACE_SECONDS_DURATION);
    if (km > max_km) {
      max_km = km;
      winner = reindeer.name;
    }
    std::cout << reindeer.name << " - " << km << "km\n";
  }

  std::cout << "Winner: " << winner << ", " << max_km << "km flight" << std::endl;
  return 0;
}

static std::vector<Reindeer> get_reindeers_data(std::istream &input) {
  std::regex line_regex("^([[:alpha:]]+) can fly ([[:digit:]]+) km/s for ([[:digit:]]+) seconds, but then must rest for ([[:digit:]]+) seconds.$");

  std::vector<Reindeer> reindeers;

  std::string line;
  while (std::getline(input, line)) {
    std::smatch matchs;
    if (!std::regex_match(line, matchs, line_regex)) {
      std::cerr << "Invalid line: " << line << '\n';
      continue;
    }
    reindeers.emplace_back(matchs[1], std::stoi(matchs[2]), std::stoi(matchs[3]), std::stoi(matchs[4]));
  }

  return reindeers;
}

static int calc_km_flight(const Reindeer &reindeer, int time_end) {
  int time = 0;
  int km = 0;

  while (time + reindeer.fly_time + reindeer.rest_time < time_end) {
    km += reindeer.kms * reindeer.fly_time;
    time += reindeer.fly_time + reindeer.rest_time;
  }
  km += reindeer.kms * std::min(reindeer.fly_time, time_end - time);

  return km;
}

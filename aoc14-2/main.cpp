#include <iostream>
#include <string>
#include <regex>

constexpr int RACE_SECONDS_DURATION = 2503;

class Reindeer {
public:
  Reindeer(const std::string &name, int kms, int fly_time, int rest_time);
  void inc_1sec() noexcept;
  void sum_points(int points) noexcept;
  const std::string &get_name() const noexcept {return name;}
  int get_dist_km() const noexcept {return dist_km;}
  int get_points() const noexcept {return race_points;}
private:
  const std::string name;
  const int vel_kms, fly_time, rest_time;
  int dist_km, elapsed_time, race_points;
};

static std::vector<Reindeer> get_reindeers_data(std::istream &input);

int main () {
  std::istream &input = std::cin;

  auto reindeers = get_reindeers_data(input);

  for (int i = 0; i < RACE_SECONDS_DURATION; i++) {
    int max_km = 0;
    for (auto &reindeer : reindeers) {
      reindeer.inc_1sec();
      if (reindeer.get_dist_km() > max_km)
        max_km = reindeer.get_dist_km();
    }
    for (auto &reindeer : reindeers) {
      if (reindeer.get_dist_km() >= max_km)
        reindeer.sum_points(1);
    }
  }

  std::string winner;
  int max_points = 0;
  for (auto &reindeer : reindeers) {
    if (reindeer.get_points() > max_points) {
      max_points = reindeer.get_points();
      winner = reindeer.get_name();
    }
  }

  std::cout << "Winner: " << winner << ", " << max_points << " points" << std::endl;
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

Reindeer::Reindeer(const std::string &name, int kms, int fly_time, int rest_time) :
    name(name), vel_kms(kms), fly_time(fly_time), rest_time(rest_time),
    dist_km(0), elapsed_time(0), race_points(0) {
}

void Reindeer::inc_1sec() noexcept {
  if (elapsed_time < fly_time)
    dist_km += vel_kms;
  if (++elapsed_time >= fly_time + rest_time)
    elapsed_time = 0;
}

void Reindeer::sum_points(int points) noexcept {
  race_points += points;
}


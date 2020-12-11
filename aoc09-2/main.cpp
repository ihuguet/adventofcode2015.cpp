#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <limits>

struct route_segment {
  std::string orig, dest;
  unsigned int dist;
};

bool operator<(route_segment &a, route_segment &b) {
  return a.orig != b.orig ? a.orig < b.orig : a.dest < b.dest;
}

static void get_dests_and_dists(
  std::istream &input,
  std::vector<std::string> &destinations,
  std::vector<route_segment> &route_segments);
static unsigned int calc_route_dist(
  std::vector<std::string> &destinations,
  std::vector<route_segment> &route_segments);

int main ()
{
  std::istream &input = std::cin;

  std::vector<std::string> destinations;
  std::vector<route_segment> route_segments;
  get_dests_and_dists(input, destinations, route_segments);

  unsigned int max_dist = 0;
  do {
    unsigned int dist = calc_route_dist(destinations, route_segments);
    if (dist > max_dist)
      max_dist = dist;
  } while (std::next_permutation(destinations.begin(), destinations.end()));

  std::cout << "Max. distance: " << max_dist << std::endl;
  return 0;
}

static void get_dests_and_dists(
  std::istream &input,
  std::vector<std::string> &destinations,
  std::vector<route_segment> &route_segments
) {
  static std::regex line_regex("^([[:alpha:]]+) to ([[:alpha:]]+) = ([[:digit:]]+)$");

  std::string line;
  while (std::getline(input, line)) {
    std::smatch matchs;
    if (!std::regex_match(line, matchs, line_regex)) {
      std::cerr << "Invalid format: " << line << '\n';
      continue;
    }

    std::string orig = matchs[1];
    std::string dest = matchs[2];
    unsigned int dist = std::stoi(matchs[3]);

    if (std::find(destinations.cbegin(), destinations.cend(), orig) == destinations.cend())
      destinations.push_back(orig);
    if (std::find(destinations.cbegin(), destinations.cend(), dest) == destinations.cend())
      destinations.push_back(dest);
    route_segments.push_back(route_segment{orig, dest, dist});
    route_segments.push_back(route_segment{dest, orig, dist});
  }
  
  std::sort(destinations.begin(), destinations.end());
  std::sort(route_segments.begin(), route_segments.end());
}

static unsigned int calc_route_dist(
  std::vector<std::string> &destinations,
  std::vector<route_segment> &route_segments
) {
  unsigned int dist = 0;
  for (auto it = destinations.cbegin(); it != std::prev(destinations.cend()); it++) {
    std::string orig = *it;
    std::string dest = *std::next(it);
    auto found_it = std::find_if(route_segments.cbegin(), route_segments.cend(), [&orig,&dest](auto &seg) {
      return seg.orig == orig && seg.dest == dest;
    });
    dist += found_it->dist;
  }
  return dist;
}
#include <iostream>
#include <string>
#include <regex>
#include <map>

enum class gate {AND, OR, LSHIFT, RSHIFT, NOT, NOOP};
struct wire {
  std::string name, in1, in2;
  gate in_gate;
};

static std::map<std::string,wire> build_circuit(std::istream &input);
static uint16_t calc_wire_value(std::map<std::string,wire> &wires, const std::string &wire_name, std::map<std::string,uint16_t> &vals_cache);
static uint16_t calc_wire_value(std::map<std::string,wire> &wires, const std::string &wire_name);
static inline bool signal_is_direct_value (const std::string &wire_name);
static inline bool gate_has_2_ops(gate g);
static gate str_to_gate(const std::string &str);

int main (int argc, char *argv[])
{
  if (argc > 3) {
    std::cerr << "Wrong args. num." << std::endl;
    return 1;
  }

  std::istream &input = std::cin;
  std::string wire_name = argc >= 2 ? argv[1] : "a";
  std::string wire_override = argc >= 3 ? argv[2] : "b";

  std::map<std::string,wire> wires = build_circuit(input);
  uint16_t value = calc_wire_value(wires, wire_name);
  wires[wire_override].in2 = std::to_string(value);
  wires[wire_override].in_gate = gate::NOOP;
  value = calc_wire_value(wires, wire_name);

  std::cout << "Value for wire '" << wire_name << "': " << value << std::endl;
  return 0;
}

static std::map<std::string,wire> build_circuit(std::istream &input) {
  std::regex line_regex("^(?:([a-z]+|[0-9]+) )?(?:([A-Z]+) )?([a-z]+|[0-9]+) -> ([a-z]+)");

  std::map<std::string,wire> wires;

  std::string line;
  while (std::getline(input, line)) {
    std::smatch matchs;
    if (!std::regex_match(line, matchs, line_regex)) {
      std::cout << "Invalid line: " << line << '\n';
      continue;
    }

    wires.emplace(matchs[4], wire {matchs[4], matchs[1], matchs[3], str_to_gate(matchs[2])});
  }

  return wires;
}

static uint16_t calc_wire_value(std::map<std::string,wire> &wires, const std::string &wire_name, std::map<std::string,uint16_t> &vals_cache) {
  if (signal_is_direct_value(wire_name))
    return static_cast<uint16_t>(std::stoi(wire_name));

  auto it = vals_cache.find(wire_name);
  if (it != vals_cache.end())
    return it->second;

  wire &w = wires.at(wire_name);

  uint16_t value_in1 = gate_has_2_ops(w.in_gate) ? calc_wire_value(wires, w.in1, vals_cache) : 0;
  uint16_t value_in2 = calc_wire_value(wires, w.in2, vals_cache);

  uint16_t value_out;
  switch (w.in_gate) {
    case gate::AND:    value_out = value_in1 & value_in2; break;
    case gate::OR:     value_out = value_in1 | value_in2; break;
    case gate::LSHIFT: value_out = value_in1 << value_in2; break;
    case gate::RSHIFT: value_out = value_in1 >> value_in2; break;
    case gate::NOT:    value_out = ~value_in2; break;
    case gate::NOOP:   value_out = value_in2; break;
  }

  vals_cache[wire_name] = value_out;
  return value_out;
}

static uint16_t calc_wire_value(std::map<std::string,wire> &wires, const std::string &wire_name) {
  std::map<std::string,uint16_t> vals_cache;
  return calc_wire_value(wires, wire_name, vals_cache);
}

static inline bool signal_is_direct_value (const std::string &sig_nme) {
  static std::regex num_regex("^\\d+$");
  return std::regex_match(sig_nme, num_regex);
}

static inline bool gate_has_2_ops(gate g) {
  return g != gate::NOT && g != gate::NOOP;
}

static gate str_to_gate(const std::string &str) {
  if (str == "AND")    return gate::AND;
  if (str == "OR")     return gate::OR;
  if (str == "LSHIFT") return gate::LSHIFT;
  if (str == "RSHIFT") return gate::RSHIFT;
  if (str == "NOT")    return gate::NOT;
  if (str == "")       return gate::NOOP;
  throw std::invalid_argument(std::string("Unknown gate: ") + str);
}

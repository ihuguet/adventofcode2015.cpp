#include <iostream>
#include <string>
#include <regex>

enum class gate {AND, OR, LSHIFT, RSHIFT, NOT, NOOP};
struct wire {
  std::string name, in1, in2;
  gate in_gate;
  bool calculated;
  uint16_t val;
};

static std::map<std::string,wire> build_circuit(std::istream &input);
static uint16_t calc_wire_value(std::map<std::string,wire> &wires, const std::string &sig_nme);
static inline bool signal_is_direct_value (const std::string &sig_nme);
static inline bool gate_has_2_ops(gate g);
static gate str_to_gate(const std::string &str);

int main (int argc, char *argv[])
{
  std::istream &input = std::cin;
  std::string wire_name = argc == 2 ? argv[1] : "a";

  std::map<std::string,wire> wires = build_circuit(input);
  uint16_t value = calc_wire_value(wires, wire_name);

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

    wires.emplace(matchs[4], wire {matchs[4], matchs[1], matchs[3], str_to_gate(matchs[2]), false, 0});
  }

  return wires;
}

static uint16_t calc_wire_value(std::map<std::string,wire> &wires, const std::string &wire_name) {
  if (signal_is_direct_value(wire_name))
    return static_cast<uint16_t>(std::stoi(wire_name));

  wire &w = wires.at(wire_name);

  if (w.calculated)
    return w.val;

  uint16_t value_in1 = gate_has_2_ops(w.in_gate) ? calc_wire_value(wires, w.in1) : 0;
  uint16_t value_in2 = calc_wire_value(wires, w.in2);

  switch (w.in_gate) {
    case gate::AND:    w.val = value_in1 & value_in2; break;
    case gate::OR:     w.val = value_in1 | value_in2; break;
    case gate::LSHIFT: w.val = value_in1 << value_in2; break;
    case gate::RSHIFT: w.val = value_in1 >> value_in2; break;
    case gate::NOT:    w.val = ~value_in2; break;
    case gate::NOOP:   w.val = value_in2; break;
  }
  w.calculated = true;
  return w.val;
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

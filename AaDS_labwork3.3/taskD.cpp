#include <iostream>
#include <unordered_map>
#include <vector>

class Automaton
{
 private:
  struct State
  {
    bool terminal;
    std::unordered_map<char, int> transitions;
  };

 private:
  explicit Automaton(size_t size = 1);

 public:
  static Automaton fromString(const std::string &string);
  bool step(char current, bool autoReset = false);
  void reset();
  bool isTerminal();

 private:
  int activeStateIdx;
  std::vector<State> states;
};

Automaton::Automaton(size_t size)
    : activeStateIdx(0)
    , states(size)
{}

Automaton Automaton::fromString(const std::string &str)
{
  Automaton result;
  std::vector<int> suffix(str.size() + 1, 0);
  suffix[0] = -1;

  for (int i = 0; i < str.size(); i++) {
    char ch = str[i];

    int p = suffix[i];
    while (p != -1 && str[p] != ch) {
      p = suffix[p];
    }
    suffix[i + 1] = p + 1;
  }

  result.states.resize(str.size() + 1);
  for (int i = 0; i < str.size(); i++) {
    result.states[i].transitions[str.at(i)] = i + 1;
  }

  for (size_t i = 1; i < suffix.size(); i++) {
    State &suf = result.states[suffix[i]];
    State &state = result.states[i];
    for (auto &trans : suf.transitions) {
      char ch = trans.first;
      if (state.transitions.count(ch) == 0) {
        state.transitions[ch] = trans.second;
      }
    }
  }

  result.states.back().terminal = true;

  return result;
}

bool Automaton::step(char current, bool autoReset)
{
  State &activeState = states[activeStateIdx];
  if (activeState.transitions.count(current) == 0) {
    if (autoReset) {
      reset();
    }
    return false;
  }

  activeStateIdx = activeState.transitions[current];
  return true;
}

void Automaton::reset()
{
  activeStateIdx = 0;
}

bool Automaton::isTerminal()
{
  return states[activeStateIdx].terminal;
}

int main() {
  std::string p, t;
  std::cin >> p >> t;

  Automaton automaton = Automaton::fromString(p);
  std::vector<int> result;
  for (int i = 0; i < t.size(); i++) {
    automaton.step(t[i], true);
    if (automaton.isTerminal()) {
      result.push_back(i + 1 - p.size());
    }
  }

  std::cout << result.size() << std::endl;
  for (int &v : result) {
    std::cout << v + 1 << " ";
  }
  return 0;
}

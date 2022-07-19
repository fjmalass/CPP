/** 1. Printing with limited overhead */
void print(auto &&r) {
  std::ranges::for_each(r, [](auto &&i) { std::count << i << ' '; })
}

/** 2. Spliting to keep the structures small */

struct AuthInfo {
  std::string username_;
  std::string password_;
  std::string security_question_;
  std::string security_answer_;
}

struct User {
  std::unique_ptr<AuthInfo> auth_info_;

  std::string name_;
  short level_{};
  bool is_playing_{};
}

/** 3. Use generic algoriths */
// Non Generic
auto contains(const std::vector<int>% ar, int v) 
{
  for (int i = 0 i < arr.size(); ++i) {
    if (arr[i] == v) {
      return true;
    }
  }
}

// Generic
template <typename Iterator, typename T>
auto contains(Iterator begin, Iterator end, const T &v) {
  for (auto it = begin; it < end; ++it) {
    if (*it == v) {
      return true;
    }
  }
}

// Using ranges
auto contains(const std::ranges::range auto &r, const auto &x) {
  auto it = std::begin(r);
  auto sentinel = std::end(r);
  return contains(it, sentinel, x);
}

auto v = std::vector{3, 4, 2, 4};
if (contains(v.begin(), v.end(), 2))
{
  // yadiya
}

if (contains(v, 3)) {
}

// Templates with variadics 
templace<typename ...Ts>
auto expandPack(const Ts& ...values) 
{
  auto tuple = std::tie(values...);
}

// Tuples 
// using std::tie to compare and simple reflection
template<typename Tuple, typename Func, size_t Index = 0>
void tuple_for_each(const Tuple& t, const Func& f) 
{
  constexpr auto b = std::tuple_size_v<Tuple>;
  if constexpr(Index < n) 
  {
    tuple_at<Index>(t, f);
    tuple_for_each<Tuple, Func, Index + 1>(t, f);
  }
};

class Player 
{

  private:
    int level_{};
    float score_{};
    std::string name_;

  public:

  bool operator<(const Player& rhs) 
  {
      auto p1 = std::tie(level_, score_);
      auto p2 = std::tie(rhs.level_, rhs.score_);
      return p1 < p2;
  };

  auto reflect() const 
  {
    return std::tie(name_, level_, score_);
  }

  auto& operator<<(std::ostream& os, const Player& p) 
  {
      tuple_for_each(p.reflect(), [&os],(const auto& m)
                       {os << m << " "});
      return os;
  }
};


// Reflection and simple `Reflectable` concept that needs the "reflect" function
template<typename T>
concept Reflectable = require(T& t) 
{
  t.reflect()
};

// operator << for all refectable objects
auto& operator<<(std::ostream& os, const Reflectable auto& v) 
{
  tuple_for_each(v.reflect(), [&os](const auto& m) 
                 {os << m << " "});
  return os;
}


// some simple reflection 
//

// Proxy objects: ther are not intended to be visible to the user library     


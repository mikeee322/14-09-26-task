#include <thread>

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

void sumFunc(const data_t& values, size_t begin, size_t end, value_t &sum)
{
  for (size_t i = begin; i < end; ++i)
  {
    sum += values[i];
  }
}

int main(int argc, char **argv){
  constexpr size_t size{1'000'000'000};
  data_t values(size, 1);
  size_t theard_count = 0;
  theard_count = std::stoull(argv[1]);
  std::vector< std::thread > thrs;
  value_t sum = 0;

  std::thread thr(sumFunc, std::ref(values), 0, values.size(), std::ref(sum));

  thr.join();

}

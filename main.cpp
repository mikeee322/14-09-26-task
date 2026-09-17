#include <thread>
#include <iostream>
#include <chrono>

namespace mtt{
  class Clicker {
  public:
    Clicker():
      start_(std::chrono::high_resolution_clock::now())
    {}
    double millisec() const {
      using std::chrono::high_resolution_clock;
      using std::chrono::duration_cast;
      using std::chrono::milliseconds;
      auto t = high_resolution_clock::now();
      return static_cast< double > (std::chrono::duration_cast< milliseconds >(t - start_).count());
    }
  private:
    std::chrono::time_point< std::chrono::high_resolution_clock > start_;
  };
}

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
  if (argc < 2)
  {
    std::cerr << "err\n";
    return 1;
  }
  constexpr size_t size{1'000'000'000};
  data_t values(size, 1);
  size_t thread_count = 0;
  thread_count = std::stoull(argv[1]);
  size_t partSize = values.size() / thread_count;

  std::vector< std::thread > thrs;
  std::vector< value_t > sums(thread_count, 0);

  mtt::Clicker cl;
  for (size_t i = 0; i < thread_count; ++i) {
    size_t begin = partSize * i;
    size_t end = begin + partSize;
    if (i == thread_count - 1) {
      end = begin + partSize + values.size() % thread_count;
    }

    std::thread thr(sumFunc, std::ref(values), begin, end, std::ref(sums[i]));

    thrs.push_back(std::move(thr));
  }

  for (size_t i = 0; i < thread_count; ++i) {
    thrs[i].join();
  }

  double totalTime = cl.millisec();

  value_t total{0};
  for (size_t i = 0; i < thread_count; ++i) {
    total += sums[i];
  }

  std::cout << "Sum: " << total << '\n';
  std::cout << "Time: " << totalTime << " ms\n";



}


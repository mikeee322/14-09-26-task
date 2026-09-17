#include <thread>
#include <iostream>

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
  data_t values(10, 1);
  value_t sum{0};
  size_t thread_count = 0;
  thread_count = std::stoull(argv[1]);
  size_t partSize = values.size() / thread_count;



  std::vector< std::thread > thrs;
  std::vector<value_t> sums(thread_count, 0);

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

  value_t total{0};
  for (size_t i = 0; i < thread_count; ++i) {
    total += sums[i];
  }



}


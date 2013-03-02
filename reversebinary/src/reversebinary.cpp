#include <bitset>
#include <iostream>

template<size_t N> uint32_t reverse(const std::bitset<N>& ordered) {
      std::bitset<N> reversed;

      short int bitset_length = 0;
      for(size_t i = 0, j = N - 1; i < N; ++i, --j) {
	    if (ordered.test(i)) bitset_length = i+1;
	    reversed[j] = ordered[i];
	    
       }

       return reversed.to_ulong() >> (32-bitset_length);
 };

 int main() {
      uint32_t num; 
      const size_t N = sizeof(num)*8;

      std::cin >> num;
      std::cout << reverse<N>(num) << std::endl;
 }
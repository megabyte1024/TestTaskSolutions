/*
** TASK: **

You are given a string consisting of lowercase letters of the English alphabet.
You must split this string into a minimal number of substrings in such a way
that no letter occurs more than once in each substring.

For example, here are some correct splits of the string "abacdec": 
('a', "bac', 'dec), ('a', bacd', 'ec') and (ab', 'ac','dec').

Write a function:

function solution(S);

that, given a string S of length N, returns the minimum number of substrings 
into which the string has to be split.

Examples:

1. Given 'world', your function should retum 1. There is no need to split the
   string into substrings as all letters occur just once.
2. Given 'dddd', your function should return 4. The result can be achieved by
   splitting the string into four substrings ('d', 'd', 'd', 'd').
3. Given 'cycle', your function should return 2. The result can be achieved by
   splitting the string into two substrings ('cy', 'cle') or ('c', 'ycle').
4. Given 'abba', your function should return 2. The result can be achieved by
   splitting the string into two substrings ('ab', 'ba').

Write an efficient algorithm for the following assumptions:
  * N is an integer within the range [1..1000000);
  * string S consists only of lowercase letters (a-z).



** SOLUTION: **

1. Start from the beginning of the string.
2. Find a longest substring, containing only unique letters, starting from 
   current position.
3. Increment a counter variable.
4. Repeat the cycle till the end of the string starting from the step 2.

In the end, the counter variable will contain the minimum number of unique 
substrings in the string.

This strategy - to find a longest unique substring, is the best choice for this
task. In the end of every iteration we have the minimum number of unique 
substrings for the current moment. It possible to split the found longest 
substring to two or more parts, but it will not be the best choice - number of
unique substrings will be more than 1. Also this strategy does not hide 
the possible best choice - minimum number of unique substrings, for the rest of
the string. Let's show that the previous sentence is true.

Let's take a string `abcadefg`. The first longest unique substring is `abc`,
the string contains two unique substrings - `abc` and `adefg`. Lets suppose 
the second letter `a` hides a possible best solution. In this case, to fit 
the task conditions, we have to split the string to the substrings 'a' and 
'bcadefg'. Indeed , in the second case we found a longer unique substring, but
the number unique substrings remains the same - 2.

If the string is longer than `abcadefg`, for instance, `abcadefgahiklmnoa`, 
then the task is possible to split on two substaks for the strings `abcadefg` 
and `ahiklmnoa` and the final result is a summary of the subtasks results - 
2 + 2 = 4.

Q.E.D.



** ASYMPTOTIC COMPUTATIONAL COMPLEXITY: **

- Time complexity: O(n)
- Space complexity: O(1)



** NOTES: **
1. The code requires a C++17 compiler, because it uses `std::string_view`.
2. The code works only if the distance between numeric values of the letters 
   'a' and 'z' is enough to store the alphabet is a 32-bit variable (one bit 
   for a letter). For the ASCII character encoding, the distance is sufficient
   to execute the code on a CPU which compiler supports bit operations with
   32-bit variables.
   A generic solution is to use either the `std::bitset<iAlphabetSize>` or even
   the `std::unordered_map<char, bool>` types as a storage of the alphabet, but
   in this case the solution will not be `constexpr`.
3. The Clang compiler is smart enough to evaluate in the compile time even 
   the `for` cycle with `assert` - https://godbolt.org/z/nh16TebG9.
*/

#include <iostream>
#include <cassert>
#include <climits>

constexpr char minLetter = std::min('a', 'z');
constexpr char maxLetter = std::max('a', 'z');

typedef uint32_t TAlphabetSet;
const size_t iAlphabetSize {maxLetter - minLetter + 1};
static_assert(iAlphabetSize <= sizeof(TAlphabetSet) * CHAR_BIT);

typedef std::pair<size_t, size_t> TSequenceIndex;

constexpr size_t CalcNumOfMaxSequence(std::string_view str) {
  size_t iNumOfSubstrings = 1;
  TAlphabetSet alphabet = 0;
  for (const char ch : str) {
    const size_t idxLetter = ch - minLetter;
    if ((alphabet & ((TAlphabetSet)1 << idxLetter)) != 0) {
      alphabet = 0;
      iNumOfSubstrings++;
    }
    alphabet |= ((TAlphabetSet)1 << idxLetter);
  }
  return iNumOfSubstrings;
}

constexpr size_t solution(std::string_view str) {
  return CalcNumOfMaxSequence(str);
}

typedef std::pair<std::string_view, size_t> TCheckItem;

constexpr TCheckItem g_lstCheck[] {
  { "abcdaefghzyx", 2 },
  { "abcdd", 2 },
  { "aabcd", 2 },
  { "adda", 2 },
  { "ddddd", 5 },
  { "world", 1 },
  { "cycle", 2 },
  { "abcadefgahiklmnoa", 4},
};

int main(int argc, char *argv[]) {
  static_assert(solution(g_lstCheck[0].first) == g_lstCheck[0].second);
  static_assert(solution(g_lstCheck[1].first) == g_lstCheck[1].second);
  static_assert(solution(g_lstCheck[2].first) == g_lstCheck[2].second);
  static_assert(solution(g_lstCheck[3].first) == g_lstCheck[3].second);
  static_assert(solution(g_lstCheck[4].first) == g_lstCheck[4].second);
  static_assert(solution(g_lstCheck[5].first) == g_lstCheck[5].second);
  static_assert(solution(g_lstCheck[6].first) == g_lstCheck[6].second);
  static_assert(solution(g_lstCheck[7].first) == g_lstCheck[7].second);
  for (const TCheckItem &item : g_lstCheck) {
    assert(solution(item.first) == item.second);
  }
  return 0;
}

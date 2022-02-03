/*

** TASK: **

A string S consisting of uppercase English letters is given. In one move we can
delete seven letters from S, forming the word "BALLOON" (one 'B', one 'A',
two 'L's, two 'O's and one 'N'), and leave a shorter word in S.

If the remaining letters in the shortened S are sufficient to allow another
instance of the word "BALLOON" to be removed, next move can be done.

What is the maximum number of such moves that we can apply to S?

Write a function:

  function solution(S);

that, given a string S of length N, returns the maximum number of moves that
can be applied.

Examples:

1. Given S="BAONXXOLL", the function should return 1.

  BAONXXOLL -> XX
  ^^^^  ^^^
2. Given S="BAOOLLNNOLOLGBAX", the function should return 2.

  BAOOLLNNOLOLGBAX -> BOLLNOGAX -> GX
   ^^   ^  ^^^ ^      ^^^^^^ ^
3. Given S="QAWABAWONL", the function should return 0.

  QAWABAWONL


 ** SOLUTION: **

1. Count the letter frequency for the word "BALLOON".

      {{'B', 1}, {'A', 1}, {'L', 2},  {'O', 2}, {'N', 1}}

2. Counter the letter frequency for an input sentence, in the same way as for
   the word "BALLOON", for instance, the frequency for the sentece
   "QAWABAWONL".

      {{'B', 1}, {'A', 3}, {'L', 1},  {'O', 1}, {'N', 1}, {'Q', 1}, {'W', 2}}

3. Calculate how many times (multiplicity) the frequency of every letter in
   the word "BALLOON" occurs in the letter frequency vector of the input
   sentence, i.e., `multiplicity[i] = freqInput[i] / freqBALLON[i];`,
   for instance,

      multiplicity['B'] = 1; // 1 div 1
      multiplicity['A'] = 3; // 3 div 1
      multiplicity['L'] = 0; // 1 div 2
      multiplicity['O'] = 0; // 1 div 2
      multiplicity['N'] = 1; // 1 div 1

4. Return the minimum multiplicity. In the example, it is 0.

** ASYMPTOTIC COMPUTATIONAL COMPLEXITY: **

  - Time complexity: O(n)
  - Space complexity: O(1)

** NOTES: **
  1. The code requires a C++17 compiler, because it uses `std::string_view`.
  2. The code works only if the distance between numeric values of 
     the letters 'A' and 'Z' is enough to store the letters frequency 
     array in memory. For the ASCII character encoding, the distance is 
     sufficient to execute the code on a computer having a few 
     kilobytes of RAM.
     A generic solution is to use the `std::unordered_map<char, size_t>` 
     type as a storage of letter frequencies. 
 */

#include <iostream>
#include <cassert>
#include <array>
#include <algorithm>

constexpr char minLetter = std::min('A', 'Z');
constexpr char maxLetter = std::max('A', 'Z');
constexpr size_t iLetterArraySize {maxLetter - minLetter + 1};
typedef std::array<size_t, iLetterArraySize> TArrLetterFreq;

constexpr TArrLetterFreq CalcLetterFrequency(std::string_view str) {
  TArrLetterFreq arrLetterFrequency {};
  for (const char chLetter : str) {
    arrLetterFrequency[chLetter - minLetter]++;
  }
  return arrLetterFrequency;
}

constexpr size_t SolutionUniversal(std::string_view strInput,
                                   const TArrLetterFreq &arrTemplateLetterFreq) {
  const TArrLetterFreq arrInputLetterFreq {CalcLetterFrequency(strInput)};
  size_t iMinLetterMultiplicity = SIZE_MAX;
  for (size_t i = 0; i < iLetterArraySize; i++) {
    const size_t iTemplateLetterFreq = arrTemplateLetterFreq[i];
    if (iTemplateLetterFreq != 0) {
      const size_t iInputLetterFreq = arrInputLetterFreq[i];
      if (iInputLetterFreq == 0) {
        iMinLetterMultiplicity = 0;
        break;
      }
      const size_t iLetterMultiplicity = iInputLetterFreq / iTemplateLetterFreq;
      if (iMinLetterMultiplicity > iLetterMultiplicity) {
        iMinLetterMultiplicity = iLetterMultiplicity;
      }
    }
  }
  return iMinLetterMultiplicity;
}

constexpr size_t solution(std::string_view str) {
  constexpr TArrLetterFreq arrBalloonLetterFreq {CalcLetterFrequency("BALLOON")};
  return SolutionUniversal(str, arrBalloonLetterFreq);
}

typedef std::pair<std::string_view, size_t> TCheckItem;

constexpr TCheckItem g_lstCheck[] {
  { "BAONXXOLL", 1 },
  { "BAOOLLNNOLOLGBAX", 2 },
  { "QAWABAWONL", 0 },
  { "", 0 },
  { "BLLOON", 0 },
  { "BALOON", 0 },
  { "BALLOOON", 1 }
};

int main(int argc, char *argv[]) {
  static_assert(solution(g_lstCheck[0].first) == g_lstCheck[0].second);
  static_assert(solution(g_lstCheck[1].first) == g_lstCheck[1].second);
  static_assert(solution(g_lstCheck[2].first) == g_lstCheck[2].second);
  static_assert(solution(g_lstCheck[3].first) == g_lstCheck[3].second);
  static_assert(solution(g_lstCheck[4].first) == g_lstCheck[4].second);
  static_assert(solution(g_lstCheck[5].first) == g_lstCheck[5].second);
  static_assert(solution(g_lstCheck[6].first) == g_lstCheck[6].second);
  for (const auto [str, iMust] : g_lstCheck) {
    assert(solution(str) == iMust);
  }
  return 0;
}

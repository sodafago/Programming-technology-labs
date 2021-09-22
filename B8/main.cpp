#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <regex>

#include "lexical-unit.hpp"
#include "ostream-iterator.hpp"

int main(int nArgs, const char* args[])
{
  try
  {
    const size_t DEFAULT_LENGTH = 40;
    const std::string FIRST_ARG = "--line-width";

    size_t lineWidth;
    if (nArgs == 1)
    {
      lineWidth = DEFAULT_LENGTH;
    }
    else if (nArgs == 3 && FIRST_ARG == args[1] && std::regex_match(args[2], std::regex("\\d+")))
    {
      lineWidth = std::stoull(args[2]);
    }
    else
    {
      throw std::invalid_argument("Bad compilation arguments!");
    }

    const size_t MAGIC_MINIMAL_LINE_WIDTH_WHICH_I_LEARNED_FROM_TESTS = 25;
    if (lineWidth < MAGIC_MINIMAL_LINE_WIDTH_WHICH_I_LEARNED_FROM_TESTS)
    {
      throw std::invalid_argument("Invalid argument \"lineWidth\".");
    }
    
    std::transform(std::istream_iterator<text::LexicalUnit>(std::cin), std::istream_iterator<text::LexicalUnit>(),
        text::OstreamIterator(std::cout, lineWidth), text::LexicalUnit::ValidateFunctor());
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << '\n';

    return 1;
  }
}

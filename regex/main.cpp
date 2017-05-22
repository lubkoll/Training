#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::string s = "Some people, when confronted with a problem, think "
                    "\"I know, I'll use regular expressions.\" "
                    "Now they have two problems.";

    // Case-insensitive regex for 'regular expressions'.
    std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::icase);
    if (regex_search(s, self_regex))
        std::cout << "Text contains the phrase 'regular expressions'\n\n";

    // Regex for words (sequences of non-whitespaces)
    auto word_regex = std::regex("(\\S+)");
    // Generate iterator for all words in s
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found " << distance(words_begin, words_end) << " words.\n\n";

    const int N = 6;
    std::cout << "Words longer than " << N << " characters:\n";
    std::for_each( words_begin, words_end,
                   [N](const auto& word)
                   {
                       if( word.str().size() > N )
                           std::cout << " " << word.str() << std::endl;
                   } );
    std::cout << std::endl;
    std::cout << count_if( words_begin, words_end,
                           [N]
                           (const auto& word)
                           { return word.str().size() > N; })
              << "\n";

    // Surround words with at least seven characters with square brackets.
    std::regex long_word_regex("(\\w{7,})");
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << "\n\n";
}

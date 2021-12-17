#ifndef COLOR_H
#define COLOR_H

/*!
 * Color code:
 * https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 * 
 * How to use this function:
 * ```c++
 *      std::cout << "Esse texto aparece normal, "
 *                << Color::tcolor("texto em vermelho e negrito", Color::RED, Color::BOLD)
 *                << "\n";
 * ```
 */
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;
#include <array>
using std::array;

namespace Color {
    // Alias
    typedef short value_t;

    /// Color attribute - colors
    static constexpr short BLACK{ 30 };
    static constexpr short RED{ 31 };
    static constexpr short GREEN{ 32 };
    static constexpr short YELLOW{ 33 };
    static constexpr short BLUE{ 34 };
    static constexpr short MAGENTA{ 35 };
    static constexpr short CYAN{ 36 };
    static constexpr short WHITE{ 37 };
    static constexpr short BRIGHT_BLACK{ 90 };
    static constexpr short BRIGHT_RED{ 91 };
    static constexpr short BRIGHT_GREEN{ 92 };
    static constexpr short BRIGHT_YELLOW{ 93 };
    static constexpr short BRIGHT_BLUE{ 94 };
    static constexpr short BRIGHT_MAGENTA{ 95 };
    static constexpr short BRIGHT_CYAN{ 96 };
    static constexpr short BRIGHT_WHITE{ 97 };
    /// Color attributes - modificators.
    static constexpr short REGULAR{ 0 };
    static constexpr short BOLD{ 1 };
    static constexpr short UNDERLINE{ 4 };
    static constexpr short BLINK{ 5 };
    static constexpr short REVERSE{ 7 };

    /// List of colors. You may which to change color ordering.
    static constexpr array< value_t, 14>color_list{
        31, 32, 33, 34, 35, 36, 37,
        91, 92, 93, 94, 95, 96, 97};

    /// Returns a string with a colored message.
    /*!
     * @param msg Message to display.
     * @param color Color code to apply to the message.
     * @param modifier Modifier code to apply to the message.
     * @return A string with the embedded color/modifier escape codes.
     */
    inline string tcolor( const string & msg, short color=Color::WHITE, short modifier=Color::REGULAR ){
        ostringstream oss;
        oss << "\33[" << modifier << ";" << color << "m" << msg << "\33[0m";
        return oss.str();
    }
}
#endif

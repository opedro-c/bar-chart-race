#include <algorithm>
using std::transform;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <thread>
#include <fstream>
#include "bcr_am.h"


// Verifies if all characters from string are numbers
/*!
* @param str The input string.
* @return A boolean value telling if string is numeric or not (false if string is empty)
*/
bool is_numeric(string str) {
    if (str.size()) {
        for (int i{0}; i < str.size(); i++) { 
            if (!isdigit(str.at(i))) return false; 
        }
        return true;
    }
    return false;
}

/// Tokenize a string
/*!
    * @param str The input string.
    * @param sep The delimiter symbol.
    * @return A list of tokenized strings.
    */
// splits string into string vector
vector<string> split(const string& str, char sep) {
    vector<string> word_vector{};
    string word;
    for (int i = 0; i < str.size(); i++) {
        // add word to word vector when current char is equals to separator
        if (*str.substr(i, 1).c_str() == sep) {
            word_vector.push_back(word);
            word.clear();
        } else {
            // concatenate current char with string
            // if it is different from separator char
            word += str.substr(i, 1);
        }
    }
    word_vector.push_back(word);
    return word_vector;
}

/**
 * Gets the next predecessor of number divisible by 5
 * @param num
 * @return predecessor of number divisible by 5
 */
int round_down(int num) {
    while (num % 5 != 0) { num--; }
    return num;
}

/**
 * Gets the next successor of number divisible by 5
 * @param num
 * @return successor of number divisible by 5
 */
int round_up(int num) {
    while (num % 5 != 0) { num++; }
    return num;
}

namespace bcra {
    // Instantiation of the global configuration variable.
    const Cfg global_cfg;

    BCRAnimation::BCRAnimation(){
        m_opt.input_filename = "";
        m_opt.fps            = global_cfg.default_fps;
        m_opt.n_bars         = global_cfg.default_bars;
    }

    void BCRAnimation::read_cli_input( int argc, char ** argv ) {
        if (argc == 1) {
            usage();
            exit(0);
        } else {
            for (int i{1}; i < argc; i++) {
                // the bars quantity will receive the default value (5)
                // if it's not in the interval or if the input value is not numeric
                if (string{argv[i]} == "-b") {
                    if (is_numeric(argv[++i])) {
                        int num_bars = atoi(argv[i]);
                        m_opt.n_bars = (num_bars > m_cfg.max_bars || num_bars < 1) ? m_cfg.default_bars : num_bars;
                    } else {
                        m_opt.n_bars = m_cfg.default_bars;
                    }
                // the fps will receive the default value (12)
                // if it's not in the interval or if the input value is not numeric
                } else if (string{argv[i]} == "-f") {
                    if (is_numeric(argv[++i])) {
                        int num_frames = atoi(argv[i]);
                        m_opt.fps = (num_frames > m_cfg.max_fps || num_frames < 1) ? m_cfg.default_fps : num_frames;
                    } else {
                        m_opt.fps = m_cfg.default_fps;
                    }
                } else {
                    m_opt.input_filename = argv[i];
                }
            }
        }
    }

    void BCRAnimation::display_welcome() const {
        for(int i{0};i<55;i++) { std::cout << "="; } std::cout << "\n";
        std::cout << "\t" << "Welcome to the Bar Chart Race, v1.0" << "\n";
        std::cout << "\t" << "Copyright (C) 2021, Pedro Costa Aragão" << "\n";
        for(int i{0};i<55;i++) { std::cout << "="; } std::cout << "\n";
        std::cout << "\n";
        string msg = ">>> Preparing to read input file \"" + m_opt.input_filename + "\"...\n\n";
        msg = Color::tcolor(msg, Color::BRIGHT_GREEN);
        std::cout << msg;
    }

    void BCRAnimation::display_input_read() {
        string msg = 
            ">>> We have " + std::to_string(bar_charts.size()) + " charts." + "\n" +
            ">>> Animation speed is: " + std::to_string(m_opt.fps) + "\n" +
            ">>> Title: " + chart_title + "\n" +
            ">>> Value is: " + chart_label + "\n" +
            ">>> " + chart_source + "\n" +
            ">>> " + "Number of categories found: " + std::to_string(num_of_categories) +"\n\n";
        std::cout << Color::tcolor(msg, Color::BRIGHT_GREEN);
    }

    void BCRAnimation::usage() {
        std::cout << 
            string{"Usage: bcr [<options>] <input_data_file>\n"}                      +
            string{"    Bar Chart Race options:\n"}                                   +
            string{"        -b  <num> Max # of bars in a single char.\n"}             +
            string{"            Valid range is [1,15]. Default values is "} + std::to_string(m_cfg.default_bars) + string{"\n"}       +
            string{"        -f  <num> Animation speed in fps (frames per second).\n"} +
            string{"            Valid range is [1,24]. Default value is "} + std::to_string(m_cfg.default_fps) + string{"\n"};
    }

    void BCRAnimation::read_input_file() {
        set<string> all_categories;
        std::ifstream file{m_opt.input_filename, std::fstream::in};
        try
        {
            if (!file) throw std::runtime_error("File could not be opened!\n");
            std::cout << Color::tcolor(">>> Processing data, please wait...\n", Color::BRIGHT_GREEN);
            // Read title, source and label
            std::getline(file, chart_title);
            std::getline(file, chart_label);
            std::getline(file, chart_source);

            string input;
            short n_lines;
            vector<string> tokens;
            BarChart bc; // instanciate barchart
            
            while (std::getline(file, input)) {
                if (is_numeric(input)) {
                    n_lines = std::atoi(input.c_str());
                    for (int i{0}; i < n_lines; i++) {
                        std::getline(file, input);
                        tokens = split(input, ','); // tokenize line
                        bc.set_date(tokens.at(m_cfg.input_date_idx));
                        // add new categories to barchart animation;
                        // if number of categories is bigger than the number of colors add "Others" category
                        if (chart_categories.size() < m_cfg.num_color_avlb) {
                            chart_categories.insert(tokens.at(m_cfg.input_categoy_idx));
                        } else {
                            chart_categories.insert("Others");
                        }
                        all_categories.insert(tokens.at(m_cfg.input_categoy_idx));
                        // add bar to barchart
                        bc.add(
                            tokens.at(m_cfg.input_label_idx),
                            std::stol(tokens.at(m_cfg.input_value_idx)),
                            tokens.at(m_cfg.input_categoy_idx)
                        );
                    }
                    bc.sort(); // sort barchart
                    bar_charts.push_back(bc); // add barchart to barchart collection
                    bc.clear(); // clear barchart so it can receive new bars
                }
            }
            num_of_categories = all_categories.size();
        }
        catch(std::exception &e)
        {
            std::cerr << Color::tcolor("\n>>> An error occurred while reading the file\n", Color::BRIGHT_RED);
            std::cerr << Color::tcolor(e.what(), Color::BRIGHT_RED);
            exit(1);
        }

        file.close();
    }

    void BCRAnimation::set_categories_colors() { 
        int c = 0;
        set<string>::iterator it;
        it = chart_categories.begin();
        while(it != chart_categories.end()) {
            categories_colors[*it] = Color::color_list.at(c);
            c++;
            it++;
        }
    }

    void BCRAnimation::print_bars(BarChart &bc) const {
        short
            total_bars = (m_opt.n_bars > bc.bars.size()) ? bc.bars.size() : m_opt.n_bars,
            k = bc.bars.size() - 1,
            num_blocks;
        string
            bar_drawing,
            block = "█";
        for (short i{0}; i < total_bars; i++) {
            // Calculate number of blocks to be inserted to bar
            num_blocks = get_num_blocks(bc, k);
            // Insert blocks to bar
            for (short j{0};j<num_blocks;j++) { bar_drawing += block; }
            try {
                std::cout << Color::tcolor(bar_drawing, categories_colors.at(bc.bars.at(k).category)) << " ";
                std::cout << Color::tcolor(bc.bars.at(k).label, categories_colors.at(bc.bars.at(k).category)) << " ";
            }
            catch(const std::out_of_range &e) {
                std::cout << Color::tcolor(bar_drawing, categories_colors.at("Others")) << " ";
                std::cout << Color::tcolor(bc.bars.at(k).label, categories_colors.at("Others")) << " ";
            }
            
            std::cout << "[ " << bc.bars.at(k).value << " ]";
            std::cout << "\n\n";
            bar_drawing.clear();
            k--;
        }
    }

    void BCRAnimation::print_x_axis(BarChart &bc) const {
        short
            total_bars = (m_opt.n_bars > bc.bars.size()) ? bc.bars.size() : m_opt.n_bars,
            line_len = m_cfg.max_bar_length + 3,
            smallest_bar_idx = bc.bars.size() - total_bars,
            biggest_bar_idx = bc.bars.size() - 1;
        int
            pos_smallest_tick = round_down(get_num_blocks(bc, smallest_bar_idx)),
            pos_biggest_tick = round_up(get_num_blocks(bc, biggest_bar_idx)),
            value_smallest_tick = round_down(bc.bars.at(smallest_bar_idx).value),
            value_biggest_tick = round_up(bc.bars.at(biggest_bar_idx).value),
            space_between_ticks = (pos_biggest_tick - pos_smallest_tick) / m_cfg.n_ticks,
            value_between_ticks = (value_biggest_tick - value_smallest_tick) / m_cfg.n_ticks;
        string
            x_axis_line,
            under_x_axis_line;
        // Build x-axis line and space under x-axis
        for (int i{0};i<line_len;i++) { x_axis_line += "-"; under_x_axis_line += " "; }
        x_axis_line += ">";
        // Put a zero in the beginning of x-axis
        under_x_axis_line.replace(0, 1, "0");
        // Replace hyphens by tick on correct places and display values under ticks
        for (int i{0};i<m_cfg.n_ticks + 1;i++) {
            x_axis_line.replace(pos_smallest_tick, 1, "+");
            under_x_axis_line.replace(pos_smallest_tick, 1, std::to_string(value_smallest_tick));
            value_smallest_tick += value_between_ticks;
            pos_smallest_tick += space_between_ticks;
        }
        std::cout << x_axis_line << "\n";
        std::cout << under_x_axis_line << "\n";
    }

    void BCRAnimation::print_categories() {
        auto it = chart_categories.begin();
        while(it != chart_categories.end()) {
            std::cout << Color::tcolor("█: " + *it + " ", categories_colors.at(*it));
            it++;
        }
        std::cout << "\n";
    }

    void BCRAnimation::display_charts() {
        for (int i{0}; i < bar_charts.size(); i++) {
            // Control thread to print in defined fps as expected by the user
            std::chrono::milliseconds  duration{ 1000/m_opt.fps };
		    std::this_thread::sleep_for( duration );
            BarChart bc = bar_charts.at(i);
            // Print title and time stamp
            std::cout << "\t\t\t" << Color::tcolor(chart_title, Color::BRIGHT_BLUE) << "\n";
            std::cout << "\t\t\t\t" << Color::tcolor("Time Stamp: " + bc.get_date(), Color::BRIGHT_BLUE) << "\n";
            std::cout << "\n";
            print_bars(bc);
            print_x_axis(bc);
            // Print label and source
            std::cout << Color::tcolor(chart_label, Color::BRIGHT_YELLOW) << "\n\n";
            std::cout << Color::tcolor(chart_source, Color::WHITE) << "\n";
            print_categories();
        }
    }

    void BCRAnimation::begin_animation() {
        string enter;
        std::cout << Color::tcolor(">>> Press enter to begin animation\n", Color::BRIGHT_GREEN);
        std::getline(std::cin, enter);
        set_categories_colors();
        display_charts();
    }
};

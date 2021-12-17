#ifndef BCR_ANIMATION_H
#define BCR_ANIMATION_H

/*!
 *  The Bar Char Race animation manager.
 */

#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <set>
using std::set;
#include <map>
using std::map;
#include <iostream>

#include "../libs/text_color.h"
#include "barchart.h"
#include "cfg.h"

// Auxiliary functions

bool is_numeric(string str);

std::vector<std::string> split(const string& str, char sep);

namespace bcra {

    /// Class representing an animation manager
    class BCRAnimation {
        private:
            struct Options {
                std::string input_filename; //!< Input data file.
                short n_bars;               //!< Requested # of bars per chart.
                short fps;                  //!< Animation speed in frames per second.
            };

            //=== Data members
            Options m_opt;                 //!< Overall options to set up the animation configuration.
            static Cfg m_cfg;              //!< Overall default values for the options and other stuff.

            string chart_title;            // barchart's main title
            string chart_source;           // information's source (displayed under the label)
            short num_of_categories;
            string chart_label;            // kind of value displayed by charts (displayed under the line)
            set<string> chart_categories;  // categories found on barcharts
            map<string, short> categories_colors;

            vector<BarChart> bar_charts;   // collection of bar charts

        public:
            BCRAnimation();
            BCRAnimation( const BCRAnimation & _clone) = delete;
            BCRAnimation( BCRAnimation && ) = delete;
            BCRAnimation & operator=( const BCRAnimation & _rhs ) = delete;
            BCRAnimation & operator=( BCRAnimation&& ) = delete;
            ~BCRAnimation() = default;

            // Read and parses CLI Options provided by user
            void read_cli_input( int argc, char ** argv );

            /// Display welcome message informing input file and asking user to wait the reading process
            void display_welcome() const;

            /// Display data related with input file
            void display_input_read();
            
            /// Allocate data based on the input file
            void read_input_file();

            // Ask user to press <enter>, then start animation
            void begin_animation();

        private:
            /// Print out the usage instructions.
            static void usage();

            /// Print bars from barchart
            void print_bars(BarChart &bc) const;

            /// Print x-axis with values
            void print_x_axis(BarChart &bc) const;

            /// Map categories and associate with available colors
            void set_categories_colors();

            // Print categories with respective colors
            void print_categories();

            /// Prints the complete chart
            void display_charts();

            /// Get number of blocks of bar that will be displayed
            static inline short get_num_blocks( BarChart &bc, short bar_idx ) {
                return m_cfg.max_bar_length * ((double) (bc.bars.at(bar_idx).value) / bc.max_bar_value());
            }


    }; // BCRAnimation class.
}
#endif

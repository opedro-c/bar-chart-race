#ifndef BARCHART_H
#define BARCHART_H

/*!
 * Bar Char Race project.
 *
 * @author Pedro
 * @data October 5th, 2020.
 */

#include <string>
using std::string;

#include <algorithm>
using std::sort;

#include <vector>
using std::vector;

#include "../libs/text_color.h"

namespace bcra {
    // The value type of data item.
    using value_t = long;

    /// This class represents a single Bar Chart.
    class BarChart {
        //=== Definition
        public:
            /// Represents a single bar information.
            struct BarItem {
                string label;    //!< Bar label.
                value_t value;   //!< Bar value.
                string category; //!< Bar category.
                BarItem( string l, value_t v, string c ) : label{l}, value{v}, category{c}
                {/*empty*/}
            };

            //== Data members
        public:
            /// The collection of bars items
            std::vector< BarItem > bars;

        private:
            /// The date (timestamp) of the bar chart.
            std::string m_date;

            //== Public interface
        public:
            /// Default ctro.
            BarChart();
            ~BarChart(){/*empty*/};

            /// Set the bar chart date.
            inline void set_date( std::string d ) { this -> m_date = d; }

            // Compare bars
            static inline bool cmp_bars( const BarItem &b1, const BarItem &b2 ) { return b1.value < b2.value; }

            /// Add a single bar to the bar chart.
            inline void add( const string& label, value_t value, const string& category ) {
                bars.push_back(BarItem(label, value, category));
            }

            /// Remove all bars from the chart.
            inline void clear() { bars.clear(); }

            /// Sort the bars in descending order.
            inline void sort() { std::sort(bars.begin(), bars.end(), cmp_bars); }

            //== Accessor methods.

            /// Retrieves the bar chart date
            inline string get_date( void ) const { return m_date; }

            /// Retrieves the value of the largest bar.
            inline value_t max_bar_value ( void ) {
                int max_value = bars.at(0).value;
                for (int i{0};i<bars.size();i++) { if (bars.at(i).value > max_value) max_value = bars.at(i).value; }
                return max_value;
            }

            /// Returns true if the bar chart has no bars.
            inline bool empty( void ) const { return bars.empty(); }
            
            /// Returns the # of bars in the chart.
            inline size_t size( void ) const { return bars.size(); }
    };

} // namespace bcra.
#endif

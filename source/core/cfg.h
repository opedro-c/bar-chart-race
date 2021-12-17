//
// Created by pedro on 16/12/2021.
//

#ifndef BARCHARRACE_CFG_H
#define BARCHARRACE_CFG_H
#include "../libs/text_color.h"

namespace bcra {
    struct Cfg {
        static constexpr short default_bars = 5;      //!< Default value for # of bars.
        static constexpr short max_bars = 15;         //!< Max number of bars allowed in the animation.
        static constexpr short default_fps = 12;      //!< Default fps.
        static constexpr short max_fps = 45;          //!< Max fps allowed.

        static constexpr short max_bar_length = 50;   //!< Max bar length in characters units.
        static constexpr short n_ticks = 5;           //!< Number of ticks on the X axis.
        static constexpr short height = 30;           //!< How many lines total one screen have.
        static constexpr short width = 60;            //!< How many columns total one screen have.
        static constexpr Color::value_t default_color = Color::GREEN;

        static constexpr short input_label_idx = 1;   //!< Label is located at tokens[1].
        static constexpr short input_value_idx = 3;   //!< Value is located at tokens[3].
        static constexpr short input_date_idx  = 0;   //!< Time is located at tokens[0].
        static constexpr short input_categoy_idx = 4; //!< Category is located at tokens[4].

        static constexpr short num_color_avlb = 13;   // number of colors available.
    };
}

#endif //BARCHARRACE_CFG_H

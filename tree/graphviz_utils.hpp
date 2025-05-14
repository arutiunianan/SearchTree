#pragma once

#include "include/graphviz.hpp"

namespace SearchTree {

namespace graphviz_formatter {

static inline graphviz_formatting root_node = {graphviz_color::ANI_PALE_SAND,
                                               graphviz_style::FILLED,
                                               graphviz_shape::RECORD};
static inline graphviz_formatting default_node = {
    graphviz_color::ANI_BROWN, graphviz_style::FILLED, graphviz_shape::RECORD};

static inline graphviz_formatting right_edge = {graphviz_color::ANI_GREEN,
                                                graphviz_style::FILLED};
static inline graphviz_formatting left_edge = {graphviz_color::ANI_RED,
                                               graphviz_style::FILLED};

}  // namespace graphviz_formatter

}  // end namespace SearchTree
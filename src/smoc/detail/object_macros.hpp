#pragma once

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define SMOC_PP_SEQ_TO_PROPERTY_PAIR(r, data, elem)                            \
  {BOOST_PP_SEQ_ELEM(0, elem), BOOST_PP_SEQ_ELEM(1, elem)},

#define SMOC_PP_SEQ_TO_PROPERTY_MAP(MAP)                                       \
  { BOOST_PP_SEQ_FOR_EACH(SMOC_PP_SEQ_TO_PROPERTY_PAIR, , MAP) }

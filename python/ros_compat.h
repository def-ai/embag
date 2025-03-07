#pragma once

#include <pybind11/pybind11.h>

#include "lib/view.h"
#include "utils.h"

namespace py = pybind11;

struct IteratorCompat {
  explicit IteratorCompat(const Embag::View::iterator& i) : iterator_(i) {}

  py::tuple operator*() const {
    const auto msg = *iterator_;
    // TODO: Change the timestamp to a rostime - they have more precision!
    return py::make_tuple(msg->topic, msg->data(), msg->timestamp.to_sec());
  }

  bool operator==(const IteratorCompat &other) const {
    return iterator_ == other.iterator_;
  }

  Embag::View::iterator& operator++() {
    return ++iterator_;
  }

  Embag::View::iterator iterator_;
};

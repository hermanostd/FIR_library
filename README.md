# EasyDSP
This is a c++ library for fir filters and windows.

FEATURES:

-No exceptions, errors handled by std::expected

-Non mutable FIR filters, with mutable windows

-Mutable windows

-Easy and explicit error handeling using enums

-No exposed constructors, validation handled by create()

-Built in convolve() and convolveInPlace() functions for using the filters

-Built in apply() and applyInPlace() functions for using windows

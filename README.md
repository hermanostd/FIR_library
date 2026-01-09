# EasyDSP
This is a c++ library for fir filters and windows.

FEATURES:
-No exceptions, errors handled by std::expected
-Non mutable FIR filters
-Mutable windows
-easy and explicit error handeling using enums
-no exposed constructors, validation handled by create()
-built in convolve() and convolveInPlace() functions for using the filters

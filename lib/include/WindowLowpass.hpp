#pragma once

#include "FIR.hpp"

namespace oh::fir{

/// @brief this class Lowpass FIR filter using window method
class WindowLowpass : public FIR {            

    private:

    double m_fc;

    /// @brief constructor, rectangular is the default window
    /// @param fc cutoff frequency
    /// @param size size of filter
    WindowLowpass(double fc, size_t size);

    /// @brief constructor
    /// @param fc cutoff frequency
    /// @param size size of filter
    /// @param w_type type of window
    WindowLowpass(double fc, size_t size, wnd::WindowType w_type);

    protected:

    /// @brief calculates coefficients
    /// @return void on success, FIRError on failure
    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    /// @brief creates WindowLowpass object, default window: Rectangular
    /// @param fc cutoff frequency
    /// @param size size of FIR
    /// @return WindowLowpass object on success, FIRError on failure
    static std::expected <WindowLowpass, FIRError> create(double fc, size_t size);

    /// @brief creates WindowLowpass object
    /// @param fc cutoff frequency
    /// @param size size of FIR
    /// @param w_type type of window
    /// @return WindowLowpass object on success, FIRError on failure
    static std::expected <WindowLowpass, FIRError> create(double fc, size_t size, wnd::WindowType w_type);

};

}

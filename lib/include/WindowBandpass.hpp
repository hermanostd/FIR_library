#pragma once

#include "FIR.hpp"

namespace oh::fir {

/// @brief this class implements a bandpass filter using window method
class WindowBandpass : public FIR {

    private:

    double m_fc_low;
    double m_fc_high;

    /// @brief constructor default window WindowType::Rectangular
    /// @param fc_low lower cutoff frequency
    /// @param fc_high higher cutoff frequency
    /// @param size size of window
    WindowBandpass(double fc_low, double fc_high, size_t size);

    /// @brief constructor
    /// @param fc_low lower cutoff frequency
    /// @param fc_high higher cutoff frequency
    /// @param size size of window
    /// @param w_type window type WindowType
    WindowBandpass(double fc_low, double fc_high, size_t size, wnd::WindowType w_type);

    protected:

    /// @brief calculates coefficients
    /// @return void on success, FIRError on failure
    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    static std::expected <WindowBandpass, FIRError> create(double fc_low, double fc_high, size_t size);

    static std::expected <WindowBandpass, FIRError> create(double fc_low, double fc_high, size_t size, wnd::WindowType w_type);

};

}

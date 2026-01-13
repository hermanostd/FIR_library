#pragma once

#include "FIR.hpp"

namespace oh::fir{

/// @brief this class implements a highpass filter using window method
class WindowHighpass : public FIR {

    private:

    double m_fc;

    /// @brief constructor, default window type: WindowType::Rectangular
    /// @param fc cutoff frequency
    /// @param size size of window
    WindowHighpass(double fc, size_t size);

    /// @brief constructor
    /// @param fc cutoff frequency
    /// @param size size of window
    /// @param w_type window type WindowType
    WindowHighpass(double fc, size_t size, wnd::WindowType w_type);

    protected:

    /// @brief calulates coefficients
    /// @return void on success, FIRError on failure
    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    /// @brief creator, default window: WindowType::Rectangular
    /// @param fc cutoff frequency
    /// @param size size of filter
    /// @return WindowHighpass object on success, FIRError on failure
    static std::expected <WindowHighpass, FIRError> create(double fc, size_t size);
    
    /// @brief creator
    /// @param fc cutoff frequency
    /// @param size size of filter
    /// @param w_type type of window
    /// @return WindowHighpass object on success, FIRError on failure
    static std::expected <WindowHighpass, FIRError> create(double fc, size_t size, wnd::WindowType w_type);

};

}

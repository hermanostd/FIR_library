#pragma once

#include "FIR.hpp"

namespace oh::fir{

class WindowLowpass : public FIR {            

    private:

    double m_fc;

    WindowLowpass(double fc, size_t size);

    WindowLowpass(double fc, size_t size, wnd::WindowType w_type);

    protected:

    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    static std::expected <WindowLowpass, FIRError> create(double fc, size_t size);

};

}

#pragma once

#include "FIR.hpp"

namespace oh::fir {

class WindowBandpass : public FIR {

    private:

    double m_fc_low;
    double m_fc_high;

    WindowBandpass(double fc_low, double fc_high, size_t size);

    protected:

    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    static std::expected <WindowBandpass, FIRError> create(double fc_low, double fc_high, size_t size);

};

}

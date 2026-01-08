#pragma once

#include "FIR.hpp"

namespace oh::fir{

class Lowpass : public FIR {            

    private:

    double m_fc;

    Lowpass(double fc, size_t size);

    protected:

    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    static std::expected <Lowpass, FIRError> create(double fc, size_t size);

};

}

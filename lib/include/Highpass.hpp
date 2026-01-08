#pragma once

#include "FIR.hpp"

namespace oh::fir{

class Highpass : public FIR {

    private:

    double m_fc;

    Highpass(double fc, size_t size);

    protected:

    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    static std::expected <Highpass, FIRError> create(double fc, size_t size);                 

};

}

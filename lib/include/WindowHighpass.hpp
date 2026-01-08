#pragma once

#include "FIR.hpp"

namespace oh::fir{

class WindowHighpass : public FIR {

    private:

    double m_fc;

    WindowHighpass(double fc, size_t size);

    protected:

    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    static std::expected <WindowHighpass, FIRError> create(double fc, size_t size);                 

};

}

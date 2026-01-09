#pragma once

#include "FIR.hpp"

namespace oh::fir {

class FrequencySampling : public FIR{
    private:

    std::vector <double> m_half_frequency_spectrum;     

    FrequencySampling(const std::vector <double>& half_frequency_spectrum, size_t size);

    protected:

    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    static std::expected <FrequencySampling, FIRError> create(const std::vector <double>& half_frequency_spectrum);

    std::vector <double> getFrequencyHalfSpectrum();

};


}
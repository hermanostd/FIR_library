#include "FrequencySampling.hpp"

namespace oh::fir {

FrequencySampling::FrequencySampling(const std::vector<double>& half_frequency_spectrum, size_t size) : FIR(FIRType::FrequencySampling, size), m_half_frequency_spectrum(half_frequency_spectrum) {}

std::expected <void, FIRError> FrequencySampling::calculateCoefficients() {
    const size_t K = m_half_frequency_spectrum.size();
    const size_t N = 2 * K + 1;
    const double center = (N - 1) / 2.0;

    std::vector<double> h(N, 0.0);

    for (size_t n = 0; n < N; ++n) {
        double sum = m_half_frequency_spectrum[0];

        for (size_t k = 1; k < K; ++k) {
            sum += 2.0 * m_half_frequency_spectrum[k] * std::cos(2.0 * std::numbers::pi * k * (n - center) / N);
        }

        h[n] = sum / N;
    }
    
    if(auto w = setCoefficients(h); !w) {
        return std::unexpected(w.error());
    } else {
        return {};
    }
};


std::expected <FrequencySampling, FIRError> FrequencySampling::create(const std::vector <double>& half_frequency_spectrum) {
    const size_t size = 2 * half_frequency_spectrum.size() + 1;

    if(auto w = checkSize(size); !w) {          ///<    check size
        return std::unexpected(w.error());
    }
  
    FrequencySampling fs(half_frequency_spectrum, size);

    if(auto w = fs.calculateCoefficients(); !w) {
        return std::unexpected(w.error());
    }

    return fs;
}

std::vector<double> FrequencySampling::getFrequencyHalfSpectrum() {
    return m_half_frequency_spectrum;
}

}
#include "Lowpass.hpp"

namespace oh::fir {

Lowpass::Lowpass(double fc, size_t size) : FIR(FIRType::Lowpass, size), m_fc(fc) {}

std::expected <void, FIRError> Lowpass::calculateCoefficients() {            
    const size_t N = getSize();
    const double fc = m_fc;
    const double M = (N - 1) / 2.0f;

    std::vector <double> h(N);

    for (size_t n = 0; n < N; ++n) {
        double x = n - M;
        h[n] = 2.0 * fc * sinc(2.0 * fc * x);
    }

    if (auto w = setCoefficients(h); !w) {
        return std::unexpected(w.error());
    } else {
        return {};
    }

}


std::expected <Lowpass, FIRError> Lowpass::create(double fc, size_t size) {          
    if(auto w = checkSize(size); !w) {          
        return std::unexpected(w.error());
    }

    if (auto w = checkFrequencyRange(fc); !w) {          
        return std::unexpected(w.error());
    }

    Lowpass lp(fc, size);

    if(auto w = lp.calculateCoefficients(); !w) {
        return std::unexpected(w.error());
    } else {
        return lp;
    }

}

}

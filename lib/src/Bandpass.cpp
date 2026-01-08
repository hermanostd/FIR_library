#include "Bandpass.hpp"

namespace oh::fir{

Bandpass::Bandpass(double fc_low, double fc_high, size_t size) : FIR(FIRType::Bandpass, size), m_fc_low(fc_low), m_fc_high(fc_high) {}

std::expected <void, FIRError> Bandpass::calculateCoefficients() {            
    const size_t N = getSize();
    const double fl = m_fc_low;
    const double fh = m_fc_high;
    const double M = (N - 1) / 2.0f;

    std::vector<double> h(N);

    for (size_t n = 0; n < N; ++n) {
        double x = n - M;
        h[n] = 2.0 * fh * sinc(2.0 * fh * x)- 2.0 * fl * sinc(2.0 * fl * x);
    }

    if(auto w = setCoefficients(h); !w) {
        return std::unexpected(w.error());
    } else {
        return {};
    }

}

std::expected <Bandpass, FIRError> Bandpass::create(double fc_low, double fc_high, size_t size) {         
    if(auto w = checkSize(size); !w) {          
        return std::unexpected(w.error());
    }

    if (auto w = checkFrequencyRange(fc_low); !w) {          
        return std::unexpected(w.error());
    } else if (auto w = checkFrequencyRange(fc_high); !w) {
        return std::unexpected(w.error());
    }

    if (auto w = checkFrequencyOrder(fc_low, fc_high); !w) {          
        return std::unexpected(w.error());
    }

    Bandpass bp(fc_low, fc_high, size);

    if(auto w = bp.calculateCoefficients(); !w) {
        return std::unexpected(w.error());
    } else {
        return bp;
    }

}

}

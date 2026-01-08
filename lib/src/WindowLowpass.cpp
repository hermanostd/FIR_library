#include "WindowLowpass.hpp"

namespace oh::fir {

WindowLowpass::WindowLowpass(double fc, size_t size) : FIR(FIRType::WindowLowpass, size), m_fc(fc) {}

std::expected <void, FIRError> WindowLowpass::calculateCoefficients() {            
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


std::expected <WindowLowpass, FIRError> WindowLowpass::create(double fc, size_t size) {          
    if(auto w = checkSize(size); !w) {          
        return std::unexpected(w.error());
    }

    if (auto w = checkFrequencyRange(fc); !w) {          
        return std::unexpected(w.error());
    }

    WindowLowpass lp(fc, size);

    if(auto w = lp.calculateCoefficients(); !w) {
        return std::unexpected(w.error());
    } else {
        return lp;
    }

}

}

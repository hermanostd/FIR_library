#include "Highpass.hpp"

namespace oh::fir {

Highpass::Highpass(double fc, size_t size) : FIR(FIRType::Highpass, size), m_fc(fc) {}

std::expected <void, FIRError> Highpass::calculateCoefficients()  {            ///< calculator of coefficients
    const size_t N = getSize();
    const double fc = m_fc;
    const double M = (N - 1) / 2.0f;

    std::vector <double> h(N);

    for (size_t n = 0; n < N; ++n) {
        double x = n - M;
        h[n] = -2.0 * fc * sinc(2.0 * fc * x);
        if (n == static_cast <size_t> (M)) {        ///< cast double to size_t
            h[n] += 1.0;
        }
    }

    if(auto w = setCoefficients(h); !w) {
        return std::unexpected(w.error());
    } else {
        return {};
    }

}

std::expected <Highpass, FIRError> Highpass::create(double fc, size_t size) {         ///< initialiser, used to hide the constructor         
    if(auto w = checkSize(size); !w) {          ///< check size
        return std::unexpected(w.error());
    }

    if (auto w = checkFrequencyRange(fc); !w) {      ///< check frequency
        return std::unexpected(w.error());
    }

    Highpass hp(fc, size);

    if(auto w = hp.calculateCoefficients(); !w) {
        return std::unexpected(w.error());
    } else {
        return hp;
    }

}


}
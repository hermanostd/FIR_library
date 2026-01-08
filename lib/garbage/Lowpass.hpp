#pragma once

#include "FIR.hpp"

#include <cmath>
#include <vector>
#include <numbers>
#include <expected>

namespace oh {

namespace fir {

class Lowpass : public FIR {            ///< implementation of Lowpass FIR

    private:

    double m_fc;

    Lowpass(double fc, size_t size) : FIR(FIRType::Lowpass, size), m_fc(fc) {}

    protected:

    std::expected <void, FIRError> calculateCoefficients() override {            ///< calculator of coefficients
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

    public:

    static std::expected <Lowpass, FIRError> create(double fc, size_t size) {          ///< initialiser, used to hide the constructor
        if(auto w = checkSize(size); !w) {          ///< check size
            return std::unexpected(w.error());
        }

        if (auto w = checkFrequencyRange(fc); !w) {          ///< check frequency
            return std::unexpected(w.error());
        }

        Lowpass lp(fc, size);

        if(auto w = lp.calculateCoefficients(); !w) {
            return std::unexpected(w.error());
        } else {
            return lp;
        }

    }

};

}

}
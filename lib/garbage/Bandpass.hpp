#pragma once

#include "FIR.hpp"

#include <cmath>
#include <vector>
#include <numbers>
#include <expected>

namespace oh {

namespace fir {

class Bandpass : public FIR {           ///< implementation of Bandpass FIR

    private:

    double m_fc_low;
    double m_fc_high;

    Bandpass(double fc_low, double fc_high, size_t size) : FIR(FIRType::Bandpass, size), m_fc_low(fc_low), m_fc_high(fc_high) {}

    protected:

    std::expected <void, FIRError> calculateCoefficients() override {            ///< calculator of coefficients
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

    public:

    static std::expected <Bandpass, FIRError> create(double fc_low, double fc_high, size_t size) {         ///< initialiser, used to hide the constructor
        if(auto w = checkSize(size); !w) {          ///< check size
            return std::unexpected(w.error());
        }

        if (auto w = checkFrequencyRange(fc_low); !w) {          ///< check frequencies
            return std::unexpected(w.error());
        } else if (auto w = checkFrequencyRange(fc_high); !w) {
            return std::unexpected(w.error());
        }

        if (auto w = checkFrequencyOrder(fc_low, fc_high); !w) {          ///< check frequencies
            return std::unexpected(w.error());
        }

        Bandpass bp(fc_low, fc_high, size);

        if(auto w = bp.calculateCoefficients(); !w) {
            return std::unexpected(w.error());
        } else {
            return bp;
        }

    }

};

}

}
#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <numbers>
#include <expected>

namespace oh {

namespace fir{

enum class FIRType {        ///< Enum FIRType
    Lowpass,
    Highpass,
    Bandpass,
    Custom 
};

enum class FIRError {       ///< Enum FIRError
    InvalidSize,
    MismatchedSize,
    InvalidParameterValue,
    InvalidParameterOrder,
    NormalisationFailed
};

/******************************************************************************
 * FIR class, used as a template to create specialised FIR filters.
 * Once created, the filters can not be resized or modified. All setters and
 * non-private helpers must be of type std::expected and must return FIRError
 * on failure. Exceptions are not allowed, every class inheriting from FIR must
 * have a private constuctor, validation must be handled by the create() method.
 ******************************************************************************/

class FIR {         ///< FIR class, used as a template to create specialised FIR filters

    private:

    FIRType m_type;
    std::vector <double> m_coefficients;

    protected:

    static std::expected <void, FIRError> checkFrequencyRange(double fc) {            ///< helper for checking the frequency
        if(fc <= 0 || fc >= 0.5) {
            return std::unexpected(FIRError::InvalidParameterValue);
        } else {
            return {};
        }
    }

    static std::expected <void, FIRError> checkFrequencyOrder(double fc_low, double fc_high) {            ///< helper for checking the frequency
        if(fc_low >= fc_high) {
            return std::unexpected(FIRError::InvalidParameterOrder);
        } else {
            return {};
        }
    }

    static std::expected <void, FIRError> checkSize(size_t size) {          ///< helper for checking the size
        if(size == 0 || size % 2 == 0) {
            return std::unexpected(FIRError::InvalidSize);
        } else {
            return {};
        }
    }

    static double sinc(double x) {          ///< helper for calulating the sinc
        const double eps = 1e-12;
        if (std::abs(x) < eps)
            return 1.0;
        return std::sin(std::numbers::pi * x) / (std::numbers::pi * x);
    }

    FIR(FIRType type, size_t size)  : m_type(type), m_coefficients(size , 0.0) {}           ///< constuctor


    std::expected <void, FIRError> setCoefficients(const std::vector <double>& coefficients) {          ///< setter for coefficients of the filter 
        if (coefficients.size() != m_coefficients.size()) {
            return std::unexpected(FIRError::MismatchedSize);
        } else {
            m_coefficients = coefficients;
        }
        return {};
    }

    std::expected <void, FIRError> normaliseCoefficients() {            ///< normalise coefficients
        const double eps = 1e-12;
        double sum = 0.0f;

        for (auto& v : m_coefficients) {
            sum += v;
        }

        if (sum < eps) {
            return std::unexpected(FIRError::NormalisationFailed);
        } else {
            for (auto& v : m_coefficients) {
                v /= sum;
            }
        }
        
    }

    virtual std::expected <void, FIRError> calculateCoefficients()  = 0;         ///< pure virtual method, override it in inheriting classes

    public:

    const std::vector <double> & getCoefficients() const {           ///< getter for coefficients of the filter
            return m_coefficients;
    }

    const size_t getSize() const noexcept {            ///< getter for m_coefficients.size()
        return m_coefficients.size();
    }

    const FIRType getType() const noexcept {          ///< getter for m_type
        return m_type;
    }

    virtual ~FIR() = default;

};

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

class Highpass : public FIR {           ///< implementation of Highpass FIR

    private:

    double m_fc;

    Highpass(double fc, size_t size) : FIR(FIRType::Highpass, size), m_fc(fc) {}

    protected:

    std::expected <void, FIRError> calculateCoefficients() override {            ///< calculator of coefficients
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

    public:

    static std::expected <Highpass, FIRError> create(double fc, size_t size) {         ///< initialiser, used to hide the constructor         
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

};

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
#include "FIR.hpp"

namespace oh::fir{

FIR::FIR(FIRType type, size_t size)  : m_type(type), m_coefficients(size , 0.0) {} 

std::expected <void, FIRError> FIR::checkFrequencyRange(double fc) {           
    if(fc <= 0 || fc >= 0.5) {
        return std::unexpected(FIRError::InvalidParameterValue);
    } else {
        return {};
    }
}

std::expected <void, FIRError> FIR::checkFrequencyOrder(double fc_low, double fc_high) {            
    if(fc_low >= fc_high) {
         return std::unexpected(FIRError::InvalidParameterOrder);
    } else {
        return {};
    }
}

std::expected <void, FIRError> FIR::checkSize(size_t size) {          
    if(size == 0 || size % 2 == 0) {
        return std::unexpected(FIRError::InvalidSize);
    } else {
        return {};
    }
}

double FIR::sinc(double x) {          
    const double eps = 1e-12;
    if (std::abs(x) < eps) {
        return 1.0;
    } else {
        return std::sin(std::numbers::pi * x) / (std::numbers::pi * x);
    }
}

std::expected <void, FIRError> FIR::setCoefficients(const std::vector <double>& coefficients) {          
    if (coefficients.size() != m_coefficients.size()) {
        return std::unexpected(FIRError::MismatchedSize);
    } else {
        m_coefficients = coefficients;
    }
    return {};
}

std::expected <void, FIRError> FIR::normaliseCoefficients() {            
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
    return {};
}


const std::vector <double> & FIR::getCoefficients() const {           
        return m_coefficients;
}

size_t FIR::getSize() const noexcept {            
    return m_coefficients.size();
}

FIRType FIR::getType() const noexcept {          
    return m_type;
}


std::expected <std::vector<double>, FIRError> FIR::convolution(const std::vector<double>& signal) const {        
    const size_t N = signal.size();
    const size_t M = m_coefficients.size();

    if (N == 0 || M == 0) {
        return std::unexpected(FIRError::InvalidSize);
    }

    std::vector<double> w(N + M - 1, 0.0);

    for (size_t n = 0; n < N; ++n) {
        for (size_t m = 0; m < M; ++m) {
            w[n + m] += signal[n] * m_coefficients[m];
        }
    }

        return w;
}

std::expected <std::vector<double>, FIRError> FIR::convolutionOverride(std::vector<double>& signal) const {        
    if (auto w = convolution(signal); !w) {
        return std::unexpected(w.error());
    } else {
        signal = *w;
        return signal;
    }
}

}



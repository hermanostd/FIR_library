#pragma once

#include <cmath>
#include <vector>
#include <numbers>
#include <cstddef>
#include <expected>

namespace oh::fir {

enum class FIRType {        
    Lowpass,
    Highpass,
    Bandpass,
    Custom 
};

enum class FIRError {       
    InvalidSize,
    MismatchedSize,
    InvalidParameterValue,
    InvalidParameterOrder,
    NormalisationFailed
};


class FIR {     
    
    private:

    FIRType m_type;
    std::vector <double> m_coefficients;

    protected:

    static std::expected <void, FIRError> checkFrequencyRange(double fc);          

    static std::expected <void, FIRError> checkFrequencyOrder(double fc_low, double fc_high);            

    static std::expected <void, FIRError> checkSize(size_t size);          

    static double sinc(double x);         

    FIR(FIRType type, size_t size);      

    std::expected <void, FIRError> setCoefficients(const std::vector <double>& coefficients);

    std::expected <void, FIRError> normaliseCoefficients();

    virtual std::expected <void, FIRError> calculateCoefficients()  = 0;

    public:

    const std::vector <double> & getCoefficients() const;

    size_t getSize() const noexcept;

    FIRType getType() const noexcept;

    std::expected <std::vector<double>, FIRError> convolution(const std::vector<double>& signal) const;

    std::expected <std::vector<double>, FIRError> convolutionOverride(std::vector<double>& signal) const;

    virtual ~FIR() = default;

};

}



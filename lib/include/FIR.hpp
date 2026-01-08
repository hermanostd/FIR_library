#pragma once

#include <cmath>
#include <vector>
#include <numbers>
#include <cstddef>
#include <expected>
#include <string>


namespace oh::fir {

/// @brief enum used to represent filter type
enum class FIRType {        
    WindowLowpass,
    WindowHighpass,
    WindowBandpass,
    FrequencySampling
};

/// @brief enum used for error handling
enum class FIRError {       
    InvalidSize,
    MismatchedSize,
    InvalidParameterValue,
    InvalidParameterOrder,
    NormalisationFailed
};

///<    debugging and error handling

/// @brief used to translate FIRError to std::string
/// @param fir_error 
/// @return string
std::string toString(oh::fir::FIRError fir_error);

/// @brief used to translate FIRType to std::string
/// @param fir_type 
/// @return string
std::string toString(oh::fir::FIRType fir_type);



/// @brief a class used as a template to implement more specific FIR filters
class FIR {     
    
    private:

    /// @brief stores the type of filter
    FIRType m_type;


    /// @brief stores the coefficients of the filter
    std::vector <double> m_coefficients;

    protected:

    ///<    these methods handle validation, they can be reused in create() method in inheriting functions

    /// @brief helper to check if the frequency is valid
    /// @param fc normalised cutoff frequency
    /// @return void on success, FIRError on failure
    static std::expected <void, FIRError> checkFrequencyRange(double fc);          

    /// @brief helper to check if frequency was provided in a right order(for filters with two cutoff frequencies)
    /// @param fc_low lower cutoff frequency
    /// @param fc_high higher cutoff frequency
    /// @return void on success, FIRError on failure
    static std::expected <void, FIRError> checkFrequencyOrder(double fc_low, double fc_high);            

    /// @brief helper used to check if the entered size is nonzero and odd
    /// @param size size of the desired filter (order+1)
    /// @return void on success, FIRError on failure
    static std::expected <void, FIRError> checkSize(size_t size);
    
    ///<    misc

    /// @brief returns normalised sinc, usefull in implementing FIRs
    /// @param x argument of sinc(x)
    /// @return value of sin(pi*x)/(pi*x)
    static double sinc(double x);

    ///<    constructor

    /// @brief protected consturctor, validation must be handled by create()
    /// @param type type of filter FIRType
    /// @param size size of filter
    FIR(FIRType type, size_t size);      


    /// @brief protected setter for coefficients
    /// @param coefficients the coefficients to be set
    /// @return void on success, FIRError on failure
    std::expected <void, FIRError> setCoefficients(const std::vector <double>& coefficients);

    /// @brief used to normalise the dc gain for some filters(currently not used)
    /// @return void on success, FIRError on failure
    std::expected <void, FIRError> normaliseCoefficients();


    /// @brief pure virtual method used to calculate coefficients, override it in inheriting classes
    /// @return void on success, FIRError on failure
    virtual std::expected <void, FIRError> calculateCoefficients()  = 0;

    public:

    ///<    getters

    /// @brief getter for coefficients
    /// @return m_coefficients
    const std::vector <double>& getCoefficients() const;


    /// @brief getter for size
    /// @return size of m_coefficients
    size_t getSize() const noexcept;

    /// @brief getter for type
    /// @return type of filter
    FIRType getType() const noexcept;

    ///<    calulating the convlution

    /// @brief calulates the convolution of signal with the filter
    /// @param signal input signal
    /// @return vector containing convluted signal(copy)
    std::expected <std::vector<double>, FIRError> convolve(const std::vector<double>& signal) const;

    /// @brief calulates the convolution of signal with the filter
    /// @param signal input signal
    /// @return vector containing convluted signal(overriden)
    std::expected <std::vector<double>, FIRError> convolveInPlace(std::vector<double>& signal) const;

    /// @brief destructor
    virtual ~FIR() = default;

};

}



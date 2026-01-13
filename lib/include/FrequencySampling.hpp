#pragma once

#include "FIR.hpp"

namespace oh::fir {

/// @brief a fir filter generated using frequency sampling method
class FrequencySampling : public FIR{
    private:

    /// @brief stores half requency spectrum
    std::vector <double> m_half_frequency_spectrum;     

    /// @brief constructor, default window type WindowType::Rectangular
    /// @param half_frequency_spectrum half frequency spectrum
    /// @param size size of filter
    FrequencySampling(const std::vector <double>& half_frequency_spectrum, size_t size);

    /// @brief constructor
    /// @param half_frequency_spectrum half frequency spectrum
    /// @param size size of filter
    /// @param w_type type of window
    FrequencySampling(const std::vector <double>& half_frequency_spectrum, size_t size, wnd::WindowType w_type);

    protected:

    /// @brief calculates coefficients of FIR filter
    /// @return void on success, FIRError on failure
    std::expected <void, FIRError> calculateCoefficients() override;

    public:

    /// @brief creates an FrequencySampling object
    /// @param half_frequency_spectrum half frequency spectrum
    /// @return FrequencySampling object on success, FIRError on failure
    static std::expected <FrequencySampling, FIRError> create(const std::vector <double>& half_frequency_spectrum);

    /// @brief getter for Half Frequency Spectrum
    /// @return m_half_frequency_spectrum
    std::vector <double> getFrequencyHalfSpectrum();

};


}
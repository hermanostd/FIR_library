#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <numbers>
#include <stdexcept>
#include <expected>

namespace oh {

namespace window {

/******************************************************************************
 * WindowType enum, used to select a window type. If you want to expand this
 * library by including your own parametric window, add its name in this enum.
 * To do: remake using std::expected
 ******************************************************************************/

enum class WindowType {
    Rectangular,
    Hamming,
    Hanning,
    Blackman,
    Custom 
};

 
/******************************************************************************
 * Window class, used as a template to implement specific windows. Coefficients
 * of the window are stored in a private variable of type vector <double>
 * named m_coefficients. The coefficients can be read using getCoefficients() 
 * method. Only objects of the inheriting class: CustomWindow can have their
 * coefficients modified directly. getCoefficients() methode ensures that no
 * outdated data is provided to the user.
 ******************************************************************************/

class Window{

    private:

    std::vector <double> m_coefficients;    
    WindowType m_type;

    protected:

    static constexpr double m_pi = std::numbers::pi_v<double>;

 /******************************************************************************
 * AutoRecalc is a feature implemented to prevent modifying the size of the
 * window without recalculating the coefficients. It can be disabled with
 * setAutoRecalc() method. The state of the AutoRecalc feature can be
 * checked with getAutoRecalc(). If you wish to include your own window,
 * with "hot-tweakable" variables, make sure to implement this feature.
 ******************************************************************************/

    bool p_auto_recalc = true;
    bool p_outdated;        ///< keeps track of modifications

    void p_checkSize(size_t size) {
        if (size < 1) {
            throw std::runtime_error("Error, the size of the window can't be lower than 1");
        } else if (m_type != WindowType::Rectangular && m_type != WindowType::Custom && size < 2) {
            throw std::runtime_error("Error, the size of the window can't be lower than 2 for windows other than Custom or Rectangular");
        }
    }

    Window(WindowType type, size_t size) : m_coefficients(size), m_type(type), p_outdated(true) {     ///< constructor
        p_checkSize(size);
    }

    void p_setCoefficients(const std::vector <double>& coefficients) {      ///< used to set coefificients inside the m_coefficients vector
        if (coefficients.size() != m_coefficients.size()) {
            throw std::runtime_error("Error, can't set the coefficients, target size mismatched");
        } else {
            m_coefficients = coefficients;
            p_outdated = false;
        }
    }

 /******************************************************************************
 * Pure virtual method for generating coefficients, if you wish to create your
 * own, procedural window, make sure to override this method.
 ******************************************************************************/

    virtual void p_generateCoefficients() = 0;  

    virtual ~Window() = default;    ///< destrucor

    public:

 /******************************************************************************
 * Method used to get current window coefficients, returns unexpected, when
 * coefficients of WindowType Custom are outdated, for other cases, 
 * automatically regenerates the coefficients if outdated.
 ******************************************************************************/

    const std::expected <std::vector <double>&, std::string> getCoefficients() noexcept {     
        if(p_outdated) {
            if(m_type == WindowType::Custom) {
                return std::unexpected("Error, the coefficients in the WindowType:Custom are outdated");
            }
            p_generateCoefficients();       ///< regenerate when the data is outdated
        }
        return m_coefficients;
    }

    WindowType getType() const noexcept{    ///< returns WindowType enum
        return m_type;
    }

    size_t getSize() const noexcept{    ///< returns the size of window
        return m_coefficients.size();
    }

    bool getAutoRecalc() const noexcept{    ///< returns true if the AutoRecalc is turned on
        return p_auto_recalc;
    }

    bool isOutdated() const noexcept{
        return p_outdated;
    }

    void setSize(size_t size) {  ///< setting the new size of window
        p_checkSize(size);
        auto copy = m_coefficients;
        m_coefficients.resize(size);

        try {
        if (p_auto_recalc && m_type != WindowType::Custom) {
            p_generateCoefficients();
        } else {
            p_outdated = true;
        }
        } catch (...) {
            m_coefficients = std::move(copy);
            throw;
        } 
    }

    void regenerate() {     ///< regenerates coefficients when outdated
        if(p_outdated && m_type != WindowType::Custom) {
            p_generateCoefficients();
        }
    }

/******************************************************************************
 * enabling/disabling the AutoRecalc feature, enabling it autamtically
 * regenerates the new coefficients, disabling it does NOT regenerate
 * the coefficients.
 ******************************************************************************/

    void setAutoRecalc(bool f) {    
        p_auto_recalc = f;
        if (f) {
            regenerate();
        }
    }

};

class RectangularWindow : public Window {

    public:
    
    RectangularWindow(size_t size) : Window(WindowType::Rectangular, size) {
        p_generateCoefficients(); 
    }

    void p_generateCoefficients() override {
        std::vector <double> coefficients(getSize(), 1);
        p_setCoefficients(coefficients);
    }

};

 /******************************************************************************
 * This is a class used to implement non-procedural windows, the coefficients
 * can be set by using the setCoefficients() method. Coefficients must be set 
 * again after resising.
 ******************************************************************************/

class CustomWindow : public Window {

    private:

    std::string m_name;     ///< used to store the name of the window

    public:

    CustomWindow(size_t size, std::string name) :  Window(WindowType::Custom, size), m_name(name) {}    ///<constructor

    CustomWindow(size_t size, std::string name, std::vector <double> coefficients) : Window(WindowType::Custom, size), m_name(name) {   ///<constructor, sets coefficients
        p_setCoefficients(coefficients);
    }

    void setCoefficients(const std::vector <double>& coefficients) {    ///< sets coefficients, make sure to set them again after resizing
        p_setCoefficients(coefficients);
    }

    void p_generateCoefficients() override final {}      ///< this window doesn't have a procedural generation    

    void setName(std::string name) {        ///< sets the name of the window
        m_name = name;
    }

    const std::string& getName() const{       ///< returns the name of the window
        return m_name;
    }
    
};

class HammingWindow : public Window {       ///< implementation of Hamming window

    private:

    double m_a = 0.54;
    double m_b = 0.46;

    protected:

    void p_setHammingCoefficients(double a, double b) {
        constexpr double eps = 1e-12;
        if ((std::abs(a + b - 1.0)) < eps) {
            if((a > 0) && (b > 0)) {
                m_a = a;
                m_b = b;
            } else {
                throw std::runtime_error("Error, the coefficients must be greater than 0");
            }
        } else {
            throw std::runtime_error("Error, the custom coefficients must add up to 1.0");
        }
    }

    public:

    HammingWindow(size_t size) : Window(WindowType::Hamming, size) {        ///< constructor
        p_generateCoefficients();
    }

    void p_generateCoefficients() override {
        const size_t size = getSize();
        std::vector <double> coefficients(size);
        for (size_t n = 0; n < size; n++) {
            coefficients[n] = m_a - m_b * std::cos(2.0 * m_pi * n / (size - 1));
        }
        p_setCoefficients(coefficients);
    }
    

};

class HanningWindow : public Window {       ///< implementation of Hanning window

    public:

    HanningWindow(size_t size) : Window(WindowType::Hanning, size) {        ///< constructor
        p_generateCoefficients();
    }

    void p_generateCoefficients() override {
        const size_t size = getSize();
        std::vector <double> coefficients(size);
        for (size_t n = 0; n < size; n++) {
            coefficients[n] = 0.5 * (1.0 - std::cos(2.0 * m_pi * n / (size - 1)));
        }
        p_setCoefficients(coefficients);
    }

};

class BlackmanWindow : public Window {      ///< implementation of Blackman window

    double m_a = 0.42;
    double m_b = 0.50;
    double m_c = 0.08;

    protected:

    void p_setBlackmanCoefficients(double a, double b, double c) {
        constexpr double eps = 1e-12;
        if (std::abs(a + b + c - 1 ) < eps) {
            if ((a > 0) && (b > 0) && (c > 0)) {
                m_a = a;
                m_b = b;
                m_c = c;
            } else {
                throw std::runtime_error("Error, the coefficients must be greater than 0");
            }
        } else {
            throw std::runtime_error("Error, the custom coefficients must add up to 1.0");
        }
    }

    public:

    BlackmanWindow(size_t size) : Window(WindowType::Blackman, size) {          ///< constructor
        p_generateCoefficients();
    }

    void p_generateCoefficients() override {
        const size_t size = getSize();
        std::vector <double> coefficients(size);
        const double denominator = size - 1;
        for (size_t n = 0; n < size; ++n) {
            const double x = 2.0 * m_pi * n / denominator;
            coefficients[n] = m_a - m_b * std::cos(x) + m_c * std::cos(2.0 * x);
        }
        p_setCoefficients(coefficients);
    }
    
};

 /******************************************************************************
 * This class can be used to tweak the parameters of the HammingWindow
 ******************************************************************************/

class HammingWindowCustom : public HammingWindow {
    
    public:

    HammingWindowCustom(size_t size) : HammingWindow(size) {}

    HammingWindowCustom(size_t size, double a, double b) : HammingWindow(size) {    ///< constructor, allows you to set custom coefficients (a and b)
        p_setHammingCoefficients(a, b);
        p_generateCoefficients();
    }

    void setHammingCoefficients(double a, double b) {   ///< set custom coefficients
        p_setHammingCoefficients(a, b);
        if (p_auto_recalc) {
            p_generateCoefficients();
        } else {
            p_outdated = true;
        }
    }
    
};

 /******************************************************************************
 * This class can be used to tweak the parameters of the BlackmanWindow
 ******************************************************************************/

class BlackmanWindowCustom : public BlackmanWindow {

    public:

    BlackmanWindowCustom(size_t size) : BlackmanWindow(size) {}     ///< constructor

    BlackmanWindowCustom(size_t size, double a, double b, double c) : BlackmanWindow(size) {    ///< constructor, allows you to set custom coefficients (a, b and c)
        p_setBlackmanCoefficients(a, b, c);
        p_generateCoefficients();
    }

    void setBlackmanCoefficients(double a, double b, double c) {        ///< set custom coefficients
        p_setBlackmanCoefficients(a, b, c);
        if (p_auto_recalc) {
            p_generateCoefficients();
        } else {
            p_outdated = true;
        }
    }
    
};

}

}
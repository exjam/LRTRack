#pragma once

#include "DSPSystem.hpp"
#include "DSPMath.hpp"

namespace dsp {


    /**
     * @brief
     */
    struct MS20TPT : DSPSystem2x1 {
        float s;
        DSPDelay1 z;


        void process() override {
            float gx = input[IN1].value * input[IN2].value;

            z.set(gx + z.get() + gx);
            s = z.get();
        }
    };


    /**
     * @brief Zero Delay Feedback
     */
    struct MS20ZDF : DSPSystem2x2 {
        float y;
        float s;
        MS20TPT tpt;


        void process() override {
            y = input[IN1].value * input[IN2].value + s;

            tpt.set(input[IN1].value - y, input[IN2].value);
            s = tpt.s;
        }

    };


    /**
     * @brief MS20 Filter class
     */
    struct MS20zdf : DSPSystem<1, 2, 3> {
        static const int OVERSAMPLE = 8;                // factor of internal oversampling
        static constexpr float DRIVE_GAIN = 20.f;       // max drive gain

        enum Inputs {
            IN
        };

        enum Params {
            FREQUENCY,
            PEAK,
            DRIVE
        };

        enum Outputs {
            LOWPASS,
            HIGHPASS
        };

    private:
        float g, g2, b, k;
        float ky, y;
        float freqHz;

        MS20ZDF zdf1, zdf2;
        OverSampler<OVERSAMPLE, 1> os;

    public:
        explicit MS20zdf(float sr);


        float getFrequency() {
            return getParam(FREQUENCY);
        }


        float getFrequencyHz() const {
            return freqHz;
        }


        void setFrequency(float value) {
            setParam(FREQUENCY, value);
        }


        void setDrive(float value) {
            setParam(DRIVE, value);
        }


        float getDrive() {
            return getParam(DRIVE);
        }


        float getPeak() {
            return getParam(PEAK);
        }


        void setPeak(float value) {
            setParam(PEAK, value);
        }


        void setIn(float value) {
            setInput(IN, value);
        }


        float getHPOut() {
            return getOutput(HIGHPASS);
        }


        float getLPOut() {
            return getOutput(LOWPASS);
        }


        void invalidate() override;
        void process() override;
    };


}
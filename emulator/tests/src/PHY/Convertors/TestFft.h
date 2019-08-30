#ifndef PHY_CONVERTORS_FFT_H
#define PHY_CONVERTORS_FFT_H

#include <gtest/gtest.h>
#include <complex>
#include <cmath>
#include <Fft.h>

const double PI = 3.14159265358979323846;

namespace TestRadio80211ah
{
    TEST(Fft, TimeToFrequencyDomainConversion)   // Reverse
    {
        const size_t samplingFrequency = 1000;
        const size_t numberOfSamples = samplingFrequency + 24;

        const size_t sinusoidFrequency1 = 30;
        const size_t sinusoidFrequency2 = 40;
        const size_t sinusoidFrequency3 = 70;

        size_t sampleIndex = 0;
        double t = 0.0;

        std::vector<std::complex<double>> inputData(numberOfSamples);
        std::vector<std::complex<double>> originalInputData(numberOfSamples);

        std::for_each(inputData.begin(), inputData.end(), [&sampleIndex, &t, samplingFrequency, sinusoidFrequency1, sinusoidFrequency2, sinusoidFrequency3](std::complex<double>& sample)
        {
            if (sampleIndex < samplingFrequency)
            {
                sample = std::complex<double>(
                    cos(static_cast<double>(sinusoidFrequency1) * ((2.0 * PI) * t)) +
                    cos(static_cast<double>(sinusoidFrequency2) * ((2.0 * PI) * t)) +
                    cos(static_cast<double>(sinusoidFrequency3) * ((2.0 * PI) * t)),

                    sin(static_cast<double>(sinusoidFrequency1) * ((2.0 * PI) * t)) +
                    sin(static_cast<double>(sinusoidFrequency2) * ((2.0 * PI) * t)) +
                    sin(static_cast<double>(sinusoidFrequency3) * ((2.0 * PI) * t)));

                ++sampleIndex;
                t += (1.0 / static_cast<double>(samplingFrequency));
            }
            else
                sample = std::complex<double>(0.0, 0.0);
        });

        originalInputData = inputData;

        Radio80211ah::Fft fft;
        fft.Transform(inputData, true, true);
        fft.Transform(inputData, false, true);

        for (size_t i = 0; i < numberOfSamples; ++i)
        {
            const double tolerance = 0.0000001;
            const std::complex<double> temp = inputData[i] - originalInputData[i];

            ASSERT_TRUE(temp.real() < tolerance && temp.imag() < tolerance);
        }
    }

    TEST(Fft, FrequencyToTimeDomainConversion)  // Direct
    {
        const size_t samplingFrequency = 8;
        const size_t numberOfSamples = samplingFrequency;

        const size_t sinusoidFrequency1 = 2; // 2Hz
        const size_t sinusoidFrequency2 = 3; // 3Hz

        std::vector<std::complex<double>> frequencyToTimeDomain;
        std::vector<std::complex<double>> timeDomain;

        frequencyToTimeDomain.push_back(std::complex<double>(0.0, 0.0)); // 0Hz
        frequencyToTimeDomain.push_back(std::complex<double>(0.0, 0.0)); // 1Hz

        frequencyToTimeDomain.push_back(std::complex<double>(1.0 * static_cast<double>(samplingFrequency), 0.0)); // 2Hz (Spike), �������� �� ������� �������������, ��� ���, ifft ���� ������ � ����������������� ����
        frequencyToTimeDomain.push_back(std::complex<double>(1.0 * static_cast<double>(samplingFrequency), 0.0)); // 3Hz (Spike), �������� �� ������� �������������, ��� ���, ifft ���� ������ � ����������������� ����

        frequencyToTimeDomain.push_back(std::complex<double>(0.0, 0.0)); // 4Hz
        frequencyToTimeDomain.push_back(std::complex<double>(0.0, 0.0)); // 5Hz
        frequencyToTimeDomain.push_back(std::complex<double>(0.0, 0.0)); // 6Hz
        frequencyToTimeDomain.push_back(std::complex<double>(0.0, 0.0)); // 7Hz

        Radio80211ah::Fft fft;
        fft.Transform(frequencyToTimeDomain, false, true); // �������� �������������� (ifft)

        double t = 0.0;

        for (size_t i = 0; i < 8; ++i)
        {
            timeDomain.push_back(std::complex<double>(
                cos(static_cast<double>(sinusoidFrequency1) * ((2.0 * PI) * t)) +
                cos(static_cast<double>(sinusoidFrequency2) * ((2.0 * PI) * t)),

                sin(static_cast<double>(sinusoidFrequency1) * ((2.0 * PI) * t)) +
                sin(static_cast<double>(sinusoidFrequency2) * ((2.0 * PI) * t))));

            t += (1.0 / static_cast<double>(samplingFrequency));
        }

        for (size_t s = 0; s < numberOfSamples; ++s)
        {
            const double tolerance = 0.0000001;
            const std::complex<double> temp = frequencyToTimeDomain[s] - timeDomain[s];

            ASSERT_TRUE(temp.real() < tolerance && temp.imag() < tolerance);
        }
    }
}

#endif

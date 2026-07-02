
#pragma once

#include <QString>

class HealthMetricsService
{
public:
    // Body Mass Index
    static double calculateBMI(double weightKg,
                               int heightCm);

    // BMI Interpretation
    static QString calculateBMIAnalysis(double bmi);

    // Basal Metabolic Rate (Mifflin-St Jeor)
    static double calculateBMR(double weightKg,
                               int heightCm,
                               int age,
                               const QString &gender);

    // Body Surface Area (Mosteller)
    static double calculateBSA(double weightKg,
                               int heightCm);
};
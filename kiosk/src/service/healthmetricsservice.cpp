
/*
This implementation follows standard clinical formulas:

BMI: World Health Organization (WHO) definition.
BMI Analysis: WHO BMI classification.
BMR: Mifflin–St Jeor equation (widely used in clinical nutrition).
BSA: Mosteller formula (commonly used for medication dosing and clinical calculations).
*/

#include "service/healthmetricsservice.h"

#include <cmath>

/* ==========================================================
 * BMI
 * Formula:
 * BMI = Weight(kg) / Height(m)^2
 * ==========================================================*/

double HealthMetricsService::calculateBMI(
        double weightKg,
        int heightCm)
{
    if (weightKg <= 0 || heightCm <= 0)
        return 0.0;

    double heightMeters =
            heightCm / 100.0;

    return weightKg /
           (heightMeters * heightMeters);
}

/* ==========================================================
 * BMI Analysis
 * WHO Classification
 * ==========================================================*/

QString HealthMetricsService::calculateBMIAnalysis(
        double bmi)
{
    if (bmi <= 0)
        return "--";

    if (bmi < 18.5)
        return "Underweight";

    if (bmi < 25.0)
        return "Normal";

    if (bmi < 30.0)
        return "Overweight";

    if (bmi < 35.0)
        return "Obesity Class I";

    if (bmi < 40.0)
        return "Obesity Class II";

    return "Obesity Class III";
}

/* ==========================================================
 * BMR
 * Mifflin-St Jeor Equation
 *
 * Male:
 * 10W + 6.25H - 5A + 5
 *
 * Female:
 * 10W + 6.25H - 5A -161
 * ==========================================================*/

double HealthMetricsService::calculateBMR(
        double weightKg,
        int heightCm,
        int age,
        const QString &gender)
{
    if (weightKg <= 0 ||
        heightCm <= 0 ||
        age <= 0)
    {
        return 0.0;
    }

    if (gender.compare(
            "Male",
            Qt::CaseInsensitive) == 0)
    {
        return (10.0 * weightKg)
             + (6.25 * heightCm)
             - (5.0 * age)
             + 5.0;
    }

    return (10.0 * weightKg)
         + (6.25 * heightCm)
         - (5.0 * age)
         - 161.0;
}

/* ==========================================================
 * BSA
 * Mosteller Formula
 *
 * sqrt(height(cm) * weight(kg) / 3600)
 * ==========================================================*/

double HealthMetricsService::calculateBSA(
        double weightKg,
        int heightCm)
{
    if (weightKg <= 0 ||
        heightCm <= 0)
    {
        return 0.0;
    }

    return std::sqrt(
            (heightCm * weightKg) /
            3600.0);
}
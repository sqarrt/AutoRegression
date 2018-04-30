#ifndef AUTOREGRESSION_H
#define AUTOREGRESSION_H

#include "autoregression_global.h"
#include <QList>

class AUTOREGRESSIONSHARED_EXPORT AutoRegression
{

public:
    AutoRegression();
    AutoRegression(const QList<double> &values, int grade, int predictionLength);
    void setRatios(const QList<double> &ratios);
    double get(int t);
    QList<double>& getResults();

private:
    QList<double> values;
    QList<QList<double>> M;
    QList<double> ratios;
    int grade;
    int predictionLength;
    QList<double> learnSelect;
    QList<double> predictionSelect;
    QList<double> testSelect;
    double calcM(int a,int b);
    double get(int t,QList<double> &set);
    void fillMatrix();
    void fillRatios();
    void fillPredictionSelect();
    double getDelta();

};

#endif // AUTOREGRESSION_H

/*
 * @author Shatalov Dmitry
 * @version 1.0
 */

#include "autoregression.h"


AutoRegression::AutoRegression()
{
    this->grade = 0;
    this->predictionLength = 0;
}

/*
 * @param &values - list of values from select
 * @param grade - power of autoregession
 * @param predictLength - count of predicted X's after select
 */
AutoRegression::AutoRegression(const QList<double> &values, int grade, int predictionLength)
{
    /*
     * @param half - divides selection by halfs on test selection and learn selection
     */
    int half = std::ceil(values.size()/2);
    if(half > grade)
    {
        this->values = values;
        this->grade = grade;
        this->predictionLength = predictionLength;

        for(int i = 0; i < this->values.size() ; i++ )
        {
            if(i<=half)
            {
                this->learnSelect.append(values[i]);
            }
            else
            {
                this->testSelect.append(values[i]);
            }
        }
    };
}

QList<double>& AutoRegression::getResults()
{
    QList<double> result;
    result.append(this->values);
    this->fillMatrix();
    this->fillRatios();
    for(int i = 0; i < this->predictionLength; i ++)
    {
        result.append(get(result.size(),result));
    }
    return result;
}

/*
 * @param a - rownumber in matrix
 * @param b - cellnumber at row
 */
double AutoRegression::calcM(int a, int b)
{
    double sum = 0.0;
    /*
     * TODO: Выяснить границы суммирования, пока оставить так
     */
    for(int t = 0 ; t < this->grade; t ++ )
    {
        sum+=learnSelect[t-a]*learnSelect[t-b];
    }
    return sum;
}

/*
 * calculating and filleng matrix
 */
void AutoRegression::fillMatrix()
{
    for(int i = 0; i < this->predictionLength ; i ++ )
    {
        QList<double> temp;
        for(int j = 0; j < this->predictionLength; j ++ )
        {
            temp.append(this->calcM(i,j));
        }
        this->M.append(temp);
    }
}

/*
 * solving the @param this->M matrix
 * and filling @param this->ratios with answers
 */
void AutoRegression::fillRatios()
{
    /*
     * TODO: описать метод Гаусса, заполнять this->ratios
     */
}

/*
 * public method for access to elements
 */
double AutoRegression::get(int t)
{
    /*
     * checking if this element is already set
     */
    if(t<this->values.size())
    {
        return values[t];
    }
    /*
     * if element is empty, trying to get previous element
     */
    else if(t-1<this->values.size())
    {
        double sum = 0.0;
        for(int i = 0; i < this->grade ; i ++)
        {
            sum+=ratios[i]*values[t-i];
        }
        return sum;
    }
    /*
     * if previous element is empty - throwing Runtime Exception
     */
    else
    {
        throw std::runtime_error("Cannot get element : out of range");
    }
}

/*
 * private method for access to specified set element
 */
double AutoRegression::get(int t, QList<double> &set)
{
    /*
     * checking if this element is already set
     */
    if(t<set.size())
    {
        return set[t];
    }
    /*
     * if element is empty, trying to get previous element
     */
    else if(t-1<set.size())
    {
        double sum = 0.0;
        for(int i = 0; i < this->grade ; i ++)
        {
            sum+=ratios[i]*set[t-i];
        }
        return sum;
    }
    /*
     * if previous element is empty - throwing Runtime Exception
     */
    else
    {
        throw std::runtime_error("Cannot get element : out of range");
    }
}

void AutoRegression::fillPredictionSelect()
{
    this->predictionSelect.clear();
    this->predictionSelect.append(this->learnSelect);
    for(int i = 0; i < this->testSelect.size(); i ++)
    {
        this->predictionSelect.append(get(this->learnSelect.size()+i,this->predictionSelect));
    }
}

double AutoRegression::getDelta()
{
    double sum = 0.0;
    for(int i = 0; i< this->testSelect.size(); i ++)
    {
        sum+=pow(this->predictionSelect[i]-this->testSelect[i],2);
    }
    return sum;
}


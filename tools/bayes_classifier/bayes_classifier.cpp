#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string.h>

#include <boost/tokenizer.hpp>

using namespace std;


struct Item
{
    int id;
    int cls;
    vector<double> values;
};

struct Parameter
{
    double mean;
    double variance;
    vector<double> values;
};

struct Cls
{
    int cls;
    vector<Parameter> params;
};

typedef map<int, Cls> ClassesMapType;
ClassesMapType classes;


double calcMean(vector<double> values)
{
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}


double calcVariance(vector<double> values, double mean)
{
    double sum = 0.0;

    for (size_t i = 0; i < values.size(); ++i)
    {
        sum += (values[i] - mean) * (values[i] - mean);
    }

    return sum / values.size();
}


double calcProbability(double x, double mean, double variance)
{
    double part1 = 1.0 / sqrt(2.0 * M_PI * variance);

    double part2 = exp(- (x - mean) * (x - mean) / (2.0 * variance));

    return part1 * part2;
}


double classBelongProbability(Cls &cls, Item &item)
{
    double result = 1.0;

    for (size_t i = 0; i < cls.params.size(); ++i)
    {
        double prob = calcProbability(item.values[i], cls.params[i].mean, cls.params[i].variance);
        result *= prob;
    }

    return result;
}


int makePrediction(Item &item)
{
    double curMax = 0.0;
    int clsId = -1;

    for (ClassesMapType::value_type &p : classes)
    {
        Cls &cls = p.second;

        double prob = classBelongProbability(cls, item);

        if (prob > curMax)
        {
            curMax = prob;
            clsId = p.first;
        }
    }

    return clsId;
}


bool readItem(std::string line, vector<Item> &items, bool withClass)
{
    boost::char_separator<char> sep(",");
    typedef boost::tokenizer<boost::char_separator<char>> TokenizerType;
    TokenizerType tok(line, sep);

    Item item;

    int col = 0;
    for (TokenizerType::iterator beg = tok.begin(); beg != tok.end(); ++beg, ++col)
    {
        switch (col)
        {
        case 0:
            item.id = atoi((*beg).c_str());
            break;
        case 1:
            if (withClass)
            {
                item.cls = atoi((*beg).c_str());
            }
            else
            {
                item.values.push_back(atoi((*beg).c_str()));
                ++col;
            }
            break;
        case 2:
        case 4:
            item.values.push_back(atoi((*beg).c_str()));
            break;
        case 3:
            if (*beg == "male")
            {
                item.values.push_back(1);
            }
            else
            {
                item.values.push_back(2);
            }
            break;
        }
    }

    while (item.values.size() < 3)
    {
        item.values.push_back(0);
    }

    if (col >= 3)
    {
        items.push_back(item);
    }

    return true;
}


bool prepareClasses(vector<Item> items)
{
    classes.clear();

    for (Item &item : items)
    {
        Cls &cls = classes[item.cls];

        if (cls.params.size() == 0)
        {
            for (int i = 0; i < 3; ++i)
            {
                cls.params.push_back(Parameter());
            }
        }

        for (int i = 0; i < 3; ++i)
        {
            cls.params[i].values.push_back(item.values[i]);
        }
    }

    return true;
}


bool calcMeanVariance()
{
    for (ClassesMapType::value_type &p : classes)
    {
        for (Parameter &param : p.second.params)
        {
            vector<double> noEmptyValues;
            for (double x : param.values)
            {
                if (x > 0.0) noEmptyValues.push_back(x);
            }

            param.mean = calcMean(noEmptyValues);

            for (size_t i = 0; i < param.values.size(); ++i)
            {
                if (param.values[i] == 0)
                {
                    param.values[i] = param.mean;
                }
            }

            param.variance = calcVariance(param.values, param.mean);
        }
    }

    return true;
}


bool readFile(const char *fileName, vector<Item> &allItems, bool readClass)
{
    std::ifstream input(fileName);

    string line;

    bool header = true;

    while (getline(input, line))
    {
        if (header)
        {
            header = false;
            continue;
        }

        if (!readItem(line, allItems, readClass))
        {
            return -1;
        }
    }

    return true;
}


int main(int argc, char *argv[])
{
    vector<Item> trainItems;

    readFile("./train_prepared.csv", trainItems, true);

    prepareClasses(trainItems);

    calcMeanVariance();

    if (argc > 1 && strcmp(argv[1], "train") == 0)
    {
        int predictOk = 0;

        for (Item &it : trainItems)
        {
            int predictedClass = makePrediction(it);
            if (predictedClass == it.cls)
            {
                ++predictOk;
            }
        }

        cout << "train data right prediction rate: " << (double)predictOk / trainItems.size() << endl;
    }
    else
    {
        vector<Item> testItems;

        readFile("./test_prepared.csv", testItems, false);


        // fill empty values of parameter 2
        {
            vector<double> param2Values;
            for (Item &it : testItems)
            {
                if (it.values[2] > 0.0)
                {
                    param2Values.push_back(it.values[2]);
                }
            }
            double param2Mean = calcMean(param2Values);
            for (Item &it : testItems)
            {
                if (it.values[2] <= 0.0)
                {
                    it.values[2] = param2Mean;
                }
            }
        }


        cout << "PassengerId,Survived" << endl;;

        for (Item &it : testItems)
        {
            int predictedClass = makePrediction(it);
            cout << it.id << "," << predictedClass << endl;
        }
    }

    return 0;
}


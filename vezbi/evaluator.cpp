#include<iostream>
#include<cstring>
using namespace std;

class WrongLabelsFormatException {
private:
    char *message;
public:
    WrongLabelsFormatException(const char *message) {
        this->message=new char[strlen(message)+1];
        strcpy(this->message, message);
    }
    void print() {
        cout<<message<<endl;
    }
};

class Evaluator {
protected:
    char *trueValues;
    char *predicted;
public:
    Evaluator(char *trueValues, char *predicted) {
        if(strlen(trueValues) != strlen(predicted)) {
            throw WrongLabelsFormatException("Labels must have the same length");
        }
        for(int i=0;i< strlen(trueValues);i++) {
            if(!(trueValues[i]=='-' || trueValues[i]=='+' || predicted[i]=='-' || predicted[i]=='+')) {
                throw WrongLabelsFormatException("Labels must be + or -");
            }
        }
        this->trueValues=new char[strlen(trueValues)+1];
        strcpy(this->trueValues, trueValues);
        this->predicted=new char[strlen(predicted)+1];
        strcpy(this->predicted, predicted);
    }

    virtual double evaluate()=0;
    virtual void print()=0;

    bool operator>=(Evaluator &e) {
        return this->evaluate()>=e.evaluate();
    }
};

class AccuracyEvaluator : public Evaluator {
public:
    AccuracyEvaluator(char *trueValues, char *predicted)
    : Evaluator(trueValues, predicted) {}

    double evaluate() override {
        int c=0;
        for(int i=0;i< strlen(trueValues);i++) {
            if(trueValues[i]==predicted[i]) {
                c++;
            }
        }
        return (float) c/strlen(trueValues);
    }

    void print() override {
        cout<<"Number of data points: "<<strlen(trueValues)<<" Prediction Accuracy: "<<evaluate()<<endl;
    }
};

class SensitivityEvaluator : public Evaluator {
public:
    SensitivityEvaluator(char *trueValues, char *predicted)
            : Evaluator(trueValues, predicted) {}

    double evaluate() override {
        int c=0;
        int c_positives=0;
        for(int i=0;i< strlen(trueValues);i++) {
            if(trueValues[i]==predicted[i] && trueValues[i]=='+') {
                c++;
            }
            if(trueValues[i]=='+') {
                c_positives++;
            }
        }
        return (float) c/c_positives;
    }

    void print() override {
        cout<<"Number of data points: "<<strlen(trueValues)<<" Prediction Sensitivity: "<<evaluate()<<endl;
    }
};

Evaluator *highestScore(Evaluator **evaluators, int n) {
    Evaluator *max=evaluators[0];
    for(int i=0;i<n;i++) {
        if(*evaluators[i]>=*max) {
            max=evaluators[i];
        }
    }
    return max;
}

int main() {
    int testCase;
    char trueLabels[100];
    char predictedLabels[100];
    cin >> testCase;
    if (testCase == 1) {
        cout << "TESTING CREATION OF ACCURACY EVALUATOR. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;
        try {
            Evaluator *evaluator = new AccuracyEvaluator(trueLabels, predictedLabels);
            cout << evaluator->evaluate() << endl;
            evaluator->print();
        }
        catch (WrongLabelsFormatException &e) {
            e.print();
        }

    } else if (testCase == 2) {
        cout << "TESTING CREATION OF ACCURACY EVALUATOR. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;
        try {
            Evaluator *evaluator = new SensitivityEvaluator(trueLabels, predictedLabels);
            cout << evaluator->evaluate() << endl;
            evaluator->print();
        }
        catch (WrongLabelsFormatException &e) {
            e.print();
        }

    } else if (testCase == 3) {
        cout << "TESTING CREATION OF BOTH EVALUATORS. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;
        try {
            Evaluator *accuracy = new AccuracyEvaluator(trueLabels, predictedLabels);
            Evaluator *sensitivity = new SensitivityEvaluator(trueLabels, predictedLabels);
            accuracy->print();
            sensitivity->print();
        }
        catch (WrongLabelsFormatException &e)
        {
            e.print();
        }
    } else if (testCase == 4) {
        cout << "TESTING OPERATOR >=" << endl;
        cin >> trueLabels >> predictedLabels;
        Evaluator *accuracy = new AccuracyEvaluator(trueLabels, predictedLabels);
        Evaluator *sensitivity = new SensitivityEvaluator(trueLabels, predictedLabels);
        cin >> trueLabels >> predictedLabels;
        Evaluator *accuracy1 = new AccuracyEvaluator(trueLabels, predictedLabels);
        Evaluator *sensitivity1 = new SensitivityEvaluator(trueLabels, predictedLabels);

        accuracy->print();
        cout << (((*accuracy) >= (*sensitivity)) ? ">=" : "<") << endl;
        sensitivity->print();
        cout << endl;

        sensitivity->print();
        cout << (((*sensitivity) >= (*accuracy)) ? ">=" : "<") << endl;
        accuracy->print();
        cout << endl;

        accuracy->print();
        cout << (((*accuracy) >= (*accuracy1)) ? ">=" : "<") << endl;
        accuracy1->print();
        cout << endl;

        sensitivity->print();
        cout << (((*sensitivity) >= (*sensitivity1)) ? ">=" : "<") << endl;
        sensitivity1->print();
        cout << endl;
    } else {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION. EXCEPTION CAN HAPPEN HERE!" << endl;
        int n;
        cin >> n;
        Evaluator **evaluators = new Evaluator *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            cin >> trueLabels >> predictedLabels;
            try {
                if (type == 1) { //accuracy
                    evaluators[i] = new AccuracyEvaluator(trueLabels, predictedLabels);
                } else { //sensitivity
                    evaluators[i] = new SensitivityEvaluator(trueLabels, predictedLabels);
                }
            }
            catch (WrongLabelsFormatException &e) {
                e.print();
                --n;
                --i;
            }
        }

        cout << "PRINT ALL EVALUATORS FIRST!" << endl;
        for (int i = 0; i < n; i++) {
            evaluators[i]->print();
        }

        cout << "RESULT FROM HIGHEST SCORE METHOD" << endl;
        highestScore(evaluators, n)->print();
    }

}
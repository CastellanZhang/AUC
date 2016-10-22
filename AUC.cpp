//cat label_score.txt | ./AUC

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


struct label_score
{
    string label;
    double score;
public:
    label_score(char _label[], double _score)
    {
        label = _label;
        score = _score;
    }
    bool operator<(const label_score& obj) const
    {
        return score < obj.score;
    }
    bool operator>(const label_score& obj) const
    {
        return score > obj.score;
    }
};


int main()
{
    long long lineNum = 0;
    double rankSum = 0.0;
    long long P = 0;
    long long N = 0;

    long long lastScoreNum = 0;
    long long lastScorePNum = 0;

    double lastScore = -10000.0;
    string lastLabel = "";

    char label[100];
    double score;
    vector<label_score> vecLabelScore;
    while(EOF != scanf("%s %lf", label, &score))
    {
        label_score ls(label, score);
        vecLabelScore.push_back(ls);
    }//end while

    sort(vecLabelScore.begin(), vecLabelScore.end(), less<label_score>());

    for(int i = 0; i < vecLabelScore.size(); ++i)
    {
        const string& label = vecLabelScore[i].label;
        score = vecLabelScore[i].score;
        lineNum++;
        if(lastLabel != "")
        {
            lastScoreNum++;
            if("+1" == lastLabel || "1" == lastLabel)
            {
                P++;
                lastScorePNum++;
            }
            else if("-1" == lastLabel || "0" == lastLabel)
            {
                N++;
            }
            else
            {
                printf("data error\n");
                exit(0);
            }
            if(lastScore != score)
            {
                if(lastScorePNum > 0)
                {
                    rankSum += (lineNum - 1 + lineNum - lastScoreNum)/2.0 * lastScorePNum;
                }
                lastScoreNum = 0;
                lastScorePNum = 0;
            }
        }
        lastScore = score;
        lastLabel = label;
    }//end for

    lineNum++;
    if(lastLabel != "")
    {
        lastScoreNum++;
        if("+1" == lastLabel || "1" == lastLabel)
        {
            P++;
            lastScorePNum++;
        }
        else if("-1" == lastLabel || "0" == lastLabel)
        {
            N++;
        }
        else
        {
            printf("data error\n");
            exit(0);
        }
        if(true)
        {
            if(lastScorePNum > 0)
            {
                rankSum += (lineNum - 1 + lineNum - lastScoreNum)/2.0 * lastScorePNum;
            }
            lastScoreNum = 0;
            lastScorePNum = 0;
        }
    }

    //printf("P = %lld\n", P);
    //printf("N = %lld\n", N);
    //printf("lineNum = %lld\n", lineNum - 1);
    //printf("rankSum = %lf\n", rankSum);

    double numerator = rankSum - P * (P + 1)/2.0;
    //printf("AUC = %lf/%lld = %lf\n", numerator, P * N, numerator / (P * N));
    printf("%lf\n", numerator / (P * N));
    return 0;
}


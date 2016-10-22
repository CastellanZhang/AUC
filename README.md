# AUC
计算二分类器预测结果的AUC。

执行方法：

cat label_score.txt | ./AUC

输入文件label_core.txt每一行的格式：

label score

其中label为正负类别标签，正样本标签可以是+1或1，负样本标签可以是-1或0。score等于把样本预测为正的概率值。

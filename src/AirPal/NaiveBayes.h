#pragma once

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;


class NaiveBayesClassifer
{
private:
	
	
	// <class id, class probility> <C, P(C)>
	unordered_map<int, double> classes;
	// <class id, <attribute id, probability>> <C, <x, P(x|C)>>
	unordered_map<int, unordered_map<int, double>> attributesPerClass;

public:


	// input: vector< pair < class id, attribute id>> , DimSize is the number of attributes
	NaiveBayesClassifer(vector<vector<int>> &data, int DimSize)
	{
		// start training
		// count all classes and attributes
		for (auto entry : data)
		{
			if (classes.find(entry[0]) == classes.end())
			{
				classes[entry[0]] = 1;
				unordered_map<int, double> pxc;
				attributesPerClass[entry[0]] = pxc;
			}
			else
			{
				classes[entry[0]] += 1;
			}
			for (int k = 1; k <= DimSize; k++)
			{
				if (attributesPerClass[entry[0]].find(entry[k]) == attributesPerClass[entry[0]].end())
				{
					attributesPerClass[entry[0]][entry[k]] = 1;
				}
				else
				{
					attributesPerClass[entry[0]][entry[k]] += 1;
				}
			}
		}
		// calculate probility per class and per attribute
		for (auto seg : attributesPerClass)
		{
			cout << " — — — Class " << seg.first << " — — — " << endl;
			for (auto entry : seg.second)
			{
				entry.second /= classes[seg.first];
				cout << "Attribute P(x = " << entry.first << " | C = " << seg.first << ") = " << entry.second << endl;
			}
			classes[seg.first] /= data.size();
			cout << "Class P(C = " << seg.first << ") = " << classes[seg.first] << endl;
		}
	}



	// predict class with attributes vector< attribute id>
	int predict(vector<int> attributes)
	{
		int maxcid = -1;
		double maxp = 0;
		for (auto cls : classes)
		{
			// p(C|x) = p(C)*p(x1|C)*p(x2|C)*…
			double pCx = cls.second;
			for (int i = 0; i < attributes.size(); i++)
			{
				pCx *= attributesPerClass[cls.first][attributes[i]];
			}
			if (pCx > maxp)
			{
				maxp = pCx;
				maxcid = cls.first;
			}
		}
		cout << "Predict Class : " << maxcid << " P(C | x) = " << maxp << endl;
		return maxcid;
	}



};


//
//extern void populateDataInModel(vector<vector<int>> &data, unordered_map<string, int> &classmap, unordered_map<string, int> &attrimap,
//	string c, string a1, string a2, int K)
//{
//	vector<int> apair = { classmap[c],attrimap[a1], attrimap[a2] };
//	vector<vector<int>> newarr(K, apair);
//	data.insert(data.end(), newarr.begin(), newarr.end());
//}















//int main() {
//	// prepare a training dataset with 2 attributes and 3 classes
//	unordered_map<string, int> classmap = { {"apple", 0}, {"pineapple", 1}, {"cherry", 2} };
//	unordered_map<string, int> attrimap =
//		// color
//	{ {"red", 0}, {"green", 1}, {"yellow", 2},
//		// shape
//		{"round", 10}, {"oval", 11}, {"heart", 12} };
//	vector<vector<int>> data;
//	populateData(data, classmap, attrimap, "apple", "green", "round", 20);
//	populateData(data, classmap, attrimap, "apple", "red", "round", 50);
//	populateData(data, classmap, attrimap, "apple", "yellow", "round", 10);
//	populateData(data, classmap, attrimap, "apple", "red", "oval", 5);
//	populateData(data, classmap, attrimap, "apple", "red", "heart", 5);
//	populateData(data, classmap, attrimap, "pineapple", "green", "oval", 30);
//	populateData(data, classmap, attrimap, "pineapple", "yellow", "oval", 70);
//	populateData(data, classmap, attrimap, "pineapple", "green", "round", 5);
//	populateData(data, classmap, attrimap, "pineapple", "yellow", "round", 5);
//	populateData(data, classmap, attrimap, "cherry", "yellow", "heart", 50);
//	populateData(data, classmap, attrimap, "cherry", "red", "heart", 70);
//	populateData(data, classmap, attrimap, "cherry", "yellow", "round", 5);
//	random_shuffle(data.begin(), data.end());
//	// train model
//	NaiveBayesClassifer mymodel(data, 2);
//	// predict with model
//	int cls = mymodel.predict({ attrimap["red"],attrimap["heart"] });
//	cout << "Predicted class " << cls << endl;
//	return 0;
//}
#pragma once

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "Vector.h"
using namespace std;


class NaiveBayesClassifer{
private:
	// <class id, class probability> <C, P(C)>
	unordered_map<int, double> classes;
	// <class id, <attribute id, probability>> <C, <x, P(x|C)>>
	unordered_map<int, unordered_map<int, double>> attributesPerClass;

public:
	// input: vector< pair < class id, attribute id>> , DimSize is the number of attributes
	NaiveBayesClassifer(Vector<Vector<int>> &data, int DimSize)
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
			classes[seg.first] /= data.Size();
			cout << "Class P(C = " << seg.first << ") = " << classes[seg.first] << endl;
		}
	}



	// predict class with attributes vector< attribute id>
	int predict(Vector<int> attributes)
	{
		int maxcid = -1;
		double maxp = 0;
		for (auto cls : classes)
		{
			// p(C|x) = p(C)*p(x1|C)*p(x2|C)*…
			double pCx = cls.second;
			for (int i = 0; i < attributes.Size(); i++)
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
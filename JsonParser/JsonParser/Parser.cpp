#include<iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <time.h>
#include <list> 

using namespace std;
using namespace rapidjson;

void processJson(Document& doc) {
	if (doc.HasParseError() == false) {

		int totalCount = 0;
		double costSum = 0;

		//list storing ids greater than 95
		list<int> idsGT95;

		//list storing ids with max cost component > 50
		list<int> idsCostCompsGT50;

		float maxCostComponent = 0;

		for (Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
		{
			totalCount++;
			bool isMaxValueGTThreshold = false;

			const Value& cost = (*itr)["cost"];
			costSum += cost.GetFloat();

			const Value& id = (*itr)["id"];
			if (cost.GetFloat() > 95) {
				idsGT95.push_back(id.GetInt());
			}

			const Value& costComponents = (*itr)["cost_components"];
			for (rapidjson::SizeType i = 0; i < costComponents.Size(); i++)
			{
				const rapidjson::Value& c = costComponents[i];
				if (maxCostComponent < c.GetFloat()) {
					maxCostComponent = c.GetFloat();
				}
				if (isMaxValueGTThreshold != true && c.GetFloat() > 50) {
					isMaxValueGTThreshold = true;
				}
			}
			if (isMaxValueGTThreshold == true) {
				idsCostCompsGT50.push_back(id.GetInt());
			}
		}
		double averageCost = costSum / totalCount;

		cout << "1:" << averageCost << "\n\n";
		cout << "2:" << maxCostComponent << "\n\n";
		cout << "3:";
		bool first = true;
		for (auto iter = idsGT95.begin(); iter != idsGT95.end(); iter++) {
			if (iter != idsGT95.begin()) cout << ", ";
			cout << *iter;
		}
		cout << "\n\n";
		cout << "4:";
		for (auto iter = idsCostCompsGT50.begin(); iter != idsCostCompsGT50.end(); iter++) {
			if (iter != idsCostCompsGT50.begin()) cout << ", ";
			cout << *iter;
		}
		cout << "\n\n";
	}
	else {
		cout << "Error Occured while parsing" << endl;
	}
}

string getFilePath(char* basePath) {
	string filePath(basePath);
	int fileSizeOption;
	cout << "Enter the file size Option:\n1.Small\n2.Medium\n3.Large\n";
	cin >> fileSizeOption;
	string fileSize;
	switch (fileSizeOption) {
	case 1:
		fileSize = "small.txt";
		break;
	case 2:
		fileSize = "medium.txt";
		break;
	case 3:
		fileSize = "large.txt";
		break;
	default:
		cout << "Incorrect Option !! Aborting Program!!";
		exit(0);
	}
	filePath.append(fileSize);
	return filePath;
}

int main(int argc, char** argv) {
	clock_t tStart = clock();
	string filePath = getFilePath(argv[1]);
	ifstream ifs(filePath);
	IStreamWrapper isw(ifs);
	Document doc;

	//parsing json to a DOM tree
	doc.ParseStream(isw);
	processJson(doc);

	printf("Total time taken to run the program: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}
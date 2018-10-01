#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "FileWrapper.hpp"
#include "utils.hpp"

using std::cout;
using std::endl;


int main(int argc, char **argv)
{
  unsigned startTime = clock();
  if(argc < 3) {
	cout << "Error: no programm arguments" << endl;
	return 220;
  }
  try {
	drmatters::FileWrapper alpha(argv[1], argv[2]);
	drmatters::sendResults(alpha);
	unsigned endTime = clock();
	unsigned diffTime = endTime - startTime;
	alpha.stringsProcessed--;
	cout << "Time: " << diffTime << " msecs" << endl;
	cout << "Mid length: " << (double)alpha.totalLength / (double)alpha.stringsProcessed << " letters" << endl;
	cout << "Strings processed: " << alpha.stringsProcessed << endl;
  } catch(...) {
	cout << "Catched error" << endl;
	throw;
  }

  return 0;
}

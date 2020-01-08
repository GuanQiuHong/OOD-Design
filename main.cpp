/* 
 * File:   main.cpp
 * Author: williamhong
 */

#include "ArgsParser.h"
#include "Reader.h"
#include "Calculator.h"
#include "Results.h"
#include "Formatter.h"
#include "Writer.h"

using namespace std;

int main(int argc, char** argv) {
    
    ArgsParser argsParser;
    bool parseSuccessful = argsParser.parse(argc, argv);

    if(!parseSuccessful) exit(0); 
    
    string fileName = argsParser.getFileName();
    
    Reader reader;
    reader.read(fileName);
    vector<ShipmentRow> adaptedData = reader.getAdaptedData();
    
    Calculator calculator;
    calculator.processData(adaptedData);
    Results results = calculator.getResults();
    
    Formatter formatter;
    formatter.format(results);
    string resultString = formatter.getResultString();
        
    Writer writer;
    writer.outputResults(resultString);
    
    return 0; 
}
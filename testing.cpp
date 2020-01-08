#define CATCH_CONFIG_MAIN 
#define private public 
#include "catch.hpp"
#include "ArgsParser.h"
#include "Reader.h"
#include "Calculator.h"
#include "Formatter.h"
#undef private


using namespace std;

TEST_CASE("ArgsParser tests. "
"Note, the file to access is shipmentstats.csv.") {
    
    int argc;
    char** argv;
    ArgsParser argsParser;
    bool parseSuccess;
    string fileName;
    
    SECTION("Testing when 2 arguments are entered: main <fileName>."
    "True is expected only when arguments entered, can index an accessible file"
    "in directory.") {
        
        argc = 2;
        argv = new char*[argc];

        argv[0] = (char*)"main"; 
        
        argv[1] = (char*)"shipmentstats.csv";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == true);
        fileName = argsParser.getFileName();
        REQUIRE(fileName == "shipmentstats.csv");

        argv[1] = (char*)"shipmentstats";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        argv[1] = (char*)"shipmentstats.csvb";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        argv[1] = (char*)"completelyRandomstuff";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
    }
    
    SECTION("Testing when 3 arguments are entered: main -f <fileName>."
    "True is expected, only when arguments entered, can index an accessible file") {
        
        argc = 3;
        argv = new char*[argc];
        
        argv[0] = (char*)"main";
        
        argv[1] = (char*)"-f";
        
        argv[2] = (char*)"shipmentstats.csv";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == true);
        fileName = argsParser.getFileName();
        REQUIRE(fileName == "shipmentstats.csv");
        
        
        argv[2] = (char*)"shipmentstats.cs";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        argv[2] = (char*)"blahblahblah";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        
        argv[1] = (char*)"-g";
        
        argv[2] = (char*)"shipmentstats.csv";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        argv[1] = (char*)"access";
        
        argv[2] = (char*)"shipmentstats.csv";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
    }
    
    SECTION("Testing when an invalid number of arguments are entered.") {
        
        argc = 1;
        argv = new char*[argc];
        
        argv[0] = (char*)"main";
        
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        argc = 3;
        argv = new char*[argc];
        
        argv[0] = (char*)"main";
        
        argv[1] = (char*)"shipmentstats.csv";
        argv[2] = (char*)"extraStuff";
        
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        argc = 4;
        argv = new char*[argc];
        
        argv[0] = (char*)"main";
        
        argv[1] = (char*)"shipmentstats.csv";
        argv[2] = (char*)"extraStuff";
        argv[3] = (char*)"moreExtraStuff";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
        argv[1] = (char*)"-f";
        argv[2] = (char*)"shipmentstats.csv";
        argv[3] = (char*)"extraStuff";
        parseSuccess = argsParser.parse(argc, argv);
        REQUIRE(parseSuccess == false);
        
    }
    
} 



TEST_CASE("Reader tests.") {
    
    geoHashTable geoHashMap;
    geoHashMap.importCountryContinentMap();
    
    SECTION("Check if country-continent hash map was built correctly, by checking if "
    "elements from countries.csv is indeed in the geoHashMap.") {
    
        REQUIRE(geoHashMap.getTable().find("china")->second == "Asia");
        REQUIRE(geoHashMap.getTable().find("chad")->second == "Africa");
        REQUIRE(geoHashMap.getTable().find("mali")->second == "Africa");
        REQUIRE(geoHashMap.getTable().find("fiji")->second == "Oceania");
        REQUIRE(geoHashMap.getTable().find("usa")->second == "North America");
        REQUIRE(geoHashMap.getTable().find("canada")->second == "North America");
        REQUIRE(geoHashMap.getTable().find("kong")->second == "Asia");
        REQUIRE(geoHashMap.getTable().find("azerbaijan")->second == "Europe");
        REQUIRE(geoHashMap.getTable().find("romania")->second == "Europe");

    }
    
    SECTION("Check if parsing country from status string works correctly") {
        Reader reader;
        pair<string, string> countryContinent;

        countryContinent = reader.parseCountryFromStatus("Shipment picked up at Shanghai, China", geoHashMap);
        REQUIRE(countryContinent.first == "china");

        countryContinent = reader.parseCountryFromStatus("Processed at HONG KONG - HONG KONG", geoHashMap);
        REQUIRE(countryContinent.first == "kong");

        countryContinent = reader.parseCountryFromStatus("Clearance processing complete at CINCINNATI HUB,OH-USA", geoHashMap);
        REQUIRE(countryContinent.first == "usa");

        countryContinent = reader.parseCountryFromStatus("Delivered - Signed for by receiver in Toronto, Canada.", geoHashMap);
        REQUIRE(countryContinent.first == "canada");

        countryContinent = reader.parseCountryFromStatus("2017-01-22, 21:16:00, Customs status updated", geoHashMap);
        REQUIRE(countryContinent.first == "default");
    
    }
    
    SECTION("Check if the rows constructed for shipmentTable match the information from shipmentstats.csv") {
        Reader reader;
        reader.read("shipmentstats.csv");
        
        SECTION("DATE checks") {
            REQUIRE(reader.getDate(0) == "2017-01-25");
            REQUIRE(reader.getDate(3) == "2017-01-24");
            REQUIRE(reader.getDate(5) == "2017-01-24");
            REQUIRE(reader.getDate(10) == "2017-01-22");
            REQUIRE(reader.getDate(14) == "2017-01-22");
            REQUIRE(reader.getDate(18) == "2017-01-21");
        }

        SECTION("TIME checks") {
            REQUIRE(reader.getTime(0) == " 12:03:41");
            REQUIRE(reader.getTime(3) == " 09:41:00");
            REQUIRE(reader.getTime(5) == " 06:57:00");
            REQUIRE(reader.getTime(8) == " 14:48:08");
            REQUIRE(reader.getTime(10) == " 21:16:00");
            REQUIRE(reader.getTime(12) == " 12:39:22");
            REQUIRE(reader.getTime(14) == " 11:41:07");
            REQUIRE(reader.getTime(17) == " 02:24:47");
            REQUIRE(reader.getTime(19) == " 22:21:42");
        }
    
        SECTION("STATUS checks") {
            REQUIRE(reader.getStatus(0) == " Delivered - Signed for by receiver in Toronto, Canada.");
            REQUIRE(reader.getStatus(1) == " With delivery courier");
            REQUIRE(reader.getStatus(3) == " Clearance processing complete at ONTARIO SERVICE AREA - CANADA");
            REQUIRE(reader.getStatus(5) == " Arrived at Sort Facility ONTARIO SERVICE AREA - CANADA");
            REQUIRE(reader.getStatus(6) == " Customs status updated");
            REQUIRE(reader.getStatus(7) == " Departed Facility in CINCINNATI HUB,OH-USA");
            REQUIRE(reader.getStatus(11) == " Departed Facility in CINCINNATI HUB,OH-USA");
            REQUIRE(reader.getStatus(13) == " Clearance processing complete at CINCINNATI HUB,OH-USA");
            REQUIRE(reader.getStatus(15) == " Departed Facility in HONG KONG - HONG KONG");
            REQUIRE(reader.getStatus(16) == " Processed at HONG KONG - HONG KONG");
            REQUIRE(reader.getStatus(19) == " Shipment picked up at Shanghai, China");

        }
    
        SECTION("COUNTRY checks, country extracted from status by strtok parsing; where 'DEFAULT' means unspecified") {
            REQUIRE(reader.getCountry(0) == "canada");
            REQUIRE(reader.getCountry(1) == "default");
            REQUIRE(reader.getCountry(4) == "default");
            REQUIRE(reader.getCountry(7) == "usa");
            REQUIRE(reader.getCountry(10) == "default");
            REQUIRE(reader.getCountry(15) == "kong");
            REQUIRE(reader.getCountry(16) == "kong");
            REQUIRE(reader.getCountry(19) == "china");
        }
        
    }
    
    
}

TEST_CASE("Calculator tests.") {
    Reader reader;
    reader.read("shipmentstats.csv");
    vector<ShipmentRow> adaptedData = reader.getAdaptedData();
    Calculator calculator;
    calculator.processData(adaptedData);
    Results results = calculator.getResults();
    
    SECTION("Check if the intervals calculated between steps is correct;"
    "note the first step doesn't have 'time since last step'.") {
        
        REQUIRE(adaptedData[0].getTimeSinceLastStep().getHour() == 2);
        REQUIRE(adaptedData[0].getTimeSinceLastStep().getMinutes() == 37);
        
        REQUIRE(adaptedData[1].getTimeSinceLastStep().getHour() == 21);
        REQUIRE(adaptedData[1].getTimeSinceLastStep().getMinutes() == 44);
        
        REQUIRE(adaptedData[2].getTimeSinceLastStep().getHour() == 2);
        REQUIRE(adaptedData[2].getTimeSinceLastStep().getMinutes() == 1);
        
        REQUIRE(adaptedData[4].getTimeSinceLastStep().getHour() == 2);
        REQUIRE(adaptedData[4].getTimeSinceLastStep().getMinutes() == 11);
        
        REQUIRE(adaptedData[7].getTimeSinceLastStep().getHour() == 1);
        REQUIRE(adaptedData[7].getTimeSinceLastStep().getMinutes() == 14);
        
        REQUIRE(adaptedData[11].getTimeSinceLastStep().getHour() == 2);
        REQUIRE(adaptedData[11].getTimeSinceLastStep().getMinutes() == 45);
        
        REQUIRE(adaptedData[14].getTimeSinceLastStep().getHour() == 4);
        REQUIRE(adaptedData[14].getTimeSinceLastStep().getMinutes() == 39);
        
        REQUIRE(adaptedData[17].getTimeSinceLastStep().getHour() == 2);
        REQUIRE(adaptedData[17].getTimeSinceLastStep().getMinutes() == 35);
        
        REQUIRE(adaptedData[19].getTimeSinceLastStep().getHour() == 0); 
        REQUIRE(adaptedData[19].getTimeSinceLastStep().getMinutes() == 0);
    }
    
    SECTION("Check if calculations for total time elapsed, "
    "time spent in continent (Asia), time spent in country (USA), "
    "time spent in country (Canada), and longest shipment step (max interval)"
    "are correct. ") {
        int hours;
        double minutes;
        
        hours = results.timeInAsia.getHour();
        minutes = results.timeInAsia.getMinutes();
        REQUIRE(hours == 13);
        REQUIRE(minutes == 19);
        
        hours = results.timeInUSA.getHour();
        minutes = results.timeInUSA.getMinutes();
        REQUIRE(hours == 43);
        REQUIRE(minutes == 16);
        
        hours = results.timeInCanada.getHour();
        minutes = results.timeInCanada.getMinutes();
        REQUIRE(hours == 29);
        REQUIRE(minutes == 7);
        
        REQUIRE(results.maxIntervalStatusPair.first == " Delivery attempted; recipient not home");
        REQUIRE(results.maxIntervalStatusPair.second == " With delivery courier");
        
        hours = results.timeElapsedInTotal.getHour();
        minutes = results.timeElapsedInTotal.getMinutes();
        REQUIRE(hours == 85);
        REQUIRE(minutes == 42);
        
    }
}

TEST_CASE("Formatter tests.") {
    
    Results results;
    results.timeElapsedInTotal.setHour(85);
    results.timeElapsedInTotal.setMinutes(42);
    results.timeInAsia.setHour(13);
    results.timeInAsia.setMinutes(19);
    results.timeInUSA.setHour(43);
    results.timeInUSA.setMinutes(16);
    results.timeInCanada.setHour(29);
    results.timeInCanada.setMinutes(7);
    results.maxIntervalStatusPair.first = " Delivery attempted; recipient not home";
    results.maxIntervalStatusPair.second = " With delivery courier";
    
    Formatter formatter;
    formatter.format(results);
    
    string resultString = formatter.getResultString();
    REQUIRE(resultString == "Total shipment time: 85:42\n"
            "Total time in Asia: 13:19\n"
            "Total time in USA: 43:16\n"
            "Total time in Canada: 29:7\n"
            "Longest shipment step: from Delivery attempted; recipient not home to With delivery courier\n");
    
}
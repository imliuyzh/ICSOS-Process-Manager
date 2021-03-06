#include "ProcessManagerUI.h"

// Please read the comments in the header file to understand the functionalities of each method.
ProcessManagerUI::ProcessManagerUI()
{
    writeOutput(0, true, true);
}

void ProcessManagerUI::getInput(char* filePath)
{
    std::fstream fileStream;
    fileStream.open(filePath, std::ios::in);
    
    std::string rawInput;
    std::getline(fileStream, rawInput);

    std::smatch matches;
    const std::regex INPUT_PATTERN("^(cr|de|rq|rl|to|in){1} {0,1}([0-9]*) {0,1}([0-9]*)\r*$");

    while (std::getline(fileStream, rawInput))
    {
        bool result = std::regex_match(rawInput, matches, INPUT_PATTERN);
        if (result == true) 
        {
            performAction(matches);
        }
        else if ((rawInput != "" && rawInput != "\r") && result == false)
        {
            writeOutput(-1, false, false);
        }
    }
    
    fileStream.close();
}

void ProcessManagerUI::performAction(std::smatch& matches)
{
    try
    {
        std::string original = matches[0].str(), first = matches[1].str(), second = matches[2].str(), third = matches[3].str();
        if (first == "in" && second == "" && third == "")
        {
            int currentProcess = manager.init();
            writeOutput(currentProcess, true, false);
        }
        else if (first == "to" && second == "" && third == "")
        {
            int currentProcess = manager.timeout();
            writeOutput(currentProcess, false, false);
        }
        else if (first == "cr" && second != "" && third == "")
        {
            int currentProcess = manager.create(std::stoi(second));
            writeOutput(currentProcess, false, false);
        }
        else if (first == "de" && second != "" && third == "")
        {
            int currentProcess = manager.destroy(std::stoi(second));
            writeOutput(currentProcess, false, false);
        }
        else if (first == "rq" && second != "" && third != "")
        {
            int currentProcess = manager.request(std::stoi(second), std::stoi(third));
            writeOutput(currentProcess, false, false);
        }
        else if (first == "rl" && second != "" && third != "")
        {
            int currentProcess = manager.release(std::stoi(second), std::stoi(third));
            writeOutput(currentProcess, false, false);
        }
        else
        {
            writeOutput(-1, false, false);
        }
    }
    catch (...)
    {
        writeOutput(-1, false, false);
    }
}
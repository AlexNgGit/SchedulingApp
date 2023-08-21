#include "Project.h"
#include <sys/stat.h>
#include "OpenXLSX.hpp"

Project::Project() {
    this->name = "";
    this->ECT = 0;
}

Project::Project(std::string name) {
    this->name = name;
    this->ECT = 0;
}

shared_ptr<Task> Project::findTask(std::string taskName) {
    for (auto element: input) {
        if (element->getName() == taskName) {
            return element;
        }
    }
    return nullptr;
}


int Project::loadExcelFiles(string path) {
    XLDocument doc = XLDocument(path);
    auto wb = doc.workbook();
    int16_t index = 1;
    //TODO: try to see what active means here

    auto name = wb.sheet(index).name();
    auto currSheet = wb.worksheet(name);
    int subIndex = 2;

    while (index != wb.sheetCount() ) {
        while (subIndex <= currSheet.columnCount()) {
            auto name = currSheet.cell("A" + subIndex).value().typeAsString();
            if (name == "END") {
                break;
            }
            auto duration = stod(currSheet.cell("B" + subIndex).value().typeAsString());
            auto cost = stod(currSheet.cell("C" + subIndex).value().typeAsString());
            shared_ptr<Task> newTask (new Task(duration, cost, name, vector< shared_ptr<Task> >()));
            input.push_back(newTask);
            subIndex++;
        }
        index++;
    }

    /*for (auto element: input) {
        int subElementIndex = 2;
        while(subElementIndex <= subIndex) {
            auto taskName = currSheet.cell("D" + subElementIndex).value().typeAsString();
            element->addParentNode(findTask(taskName));
        }
    }
    return 1;*/
}


int Project::loadProjectHelper(string pathname) {
    struct stat fileInfo;
    if(stat(pathname.c_str(), &fileInfo) == 0) {
        if(S_ISREG(fileInfo.st_mode)) {
            future<int> ret = async([&]() { return this->loadExcelFiles(pathname); });
            if (!ret.get()) {
                throw logic_error("FAIL TO LOAD FILE");
            }
            return 1;
        }
    } else {
        throw logic_error("NOT VALID FILE");
    }
    return 0;
}

future<int> Project::addTasks(string pathName) {
    return async(std::launch::async, [&]{
        return this->loadProjectHelper(pathName);
    });
}

const vector<shared_ptr<Task>> &Project::getInput() const {
    return input;
}


#ifndef READFOLDER_H
#define READFOLDER_H
#include <QString>
#include <QDir>
#include <string>
#include <fstream>
#include <iostream>
#include <QDebug>
using namespace std;
class ReadFolder
{
public:
    ReadFolder(QString name);
    ~ReadFolder();
    bool creatCSV(string dirname);
    string creatCSV(string dirname);
    bool deleteDIR(string table);
    bool deleteImg(string table);
private:
    void creatTXT(string dirname);
    string filename;
    QString folderName;
    QString trainTXT,testTXT,wordTXT,tableTXT;
    ofstream TrainCSV,TestCSV,Word,TableTXT;
    int label=0;
};

#endif // READFOLDER_H

#include "readfolder.h"

ReadFolder::ReadFolder(QString name)
{
    folderName = name;
    QString CSVname;
    CSVname.append(name);
    CSVname.append("/Train.txt");
    filename = CSVname.toStdString();
}
ReadFolder::~ReadFolder(){

}
string ReadFolder::creatCSV(string dirname){
    QDir dir = QDir(QString::fromStdString(dirname));
    string temp;
    if(QString::fromStdString(dirname).contains(".jpg") || QString::fromStdString(dirname).contains(".png")){
        return dirname;
    }
    if(!dir.exists()){
        cout<<dirname<<" is not exist"<<endl;
        return "";
    }
    if(QString::fromStdString(dirname).contains(".") || QString::fromStdString(dirname).contains("..")){
        return "";
    }
    for(int i=0;i<dir.entryList().size();i++){
        temp = creatCSV(dirname+dir.entryList()[i].toStdString()+"/");
        if(QString::fromStdString(temp).contains(".jpg")||QString::fromStdString(temp).contains(".png")){
            temp.erase(temp.size()-1);
            cout<<temp<<endl;
            temp.clear();
        }
    }
    return temp;
}

void ReadFolder::creatTXT(string dirname){
    trainTXT.append(folderName);
    trainTXT.append("/../Train.txt");

    testTXT.append(folderName);
    testTXT.append("/../Test.txt");

    wordTXT.append(folderName);
    wordTXT.append("/../Word.txt");

    tableTXT.append(folderName);
    tableTXT.append("/../Table.txt");
    TrainCSV = ofstream (trainTXT.toStdString().c_str());
    TestCSV = ofstream (testTXT.toStdString().c_str());
    Word = ofstream (wordTXT.toStdString().c_str());
    TableTXT = ofstream (tableTXT.toStdString().c_str());
}
/*******************************
 * creat CSV file
 * table : 目標資料夾
 * *****************************/
bool ReadFolder::creatCSV(string dirname){
    creatTXT(dirname);
    /********** open dir ***************/
    QDir dir = QDir(folderName);
    if(!dir.exists()){
        return false;
    }
    /********** Layer 1 ***************/
    for(int i=0;i<dir.entryList().size();i++){
        if(dir.entryList()[i]=="." || dir.entryList()[i]==".." || dir.entryList()[i].contains(".txt"))
            continue;

        QString folder_1;
        folder_1.append(folderName);
        folder_1.append("/");
        folder_1.append(dir.entryList()[i]);
        QDir dir_1 = QDir(folder_1);
        if(!dir_1.exists()){
            continue;
        }

        /********** Layer 2 ***************/
        for(int j=0;j<dir_1.entryList().size();j++){
            if(dir_1.entryList()[j]=="." || dir_1.entryList()[j]=="..")
                continue;

            /**********************************/
            if(dir_1.entryList()[j].contains(".jpg") ||dir_1.entryList()[j].contains(".png") ){
                if(j <= dir_1.entryList().size() ){// train & test 區別條件
                    // write train (relative address label)
                    TrainCSV<<dir.entryList()[i].toStdString()<<"/"
                           <<dir_1.entryList()[j].toStdString()<<" "<<label<<endl;
                }
                else{
                    // write test (relative address label)
                     TestCSV<<dir.entryList()[i].toStdString()<<"/"
                           <<dir_1.entryList()[j].toStdString()<<" "<<label<<endl;
                }
                // write table (absolute address)
                TableTXT<<folderName.toStdString()<<"/"
                       <<dir.entryList()[i].toStdString()<<"/"
                      <<dir_1.entryList()[j].toStdString()<<endl;
            }

//            QString folder_2;
//            folder_2.append(folder_1);
//            folder_2.append("/");
//            folder_2.append(dir_1.entryList()[j]);
//            QDir dir_2 = QDir(folder_2);
//            if(!dir_2.exists()){
//                continue;
//            }

//            /********** Layer 3 ***************/
//            for(int k=0;k<dir_2.entryList().size();k++){
//                if(dir_2.entryList()[k]=="." || dir_2.entryList()[k]=="..")
//                    continue;

//                /**********************************/
//                if(dir_2.entryList()[k].contains(".jpg") ||dir_2.entryList()[k].contains(".png")){
//                    if(k <= dir_2.entryList().size()){ //train & test 區別條件
//                        // write train (relative address label)
//                        TrainCSV<<dir.entryList()[i].toStdString()<<"/"
//                               <<dir_1.entryList()[j].toStdString()<<"/"
//                              <<dir_2.entryList()[k].toStdString()<<" "<<label<<endl;
//                    }
//                    else{
//                        // write test (relative address label)
//                         TestCSV<<dir.entryList()[i].toStdString()<<"/"
//                               <<dir_1.entryList()[j].toStdString()<<"/"
//                              <<dir_2.entryList()[k].toStdString()<<" "<<label<<endl;
//                    }
//                    // write table (absolute address)
//                    TableTXT<<folderName.toStdString()<<"/"
//                           <<dir.entryList()[i].toStdString()<<"/"
//                          <<dir_1.entryList()[j].toStdString()<<endl;
//                }

//                QString folder_3;
//                folder_3.append(folder_2);
//                folder_3.append("/");
//                folder_3.append(dir_2.entryList()[k]);
//                QDir dir_3 = QDir(folder_3);
//                if(!dir_3.exists()){
//                    continue;
//                }

//                /********** Layer 4 ***************/
//                for(int l=0;l<dir_3.entryList().size();l++){
//                    if(dir_3.entryList()[l]=="." || dir_3.entryList()[l]=="..")
//                        continue;

//                    if(dir_3.entryList()[l].contains(".jpg") || dir_3.entryList()[l].contains(".png")){
//                        if(l <= dir_3.entryList().size()){ //train & test 區別條件
//                            // write train (relative address label)
//                            TrainCSV<<dir.entryList()[i].toStdString()<<"/"
//                                   <<dir_1.entryList()[j].toStdString()<<"/"
//                                  <<dir_2.entryList()[k].toStdString()<<"/"
//                                 <<dir_3.entryList()[l].toStdString()<<" "<<label<<endl;
//                        }
//                        else{
//                            // write test (relative address label)
//                             TestCSV<<dir.entryList()[i].toStdString()<<"/"
//                                   <<dir_1.entryList()[j].toStdString()<<"/"
//                                  <<dir_2.entryList()[k].toStdString()<<"/"
//                                 <<dir_3.entryList()[l].toStdString()<<" "<<label<<endl;
//                        }
//                        // write table (absolute address)
//                        TableTXT<<folderName.toStdString()<<"/"
//                               <<dir.entryList()[i].toStdString()<<"/"
//                              <<dir_1.entryList()[j].toStdString()<<"/"<<"/"
//                             <<dir_3.entryList()[l].toStdString()<<endl;
//                    }
//                }
//            }

        }
        /**********************************************************************/

        if(dir_1.entryList().size()==2)
            label--;
        label++;
    }

    Word.close();
    TestCSV.close();
    TrainCSV.close();
    TableTXT.close();
    return true;
}
/*******************************
 * 更名目標資料夾，須提供Table
 * table : 目標文件
 * *****************************/
bool ReadFolder::deleteDIR(string table){
    ifstream in(table.c_str());
    string temp;
    vector<string> target;
    while(getline(in,temp)){
        target.push_back(temp);
    }
    in.close();
    QDir dir = QDir(folderName);
    if(!dir.exists()){
        return false;
    }
    for(int i=0;i<dir.entryList().size();i++){
        for(int j=0;j<target.size();j++){
            if(target[j]==dir.entryList()[i].toStdString()){
                QString oldfolder,newfolder;
                oldfolder.append(folderName);
                oldfolder.append("/");
                oldfolder.append(dir.entryList()[i]);

                newfolder.append(folderName);
                newfolder.append("/new");
                newfolder.append(dir.entryList()[i]);

                dir.rename(oldfolder,newfolder);
            }
        }
    }
    return true;
}
/*******************************
 * 刪除目標檔案，須提供Table
 * table : 刪除文件
 * *****************************/
bool ReadFolder::deleteImg(string table){
    ifstream in(table.c_str());
    string temp;
    vector<string> target;
    while(getline(in,temp)){
        target.push_back(temp);
    }
    in.close();
    for(int i=0;i<target.size();i++){
        QFile img(QString::fromStdString(target[i]));
        img.remove();
    }
    return true;
}

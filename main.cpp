#include <QString>
#include "readfolder.h"
int main()
{
    QString foldername = QString("D:/caffe/experiment/LFW/train/");
    ReadFolder folder = ReadFolder(foldername);
    folder.creatCSV(foldername.toStdString());
    //folder.creatCSV();
    //folder.deleteImg("D:/vgg-face_dataset/vgg_face_dataset/delete85.txt");
    //system("pause");
    return 0;
}

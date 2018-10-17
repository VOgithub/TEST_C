#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QString>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
// переменные


struct item {
    QString StCode; //имя
//     float Amount;
    float Data[5]; // 5tk оценки
};


QString LineToItem(QString StrFromFile);
void writeFile ( QString Final);

int main()
{
    float Summ = 0;
    QString Start[6];
    QString FinalRow;
    QString message;
    QString qsFileName = "StudentList.txt";
    item TempA;
//begin
    QFile resFile ("StudentResult.txt"); //если файл существует - удаляем!
    resFile.remove();

    //наличие файла?
    QFile file(qsFileName);
        if (!file.exists()){
            message = "Can't find file %1 to read\n";
            message = message.arg(qsFileName);
            qDebug() << message;
            return -1;
        }

        if(!file.open(QFile::ReadOnly | QFile::Text))  {
            message = "Can't open the file %1 for reading\n";
            message = message.arg(qsFileName);
            qDebug() << message;
            return -1;
    }

        QTextStream in(&file);
            in.setAutoDetectUnicode(true);
            in.setCodec("UTF-8");

        system("chcp 65001");
        char buff[50];
        ifstream fin("StudentList.txt"); // открыли файл для чтения
        if (!fin.is_open()) // если файл не открыт
                cout << "Файл не может быть открыт!\n"; // сообщить об этом
            else
            {
            for (int i=0;i<6;i++){   //первая строка
            fin >> buff;
            Start[i]= buff;
//            cout <<" " << buff;
            }
//            cout << endl;
            while (!fin.eof()){
            fin >> buff; // считали первое слово из файла
            TempA.StCode = buff;
 //          qDebug()<<TempA.StCode;              // OK
  //          cout << buff << ":  ";
            for (int i=0;i<5;i++){
                fin >> TempA.Data[i];
//                cout << "  "<<  TempA.Data[i];
            if (i<4){
                Summ = Summ + (TempA.Data[i]*10);
            } else {
                Summ = Summ + (TempA.Data[4]*60);
                Summ = Summ /100;
            }
//            cout << endl;

}
            QString qsTemp= " %1 %2 \n";
            qsTemp=qsTemp.arg(TempA.StCode).arg( double(Summ),0,'g', 2 );
            qDebug()<< qsTemp << endl;
            writeFile (qsTemp);



 //           cout <<" : "<< Summ << endl;
            }
    fin.close();
    resFile.close();

    cout << "Done!"<< endl;
     return 0;
}





}
void writeFile (QString FRow){
    QFile resFile ("StudentResult.txt");
                if (resFile.open(QFile::WriteOnly |QFile::Append )){
                    QTextStream out(&resFile);
                    out<< FRow;

                    out<<"\r\n";
}
}






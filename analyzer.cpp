#include "analyzer.h"

////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer() {}
////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer(const QString &fileName)
{
    this->fileName=fileName;
    this->fileSize = 0;
    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        return ;
    }
    fileSize = file->size();
    mdatOffset = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned long int Analyzer:: valueOfGroupOfBytes(const int &length, const unsigned long int& offset) {
    QByteArray array;
    unsigned long int num = 0;
    file->seek(offset);
    array = file->read(length);
    for(int i = 0; i< length; ++i) {
        num |= static_cast<unsigned int>(array[i]) & 0xFF; //suma bit po bicie
        if(0!=length && i!=(length-1)) {
            num=(num<<8); //przesuniecie o 8 bitow w lewo
        }
    }
    return num;
}
////////////////////////////////////////////////////////////////////////////////////////////
signed long int Analyzer:: signedValueOfGroupOfBytes(const int &length, const unsigned long int& offset) {
    QByteArray array;
    signed long int num = 0;
    file->seek(offset);
    array = file->read(length);
    for(int i = 0; i< length; ++i) {
        num |= static_cast<unsigned int>(array[i]) & 0xFF; //suma bit po bicie
        if(0!=length && i!=(length-1)) {
            num=(num<<8); //przesuniecie o 8 bitow w lewo
        }
    }
    return num;
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned long int Analyzer::valueOfGroupOfBits(const int & length, const unsigned long int& offset) {
    int firstByteNum = offset/8;
    int lastByteNum = (offset + length)/8;

    unsigned long int byteValue = this->valueOfGroupOfBytes(lastByteNum - firstByteNum + 1, firstByteNum);
    int suffix = 8 - (offset + length)%8;

    unsigned long int bitValue = 0;
    int pattern = 0;

    for(int i = 0; i < length; ++i) { //utworzenie wzoru: liczby, ktora w reprezentacji binarnej ma jedynki tam, ktory fragment mamy wyciac
        //i zera w pozostalych przypadkach: wygenerowanie ciagu 1
        pattern |= 1;
        pattern = pattern << 1;
    }
    for(int i = 0; i < suffix; ++i) {//dodanie odpowiedniej ilosci zer
        pattern |= 0;
        if (!(i== suffix - 1))
            pattern = pattern << 1;
    }

    bitValue = (byteValue & pattern) >> suffix; //iloczyn logiczny bit po bicie i przesuniecie bitowe w prawo

    return bitValue;
}
////////////////////////////////////////////////////////////////////////////////////////////
QString Analyzer:: qstringValue(const unsigned int& length, const unsigned int& offset) {
    QByteArray array;
    file->seek(offset);
    array = file->read(length);
    return QString(array);
}
////////////////////////////////////////////////////////////////////////////////////////////

Analyzer::~Analyzer() {
}
////////////////////////////////////////////////////////////////////////////////////////////
void Analyzer::setData(TreeItem* parent, QHash<long, TreeItem *>* items) {
    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        return ;
    }
    setData(parent, items, 0, fileSize); //zaczynamy od zerowego offsetu
    file->close();
}
////////////////////////////////////////////////////////////////////////////////////////////

void Analyzer::setData(TreeItem *&parent, QHash<long, TreeItem *>* items, const unsigned long &off, unsigned long int maxOff) {
    //qDebug()<<"setData wywołanie!"<<maxOff;
    unsigned long int offset= off;//offset w pliku
    bool progress= true;
    while(progress) {
        unsigned long int size; //rozmiar boxa
        //unsigned long int type; //typ boxa
        QString type;
        //unsigned int [16] extendedType;//to-do
        size = valueOfGroupOfBytes(4, 0 + offset);
        //type = valueOfGroupOfBytes(4, 4 + offset);
        type = qstringValue(4, 4 + offset);
        //qDebug()<<"setData jaki box"<<type<<QString::number(size)<<QString::number(offset);
        if(size == 0) { //gdy size = 0, to box ciągnie się do końca pliku
            size = fileSize - offset;  //nieprzetestowane!
        }
        if(size == 1 ) { //dla size = 1, rozmiar przybiera wartość rozszerzoną int(64), po typie
            size = valueOfGroupOfBytes(8, 8 + offset);
        }

        if(type == QString("uuid")) {
            if(size == 1) {
                //to-do
            }
            else {

            }
        }
        if(!type.size())
            return;

        if(type == QString("mdat"))
            mdatOffset = offset;

        QList<QVariant> columnData; //konstrukcja danych, ktore beda wyswietlane w drzewie
        columnData<<type;
        columnData<<QString::number(size);
        columnData<<QString::number(offset);

        TreeItem *newItem= new TreeItem(this,columnData,parent,offset);//tworzymy treeitem

        parent->appendChild(newItem);
        items->insert(offset, newItem);
        if(newItem->isContainer()){//gdy treeitem zawiera inne boxy, tworzymy subarray wycinajac offset na atrybuty
            //qDebug()<<"is container tempSize"<<offset + size;

            setData(newItem,
                    items,
                    offset + newItem->getOffset(), offset + size);
        }

        offset += size;

        //maxTempOff += size;
        //qDebug()<<"setData off temps"<<offset<<maxOff;
        if( offset >= fileSize )
            progress = false;
        if( offset >= maxOff ) {
            progress = false;
            //maxTempOff -= size;
            // qDebug()<<"setData progress-false";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

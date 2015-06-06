#include "analyzer.h"

////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer() {}
////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer(const QString &fileName) {
    this->fileName=fileName;
    this->fileSize = 0;
    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        return ;
    }
    fileSize = file->size();
    mdatOffset = 0;
    bitOperator = new BitOperator();
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned long int Analyzer:: valueOfGroupOfBytes(const int &length, const unsigned long int& offset) {
    return bitOperator->valueOfGroupOfBytes(file, length, offset);
}
////////////////////////////////////////////////////////////////////////////////////////////
signed long int Analyzer:: signedValueOfGroupOfBytes(const int &length, const unsigned long int& offset) {
    return bitOperator->signedValueOfGroupOfBytes(file, length, offset);
}
////////////////////////////////////////////////////////////////////////////////////////////
unsigned long int Analyzer::valueOfGroupOfBits(const int & length, const unsigned long int& offset) {
    return bitOperator->valueOfGroupOfBits(file, length, offset);
}
////////////////////////////////////////////////////////////////////////////////////////////
QString Analyzer:: qstringValue(const unsigned int& length, const unsigned int& offset) {
    return bitOperator->qstringValue(file, length, offset);
}
////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::~Analyzer() {
    delete bitOperator;
    delete file;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Analyzer::setData(TreeItem *parent, QHash<long, TreeItem *> *items) {
    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        return ;
    }
    setData(parent, items, 0, fileSize); //zaczynamy od zerowego offsetu
    file->close();
}
////////////////////////////////////////////////////////////////////////////////////////////
void Analyzer::setData(TreeItem *&parent, QHash<long, TreeItem *> *items, const unsigned long &off, unsigned long int maxOff) {
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
        if(size == 0)  //gdy size = 0, to box ciągnie się do końca pliku
            size = fileSize - offset;  //nieprzetestowane!

        if(size == 1 )  //dla size = 1, rozmiar przybiera wartość rozszerzoną int(64), po typie
            size = valueOfGroupOfBytes(8, 8 + offset);

        if(!type.size())
            return;

        if(type == QString("mdat"))
            mdatOffset = offset;

        //qDebug()<<offset;

        QList<QVariant> columnData; //konstrukcja danych, ktore beda wyswietlane w drzewie
        columnData<<type;
        columnData<<QString::number(size);

        QString hexOff = QString::number(offset, 16);
        int zeroPrefNum = 8 - hexOff.length();
        QString hexOffRes("0x");
        for(int i = 0; i < zeroPrefNum; ++ i)
            hexOffRes.append("0");
        hexOffRes.append(hexOff);

        columnData<<hexOffRes;

        TreeItem *newItem= new TreeItem(this,columnData,parent,offset);//tworzymy treeitem

        parent->appendChild(newItem);
        items->insert(offset, newItem);
        if(newItem->isContainer()){//gdy treeitem zawiera inne boxy, tworzymy subarray wycinajac offset na atrybuty
            setData(newItem,
                    items,
                    offset + newItem->getOffset(), offset + size);
        }

        offset += size;

        if( offset >= fileSize )
            progress = false;
        if( offset >= maxOff )
            progress = false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////

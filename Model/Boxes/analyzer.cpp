#include "analyzer.h"

////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer() {}
////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer(FileBitOperator *fs): fbOperator(fs) {
    mdatOffset = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
QString Analyzer::decToHex(const unsigned long& offset) {
    QString hexOff = QString::number(offset, 16);
    int zeroPrefNum = 8 - hexOff.length();
    QString hexOffRes("0x");
    for(int i = 0; i < zeroPrefNum; ++ i)
        hexOffRes.append("0");
    hexOffRes.append(hexOff);
    return hexOffRes;
}
////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::~Analyzer() {
    delete fbOperator;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Analyzer::setData(TreeItem *parent, QHash<long, TreeItem *> *items) {
    fbOperator->openFile();
    setData(parent, items, 0, fbOperator->getSize()); //zaczynamy od zerowego offsetu
    fbOperator->close();
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
        size = fbOperator->valueOfGroupOfBytes(4, 0 + offset);
        type = fbOperator->stringValue(4, 4 + offset);

        if(size == 0)  //gdy size = 0, to box ciągnie się do końca pliku
            size = fbOperator->getSize() - offset;  //nieprzetestowane!

        if(size == 1 )//dla size = 1, rozmiar przybiera wartość rozszerzoną int(64), po typie
            size = fbOperator->valueOfGroupOfBytes(8, 8 + offset);

        if(!type.size())
            return;

        if(type == QString("mdat"))
            mdatOffset = offset;

        //qDebug()<<"ANALYZER: setData"<<type;//<<size<<offset;

        QList<QVariant> columnData; //konstrukcja danych, ktore beda wyswietlane w drzewie
        columnData<<type;
        columnData<<QString::number(size);
        columnData<<decToHex(offset);

        TreeItem *newItem= new TreeItem(fbOperator,columnData,parent,offset);//tworzymy treeitem

        parent->appendChild(newItem);
        items->insert(offset, newItem);
        if(newItem->isContainer()){//gdy treeitem zawiera inne boxy, tworzymy subarray wycinajac offset na atrybuty
            setData(newItem,
                    items,
                    offset + newItem->getOffset(), offset + size);
        }

        offset += size;

        if( offset >= fbOperator->getSize() )
            progress = false;
        if( offset >= maxOff )
            progress = false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////

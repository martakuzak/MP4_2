#include "analyzer.h"

////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer() {}
////////////////////////////////////////////////////////////////////////////////////////////
Analyzer::Analyzer(FileService *fs): fileService(fs) {
    qDebug()<<"ANALYZER: constructor";
    mdatOffset = 0;
    bitOperator = new BitOperator();
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
    qDebug()<<"ANALYZER: destructor";
    delete bitOperator;
    //delete file;
    delete fileService;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Analyzer::setData(TreeItem *parent, QHash<long, TreeItem *> *items) {
    qDebug()<<"ANALYZER: setData public";
    fileService->openFile();
    qDebug()<<"ANALYZER: setData 2";
    setData(parent, items, 0, fileService->getSize()); //zaczynamy od zerowego offsetu
    fileService->close();
}
////////////////////////////////////////////////////////////////////////////////////////////
void Analyzer::setData(TreeItem *&parent, QHash<long, TreeItem *> *items, const unsigned long &off, unsigned long int maxOff) {
    qDebug()<<"ANALYZER: setData";
    unsigned long int offset= off;//offset w pliku
    bool progress= true;
    while(progress) {
        unsigned long int size; //rozmiar boxa
        //unsigned long int type; //typ boxa
        QString type;
        //unsigned int [16] extendedType;//to-do
        size = bitOperator->valueOfGroupOfBytes(fileService->getBytes(4, 0 + offset), 4); //valueOfGroupOfBytes(4, 0 + offset);
        //type = valueOfGroupOfBytes(4, 4 + offset);
        type = bitOperator->stringValue(fileService->getBytes(4, 4 + offset), 4); //qstringValue(4, 4 + offset);
        if(size == 0)  //gdy size = 0, to box ciągnie się do końca pliku
            size = fileService->getSize() - offset;  //nieprzetestowane!

        if(size == 1 )  //dla size = 1, rozmiar przybiera wartość rozszerzoną int(64), po typie
            size = bitOperator->valueOfGroupOfBytes(fileService->getBytes(8, 8 + offset), 8);//valueOfGroupOfBytes(8, 8 + offset);

        if(!type.size())
            return;

        if(type == QString("mdat"))
            mdatOffset = offset;

        qDebug()<<"ANALYZER: setData"<<type<<size<<offset;

        QList<QVariant> columnData; //konstrukcja danych, ktore beda wyswietlane w drzewie
        columnData<<type;
        columnData<<QString::number(size);
        columnData<<decToHex(offset);

        TreeItem *newItem= new TreeItem(fileService,columnData,parent,offset);//tworzymy treeitem

        parent->appendChild(newItem);
        items->insert(offset, newItem);
        if(newItem->isContainer()){//gdy treeitem zawiera inne boxy, tworzymy subarray wycinajac offset na atrybuty
            setData(newItem,
                    items,
                    offset + newItem->getOffset(), offset + size);
        }

        offset += size;

        if( offset >= fileService->getSize() )
            progress = false;
        if( offset >= maxOff )
            progress = false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////

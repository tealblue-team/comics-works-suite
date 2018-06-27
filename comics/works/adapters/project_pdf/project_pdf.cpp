#include <QDebug>
#include <QPrinter>
#include <QFileInfo>
#include <QTextCursor>
#include <QTextDocument>
#include "project_pdf.h"
#include "../../usecases/usecases.h"

using namespace comics::works::adapters;

ProjectPdf::ProjectPdf(QObject *parent) : QObject(parent)
{

}

void ProjectPdf::setUsecases(usecases* uc)
{
    m_uc = uc;
}

void ProjectPdf::saveToPdf(const QString& fileName)
{
    QString filePath = fileName;
    if (!fileName.isEmpty()) {
        auto doc = convertToTextDoc();
        if (QFileInfo(filePath).suffix().isEmpty())
            filePath.append(".pdf");

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::Letter);
        qDebug() << filePath;
        printer.setOutputFileName(filePath.startsWith("file:/") ? filePath.remove(0,6) : filePath);
        printer.setFontEmbeddingEnabled(true);

        doc->print(&printer);
        doc->deleteLater();

        emit saved(filePath);
    }
}

QTextDocument* ProjectPdf::convertToTextDoc() {
    auto document = new QTextDocument();
    QTextCursor cursor(document);

    auto characters = m_uc->entities_reg->currentWorkspace->characters();
    cursor.insertText(tr("Characters: "));
    for (int i=0; i < characters->length(); ++i) {
        auto character = characters->at(i);
        cursor.insertText(QString(i==characters->length()-1 ? "%1\n" : "%1, ").arg(character->name()));
    }

    auto panels = m_uc->entities_reg->currentWorkspace->panels();
    for (int i=0; i < panels->length(); ++i) {
        auto panel = panels->at(i);
        cursor.insertBlock();
        cursor.insertText(QString("%1\n").arg(panel->name() != "" ? panel->name() : panel->eid()));
        if (panel->description() != "")
            cursor.insertText(QString("%1\n").arg(panel->description()));
        for (int j=0; j < panel->dialogs().length(); ++j) {
            cursor.insertText(QString("%1: %2\n").arg(
                                  panel->dialogs().at(j).toMap().value("characterName").toString(),
                                  panel->dialogs().at(j).toMap().value("dialogContent_en_US").toString())
                              );
        }
    }
    return document;
}

#include <QDebug>
#include <QPrinter>
#include <QFileInfo>
#include <QTextCursor>
#include <QTextDocument>
#include "project_pdf.h"
#include "comics/works/usecases/usecases.h"
#include "comics/works/entities/character/character_base.h"
#include "comics/works/entities/project/project_base.h"

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

    QTextCharFormat plain;

    QTextCharFormat italic;
    italic.setFontItalic(true);

    QTextCharFormat bold;
    bold.setFontWeight(600);

    cursor.setCharFormat(plain);

    auto characters = m_uc->entities_reg->currentProject->characters();
    cursor.insertText(tr("Characters: "));
    for (int i=0; i < characters->length(); ++i) {
        auto character = characters->at(i);
        cursor.insertText(QString(i==characters->length()-1 ? "%1\n" : "%1, ").arg(character->name()));
    }

    auto panels = m_uc->entities_reg->currentProject->panels();
    for (int i=0; i < panels->length(); ++i) {
        auto panel = panels->at(i);
        cursor.insertBlock();
        cursor.insertText(QString("%1\n").arg(panel->name() != "" ? panel->name() : panel->eid()));
        if (panel->description() != "") {
            cursor.setCharFormat(italic);
            cursor.insertText(QString("%1\n").arg(panel->description()));
            cursor.setCharFormat(plain);
        }
        for (int j=0; j < panel->dialogs().length(); ++j) {
            cursor.setCharFormat(bold);
            cursor.insertText(QString("%1: ").arg(panel->dialogs().at(j).toMap().value("characterName").toString()));
            cursor.setCharFormat(plain);
            cursor.insertText(QString("%1\n").arg(panel->dialogs().at(j).toMap().value("dialogContent_en_US").toString()));
        }
    }
    return document;
}

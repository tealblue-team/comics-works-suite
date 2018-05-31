#ifndef PROJECT_PDF_H
#define PROJECT_PDF_H

#include <QObject>

class QTextDocument;

namespace comics {
namespace works {
class usecases;
namespace entities {
class Register;
class PanelBase;
class CharacterBase;
}
namespace adapters {
class ProjectPdf : public QObject
{
    Q_OBJECT
public:
    explicit ProjectPdf(QObject *parent = nullptr);
    void setUsecases(usecases*);
    Q_INVOKABLE void saveToPdf(const QString& fileName);
signals:
    void saved(const QString& filePath);
    void notSaved(const QString& errorMessage);
private:
    QTextDocument *convertToTextDoc();
    usecases* m_uc = nullptr;
};
}
}
}

#endif // PROJECT_PDF_H

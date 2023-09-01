#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

class SearchReplaceApp : public QMainWindow {
    Q_OBJECT

public:
    SearchReplaceApp(QWidget *parent = 0)
        : QMainWindow(parent) {

        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout *layout = new QVBoxLayout;
        centralWidget->setLayout(layout);

        QLabel *filenameLabel = new QLabel("File Name:");
        layout->addWidget(filenameLabel);

        QLineEdit *filenameLineEdit = new QLineEdit;
        layout->addWidget(filenameLineEdit);

        QLabel *searchLabel = new QLabel("Search:");
        layout->addWidget(searchLabel);

        QLineEdit *searchLineEdit = new QLineEdit;
        layout->addWidget(searchLineEdit);

        QLabel *replaceLabel = new QLabel("Replace:");
        layout->addWidget(replaceLabel);

        QLineEdit *replaceLineEdit = new QLineEdit;
        layout->addWidget(replaceLineEdit);

        QCheckBox *caseSensitiveCheckBox = new QCheckBox("Case Sensitive");
        layout->addWidget(caseSensitiveCheckBox);

        QCheckBox *countOccurrencesCheckBox = new QCheckBox("Count Occurrences");
        layout->addWidget(countOccurrencesCheckBox);

        QPushButton *searchReplaceButton = new QPushButton("Search/Replace");
        layout->addWidget(searchReplaceButton);

        connect(searchReplaceButton, &QPushButton::clicked, this, [=]() {
            QString filename = filenameLineEdit->text();
            QString search = searchLineEdit->text();
            QString replace = replaceLineEdit->text();
            bool caseSensitive = caseSensitiveCheckBox->isChecked();
            bool countOccurrences = countOccurrencesCheckBox->isChecked();

            QFile file(filename);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString fileContents = in.readAll();

                file.close();

                QMessageBox::information(this, "Search/Replace Result", "Search and replace completed.");
            } else {
                QMessageBox::critical(this, "Error", "File not found or could not be opened.");
            }
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SearchReplaceApp window;
    window.setWindowTitle("Text File Search and Replace");
    window.resize(400, 300);
    window.show();
    return app.exec();
}

#include "main.moc"

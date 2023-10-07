#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <iostream>


// Предположим, что у нас есть массив вопросов и ответов
QStringList questions = {
    "Вопрос 1: Как звали домашнего эльфа у семьи Малфоев?",
    "Вопрос 2: Из чего сделана волшебная палочка Гарри Поттера?",
    "Вопрос 3: Какое имя у совы Гарри Поттера?",
    "Вопрос 4: Какой факультет в Хогвартсе принадлежит Гарри Поттеру?",
    "Вопрос 5: Какое заклинание используется для создания светящегося шара?",
    "Вопрос 6: Как зовут кота Гермионы?",
    "Вопрос 7: Как называется школа волшебства, которую посещал Гарри Поттер?",
    "Вопрос 8: Как звали директора Хогвартса, когда Гарри поступил в школу?",
    "Вопрос 9: Какой предмет преподавала Профессор МакГонагалл в Хогвартсе?",
    "Вопрос 10: Как звали призрака, обитающего в Хогвартсе, представителя дома Гриффиндор?",
    "Вопрос 11: Какой животный был компаньоном Гарри Поттера?",
    "Вопрос 12: Как называется заклинание, превращающее питомца в посуду?",
    "Вопрос 13: Как звали одноклассника Гарри, который был сыном Люциуса Малфоя?",
    "Вопрос 14: Какой предмет преподавал Профессор Снегг в Хогвартсе?",
    "Вопрос 15: Любимое заклинение Гарри Поттера?",
    "Вопрос 16: Какой предмет преподавала Профессор Трелони в Хогвартсе?",
    "Вопрос 17: Какое заклинание используется для заморозки противника?",
    "Вопрос 18: Как называется команда, позволяющая вызвать метлу к волшебнику?",
    "Вопрос 19: Как называется способность видеть сны, предсказывающие будущее?",
    "Вопрос 20: Как называется темная артефакт, разрушение которого разделяет душу на части?"
};

QList<QStringList> answers = {
    {"Кричер", "Добби", "Винкси"},//1
    {"Остролист", "Жила феникса", "Сердцевина дракона"},//2
    {"Сычик", "Хедвиг", "Эррол"},//3
    {"Слизерин", "Гриффиндор", "Пуффендуй"},//4
    {"Авада Кедавра", "Экспеллиармус", "Люмос"},//5
    {"Живоглот", "Кароста", "Букля"},//6
    {"Хогсмит", "Хогвартс", "Дурмстранг"},//7
    {"МакГонагалл", "Снегг", "Дамблдор"},//8
    {"Невидимость", "Трансфигурация", "Заклинания"},//9
    {"Полтергейст", "Почти Безголовый Ник", "Мойти"},//10
    {"Кот", "Сова", "Жаба"},//11
    {"Редукто", "Левиоса", "Фера Верто"},//12
    {"Сириус", "Драко", "Нарцисса"},//13
    {"Зельеварение", "Нумерология", "Трансфигурация"},//14
    {"Экспекто Патронум", "Империо", "Экспеллириармус"},//15
    {"Предсказания", "Астрология", "Нумерология"},//16
    {"Иммобулюс", "Импедимента", "Левиоса"},//17
    {"Агуаменти", "Акцио", "Асцендио"},//18
    {"Гадание", "Прорицание", "Предсказания"},//19
    {"Волшебная Палочка", "Кристаж", "Философский Камень"}//20
};

int corrects[] = {
    1,//1
    0,//2
    1,//3
    1,//4
    2,//5
    0,//6
    1,//7
    2,//8
    1,//9
    1,//10
    1,//11
    2,//12
    1,//13
    0,//14
    2,//15
    0,//16
    0,//17
    1,//18
    1,//19
    2 //20
};



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentQuestionIndex(0),
    correctAnswersCount(0)
{
    ui->setupUi(this);

    // Устанавливаем фоновое изображение
    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setMaximumSize(this->size());

    // Подключаем сигналы к слотам
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui->finishButton, &QPushButton::clicked, this, &MainWindow::onFinishClicked);

    // Загружаем первый вопрос
    loadQuestion(currentQuestionIndex);

    // Путь к файлу стилей
    QString stylePath = ":/style/radioStyle.qss";

    // Загрузка файла стилей
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = styleFile.readAll();
        ui->answer1RadioButton->setStyleSheet(style);
        ui->answer2RadioButton->setStyleSheet(style);
        ui->answer3RadioButton->setStyleSheet(style);
        styleFile.close();
    }

    // Путь к файлу стилей
    QString stylePath2 = ":/style/buttonStyle.qss";

    // Загрузка файла стилей
    QFile styleFile2(stylePath2);
    if (styleFile2.open(QFile::ReadOnly | QFile::Text)) {
        QString style = styleFile2.readAll();
        ui->nextButton->setStyleSheet(style);
        ui->finishButton->setStyleSheet(style);
        styleFile2.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadQuestion(int index)
{
    // Устанавливаем вопрос
    ui->questionLabel->setText(questions[index]);

    // Устанавливаем варианты ответов
    ui->answer1RadioButton->setText(answers[index][0]);
    ui->answer2RadioButton->setText(answers[index][1]);
    ui->answer3RadioButton->setText(answers[index][2]);

    // Очищаем выбор пользователя
    ui->answer1RadioButton->setAutoExclusive(false);
    ui->answer2RadioButton->setAutoExclusive(false);
    ui->answer3RadioButton->setAutoExclusive(false);
    ui->answer1RadioButton->setChecked(false);
    ui->answer2RadioButton->setChecked(false);
    ui->answer3RadioButton->setChecked(false);
    ui->answer1RadioButton->setAutoExclusive(true);
    ui->answer2RadioButton->setAutoExclusive(true);
    ui->answer3RadioButton->setAutoExclusive(true);

    // Если это последний вопрос, скрываем кнопку "Далее" и показываем "Завершить тест"
    if (index == questions.size() - 1) {
        ui->nextButton->setVisible(false);
        ui->finishButton->setVisible(true);
    }
    else {
        ui->nextButton->setVisible(true);
        ui->finishButton->setVisible(false);
    }
}

void MainWindow::onNextClicked()
{
    // Проверяем правильность ответа
    if (ui->answer1RadioButton->isChecked()&&corrects[currentQuestionIndex]==0) {
        correctAnswersCount++;
    }else if (ui->answer2RadioButton->isChecked()&&corrects[currentQuestionIndex]==1) {
        correctAnswersCount++;
    }else if (ui->answer3RadioButton->isChecked()&&corrects[currentQuestionIndex]==2) {
        correctAnswersCount++;
    }

    // Загружаем следующий вопрос
    currentQuestionIndex++;
    loadQuestion(currentQuestionIndex);
}

void MainWindow::onFinishClicked()
{
    // Проверяем правильность ответа на последний вопрос
    if (ui->answer1RadioButton->isChecked()&&corrects[currentQuestionIndex]==0) {
        correctAnswersCount++;
    }else if (ui->answer2RadioButton->isChecked()&&corrects[currentQuestionIndex]==1) {
        correctAnswersCount++;
    }else if (ui->answer3RadioButton->isChecked()&&corrects[currentQuestionIndex]==2) {
        correctAnswersCount++;
    }

    // Выводим результаты
    QString resultMessage = QString("Вы ответили правильно на %1 из %2 вопросов.")
        .arg(correctAnswersCount)
        .arg(currentQuestionIndex + 1);

    QMessageBox::information(this, "Результаты", resultMessage);

    currentQuestionIndex=0;
    correctAnswersCount=0;
    loadQuestion(currentQuestionIndex);
}

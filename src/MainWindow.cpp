#include "MainWindow.h"
#include "WarehouseVisualizer.h"
#include "DataStorage.h"

#include <QAbstractItemView>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QSplitter>
#include <QStatusBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    m_nameEdit(nullptr),
    m_categoryEdit(nullptr),
    m_quantitySpin(nullptr),
    m_rowSpin(nullptr),
    m_cellSpin(nullptr),
    m_searchEdit(nullptr),
    m_addButton(nullptr),
    m_updateButton(nullptr),
    m_deleteButton(nullptr),
    m_clearButton(nullptr),
    m_searchButton(nullptr),
    m_resetSearchButton(nullptr),
    m_saveButton(nullptr),
    m_loadButton(nullptr),
    m_table(nullptr),
    m_visualizer(nullptr),
    m_currentSelectedId(-1)
{
    setupUi();
    setupConnections();

    updateVisualizer();
    statusBar()->showMessage("Программа готова к работе");
}

void MainWindow::setupUi()
{
    setWindowTitle("АРМ специалиста склада");
    resize(1150, 680);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);
    mainLayout->addWidget(splitter);

    QWidget* leftPanel = new QWidget(splitter);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    QGroupBox* inputGroup = new QGroupBox("Исходные данные", leftPanel);
    QFormLayout* formLayout = new QFormLayout(inputGroup);

    m_nameEdit = new QLineEdit(inputGroup);
    m_nameEdit->setPlaceholderText("Например: Ноутбук");

    m_categoryEdit = new QLineEdit(inputGroup);
    m_categoryEdit->setPlaceholderText("Например: Техника");

    m_quantitySpin = new QSpinBox(inputGroup);
    m_quantitySpin->setRange(0, 100000);
    m_quantitySpin->setValue(1);

    m_rowSpin = new QSpinBox(inputGroup);
    m_rowSpin->setRange(1, 8);
    m_rowSpin->setValue(1);

    m_cellSpin = new QSpinBox(inputGroup);
    m_cellSpin->setRange(1, 10);
    m_cellSpin->setValue(1);

    formLayout->addRow("Название товара:", m_nameEdit);
    formLayout->addRow("Категория:", m_categoryEdit);
    formLayout->addRow("Количество:", m_quantitySpin);
    formLayout->addRow("Ряд:", m_rowSpin);
    formLayout->addRow("Ячейка:", m_cellSpin);

    leftLayout->addWidget(inputGroup);

    QHBoxLayout* actionLayout = new QHBoxLayout();

    m_addButton = new QPushButton("Добавить", leftPanel);
    m_updateButton = new QPushButton("Изменить", leftPanel);
    m_deleteButton = new QPushButton("Удалить", leftPanel);
    m_clearButton = new QPushButton("Очистить", leftPanel);

    actionLayout->addWidget(m_addButton);
    actionLayout->addWidget(m_updateButton);
    actionLayout->addWidget(m_deleteButton);
    actionLayout->addWidget(m_clearButton);

    leftLayout->addLayout(actionLayout);

    QHBoxLayout* fileLayout = new QHBoxLayout();

    m_saveButton = new QPushButton("Сохранить", leftPanel);
    m_loadButton = new QPushButton("Загрузить", leftPanel);

    fileLayout->addWidget(m_saveButton);
    fileLayout->addWidget(m_loadButton);

    leftLayout->addLayout(fileLayout);

    QGroupBox* searchGroup = new QGroupBox("Поиск товара", leftPanel);
    QHBoxLayout* searchLayout = new QHBoxLayout(searchGroup);

    m_searchEdit = new QLineEdit(searchGroup);
    m_searchEdit->setPlaceholderText("ID, название или категория");

    m_searchButton = new QPushButton("Найти", searchGroup);
    m_resetSearchButton = new QPushButton("Сброс", searchGroup);

    searchLayout->addWidget(m_searchEdit);
    searchLayout->addWidget(m_searchButton);
    searchLayout->addWidget(m_resetSearchButton);

    leftLayout->addWidget(searchGroup);

    m_table = new QTableWidget(leftPanel);
    m_table->setColumnCount(6);
    m_table->setHorizontalHeaderLabels({"ID", "Название", "Категория", "Количество", "Ряд", "Ячейка"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    leftLayout->addWidget(m_table, 1);

    QWidget* rightPanel = new QWidget(splitter);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    QGroupBox* visualGroup = new QGroupBox("Визуализирующая часть OpenGL", rightPanel);
    QVBoxLayout* visualLayout = new QVBoxLayout(visualGroup);

    m_visualizer = new WarehouseVisualizer(visualGroup);
    visualLayout->addWidget(m_visualizer);

    rightLayout->addWidget(visualGroup);

    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 4);
}

void MainWindow::setupConnections()
{
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(m_updateButton, &QPushButton::clicked, this, &MainWindow::updateProduct);
    connect(m_deleteButton, &QPushButton::clicked, this, &MainWindow::removeProduct);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::clearForm);

    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::saveProducts);
    connect(m_loadButton, &QPushButton::clicked, this, &MainWindow::loadProducts);

    connect(m_searchButton, &QPushButton::clicked, this, &MainWindow::searchProducts);
    connect(m_resetSearchButton, &QPushButton::clicked, this, &MainWindow::resetSearch);
    connect(m_searchEdit, &QLineEdit::returnPressed, this, &MainWindow::searchProducts);

    connect(m_table, &QTableWidget::itemSelectionChanged, this, &MainWindow::tableSelectionChanged);
    connect(m_visualizer, &WarehouseVisualizer::productSelected, this, &MainWindow::visualizerSelectionChanged);
}

bool MainWindow::readForm(QString& name, QString& category, int& quantity, int& row, int& cell)
{
    name = m_nameEdit->text().trimmed();
    category = m_categoryEdit->text().trimmed();
    quantity = m_quantitySpin->value();
    row = m_rowSpin->value();
    cell = m_cellSpin->value();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название товара.");
        return false;
    }

    if (category.isEmpty()) {
        category = "Без категории";
    }

    return true;
}

void MainWindow::addProduct()
{
    QString name;
    QString category;
    int quantity;
    int row;
    int cell;

    if (!readForm(name, category, quantity, row, cell)) {
        return;
    }

    if (m_warehouse.isCellBusy(row, cell)) {
        QMessageBox::warning(this, "Ячейка занята", "В выбранной ячейке уже расположен другой товар.");
        return;
    }

    const int productId = m_warehouse.addProduct(name, category, quantity, row, cell);
    m_currentSelectedId = productId;

    m_searchEdit->clear();
    refreshTable(m_warehouse.products());
    selectTableRowByProductId(productId);
    updateVisualizer();

    statusBar()->showMessage("Товар добавлен");
}

void MainWindow::updateProduct()
{
    const int productId = selectedProductId();

    if (productId == -1) {
        QMessageBox::information(this, "Изменение", "Сначала выберите товар в таблице.");
        return;
    }

    QString name;
    QString category;
    int quantity;
    int row;
    int cell;

    if (!readForm(name, category, quantity, row, cell)) {
        return;
    }

    if (m_warehouse.isCellBusy(row, cell, productId)) {
        QMessageBox::warning(this, "Ячейка занята", "В выбранной ячейке уже расположен другой товар.");
        return;
    }

    if (!m_warehouse.updateProduct(productId, name, category, quantity, row, cell)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось изменить товар.");
        return;
    }

    m_currentSelectedId = productId;
    m_searchEdit->clear();

    refreshTable(m_warehouse.products());
    selectTableRowByProductId(productId);
    updateVisualizer();

    statusBar()->showMessage("Товар изменён");
}

void MainWindow::removeProduct()
{
    const int productId = selectedProductId();

    if (productId == -1) {
        QMessageBox::information(this, "Удаление", "Сначала выберите товар в таблице.");
        return;
    }

    const QMessageBox::StandardButton answer = QMessageBox::question(
        this,
        "Удаление товара",
        "Удалить выбранный товар?"
        );

    if (answer != QMessageBox::Yes) {
        return;
    }

    if (!m_warehouse.removeProduct(productId)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить товар.");
        return;
    }

    m_currentSelectedId = -1;
    m_searchEdit->clear();

    refreshTable(m_warehouse.products());
    clearForm();
    updateVisualizer();

    statusBar()->showMessage("Товар удалён");
}

void MainWindow::clearForm()
{
    m_nameEdit->clear();
    m_categoryEdit->clear();
    m_quantitySpin->setValue(1);
    m_rowSpin->setValue(1);
    m_cellSpin->setValue(1);

    m_currentSelectedId = -1;
    m_table->clearSelection();

    updateVisualizer();
}

void MainWindow::searchProducts()
{
    const QVector<Product> result = m_warehouse.searchProducts(m_searchEdit->text());

    refreshTable(result);
    statusBar()->showMessage(QString("Найдено записей: %1").arg(result.size()));
}

void MainWindow::resetSearch()
{
    m_searchEdit->clear();
    refreshTable(m_warehouse.products());

    statusBar()->showMessage("Поиск сброшен");
}

void MainWindow::saveProducts()
{
    const QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить данные склада",
        "warehouse.json",
        "JSON files (*.json)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    QString errorText;

    if (!DataStorage::saveProducts(fileName, m_warehouse.products(), errorText)) {
        QMessageBox::warning(this, "Ошибка сохранения", errorText);
        return;
    }

    statusBar()->showMessage("Данные склада сохранены");
}

void MainWindow::loadProducts()
{
    const QString fileName = QFileDialog::getOpenFileName(
        this,
        "Загрузить данные склада",
        "",
        "JSON files (*.json)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    QVector<Product> loadedProducts;
    QString errorText;

    if (!DataStorage::loadProducts(fileName, loadedProducts, errorText)) {
        QMessageBox::warning(this, "Ошибка загрузки", errorText);
        return;
    }

    m_warehouse.setProducts(loadedProducts);
    m_currentSelectedId = -1;

    m_searchEdit->clear();
    clearForm();
    refreshTable(m_warehouse.products());
    updateVisualizer();

    statusBar()->showMessage("Данные склада загружены");
}

void MainWindow::tableSelectionChanged()
{
    const int productId = selectedProductId();

    if (productId == -1) {
        return;
    }

    const Product* product = m_warehouse.findById(productId);

    if (product == nullptr) {
        return;
    }

    m_currentSelectedId = productId;

    fillForm(*product);
    updateVisualizer();
}

void MainWindow::visualizerSelectionChanged(int productId)
{
    const Product* product = m_warehouse.findById(productId);

    if (product == nullptr) {
        return;
    }

    m_currentSelectedId = productId;
    m_searchEdit->clear();

    refreshTable(m_warehouse.products());
    selectTableRowByProductId(productId);
    fillForm(*product);
    updateVisualizer();

    statusBar()->showMessage("Товар выбран на схеме склада");
}

void MainWindow::refreshTable(const QVector<Product>& products)
{
    QSignalBlocker blocker(m_table);

    m_table->setRowCount(0);

    for (const Product& product : products) {
        const int rowIndex = m_table->rowCount();
        m_table->insertRow(rowIndex);

        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(product.id()));
        idItem->setData(Qt::UserRole, product.id());

        m_table->setItem(rowIndex, 0, idItem);
        m_table->setItem(rowIndex, 1, new QTableWidgetItem(product.name()));
        m_table->setItem(rowIndex, 2, new QTableWidgetItem(product.category()));
        m_table->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(product.quantity())));
        m_table->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(product.row())));
        m_table->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(product.cell())));
    }
}

void MainWindow::fillForm(const Product& product)
{
    m_nameEdit->setText(product.name());
    m_categoryEdit->setText(product.category());
    m_quantitySpin->setValue(product.quantity());
    m_rowSpin->setValue(product.row());
    m_cellSpin->setValue(product.cell());
}

void MainWindow::selectTableRowByProductId(int productId)
{
    for (int row = 0; row < m_table->rowCount(); ++row) {
        QTableWidgetItem* idItem = m_table->item(row, 0);

        if (idItem != nullptr && idItem->data(Qt::UserRole).toInt() == productId) {
            m_table->selectRow(row);
            return;
        }
    }
}

void MainWindow::updateVisualizer()
{
    m_visualizer->setProducts(m_warehouse.products());
    m_visualizer->setSelectedProductId(m_currentSelectedId);
}

int MainWindow::selectedProductId() const
{
    const QList<QTableWidgetItem*> selectedItems = m_table->selectedItems();

    if (selectedItems.isEmpty()) {
        return -1;
    }

    const int row = selectedItems.first()->row();
    const QTableWidgetItem* idItem = m_table->item(row, 0);

    if (idItem == nullptr) {
        return -1;
    }

    return idItem->data(Qt::UserRole).toInt();
}
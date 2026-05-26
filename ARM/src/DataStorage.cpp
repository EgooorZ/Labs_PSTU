#include "DataStorage.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

bool DataStorage::saveProducts(const QString& fileName,
                               const QVector<Product>& products,
                               QString& errorText)
{
    QJsonArray array;

    for (const Product& product : products) {
        QJsonObject object;

        object["id"] = product.id();
        object["name"] = product.name();
        object["category"] = product.category();
        object["quantity"] = product.quantity();
        object["row"] = product.row();
        object["cell"] = product.cell();

        array.append(object);
    }

    QJsonDocument document(array);

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        errorText = "Не удалось открыть файл для записи.";
        return false;
    }

    file.write(document.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

bool DataStorage::loadProducts(const QString& fileName,
                               QVector<Product>& products,
                               QString& errorText)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        errorText = "Не удалось открыть файл для чтения.";
        return false;
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError || !document.isArray()) {
        errorText = "Файл имеет неверный формат JSON.";
        return false;
    }

    QVector<Product> loadedProducts;
    QJsonArray array = document.array();

    for (const QJsonValue& value : array) {
        if (!value.isObject()) {
            continue;
        }

        QJsonObject object = value.toObject();

        Product product(
            object["id"].toInt(),
            object["name"].toString(),
            object["category"].toString(),
            object["quantity"].toInt(),
            object["row"].toInt(),
            object["cell"].toInt()
            );

        loadedProducts.push_back(product);
    }

    products = loadedProducts;

    return true;
}
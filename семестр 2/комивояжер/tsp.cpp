#include "tsp.h"
#include "ui_tsp.h"
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>
#include <cmath>
#include <QGraphicsTextItem>
#include <QQueue>
#include <queue>


TSP::TSP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TSP)
    , scene(new QGraphicsScene(this))
    , totalCost(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::white);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setSceneRect(0, 0, 800, 600);
    ui->resultLabel->setWordWrap(true);

}

TSP::~TSP()
{
    delete ui;
}

bool TSP::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->graphicsView->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());
            addVertexAtPosition(scenePos);
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void TSP::on_addVertexButton_clicked()
{
    ui->resultLabel->setText("Кликните на сцену, чтобы разместить вершину");
    ui->graphicsView->setMouseTracking(true);
}

void TSP::addVertexAtPosition(const QPointF &pos)
{
    if (isOverlapping(pos.x(), pos.y(), 40)) {
        QMessageBox::warning(this, "Ошибка", "Вершины слишком близко друг к другу!");
        return;
    }

    QGraphicsEllipseItem *vertex = scene->addEllipse(0, 0, 30, 30, QPen(Qt::black), QBrush(Qt::lightGray));
    vertex->setPos(pos.x() - 15, pos.y() - 15);

    QGraphicsTextItem *label = scene->addText(QString::number(vertices.size() + 1));
    label->setPos(vertex->pos() + QPointF(15 - label->boundingRect().width()/2,
                                        15 - label->boundingRect().height()/2));
    label->setDefaultTextColor(Qt::black);

    vertices.append(vertex);
    adjacencyMatrix.resize(vertices.size());
    for (auto &row : adjacencyMatrix) {
        row.resize(vertices.size(), INT_MAX);
    }
}

void TSP::on_addEdgeButton_clicked()
{
    if (vertices.size() < 2) {
        QMessageBox::warning(this, "Ошибка", "Нужно минимум 2 вершины!");
        return;
    }

    QStringList vertexList;
    for (int i = 0; i < vertices.size(); ++i) {
        vertexList << QString::number(i + 1);
    }

    bool ok;
    QString from = QInputDialog::getItem(this, "Выберите вершину", "От:", vertexList, 0, false, &ok);
    if (!ok) return;

    QString to = QInputDialog::getItem(this, "Выберите вершину", "До:", vertexList, 1, false, &ok);
    if (!ok || from == to)
    {
        QMessageBox::warning(this, "Ошибка", "Выберите разные вершины!");
        return;
    }

    int cost = QInputDialog::getInt(this, "Стоимость", "Введите стоимость:", 1, 1, 1000, 1, &ok);
    if (!ok) return;

    int fromIdx = from.toInt() - 1;
    int toIdx = to.toInt() - 1;

    adjacencyMatrix[fromIdx][toIdx] = cost;
    adjacencyMatrix[toIdx][fromIdx] = cost;

    QPointF fromCenter = vertices[fromIdx]->pos() + QPointF(15, 15);
    QPointF toCenter = vertices[toIdx]->pos() + QPointF(15, 15);

    QPointF direction = toCenter - fromCenter;
    qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (length > 0) {
        QPointF normalized = direction / length;
        QPointF startPoint = fromCenter + normalized * 15;
        QPointF endPoint = toCenter - normalized * 15;

        QLineF line(startPoint, endPoint);
        QGraphicsLineItem *edge = scene->addLine(line, QPen(Qt::black, 2));
        edge->setZValue(1);

        QGraphicsTextItem *costLabel = scene->addText(QString::number(cost));
        costLabel->setPos(line.center());
        costLabel->setDefaultTextColor(Qt::darkBlue);
        costLabel->setZValue(2);

        selectedEdges.append(qMakePair(fromIdx, toIdx));
        selectedEdgeItems.append(edge);
        selectedEdgeLabels.append(costLabel);
    }
}

void TSP::on_solveButton_clicked()
{
    for (auto item : scene->items()) {
        if (auto line = dynamic_cast<QGraphicsLineItem*>(item)) {
            line->setPen(QPen(Qt::blue, 2));
        }
    }

    solveTSP();
}

QVector<QVector<int>> TSP::reduceMatrix(QVector<QVector<int>> matrix, int &reductionCost)
{
    reductionCost = 0;
    int n = matrix.size();
    // Редукция строк: вычитаем минимальный элемент из каждой строки
    for (int i = 0; i < n; ++i) {
        int minVal = *std::min_element(matrix[i].begin(), matrix[i].end());
        if (minVal != INT_MAX && minVal != 0) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minVal;
                }
            }
            reductionCost += minVal;
        }
    }
    // Редукция столбцов: вычитаем минимальный элемент из каждого столбца
    for (int j = 0; j < n; ++j) {
        int minVal = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }

        if (minVal != INT_MAX && minVal != 0) {
            for (int i = 0; i < n; ++i) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minVal;
                }
            }
            reductionCost += minVal;
        }
    }

    return matrix;
}

int TSP::calculateZeroCost(QVector<QVector<int>> matrix, int row, int col)
{
    int minRow = INT_MAX;
    for (int j = 0; j < matrix[row].size(); ++j) {
        if (j != col && matrix[row][j] < minRow) {
            minRow = matrix[row][j];
        }
    }

    int minCol = INT_MAX;
    for (int i = 0; i < matrix.size(); ++i) {
        if (i != row && matrix[i][col] < minCol) {
            minCol = matrix[i][col];
        }
    }

    if (minRow == INT_MAX) minRow = 0;
    if (minCol == INT_MAX) minCol = 0;

    return minRow + minCol;
}

void TSP::solveTSP()
{
    // Проверка на минимальное количество вершин
    if (vertices.size() < 2) {
        QMessageBox::warning(this, "Ошибка", "Добавьте минимум 2 вершины!");
        return;
    }

    // Обработка тривиального случая для 2 вершин
    if (vertices.size() == 2) {
        int cost = adjacencyMatrix[0][1];
        if (cost == INT_MAX) {
            ui->resultLabel->setText("Нет пути между вершинами!");
            return;
        }
        ui->resultLabel->setText(QString("Оптимальный маршрут: 1 → 2 → 1\nСтоимость: %1").arg(2 * cost));
        return;
    }

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    // Создание узла (начинаем с вершины 0)
    Node* root = new Node();
    root->path = {0};
    root->level = 0;
    root->vertex = 0;
    root->reducedMatrix = adjacencyMatrix;

    // Редукция матрицы и вычисление нижней границы
    int cost = 0;
    root->reducedMatrix = reduceMatrix(root->reducedMatrix, cost);
    root->cost = cost;
    root->zeroEvaluation = 0;

    pq.push(root); // Добавляем корневой узел в очередь

    int bestCost = INT_MAX; // Лучшая найденная стоимость
    QVector<int> bestPath;

    while (!pq.empty()) {
        // Извлекаем узел с минимальной нижней границей
        Node* min = pq.top();
        pq.pop();


        if (min->cost >= bestCost) {
            delete min;
            continue;
        }

        int currentVertex = min->vertex;

        // Если все вершины посещены (кроме возврата в начало)
        if (min->level == vertices.size() - 1) {
            // Проверяем возможность вернуться в начальную вершину
            if (min->reducedMatrix[currentVertex][0] != INT_MAX) {
                int totalCost = min->cost + min->reducedMatrix[currentVertex][0];
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    bestPath = min->path;
                    bestPath.push_back(0); // Замыкаем цикл
                }
            }
            delete min;
            continue;
        }

        // Поиск всех нулевых элементов для ветвления
        QVector<QPair<int, int>> zeroElements;
        QVector<int> zeroEvaluations;

        for (int i = 0; i < vertices.size(); ++i) {
            // Ищем нули в строке текущей вершины для непосещенных вершин
            if (min->reducedMatrix[currentVertex][i] == 0 &&
                std::find(min->path.begin(), min->path.end(), i) == min->path.end()) {
                // Оцениваем "стоимость" нуля
                int evaluation = calculateZeroCost(min->reducedMatrix, currentVertex, i);
                zeroElements.append(qMakePair(currentVertex, i));
                zeroEvaluations.append(evaluation);
            }
        }
        // Если нет нулей для ветвления - пропускаем
        if (zeroElements.isEmpty()) {
            delete min;
            continue;
        }
        // Выбираем ноль с максимальной оценкой
        int maxEvalIndex = std::max_element(zeroEvaluations.begin(), zeroEvaluations.end()) - zeroEvaluations.begin();
        auto bestZero = zeroElements[maxEvalIndex];
        int nextVertex = bestZero.second;
        // Создаем узел с ВКЛЮЧЕНИЕМ выбранного ребра
        Node* includeNode = new Node();
        includeNode->path = min->path;
        includeNode->path.push_back(nextVertex);
        includeNode->level = min->level + 1;
        includeNode->vertex = nextVertex;
        includeNode->reducedMatrix = min->reducedMatrix;

        // Запрещаем переходы из текущей вершины и в следующую
        for (int j = 0; j < vertices.size(); ++j) {
            includeNode->reducedMatrix[currentVertex][j] = INT_MAX;
            includeNode->reducedMatrix[j][nextVertex] = INT_MAX;
        }
        includeNode->reducedMatrix[nextVertex][currentVertex] = INT_MAX;
        // Редуцируем матрицу и вычисляем новую нижнюю границу
        int reductionCost = 0;
        includeNode->reducedMatrix = reduceMatrix(includeNode->reducedMatrix, reductionCost);
        includeNode->cost = min->cost + reductionCost;
        includeNode->zeroEvaluation = zeroEvaluations[maxEvalIndex];

        if (includeNode->cost < bestCost) {
            pq.push(includeNode);
        } else {
            delete includeNode;
        }

        Node* excludeNode = new Node();
        excludeNode->path = min->path;
        excludeNode->level = min->level;
        excludeNode->vertex = currentVertex;
        excludeNode->reducedMatrix = min->reducedMatrix;

        excludeNode->reducedMatrix[currentVertex][nextVertex] = INT_MAX;
        // Редуцируем матрицу и вычисляем новую нижнюю границу
        reductionCost = 0;
        excludeNode->reducedMatrix = reduceMatrix(excludeNode->reducedMatrix, reductionCost);
        excludeNode->cost = min->cost + reductionCost;
        excludeNode->zeroEvaluation = zeroEvaluations[maxEvalIndex];

        if (excludeNode->cost < bestCost) {
            pq.push(excludeNode);
        } else {
            delete excludeNode;
        }

        delete min;
    }
    // Вывод результатов
    if (bestPath.isEmpty())
    {
        ui->resultLabel->setText("Нет возможного маршрута!");
        return;
    }

    QString result = "Оптимальный маршрут: ";
    for (int i = 0; i < bestPath.size(); ++i) {
        if (i != 0) result += " → ";
        result += QString::number(bestPath[i] + 1);
    }
    result += QString("\nСтоимость: %1").arg(bestCost);

    ui->resultLabel->setText(result);

    highlightPath(bestPath);
}

void TSP::highlightPath(const QVector<int>& path)
{
    for (auto item : scene->items()) {
        if (auto line = dynamic_cast<QGraphicsLineItem*>(item)) {
            line->setPen(QPen(Qt::blue, 2));
        }
    }

    for (int i = 0; i < path.size() - 1; ++i) {
        int from = path[i];
        int to = path[i+1];

        for (int j = 0; j < selectedEdges.size(); ++j) {
            auto edge = selectedEdges[j];
            if ((edge.first == from && edge.second == to) ||
                (edge.first == to && edge.second == from)) {
                selectedEdgeItems[j]->setPen(QPen(Qt::red, 3));

                if (i < path.size() - 2)
                {
                    selectedEdgeLabels[j]->setPlainText(
                        QString::number(adjacencyMatrix[from][to]));
                    selectedEdgeLabels[j]->setDefaultTextColor(Qt::darkRed);
                }
                break;
            }
        }
    }
}

void TSP::on_removeVertexButton_clicked()
{
    if (vertices.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет вершин для удаления!");
        return;
    }

    QStringList vertexList;
    for (int i = 0; i < vertices.size(); ++i) {
        vertexList << QString::number(i + 1);
    }

    bool ok;
    QString vertexToRemove = QInputDialog::getItem(this, "Удаление вершины",
                                                 "Выберите вершину для удаления:",
                                                 vertexList, 0, false, &ok);
    if (!ok) return;

    int vertexIndex = vertexToRemove.toInt() - 1;
    QGraphicsEllipseItem* vertexItem = vertices[vertexIndex];

    QList<QGraphicsItem*> itemsToRemove;
    for (auto item : scene->items()) {
        if (auto line = dynamic_cast<QGraphicsLineItem*>(item)) {
            QLineF lineF = line->line();
            QPointF vertexCenter = vertexItem->pos() + QPointF(15, 15);

            if (lineF.p1() == vertexCenter || lineF.p2() == vertexCenter) {
                itemsToRemove.append(line);

                for (auto label : scene->items(lineF.center())) {
                    if (dynamic_cast<QGraphicsTextItem*>(label)) {
                        itemsToRemove.append(label);
                    }
                }
            }
        }
        else if (auto text = dynamic_cast<QGraphicsTextItem*>(item)) {
            if (text->pos() == vertexItem->pos() + QPointF(15 - text->boundingRect().width()/2,
                                                         15 - text->boundingRect().height()/2)) {
                itemsToRemove.append(text);
            }
        }
    }

    for (auto item : itemsToRemove) {
        scene->removeItem(item);
        delete item;
    }

    scene->removeItem(vertexItem);
    delete vertexItem;
    vertices.remove(vertexIndex);
    adjacencyMatrix.remove(vertexIndex);
    for (auto &row : adjacencyMatrix) {
        row.remove(vertexIndex);
    }

    for (int i = 0; i < vertices.size(); ++i) {
        for (auto item : scene->items(vertices[i]->pos())) {
            if (auto text = dynamic_cast<QGraphicsTextItem*>(item)) {
                text->setPlainText(QString::number(i + 1));
            }
        }
    }

    ui->resultLabel->setText(QString("Вершина %1 удалена").arg(vertexIndex + 1));
}

void TSP::on_removeEdgeButton_clicked()
{
    if (selectedEdgeItems.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет рёбер для удаления!");
        return;
    }

    QStringList edgeList;
    for (int i = 0; i < selectedEdgeItems.size(); ++i) {
        int from = selectedEdges[i].first + 1;
        int to = selectedEdges[i].second + 1;
        edgeList << QString("%1 ↔ %2").arg(from).arg(to);
    }

    bool ok;
    QString edgeToRemove = QInputDialog::getItem(this, "Удаление рёбер", "Выберите ребро для удаления:", edgeList, 0, false, &ok);
    if (!ok) return;

    int edgeIndex = edgeList.indexOf(edgeToRemove);
    if (edgeIndex == -1) return;

    int fromIdx = selectedEdges[edgeIndex].first;
    int toIdx = selectedEdges[edgeIndex].second;

    QGraphicsLineItem *edge = selectedEdgeItems[edgeIndex];
    scene->removeItem(edge);
    delete edge;

    QGraphicsTextItem *costLabel = selectedEdgeLabels[edgeIndex];
    scene->removeItem(costLabel);
    delete costLabel;

    adjacencyMatrix[fromIdx][toIdx] = INT_MAX;
    adjacencyMatrix[toIdx][fromIdx] = INT_MAX;

    selectedEdges.removeAt(edgeIndex);
    selectedEdgeItems.removeAt(edgeIndex);
    selectedEdgeLabels.removeAt(edgeIndex);

    ui->resultLabel->setText(QString("Ребро между %1 и %2 удалено").arg(fromIdx + 1).arg(toIdx + 1));
}

void TSP::on_clearButton_clicked()
{
    scene->clear();
    vertices.clear();
    adjacencyMatrix.clear();
    selectedEdges.clear();
    selectedEdgeItems.clear();
    selectedEdgeLabels.clear();
    totalCost = 0;
    ui->resultLabel->setText("Граф очищен");
}

bool TSP::isOverlapping(int x, int y, int minDistance)
{
    for (auto vertex : vertices) {
        QPointF pos = vertex->pos();
        if (sqrt(pow(x - pos.x(), 2) + pow(y - pos.y(), 2) < minDistance))
{
            return true;
        }
    }
    return false;
}

void TSP::on_deep_clicked()
{
    if (vertices.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Граф не содержит вершин!");
        return;
    }

    // Создаем список посещенных вершин
    QVector<bool> visited(vertices.size(), false);
    QVector<int> traversalOrder;

    // Выбираем начальную вершину (можно первую, или запросить у пользователя)
    int startVertex = 0;

    // Выполняем обход в глубину
    dfs(startVertex, visited, traversalOrder);

    // Формируем строку результата
    QString result = "Порядок обхода вершин: ";
    for (int i = 0; i < traversalOrder.size(); ++i) {
        if (i != 0) result += " → ";
        result += QString::number(traversalOrder[i] + 1);
    }

    // Выводим результат
    ui->resultLabel->setText(result);
}

void TSP::dfs(int vertex, QVector<bool>& visited, QVector<int>& traversalOrder)
{
    // Помечаем текущую вершину как посещенную
    visited[vertex] = true;
    traversalOrder.append(vertex);

    // Получаем список смежных вершин
    QVector<int> neighbors;
    for (int i = 0; i < vertices.size(); ++i) {
        if (adjacencyMatrix[vertex][i] != INT_MAX && !visited[i]) {
            neighbors.append(i);
        }
    }

    // Рекурсивно посещаем все смежные вершины
    for (int neighbor : neighbors) {
        if (!visited[neighbor]) {
            dfs(neighbor, visited, traversalOrder);
        }
    }
}

void TSP::on_width_clicked()
{
    if (vertices.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Граф не содержит вершин!");
        return;
    }

    // Выбираем начальную вершину (первую или можно запросить у пользователя)
    int startVertex = 0;

    // Выполняем обход в ширину
    bfs(startVertex);
}

void TSP::bfs(int startVertex)
{
    QVector<bool> visited(vertices.size(), false);
    QQueue<int> queue;
    QVector<int> traversalOrder;

    // Начинаем с начальной вершины
    visited[startVertex] = true;
    queue.enqueue(startVertex);

    while (!queue.isEmpty()) {
        int currentVertex = queue.dequeue();
        traversalOrder.append(currentVertex);

        // Находим всех соседей текущей вершины
        for (int i = 0; i < vertices.size(); ++i) {
            if (adjacencyMatrix[currentVertex][i] != INT_MAX && !visited[i]) {
                visited[i] = true;
                queue.enqueue(i);
            }
        }
    }

    // Формируем строку результата
    QString result = "Порядок обхода вершин: ";
    for (int i = 0; i < traversalOrder.size(); ++i) {
        if (i != 0) result += " → ";
        result += QString::number(traversalOrder[i] + 1);
    }

    // Выводим результат
    ui->resultLabel->setText(result);
}



void TSP::on_Dijkstra_clicked()
{
    if (vertices.empty()) {
        QMessageBox::warning(this, "Ошибка", "Граф не содержит вершин!");
        return;
    }

    // Запрашиваем начальную вершину
    QStringList vertexList;
    for (int i = 0; i < vertices.size(); ++i) {
        vertexList << QString::number(i + 1);
    }

    bool ok;
    QString startVertex = QInputDialog::getItem(this, "Алгоритм Дейкстры",
                                                "Выберите начальную вершину:",
                                                vertexList, 0, false, &ok);
    if (!ok) return;

    dijkstra(startVertex.toInt() - 1);  // Передаем индекс вершины
}

void TSP::dijkstra(int startVertex)
{
    int n = vertices.size();
    QVector<int> dist(n, INT_MAX);
    QVector<int> parent(n, -1);
    QVector<bool> visited(n, false);

    dist[startVertex] = 0;

    using Pair = std::pair<int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (adjacencyMatrix[u][v] != INT_MAX && !visited[v]) {
                int newDist = dist[u] + adjacencyMatrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    QString result = "Кратчайшие пути от вершины " + QString::number(startVertex + 1) + ":\n";

    for (int i = 0; i < n; ++i) {
        if (i != startVertex) {
            QVector<int> path = getShortestPath(parent, i);
            result += QString("До %1: %2 (Расстояние: %3)\n")
                          .arg(i + 1)
                          .arg(pathToText(path))
                          .arg(dist[i] == INT_MAX ? "∞" : QString::number(dist[i]));
        }
    }

    ui->resultLabel->setText(result);
}

QVector<int> TSP::getShortestPath(const QVector<int>& parent, int endVertex) const
{
    QVector<int> path;
    for (int v = endVertex; v != -1; v = parent[v]) {
        path.prepend(v);
    }
    return path;
}

QString TSP::pathToText(const QVector<int>& path) const
{
    if (path.isEmpty()) return "Нет пути";

    QString result;
    for (int i = 0; i < path.size(); ++i) {
        if (i != 0) result += " → ";
        result += QString::number(path[i] + 1);
    }
    return result;
}

void TSP::on_Floyd_clicked()
{
    if (vertices.empty()) {
        QMessageBox::warning(this, "Ошибка", "Граф не содержит вершин!");
        return;
    }

    floydWarshall();
}

void TSP::floydWarshall()
{
    int n = vertices.size();
    // Матрица расстояний
    QVector<QVector<int>> dist(n, QVector<int>(n));
    // Матрица для восстановления путей
    QVector<QVector<int>> next(n, QVector<int>(n, -1));

    // Инициализация матриц
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Копируем веса рёбер из матрицы смежности
            dist[i][j] = adjacencyMatrix[i][j];
            // Если есть прямое ребро между i и j, запоминаем следующую вершину
            if (adjacencyMatrix[i][j] != INT_MAX && i != j) {
                next[i][j] = j;
            }
        }
    }

    // Основной алгоритм
    for (int k = 0; k < n; ++k) { // Промежуточная вершина
        for (int i = 0; i < n; ++i) { // Начальная вершина
            for (int j = 0; j < n; ++j) { // Конечная вершина
                // Проверяем, можно ли улучшить путь через вершину k
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    // Обновляем расстояние
                    dist[i][j] = dist[i][k] + dist[k][j];
                    // Обновляем информацию для восстановления пути
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Вывод результатов
    QString result = getAllPairsShortestPaths(dist, next);
    ui->resultLabel->setText(result);
}

QString TSP::getAllPairsShortestPaths(const QVector<QVector<int>>& dist,
                                      const QVector<QVector<int>>& next) const
{
    QString result = "Кратчайшие пути между всеми парами вершин:\n";
    int n = vertices.size();
    // Перебираем все пары вершин
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                result += QString("%1 → %2: ").arg(i+1).arg(j+1);
                // Проверяем существование пути
                if (dist[i][j] == INT_MAX) {
                    result += "Нет пути\n";
                } else {
                    // Восстанавливаем и форматируем путь
                    result += reconstructPath(i, j, next) +
                              QString(" (Расстояние: %1)\n").arg(dist[i][j]);
                }
            }
        }
    }

    return result;
}

QString TSP::reconstructPath(int i, int j,
                             const QVector<QVector<int>>& next) const
{
    if (next[i][j] == -1) return "Нет пути";

    QString path = QString::number(i+1);

    // Последовательно проходим по вершинам пути
    while (i != j) {
        i = next[i][j]; // Переходим к следующей вершине
        path += " → " + QString::number(i+1);
    }
    return path;
}

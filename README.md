# Qt TCP Server & Client with Structure Transfer

Этот проект реализует TCP-сервер и клиент с использованием **Qt 6 (C++ / Qt Widgets)**. При подключении клиента к серверу отправляется структура с сообщением, временем и количеством подключённых клиентов. Клиент отображает полученные данные в графическом интерфейсе.

---

## 📦 Что реализовано

- ✅ TCP-сервер (порт `2323`)
- ✅ Клиенты подключаются и отправляют текст
- ✅ Сервер формирует структуру `ClientInfo`:
  - `QTime time` — время получения сообщения
  - `QString message` — текст сообщения
  - `int clientCount` — количество подключённых клиентов
- ✅ Сервер рассылает структуру всем клиентам
- ✅ Клиент отображает структуру в `QTextBrowser`

---

## 📁 Структура проекта

project/
├── main.cpp # Сервер или клиент (в зависимости от запуска)
├── mainwindow.h/.cpp # Клиентская логика и GUI
├── server.h/.cpp # Серверная логика
├── shared.h # Структура ClientInfo
├── mainwindow.ui # Интерфейс клиента
├── README.md # Этот файл


---

## 🚀 Инструкция по запуску

### 1. Скачай и установи Qt

[Скачать Qt Open Source](https://www.qt.io/download-open-source)

Убедись, что установлен:
- Qt 6.x
- Qt Creator

---

### 2. Запусти сервер

1. Открой `server.h`, `server.cpp` и `main.cpp` (серверный).
2. Запусти проект как **консольное приложение**.
3. Сервер начинает слушать порт `2323`.

---

### 3. Запусти клиент

1. Открой `mainwindow.h`, `mainwindow.cpp`, `mainwindow.ui`, `main.cpp` (клиентский).
2. Построй GUI-приложение.
3. В интерфейсе нажми **"Подключиться"**, затем введи сообщение и нажми **Enter** или **"Отправить"**.

---

## 🧩 Пример структуры ClientInfo

```cpp
struct ClientInfo {
    QTime time;
    QString message;
    int clientCount;
};
Сериализация:

QDataStream &operator<<(QDataStream &out, const ClientInfo &info);
QDataStream &operator>>(QDataStream &in, ClientInfo &info);
🖼️ Интерфейс клиента

QLineEdit — ввод текста
QPushButton — "Подключиться", "Отправить"
QTextBrowser — отображение истории сообщений
📜 Пример вывода

12:44:22 Hello world | Clients connected: 3
12:44:24 Test message | Clients connected: 4
🔧 Возможные доработки

Вывод списка всех клиентов
Статус соединения (индикатор)
Автоматическое переподключение
TLS/SSL шифрование (через QSslSocket)
⚙️ Зависимости

Qt 6.2 или выше
Qt Widgets
Qt Network

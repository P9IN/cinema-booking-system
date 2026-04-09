```markdown
# Cinema Booking System

Клиент-серверное приложение для бронирования билетов в кино.

## Технологии

- Backend: Python, Django REST Framework, SQLite
- Frontend: C++, Qt 6.8.2, httplib.h
- Архитектура: REST API, SOLID, Dependency Injection, Strategy

## Требования

- Python 3.10 или выше
- Qt 6.8.2 (модули: core, gui, network, widgets)
- Visual Studio 2022 (с поддержкой C++)
- Git

## Установка и запуск

### 1. Клонирование репозитория

```bash
git clone https://github.com/P9IN/cinema-booking-system.git
cd cinema-booking-system
```

### 2. Запуск Backend

Перейдите в папку Backend, создайте и активируйте виртуальное окружение:

```bash
cd Backend
python -m venv venv
```

Windows:
```bash
venv\Scripts\activate
```

Linux/Mac:
```bash
source venv/bin/activate
```

Установите зависимости:

```bash
pip install -r requirements.txt
```

Выполните миграции:

```bash
python manage.py migrate
```

Создайте суперпользователя:

```bash
python manage.py createsuperuser
```

Запустите сервер:

```bash
python manage.py runserver
```

Сервер будет доступен по адресу: `http://127.0.0.1:8000`

### 3. Настройка токена аутентификации

Откройте файл `Backend/dronExam/settings.py` и убедитесь, что в `INSTALLED_APPS` добавлен `rest_framework.authtoken`:

```python
INSTALLED_APPS = [
    ...
    'rest_framework',
    'rest_framework.authtoken',
    'cinema',
]
```

Создайте токен для пользователя:

```bash
python manage.py shell -c "from cinema.models import CinemaUser; from rest_framework.authtoken.models import Token; user = CinemaUser.objects.first(); token = Token.objects.create(user=user); print(f'Token: {token.key}')"
```

Скопируйте полученный токен. Он понадобится для настройки клиента.

### 4. Сборка Frontend

Откройте файл `Frontend/drom.sln` в Visual Studio 2022.

Выберите конфигурацию `Debug x64`.

Выполните сборку: `Build` -> `Build Solution` (Ctrl+Shift+B)

### 5. Настройка токена в клиенте

В файле `Frontend/Services/ApiService.cpp` найдите строку с токеном и замените его на скопированный ранее:

```cpp
const QString API_TOKEN = "ваш_токен_сюда";
```

## Описание API

Ниже приведены эндпоинты, которые использует клиент для работы с сервером. Эта информация нужна для понимания механики запросов, а не для настройки.

### GET /sessions

Возвращает список доступных сеансов.

Пример ответа:

```json
{
  "id": 1,
  "date": "2025-02-15T18:00:00Z",
  "price": 500,
  "movie": {
    "name": "Дюна 2",
    "rating": 8.5,
    "genre": "Фантастика",
    "age": 12
  }
}
```

### POST /ticket

Создаёт бронирование билета. Требуется авторизация.

Заголовок запроса:

```
Authorization: Token ваш_токен
```

Тело запроса:

```json
{
  "session": 1,
  "seat": 15
}
```

## Структура проекта

```
cinema-booking-system/
??? Backend/
?   ??? cinema/            # models, views, serializers
?   ??? dronExam/          # Настройки Django
?   ??? manage.py
?   ??? requirements.txt
??? Frontend/
?   ??? Domain/            # Классы данных: Movie.h, Session.h
?   ??? Interfaces/        # Абстрактные классы для сервисов (IApiService, IAuthService и др.)
?   ??? Services/          # Реализация сервисов
?   ??? UI/                # Qt виджеты: главное окно (MainWindow), диалог профиля (UserProfileDialog)
?   ??? main.cpp
?   ??? httplib.h
?   ??? drom.sln
??? README.md
```

## Возможные проблемы

**Ошибка: `No installed app with label 'authtoken'`**

Решение: добавь `rest_framework.authtoken` в `INSTALLED_APPS` и выполни `python manage.py migrate`.

**Ошибка: `ModuleNotFoundError: No module named 'dotenv'`**

Решение: установи пакет `pip install python-dotenv`.

**Клиент не подключается к серверу**

Проверь, что сервер запущен на порту 8000, и токен в коде клиента указан верно.
# Музыкальная база данных

## Зависимости
- Docker
- Docker Compose

## Инструкция по запуску

### 1. Клонируйте репозиторий
```bash
git clone https://github.com/Alexandr-bit253/sql/tree/main/data_selection/task_4
cd task_4
```
### 2. Запустите контейнер
```bash
docker-compose up -d
```
### 3. Выполните запросы
```bash
docker exec -i music_db psql -U music_user -d music_db < queries.sql
```
# Client Manager

Приложение для управления клиентами с использованием PostgreSQL, C++17 и Docker.

## Зависимости
### Системные (Ubuntu)
```bash
sudo apt-get update && sudo apt-get install -y \
    docker.io \
    docker-compose \
    build-essential \
    cmake \
    libpqxx-dev
````
## Инструкция по запуску

### 1. Клонируйте репозиторий и перейдите в директорию проекта
```bash
   git clone https://github.com/your-name/client-manager.git
   cd client-manager
```

### 2. Сборка приложения
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

### 3. Создайте .env файл
```bash
cp .env.example .env
```

### 4. Запустите контейнер
```bash
docker-compose up -d
```

### 5. Запуск программы
```bash
./build/main
```
## Сортировка данных с входной ленты на выходную
### Содержание репозитория

Репозиторий состоит из следующих файлов:

- `src/`: папка с исходниками проекта
- `txt/`: папка с текстовыми файлами для проверки работы программы
- `build.sh`: shell-скрипт для сборки проекта
- `CMakeLists.txt`: файл CMake для автоматической сборки
- `README.md`: файл с информацией о репозитории

### Инструкция по сборке

Для начала склонируйте репозиторий к себе на компьютер через команду терминала:
```
git clone https://github.com/sindwrr/tape_sort.git
```
Способы сборки проекта:

#### 1. Через shell-скрипт (для Linux)
Откройте терминал в папке с репозиторием. Сначала дайте доступ к скрипту командой:
```
chmod +x build.sh
```
Затем запустите скрипт через терминал:
```
./build.sh
```
Появится папка `build`. В ней будет находиться исполняемый файл `app`.

#### 2. Через CMake
Откройте терминал в папке с репозиторием. В окне терминала поочередно выполните следующие команды:
```
mkdir build
cd build
cmake ..
cmake --build . --target app
```
После их выполнения в новой папке `build` будет находиться исполняемый файл `task` (на Windows `app.exe` будет находиться в `build/Debug`). Затем можно выйти из папки `build` (`cd ..`) и запустить программу.

#### 3. Через команду компилятора
Откройте терминал в папке с репозиторием. Сначала создайте папку `build`:
```
mkdir build
```
Затем выполните следующую команду:
```
clang++ -std=c++17 src/main.cpp src/FileTape.cpp src/TapeSort.cpp -o build/app 
```
То же самое работает с `g++`. В обоих случаях в папке `build` появится исполняемый файл `app`.

### Аргументы командной строки
Команда запуска должна принимать вид:
```
./build/app <X> <Y> <Z>
``` 
где X - имя входного файла, Y - имя выходного файла, Z - имя конфигурационного файла.

### Конфигурационный файл 

Для правильной работы программы конфигурационный файл должен содержать 4 строки, в каждой из которых - по одному числу.
- 1-е число: задержка по чтению с ленты
- 2-е число: задержка по записи в ленту
- 3-е число: задержка по перемотке ленты
- 4-е число: задержка по сдвигу на одну позицию

Числа отображают задержку в *миллисекундах*.

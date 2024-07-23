## Сборка
Проект планируется быть кроссплатформенным, в настоящее время протестирован на Windows, Linux и Mac.
Для сборки необходимы только Git, CMake и компилятор

```powershell
git clone https://github.com/simple-coding-channel/battle_city.git
cd battle_city
mkdir build
cmake ..
cmake --build .
```

Под Ubuntu возможно нужно будет еще установить следующую зависимость:
```powershell
sudo apt-get install xorg-dev libglu1-mesa-dev
```

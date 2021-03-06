# Ассемблер PDP11/БК0010

Транслятор ассемблерных программ для процессоров семейства DEC в машинный код PDP11/БК0010.


## Как собрать транслятор из исходников

```bash
make
```

Скомпилированые бинарники под некоторые платформы лежат в папке [release](https://github.com/imachug/pdp11asm/tree/master/release).


## Трансляция ассемблерного текста в машинные коды


1. Скопируйте бинарник под вашу платформу куда-нибудь (например, `/Users/Ivanq/Documents/BK0010/compiler` на MacOS или `/home/Documents/BK0010/compiler` на Linux).

2. Скачайте файл [compile.sh](https://gist.github.com/imachug/3a27a7516fc50b5b8b2595b8af2d571e) и положите его в ту же директорию.

3. Добавьте права на выполение командой `chmod +x compiler compile.sh`.

4. Вам понадобится текстовый редактор Sublime Text и [плагин для подсветки синтаксиса DEC/PDP11](https://gist.github.com/imachug/3ab11df5e91c8d815a8c63a76bb08b14).

5. В настройках Sublime Text выберете *Browse packages...*. Откроется папка пакетов. Скачайте файл [BK0010.sublime-build](https://gist.github.com/imachug/223e7b30b041ec93938f1c8dda6afaf7) и положите его в поддиректорию `User`. Откройте файл текстовым редактором и замените в нём `/Users/Ivanq/Documents/BK0010/compile.sh` на полный путь к файлу [compile.sh](https://gist.github.com/imachug/3a27a7516fc50b5b8b2595b8af2d571e) на вашем компьютере (относительный путь типа `~/Documents` почему-то не работает). Чтобы узнать полный путь к файлу на MacOS, нажмите на него правой кнопкой мыши, затем удерживайте <kbd>alt</kbd> и выберете *Copy as Pathname*.

6. Теперь, чтобы транслировать ассемблерную программу, нажмите в Sublime Text <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>, выберите `BK0010`. Либо в меню Sublime Text `Tools\Build System` выберите `BK0010`. В следующий раз будет работать просто <kbd>Ctrl</kbd>+<kbd>B</kbd>.

7. По умолчанию программа компилируется с адреса 1000. Это значение можно изменить добавлением строки `.LINK 3000` в самое начало программы (здесь `3000` - новый адрес компиляции). Результат работы транслятора - BIN-файл с машинным кодом и заголовком, содержащим адрес и длину - запишется в ту же директорию, где лежит исходный текст.

Имя выходного файла можно изменить, добавив в самый конец программы строку `make_bk0010_rom "file.bin"`. Там же можно указать область памяти БК, которая будет сохранена на диск: `make_bk0010_rom "file.bin", 760, 40000` (сохранится вся область памяти с 760 по 40000, независимо от того, по какому адресу скомпилирована программа). Если конечный адрес не указан, сохранится область памяти до последнего байта скомпилированной программы.

Можно сохранить данные в чистом виде, без заголовка. Для этого вместо команды `make_bk0010_rom` используйте `make_raw` с теми же параметрами. По умолчанию имя выходного файла будет без расширения.

Помимо исполняемого файла, сохраняется текстовый файл .lst для удобства отладки.

8. Для запуска скомпилированной программы вам понадобится эмулятор БК0010/11М, например [BK2010 Java](http://bk-files.perestoroniny.ru/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BD%D0%B8%D0%BA%D0%B0%20%D0%91%D0%9A-0010%5B.01%5D,%20%D0%91%D0%9A-0011%5B%D0%9C%5D/[%D0%AD%D0%BC%D1%83%D0%BB%D1%8F%D1%82%D0%BE%D1%80%D1%8B]/BK2010%20-%20%D0%AD%D0%BC%D1%83%D0%BB%D1%8F%D1%82%D0%BE%D1%80%20%D0%91%D0%9A-0010%20%D0%BD%D0%B0%20%D0%BF%D0%BB%D0%B0%D1%82%D1%84%D0%BE%D1%80%D0%BC%D0%B5%20Java%20v0.5%20(%D0%A2%D0%B8%D1%88%D0%B8%D0%BD%D0%B0)/).

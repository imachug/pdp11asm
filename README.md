# PDP11ASM

Компилятор под PDP11/BK0010.

```bash
g++ pdp11asm/*.cpp -o compiler
```

Некоторые релизы уже скомпилированы в папку `releases`.


## Компиляция из Sublime Text

1. Скопируйте бинарник под вашу платформу куда-нибудь (например, `/Users/Ivanq/Documents/BK0010/compiler` на OS X или `/home/Documents/BK0010/compiler` на Linux).

2. Создайте файл `compile.sh` в той же директории и добавьте ему права на выполнение (например, `chmod +x compile.sh`):

```bash
#!/usr/bin/env bash

cd "$(dirname "$0")"

echo Compiling $1
rm _code.asm
cp "$1" _code.asm

./compiler _code.asm >_log
if [ $? -ne 0 ]; then
    cat _log | python -c "import sys; print sys.stdin.read().decode('utf-8', 'ignore').encode('utf-8')" | tail -2 | head -1
    exit
fi

name="$1"
name="$(basename -s ".asm" $name)"
name="$(basename -s ".mac" $name)"
name="$name.exe"

rm "$(dirname "$1")/$name" 2>/dev/null
mv _code.bin "$(dirname "$1")/$name"

echo Saved as $name
```

По умолчанию компилятор создает EXE-файл, но если Вам нужен BIN-файл, добавьте строку `make_bk0010_rom` в исходный код на ассемблере и замените `name="$name.exe"` на `name="$name.exe"` в файле `compile.sh`.

3. Откройте папку пакетов, выбрав в настройках Sublime *Browse packages...*, а затем создайте файл `Packages/User/BK0010.sublime-build`:

```json
{
    "shell_cmd": "<path_to_compiler>/compile.sh \"$file_path/$file_name\""
}
```

4. Теперь, чтобы собрать файл, нажмите <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>, выберите `BK0010`. В следующий раз будет работать просто <kbd>Ctrl</kbd>+<kbd>B</kbd>.
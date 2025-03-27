# gcc src/main.c src/background.c src/common.c src/db.c -o main.exe -O1 -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -I'C:\Program Files\MySQL\MySQL Server 8.0\include' -L'C:\Program Files\MySQL\MySQL Server 8.0\lib'

# gcc -o main.exe src\main.c src\common.c src\background.c -Iinclude -IC:\mysql\include -Llib -LC:\mysql\lib -lraylib -lmysql

gcc src/main.c src/background.c src/common.c src/db.c -o main.exe -O1 -std=c99 -Wno-missing-braces `
    -I include/ `
    -I "C:\Program Files\MySQL\MySQL Connector C 6.1\include" `
    -L lib/ `
    -L "C:\Program Files\MySQL\MySQL Connector C 6.1\lib" `
    -lraylib -lopengl32 -lgdi32 -lwinmm -lmysql
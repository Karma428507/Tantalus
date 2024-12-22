REM Compiler options
SET INCLUDE=-Iinclude
REM Source codes
SET COMPILER_AMD64=src/compiler/AMD64/*.c
SET COMPILER_POWERPC64=src/compiler/POWERPC64/*.c
SET COMPILER_X86=src/compiler/x86/*.c
SET COMPILER_X86-64=src/compiler/x86-64/*.c
SET SRC_COMPILER_BASE=src/compiler/Base/*.c
SET SRC_COMPILER=%COMPILER_AMD64% %COMPILER_POWERPC64% %COMPILER_X86% %COMPILER_X86-64% %SRC_COMPILER_BASE%

SET SRC_ASSEMBLER=src/assembler/*.c
SET SRC_EXECUTABLE=src/executable/*.c
SET SRC_LEXER=src/lexer/*.c
SET SRC_OPTIMIZATION=src/optimization/*.c
SET SRC_PARSER=src/parser/*.c
SET SRC_PREPROCESS=src/preprocess/*.c
SET SRC_MAIN=src/main.c %SRC_ASSEMBLER% %SRC_EXECUTABLE% %SRC_LEXER% %SRC_OPTIMIZATION% %SRC_PARSER% %SRC_PREPROCESS%

gcc %SRC_COMPILER% %SRC_MAIN% %INCLUDE% -o build/TantalusCompiler.exe

rem Debugging
cd build
TantalusCompiler debug.asm -f elf64 -o test.elf
pause
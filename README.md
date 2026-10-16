# T9 Search

Simple C program for searching contacts using T9 keypad mapping.

The program reads contacts from standard input, where each contact consists of a name and a phone number, and filters them using a numeric search pattern.

## Features

- Search in both contact names and phone numbers
- Case-insensitive T9 matching
- Support for `+` as `0`
- Input validation for names, phone numbers and search arguments
- Streaming input processing without dynamic memory allocation

## Build

```bash
gcc -std=c23 -Wall -Wextra -Werror -pedantic t9search.c -o t9search
```

## Usage

Show all contacts:
```bash
    ./t9search < seznam.txt
```

Search using a T9 pattern:
```bash
    ./t9search 5262 < seznam.txt
```

Example contact:
```text
    Jana Novotna
    777987654
```

Pattern `5262` matches `Jana`.

The project was created as part of the IZP course at FIT VUT.
# MyCowsay
A course project based on the cowsay program. The goal was to rewrite it and add new features. I extended it further than the initial requirements.

---

## Features

### Basic cowsay
- Display a custom message with ASCII cow
- Display help (`-h`)
- Change eyes (`-e`)
- Change tongue (`-T`)
- Change color (`-c`)
- Wrap message width (`-W`)
- Predefined states (borg, dead, greedy, paranoid, stoned, tired, wired, youthful)

### Additional features
- Cow explosion mode (`-E`)
- Cow running animation (`-r`)
- Color list display (`-l`)

### Games
- **Cow Game** (`-G`)
  - Move using `Z Q S D`
  - Objective: find the hidden message (`$`)
  - Grass changes color where the cow walks
  - Optional debug mode with `--dev`

- **Tamagocow** (`-C`)
  - Virtual cow simulation
  - Fitness system
  - Debug mode available with `--dev`

---

## Controls (Game mode)

- `Z Q S D` → move the cow
- `E` → exit game

---

## Build

This project uses a Makefile.

### Compile
```bash
make
```
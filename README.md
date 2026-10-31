<div align="center">

# 🎶 SpinTune

### *Pulsa, gira y suena*

Mantén pulsado un botón y un servo de rotación continua gira mientras suena una melodía festiva. Una pantalla OLED te dice qué está pasando: **"Interactuando..."**.

![Plataforma](https://img.shields.io/badge/plataforma-Arduino%20%2F%20KidsUno-00979d)
![Lenguaje](https://img.shields.io/badge/lenguaje-C%2B%2B%20(Arduino)-blue)
![Servo](https://img.shields.io/badge/servo-360%C2%B0%20continuo-orange)
![Pantalla](https://img.shields.io/badge/OLED-128×64%20SSD1306-lightgrey)
![Sonido](https://img.shields.io/badge/buzzer-8%20notas-ff69b4)
![Licencia](https://img.shields.io/badge/licencia-MIT-green)

</div>

---

## 📖 Tabla de contenidos

1. [¿Qué es SpinTune?](#-qué-es-spintune)
2. [Características](#-características)
3. [Requisitos](#-requisitos)
4. [Conexiones](#-conexiones)
5. [Instalación](#-instalación)
6. [Cómo usarlo](#-cómo-usarlo)
7. [La melodía](#-la-melodía)
8. [Pantalla OLED](#-pantalla-oled)
9. [Estructura del código](#-estructura-del-código)
10. [Detalles técnicos](#-detalles-técnicos)
11. [Personalización](#-personalización)
12. [Solución de problemas](#-solución-de-problemas)
13. [Limitaciones conocidas](#-limitaciones-conocidas)
14. [Ideas para el futuro](#-ideas-para-el-futuro)
15. [Contribuir](#-contribuir)
16. [Licencia](#-licencia)

---

## 🎠 ¿Qué es SpinTune?

**SpinTune** es un proyecto de Arduino que combina **movimiento, sonido y una pantalla** con un solo botón. Mientras mantienes el botón pulsado:

- 🔄 Un **servo de rotación continua** gira a toda velocidad.
- 🎵 Un **buzzer** reproduce en bucle una **melodía festiva original** de 8 notas.
- 🖥️ Una **pantalla OLED** muestra el mensaje *"Interactuando..."*.

Al soltar el botón, todo se detiene: el servo se apaga, la música calla y la pantalla vuelve a decir *"Pulsa el boton"*. Funciona como un pequeño carrusel musical, una decoración animada o una base para proyectos de feria de ciencias.

> Repositorio: <https://github.com/miusarname2/SpinTune>

---

## ✨ Características

- 🕹️ **Control con un solo botón:** mantener pulsado = activar; soltar = detener.
- 🔁 **Melodía en bucle** mientras el botón está pulsado, siempre desde la primera nota.
- ⚡ **Sin bloqueos:** la música se gestiona con `millis()`, así que el botón responde al instante.
- 🔌 **Servo seguro:** se conecta solo cuando se necesita (`attach`) y se desconecta al soltar (`detach`), evitando zumbidos y consumo en reposo.
- 🖥️ **Pantalla OLED** con dos estados claros: reposo y activo.
- 🧩 **Tolerancia a fallos:** si la pantalla no se detecta, el resto del proyecto sigue funcionando y se avisa por el monitor serie.
- 📦 **Un solo archivo fuente**, fácil de leer y modificar.

---

## 🧰 Requisitos

### Hardware

| Componente | Detalle |
|------------|---------|
| Placa | **KidsUno** o compatible con Arduino UNO |
| Botón | Pulsador conectado al pin `D3` (activo en `LOW`) |
| Buzzer | Buzzer pasivo (o activo) en el pin `D6` |
| Servo | Servo de **rotación continua (360°)** en el pin `D13` |
| Pantalla | OLED **SSD1306 128×64** por I2C (dirección `0x3C`) |
| Alimentación | Fuente adecuada para el servo (ver nota abajo) |

> ⚡ **Importante:** los servos consumen bastante corriente al arrancar. Si la placa se reinicia o la pantalla parpadea cuando el servo gira, alimenta el servo con una fuente externa y **une todas las tierras (GND)**.

### Software

- [Arduino IDE](https://www.arduino.cc/en/software) (o [PlatformIO](https://platformio.org/)).
- Librerías:

| Librería | Origen |
|----------|--------|
| `Adafruit SSD1306` | Gestor de librerías de Arduino |
| `Adafruit GFX Library` | Dependencia de la anterior (se instala junto a ella) |
| `Servo` | Incluida con Arduino |

---

## 🔌 Conexiones

| Elemento | Pin / Bus | Notas |
|----------|-----------|-------|
| Botón | `D3` | Lee `LOW` cuando está pulsado |
| Buzzer | `D6` | Señal de la melodía |
| Servo 360° (señal) | `D13` | Alimentación y GND según el servo |
| Pantalla OLED | `SDA` / `SCL` | Dirección `0x3C` |

> ℹ️ El código configura el botón con `pinMode(BUTTON_PIN, INPUT)`, **sin resistencia pull-up interna**. Usa un módulo de botón que ya entregue `LOW` al pulsar o añade una resistencia pull-up externa (por ejemplo, 10 kΩ a 5 V). Si prefieres usar la interna, cambia a `INPUT_PULLUP` y conecta el botón entre `D3` y GND.

---

## 📥 Instalación

### 1. Clonar el repositorio

```bash
git clone https://github.com/miusarname2/SpinTune.git
cd SpinTune
```

### 2. Opción A: con Arduino IDE

1. Abre el archivo del sketch (`.ino`) con **Arduino IDE**.
2. Instala la librería desde **Herramientas → Administrar bibliotecas…**:
   - `Adafruit SSD1306` (acepta instalar también `Adafruit GFX Library`).
3. Selecciona tu placa en **Herramientas → Placa** (Arduino UNO o KidsUno) y el puerto correcto.
4. Pulsa **Subir**.
5. Opcional: abre el **Monitor serie** a **9600 baudios** para ver los avisos.

### 3. Opción B: con PlatformIO

Agrega estas dependencias a tu `platformio.ini`:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 9600
lib_deps =
    adafruit/Adafruit SSD1306
    adafruit/Adafruit GFX Library
```

Luego compila y sube:

```bash
pio run -t upload
pio device monitor
```

> ℹ️ El nombre del archivo fuente puede variar según cómo lo hayas guardado en el repositorio. Ajusta las rutas al nombre real.

---

## 🚀 Cómo usarlo

1. Conecta la alimentación. La pantalla muestra **"Pulsa el boton"** y el servo permanece quieto.
2. **Mantén pulsado el botón**: el servo gira, empieza a sonar la melodía y la pantalla muestra **"Interactuando..."**.
3. **Suelta el botón**: el servo se detiene, la música se corta y la pantalla vuelve al mensaje de reposo.

| Acción | Servo | Sonido | Pantalla |
|--------|-------|--------|----------|
| Sin pulsar | Detenido | Silencio | `Pulsa el boton` |
| Pulsado | Gira a máxima velocidad | Melodía en bucle | `Interactuando...` |
| Soltar | Se detiene | Se corta al instante | `Pulsa el boton` |

---

## 🎵 La melodía

Una frase corta y festiva de **8 notas**, compuesta para este proyecto, que se repite mientras mantienes el botón pulsado.

| # | Nota (aprox.) | Frecuencia | Duración |
|---|---------------|-----------|----------|
| 1 | Sol (G5) | 784 Hz | 220 ms |
| 2 | Si (B5) | 988 Hz | 220 ms |
| 3 | Re (D6) | 1175 Hz | 360 ms |
| 4 | Si (B5) | 988 Hz | 220 ms |
| 5 | La (A5) | 880 Hz | 220 ms |
| 6 | Do (C6) | 1047 Hz | 360 ms |
| 7 | La (A5) | 880 Hz | 220 ms |
| 8 | Sol (G5) | 784 Hz | 420 ms |

- Entre nota y nota hay una pausa de **50 ms**.
- Cada vuelta completa dura unos **2,6 segundos**.
- Siempre arranca desde la primera nota al pulsar el botón.

---

## 🖥️ Pantalla OLED

```
En reposo:                  Activo:

                             Interactu
                             ando...
   Pulsa el boton
```

| Estado | Texto | Tamaño |
|--------|-------|--------|
| Reposo | `Pulsa el boton` | Pequeño |
| Activo | `Interactu` / `ando...` (en dos líneas) | Grande (×2) |

> La pantalla se muestra rotada 180° (`setRotation(2)`). Si no se detecta, el monitor serie muestra: `No se pudo iniciar la pantalla OLED SSD1306.` y el resto del proyecto sigue funcionando.

---

## 🗂️ Estructura del código

Todo el proyecto vive en un único archivo, organizado así:

```
SpinTune
│
├── Constantes y variables globales
│     (pines, pulso del servo, tamaño de pantalla, melodía, estados)
│
├── 🎵 Melodía
│     Note (struct) · MELODY[] · startMelody · updateMelody
│
├── 🖥️ Pantalla
│     showStatus
│
├── ⚙️ setup()
│     Serie · Botón · Servo en neutro · Pantalla OLED
│
└── 🔁 loop()
      Lectura del botón · Arranque/parada del servo · updateMelody
```

---

## 🔧 Detalles técnicos

- **Servo continuo:** se controla con `writeMicroseconds()`. Un pulso de `1500 µs` equivale a "detenido", y `2000 µs` (`SERVO_FORWARD_US`) a giro hacia adelante a máxima velocidad.
- **Arranque seguro:** en `setup()` el servo recibe un pulso neutro de `1500 µs` y se desconecta inmediatamente, así no se mueve al encender.
- **Parada por desconexión:** al soltar el botón se hace `detach()`, que deja de enviar pulsos y detiene el servo sin vibraciones.
- **Detección de flancos:** el programa solo reacciona cuando cambia el estado (`buttonPressed && !servoRunning` y viceversa), no en cada vuelta del `loop()`.
- **Melodía no bloqueante:** `updateMelody()` compara `millis()` con `nextNoteAt`; cuando llega el momento lanza la siguiente nota con `tone(pin, frecuencia, duración)`. Usa `static_cast<long>(now - nextNoteAt) < 0` para que la comparación siga siendo correcta aunque `millis()` desborde (~49 días).
- **Bucle circular:** el índice de nota avanza con `(currentNote + 1) % MELODY_LENGTH`.
- **Silencio inmediato:** al soltar el botón se llama a `noTone()` para cortar la nota en curso.
- **Longitud automática:** `MELODY_LENGTH` se calcula con `sizeof`, así puedes añadir o quitar notas sin tocar nada más.

---

## 🎨 Personalización

| Quieres cambiar… | Dónde buscarlo |
|------------------|----------------|
| Pin del botón / buzzer / servo | `BUTTON_PIN`, `BUZZER_PIN`, `SERVO_PIN` |
| Sentido y velocidad del servo | `SERVO_FORWARD_US` (`1000` = sentido contrario, valores cercanos a `1500` = más lento) |
| La melodía | Arreglo `MELODY[]` (frecuencia en Hz y duración en ms) |
| Pausa entre notas | El `+ 50` en `updateMelody()` |
| Textos de la pantalla | Función `showStatus()` |
| Rotación de la pantalla | `display.setRotation(2)` en `setup()` |
| Dirección I2C de la pantalla | `0x3C` en `display.begin()` |

Ejemplo para añadir una nota (La a 880 Hz durante 300 ms):

```cpp
{880, 300},
```

---

## 🩺 Solución de problemas

| Problema | Posible solución |
|----------|------------------|
| El botón no hace nada | Revisa que entregue `LOW` al pulsar; si no, añade pull-up externa o usa `INPUT_PULLUP`. |
| El servo gira solo en reposo | El servo se desconecta al arrancar; si persiste, ajusta el punto neutro del servo (potenciómetro de ajuste). |
| El servo gira al revés | Cambia `SERVO_FORWARD_US` a `1000`. |
| No suena el buzzer | Verifica el pin `D6`, la polaridad y que sea un buzzer compatible con `tone()`. |
| La pantalla no enciende | Verifica la dirección `0x3C`, las conexiones `SDA`/`SCL` y que `Adafruit SSD1306` esté instalada. |
| La placa se reinicia al girar el servo | Usa fuente externa para el servo y une los GND. |
| La música se oye entrecortada | Es normal que haya una pausa de 50 ms entre notas; puedes reducirla en `updateMelody()`. |

---

## ⚠️ Limitaciones conocidas

- La melodía es **monofónica** (una nota a la vez), ya que usa `tone()`.
- El servo gira siempre a **máxima velocidad**: no hay control de velocidad ni de dirección en este código.
- Sin antirrebote: al ser un botón de "mantener pulsado", los rebotes son poco visibles, pero un botón de mala calidad podría provocar pequeños cortes.
- Al soltar el botón la melodía se corta de golpe, sin terminar la frase.
- En la placa UNO, el pin `D13` también tiene el LED integrado, que parpadeará con la señal del servo.

---

## 🔮 Ideas para el futuro

- [ ] Control de velocidad del servo con un potenciómetro.
- [ ] Alternar sentido de giro con un segundo botón.
- [ ] Varias melodías seleccionables (por ejemplo, de Halloween y de Navidad).
- [ ] Luces LED que se enciendan al ritmo de la música.
- [ ] Modo "toque" (un clic activa, otro clic detiene).
- [ ] Mostrar una animación o el nombre de la nota en la pantalla OLED.
- [ ] Hacer que el servo gire más rápido o más lento según la nota.

---

## 🤝 Contribuir

¡Las contribuciones son bienvenidas!

1. Haz un **fork** del repositorio.
2. Crea una rama para tu mejora: `git checkout -b feature/mi-mejora`
3. Haz tus cambios y pruébalos en hardware real.
4. Haz commit: `git commit -m "Añade mi mejora"`
5. Sube la rama: `git push origin feature/mi-mejora`
6. Abre un **Pull Request** describiendo qué cambia y por qué.

**Pautas sugeridas:**

- Mantén el estilo del código (constantes descriptivas, funciones cortas).
- Evita `delay()` en el bucle principal; usa `millis()`.
- Documenta cualquier cambio de pines o dirección I2C en este README.

---

## 📄 Licencia

Distribuido bajo la Licencia **MIT**. Consulta el archivo [LICENSE](LICENSE) para más detalles.

*Copyright (c) 2026 Oscar M. Alvarez G.*

---

## 🙌 Créditos

- Proyecto creado al 100% por [**miusarname2**](https://github.com/miusarname2).
- Melodía original compuesta para este proyecto.
- Hecho con ❤️ para la placa **KidsUno** y el ecosistema **Arduino**.

<div align="center">

**¿Te gustó SpinTune? ¡Dale una ⭐ al repositorio!**

[github.com/miusarname2/SpinTune](https://github.com/miusarname2/SpinTune)

</div>

<div align="center">

# 🔐 WiFi Scanner C++

![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Version](https://img.shields.io/badge/Version-2.0-blue?style=for-the-badge)

**Utilidad de consola para Windows que permite recuperar las contraseñas de las redes WiFi guardadas en el sistema.**

</div>

---

## 📋 Descripción

¿Alguna vez olvidaste la contraseña de tu propia red WiFi? ¿O necesitás compartirla con una visita y no la recordás? **WiFi Scanner C++** es una herramienta sencilla y eficaz que te permite visualizar todas las contraseñas de las redes WiFi guardadas en tu PC con Windows.

El programa utiliza el comando `netsh wlan show profile key=clear` de Windows para extraer la información de los perfiles almacenados, mostrándola en una interfaz de consola clara y organizada.

## ✨ Características principales

|                                |                                                                                       |
| ------------------------------ | ------------------------------------------------------------------------------------- |
| 🔑 **Ver redes guardadas**     | Muestra todas las redes WiFi conectadas anteriormente con sus respectivas contraseñas |
| 📡 **Escanear redes cercanas** | Detecta redes WiFi disponibles en el entorno y muestra su intensidad de señal         |
| 💾 **Exportar a archivo**      | Guarda los resultados en un archivo `.txt` con nombre personalizable                  |
| 🌍 **Soporte multilingüe**     | Compatible con sistemas en español e inglés                                           |
| 🖥️ **Interfaz intuitiva**      | Menú interactivo fácil de usar                                                        |
| ⚡ **Ligero y rápido**         | No requiere instalación, solo ejecutar el `.exe`                                      |

---

## 🚀 Requisitos

- **Sistema operativo:** Windows (XP, 7, 8, 10, 11)
- **Permisos:** Ejecutar como **Administrador** para ver las contraseñas
- **Compilador:** C++98 o superior (compatible con versiones antiguas)

---

## 📥 Instalación

### Opción 1: Descargar ejecutable (recomendado)

1. Ir a la sección [Releases](https://github.com/EliasTiki951/wifi-scanner-cpp/releases)
2. Descargar el archivo `wifi-scanner-cpp.exe`
3. Ejecutar como Administrador (clic derecho → _"Ejecutar como administrador"_)

### Opción 2: Compilar desde código fuente

```bash
# Clonar el repositorio
git clone https://github.com/EliasTiki951/wifi-scanner-cpp.git
cd wifi-scanner-cpp

# Compilar con Make
make

# O compilar manualmente con g++
g++ -o wifi-scanner-cpp.exe main.cpp
```

---

## 🎮 Uso

1. Ejecutar el programa **como Administrador** (obligatorio para ver contraseñas).
2. Elegir una opción del menú:

```
=============================
    WiFi Scanner C++ v2.0
=============================

¿Qué querés hacer?
  1. Ver redes guardadas y contraseñas
  2. Escanear redes cercanas
  3. Salir

Opción (1-3):
```

- **Opción 1:** lista todas las redes guardadas con sus contraseñas.
- **Opción 2:** escanea redes WiFi disponibles cercanas.
- En ambas opciones se puede guardar el resultado en un archivo `.txt`.

### Ejemplo de salida

```
=== REDES WIFI GUARDADAS ===

Total: 3

[1] MiCasaWiFi
    Clave: 12345678
    ---
[2] Oficina_5G
    Clave: ContraseñaSegura2024
    ---
[3] WiFi_Gratis
    Clave: (Sin contraseña)
    ---

RESUMEN:
Total: 3
Con clave: 2
Abiertas: 1

¿Guardar en .txt? (s/n): s
Nombre (default: wifi_passwords.txt): mis_redes.txt

✓ Guardado en: mis_redes.txt
```

---

## 🛠️ Compilación

**Usando Make (recomendado)**

```bash
make          # Compila el programa
make clean    # Elimina archivos objeto y ejecutable
make run      # Compila y ejecuta
make help     # Muestra todas las opciones disponibles
```

**Usando g++ directamente**

```bash
g++ -o wifi-scanner-cpp.exe main.cpp
```

**Para compiladores antiguos (C++98)**

```bash
g++ -o wifi-scanner-cpp.exe main.cpp -std=c++98
```

---

## 📂 Estructura del proyecto

```
wifi-scanner-cpp/
├── main.cpp                   # Código fuente principal
├── Makefile                   # Archivo de compilación
├── LICENSE                    # Licencia MIT
├── README.md                  # Este archivo
├── .gitignore                 # Archivos ignorados por Git
└── wifi-scanner-cpp.exe       # Ejecutable
```

---

## ⚠️ Advertencia de seguridad

> Este programa solo funciona en tu propia PC y muestra las contraseñas que vos mismo guardaste. No es un "hackeador de WiFi" ni puede acceder a redes ajenas. Es una herramienta de recuperación de contraseñas olvidadas.

**Recomendaciones:**

- No compartas el archivo `wifi_passwords.txt` con nadie.
- Ejecutá siempre como Administrador para que funcione correctamente.
- Usá esta herramienta de forma ética y solo en tus propios equipos.

---

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Si querés mejorar el proyecto:

1. Hacé un **Fork** del repositorio.
2. Creá una rama con tu feature (`git checkout -b feature/mejora`).
3. Hacé commit de tus cambios (`git commit -m 'Agrega nueva funcionalidad'`).
4. Hacé push a la rama (`git push origin feature/mejora`).
5. Abrí un **Pull Request**.

---

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Ver el archivo [LICENSE](LICENSE) para más detalles.

---

<div align="center">

## 👨‍💻 Autor

**Elias Tiquicala** (EliasTiki951)

[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/EliasTiki951)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/elias-tiquicala-7672701b6/)

</div>

---

## 📞 Soporte

Si encontrás algún problema o tenés sugerencias:

- Abrí un [Issue](https://github.com/EliasTiki951/wifi-scanner-cpp/issues)
- Contactame directamente

---

<div align="center">

**¡No olvides dejar una ⭐ si te fue útil!**

</div>

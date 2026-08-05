<div align="center">

# 🔐 WiFi Scanner C++

![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Version](https://img.shields.io/badge/Version-3.0-blue?style=for-the-badge)
![Multi-OS](https://img.shields.io/badge/Multi--OS-Windows%20%7C%20Linux-purple?style=for-the-badge)

**Utilidad de consola para Windows y Linux que permite recuperar las contraseñas de las redes WiFi guardadas en el sistema.**

</div>

---

## 📋 Descripción

¿Alguna vez olvidaste la contraseña de tu propia red WiFi? ¿O necesitás compartirla con una visita y no la recordás? **WiFi Scanner C++** es una herramienta sencilla y eficaz que te permite visualizar todas las contraseñas de las redes WiFi guardadas en tu PC.

El programa utiliza los comandos nativos de cada sistema operativo:

- **Windows:** `netsh wlan show profile key=clear`
- **Linux:** `nmcli` y archivos de NetworkManager

---

## ✨ Características principales

|                                |                                                                                       |
| ------------------------------ | ------------------------------------------------------------------------------------- |
| 🔑 **Ver redes guardadas**     | Muestra todas las redes WiFi conectadas anteriormente con sus respectivas contraseñas |
| 📡 **Escanear redes cercanas** | Detecta redes WiFi disponibles en el entorno y muestra su intensidad de señal         |
| 💾 **Exportar a archivo**      | Guarda los resultados en un archivo `.txt` con nombre personalizable                  |
| 🌍 **Soporte multilingüe**     | Compatible con sistemas en español e inglés                                           |
| 🖥️ **Interfaz intuitiva**      | Menú interactivo fácil de usar                                                        |
| ⚡ **Ligero y rápido**         | No requiere instalación, solo ejecutar el binario                                     |
| 🐧 **Multi-OS**                | Compatible con Windows y Linux                                                        |
| 🔄 **Auto-elevación**          | En Windows se solicita automáticamente permisos de Administrador                      |

---

## 📜 Historial de versiones

| Versión         | Fecha          | Cambios                                                      |
| --------------- | -------------- | ------------------------------------------------------------ |
| **v1.0 (Beta)** | 2026           | Solo mostraba redes guardadas y contraseñas en Windows       |
| **v1.1**        | 2026           | Opción para guardar resultados en `.txt` y arreglos menores  |
| **v2.0**        | 2026           | Escaneo de redes cercanas en Windows. Mejoras en la interfaz |
| **v2.1**        | 2026           | Mejoras en escaneo y muestra de intensidad de señal          |
| **v3.0**        | 2026           | Soporte para Linux (NetworkManager) y mejoras generales      |
| **v3.1**        | _Próximamente_ | Muchas mejoras pendientes para futuras versiones             |

---

## 🚀 Requisitos

### Windows

- **Sistema operativo:** Windows (XP, 7, 8, 10, 11)
- **Permisos:** Ejecutar como **Administrador** (se solicita automáticamente)
- **Compilador:** C++98 o superior

### Linux

- **Sistema operativo:** Cualquier distribución (Ubuntu, Debian, Fedora, Arch, etc.)
- **Permisos:** Ejecutar con **sudo** (root)
- **Dependencias:** NetworkManager (`nmcli` instalado)
- **Compilador:** g++ (C++98 o superior)

---

## 📥 Instalación

### Opción 1: Descargar ejecutable (recomendado)

1. Ir a la sección [Releases](https://github.com/EliasTiki951/wifi-scanner-cpp/releases)
2. Descargar el archivo correspondiente a tu sistema:
   - `wifi-scanner-cpp-v3.exe` → Windows
   - `wifi-scanner-cpp-v3` → Linux
3. Ejecutar según tu sistema:
   - **Windows:** Clic derecho → _"Ejecutar como administrador"_
   - **Linux:** `sudo ./wifi-scanner-cpp-v3`

### Opción 2: Compilar desde código fuente

```bash
# Clonar el repositorio
git clone https://github.com/EliasTiki951/wifi-scanner-cpp.git
cd wifi-scanner-cpp

# Compilar en Linux
make

# Compilar en Windows (con g++ o MinGW)
g++ -o wifi-scanner-cpp.exe main.cpp

---

## ▶️ Uso

1. Ejecutar el programa con permisos de administrador/root.
2. Elegir una opción del menú:

```

==================================
Wifi Scanner C++ v3.0 (Multi-OS)
==================================

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

````

---

## 🛠️ Compilación

**Usando Make (recomendado)**

```bash
make          # Compila el programa
make clean    # Elimina archivos objeto y ejecutable
make run      # Compila y ejecuta
make help     # Muestra todas las opciones disponibles
````

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
└── wifi-scanner-cpp-v3.exe    # Ejecutable
```

---

## ⚠️ Advertencia de seguridad

> Este programa solo funciona en tu propia PC y muestra las contraseñas que vos mismo guardaste. No es un "hackeador de WiFi" ni puede acceder a redes ajenas. Es una herramienta de recuperación de contraseñas olvidadas.

**Recomendaciones:**

- No compartas el archivo `wifi_passwords.txt` con nadie.
- Ejecutá siempre como Administrador/sudo para que funcione correctamente.
- Usá esta herramienta de forma ética y solo en tus propios equipos.
- Eliminá el archivo generado después de usarlo si contiene información sensible.

**Responsabilidad:**
El autor no se hace responsable del uso malintencionado que se le pueda dar a esta herramienta. El programa fue diseñado con fines educativos y de recuperación de contraseñas personales. El usuario es el único responsable del uso que le dé y de cumplir con las leyes aplicables en su país o región.

**Aviso legal:**
El acceso no autorizado a redes WiFi ajenas está penado por la ley en muchos países. Esta herramienta solo debe utilizarse en redes propias o con autorización expresa del propietario. El autor no promueve ni apoya el uso ilegal de este software.

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

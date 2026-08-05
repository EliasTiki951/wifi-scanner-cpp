/*
 * -------------------------------------
 *   Wifi Scanner C++ V.3.0 (Multi-OS)
 * -------------------------------------
 * Utilidad de consola para Windows y Linux que permite consultar las contraseñas
 * de las redes WiFi que el propio equipo ya tiene guardadas
 * Pensada para casos como: "me olvidé la contraseña de mi propio router"
 * o "quiero compartirla con una visita".
 *
 * Requisitos:
 *   - Administrador (Windows) / Root (Linux)
 *   - C++98 o superior
 *
 * Características:
 *   - Ver todas las redes WiFi guardadas con sus contraseñas
 *   - Escanear redes WiFi cercanas con intensidad de señal
 *   - Exportar resultados a archivos .txt
 *   - Interfaz de menú interactiva
 *   - Soporte para sistemas en español e inglés
 *
 * Compilación:
 *   - Linux:   g++ main.cpp -o wifi-scanner
 *   - Windows: g++ main.cpp -o wifi-scanner.exe (No se requieren flags especiales)
 *
 * Ejecución:
 *   - Linux:   sudo ./wifi-scanner
 *   - Windows: wifi-scanner.exe  (se auto-eleva)
 *
 * Versiones Anteriores:
 *   - V.1.0 (Beta): Solo mostraba las redes guardadas y sus contraseñas en Windows.
 *   - V.1.1: Opción para guardar los resultados en un archivo .txt y arreglos menores.
 *   - V.2.0: Escaneo de redes cercanas en Windows. Pequeñas mejoras en la interfaz.
 *   - V.2.1: Pequeñas mejoras con el escaneo de redes cercanas en Windows y con muestra de intensidad de señal.
 *   - V.3.0: Expandimos la compatibilidad a Linux (NetworkManager).
 *   - Hay buenas ideas y muchas mejoras pendientes para futuras versiones.
 *
 * REPOSITORIO:  https://github.com/EliasTiki951/wifi-scanner-cpp?tab=readme-ov-file
 *
 * Autor: EliasTiki
 * Licencia: MIT
 * Versión: 3.0
 * Fecha: 2026
 * Compilador: C++98 o superior (compatible con versiones antiguas)
 * Sistema: Windows (XP, 7, 8, 10, 11) y Linux
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>

// Detectar Sistema Operativo
#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#include <unistd.h>
#include <sys/stat.h>
#endif

// FUNCIONES AUXILIARES COMUNES
std::string intToString(int num)
{
    char buffer[50];
    sprintf(buffer, "%d", num);
    return std::string(buffer);
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string getCurrentDateTime()
{
    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(timeStr);
}

bool saveToFile(const std::string &filename, const std::string &content)
{
    std::ofstream outputFile(filename.c_str());
    if (!outputFile.is_open())
    {
        std::cerr << "ERROR: No se pudo crear el archivo " << filename << std::endl;
        return false;
    }
    outputFile << content;
    outputFile.close();
    return true;
}

void waitForEnter()
{
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

std::string execCommand(const std::string &cmd)
{
    char buffer[4096];
    std::string result = "";
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
        return "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

std::string trimString(std::string str)
{
    while (str.size() > 0 && (str[str.size() - 1] == ' ' || str[str.size() - 1] == '\r' || str[str.size() - 1] == '\n'))
    {
        str.erase(str.size() - 1, 1);
    }
    while (str.size() > 0 && str[0] == ' ')
    {
        str.erase(0, 1);
    }
    return str;
}

// LÓGICA PARA WINDOWS
#ifdef _WIN32

bool isAdminWindows()
{
    bool isAdmin = false;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        TOKEN_ELEVATION elevation;
        DWORD size = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &size))
        {
            isAdmin = elevation.TokenIsElevated;
        }
        CloseHandle(hToken);
    }
    return isAdmin;
}

void runAsAdminWindows()
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    SHELLEXECUTEINFOA sei = {0};
    sei.cbSize = sizeof(SHELLEXECUTEINFOA);
    sei.lpVerb = "runas";
    sei.lpFile = exePath;
    sei.nShow = SW_NORMAL;
    ShellExecuteExA(&sei);
    exit(0);
}

std::vector<std::string> getSavedProfilesWin()
{
    std::vector<std::string> profiles;
    std::string output = execCommand("netsh wlan show profiles");

    size_t pos = 0;
    while (true)
    {
        size_t findPos = output.find("Perfil de todos los usuarios", pos);
        if (findPos == std::string::npos)
        {
            findPos = output.find("All User Profile", pos);
        }
        if (findPos == std::string::npos)
            break;

        size_t colonPos = output.find(':', findPos);
        if (colonPos != std::string::npos)
        {
            size_t endPos = output.find('\n', colonPos);
            if (endPos == std::string::npos)
                endPos = output.length();
            std::string name = trimString(output.substr(colonPos + 2, endPos - colonPos - 2));
            if (!name.empty())
                profiles.push_back(name);
        }
        pos = colonPos + 1;
    }
    return profiles;
}

std::string getPasswordWin(const std::string &profileName)
{
    std::string cmd = "netsh wlan show profile name=\"" + profileName + "\" key=clear";
    std::string output = execCommand(cmd);

    size_t keyPos = output.find("Key Content");
    if (keyPos == std::string::npos)
        keyPos = output.find("Contenido de la clave");
    if (keyPos != std::string::npos)
    {
        size_t colonPos = output.find(':', keyPos);
        if (colonPos != std::string::npos)
        {
            size_t endLine = output.find('\n', colonPos);
            std::string pass = trimString(output.substr(colonPos + 2, (endLine == std::string::npos) ? std::string::npos : endLine - colonPos - 2));
            if (pass == "Ausente" || pass == "Absent" || pass.empty())
                return "(Sin contraseña)";
            return pass;
        }
    }
    return "(Sin contraseña)";
}

std::vector<std::string> scanNetworksWin()
{
    std::vector<std::string> networks;
    system("netsh wlan scan");
    std::string output = execCommand("netsh wlan show networks mode=bssid");

    size_t pos = 0;
    while (true)
    {
        size_t ssidPos = output.find("SSID", pos);
        if (ssidPos == std::string::npos)
            break;
        size_t colonPos = output.find(':', ssidPos);
        if (colonPos != std::string::npos)
        {
            size_t endPos = output.find('\n', colonPos);
            std::string ssid = trimString(output.substr(colonPos + 2, (endPos == std::string::npos) ? std::string::npos : endPos - colonPos - 2));

            if (!ssid.empty() && ssid != "\r")
            {
                size_t signalPos = output.find("Signal", ssidPos);
                if (signalPos == std::string::npos)
                    signalPos = output.find("Señal", ssidPos);

                std::string signal = "N/A";
                if (signalPos != std::string::npos)
                {
                    size_t sigColon = output.find(':', signalPos);
                    size_t sigEnd = output.find('\n', sigColon);
                    signal = trimString(output.substr(sigColon + 2, (sigEnd == std::string::npos) ? std::string::npos : sigEnd - sigColon - 2));
                }
                networks.push_back(ssid + " (Señal: " + signal + ")");
            }
        }
        pos = colonPos + 1;
    }
    return networks;
}

#else
// LÓGICA PARA LINUX
bool isAdminLinux() { return (geteuid() == 0); }
std::vector<std::string> getSavedProfilesLinux()
{
    std::vector<std::string> profiles;
    std::string output = execCommand("ls /etc/NetworkManager/system-connections/ 2>/dev/null");
    size_t start = 0, end;
    while ((end = output.find('\n', start)) != std::string::npos)
    {
        std::string file = output.substr(start, end - start);
        if (file.find(".nmconnection") != std::string::npos)
        {
            size_t dotPos = file.find('.');
            if (dotPos != std::string::npos)
                profiles.push_back(file.substr(0, dotPos));
        }
        start = end + 1;
    }
    return profiles;
}
std::string getPasswordLinux(const std::string &profileName)
{
    std::string cmd = "cat /etc/NetworkManager/system-connections/\"" + profileName + "\".nmconnection | grep -i psk=";
    std::string output = execCommand(cmd);
    size_t equalsPos = output.find('=');
    if (equalsPos != std::string::npos)
        return trimString(output.substr(equalsPos + 1));
    return "(Red abierta o desconocida)";
}
std::vector<std::string> scanNetworksLinux()
{
    std::vector<std::string> networks;
    std::string output = execCommand("nmcli -t -f SSID,SIGNAL dev wifi list");
    size_t start = 0, end;
    while ((end = output.find('\n', start)) != std::string::npos)
    {
        std::string line = output.substr(start, end - start);
        if (!line.empty() && line.find("SSID") != 0)
        {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos)
            {
                std::string ssid = line.substr(0, colonPos);
                std::string signal = line.substr(colonPos + 1);
                if (!ssid.empty() && ssid != "--")
                    networks.push_back(ssid + " (Señal: " + signal + "%)");
            }
        }
        start = end + 1;
    }
    return networks;
}
#endif

// FUNCIONES DE MENÚ
void viewAllNetworks()
{
    clearScreen();
    std::cout << "=== REDES WIFI GUARDADAS ===\n\n";

    std::vector<std::string> profiles;
#ifdef _WIN32
    profiles = getSavedProfilesWin();
#else
    profiles = getSavedProfilesLinux();
#endif

    if (profiles.empty())
    {
#ifdef _WIN32
        std::cout << "No se encontraron perfiles WiFi guardados en Windows.\n";
#else
        std::cout << "No se encontraron redes guardadas en NetworkManager (Linux).\n";
#endif
        waitForEnter();
        return;
    }

    std::cout << "Total: " << profiles.size() << "\n\n";

    std::string content = "=== WIFI PASSWORDS ===\n";
    content += "Fecha: " + getCurrentDateTime() + "\n\n";

    for (size_t i = 0; i < profiles.size(); i++)
    {
        std::string pass;
#ifdef _WIN32
        pass = getPasswordWin(profiles[i]);
#else
        pass = getPasswordLinux(profiles[i]);
#endif

        std::string line = "[" + intToString(i + 1) + "] " + profiles[i] + "\n";
        line += "    Clave: " + pass + "\n";
        line += "    ---\n";

        std::cout << line;
        content += line;
    }

    std::cout << "\n¿Guardar en .txt? (s/n): ";
    char option;
    std::cin >> option;
    std::cin.ignore();

    if (option == 's' || option == 'S')
    {
        std::cout << "Nombre (default: wifi_passwords.txt): ";
        std::string filename;
        std::getline(std::cin, filename);
        if (filename.empty())
            filename = "wifi_passwords.txt";
        if (filename.find(".txt") == std::string::npos)
            filename += ".txt";

        if (saveToFile(filename, content))
        {
            std::cout << "\nGuardado en: " << filename << std::endl;
        }
    }
    waitForEnter();
}

void scanNearbyNetworks()
{
    clearScreen();
    std::cout << "=== ESCANEO WIFI ===\n\n";
    std::cout << "Escaneando... (espera unos segundos)\n\n";

    std::vector<std::string> networks;
#ifdef _WIN32
    networks = scanNetworksWin();
#else
    networks = scanNetworksLinux();
#endif

    std::string content = "=== WIFI SCAN ===\n";
    content += "Fecha: " + getCurrentDateTime() + "\n\n";

    if (networks.empty())
    {
        std::cout << "No se encontraron redes WiFi.\n";
        std::cout << "\nCausas posibles: WiFi desactivado o sin redes disponibles.\n";
    }
    else
    {
        std::sort(networks.begin(), networks.end());
        networks.erase(std::unique(networks.begin(), networks.end()), networks.end());

        std::cout << "Redes encontradas:\n\n";
        for (size_t i = 0; i < networks.size(); i++)
        {
            std::string line = "[" + intToString(i + 1) + "] " + networks[i] + "\n";
            std::cout << line;
            content += line;
        }
        std::cout << "\nTotal: " << networks.size() << std::endl;
        content += "\nTotal: " + intToString(networks.size()) + "\n";
    }

    std::cout << "\n¿Guardar en .txt? (s/n): ";
    char option;
    std::cin >> option;
    std::cin.ignore();

    if (option == 's' || option == 'S')
    {
        std::cout << "Nombre (default: wifi_scan.txt): ";
        std::string filename;
        std::getline(std::cin, filename);
        if (filename.empty())
            filename = "wifi_scan.txt";
        if (filename.find(".txt") == std::string::npos)
            filename += ".txt";

        if (saveToFile(filename, content))
        {
            std::cout << "\nGuardado en: " << filename << std::endl;
        }
    }
    waitForEnter();
}

// MAIN
int main()
{
#ifdef _WIN32
    // Configurar consola para caracteres especiales
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "spanish");

    if (!isAdminWindows())
    {
        std::cout << "Solicitando permisos de Administrador...\n";
        runAsAdminWindows();
        return 0;
    }
#else
    if (!isAdminLinux())
    {
        std::cout << "Advertencia: No tienes permisos de root.\n";
        std::cout << "Se necesita sudo para ver contraseñas. Intenta: sudo ./programa\n\n";
    }
#endif

    int option = 0;
    while (option != 3)
    {
        clearScreen();

#ifdef _WIN32
        std::wcout << L"====================================\n";
        std::wcout << L"  Wifi Scanner C++ V.3.0 (Windows)\n";
        std::wcout << L"====================================\n";
        std::wcout << L"\n¿Qué quieres hacer?\n";
        std::wcout << L"  1. Ver redes guardadas y contraseñas\n";
        std::wcout << L"  2. Escanear redes cercanas\n";
        std::wcout << L"  3. Salir\n";
        std::wcout << L"\nOpción (1-3): ";
#else
        std::cout << "==================================\n";
        std::cout << "  Wifi Scanner C++ V.3.0 (Linux)\n";
        std::cout << "==================================\n";
        std::cout << "\n¿Qué quieres hacer?\n";
        std::cout << "  1. Ver redes guardadas y contraseñas\n";
        std::cout << "  2. Escanear redes cercanas\n";
        std::cout << "  3. Salir\n";
        std::cout << "\nOpción (1-3): ";
#endif

        std::cin >> option;
        std::cin.ignore();

        switch (option)
        {
        case 1:
            viewAllNetworks();
            break;
        case 2:
            scanNearbyNetworks();
            break;
        case 3:
            std::cout << "\n¡Hasta luego!\n";
            break;
        default:
            std::cout << "\nOpción no válida.\n";
            waitForEnter();
            break;
        }
    }
    return 0;
}
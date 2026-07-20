/*
 * --------------------
 *   Wifi Scanner C++
 * --------------------
 * Utilidad de consola para Windows que permite consultar las contraseñas
 * de las redes WiFi que el propio equipo ya tiene guardadas
 * Pensada para casos como: "me olvidé la contraseña de mi propio router" 
 * o "quiero compartirla con una visita".
 *
 * Requiere permisos de Administrador porque Windows exige ese nivel de
 * privilegio para exponer la clave (key=clear) de un perfil WiFi, incluso
 * cuando el usuario consulta su propia PC.
 *
 * Características:
 *   - Ver todas las redes WiFi guardadas con sus contraseñas
 *   - Escanear redes WiFi cercanas con intensidad de señal
 *   - Exportar resultados a archivos .txt
 *   - Interfaz de menú interactiva
 *   - Soporte para sistemas en español e inglés
 *
 * Autor: EliasTiki
 * Licencia: MIT
 * Versión: 2.0
 * Fecha: 2026
 * Compilador: C++98 o superior (compatible con versiones antiguas)
 * Sistema: Windows (XP, 7, 8, 10, 11)
 */

#include <iostream>
#include <string>
#include <windows.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <locale>

// Convierte int a string (compatible con C++98)
std::string intToString(int num) {
    char buffer[50];
    sprintf(buffer, "%d", num);
    return std::string(buffer);
}

// Limpia pantalla
void clearScreen() {
    system("cls");
}

// Pausa hasta que el usuario presione Enter
void waitForEnter() {
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

// Obtiene fecha y hora actual
std::string getCurrentDateTime() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(timeStr);
}

// Guarda texto en un archivo
bool saveToFile(const std::string& filename, const std::string& content) {
    std::ofstream outputFile(filename.c_str());
    if (!outputFile.is_open()) {
        std::cerr << "ERROR: No se pudo crear el archivo " << filename << std::endl;
        return false;
    }
    outputFile << content;
    outputFile.close();
    return true;
}

// Obtiene lista de redes WiFi guardadas
std::vector<std::string> getSavedProfiles() {
    std::vector<std::string> profiles;
    FILE* pipe = _popen("netsh wlan show profiles", "r");
    if (!pipe) return profiles;
    
    std::string output;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        output += buffer;
    }
    _pclose(pipe);

    size_t pos = 0;
    while (true) {
        size_t findPos = output.find("Perfil de todos los usuarios", pos);
        if (findPos == std::string::npos) {
            findPos = output.find("All User Profile", pos);
        }
        if (findPos == std::string::npos) break;
        
        size_t colonPos = output.find(':', findPos);
        if (colonPos != std::string::npos) {
            size_t endPos = output.find('\n', colonPos);
            if (endPos == std::string::npos) endPos = output.length();
            
            std::string profileName = output.substr(colonPos + 2, endPos - colonPos - 2);
            
            // Limpiar espacios
            while (profileName.size() > 0 && (profileName[profileName.size() - 1] == ' ' || 
                   profileName[profileName.size() - 1] == '\r')) {
                profileName.erase(profileName.size() - 1, 1);
            }
            while (profileName.size() > 0 && profileName[0] == ' ') {
                profileName.erase(0, 1);
            }
            
            if (profileName.size() > 0) {
                profiles.push_back(profileName);
            }
        }
        pos = colonPos + 1;
    }
    return profiles;
}

// Obtiene la contraseña de una red WiFi específica
std::string getPasswordForProfile(const std::string& profileName) {
    // Ejecuta: netsh wlan show profile name="Nombre" key=clear
    std::string getCmd = "netsh wlan show profile name=\"" + profileName + "\" key=clear";
    FILE* passPipe = _popen(getCmd.c_str(), "r");
    if (!passPipe) return "(Error)";
    
    std::string passOutput;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), passPipe) != NULL) {
        passOutput += buffer;
    }
    _pclose(passPipe);
    
    // Busca la línea que contiene la contraseña
    std::string password = "(Red abierta)";
    size_t keyPos = passOutput.find("Key Content");
    if (keyPos == std::string::npos) {
        keyPos = passOutput.find("Contenido de la clave");
    }
    
    if (keyPos != std::string::npos) {
        size_t colonPos = passOutput.find(':', keyPos);
        if (colonPos != std::string::npos) {
            size_t endLine = passOutput.find('\n', colonPos);
            if (endLine == std::string::npos) endLine = passOutput.length();
            
            password = passOutput.substr(colonPos + 2, endLine - colonPos - 2);
            
            // Limpiar espacios
            while (password.size() > 0 && (password[password.size() - 1] == ' ' || 
                   password[password.size() - 1] == '\r')) {
                password.erase(password.size() - 1, 1);
            }
            while (password.size() > 0 && password[0] == ' ') {
                password.erase(0, 1);
            }
            
            if (password == "Ausente" || password == "Absent" || password.empty()) {
                password = "(Sin contraseña)";
            }
        }
    }
    return password;
}

// Opción 1: Ver redes guardadas
void viewAllNetworks() {
    clearScreen();
    std::cout << "=== REDES WIFI GUARDADAS ===\n\n";
    
    std::vector<std::string> profiles = getSavedProfiles();
    if (profiles.empty()) {
        std::cout << "No se encontraron perfiles WiFi.\n";
        waitForEnter();
        return;
    }
    
    std::cout << "Total: " << profiles.size() << "\n\n";
    
    int withPass = 0, openNetworks = 0;
    std::string content = "";
    content += "=== WIFI PASSWORDS ===\n";
    content += "Fecha: " + getCurrentDateTime() + "\n\n";
    
    for (size_t i = 0; i < profiles.size(); i++) {
        std::string pass = getPasswordForProfile(profiles[i]);
        
        if (pass == "(Sin contraseña)" || pass == "(Red abierta)") {
            openNetworks++;
        } else if (pass != "(Error)") {
            withPass++;
        }
        
        std::string line = "[" + intToString(i+1) + "] " + profiles[i] + "\n";
        line += "    Clave: " + pass + "\n";
        line += "    ---\n";
        
        std::cout << line;
        content += line;
    }
    
    std::string summary = "\nRESUMEN:\n";
    summary += "Total: " + intToString(profiles.size()) + "\n";
    summary += "Con clave: " + intToString(withPass) + "\n";
    summary += "Abiertas: " + intToString(openNetworks) + "\n";
    
    std::cout << summary;
    content += summary;
    
    // Guardar en archivo
    std::cout << "\n¿Guardar en .txt? (s/n): ";
    char option;
    std::cin >> option;
    std::cin.ignore();
    
    if (option == 's' || option == 'S') {
        std::cout << "Nombre (default: wifi_passwords.txt): ";
        std::string filename;
        std::getline(std::cin, filename);
        if (filename.empty()) filename = "wifi_passwords.txt";
        if (filename.find(".txt") == std::string::npos) filename += ".txt";
        
        if (saveToFile(filename, content)) {
            std::cout << "\n? Guardado en: " << filename << std::endl;
        }
    }
    waitForEnter();
}

// Opción 2: Escanear redes cercanas
void scanNearbyNetworks() {
    clearScreen();
    std::cout << "=== ESCANEO WIFI ===\n\n";
    std::cout << "Escaneando...\n\n";
    
    system("netsh wlan scan");
    Sleep(2000);
    
    FILE* pipe = _popen("netsh wlan show networks mode=bssid", "r");
    if (!pipe) {
        std::cout << "Error al escanear.\n";
        waitForEnter();
        return;
    }
    
    std::string output;
    char buffer[8192];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        output += buffer;
    }
    _pclose(pipe);
    
    std::string content = "=== WIFI SCAN ===\n";
    content += "Fecha: " + getCurrentDateTime() + "\n\n";
    
    int count = 0;
    size_t pos = 0;
    
    while (true) {
        size_t ssidPos = output.find("SSID", pos);
        if (ssidPos == std::string::npos) break;
        
        size_t colonPos = output.find(':', ssidPos);
        if (colonPos != std::string::npos) {
            size_t endPos = output.find('\n', colonPos);
            if (endPos == std::string::npos) endPos = output.length();
            
            std::string ssid = output.substr(colonPos + 2, endPos - colonPos - 2);
            
            // Limpiar espacios
            while (ssid.size() > 0 && (ssid[ssid.size() - 1] == ' ' || ssid[ssid.size() - 1] == '\r')) {
                ssid.erase(ssid.size() - 1, 1);
            }
            while (ssid.size() > 0 && ssid[0] == ' ') {
                ssid.erase(0, 1);
            }
            
            // Buscar señal
            std::string signal = "N/A";
            size_t bssidPos = output.find("BSSID", ssidPos);
            if (bssidPos != std::string::npos) {
                size_t signalPos = output.find("Signal", bssidPos);
                if (signalPos == std::string::npos) {
                    signalPos = output.find("Señal", bssidPos);
                }
                if (signalPos != std::string::npos) {
                    size_t signalColon = output.find(':', signalPos);
                    if (signalColon != std::string::npos) {
                        size_t signalEnd = output.find('\n', signalColon);
                        if (signalEnd == std::string::npos) signalEnd = output.length();
                        signal = output.substr(signalColon + 2, signalEnd - signalColon - 2);
                        
                        while (signal.size() > 0 && (signal[signal.size() - 1] == ' ' || signal[signal.size() - 1] == '\r')) {
                            signal.erase(signal.size() - 1, 1);
                        }
                        while (signal.size() > 0 && signal[0] == ' ') {
                            signal.erase(0, 1);
                        }
                    }
                }
            }
            
            if (!ssid.empty() && ssid != "\r" && ssid != "\n") {
                count++;
                std::string line = "[" + intToString(count) + "] " + ssid + "\n";
                line += "    Señal: " + signal + "\n";
                line += "    ---\n";
                
                std::cout << line;
                content += line;
            }
        }
        pos = colonPos + 1;
    }
    
    if (count == 0) {
        std::cout << "No se encontraron redes.\n";
        std::cout << "\nPosibles causas:\n";
        std::cout << "  - WiFi desactivado\n";
        std::cout << "  - Modo avión activado\n";
        std::cout << "  - Sin redes disponibles\n";
    } else {
        std::cout << "\nTotal: " << count << std::endl;
        content += "\nTotal: " + intToString(count) + "\n";
    }
    
    // Guardar en archivo
    std::cout << "\n¿Guardar en .txt? (s/n): ";
    char option;
    std::cin >> option;
    std::cin.ignore();
    
    if (option == 's' || option == 'S') {
        std::cout << "Nombre (default: wifi_scan.txt): ";
        std::string filename;
        std::getline(std::cin, filename);
        if (filename.empty()) filename = "wifi_scan.txt";
        if (filename.find(".txt") == std::string::npos) filename += ".txt";
        
        if (saveToFile(filename, content)) {
            std::cout << "\n? Guardado en: " << filename << std::endl;
        }
    }
    waitForEnter();
}

// Programa principal
int main() {
    setlocale(LC_ALL, "spanish");
    
    // Verificar administrador
    bool isAdmin = false;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION elevation;
        DWORD size = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &size)) {
            isAdmin = elevation.TokenIsElevated;
        }
        CloseHandle(hToken);
    }
    
    if (!isAdmin) {
        std::cout << "? Ejecuta como Administrador para ver contraseñas.\n\n";
    }
    
    int option = 0;
    while (option != 3) {
        clearScreen();
        std::cout << "=============================\n";
        std::cout << "    Wifi Scanner Cpp v2.0\n";
        std::cout << "=============================\n";
        std::cout << "\n¿Qué quieres hacer?\n";
        std::cout << "  1. Ver redes guardadas y contraseñas\n";
        std::cout << "  2. Escanear redes cercanas\n";
        std::cout << "  3. Salir\n";
        std::cout << "\nOpción (1-3): ";
        
        std::cin >> option;
        std::cin.ignore();
        
        switch (option) {
            case 1: viewAllNetworks(); break;
            case 2: scanNearbyNetworks(); break;
            case 3: std::cout << "\n¡Hasta luego!\n"; break;
            default:
                std::cout << "\nOpción no válida.\n";
                waitForEnter();
                break;
        }
    }
    return 0;
}

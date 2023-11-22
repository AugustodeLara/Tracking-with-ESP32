#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

struct Event {
    std::string controllerId;
    std::string payload;
    std::string timestamp;
};

void readEventsFromFile(const std::string& filename, std::vector<Event>& events) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        Event event;
        std::istringstream iss(line);

        // Ler ID do Controlador
        iss >> event.controllerId;

        // Ler Payload
        std::getline(iss >> std::ws, event.payload, ',');

        // Ler Data/Hora
        std::getline(iss >> std::ws, event.timestamp);

        // Adicionando mensagem de debug
        std::cout << "Lido: ID=" << event.controllerId << ", Payload=" << event.payload << ", Timestamp=" << event.timestamp << std::endl;

        events.push_back(event);
    }

    inputFile.close();
}

int timeStringToSeconds(const std::string& timeStr) {
    std::istringstream iss(timeStr);
    int hours, minutes, seconds;
    char dummy;  // To capture ':' and ' '

    iss >> hours >> dummy >> minutes >> dummy >> seconds;

    return hours * 3600 + minutes * 60 + seconds;
}

bool isBetween(const Event& event, const std::string& start, const std::string& end) {
    int eventTime = timeStringToSeconds(event.timestamp);
    int startTime = timeStringToSeconds(start);
    int endTime = timeStringToSeconds(end);

    // Verifica se o evento está no intervalo [startTime, endTime]
    return (eventTime >= startTime) && (eventTime <= endTime);
}

void listAllEvents(const std::vector<Event>& events) {
    std::cout << "Todos os eventos:" << std::endl;

    for (const auto& event : events) {
        std::cout << "ID do Controlador: " << event.controllerId
                  << ", Payload: " << event.payload
                  << ", Data/Hora: " << event.timestamp
                  << std::endl;
    }
}

void listEventsInInterval(const std::vector<Event>& events, const std::string& start, const std::string& end) {
    std::cout << "Eventos no intervalo de " << start << " a " << end << " AM:" << std::endl;

    for (const auto& event : events) {
        // Verifica se o evento está no intervalo [start, end]
        if (isBetween(event, start, end)) {
            std::cout << "ID do Controlador: " << event.controllerId
                      << ", Payload: " << event.payload
                      << ", Data/Hora: " << event.timestamp
                      << std::endl;
        }
    }
}

int main() {
    std::vector<Event> events;
    readEventsFromFile("eventList.txt", events);

    if (events.empty()) {
        std::cerr << "Nenhum evento encontrado no arquivo." << std::endl;
        return 1;
    }

    // Opção para listar todos os eventos antes de pedir o intervalo ao usuário
    listAllEvents(events);

    std::cout << "\nEscolha uma opção:" << std::endl;
    std::cout << "1. Listar eventos em um intervalo de datas" << std::endl;

    int option;
    std::cin >> option;

    if (option == 1) {
        std::string startStr, endStr;

        std::cout << "Digite a data/hora de início (formato H:MM:SS AM/PM): ";
        std::cin >> startStr;

        std::cout << "Digite a data/hora de término (formato H:MM:SS AM/PM): ";
        std::cin >> endStr;

        listEventsInInterval(events, startStr, endStr);
    }

    return 0;
}

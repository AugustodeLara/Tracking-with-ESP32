#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "UARTConfig.h"

struct Event {
    std::string timestamp;
    std::string controllerId;
    std::string payload;

    // Função de comparação para eventos
    bool operator==(const Event& other) const {
        return (timestamp == other.timestamp &&
                controllerId == other.controllerId &&
                payload == other.payload);
    }
};

std::mutex mtx;
std::condition_variable cv;
bool menuShouldBeDisplayed = false;
bool eventReceived = false;
int estabilizou = 0;  // Adicionando a variável estabilizou
std::string userOption;
std::mutex userInputMutex;
bool userInputComplete = false;  // Variável adicional para indicar que a entrada do usuário foi concluída
std::string userInput;  // Variável para armazenar a entrada do usuário



void showMenu(const std::vector<Event>& eventList);
void readUART(std::vector<Event>& eventList, int& lineIndex, UARTConfig& uart);
void listEventsInInterval(const std::vector<Event>& eventList, const std::string& startDate, const std::string& endDate);
void totalActiveTimeInInterval(const std::vector<Event>& eventList, const std::string& startDate, const std::string& endDate);
void saveToFileThread(std::vector<Event>& eventList);
void getUserOption();

std::string parseTimestamp(const std::string& timestampString) {
    return timestampString;
}

void processPayload(const std::string& lineString, std::string& payloadData) {
    size_t payloadPos = lineString.find("Payload: ");
    payloadData = "";
    if (payloadPos != std::string::npos) {
        payloadPos += 9;
        size_t commaPos = lineString.find(",", payloadPos);
        if (commaPos != std::string::npos) {
            payloadData = lineString.substr(payloadPos, commaPos - payloadPos);
            std::cout << "Payload IF: " << payloadData << std::endl;
        } else {
            payloadData = lineString.substr(payloadPos);
            std::cout << "Payload ELSE: " << payloadData << std::endl;
        }
    }
}

void processControllerId(const std::string& lineString, std::string& controllerIdData) {
    size_t controllerIdPos = lineString.find("ID do Controlador: ");
    controllerIdData = "";
    if (controllerIdPos != std::string::npos) {
        controllerIdPos += 19;
        size_t commaPosID = lineString.find(",", controllerIdPos);
        if (commaPosID != std::string::npos) {
            controllerIdData = lineString.substr(controllerIdPos, commaPosID - controllerIdPos);
            std::cout << "IDCONTROLLER IF: " << controllerIdData << std::endl;
        } else {
            controllerIdData = lineString.substr(controllerIdPos);
            std::cout << "IDCONTROLLER ELSE: " << controllerIdData << std::endl;
        }
    }
}

void processTimestamp(const std::string& lineString, std::string& timestampData) {
    size_t timestampPos = lineString.find("Data/Hora: ");
    timestampData = "";
    if (timestampPos != std::string::npos) {
        timestampPos += 11;
        timestampData = lineString.substr(timestampPos);
    }
}

void saveEventListToFile(const std::vector<Event>& eventList, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída '" << filename << "' para escrita." << std::endl;
        return;
    }

    for (const auto& event : eventList) {
        outputFile << "ID do Controlador: " << event.controllerId
                   << ", Payload: " << event.payload
                   << ", Data/Hora: " << event.timestamp << std::endl;
    }

    outputFile.close();
    std::cout << "Lista de eventos salva em " << filename << std::endl;
}

bool isDuplicateEvent(const Event& newEvent, const std::vector<Event>& eventList) {
    return std::find(eventList.begin(), eventList.end(), newEvent) != eventList.end();
}



void listEventsInInterval(const std::vector<Event>& eventList, const std::string& startDate, const std::string& endDate) {
    // Implementação para listar eventos no intervalo de datas
    std::cout << "Função listEventsInInterval não implementada.\n";
}

void totalActiveTimeInInterval(const std::vector<Event>& eventList, const std::string& startDate, const std::string& endDate) {
    // Implementação para calcular o tempo total ativo no intervalo de datas
    std::cout << "Função totalActiveTimeInInterval não implementada.\n";
}

void readUART(std::vector<Event>& eventList, int& lineIndex, UARTConfig& uart) {
    char buffer[256];
    char lineBuffer[256];

    while (true) {
        int bytesRead = read(uart.getSerialPort(), buffer, sizeof(buffer) - 1);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            for (int i = 0; i < bytesRead; ++i) {
                if (buffer[i] == '\n') {
                    lineBuffer[lineIndex] = '\0';
                    std::cout << "Recebido: " << lineBuffer << std::endl;

                    std::string lineString(lineBuffer);

                    std::string payloadData;
                    processPayload(lineString, payloadData);

                    std::string controllerIdData;
                    processControllerId(lineString, controllerIdData);

                    std::string timestampData;
                    processTimestamp(lineString, timestampData);

                    Event event;
                    event.controllerId = controllerIdData;
                    event.payload = payloadData;
                    event.timestamp = timestampData;

                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        if (!isDuplicateEvent(event, eventList)) {
                            eventList.push_back(event);
                            eventReceived = true;
                            cv.notify_one();
                        }
                    }

                    lineIndex = 0;
                } else {
                    lineBuffer[lineIndex] = buffer[i];
                    ++lineIndex;

                    if (lineIndex >= sizeof(lineBuffer)) {
                        std::cerr << "Aviso: Tamanho do buffer da linha excedido." << std::endl;
                        lineIndex = 0;
                    }
                }
            }
        } else if (bytesRead < 0) {
            std::cerr << "Erro ao ler da porta serial." << std::endl;
            break;
        }
    }
}

void saveToFileThread(std::vector<Event>& eventList) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::vector<Event> eventsToSave;

        {
            std::unique_lock<std::mutex> lock(mtx);

            cv.wait(lock, [&eventList] { return eventReceived || !eventList.empty(); });

            std::cout << "Thread SaveToFile: Recebida notificação.\n";

            if (eventReceived || !eventList.empty()) {
                eventsToSave = std::move(eventList);
                eventReceived = false;
            }
        }

        if (!eventsToSave.empty()) {
            saveEventListToFile(eventsToSave, "eventList15.txt");
        }
    }
}

void getUserInput() {
    while (true) {
        std::string input;
        std::cout << "Digite algo: ";
        std::cin >> input;

        {
            std::lock_guard<std::mutex> lock(userInputMutex);
            userInput = input;
            userInputComplete = true;
            cv.notify_one();
        }
    }
}

void showMenu() {
    std::unique_lock<std::mutex> lock(mtx);
    if (!menuShouldBeDisplayed) {
        return;
    }

    // Implemente a lógica do seu menu aqui
    std::cout << "Menu exibido!\n";

    // Aguarde um curto período para dar tempo de o usuário interagir, se desejar
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Implemente o restante da lógica do seu menu conforme necessário
    std::cout << "Continuando processamento...\n";
}

void displayMenu(std::vector<Event>& eventList) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Aguarda 100 milissegundos
        {
            std::lock_guard<std::mutex> lock(mtx);
            menuShouldBeDisplayed = true;
            cv.notify_one();
        }

        showMenu();

        {
            std::unique_lock<std::mutex> lock(mtx);
            menuShouldBeDisplayed = false;
            cv.wait(lock, [] { return !userInputComplete; });
        }

        // Processar userInput conforme necessário
        {
            std::lock_guard<std::mutex> lock(userInputMutex);
            std::cout << "Usuário digitou: " << userInput << std::endl;
            userInputComplete = false;
        }
    }
}





int main() {
    UARTConfig uart("/dev/ttyACM0", B115200);

    if (!uart.openPort() || !uart.configurePort()) {
        return 1;
    }

    std::vector<Event> eventList;

    char buffer[256];
    char lineBuffer[256];
    int lineIndex = 0;

    std::thread uartThread(readUART, std::ref(eventList), std::ref(lineIndex), std::ref(uart));
    std::thread menuThread(displayMenu, std::ref(eventList));
    std::thread saveToFile(saveToFileThread, std::ref(eventList));
    //std::thread userInputThread(getUserOption);

    while (true) {
        // Adicione suas operações principais aqui.

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    uartThread.join();
    saveToFile.join();
    menuThread.join();

    close(uart.getSerialPort());

    return 0;
}
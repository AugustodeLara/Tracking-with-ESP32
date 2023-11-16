#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int serialPort = open("/dev/ttyACM0", O_RDWR);

    if (serialPort == -1) {
        std::cerr << "Erro ao abrir a porta serial." << std::endl;
        return 1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(serialPort, &tty) != 0) {
        std::cerr << "Erro ao obter os atributos da porta serial." << std::endl;
        return 1;
    }

    tty.c_cflag &= ~PARENB;    // Desativa a paridade
    tty.c_cflag &= ~CSTOPB;    // Configura 1 bit de parada
    tty.c_cflag &= ~CSIZE;     // Limpa os bits de tamanho de caractere
    tty.c_cflag |= CS8;        // Configura 8 bits de dados
    tty.c_cflag &= ~CRTSCTS;   // Desativa o controle de fluxo

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;  // Alteração aqui: espera pelo menos 1 caractere
    tty.c_cc[VTIME] = 0; // Alteração aqui: sem timeout

    if (cfsetispeed(&tty, B115200) != 0 || cfsetospeed(&tty, B115200) != 0) {
        std::cerr << "Erro ao configurar a velocidade da porta serial." << std::endl;
        return 1;
    }

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        std::cerr << "Erro ao aplicar os atributos da porta serial." << std::endl;
        return 1;
    }

    char buffer[256];

    while (true) {
        int bytesRead = read(serialPort, buffer, sizeof(buffer) - 1);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::cout << "Recebido: " << buffer << std::endl;
        } else if (bytesRead < 0) {
            std::cerr << "Erro ao ler da porta serial." << std::endl;
            break;
        }
    }

    close(serialPort);

    return 0;
}


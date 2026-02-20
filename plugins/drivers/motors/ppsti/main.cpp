#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for std::stof
#include "driver.h"

int main(int argc, char* argv[]) {
    std::string serial_port = "/dev/ttyACM0";

    // === Case 1: INIT MODE ===
    if (argc >= 2 && std::string(argv[1]) == "init") {
        if (argc == 3) {
            serial_port = argv[2];
        }

        std::cout << "[Host] Sending initialization command to Pi Pico...\n";
        std::string init_response = avoe_ppsti::sendAndReceive("INIT_THRUSTERS\n", serial_port);

        if (init_response.find("THRUSTERS_INITIALIZED") != std::string::npos) {
            std::cout << "[Host] Pico confirmed: " << init_response << "\n";
            return 0;
        } else {
            std::cerr << "[Host] Error: Did not receive THRUSTERS_INITIALIZED\n";
            std::cerr << "[Host] Received: " << init_response << "\n";
            return 1;
        }
    }
    else if (argc >= 2 && std::string(argv[1]) == "deinit") {
        if (argc == 3) {
            serial_port = argv[2];
        }

        std::cout << "[Host] Sending deinitialization command to Pi Pico...\n";
        std::string deinit_response = avoe_ppsti::sendAndReceive("DEINIT_THRUSTERS\n", serial_port);

        if (deinit_response.find("THRUSTERS_DEINITIALIZED") != std::string::npos) {
            std::cout << "[Host] Pico confirmed: " << deinit_response << "\n";
            return 0;
        } else {
            std::cerr << "[Host] Error: Did not receive THRUSTERS_DEINITIALIZED\n";
            std::cerr << "[Host] Received: " << deinit_response << "\n";
            return 1;
        }
    }

    // === Case 2: PWM MODE ===
    if (argc < 7 || argc > 8) {
        std::cerr << "Usage:\n";
        std::cerr << "  " << argv[0] << " init [serial_port]                  -> Initialize thrusters\n";
        std::cerr << "  " << argv[0] << " deinit [serial_port]                -> Deinitialize thrusters\n";
        std::cerr << "  " << argv[0] << " t1 t2 t3 t4 t5 t6 [serial_port]   -> Send PWM values\n";
        return 1;
    }

    std::vector<float> input_values;
    for (int i = 1; i <= 6; ++i) {
        float val;
        try {
            val = std::stof(argv[i]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid float value for thruster" << i << ": " << argv[i] << "\n";
            return 1;
        }

        if (val < -1.0f || val > 1.0f) {
            std::cerr << "Error: Thruster value out of range (-1.0 to 1.0): " << val << "\n";
            return 1;
        }
        input_values.push_back(val);
    }

    if (argc == 8) {
        serial_port = argv[7];
    }

    std::vector<int> pwm_values = avoe_ppsti::convertToPWM(input_values);
    std::string pwm_command = avoe_ppsti::encodeToCommand(pwm_values) + "\n";

    std::string pwm_response = avoe_ppsti::sendAndReceive(pwm_command, serial_port);
    std::cout << "[Host] Sent PWM command. Response: " << pwm_response << std::endl;

    return 0;
}

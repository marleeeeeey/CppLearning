#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

enum class CarOption
{
    none, beep,
};

std::ostream & operator<<(std::ostream & os, const CarOption & opt)
{
    using symbol_type = std::string;

    const std::map<CarOption, symbol_type> symbol_map =
    {
        { CarOption::none, "" },
        { CarOption::beep, " beep" },
    };

    os << symbol_map.at(opt);

    return os;
}

enum class CarCommand
{
    left, right, beep,
};

using raw_command = char;
CarCommand make_command(const raw_command & rcmd)
{
    const std::map<raw_command, CarCommand> cmd_map =
    {
        { 'L', CarCommand::left },
        { 'R', CarCommand::right },
        { 'B', CarCommand::beep },
    };

    return cmd_map.at(rcmd);
}

enum class CarDirection
{
    N, W, S, E, last_direction=E, first_direction=N,
};

std::ostream & operator<<(std::ostream & os, const CarDirection & dir)
{
    using symbol_type = char;

    const std::map<CarDirection, symbol_type> symbol_map =
    {
        { CarDirection::N, '^' },
        { CarDirection::E, '>' },
        { CarDirection::W, '<' },
        { CarDirection::S, 'v' },
    };

    os << symbol_map.at(dir);

    return os;
}

CarDirection move_left(const CarDirection & prev_dir)
{
    if(prev_dir == CarDirection::last_direction)
        return CarDirection::first_direction;

    int dir_index = static_cast<int>(prev_dir);
    dir_index++;
    return static_cast<CarDirection>(dir_index);
}

CarDirection move_right(const CarDirection & prev_dir)
{
    if (prev_dir == CarDirection::first_direction)
        return CarDirection::last_direction;

    int dir_index = static_cast<int>(prev_dir);
    dir_index--;
    return static_cast<CarDirection>(dir_index);
}

class CarSimulator
{
    friend std::ostream & operator<<(std::ostream & os, const CarSimulator & car);

public:
    void set_command(CarCommand & cmd)
    {
        if (cmd == CarCommand::beep)
            m_car_option = CarOption::beep;
        else
            m_car_option = CarOption::none;

        if (cmd == CarCommand::left)
            m_direction = move_left(m_direction);
        else if (cmd == CarCommand::right)
            m_direction = move_right(m_direction);
    }
    
private:
    CarDirection m_direction = CarDirection::N;
    CarOption m_car_option = CarOption::none;
};

std::ostream & operator<<(std::ostream & os, const CarSimulator & car)
{
    os << car.m_direction << car.m_car_option;
    return os;
}

void parse_string(std::istream & is, std::ostream & os)
{
    char ch;
    CarSimulator car_simulator;
    os << car_simulator << std::endl;
    while (is.get(ch) && is.good())
    {
        if (ch == '\n')
            continue;

        CarCommand cmd = make_command(ch);
        car_simulator.set_command(cmd);
        os << car_simulator << std::endl;
    }    
}

int main()
{
    parse_string(std::istringstream("LLBR"), std::cout);
    std::cin.get();
}

#include "/home/Andrew/Documents/hydrobotics/AVOEMK2/AVOE/core/motor.cpp"
// bph bsh sh y ps ss
void set_TDG_Thurst(motor_t bph, motor_t bsh,motor_t sh,motor_t y,motor_t ps,motor_t ss)
{
    char* values[6];

    values[0] = bph.read(0);
    values[1] = bsh.read(0);
    values[2] = sh.read(0);
    values[3] = y.read(0);
    values[4] = ps.read(0);
    values[5] = ss.read(0);

    //writetomotrs(values);
    
}
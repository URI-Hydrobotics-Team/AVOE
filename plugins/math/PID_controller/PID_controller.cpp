#include "PID_controller.h"

PID_controller::PID_controller(double p, double i, double d, double t, double lmin, double lmax, double lmini, double lmaxi, double time){
    Kp = p;
    Ki = i;
    Kd = d;
    limMin = lmin;
    limMax = lmax;
    limMinInt = lmini;
    limMinInt = lmaxi;
    T = time;
    // windup = false;
}

PID_controller::PID_controller(double p, double i, double d, double t, double lmin, double lmax, double time){
    Kp = p;
    Ki = i;
    Kd = d;
    limMin = lmin;
    limMax = lmax;
    // limMinInt = lmini;
    // limMinInt = lmaxi;
    T = time;
    windup = false;
}

void PID_controller::init(){
    integrator = 0;
    prevError = 0;
    diff = 0;
    prevMeasurement = 0;
}

void PID_controller::reset(){
    integrator = 0;
    diff = 0;
    windup = false;
    prevError = 0;
    prevMeasurement = 0;
}

double PID_controller::getOutput(){
    return out;
}

double PID_controller::getIntegral(){
    return integrator;
}

double PID_controller::getDerivative(){
    return diff;
}

bool PID_controller::isWindUp(double error, double prev_output, double after_output){
    if ((prev_output != after_output) && ((error < 0 && prev_output < 0) or (error > 0 && prev_output > 0))){
        return true;
    }

    return false;
}

void PID_controller::setKp(double new_kp){
    Kp = new_kp;
}

void PID_controller::setKi(double new_ki){
    Ki = new_ki;
}

void PID_controller::setKd(double new_kd){
    Kd = new_kd;
}

double PID_controller::update(double setpoint, double measurement){
    /* error signal */
    double error = setpoint - measurement;

    /*proportional */
    double proportional = Kp * error;				

    /* integral*/
    // only accumulate error if the integral is not wind up, else switch off integral, as it shouldn't change at that case
    if (!windup) {
        integrator += 0.5 * Ki * T * (error + prevError);
    }

    /* derivative (calculation already have a low pass filter built in)*/
    diff = -(2.0f * Kd * (measurement - prevMeasurement) + (2.0f * tau - T) * diff) / (2.0f * tau + T);

    /* Compute output and apply limit */
    out = proportional + integrator + diff;

    // store the error before the output saturation check to compare later
    double prev_out = out;

    // output saturation check
    if (out > limMax) {

        out = limMax;

    }else if (out < limMin) {

        out = limMin;

    }

    // conditional intergration for anti-wind-up
    // if the integral term is wind up, 
    if(isWindUp(error, prev_out, out)){
        windup = true;
    }else {
        windup = false;
    }

    prevError = error;
    prevMeasurement = measurement;

    /* Return controller output */
    return out;

}


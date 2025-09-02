/*
	URI Hydrobotics PID Controller for Tardigrade


*/

class PID_controller{

	private:
		double Kp, Ki, Kd;
		double tau;
		double limMin, limMax; //output limits
		double limMinInt, limMaxInt; //integrator limits
		double T; //sample time
		double integrator, prevError, diff, prevMeasurement;
		double out;
		bool windup;

	public:
		//initialization
		PID_controller(double p, double i, double d, double t, double lmin, double lmax, double lmini, double lmaxi, double time);
		PID_controller(double p, double i, double d, double t, double lmin, double lmax, double time);

		void init();

		// reset some internal variables 
		// including: integrator, prevError, diff, prevMeasurement, and wind up
		void reset();

		// return the integral of the PID controller
		double getIntegral();

		// return the derivative of the PID controller
		double getDerivative();

		// get the current output 
		double getOutput();

		// function to change the Kp value
		void setKp(double new_kp);

		// function change the Ki value
		void setKi(double new_ki);

		// function to change the Kd value
		void setKd(double new_kd);

		// check if integral is wind up 
		bool isWindUp(double error, double prev_output, double after_output);

		// compute and return the output from the PID controller
		double update(double setpoint, double measurement);

};
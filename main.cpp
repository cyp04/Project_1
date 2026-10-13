#include <iostream>

struct _capacitor
{
	double *time;		// Time array
	double *voltage;	// Voltage array
	double *current;	// Current array
	double C;		// Capacitance value
};

typedef struct _capacitor Capacitor;

int main()
{
	// Values provided in the project description
	const double dt = 1e-10;
	const double final_time = 5e-6;
	const int timesteps = 50000;
	const double R = 1000.0;
	const double capacitance = 100e-12;
	const double supply_current = 1e-2;
	const double V0 = 10.0;

	// Create a structure for each charging circuit.
	Capacitor constant_current;
	Capacitor constant_voltage;

	constant_current.C = capacitance;
	constant_voltage.C = capacitance;

	// Allocate space for 50,000 timesteps and the initial conditions
	constant_current.time = new double[timesteps + 1];
	constant_current.voltage = new double[timesteps + 1];
	constant_current.current = new double[timesteps + 1];

	constant_voltage.time = new double[timesteps + 1];
	constant_voltage.voltage = new double[timesteps + 1];
	constant_voltage.current = new double[timesteps + 1];

	// Set the initial conditions for the constant current circuit
	constant_current.time[0] = 0.0;
	constant_current.voltage[0] = 0.0;
	constant_current.current[0] = supply_current;

	// Set the initial conditions for the constant voltage circuit
	constant_voltage.time[0] = 0.0;
	constant_voltage.voltage[0] = 0.0;
	constant_voltage.current[0] = V0 / R;

	// Start a timestamp 1 and calculate values from the previous timestep
	for (int i = 1; i <= timesteps; i++)
	{
		constant_current.time[i] = i * dt;
		constant_voltage.time[i] = i * dt;

		// Current stays constant for the constant current supply
		constant_current.current[i] = supply_current;

		// Update capacitor voltage using the finite-difference equation
		constant_current.voltage[i] = 
			constant_current.voltage[i - 1]
			+ constant_current.current[i - 1] * dt
			/ constant_current.C;

		// Update current using the finite-difference equation
		constant_voltage.current[i] = 
			constant_voltage.current[i - 1]
			- constant_voltage.current[i - 1] * dt
			/ (R * constant_voltage.C);

		// Use KVL to calculate the capacitor voltage: Vc = V0 - IR
		constant_voltage.voltage[i] = 
			V0 - constant_voltage.current[i] * R;
	}

	// Print constant current circuit results every 200 timesteps
	std::cout << "Constant Current Supply\n";
	std::cout << "Final time: " << final_time << " s\n";
	std::cout << "Time (s)\tVoltage (V)\tCurrent (A)\n";

	for (int i = 0; i <= timesteps; i += 200)
	{
		std::cout << constant_current.time[i] << "\t"
			  << constant_current.voltage[i] << "\t"
			  << constant_current.current[i] << "\n";
	}

	// Print constant voltage circuit results every 200 timesteps 
	std::cout << "\nConstant Voltage supply\n";
	std::cout << "Final time: " << final_time << "s\n";
	std::cout << "Time (s)\tVoltage (V)\tCurrent (A)\n";

	for (int i = 0; i <= timesteps; i += 200)
	{
		std::cout << constant_voltage.time[i] << "\t"
			  << constant_voltage.voltage[i] << "\t"
			  << constant_voltage.current[i] << "\n";
	}

	// Free the dynamically allocated arrays
	delete[] constant_current.time;
	delete[] constant_current.voltage;
	delete[] constant_current.current;

	delete[] constant_voltage.time;
	delete[] constant_voltage.voltage;
	delete[] constant_voltage.current;

	return 0;
}

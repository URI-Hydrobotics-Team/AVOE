/*

   URI Hydrdobotics
   AVOE sensor class

   Sensor drivers will interface with each sensor object. The vehicle class will hold sensor objects and provide an interface for accessing them.

*/


#ifndef SENSOR_H
#define SENSOR_H

#include "log.h"
#include "../lib/lib.h"


/// @brief Sensor drivers will interface with each sensor object. The vehicle class will hold sensor objects and provide an interface for accessing them.
class sensor_t{

	private:
		char *model, *vendor, *protocol, *type, **data;
		int state = 0; ///< 0 = Uninitialized, 1 = ready		
		size_t field_count; ///< How many values the sensor outputs
		/* positioning */
		vector_t offset; //position offset from center of vehicle in mm
		vector_t facing; //direction the sensor is pointed torwads if applicable

	public:

		sensor_t(size_t fields);
		~sensor_t();
		/** @brief Initializes the sensor by taking the arguments as below
		* @param m Model
		* @param v Vendor
		* @param p Protocol
		* @param t Type
		* @param off  \e Offset: position offset from the center of the Vehicle in mm.
		* @param face \e Facing: direction on where the sensor is pointed.
		**/
		void init(const char *m, const char *v, const char *p, const char *t, vector_t off, vector_t face);
		void local_update(const char *t, const char* model);
		char *getModel();
		char *getVendor();
		char *getProtocol();
		char *getType();
		char *read(size_t field);
		void init();
		int getState();
		void write(const char *input, size_t field, size_t n);
		void log(log_t *log);
		void print();
		size_t getFieldCount();
		size_t getBufferSize(); //used for io.h
		void writeToBuffer(char *buffer); // used for io.h 



};

#endif

#ifndef __I_SENSOR_H__
#define __I_SENSOR_H__

class ISensor{

	/**
	* Gets a value indicating if the communication port with the device is open
	*/
	bool isOpen() const = 0;

	/**
	* Gets a value indicating if the continous asynchronous read operation of the sensor has been started
	*/
	bool started() const = 0;

	/**
	* Connects to the sensor device
	*/
	void connect() = 0;

	/**
	* Disconnects from the sensor device
	*/
	void disconnect() = 0;

	/**
	* Starts the continous asynchronous read of the sensor
	*/
	void start() = 0;

	/**
	* Stops the continous asynchronous read of the sensor
	*/
	void stop() = 0;
}

#endif // __I_SENSOR_H__
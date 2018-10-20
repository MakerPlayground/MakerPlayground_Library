#ifndef MP_BLYNK_H
#define MP_BLYNK_H

class MP_NETPIE 
{
public:
	virtual int init();
	virtual void update(unsigned long current_time);
	virtual void printStatus();
	static const char* const* ERRORS;

	virtual void publish(char* topic, double value);
	virtual void subscribe(char* topic);
	virtual void unsubscribe(char* topic);
	double getValue(char* topic);
};

#endif
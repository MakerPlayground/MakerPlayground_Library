#ifndef MP_NETPIE2020_H
#define MP_NETPIE2020_H

class MP_NETPIE2020 
{
public:
	virtual int init();
	virtual void update(unsigned long current_time);
	virtual void printStatus();

	virtual void publish(char* topic, double value);
	virtual void subscribe(char* topic);
	virtual void unsubscribe(char* topic);
	virtual double getValue(char* topic);
};

#endif
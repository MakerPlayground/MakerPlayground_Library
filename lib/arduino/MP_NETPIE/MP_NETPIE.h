#ifndef MP_NETPIE_H
#define MP_NETPIE_H

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
	virtual double getValue(char* topic);
	virtual void writeFeed(char* feedId, String data, char* apiKey);
};

#endif
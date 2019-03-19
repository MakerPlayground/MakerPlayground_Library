#ifndef MP_REST_H
#define MP_REST_H

class MP_REST
{
public:
    virtual int init();
	virtual void update(unsigned long currentTime);
	virtual void printStatus();

    virtual bool isConnected();
};

#endif
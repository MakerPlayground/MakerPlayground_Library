#ifndef MP_AZURE_H
#define MP_AZURE_H

class MP_AZURE
{
public:
    virtual int init();
	virtual void update(unsigned long currentTime);
	virtual void printStatus();

    virtual bool isConnected();
};

#endif
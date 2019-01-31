#ifndef MP_REST_H
#define MP_REST_H


class MP_REST
{
public:
    virtual int init();
	virtual void update(unsigned long currentTime);
	virtual void printStatus();
	static const char* const* ERRORS;

    virtual bool isConnected();
};

#endif
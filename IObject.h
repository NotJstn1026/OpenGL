#pragma once
class IObject {
public:
	const virtual int Initialize(void) = 0;
	const virtual int Update(void) = 0;
	const virtual int Draw(void) = 0;
	const virtual int Finalize(void) = 0;
};


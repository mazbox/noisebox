#pragma once

class Parameter {
public:
	Parameter(float defaultValue) {
		this->value = defaultValue;
		this->target = this->value;
		lerp = 0.9996;
	}
	void set(float target) {
		this->target = target;
	}
	
	// only call this once a frame
	float get() {
		this->value = this->value * lerp + this->target * (1.f - lerp);
		return this->value;
	}
private:
	float value;
	float target;
	float lerp;
};
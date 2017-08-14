#ifndef _H_TIMING_H_
#define _H_TIMING_H_

//Will hold on timing classes and functions

namespace EngineProject2D {
	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float maxFPS);
		void setMaxFPS(float maxFPS);
		void begin();
		float end(); //Will return fps
	private:
		void calculateFPS();
		float m_maxFPS;
		unsigned int m_startTicks; //unsigned int is not guaranteed to be 4 bytes.
		float m_frameTime;
		float m_fps;
	};
}

#endif // !_H_TIMING_H_